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
// string epsName = "../pics/roofit/"+dirName+fileName+".eps";
// string resultsFile = "results/"+dirName+fileName+".fit";

string epsName = "../pics/roofit/working.eps";
string resultsFile = "results/working.dat";

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

    //Set the information for the peaks
    double peaks[]={10., 35., 60.};
    double wiggle0 = 10.;

    //Set the information for the yields
    double yieldStart = 3.e3;
    double yieldLow = 0.0;
    double yieldHigh = 1.e7;

    //Set the information for the sigmas.
    double res0 = 3.375 / (2*sqrt(2*log(2)));
    double res1 = 5.805 / (2*sqrt(2*log(2)));
    double resLow = 0.;
    double resHigh = 10.;

    //Set the information for the power parameter
    double nStart = 1.;
    double nLow = 0.;
    double nHigh = 5.;
    
    //Set the information for the scaling
    double aStart = -1.0;
    double aLow = -10.;
    double aHigh = 0.;

    //---------- Constants ----------
    // RooRealVar sigma0("sigma0", "", res0);
    // RooRealVar sigma1("sigma1", "", res1);

    //RooRealVar n("n","",1.0);

    //---------- Pdfs ----------
    RooRealVar yield0("yield0", "", yieldStart, yieldLow, yieldHigh);
    RooRealVar sigma0("sigma0", "", res1, resLow, resHigh);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle0, peaks[0]+wiggle0);
    RooRealVar alpha0("alpha", "", aStart, aLow, aHigh);
    RooRealVar n0("n0", "", nStart, nLow, nHigh);
    RooCBShape cb0("cb0", "", tof, mu0, sigma0, alpha0, n0);

    RooRealVar yield1("yield1", "", yieldStart, yieldLow, yieldHigh);
    RooRealVar sigma1("sigma1", "", res1, resLow, resHigh);
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle0, peaks[1]+wiggle0);
    RooRealVar alpha1("alpha1", "", aStart, aLow, aHigh);
    RooRealVar n1("n1", "", nStart, nLow, nHigh);
    RooCBShape cb1("cb1", "", tof, mu1, sigma1, alpha1, n1);

    RooRealVar yield2("yield2", "", yieldStart, yieldLow, yieldHigh);
    RooRealVar sigma2("sigma2", "", res1, resLow, resHigh);
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle0, peaks[2]+wiggle0);
    RooRealVar alpha2("alpha2", "", aStart, aLow, aHigh);
    RooRealVar n2("n2", "", nStart, nLow, nHigh);
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
    frame->SetMaximum(high);
    frame->GetYaxis()->SetTitleOffset(1.2);
    
    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    frame->Draw();
    c->SaveAs(epsName.c_str());
}
