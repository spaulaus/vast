#include <iostream>
#include <iomanip>

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
    double numPoints = 110;
    double fitMax = numPoints;
    RooRealVar tof("tof","tof",0,numPoints);
    RooDataSet *data = RooDataSet::read("data/tof-banana.dat", RooArgList(tof));

    double peaks[]={18.333, 22.3378, 26.111, 31.111, 34.222, 40.444, 45.778, 
                    49.778, 56, 60.444, 66.222, 70.667, 77.333, 84.889,
                    92.889, 102.222, 111.111, 120, 127};
    double areaStart = 100;
    double resolution0 = 3.945;
    double resolution1 = 5.805;
    double wiggle = 3;

    //---------- Constants ----------
    RooRealVar sigma0("sigma0", "sigma for the gaussians", 
                      resolution0/(2*sqrt(2*log(2))));
    RooRealVar sigma1("sigma1", "sigma for the gaussians", 
                      resolution1/(2*sqrt(2*log(2))));

    //---------- Pdfs ----------
    RooRealVar alpha0("alpha0","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooGaussModel core0("core0", "Gaussian for resolution", tof, mu0, sigma0);

    RooRealVar alpha1("alpha1","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooGaussModel core1("core1", "Gaussian for resolution", tof, mu1, sigma0);

    RooRealVar alpha2("alpha2","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle, peaks[2]+wiggle);
    RooGaussModel core2("core2", "Gaussian for resolution", tof, mu2, sigma0);

    RooRealVar alpha3("alpha3","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu3("mu3","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooGaussModel core3("core3", "Gaussian for resolution", tof, mu3, sigma0);

    RooRealVar alpha4("alpha4","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu4("mu4","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooGaussModel core4("core4", "Gaussian for resolution", tof, mu4, sigma0);

    RooRealVar alpha5("alpha5","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu5("mu5","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooGaussModel core5("core5", "Gaussian for resolution", tof, mu5, sigma0);

    RooRealVar alpha6("alpha6","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu6("mu6","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooGaussModel core6("core6", "Gaussian for resolution", tof, mu6, sigma0);

    RooRealVar alpha7("alpha7","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu7("mu7","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooGaussModel core7("core7", "Gaussian for resolution", tof, mu7, sigma0);

    RooRealVar alpha8("alpha8","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu8("mu8","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooGaussModel core8("core8", "Gaussian for resolution", tof, mu8, sigma0);

    RooRealVar alpha9("alpha9","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu9("mu9","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooGaussModel core9("core9", "Gaussian for resolution", tof, mu9, sigma0);

    RooRealVar alpha10("alpha10","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooGaussModel core10("core10", "Gaussian for resolution", tof, mu10, sigma1);

    RooRealVar alpha11("alpha11","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu11("mu11","", peaks[11], peaks[11]-wiggle, peaks[11]+wiggle);
    RooGaussModel core11("core11", "Gaussian for resolution", tof, mu11, sigma1);

    RooRealVar alpha12("alpha12","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu12("mu12","", peaks[12], peaks[12]-wiggle, peaks[12]+wiggle);
    RooGaussModel core12("core12", "Gaussian for resolution", tof, mu12, sigma1);
    
    RooRealVar alpha13("alpha13","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu13("mu13","", peaks[13], peaks[13]-wiggle, peaks[13]+wiggle);
    RooGaussModel core13("core13", "Gaussian for resolution", tof, mu13, sigma1);

    RooRealVar alpha14("alpha14","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu14("mu14","", peaks[14], peaks[14]-wiggle, peaks[14]+wiggle);
    RooGaussModel core14("core14", "Gaussian for resolution", tof, mu14, sigma1);

    RooRealVar alpha15("alpha15","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu15("mu15","", peaks[15], peaks[15]-wiggle, peaks[15]+wiggle);
    RooGaussModel core15("core15", "Gaussian for resolution", tof, mu15, sigma1);

    RooRealVar alpha16("alpha16","number of events in peak 0", areaStart, 0, 5000);
    RooRealVar mu16("mu16","", peaks[16], peaks[16]-wiggle, peaks[16]+wiggle);
    RooGaussModel core16("core16", "Gaussian for resolution", tof, mu16, sigma1);

    RooArgList prodList(core0,core1,core2, core3, core4, core5, core6, core7, core8);
    prodList.add(RooArgList(core9, core10, core11, core12, core13, core14, core15, core16));
    RooArgList areaList(alpha0,alpha1,alpha2, alpha3, alpha4, alpha5, alpha6, alpha7, alpha8);
    areaList.add(RooArgList(alpha9, alpha10, alpha11, alpha12, alpha13, alpha14, alpha15, alpha16));

    // /////////////////////////////////
    RooAddPdf model("model","model", prodList, areaList);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(0., fitMax));

    ofstream resultsParam("results-full.dat");
    fitResult->printMultiline(resultsParam, 0, false, "");
    resultsParam.close();
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(numPoints);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events/(ns)");
    frame->GetYaxis()->SetTitleOffset(1.2);
    data->plotOn(frame,Name("data"));
    
    model.plotOn(frame,Name("model"));
    model.plotOn(frame,RooFit::Components("core0"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core1"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core2"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core3"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core4"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core5"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core6"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core7"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core8"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core9"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core10"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core11"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core12"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core13"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core14"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core15"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("core16"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    
    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    c->SetFillColor(kWhite);
    frame->Draw();
    c->SaveAs("../pics/roofit/working.eps");
}
