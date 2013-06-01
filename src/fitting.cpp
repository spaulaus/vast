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
string fileName = "1000keV";

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
    double maxTof = 120;
    double fitMax = maxTof;
    RooRealVar tof("tof","tof",0,maxTof);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    double peaks[]={60.};
    double areaStart = 100.;
    double resolution0 = 3.375;
    double resolution1 = 5.805;
    double wiggle0 = 3.;
    double wiggle1 = 10.;

    //---------- Constants ----------
    RooRealVar sigma0("sigma0", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))));
    RooRealVar sigma1("sigma1", "sigma for the gaussians", 
                      resolution1/(2*sqrt(2*log(2))), 0., 100.);

    //---------- Pdfs ----------
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle1, peaks[0]+wiggle1);
    RooRealVar alpha("alpha", "", -1.0, -100., 0.);
    RooRealVar n("n", "", 1., -100., 200.);
    RooCBShape model("model", "", tof, mu0, sigma1, alpha, n);
                  
    ///////////////////////////////////
    //RooNumConvPdf model("model","model", tof, core0, gp);
                     //model.setConvolutionWindow(mu0, sigma0, 5);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(50., fitMax));

    ofstream resultsParam(resultsFile.c_str());
    fitResult->printMultiline(resultsParam, 0, false, "");
    resultsParam.close();
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(maxTof);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events/ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    data->plotOn(frame,Name("data"));
    
    model.plotOn(frame,Name("model"));

    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    c->SetFillColor(kWhite);
    frame->Draw();
    c->SaveAs(epsName.c_str());
}
