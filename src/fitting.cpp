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
string fileName = "all";

string dataName="../data/roofit/"+dirName+fileName+".dat";
//string epsName = "../pics/roofit/"+dirName+fileName+".eps";
//string resultsFile = "results/"+dirName+fileName+".fit";

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
    double peaks[]={15.,35.,60.};
    double wiggle0 = 10.;
    //Set the information for the sigmas.
    //double res0 = 3.375 / (2*sqrt(2*log(2)));
    double res1 = 5.805 / (2*sqrt(2*log(2)));

    RooRealVar yield0("yield0", "", 3.e3, 0., 1.e7);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle0, peaks[0]+wiggle0);
    RooFormulaVar sigma0("sigma0", "0.0264412*mu0+0.0432495", mu0);
    RooFormulaVar alpha0("alpha0", "-9.53022/mu0-0.35706", mu0);
    RooRealVar n0("n0", "", 1., 0., 5.);
    RooCBShape cb0("cb0", "", tof, mu0, sigma0, alpha0, n0);

    RooRealVar yield1("yield1", "", 3.e3, 0., 1.e7);
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle0, peaks[1]+wiggle0);
    RooFormulaVar sigma1("sigma1", "0.0264412*mu1+0.0432495", mu1);
    RooFormulaVar alpha1("alpha1", "-9.53022/mu1-0.35706", mu1);
    RooRealVar n1("n1", "", 1., 0., 5.);
    RooCBShape cb1("cb1", "", tof, mu1, sigma1, alpha1, n1);

    RooRealVar yield2("yield2", "", 3.e3, 0., 1.e7);
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle0, peaks[2]+wiggle0);
    RooFormulaVar sigma2("sigma2", "0.0264412*mu2+0.0432495", mu2);
    RooFormulaVar alpha2("alpha2", "-9.53022/mu2-0.35706", mu2);
    RooRealVar n2("n2", "", 1., 0., 5.);
    RooCBShape cb2("cb2", "", tof, mu2, sigma2, alpha2, n2);


    RooArgList cbs(cb0,cb1,cb2);
    RooArgList yields(yield0,yield1,yield2);

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
