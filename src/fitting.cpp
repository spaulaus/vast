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

string dirName = "077cu-ban4-lower/";
string fileName = "077cu-ban4-lower-tof";

string dataName="../data/roofit/"+dirName+fileName+".dat";
//string epsName = "../pics/roofit/"+dirName+fileName+".eps";
//string resultsFile = "results/"+dirName+fileName+".fit";

string epsName = "../pics/roofit/muFree.eps";
string resultsFile = "results/muFree.dat";

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
    double high = 200.;
    RooRealVar tof("tof","tof", low, high);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    //Set the information for the peaks
    double peaks[]={24.1, 30.574, 37.6, 45.68, 52.32, 
                    66.25, 76.6, 92.48, 106.404, 138.04};
    double wiggle = 10.;
    
    //Set the information for the sigmas.
    //RooRealVar res("res", "", 3.375 / (2*sqrt(2*log(2))));
    RooRealVar res("res", "", 5.805 / (2*sqrt(2*log(2))));

    double nStart = 1.0, nLow = 0., nHigh = 50.;
    double yStart = 3.e3, yLow = 0., yHigh = 1.e7;

    RooRealVar yield0("yield0", "", yStart, yLow, yHigh);
    RooRealVar mu0("mu0","", peaks[0]);
    RooFormulaVar sigma0("sigma0", "res*(0.0264412*mu0+0.0432495)",RooArgList(res,mu0));
    RooFormulaVar alpha0("alpha0", "-9.53022/mu0-0.35706", mu0);
    RooRealVar n0("n0", "", nStart, nLow, nHigh);
    RooCBShape cb0("cb0", "", tof, mu0, sigma0, alpha0, n0);

    RooRealVar yield1("yield1", "", yStart, yLow, yHigh);
    RooRealVar mu1("mu1","", peaks[1]);
    RooFormulaVar sigma1("sigma1", "res*(0.0264412*mu1+0.0432495)",RooArgList(res,mu1));
    RooFormulaVar alpha1("alpha1", "-9.53022/mu1-0.35706", mu1);
    RooRealVar n1("n1", "", nStart, nLow, nHigh);
    RooCBShape cb1("cb1", "", tof, mu1, sigma1, alpha1, n1);

    RooRealVar yield2("yield2", "", yStart, yLow, yHigh);
    RooRealVar mu2("mu2","", peaks[2]);
    RooFormulaVar sigma2("sigma2", "res*(0.0264412*mu2+0.0432495)",RooArgList(res,mu2));
    RooFormulaVar alpha2("alpha2", "-9.53022/mu2-0.35706", mu2);
    RooRealVar n2("n2", "", nStart, nLow, nHigh);
    RooCBShape cb2("cb2", "", tof, mu2, sigma2, alpha2, n2);

    RooRealVar yield3("yield3", "", yStart, yLow, yHigh);
    RooRealVar mu3("mu3","", peaks[3]);
    RooFormulaVar sigma3("sigma3", "res*(0.0264412*mu3+0.0432495)",RooArgList(res,mu3));
    RooFormulaVar alpha3("alpha3", "-9.53022/mu3-0.35706", mu3);
    RooRealVar n3("n3", "", nStart, nLow, nHigh);
    RooCBShape cb3("cb3", "", tof, mu3, sigma3, alpha3, n3);

    RooRealVar yield4("yield4", "", yStart, yLow, yHigh);
    RooRealVar mu4("mu4","", peaks[4]);
    RooFormulaVar sigma4("sigma4", "res*(0.0264412*mu4+0.0432495)",RooArgList(res,mu4));
    RooFormulaVar alpha4("alpha4", "-9.53022/mu4-0.35706", mu4);
    RooRealVar n4("n4", "", nStart, nLow, nHigh);
    RooCBShape cb4("cb4", "", tof, mu4, sigma4, alpha4, n4);

    RooRealVar yield5("yield5", "", yStart, yLow, yHigh);
    RooRealVar mu5("mu5","", peaks[5]);
    RooFormulaVar sigma5("sigma5", "res*(0.0264412*mu5+0.0432495)",RooArgList(res,mu5));
    RooFormulaVar alpha5("alpha5", "-9.53022/mu5-0.35706", mu5);
    RooRealVar n5("n5", "", nStart, nLow, nHigh);
    RooCBShape cb5("cb5", "", tof, mu5, sigma5, alpha5, n5);

    RooRealVar yield6("yield6", "", yStart, yLow, yHigh);
    RooRealVar mu6("mu6","", peaks[6]);
    RooFormulaVar sigma6("sigma6", "res*(0.0264412*mu6+0.0432495)",RooArgList(res,mu6));
    RooFormulaVar alpha6("alpha6", "-9.53022/mu6-0.35706", mu6);
    RooRealVar n6("n6", "", nStart, nLow, nHigh);
    RooCBShape cb6("cb6", "", tof, mu6, sigma6, alpha6, n6);

    RooRealVar yield7("yield7", "", yStart, yLow, yHigh);
    RooRealVar mu7("mu7","", peaks[7]);
    RooFormulaVar sigma7("sigma7", "res*(0.0264412*mu7+0.0432495)",RooArgList(res,mu7));
    RooFormulaVar alpha7("alpha7", "-9.53022/mu7-0.35706", mu7);
    RooRealVar n7("n7", "", nStart, nLow, nHigh);
    RooCBShape cb7("cb7", "", tof, mu7, sigma7, alpha7, n7);

    RooRealVar yield8("yield8", "", yStart, yLow, yHigh);
    RooRealVar mu8("mu8","", peaks[8]);
    RooFormulaVar sigma8("sigma8", "res*(0.0264412*mu8+0.0432495)",RooArgList(res,mu8));
    RooFormulaVar alpha8("alpha8", "-9.53022/mu8-0.35706", mu8);
    RooRealVar n8("n8", "", nStart, nLow, nHigh);
    RooCBShape cb8("cb8", "", tof, mu8, sigma8, alpha8, n8);

    RooRealVar yield9("yield9", "", yStart, yLow, yHigh);
    RooRealVar mu9("mu9","", peaks[9]);
    RooFormulaVar sigma9("sigma9", "res*(0.0264412*mu9+0.0432495)",RooArgList(res,mu9));
    RooFormulaVar alpha9("alpha9", "-9.53022/mu9-0.35706", mu9);
    RooRealVar n9("n9", "", nStart, nLow, nHigh);
    RooCBShape cb9("cb9", "", tof, mu9, sigma9, alpha9, n9);

    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10]);
    RooFormulaVar sigma10("sigma10", "res*(0.0264412*mu10+0.0432495)",RooArgList(res,mu10));
    RooFormulaVar alpha10("alpha10", "-9.53022/mu10-0.35706", mu10);
    RooRealVar n10("n10", "", nStart, nLow, nHigh);
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);

    RooArgList cbs(cb0,cb1,cb2,cb3,cb4,cb5,cb6,cb7,cb8);
    cbs.add(RooArgList(cb9));
    RooArgList yields(yield0,yield1,yield2,yield3,yield4,yield5,yield6,yield7,yield8);
    yields.add(RooArgList(yield9));
    RooAddPdf model("model", "", cbs, yields);

    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(low, high));

    ofstream resultsParam(resultsFile.c_str());
    fitResult->printMultiline(resultsParam, 0, false, "");
    resultsParam.close();
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(high*0.25);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (2 ns)");
    frame->SetYTitle("Events/ 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    
    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    model.plotOn(frame,RooFit::Components("cb0"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb1"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb2"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb3"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb4"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb5"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb6"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb7"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb8"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb9"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    
    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    frame->Draw();
    c->SaveAs(epsName.c_str());
    
    if(fitResult->statusCodeHistory(0) != 0)
        cout << endl << endl << "Oh, Jesus, the fit did not converge." << endl;
    else
        cout << endl << endl << "The fit converged successfully." << endl;

    if(fitResult->statusCodeHistory(1) != 0)
        cout << "Hesse FAILED to calculate things properly." << endl << endl;
    else
        cout << "HESSE successfully calculated things." << endl << endl;
}
