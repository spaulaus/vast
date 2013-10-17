#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include <cmath>
#include <cstdio>

#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
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

vector<double> mus, yields;

void ReadData(void) {
    ifstream data("results/077cu-ban4-lower/077cu-ban4-lower-tof.out");
    if(data.is_open()) {
        while(data.good()) {
            if(isdigit(data.peek())) {
                double junk, temp, temp1;
                data >> junk >> temp >> junk >> temp1 >> junk >> junk;
                mus.push_back(temp);
                yields.push_back(temp1);
            }else {
                data.ignore(1000,'\n');
            }
        }
    }
    data.close();
}

int main() {
    //Read in the data and set the variable to fit.
    double low = 0.;
    double high = 2000.;
    RooRealVar tof("tof","",0.0,low,high,"ns");
    tof.setBins(1e5,"cache");

    ReadData();

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
    RooConstVar yield00("yield00", "", yields[0]);
    RooConstVar mu00("mu00","", mus[0]);
    RooFormulaVar sigma00("sigma00", "sM*mu00+sB", RooArgList(sM,mu00,sB));
    RooFormulaVar alpha00("alpha00", "aM/mu00+aB", RooArgList(aM,mu00,aB));
    RooFormulaVar n00("n00", "nM/mu00+nB", RooArgList(nM,mu00,nB));
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);
    
    RooGaussModel res00("res00", "", tof, x, res);
    RooFFTConvPdf pk00("pk00","",tof,cb00,res00);

    //---------- Peak Number 1 ----------
    RooConstVar yield01("yield01", "", yields[1]);
    RooConstVar mu01("mu01","", mus[1]);
    RooFormulaVar sigma01("sigma01", "sM*mu01+sB", RooArgList(sM,mu01,sB));
    RooFormulaVar alpha01("alpha01", "aM/mu01+aB", RooArgList(aM,mu01,aB));
    RooFormulaVar n01("n01", "nM/mu01+nB", RooArgList(nM,mu01,nB));
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);
    
    RooGaussModel res01("res01", "", tof, x, res);
    RooFFTConvPdf pk01("pk01","",tof,cb01,res01);
    
    //---------- Peak Number 2 ----------
    RooConstVar yield02("yield02", "", yields[2]);
    RooConstVar mu02("mu02","", mus[2]);
    RooFormulaVar sigma02("sigma02", "sM*mu02+sB", RooArgList(sM,mu02,sB));
    RooFormulaVar alpha02("alpha02", "aM/mu02+aB", RooArgList(aM,mu02,aB));
    RooFormulaVar n02("n02", "nM/mu02+nB", RooArgList(nM,mu02,nB));
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);
    
    RooGaussModel res02("res02", "", tof, x, res);
    RooFFTConvPdf pk02("pk02","",tof,cb02,res02);
    
    //---------- Peak Number 3 ----------
    RooConstVar yield03("yield03", "", yields[3]);
    RooConstVar mu03("mu03","", mus[3]);
    RooFormulaVar sigma03("sigma03", "sM*mu03+sB", RooArgList(sM,mu03,sB));
    RooFormulaVar alpha03("alpha03", "aM/mu03+aB", RooArgList(aM,mu03,aB));
    RooFormulaVar n03("n03", "nM/mu03+nB", RooArgList(nM,mu03,nB));
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);
    
    RooGaussModel res03("res03", "", tof, x, res);
    RooFFTConvPdf pk03("pk03","",tof,cb03,res03);
    
    //---------- Peak Number 4 ----------
    RooConstVar yield04("yield04", "", yields[4]);
    RooConstVar mu04("mu04","", mus[4]);
    RooFormulaVar sigma04("sigma04", "sM*mu04+sB", RooArgList(sM,mu04,sB));
    RooFormulaVar alpha04("alpha04", "aM/mu04+aB", RooArgList(aM,mu04,aB));
    RooFormulaVar n04("n04", "nM/mu04+nB", RooArgList(nM,mu04,nB));
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);
    
    RooGaussModel res04("res04", "", tof, x, res);
    RooFFTConvPdf pk04("pk04","",tof,cb04,res04);
    
    //---------- Peak Number 5 ----------
    RooConstVar yield05("yield05", "", yields[5]);
    RooConstVar mu05("mu05","", mus[5]);
    RooFormulaVar sigma05("sigma05", "sM*mu05+sB", RooArgList(sM,mu05,sB));
    RooFormulaVar alpha05("alpha05", "aM/mu05+aB", RooArgList(aM,mu05,aB));
    RooFormulaVar n05("n05", "nM/mu05+nB", RooArgList(nM,mu05,nB));
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);
    
    RooGaussModel res05("res05", "", tof, x, res);
    RooFFTConvPdf pk05("pk05","",tof,cb05,res05);
    
    //---------- Peak Number 6 ----------
    RooConstVar yield06("yield06", "", yields[6]);
    RooConstVar mu06("mu06","", mus[6]);
    RooFormulaVar sigma06("sigma06", "sM*mu06+sB", RooArgList(sM,mu06,sB));
    RooFormulaVar alpha06("alpha06", "aM/mu06+aB", RooArgList(aM,mu06,aB));
    RooFormulaVar n06("n06", "nM/mu06+nB", RooArgList(nM,mu06,nB));
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);
    
    RooGaussModel res06("res06", "", tof, x, res);
    RooFFTConvPdf pk06("pk06","",tof,cb06,res06);
    
    //---------- Peak Number 7 ----------
    RooConstVar yield07("yield07", "", yields[7]);
    RooConstVar mu07("mu07","", mus[7]);
    RooFormulaVar sigma07("sigma07", "sM*mu07+sB", RooArgList(sM,mu07,sB));
    RooFormulaVar alpha07("alpha07", "aM/mu07+aB", RooArgList(aM,mu07,aB));
    RooFormulaVar n07("n07", "nM/mu07+nB", RooArgList(nM,mu07,nB));
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);
    
    RooGaussModel res07("res07", "", tof, x, res);
    RooFFTConvPdf pk07("pk07","",tof,cb07,res07);
    
    //---------- Peak Number 8 ----------
    RooConstVar yield08("yield08", "", yields[8]);
    RooConstVar mu08("mu08","", mus[8]);
    RooFormulaVar sigma08("sigma08", "sM*mu08+sB", RooArgList(sM,mu08,sB));
    RooFormulaVar alpha08("alpha08", "aM/mu08+aB", RooArgList(aM,mu08,aB));
    RooFormulaVar n08("n08", "nM/mu08+nB", RooArgList(nM,mu08,nB));
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);
    
    RooGaussModel res08("res08", "", tof, x, res);
    RooFFTConvPdf pk08("pk08","",tof,cb08,res08);
    
    //---------- Peak Number 9 ----------
    RooConstVar yield09("yield09", "", yields[9]);
    RooConstVar mu09("mu09","", mus[9]);
    RooFormulaVar sigma09("sigma09", "sM*mu09+sB", RooArgList(sM,mu09,sB));
    RooFormulaVar alpha09("alpha09", "aM/mu09+aB", RooArgList(aM,mu09,aB));
    RooFormulaVar n09("n09", "nM/mu09+nB", RooArgList(nM,mu09,nB));
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);
    
    RooGaussModel res09("res09", "", tof, x, res);
    RooFFTConvPdf pk09("pk09","",tof,cb09,res09);
    
    //---------- Peak Number 10 ----------
    RooConstVar yield10("yield10", "", yields[10]);
    RooConstVar mu10("mu10","", mus[10]);
    RooFormulaVar sigma10("sigma10", "sM*mu10+sB", RooArgList(sM,mu10,sB));
    RooFormulaVar alpha10("alpha10", "aM/mu10+aB", RooArgList(aM,mu10,aB));
    RooFormulaVar n10("n10", "nM/mu10+nB", RooArgList(nM,mu10,nB));
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);
    
    RooGaussModel res10("res10", "", tof, x, res);
    RooFFTConvPdf pk10("pk10","",tof,cb10,res10);
    
    //---------- Peak Number 11 ----------
    RooConstVar yield11("yield11", "", yields[11]);
    RooConstVar mu11("mu11","", mus[11]);
    RooFormulaVar sigma11("sigma11", "sM*mu11+sB", RooArgList(sM,mu11,sB));
    RooFormulaVar alpha11("alpha11", "aM/mu11+aB", RooArgList(aM,mu11,aB));
    RooFormulaVar n11("n11", "nM/mu11+nB", RooArgList(nM,mu11,nB));
    RooCBShape cb11("cb11", "", tof, mu11, sigma11, alpha11, n11);
    
    RooGaussModel res11("res11", "", tof, x, res);
    RooFFTConvPdf pk11("pk11","",tof,cb11,res11);
    
    //---------- Peak Number 12 ----------
    RooConstVar yield12("yield12", "", yields[12]);
    RooConstVar mu12("mu12","", mus[12]);
    RooFormulaVar sigma12("sigma12", "sM*mu12+sB", RooArgList(sM,mu12,sB));
    RooFormulaVar alpha12("alpha12", "aM/mu12+aB", RooArgList(aM,mu12,aB));
    RooFormulaVar n12("n12", "nM/mu12+nB", RooArgList(nM,mu12,nB));
    RooCBShape cb12("cb12", "", tof, mu12, sigma12, alpha12, n12);
    
    RooGaussModel res12("res12", "", tof, x, res);
    RooFFTConvPdf pk12("pk12","",tof,cb12,res12);

    //---------- Peak Number 13 ----------
    RooConstVar yield13("yield13", "", yields[13]);
    RooConstVar mu13("mu13","", mus[13]);
    RooFormulaVar sigma13("sigma13", "sM*mu13+sB", RooArgList(sM,mu13,sB));
    RooFormulaVar alpha13("alpha13", "aM/mu13+aB", RooArgList(aM,mu13,aB));
    RooFormulaVar n13("n13", "nM/mu13+nB", RooArgList(nM,mu13,nB));
    RooCBShape cb13("cb13", "", tof, mu13, sigma13, alpha13, n13);
    
    RooGaussModel res13("res13", "", tof, x, res);
    RooFFTConvPdf pk13("pk13","",tof,cb13,res13);
    

    RooDataSet* mcData=pk01.generate(tof,1.e5);
    int prk = 1;

    RooRealVar yieldZ("yieldZ", "", yields[prk], 0., 1.e8);
    RooRealVar muZ("muZ","",mus[prk], 0., 200.);
    RooRealVar sigmaZ("sigmaZ", "", 2.0, 0., 10.);
    RooFormulaVar alphaZ("alphaZ", "aM/muZ+aB", RooArgList(aM,muZ,aB));
    RooFormulaVar nZ("nZ", "nM/muZ+nB", RooArgList(nM,muZ,nB));
    RooCBShape cbZ("cbZ", "", tof, muZ, sigmaZ, alphaZ, nZ);
    
    RooAddPdf model("model", "", cbZ, yieldZ); 
    RooDataSet *data = RooDataSet::read("../data/roofit/077cu-ban4-lower/077cu-ban4-lower-tof.dat", RooArgList(tof));
    RooFitResult* fitResult = model.fitTo(*mcData, NumCPU(3), 
                                          Range(0., 200.));

    //Do the plots
    RooPlot* frame = tof.frame();
    tof.plotOn(frame);
    mcData->plotOn(frame);
    model.plotOn(frame);
    pk01.plotOn(frame, LineStyle(kDashed), LineColor(kGreen));

    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    frame->Draw();
    c->SaveAs("../pics/roofit/working-params.eps");

   if(fitResult->statusCodeHistory(0) != 0)
        cout << endl << endl << "Oh, Jesus, the fit did not converge." << endl;
    else
        cout << endl << endl << "The fit converged successfully." << endl;

    if(fitResult->statusCodeHistory(1) != 0)
        cout << "Hesse FAILED to calculate things properly." << endl << endl;
    else
        cout << "HESSE successfully calculated things." << endl << endl;

    cout << "Mu = " << mus[prk] << endl;
}
