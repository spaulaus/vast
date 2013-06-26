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

#include "ToFFitter.hpp"

using namespace std;

void fitting(void);

int main(int argc, char* argv[]) {
    ToFFitter fitter(0.,200.);

    string dirName = "077cu-ban4-lower/";
    string fileName = "077cu-ban4-lower-tof";
    fitter.LoadData(dirName, fileName);
    fitter.SetEpsName("../pics/roofit/working.eps");
    fitter.SetResultsFile("results/working.fit");
    
    //fit.FitData(pks,yields);
}

void fitting(void) {
    // //Do the plots
    // RooPlot* frame = tof.frame();
    // frame = tof.frame(high*0.5);
    // frame->SetTitle("Time-of-Flight Spectrum");
    // frame->SetXTitle("Time-of-Flight (2 ns)");
    // frame->SetYTitle("Events / 2 ns");
    // frame->GetYaxis()->SetTitleOffset(1.2);
    
    // data->plotOn(frame,Name("data"));
    // model.plotOn(frame,Name("model"));

    // model.plotOn(frame,Components("pk00"),LineColor(kGreen), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk01"),LineColor(kRed), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk02"),LineColor(kYellow), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk03"),LineColor(kViolet), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk04"),LineColor(kOrange), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk05"),LineColor(kPink), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk06"),LineColor(kGreen), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk07"),LineColor(kRed), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk08"),LineColor(kYellow), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk09"),LineColor(kViolet), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk11"),LineColor(kOrange), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk12"),LineColor(kPink), 
    //              LineStyle(kDashed));
    // model.plotOn(frame,Components("pk13"),LineColor(kGreen), 
    //              LineStyle(kDashed));
    
    // TCanvas* c = new TCanvas("c","",0,0,700,500);
    // c->cd();
    // frame->Draw();
    // c->SaveAs(epsName.c_str());
       
    // if(fitResult->statusCodeHistory(0) != 0)
    //     cout << endl << endl << "Oh, Jesus, the fit did not converge." << endl;
    // else
    //     cout << endl << endl << "The fit converged successfully." << endl;

    // if(fitResult->statusCodeHistory(1) != 0)
    //     cout << "Hesse FAILED to calculate things properly." << endl << endl;
    // else
    //     cout << "HESSE successfully calculated things." << endl << endl;
}
