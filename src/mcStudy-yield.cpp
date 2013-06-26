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
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace std;
using namespace RooFit;

void fitting(void);
void MCStudy(const RooRealVar &data, const RooAddPdf &model, const RooArgList &subjects);

string dirName = "077cu-ban4-lower/";
string fileName = "077cu-ban4-lower-tof";
string mcStudyFldr = "../pics/roofit/"+dirName+"mcStudy/";

string dataName="../data/roofit/"+dirName+fileName+".dat";
string epsName = "../pics/roofit/"+dirName+fileName+"-mcStudy.eps";
string resultsFile = "results/"+dirName+fileName+"-mcStudy.fit";

// string picFldr = "../pics/roofit/working/";
// string epsName = picFldr+"working.eps";
// string mcStudyFldr = picFldr+"mcStudy/";
// string resultsFile = "results/working.dat";

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
    double peaks[]={21.618, 25.913, 32.203, 39.220, 45.983,
                    51.809, 57.904, 65.971, 72.315, 80.477, 
                    90.189, 97.541, 107.96, 134.16};

    double yStart = 3.e3, yLow = 0., yHigh = 1.e8;
    
    //Set the information for the resolution model
    double detRes = 4.0;
    RooRealVar res("res", "res for gauss model", detRes / (2*sqrt(2*log(2))));
    RooRealVar x("x", "mean for gauss model", 0.0);

    //Parameterization Parameters for Sigma -> sM*mu + sB
    RooRealVar sM("sM","Slope for sigma para.", 0.0264412131874119);
    RooRealVar sB("sB","Intercept for sigma para.", 0.0432494943386515);

    //Parameterization Parameters for Alpha -> aM/mu + aB
    RooRealVar aM("aM","Scale for alpha para.", -9.53022215447638);
    RooRealVar aB("aB","Intercept for alpha para.", -0.357060159281673);

    //Parameterization Parameters for N -> nM/mu + nB
    RooRealVar nM("nM","Scale for n para.", -5.99204241877324);
    RooRealVar nB("nB","Intercept for n para.", 1.25859614260662);
    
    //---------- Peak Number 0 ----------
    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", peaks[0]);
    RooFormulaVar sigma00("sigma00", "sM*mu00+sB", RooArgList(sM,mu00,sB));
    RooFormulaVar alpha00("alpha00", "aM/mu00+aB", RooArgList(aM,mu00,aB));
    RooFormulaVar n00("n00", "nM/mu00+nB", RooArgList(nM,mu00,nB));
    RooCBShape cb00("cb00", "", tof, mu00, sigma00, alpha00, n00);
    
    RooGaussModel res00("res00", "", tof, x, res);
    RooFFTConvPdf pk00("pk00","",tof,cb00,res00);
    
    //---------- Peak Number 1 ----------
    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", peaks[1]);
    RooFormulaVar sigma01("sigma01", "sM*mu01+sB", RooArgList(sM,mu01,sB));
    RooFormulaVar alpha01("alpha01", "aM/mu01+aB", RooArgList(aM,mu01,aB));
    RooFormulaVar n01("n01", "nM/mu01+nB", RooArgList(nM,mu01,nB));
    RooCBShape cb01("cb01", "", tof, mu01, sigma01, alpha01, n01);
    
    RooGaussModel res01("res01", "", tof, x, res);
    RooFFTConvPdf pk01("pk01","",tof,cb01,res01);
    
    //---------- Peak Number 2 ----------
    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", peaks[2]);
    RooFormulaVar sigma02("sigma02", "sM*mu02+sB", RooArgList(sM,mu02,sB));
    RooFormulaVar alpha02("alpha02", "aM/mu02+aB", RooArgList(aM,mu02,aB));
    RooFormulaVar n02("n02", "nM/mu02+nB", RooArgList(nM,mu02,nB));
    RooCBShape cb02("cb02", "", tof, mu02, sigma02, alpha02, n02);
    
    RooGaussModel res02("res02", "", tof, x, res);
    RooFFTConvPdf pk02("pk02","",tof,cb02,res02);
    
    //---------- Peak Number 3 ----------
    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", peaks[3]);
    RooFormulaVar sigma03("sigma03", "sM*mu03+sB", RooArgList(sM,mu03,sB));
    RooFormulaVar alpha03("alpha03", "aM/mu03+aB", RooArgList(aM,mu03,aB));
    RooFormulaVar n03("n03", "nM/mu03+nB", RooArgList(nM,mu03,nB));
    RooCBShape cb03("cb03", "", tof, mu03, sigma03, alpha03, n03);
    
    RooGaussModel res03("res03", "", tof, x, res);
    RooFFTConvPdf pk03("pk03","",tof,cb03,res03);
    
    //---------- Peak Number 4 ----------
    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", peaks[4]);
    RooFormulaVar sigma04("sigma04", "sM*mu04+sB", RooArgList(sM,mu04,sB));
    RooFormulaVar alpha04("alpha04", "aM/mu04+aB", RooArgList(aM,mu04,aB));
    RooFormulaVar n04("n04", "nM/mu04+nB", RooArgList(nM,mu04,nB));
    RooCBShape cb04("cb04", "", tof, mu04, sigma04, alpha04, n04);
    
    RooGaussModel res04("res04", "", tof, x, res);
    RooFFTConvPdf pk04("pk04","",tof,cb04,res04);
    
    //---------- Peak Number 5 ----------
    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", peaks[5]);
    RooFormulaVar sigma05("sigma05", "sM*mu05+sB", RooArgList(sM,mu05,sB));
    RooFormulaVar alpha05("alpha05", "aM/mu05+aB", RooArgList(aM,mu05,aB));
    RooFormulaVar n05("n05", "nM/mu05+nB", RooArgList(nM,mu05,nB));
    RooCBShape cb05("cb05", "", tof, mu05, sigma05, alpha05, n05);
    
    RooGaussModel res05("res05", "", tof, x, res);
    RooFFTConvPdf pk05("pk05","",tof,cb05,res05);
    
    //---------- Peak Number 6 ----------
    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", peaks[6]);
    RooFormulaVar sigma06("sigma06", "sM*mu06+sB", RooArgList(sM,mu06,sB));
    RooFormulaVar alpha06("alpha06", "aM/mu06+aB", RooArgList(aM,mu06,aB));
    RooFormulaVar n06("n06", "nM/mu06+nB", RooArgList(nM,mu06,nB));
    RooCBShape cb06("cb06", "", tof, mu06, sigma06, alpha06, n06);
    
    RooGaussModel res06("res06", "", tof, x, res);
    RooFFTConvPdf pk06("pk06","",tof,cb06,res06);
    
    //---------- Peak Number 7 ----------
    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", peaks[7]);
    RooFormulaVar sigma07("sigma07", "sM*mu07+sB", RooArgList(sM,mu07,sB));
    RooFormulaVar alpha07("alpha07", "aM/mu07+aB", RooArgList(aM,mu07,aB));
    RooFormulaVar n07("n07", "nM/mu07+nB", RooArgList(nM,mu07,nB));
    RooCBShape cb07("cb07", "", tof, mu07, sigma07, alpha07, n07);
    
    RooGaussModel res07("res07", "", tof, x, res);
    RooFFTConvPdf pk07("pk07","",tof,cb07,res07);
    
    //---------- Peak Number 8 ----------
    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", peaks[8]);
    RooFormulaVar sigma08("sigma08", "sM*mu08+sB", RooArgList(sM,mu08,sB));
    RooFormulaVar alpha08("alpha08", "aM/mu08+aB", RooArgList(aM,mu08,aB));
    RooFormulaVar n08("n08", "nM/mu08+nB", RooArgList(nM,mu08,nB));
    RooCBShape cb08("cb08", "", tof, mu08, sigma08, alpha08, n08);
    
    RooGaussModel res08("res08", "", tof, x, res);
    RooFFTConvPdf pk08("pk08","",tof,cb08,res08);
    
    //---------- Peak Number 9 ----------
    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", peaks[9]);
    RooFormulaVar sigma09("sigma09", "sM*mu09+sB", RooArgList(sM,mu09,sB));
    RooFormulaVar alpha09("alpha09", "aM/mu09+aB", RooArgList(aM,mu09,aB));
    RooFormulaVar n09("n09", "nM/mu09+nB", RooArgList(nM,mu09,nB));
    RooCBShape cb09("cb09", "", tof, mu09, sigma09, alpha09, n09);
    
    RooGaussModel res09("res09", "", tof, x, res);
    RooFFTConvPdf pk09("pk09","",tof,cb09,res09);
    
    //---------- Peak Number 10 ----------
    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", peaks[10]);
    RooFormulaVar sigma10("sigma10", "sM*mu10+sB", RooArgList(sM,mu10,sB));
    RooFormulaVar alpha10("alpha10", "aM/mu10+aB", RooArgList(aM,mu10,aB));
    RooFormulaVar n10("n10", "nM/mu10+nB", RooArgList(nM,mu10,nB));
    RooCBShape cb10("cb10", "", tof, mu10, sigma10, alpha10, n10);
    
    RooGaussModel res10("res10", "", tof, x, res);
    RooFFTConvPdf pk10("pk10","",tof,cb10,res10);
    
    //---------- Peak Number 11 ----------
    RooRealVar yield11("yield11", "", yStart, yLow, yHigh);
    RooRealVar mu11("mu11","", peaks[11]);
    RooFormulaVar sigma11("sigma11", "sM*mu11+sB", RooArgList(sM,mu11,sB));
    RooFormulaVar alpha11("alpha11", "aM/mu11+aB", RooArgList(aM,mu11,aB));
    RooFormulaVar n11("n11", "nM/mu11+nB", RooArgList(nM,mu11,nB));
    RooCBShape cb11("cb11", "", tof, mu11, sigma11, alpha11, n11);
    
    RooGaussModel res11("res11", "", tof, x, res);
    RooFFTConvPdf pk11("pk11","",tof,cb11,res11);
    
    //---------- Peak Number 12 ----------
    RooRealVar yield12("yield12", "", yStart, yLow, yHigh);
    RooRealVar mu12("mu12","", peaks[12]);
    RooFormulaVar sigma12("sigma12", "sM*mu12+sB", RooArgList(sM,mu12,sB));
    RooFormulaVar alpha12("alpha12", "aM/mu12+aB", RooArgList(aM,mu12,aB));
    RooFormulaVar n12("n12", "nM/mu12+nB", RooArgList(nM,mu12,nB));
    RooCBShape cb12("cb12", "", tof, mu12, sigma12, alpha12, n12);
    
    RooGaussModel res12("res12", "", tof, x, res);
    RooFFTConvPdf pk12("pk12","",tof,cb12,res12);
    
    //---------- Peak Number 13 ----------
    RooRealVar yield13("yield13", "", yStart, yLow, yHigh);
    RooRealVar mu13("mu13","", peaks[13]);
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

    MCStudy(tof,model,yields);

    if(fitResult->statusCodeHistory(0) != 0)
        cout << endl << endl << "Oh, Jesus, the fit did not converge." << endl;
    else
        cout << endl << endl << "The fit converged successfully." << endl;

    if(fitResult->statusCodeHistory(1) != 0)
        cout << "Hesse FAILED to calculate things properly." << endl << endl;
    else
        cout << "HESSE successfully calculated things." << endl << endl;
}

