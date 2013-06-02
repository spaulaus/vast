#include <fstream>
#include <iostream>
#include <iomanip>

#include <cmath>
#include <cstdio>

#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace std;
using namespace RooFit;

void fitting(void);

string dirName = "tofSim/";
string fileName = "0300keV";

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
    double high = 140.;
    RooRealVar tof("tof","tof", low, high);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    //Set the information for the peaks
    double peaks[]={60.};
    double wiggle0 = 10.;
    //Set the information for the sigmas.
    //double res0 = 3.375 / (2*sqrt(2*log(2)));
    double res1 = 5.805 / (2*sqrt(2*log(2)));

    RooRealVar yield0("yield0", "", 3.e3, 0., 1.e7);
    RooRealVar sigma0("sigma0", "", res1, 0., 10.);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle0, peaks[0]+wiggle0);
    RooRealVar alpha0("alpha", "", -1.0, -10., 0.);
    RooRealVar n0("n0", "", 1., 0., 5.);

    RooFormulaVar sigma("sigma", "0.0264412*mu0+0.0432495", mu0);

    RooCBShape cb0("cb0", "", tof, mu0, sigma, alpha0, n0);

    RooArgList cbs(cb0);
    RooArgList yields(yield0);

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
