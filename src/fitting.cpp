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
    double maxTof = 120;
    double fitMax = maxTof;
    RooRealVar tof("tof","tof",0,maxTof);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    double peaks[]={30.};
    double areaStart = 100.;
    double resolution0 = 3.375;
    double resolution1 = 5.805;
    double wiggle0 = 3.;
    double wiggle1 = 10.;

    //---------- Constants ----------
    RooRealVar sigma0("sigma0", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))));
    RooRealVar sigma1("sigma1", "sigma for the gaussians", 
                      resolution1/(2*sqrt(2*log(2))), 0., 10.);

    //---------- Pdfs ----------
    RooRealVar yield0("yield0","number of events in peak 0", areaStart, 0, 2000);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle0, peaks[0]+wiggle0);
    RooGaussian core0("core0", "Gaussian for resolution", tof, mu0, sigma1);

    RooRealVar nu0("nu0", "", peaks[0]+10, peaks[0], peaks[0]+1000.);
    RooRealVar g0("g0", "", 1.0, 0, 4.);
    RooBreitWigner scat0("scat0", "Breit-Wigner for scattered stuff", tof, nu0, g0);
                  
    ///////////////////////////////////
    RooNumConvPdf model("model","model", tof, core0, scat0);
    model.setConvolutionWindow(mu0, sigma0, 5);
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
