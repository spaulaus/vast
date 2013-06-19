#include <fstream>
#include <iostream>
#include <iomanip>

#include <cmath>
#include <cstdio>

#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGaussModel.h"
#include "RooMCStudy.h"
#include "RooNumConvPdf.h"
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
    double high = 200.;
    RooRealVar tof("tof","tof", low, high);
    tof.setBins(10000);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    //Set the information for the peaks
    double peaks[]={20.468, 38.306, 25.209, 31.149, 46.603, 55.006, 
                    66.831, 79.785, 93.401, 108.52, 138.87};
    double wiggle = 15.;
    
    //Set the information for the sigmas.
    RooRealVar res("res", "", 4.00 / (2*sqrt(2*log(2))));

    double nStart = 1.0, nLow = 0., nHigh = 50.;
    double yStart = 3.e3, yLow = 0., yHigh = 1.e7;
    
    //---------- Peak Number 0 ----------
    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooFormulaVar sigma00("sigma00", "res*(0.0264412*mu00+0.0432495)",RooArgList(res,mu00));
    RooFormulaVar alpha00("alpha00", "-9.53022/mu00-0.35706", mu00);
    RooRealVar n00("n00", "", nStart, nLow, nHigh);
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);

    RooFormulaVar x00("x00", "", "mu00", mu00);
    RooGaussModel res00("res00", "", tof, x00, res);
    RooFFTConvPdf pk00("pk00","",tof,cb00,res00);

    //---------- Peak Number 1 ----------
    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooFormulaVar sigma01("sigma01", "res*(0.0264412*mu01+0.0432495)",RooArgList(res,mu01));
    RooFormulaVar alpha01("alpha01", "-9.53022/mu01-0.35706", mu01);
    RooRealVar n01("n01", "", nStart, nLow, nHigh);
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);

    RooFormulaVar x01("x01", "", "mu01", mu01);
    RooGaussModel res01("res01", "", tof, x01, res);
    RooFFTConvPdf pk01("pk01","",tof,cb01,res01);

    //---------- Peak Number 2 ----------
    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", peaks[2], peaks[2]-wiggle,peaks[2]+wiggle);
    RooFormulaVar sigma02("sigma02", "res*(0.0264412*mu02+0.0432495)",RooArgList(res,mu02));
    RooFormulaVar alpha02("alpha02", "-9.53022/mu02-0.35706", mu02);
    RooRealVar n02("n02", "", nStart, nLow, nHigh);
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);
    
    RooFormulaVar x02("x02", "", "mu02", mu02);
    RooGaussModel res02("res02", "", tof, x02, res);
    RooFFTConvPdf pk02("pk02","",tof,cb02,res02);

    //---------- Peak Number 3 ----------
    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooFormulaVar sigma03("sigma03", "res*(0.0264412*mu03+0.0432495)",RooArgList(res,mu03));
    RooFormulaVar alpha03("alpha03", "-9.53022/mu03-0.35706", mu03);
    RooRealVar n03("n03", "", nStart, nLow, nHigh);
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);

    RooFormulaVar x03("x03", "", "mu03", mu03);
    RooGaussModel res03("res03", "", tof, x03, res);
    RooFFTConvPdf pk03("pk03","",tof,cb03,res03);

    //---------- Peak Number 4 ----------
    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooFormulaVar sigma04("sigma04", "res*(0.0264412*mu04+0.0432495)",RooArgList(res,mu04));
    RooFormulaVar alpha04("alpha04", "-9.53022/mu04-0.35706", mu04);
    RooRealVar n04("n04", "", nStart, nLow, nHigh);
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);

    RooFormulaVar x04("x04", "", "mu04", mu04);
    RooGaussModel res04("res04", "", tof, x04, res);
    RooFFTConvPdf pk04("pk04","",tof,cb04,res04);

    //---------- Peak Number 5 ----------
    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooFormulaVar sigma05("sigma05", "res*(0.0264412*mu05+0.0432495)",RooArgList(res,mu05));
    RooFormulaVar alpha05("alpha05", "-9.53022/mu05-0.35706", mu05);
    RooRealVar n05("n05", "", nStart, nLow, nHigh);
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);
    
    RooFormulaVar x05("x05", "", "mu05", mu05);
    RooGaussModel res05("res05", "", tof, x05, res);
    RooFFTConvPdf pk05("pk05","",tof,cb05,res05);

    //---------- Peak Number 6 ----------
    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooFormulaVar sigma06("sigma06", "res*(0.0264412*mu06+0.0432495)",RooArgList(res,mu06));
    RooFormulaVar alpha06("alpha06", "-9.53022/mu06-0.35706", mu06);
    RooRealVar n06("n06", "", nStart, nLow, nHigh);
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);

    RooFormulaVar x06("x06", "", "mu06", mu06);
    RooGaussModel res06("res06", "", tof, x06, res);
    RooFFTConvPdf pk06("pk06","",tof,cb06,res06);

    //---------- Peak Number 7 ----------
    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooFormulaVar sigma07("sigma07", "res*(0.0264412*mu07+0.0432495)",RooArgList(res,mu07));
    RooFormulaVar alpha07("alpha07", "-9.53022/mu07-0.35706", mu07);
    RooRealVar n07("n07", "", nStart, nLow, nHigh);
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);

    RooFormulaVar x07("x07", "", "mu07", mu07);
    RooGaussModel res07("res07", "", tof, x07, res);
    RooFFTConvPdf pk07("pk07","",tof,cb07,res07);

    //---------- Peak Number 8 ----------
    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooFormulaVar sigma08("sigma08", "res*(0.0264412*mu08+0.0432495)",RooArgList(res,mu08));
    RooFormulaVar alpha08("alpha08", "-9.53022/mu08-0.35706", mu08);
    RooRealVar n08("n08", "", nStart, nLow, nHigh);
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);
    
    RooFormulaVar x08("x08", "", "mu08", mu08);
    RooGaussModel res08("res08", "", tof, x08, res);
    RooFFTConvPdf pk08("pk08","",tof,cb08,res08);

    //---------- Peak Number 9 ----------
    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooFormulaVar sigma09("sigma09", "res*(0.0264412*mu09+0.0432495)",RooArgList(res,mu09));
    RooFormulaVar alpha09("alpha09", "-9.53022/mu09-0.35706", mu09);
    RooRealVar n09("n09", "", nStart, nLow, nHigh);
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);

    RooFormulaVar x09("x09", "", "mu09", mu09);
    RooGaussModel res09("res09", "", tof, x09, res);
    RooFFTConvPdf pk09("pk09","",tof,cb09,res09);
    
    //---------- Peak Number 10 ----------
    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooFormulaVar sigma10("sigma10", "res*(0.0264412*mu10+0.0432495)",RooArgList(res,mu10));
    RooFormulaVar alpha10("alpha10", "-9.53022/mu10-0.35706", mu10);
    RooRealVar n10("n10", "", nStart, nLow, nHigh);
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);
    
    RooFormulaVar x10("x10", "", "mu10", mu10);
    RooGaussModel res10("res10", "", tof, x10, res);
    RooFFTConvPdf pk10("pk10","",tof,cb10,res10);
    
    RooArgList pks(pk00,pk01,pk02,pk03,pk04,pk05,pk06,pk07,pk08);
    pks.add(RooArgList(pk09, pk10));
    RooArgList yields(yield00,yield01,yield02,yield03,yield04,yield05,yield06,yield07,yield08);
    yields.add(RooArgList(yield09,yield10));
    RooAddPdf model("model", "", pks, yields);

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

    model.plotOn(frame,RooFit::Components("pk00"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk01"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk02"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk03"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk04"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk05"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk06"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk07"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk08"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk09"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk10"),RooFit::LineColor(kOrange), 
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
