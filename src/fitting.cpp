#include <iostream>

#include <cmath>

#include "TFile.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooDecay.h"
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
    double fitMax = numPoints;
    RooRealVar tof("tof","tof",0,numPoints);
    RooDataSet *data = RooDataSet::read("data/tofs.dat", RooArgList(tof));

    double peaks[]={17.333, 21.333, 27.111, 31.111, 34.222, 40.444, 45.778, 
                    49.778, 56, 60.444, 66.222, 70.667, 77.333, 84.889,
                    92.889, 102.222, 111.111, 120, 127};
    double wiggle=7.;
    double areaStart = 100;
    double resolution=3.945;

    //---------- Constants ----------
    RooRealVar sigma("sigma", "sigma for the gaussians", 
                     resolution/(2*sqrt(2*log(2))));
    //RooRealVar tau("tau", "decay constant for penetration", 0.0253);
    RooRealVar tau("tau", "decay constant for penetration", 0.);
    
    //---------- Pdfs ----------
    RooRealVar alpha0("alpha0","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    //RooRealVar tau0("tau0", "decay constant for penetration", 0.0253, 0, 3);
    RooGaussModel core0("core", "Gaussian for resolution", tof, mu0, sigma);
    RooDecay vandle0("vandle0", "Penetration into bar", tof, 
                     tau, core0, RooDecay::SingleSided);
    //tau0, core0, RooDecay::SingleSided);
     
    RooRealVar alpha1("alpha1","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    //RooRealVar tau1("tau1", "decay constant for penetration", 0.0253, 0, 3);
    RooGaussModel core1("core1", "Gaussian for resolution", tof, mu1, sigma);
    RooDecay vandle1("vandle1", "Penetration into bar", tof, 
                     tau, core1, RooDecay::SingleSided);
    //tau1, core1, RooDecay::SingleSided);

    RooRealVar alpha2("alpha2","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle, peaks[2]+wiggle);
    //RooRealVar tau2("tau2", "decay constant for penetration", 0.0253, 0, 3);
    RooGaussModel core2("core2", "Gaussian for resolution", tof, mu2, sigma);
    RooDecay vandle2("vandle2", "Penetration into bar", tof, 
                     //tau2, core2, RooDecay::SingleSided);
                     tau, core2, RooDecay::SingleSided);

    RooRealVar alpha3("alpha3","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu3("mu3","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    //RooRealVar tau3("tau3", "decay constant for penetration", 0.0253, 0, 3);
    RooGaussModel core3("core3", "Gaussian for resolution", tof, mu3, sigma);
    RooDecay vandle3("vandle3", "Penetration into bar", tof, 
                     //                 tau3, core3, RooDecay::SingleSided);
                 tau, core3, RooDecay::SingleSided);

    RooRealVar alpha4("alpha4","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu4("mu4","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    //RooRealVar tau4("tau4", "decay constant for penetration", 0.0253, 0, 3);
    RooGaussModel core4("core4", "Gaussian for resolution", tof, mu4, sigma);
    RooDecay vandle4("vandle4", "Penetration into bar", tof, 
                     tau, core4, RooDecay::SingleSided);
    //                 tau4, core4, RooDecay::SingleSided);

    RooRealVar alpha5("alpha5","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu5("mu5","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    //RooRealVar tau5("tau5", "decay constant for penetration", 0.0253, 0, 3);
    RooGaussModel core5("core5", "Gaussian for resolution", tof, mu5, sigma);
    RooDecay vandle5("vandle5", "Penetration into bar", tof, 
                     tau, core5, RooDecay::SingleSided);
    //                 tau5, core5, RooDecay::SingleSided);

    RooArgList prodList(vandle0,vandle1,vandle2, vandle3, vandle4, vandle5);
    RooArgList areaList(alpha0,alpha1,alpha2, alpha3, alpha4, alpha5);

    // /////////////////////////////////
    RooAddPdf model("model","model", prodList, areaList);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), Range(0., fitMax));

    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(numPoints);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events/(ns)");
    frame->GetYaxis()->SetTitleOffset(1.2);
    data->plotOn(frame,Name("data"));
    
    model.plotOn(frame,Name("model"));
    model.plotOn(frame,RooFit::Components("vandle0"),RooFit::LineColor(kGreen), 
        RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("vandle1"),RooFit::LineColor(kRed), 
        RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("vandle2"),RooFit::LineColor(kYellow), 
        RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("vandle3"),RooFit::LineColor(kViolet), 
        RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("vandle4"),RooFit::LineColor(kOrange), 
        RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("vandle5"),RooFit::LineColor(kPink), 
        RooFit::LineStyle(kDashed));
    
    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    c->SetFillColor(kWhite);
    frame->Draw();
    c->SaveAs("pics/image.eps");
}
