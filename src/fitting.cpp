#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

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

void fitting(void);

string dirName = "077cu-ban4-lower/";
string fileName = "077cu-ban4-lower-tof";

string dataName="../data/roofit/"+dirName+fileName+".dat";
string epsName = "../pics/roofit/"+dirName+fileName+"-noConv.eps";
string resultsFile = "results/"+dirName+fileName+"-noConv.fit";

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
    double low = 0.;
    double high = 200.;
    RooRealVar tof("tof","tof", 0.0, low, high);

    double binning = 0.5;

    //Set the information for the peaks
    double peaks[]={23.855, 30.1971, 38.128, 44.917, 
                    50.181, 56.835, 65.151, 70.826,
                    79.253, 87.198, 94.690, 104.69, 
                    112.73, 135.93};
    double wiggle = 100.;
    
    double yStart = 3.e3, yLow = 0., yHigh = 1.e8;
    
    //Parameterization Parameters for Sigma -> sM*mu + sB
    RooConstVar sA("sA","", 2.55056292412568);
    RooConstVar sB("sB","", -0.0192702755935177);
    RooConstVar sC("sC","", 0.000620834380435262);
    RooConstVar sD("sD","", -4.02706921636101e-6);
    RooConstVar sE("sE","", 1.01415462736843e-8);

    //Parameterization Parameters for Alpha -> aM/mu + aB
    RooConstVar aI("aI","", 2.97314684100351e-7);
    RooConstVar aH("aH","", -0.000105412912022653);
    RooConstVar aG("aG","", 0.0135441451470589 );
    RooConstVar aF("aF","", -1.18042124700263);

    //Parameterization Parameters for N -> nM/mu + nB
    RooConstVar nJ("nJ","", -4.38376875421603);
    RooConstVar nK("nK","", -0.000234978549811854);
    RooConstVar nL("nL","", 1.32334100981145);
    
    //---------- Peak Number 0 ----------
    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooFormulaVar sigma00("sigma00", "sE*pow(mu00,4)+sD*pow(mu00,3)+sC*pow(mu00,2)+sB*mu00+sA", RooArgList(sA,sB,sC,sD,sE,mu00));
    RooFormulaVar alpha00("alpha00", "aI*pow(mu00,3)+aH*pow(mu00,2)+aG*mu00+aF", RooArgList(aI,aH,aG,aF,mu00));
    RooFormulaVar n00("n00", "nJ/mu00+nK*mu00+nL", RooArgList(nJ,mu00,nK,nL));
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);
    
    //---------- Peak Number 1 ----------
    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooFormulaVar sigma01("sigma01", "sE*pow(mu01,4)+sD*pow(mu01,3)+sC*pow(mu01,2)+sB*mu01+sA", RooArgList(sA,sB,sC,sD,sE,mu01));
    RooFormulaVar alpha01("alpha01", "aI*pow(mu01,3)+aH*pow(mu01,2)+aG*mu01+aF", RooArgList(aI,aH,aG,aF,mu01));
    RooFormulaVar n01("n01", "nJ/mu01+nK*mu01+nL", RooArgList(nJ,mu01,nK,nL));
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);
    
    //---------- Peak Number 2 ----------
    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", peaks[2], peaks[2]-wiggle,peaks[2]+wiggle);
    RooFormulaVar sigma02("sigma02", "sE*pow(mu02,4)+sD*pow(mu02,3)+sC*pow(mu02,2)+sB*mu02+sA", RooArgList(sA,sB,sC,sD,sE,mu02));
    RooFormulaVar alpha02("alpha02", "aI*pow(mu02,3)+aH*pow(mu02,2)+aG*mu02+aF", RooArgList(aI,aH,aG,aF,mu02));
    RooFormulaVar n02("n02", "nJ/mu02+nK*mu02+nL", RooArgList(nJ,mu02,nK,nL));
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);
    
    //---------- Peak Number 3 ----------
    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooFormulaVar sigma03("sigma03", "sE*pow(mu03,4)+sD*pow(mu03,3)+sC*pow(mu03,2)+sB*mu03+sA", RooArgList(sA,sB,sC,sD,sE,mu03));
    RooFormulaVar alpha03("alpha03", "aI*pow(mu03,3)+aH*pow(mu03,2)+aG*mu03+aF", RooArgList(aI,aH,aG,aF,mu03));
    RooFormulaVar n03("n03", "nJ/mu03+nK*mu03+nL", RooArgList(nJ,mu03,nK,nL));
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);
    
    //---------- Peak Number 4 ----------
    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooFormulaVar sigma04("sigma04", "sE*pow(mu04,4)+sD*pow(mu04,3)+sC*pow(mu04,2)+sB*mu04+sA", RooArgList(sA,sB,sC,sD,sE,mu04));
    RooFormulaVar alpha04("alpha04", "aI*pow(mu04,3)+aH*pow(mu04,2)+aG*mu04+aF", RooArgList(aI,aH,aG,aF,mu04));
    RooFormulaVar n04("n04", "nJ/mu04+nK*mu04+nL", RooArgList(nJ,mu04,nK,nL));
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);
    
    //---------- Peak Number 5 ----------
    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooFormulaVar sigma05("sigma05", "sE*pow(mu05,4)+sD*pow(mu05,3)+sC*pow(mu05,2)+sB*mu05+sA", RooArgList(sA,sB,sC,sD,sE,mu05));
    RooFormulaVar alpha05("alpha05", "aI*pow(mu05,3)+aH*pow(mu05,2)+aG*mu05+aF", RooArgList(aI,aH,aG,aF,mu05));
    RooFormulaVar n05("n05", "nJ/mu05+nK*mu05+nL", RooArgList(nJ,mu05,nK,nL));
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);
    
    //---------- Peak Number 6 ----------
    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooFormulaVar sigma06("sigma06", "sE*pow(mu06,4)+sD*pow(mu06,3)+sC*pow(mu06,2)+sB*mu06+sA", RooArgList(sA,sB,sC,sD,sE,mu06));
    RooFormulaVar alpha06("alpha06", "aI*pow(mu06,3)+aH*pow(mu06,2)+aG*mu06+aF", RooArgList(aI,aH,aG,aF,mu06));
    RooFormulaVar n06("n06", "nJ/mu06+nK*mu06+nL", RooArgList(nJ,mu06,nK,nL));
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);
    
    //---------- Peak Number 7 ----------
    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooFormulaVar sigma07("sigma07", "sE*pow(mu07,4)+sD*pow(mu07,3)+sC*pow(mu07,2)+sB*mu07+sA", RooArgList(sA,sB,sC,sD,sE,mu07));
    RooFormulaVar alpha07("alpha07", "aI*pow(mu07,3)+aH*pow(mu07,2)+aG*mu07+aF", RooArgList(aI,aH,aG,aF,mu07));
    RooFormulaVar n07("n07", "nJ/mu07+nK*mu07+nL", RooArgList(nJ,mu07,nK,nL));
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);
    
    //---------- Peak Number 8 ----------
    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooFormulaVar sigma08("sigma08", "sE*pow(mu08,4)+sD*pow(mu08,3)+sC*pow(mu08,2)+sB*mu08+sA", RooArgList(sA,sB,sC,sD,sE,mu08));
    RooFormulaVar alpha08("alpha08", "aI*pow(mu08,3)+aH*pow(mu08,2)+aG*mu08+aF", RooArgList(aI,aH,aG,aF,mu08));
    RooFormulaVar n08("n08", "nJ/mu08+nK*mu08+nL", RooArgList(nJ,mu08,nK,nL));
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);
    
    //---------- Peak Number 9 ----------
    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooFormulaVar sigma09("sigma09", "sE*pow(mu09,4)+sD*pow(mu09,3)+sC*pow(mu09,2)+sB*mu09+sA", RooArgList(sA,sB,sC,sD,sE,mu09));
    RooFormulaVar alpha09("alpha09", "aI*pow(mu09,3)+aH*pow(mu09,2)+aG*mu09+aF", RooArgList(aI,aH,aG,aF,mu09));
    RooFormulaVar n09("n09", "nJ/mu09+nK*mu09+nL", RooArgList(nJ,mu09,nK,nL));
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);
    
    //---------- Peak Number 10 ----------
    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooFormulaVar sigma10("sigma10", "sE*pow(mu10,4)+sD*pow(mu10,3)+sC*pow(mu10,2)+sB*mu10+sA", RooArgList(sA,sB,sC,sD,sE,mu10));
    RooFormulaVar alpha10("alpha10", "aI*pow(mu10,3)+aH*pow(mu10,2)+aG*mu10+aF", RooArgList(aI,aH,aG,aF,mu10));
    RooFormulaVar n10("n10", "nJ/mu10+nK*mu10+nL", RooArgList(nJ,mu10,nK,nL));
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);
    
    //---------- Peak Number 11 ----------
    RooRealVar yield11("yield11", "", yStart, yLow, yHigh);
    RooRealVar mu11("mu11","", peaks[11], peaks[11]-wiggle, peaks[11]+wiggle);
    RooFormulaVar sigma11("sigma11", "sE*pow(mu11,4)+sD*pow(mu11,3)+sC*pow(mu11,2)+sB*mu11+sA", RooArgList(sA,sB,sC,sD,sE,mu11));
    RooFormulaVar alpha11("alpha11", "aI*pow(mu11,3)+aH*pow(mu11,2)+aG*mu11+aF", RooArgList(aI,aH,aG,aF,mu11));
    RooFormulaVar n11("n11", "nJ/mu11+nK*mu11+nL", RooArgList(nJ,mu11,nK,nL));
    RooCBShape cb11("cb11", "", tof, mu11, sigma11, alpha11, n11);
    
    //---------- Peak Number 12 ----------
    RooRealVar yield12("yield12", "", yStart, yLow, yHigh);
    RooRealVar mu12("mu12","", peaks[12], peaks[12]-wiggle, peaks[12]+wiggle);
    RooFormulaVar sigma12("sigma12", "sE*pow(mu12,4)+sD*pow(mu12,3)+sC*pow(mu12,2)+sB*mu12+sA", RooArgList(sA,sB,sC,sD,sE,mu12));
    RooFormulaVar alpha12("alpha12", "aI*pow(mu12,3)+aH*pow(mu12,2)+aG*mu12+aF", RooArgList(aI,aH,aG,aF,mu12));
    RooFormulaVar n12("n12", "nJ/mu12+nK*mu12+nL", RooArgList(nJ,mu12,nK,nL));
    RooCBShape cb12("cb12", "", tof, mu12, sigma12, alpha12, n12);
    
    //---------- Peak Number 13 ----------
    RooRealVar yield13("yield13", "", yStart, yLow, yHigh);
    RooRealVar mu13("mu13","", peaks[13], peaks[13]-wiggle, peaks[13]+wiggle);
    RooFormulaVar sigma13("sigma13", "sE*pow(mu13,4)+sD*pow(mu13,3)+sC*pow(mu13,2)+sB*mu13+sA", RooArgList(sA,sB,sC,sD,sE,mu13));
    RooFormulaVar alpha13("alpha13", "aI*pow(mu13,3)+aH*pow(mu13,2)+aG*mu13+aF", RooArgList(aI,aH,aG,aF,mu13));
    RooFormulaVar n13("n13", "nJ/mu13+nK*mu13+nL", RooArgList(nJ,mu13,nK,nL));
    RooCBShape cb13("cb13", "", tof, mu13, sigma13, alpha13, n13);
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(high*binning);
    frame->SetTitle("");
    frame->SetAxisRange(0.,500.,"Y");
    frame->SetAxisRange(0.,200.,"X");
    frame->SetXTitle("Time-of-Flight (2 ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    
    RooArgList cbs(cb00,cb01,cb02,cb03,cb04,cb05,cb06,cb07,cb08);
    cbs.add(RooArgList(cb09,cb10,cb11,cb12,cb13));
    RooArgList yields(yield00,yield01,yield02,yield03,yield04,yield05,yield06,yield07,yield08);
    yields.add(RooArgList(yield09,yield10,yield11,yield12,yield13));
    RooAddPdf model("model", "", cbs, yields);

    RooDataSet *data = RooDataSet::read(dataName.c_str(), RooArgList(tof));

    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(low, high));

    cout << sigma00.getVal() << " " << alpha00.getVal() << " " << n00.getVal() 
         << endl;

    ofstream resultsParam(resultsFile.c_str());
    fitResult->printMultiline(resultsParam, 0, true, "");
    resultsParam.close();

    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    model.plotOn(frame,Components("cb00"),LineColor(kGreen), LineStyle(kDashed));
    model.plotOn(frame,Components("cb01"),LineColor(kRed), LineStyle(kDashed));
    model.plotOn(frame,Components("cb02"),LineColor(kBlue), LineStyle(kDashed));
    model.plotOn(frame,Components("cb03"),LineColor(kViolet), LineStyle(kDashed));
    model.plotOn(frame,Components("cb04"),LineColor(kBlack), LineStyle(kDashed));
    model.plotOn(frame,Components("cb05"),LineColor(kPink), LineStyle(kDashed));
    model.plotOn(frame,Components("cb06"),LineColor(kGreen), LineStyle(kDashed));
    model.plotOn(frame,Components("cb07"),LineColor(kRed), LineStyle(kDashed));
    model.plotOn(frame,Components("cb08"),LineColor(kBlue), LineStyle(kDashed));
    model.plotOn(frame,Components("cb09"),LineColor(kViolet), LineStyle(kDashed));
    model.plotOn(frame,Components("cb10"),LineColor(kBlack), LineStyle(kDashed));
    model.plotOn(frame,Components("cb11"),LineColor(kPink), LineStyle(kDashed));
    model.plotOn(frame,Components("cb12"),LineColor(kGreen), LineStyle(kDashed));
    model.plotOn(frame,Components("cb13"),LineColor(kRed), LineStyle(kDashed));
    
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
