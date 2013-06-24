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
    double high = 200.;
    RooRealVar tof("tof","tof", low, high);
    //tof.setBins(10000);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    //Set the information for the peaks
    double peaks[]={23.895, 30.181, 37.956, 44.078, 48.314,
                    53.973, 59.620, 67.166, 76.657, 84.296, 
                    93.422, 103.20, 110.74, 134.61};
    double wiggle = 100.;
    
    RooRealVar nScale("nScale", "", 1.0);
    double yStart = 3.e3, yLow = 0., yHigh = 1.e7;

    //Set the information for the resolution model
    RooRealVar res("res", "", 4.00 / (2*sqrt(2*log(2))));
    RooRealVar x("x", "", 0.0);
    
    //---------- Peak Number 0 ----------
    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooFormulaVar sigma00("sigma00", "(0.0264412131874119*mu00+0.0432494943386515)",mu00);
    RooFormulaVar alpha00("alpha00", "-9.53022215447638/mu00-0.357060159281673", mu00);
    RooFormulaVar n00("n00", "(-5.99204241877324/mu00+1.25859614260662)*nScale", RooArgList(mu00,nScale));
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);

    RooGaussModel res00("res00", "", tof, x, res);
    RooFFTConvPdf pk00("pk00","",tof,cb00,res00);

    //---------- Peak Number 1 ----------
    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooFormulaVar sigma01("sigma01", "0.0264412131874119*mu01+0.0432494943386515",mu01);
    RooFormulaVar alpha01("alpha01", "-9.53022215447638/mu01-0.357060159281673", mu01);
    RooFormulaVar n01("n01", "(-5.99204241877324/mu01+1.25859614260662)*nScale", RooArgList(mu01,nScale));
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);

    RooGaussModel res01("res01", "", tof, x, res);
    RooFFTConvPdf pk01("pk01","",tof,cb01,res01);

    //---------- Peak Number 2 ----------
    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", peaks[2], peaks[2]-wiggle,peaks[2]+wiggle);
    RooFormulaVar sigma02("sigma02", "0.0264412131874119*mu02+0.0432494943386515",mu02);
    RooFormulaVar alpha02("alpha02", "-9.53022215447638/mu02-0.357060159281673", mu02);
    RooFormulaVar n02("n02", "(-5.99204241877324/mu02+1.25859614260662)*nScale", RooArgList(mu02,nScale));
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);
    
    RooGaussModel res02("res02", "", tof, x, res);
    RooFFTConvPdf pk02("pk02","",tof,cb02,res02);

    //---------- Peak Number 3 ----------
    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooFormulaVar sigma03("sigma03", "(0.0264412131874119*mu03+0.0432494943386515)",mu03);
    RooFormulaVar alpha03("alpha03", "-9.53022215447638/mu03-0.357060159281673", mu03);
    RooFormulaVar n03("n03", "(-5.99204241877324/mu03+1.25859614260662)*nScale", RooArgList(mu03,nScale));
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);

    RooGaussModel res03("res03", "", tof, x, res);
    RooFFTConvPdf pk03("pk03","",tof,cb03,res03);

    //---------- Peak Number 4 ----------
    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooFormulaVar sigma04("sigma04", "(0.0264412131874119*mu04+0.0432494943386515)",mu04);
    RooFormulaVar alpha04("alpha04", "-9.53022215447638/mu04-0.357060159281673", mu04);
    RooFormulaVar n04("n04", "(-5.99204241877324/mu04+1.25859614260662)*nScale", RooArgList(mu04,nScale));
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);

    RooGaussModel res04("res04", "", tof, x, res);
    RooFFTConvPdf pk04("pk04","",tof,cb04,res04);

    //---------- Peak Number 5 ----------
    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooFormulaVar sigma05("sigma05", "(0.0264412131874119*mu05+0.0432494943386515)",mu05);
    RooFormulaVar alpha05("alpha05", "-9.53022215447638/mu05-0.357060159281673", mu05);
    RooFormulaVar n05("n05", "(-5.99204241877324/mu05+1.25859614260662)*nScale", RooArgList(mu05,nScale));
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);
    
    RooGaussModel res05("res05", "", tof, x, res);
    RooFFTConvPdf pk05("pk05","",tof,cb05,res05);

    //---------- Peak Number 6 ----------
    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooFormulaVar sigma06("sigma06", "(0.0264412131874119*mu06+0.0432494943386515)",mu06);
    RooFormulaVar alpha06("alpha06", "-9.53022215447638/mu06-0.357060159281673", mu06);
    RooFormulaVar n06("n06", "(-5.99204241877324/mu06+1.25859614260662)*nScale", RooArgList(mu06,nScale));
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);

    RooGaussModel res06("res06", "", tof, x, res);
    RooFFTConvPdf pk06("pk06","",tof,cb06,res06);

    //---------- Peak Number 7 ----------
    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooFormulaVar sigma07("sigma07", "(0.0264412131874119*mu07+0.0432494943386515)",mu07);
    RooFormulaVar alpha07("alpha07", "-9.53022215447638/mu07-0.357060159281673", mu07);
    RooFormulaVar n07("n07", "(-5.99204241877324/mu07+1.25859614260662)*nScale", RooArgList(mu07,nScale));
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);

    RooGaussModel res07("res07", "", tof, x, res);
    RooFFTConvPdf pk07("pk07","",tof,cb07,res07);

    //---------- Peak Number 8 ----------
    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooFormulaVar sigma08("sigma08", "(0.0264412131874119*mu08+0.0432494943386515)",mu08);
    RooFormulaVar alpha08("alpha08", "-9.53022215447638/mu08-0.357060159281673", mu08);
    RooFormulaVar n08("n08", "(-5.99204241877324/mu08+1.25859614260662)*nScale", RooArgList(mu08,nScale));
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);
    
    RooGaussModel res08("res08", "", tof, x, res);
    RooFFTConvPdf pk08("pk08","",tof,cb08,res08);

    //---------- Peak Number 9 ----------
    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooFormulaVar sigma09("sigma09", "(0.0264412131874119*mu09+0.0432494943386515)",mu09);
    RooFormulaVar alpha09("alpha09", "-9.53022215447638/mu09-0.357060159281673", mu09);
    RooFormulaVar n09("n09", "(-5.99204241877324/mu09+1.25859614260662)*nScale", RooArgList(mu09,nScale));
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);

    RooGaussModel res09("res09", "", tof, x, res);
    RooFFTConvPdf pk09("pk09","",tof,cb09,res09);
    
    //---------- Peak Number 10 ----------
    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooFormulaVar sigma10("sigma10", "(0.0264412131874119*mu10+0.0432494943386515)",mu10);
    RooFormulaVar alpha10("alpha10", "-9.53022215447638/mu10-0.357060159281673", mu10);
    RooFormulaVar n10("n10", "(-5.99204241877324/mu10+1.25859614260662)*nScale", RooArgList(mu10,nScale));
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);
    
    RooGaussModel res10("res10", "", tof, x, res);
    RooFFTConvPdf pk10("pk10","",tof,cb10,res10);

    //---------- Peak Number 11 ----------
    RooRealVar yield11("yield11", "", yStart, yLow, yHigh);
    RooRealVar mu11("mu11","", peaks[11], peaks[11]-wiggle, peaks[11]+wiggle);
    RooFormulaVar sigma11("sigma11", "(0.0264412131874119*mu11+0.0432494943386515)",mu11);
    RooFormulaVar alpha11("alpha11", "-9.53022215447638/mu11-0.357060159281673", mu11);
    RooFormulaVar n11("n11", "(-5.99204241877324/mu11+1.25859614260662)*nScale", RooArgList(mu11,nScale));
    RooCBShape cb11("cb11", "", tof, mu11, sigma11, alpha11, n11);
    
    RooGaussModel res11("res11", "", tof, x, res);
    RooFFTConvPdf pk11("pk11","",tof,cb11,res11);

    //---------- Peak Number 12 ----------
    RooRealVar yield12("yield12", "", yStart, yLow, yHigh);
    RooRealVar mu12("mu12","", peaks[12], peaks[12]-wiggle, peaks[12]+wiggle);
    RooFormulaVar sigma12("sigma12", "(0.0264412131874119*mu12+0.0432494943386515)",mu12);
    RooFormulaVar alpha12("alpha12", "-9.53022215447638/mu12-0.357060159281673", mu12);
    RooFormulaVar n12("n12", "(-5.99204241877324/mu12+1.25859614260662)*nScale", RooArgList(mu12,nScale));
    RooCBShape cb12("cb12", "", tof, mu12, sigma12, alpha12, n12);
    
    RooGaussModel res12("res12", "", tof, x, res);
    RooFFTConvPdf pk12("pk12","",tof,cb12,res12);

    //---------- Peak Number 13 ----------
    RooRealVar yield13("yield13", "", yStart, yLow, yHigh);
    RooRealVar mu13("mu13","", peaks[13], peaks[13]-wiggle, peaks[13]+wiggle);
    RooFormulaVar sigma13("sigma13", "(0.0264412131874119*mu13+0.0432494943386515)",mu13);
    RooFormulaVar alpha13("alpha13", "-9.53022215447638/mu13-0.357060159281673", mu13);
    RooFormulaVar n13("n13", "(-5.99204241877324/mu13+1.25859614260662)*nScale", RooArgList(mu13,nScale));
    RooCBShape cb13("cb13", "", tof, mu13, sigma13, alpha13, n13);
    
    RooGaussModel res13("res13", "", tof, x, res);
    RooFFTConvPdf pk13("pk13","",tof,cb13,res13);

    RooArgList pks(pk00,pk01,pk02,pk03,pk04,pk05,pk06,pk07,pk08);
    pks.add(RooArgList(pk09,pk10,pk11,pk12,pk13));
    RooArgList yields(yield00,yield01,yield02,yield03,yield04,yield05,yield06,yield07,yield08);
    yields.add(RooArgList(yield09,yield10,yield11,yield12,yield13));
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
    model.plotOn(frame,RooFit::Components("pk11"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk12"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("pk13"),RooFit::LineColor(kGreen), 
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
