#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>
#include <cstdio>

#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGaussModel.h"
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
    RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                        RooArgList(tof));

    double binning = 0.5;

    //Set the information for the peaks
    double peaks[]={23.855, 30.196, 38.128, 44.917, 
                    50.181, 56.835, 65.151, 70.826,
                    79.253, 87.198, 94.690, 104.69, 
                    112.73, 135.93};
    double wiggle = 100.;
    
    double yStart = 3.e3, yLow = 0., yHigh = 1.e8;
    
    //Set the information for the resolution model
    double detRes = 4.04;
    RooRealVar res("res", "res for gauss model", detRes / (2*sqrt(2*log(2))));
    RooRealVar x("x", "mean for gauss model", 0.0);

    //Parameterization Parameters for Sigma -> sM*mu + sB
    RooRealVar sM("sM","Slope for sigma para.", 0.0288026438611703);
    RooRealVar sB("sB","Intercept for sigma para.", -0.0413372812483731);

    //Parameterization Parameters for Alpha -> aM/mu + aB
    RooRealVar aM("aM","Scale for alpha para.",-5.66309545261006);
    RooRealVar aB("aB","Intercept for alpha para.", -0.408753253930762);

    //Parameterization Parameters for N -> nM/mu + nB
    RooRealVar nM("nM","Scale for n para.", -4.53373119793572);
    RooRealVar nB("nB","Intercept for n para.", 1.3468761986679);
    
    //---------- Peak Number 0 ----------
    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooFormulaVar sigma00("sigma00", "sM*mu00+sB", RooArgList(sM,mu00,sB));
    RooFormulaVar alpha00("alpha00", "aM/mu00+aB", RooArgList(aM,mu00,aB));
    RooFormulaVar n00("n00", "nM/mu00+nB", RooArgList(nM,mu00,nB));
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);
    
    RooGaussModel res00("res00", "", tof, x, res);
    RooFFTConvPdf pk00("pk00","",tof,cb00,res00);
    
    //---------- Peak Number 1 ----------
    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooFormulaVar sigma01("sigma01", "sM*mu01+sB", RooArgList(sM,mu01,sB));
    RooFormulaVar alpha01("alpha01", "aM/mu01+aB", RooArgList(aM,mu01,aB));
    RooFormulaVar n01("n01", "nM/mu01+nB", RooArgList(nM,mu01,nB));
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);
    
    RooGaussModel res01("res01", "", tof, x, res);
    RooFFTConvPdf pk01("pk01","",tof,cb01,res01);
    
    //---------- Peak Number 2 ----------
    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", peaks[2], peaks[2]-wiggle,peaks[2]+wiggle);
    RooFormulaVar sigma02("sigma02", "sM*mu02+sB", RooArgList(sM,mu02,sB));
    RooFormulaVar alpha02("alpha02", "aM/mu02+aB", RooArgList(aM,mu02,aB));
    RooFormulaVar n02("n02", "nM/mu02+nB", RooArgList(nM,mu02,nB));
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);
    
    RooGaussModel res02("res02", "", tof, x, res);
    RooFFTConvPdf pk02("pk02","",tof,cb02,res02);
    
    //---------- Peak Number 3 ----------
    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooFormulaVar sigma03("sigma03", "sM*mu03+sB", RooArgList(sM,mu03,sB));
    RooFormulaVar alpha03("alpha03", "aM/mu03+aB", RooArgList(aM,mu03,aB));
    RooFormulaVar n03("n03", "nM/mu03+nB", RooArgList(nM,mu03,nB));
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);
    
    RooGaussModel res03("res03", "", tof, x, res);
    RooFFTConvPdf pk03("pk03","",tof,cb03,res03);
    
    //---------- Peak Number 4 ----------
    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooFormulaVar sigma04("sigma04", "sM*mu04+sB", RooArgList(sM,mu04,sB));
    RooFormulaVar alpha04("alpha04", "aM/mu04+aB", RooArgList(aM,mu04,aB));
    RooFormulaVar n04("n04", "nM/mu04+nB", RooArgList(nM,mu04,nB));
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);
    
    RooGaussModel res04("res04", "", tof, x, res);
    RooFFTConvPdf pk04("pk04","",tof,cb04,res04);
    
    //---------- Peak Number 5 ----------
    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooFormulaVar sigma05("sigma05", "sM*mu05+sB", RooArgList(sM,mu05,sB));
    RooFormulaVar alpha05("alpha05", "aM/mu05+aB", RooArgList(aM,mu05,aB));
    RooFormulaVar n05("n05", "nM/mu05+nB", RooArgList(nM,mu05,nB));
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);
    
    RooGaussModel res05("res05", "", tof, x, res);
    RooFFTConvPdf pk05("pk05","",tof,cb05,res05);
    
    //---------- Peak Number 6 ----------
    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooFormulaVar sigma06("sigma06", "sM*mu06+sB", RooArgList(sM,mu06,sB));
    RooFormulaVar alpha06("alpha06", "aM/mu06+aB", RooArgList(aM,mu06,aB));
    RooFormulaVar n06("n06", "nM/mu06+nB", RooArgList(nM,mu06,nB));
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);
    
    RooGaussModel res06("res06", "", tof, x, res);
    RooFFTConvPdf pk06("pk06","",tof,cb06,res06);
    
    //---------- Peak Number 7 ----------
    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooFormulaVar sigma07("sigma07", "sM*mu07+sB", RooArgList(sM,mu07,sB));
    RooFormulaVar alpha07("alpha07", "aM/mu07+aB", RooArgList(aM,mu07,aB));
    RooFormulaVar n07("n07", "nM/mu07+nB", RooArgList(nM,mu07,nB));
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);
    
    RooGaussModel res07("res07", "", tof, x, res);
    RooFFTConvPdf pk07("pk07","",tof,cb07,res07);
    
    //---------- Peak Number 8 ----------
    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooFormulaVar sigma08("sigma08", "sM*mu08+sB", RooArgList(sM,mu08,sB));
    RooFormulaVar alpha08("alpha08", "aM/mu08+aB", RooArgList(aM,mu08,aB));
    RooFormulaVar n08("n08", "nM/mu08+nB", RooArgList(nM,mu08,nB));
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);
    
    RooGaussModel res08("res08", "", tof, x, res);
    RooFFTConvPdf pk08("pk08","",tof,cb08,res08);
    
    //---------- Peak Number 9 ----------
    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooFormulaVar sigma09("sigma09", "sM*mu09+sB", RooArgList(sM,mu09,sB));
    RooFormulaVar alpha09("alpha09", "aM/mu09+aB", RooArgList(aM,mu09,aB));
    RooFormulaVar n09("n09", "nM/mu09+nB", RooArgList(nM,mu09,nB));
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);
    
    RooGaussModel res09("res09", "", tof, x, res);
    RooFFTConvPdf pk09("pk09","",tof,cb09,res09);
    
    //---------- Peak Number 10 ----------
    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooFormulaVar sigma10("sigma10", "sM*mu10+sB", RooArgList(sM,mu10,sB));
    RooFormulaVar alpha10("alpha10", "aM/mu10+aB", RooArgList(aM,mu10,aB));
    RooFormulaVar n10("n10", "nM/mu10+nB", RooArgList(nM,mu10,nB));
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);
    
    RooGaussModel res10("res10", "", tof, x, res);
    RooFFTConvPdf pk10("pk10","",tof,cb10,res10);
    
    //---------- Peak Number 11 ----------
    RooRealVar yield11("yield11", "", yStart, yLow, yHigh);
    RooRealVar mu11("mu11","", peaks[11], peaks[11]-wiggle, peaks[11]+wiggle);
    RooFormulaVar sigma11("sigma11", "sM*mu11+sB", RooArgList(sM,mu11,sB));
    RooFormulaVar alpha11("alpha11", "aM/mu11+aB", RooArgList(aM,mu11,aB));
    RooFormulaVar n11("n11", "nM/mu11+nB", RooArgList(nM,mu11,nB));
    RooCBShape cb11("cb11", "", tof, mu11, sigma11, alpha11, n11);
    
    RooGaussModel res11("res11", "", tof, x, res);
    RooFFTConvPdf pk11("pk11","",tof,cb11,res11);
    
    //---------- Peak Number 12 ----------
    RooRealVar yield12("yield12", "", yStart, yLow, yHigh);
    RooRealVar mu12("mu12","", peaks[12], peaks[12]-wiggle, peaks[12]+wiggle);
    RooFormulaVar sigma12("sigma12", "sM*mu12+sB", RooArgList(sM,mu12,sB));
    RooFormulaVar alpha12("alpha12", "aM/mu12+aB", RooArgList(aM,mu12,aB));
    RooFormulaVar n12("n12", "nM/mu12+nB", RooArgList(nM,mu12,nB));
    RooCBShape cb12("cb12", "", tof, mu12, sigma12, alpha12, n12);
    
    RooGaussModel res12("res12", "", tof, x, res);
    RooFFTConvPdf pk12("pk12","",tof,cb12,res12);

    //---------- Peak Number 13 ----------
    RooRealVar yield13("yield13", "", yStart, yLow, yHigh);
    RooRealVar mu13("mu13","", peaks[13], peaks[13]-wiggle, peaks[13]+wiggle);
    RooFormulaVar sigma13("sigma13", "sM*mu13+sB", RooArgList(sM,mu13,sB));
    RooFormulaVar alpha13("alpha13", "aM/mu13+aB", RooArgList(aM,mu13,aB));
    RooFormulaVar n13("n13", "nM/mu13+nB", RooArgList(nM,mu13,nB));
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
    frame = tof.frame(high*binning);
    frame->SetTitle("");
    frame->SetAxisRange(0.,500.,"Y");
    frame->SetAxisRange(0.,200.,"X");
    frame->SetXTitle("Time-of-Flight (2 ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    
    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    model.plotOn(frame,Components("pk00"),LineColor(kGreen), LineStyle(kDashed));
    model.plotOn(frame,Components("pk01"),LineColor(kRed), LineStyle(kDashed));
    model.plotOn(frame,Components("pk02"),LineColor(kBlue), LineStyle(kDashed));
    model.plotOn(frame,Components("pk03"),LineColor(kViolet), LineStyle(kDashed));
    model.plotOn(frame,Components("pk04"),LineColor(kBlack), LineStyle(kDashed));
    model.plotOn(frame,Components("pk05"),LineColor(kPink), LineStyle(kDashed));
    model.plotOn(frame,Components("pk06"),LineColor(kGreen), LineStyle(kDashed));
    model.plotOn(frame,Components("pk07"),LineColor(kRed), LineStyle(kDashed));
    model.plotOn(frame,Components("pk08"),LineColor(kBlue), LineStyle(kDashed));
    model.plotOn(frame,Components("pk09"),LineColor(kViolet), LineStyle(kDashed));
    model.plotOn(frame,Components("pk10"),LineColor(kBlack), LineStyle(kDashed));
    model.plotOn(frame,Components("pk11"),LineColor(kPink), LineStyle(kDashed));
    model.plotOn(frame,Components("pk12"),LineColor(kGreen), LineStyle(kDashed));
    model.plotOn(frame,Components("pk13"),LineColor(kRed), LineStyle(kDashed));
    
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
