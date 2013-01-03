#include <iostream>

#include <cmath>

#include "TFile.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

using namespace std;
using namespace RooFit;

void fitting(void);

int main(int argc, char* argv[]) {
    string fileName="data/tofs.dat";
    fitting();
}

void fitting(void) {
    //Read in the data and set the variable to fit.
    double numPoints = 40;
    RooRealVar tof("tof","tof",0,numPoints);
    RooDataSet *data = RooDataSet::read("data/tofs.dat", RooArgList(tof));

    double peaks[]={17.333, 21.333, 27.111, 31.111, 34.222, 40.444, 45.778, 
                    49.778, 56, 60.444, 66.222, 70.667, 77.333, 84.889,
                    92.889, 102.222, 111.111, 120, 127};
    double wiggle=7.;
    double areaStart = 500.;
    double resolution=3.5;
    double sigma = resolution/(2*sqrt(2*log(2)));
    double tau=-0.0253;
    
    // PDFs parameters for peak 0
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooRealVar sigma0("sigma0","", sigma);
    RooRealVar alpha0("alpha0","number of events in peak 0", areaStart, 0, 5000);
    RooGaussian peak0("peak0","peak distribution", tof, mu0, sigma0);
    RooRealVar tau0("tau0", "", CalcVelocity(peaks[0])*tau, -5., 0.);
    RooExponential decay0("decay0", "decay part 0", tof, tau0);
    RooProdPdf vandle0 ("vandle0", "vandle dist 0", RooArgList(decay0,peak0));
    // PDFs parameters for peak 1
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooRealVar sigma1("sigma1","", sigma);
    RooRealVar alpha1("alpha1","number of events in peak 1", areaStart, 0, 5000);
    RooGaussian peak1("peak1","peak distribution",tof,mu1,sigma1);
    RooRealVar tau1("tau1", "", CalcVelocity(peaks[1])*tau, -5., 0.);
    RooExponential decay1("decay1", "decay part 0", tof, tau1);
    RooProdPdf vandle1 ("vandle1", "vandle dist 0", RooArgList(decay1,peak1));
    // PDFs parameters for peak 2
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle, peaks[2]+wiggle);
    RooRealVar sigma2("sigma2","", sigma);
    RooRealVar alpha2("alpha2","number of events in peak 2", areaStart, 0, 5000.);
    RooGaussian peak2("peak2","peak distribution",tof,mu2,sigma2);
    RooRealVar tau2("tau2", "", CalcVelocity(peaks[2])*tau, -5., 0.);
    RooExponential decay2("decay2", "decay part 2", tof, tau2);
    RooProdPdf vandle2("vandle2", "vandle dist 2", RooArgList(decay2,peak2));
    // PDFs parameters for peak 3
    RooRealVar mu3("mu3","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooRealVar sigma3("sigma3","", sigma);
    RooRealVar alpha3("alpha3","number of events in peak 3",areaStart,0, 5000.);
    RooGaussian peak3("peak3","peak distribution",tof,mu3,sigma3);
    RooRealVar tau3("tau3", "", CalcVelocity(peaks[3])*tau, -5., 0.);
    RooExponential decay3("decay3", "decay part 3", tof, tau3);
    RooProdPdf vandle3 ("vandle3", "vandle dist 3", RooArgList(decay3,peak3));
    // PDFs parameters for peak 4
    RooRealVar mu4("mu4","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooRealVar sigma4("sigma4","", sigma);
    RooRealVar alpha4("alpha4","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak4("peak4","peak distribution",tof,mu4,sigma4);
    RooRealVar tau4("tau4", "", CalcVelocity(peaks[4])*tau, -5., 0.);
    RooExponential decay4("decay4", "decay part 4", tof, tau4);
    RooProdPdf vandle4 ("vandle4", "vandle dist 4", RooArgList(decay4,peak4));
    // PDFs parameters for peak 5
    RooRealVar mu5("mu5","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooRealVar sigma5("sigma5","", sigma);
    RooRealVar alpha5("alpha5","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak5("peak5","peak distribution",tof,mu5,sigma5);
    RooRealVar tau5("tau5", "", CalcVelocity(peaks[5])*tau, -5., 0.);
    RooExponential decay5("decay5", "decay part 5", tof, tau5);
    RooProdPdf vandle5 ("vandle5", "vandle dist 5", RooArgList(decay5,peak5));
    // PDFs parameters for peak 6
    RooRealVar mu6("mu6","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooRealVar sigma6("sigma6","", sigma);
    RooRealVar alpha6("alpha6","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak6("peak6","peak distribution",tof,mu6,sigma6);
    RooRealVar tau6("tau6", "", CalcVelocity(peaks[6])*tau, -5., 0.);
    RooExponential decay6("decay6", "decay part 6", tof, tau6);
    RooProdPdf vandle6 ("vandle6", "vandle dist 6", RooArgList(decay6,peak6));
    // PDFs parameters for peak 7
    RooRealVar mu7("mu7","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooRealVar sigma7("sigma7","", sigma);
    RooRealVar alpha7("alpha7","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak7("peak7","peak distribution",tof,mu7,sigma7);
    RooRealVar tau7("tau7", "", CalcVelocity(peaks[7])*tau, -5., 0.);
    RooExponential decay7("decay7", "decay part 7", tof, tau7);
    RooProdPdf vandle7 ("vandle7", "vandle dist 7", RooArgList(decay7,peak7));

    RooArgList prodList(vandle0,vandle1,vandle2,vandle3,vandle4,vandle5,vandle6, 
                        vandle7);
    RooArgList areaList(alpha0,alpha1,alpha2,alpha3,alpha4,alpha5,alpha6, alpha7);

    /////////////////////////////////
    RooAddPdf model("model","model", prodList, areaList);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), Range(0.,140.));

    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(numPoints*0.5);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events/(ns)");
    frame->GetYaxis()->SetTitleOffset(1.2);
    data->plotOn(frame,Name("data"));
    
    // model.plotOn(frame,Name("model"));
    // model.plotOn(frame,RooFit::Components("peak0"),RooFit::LineColor(kGreen), 
    //              RooFit::LineStyle(kDashed));
    // model.plotOn(frame,RooFit::Components("peak1"),RooFit::LineColor(kRed), 
    //              RooFit::LineStyle(kDashed));
    // model.plotOn(frame,RooFit::Components("peak2"),RooFit::LineColor(kYellow), 
    //              RooFit::LineStyle(kDashed));
    // model.plotOn(frame,RooFit::Components("peak3"),RooFit::LineColor(kViolet), 
    //              RooFit::LineStyle(kDashed));
    // model.plotOn(frame,RooFit::Components("peak4"),RooFit::LineColor(kOrange), 
    //              RooFit::LineStyle(kDashed));
    // model.plotOn(frame,RooFit::Components("peak5"),RooFit::LineColor(kPink), 
    //              RooFit::LineStyle(kDashed));
    
    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    c->SetFillColor(kWhite);
    frame->Draw();
    c->SaveAs("pics/image.eps");
}
