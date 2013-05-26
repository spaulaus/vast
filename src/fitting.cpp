#include <iostream>
#include <iomanip>

#include <cmath>
#include <cstdio>

#include "TFile.h"
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
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

using namespace std;
using namespace RooFit;

void fitting(void);

string dirName = "tofSim/";
string fileName = "0300keV";

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
    double maxTof = 68;
    double fitMax = maxTof;
    RooRealVar tof("tof","tof",0,maxTof);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    double peaks[]={63.659, 22.3378, 26.111, 31.111, 34.222, 40.444, 43, 45.778, 
                    49.778, 56, 60.444, 64.222, 70.667, 77.333, 84.889, 87,
                    92.889, 95, 102.222, 108, 111.111, 115, 118, 120};
    double areaStart = 100;
    double resolution0 = 3.375;
    double resolution1 = 5.805;
    double wiggle = 3;

    //---------- Constants ----------
    RooRealVar sigma0("sigma0", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))));
    RooRealVar sigma1("sigma1", "sigma for the gaussians", 
                      resolution1/(2*sqrt(2*log(2))));

    //---------- Pdfs ----------
    RooRealVar alpha0("alpha0","number of events in peak 0", areaStart, 0, 2000);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooGaussModel core0("core0", "Gaussian for resolution", tof, mu0, sigma0);

    RooArgList prodList(core0);
    RooArgList areaList(alpha0);
    
    // /////////////////////////////////
    RooAddPdf model("model","model", prodList, areaList);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(0., fitMax));

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
