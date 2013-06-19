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
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace std;
using namespace RooFit;

void fitting(void);
void plotting(void);

string dirName = "077cu-ban4-lower-betaCut/";
string fileName = "077cu-ban4-lower-betaCut-tof";

string dataName="../data/roofit/"+dirName+fileName+".dat";
//string epsName = "../pics/roofit/"+dirName+fileName+".eps";
//string resultsFile = "results/"+dirName+fileName+".fit";

string epsName = "../pics/roofit/working/working.eps";
string resultsFile = "results/working.dat";

int main(int argc, char* argv[]) {
    ifstream test(dataName.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the data file to read in the sexy data!!" << endl << endl;
        exit(1);
    }

    //if(argc == 1)
        fitting();
        //else
        // plotting();
}

void fitting(void) {
    //Read in the data and set the variable to fit.
    double low = 0.;
    double high = 200.;
    RooRealVar tof("tof","tof", low, high);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    //Set the information for the peaks
    double peaks[]={20.468, 38.306, 25.209, 31.149, 46.603, 55.006, 
                    66.831, 79.785, 93.401, 108.52, 138.87};
    double wiggle = 15.;
    
    //Set the information for the sigmas.
    //RooRealVar res("res", "", 3.375 / (2*sqrt(2*log(2))));
    RooRealVar res("res", "", 6.805 / (2*sqrt(2*log(2))));

    double nStart = 1.0, nLow = 0., nHigh = 50.;
    double yStart = 3.e3, yLow = 0., yHigh = 1.e7;

    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooFormulaVar sigma00("sigma00", "res*(0.0264412*mu00+0.0432495)",RooArgList(res,mu00));
    RooFormulaVar alpha00("alpha00", "-9.53022/mu00-0.35706", mu00);
    RooRealVar n00("n00", "", nStart, nLow, nHigh);
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);

    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooFormulaVar sigma01("sigma01", "res*(0.0264412*mu01+0.0432495)",RooArgList(res,mu01));
    RooFormulaVar alpha01("alpha01", "-9.53022/mu01-0.35706", mu01);
    RooRealVar n01("n01", "", nStart, nLow, nHigh);
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);

    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", peaks[2], peaks[2]-wiggle,peaks[2]+wiggle);
    RooFormulaVar sigma02("sigma02", "res*(0.0264412*mu02+0.0432495)",RooArgList(res,mu02));
    RooFormulaVar alpha02("alpha02", "-9.53022/mu02-0.35706", mu02);
    RooRealVar n02("n02", "", nStart, nLow, nHigh);
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);

    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooFormulaVar sigma03("sigma03", "res*(0.0264412*mu03+0.0432495)",RooArgList(res,mu03));
    RooFormulaVar alpha03("alpha03", "-9.53022/mu03-0.35706", mu03);
    RooRealVar n03("n03", "", nStart, nLow, nHigh);
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);

    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooFormulaVar sigma04("sigma04", "res*(0.0264412*mu04+0.0432495)",RooArgList(res,mu04));
    RooFormulaVar alpha04("alpha04", "-9.53022/mu04-0.35706", mu04);
    RooRealVar n04("n04", "", nStart, nLow, nHigh);
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);

    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooFormulaVar sigma05("sigma05", "res*(0.0264412*mu05+0.0432495)",RooArgList(res,mu05));
    RooFormulaVar alpha05("alpha05", "-9.53022/mu05-0.35706", mu05);
    RooRealVar n05("n05", "", nStart, nLow, nHigh);
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);

    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooFormulaVar sigma06("sigma06", "res*(0.0264412*mu06+0.0432495)",RooArgList(res,mu06));
    RooFormulaVar alpha06("alpha06", "-9.53022/mu06-0.35706", mu06);
    RooRealVar n06("n06", "", nStart, nLow, nHigh);
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);

    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooFormulaVar sigma07("sigma07", "res*(0.0264412*mu07+0.0432495)",RooArgList(res,mu07));
    RooFormulaVar alpha07("alpha07", "-9.53022/mu07-0.35706", mu07);
    RooRealVar n07("n07", "", nStart, nLow, nHigh);
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);

    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooFormulaVar sigma08("sigma08", "res*(0.0264412*mu08+0.0432495)",RooArgList(res,mu08));
    RooFormulaVar alpha08("alpha08", "-9.53022/mu08-0.35706", mu08);
    RooRealVar n08("n08", "", nStart, nLow, nHigh);
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);

    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooFormulaVar sigma09("sigma09", "res*(0.0264412*mu09+0.0432495)",RooArgList(res,mu09));
    RooFormulaVar alpha09("alpha09", "-9.53022/mu09-0.35706", mu09);
    RooRealVar n09("n09", "", nStart, nLow, nHigh);
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);

    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooFormulaVar sigma10("sigma10", "res*(0.0264412*mu10+0.0432495)",RooArgList(res,mu10));
    RooFormulaVar alpha10("alpha10", "-9.53022/mu10-0.35706", mu10);
    RooRealVar n10("n10", "", nStart, nLow, nHigh);
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);

    RooArgList cbs(cb00,cb01,cb02,cb03,cb04,cb05,cb06,cb07,cb08);
    cbs.add(RooArgList(cb09, cb10));
    RooArgList yields(yield00,yield01,yield02,yield03,yield04,yield05,yield06,yield07,yield08);
    yields.add(RooArgList(yield09,yield10));
    RooAddPdf model("model", "", cbs, yields);

    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(low, high));

    ofstream resultsParam(resultsFile.c_str());
    fitResult->printMultiline(resultsParam, 0, false, "");
    resultsParam.close();
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(high*0.5);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (2 ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    
    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    model.plotOn(frame,RooFit::Components("cb00"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb01"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb02"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb03"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb04"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb05"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb06"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb07"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb08"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb09"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("cb10"),RooFit::LineColor(kOrange), 
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
