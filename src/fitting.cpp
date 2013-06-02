#include <iostream>
#include <iomanip>

#include <cmath>
#include <cstdio>

#include "TFile.h"
#include "RooBreitWigner.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooDecay.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooNumConvPdf.h"
#include "RooCBShape.h"
#include "RooGenericPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

using namespace std;
using namespace RooFit;

void fitting(void);

string dirName = "tofSim/";
string fileName = "all";

string dataName="../data/roofit/"+dirName+fileName+".dat";
string resultsFile = "results/"+dirName+fileName+".fit";
string epsName = "../pics/roofit/"+dirName+fileName+".eps";

//string epsName = "../pics/roofit/working.eps";
//string resultsFile = "results/working.dat";

int main(int argc, char* argv[]) {
    ifstream test(dataName.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the data file to read in the sexy data!!" << endl << endl;
        exit(1);
    }
    fitting();
}

void fitting(void) {
    //Read in the data and set the variable to fit.
    double low = 0.;
    double high = 120.;
    RooRealVar tof("tof","tof", low, high);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    double peaks[]={15., 35., 60.};
    double areaStart = 1000.;
    double resolution0 = 0.375;
    double resolution1 = 5.805;
    double wiggle0 = 3.;
    double wiggle1 = 50.;

    //---------- Constants ----------
    // RooRealVar sigma0("sigma0", "sigma for the gaussians", 
    //                   resolution0/(2*sqrt(2*log(2))), 0., 100.);
    // RooRealVar sigma1("sigma1", "sigma for the gaussians", 
    //                   resolution1/(2*sqrt(2*log(2))), 0., 100.);

    //---------- Pdfs ----------
    RooRealVar yield0("yield0", "", 3000., 0., 1.e7);
    RooRealVar sigma0("sigma0", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))), 0., 100.);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle1, peaks[0]+wiggle1);
    RooRealVar alpha0("alpha", "", -1.0, -5000., 0.);
    RooRealVar n0("n0", "", 3., 0., 500.);
    RooCBShape cb0("cb0", "", tof, mu0, sigma0, alpha0, n0);

    RooRealVar yield1("yield1", "", 3000., 0., 1.e7);
    RooRealVar sigma1("sigma1", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))), 0., 100.);
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle1, peaks[1]+wiggle1);
    RooRealVar alpha1("alpha1", "", -1.0, -5000., 0.);
    RooRealVar n1("n1", "", 3., 0., 500.);
    RooCBShape cb1("cb1", "", tof, mu1, sigma1, alpha1, n1);

    RooRealVar yield2("yield2", "", 3000., 0.,  1.e7);
    RooRealVar sigma2("sigma2", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))), 0., 100.);
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle1, peaks[2]+wiggle1);
    RooRealVar alpha2("alpha2", "", -1.0, -5000., 0.);
    RooRealVar n2("n2", "", 3., 0., 500.);
    RooCBShape cb2("cb2", "", tof, mu2, sigma2, alpha2, n2);

    RooArgList cbs(cb0,cb1,cb2);
    RooArgList yields(yield0, yield1, yield2);

    RooAddPdf model("model", "", cbs, yields);

    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(low, high));

    ofstream resultsParam(resultsFile.c_str());
    fitResult->printMultiline(resultsParam, 0, false, "");
    resultsParam.close();
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(high);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events/ns");
    
    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    //c->SetFillColor(kWhite);
    frame->Draw();
    c->SaveAs(epsName.c_str());
}