void MCStudy(const RooRealVar &data, const RooAddPdf &model, const RooArgList &subjects) {
    // validation of the ML fitting technique (also called MC "Toy" Experiment)
    // ---------------------------
    // C r e a t e   m a n a g e r
    // ---------------------------
    
    // Instantiate RooMCStudy manager on model with x as observable and given choice of fit options
    //
    // The Silence() option kills all messages below the PROGRESS level, leaving only a single message
    // per sample executed, and any error message that occur during fitting
    //
    // The Extended() option has two effects: 
    //    1) The extended ML term is included in the likelihood and 
    //    2) A poisson fluctuation is introduced on the number of generated events 
    //
    // The FitOptions() given here are passed to the fitting stage of each toy experiment.
    // If Save() is specified, the fit result of each experiment is saved by the manager  
    //
    // A Binned() option is added in this example to bin the data between generation and fitting
    // to speed up the study at the expense of some precision
    
    RooMCStudy* mcstudy = new RooMCStudy(model,data,Binned(kTRUE),Silence(),Extended(),
                                         FitOptions(Save(kTRUE),Range(0.,200.),PrintEvalErrors(0))) ;
    
    // ---------------------------------------------
    // G e n e r a t e   a n d   f i t   e v e n t s
    // ---------------------------------------------
    
    // Generate and fit 500 samples of Poisson(nExpected) events
    mcstudy->generateAndFit(1000) ;
    
    // ------------------------------------------------
    // E x p l o r e   r e s u l t s   o f   s t u d y 
    // ------------------------------------------------
    
    for(int i = 0; i < 14; i++) {
        // Plot distribution of minimized likelihood
        RooPlot* frame1 = mcstudy->plotNLL(Bins(40)) ;
        
        // Make plots of the distributions of the yield, the error on yield and the pull of yield
        RooRealVar subject = *((RooRealVar*)subjects.at(i));
        RooPlot* frame2 = mcstudy->plotParam(subject,Bins(40)) ;
        RooPlot* frame3 = mcstudy->plotError(subject,Bins(40)) ;
        RooPlot* frame4 = mcstudy->plotPull(subject,Bins(40),FitGauss(kTRUE)) ;
        
        TCanvas* cc = new TCanvas("cc","",500,500) ;
        cc->Divide(2,2) ;
        cc->cd(1) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
        cc->cd(2) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
        cc->cd(3) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
        cc->cd(4) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
        
        stringstream name;
        if(i < 10)
            name << mcStudyFldr << "yield0" << i << ".eps";
        else
            name << mcStudyFldr << "yield" << i << ".eps";
        cc->SaveAs(name.str().c_str());
    }
}
