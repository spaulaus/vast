#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>
#include <cstdio>


#include <RooAddPdf.h>
#include <RooCBShape.h>
#include <RooConstVar.h>
#include <RooDataSet.h>
#include <RooFFTConvPdf.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include <RooGaussModel.h>
#include <RooMCStudy.h>
#include <RooPlot.h>
#include <RooRealVar.h>

#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>

#include <PhysConstants.hpp>

#include "FileChecker.hpp"
#include "SimConvoluter.hpp"

using namespace std;
using namespace RooFit;

SimConvoluter::SimConvoluter(const vector<string> &names, const string &dir, 
                             const pair<double,double> &rng) {
    header_ = "#Energy(keV) ToF(ns) sigma sigmaErr alpha alphaErr n nErr";
    names_  = names;
    dir_    = dir;
    rng_    = rng;
    FitSim();
}

double SimConvoluter::CalcBetaRes(const double &tof) {
    //These parameters are from Miguel's spreadsheet
    if(tof <= 42.5)
        return(0.071824559*tof+1.5544112228);
    else
        return(0.0168145157*tof+3.7803929763);
}

void SimConvoluter::FitMc(const string &name, const double &mu, 
                          const double &sigma, const double &alpha, 
                          const double &n, ofstream &convOut) {
    convOut << header_ << endl;

    string mcName = "pics/tof/"+dir_+name+"keV-mc-b.jpg";
    FileChecker mcChk("dir", mcName);
    
    //---------- DO THE CONVOLUTION AND RECALCULATE THE PARAMETERS -------
    double simLow  = mu - 20.;
    double simHigh = mu + 180.;
    RooRealVar simTof("simTof", "tof for the simulation", 0.0, rng_.first, rng_.second, "ns");
    simTof.setBins(1e5,"cache");
    
    //Set the information for the resolution model
    double detRes = CalcBetaRes(mu);
    RooRealVar res("res", "res for gauss model", detRes / (2*sqrt(2*log(2))));
    RooRealVar x("x", "mean for gauss model", 0.0);
    
    RooRealVar simMu("simMu","", mu);
    RooRealVar simSigma("simSigma", "", sigma);
    RooRealVar simAlpha("simAlpha", "", alpha);
    RooRealVar simN("simN", "", n);
    RooCBShape simCb("simCb", "", simTof, simMu, simSigma, simAlpha, simN);
    
    RooGaussModel gauss("gauss", "", simTof, x, res);
    RooFFTConvPdf pk("pk","",simTof,simCb,gauss);
    RooDataSet* mcData = pk.generate(simTof,1.e6);
    
    RooRealVar zYield("zYield", "", 1.e6, 0., 1.e8);
    RooRealVar zMu("zMu","", mu);
    RooRealVar zSigma("zSigma", "", 2., 0., 100.);
    RooRealVar zAlpha("zAlpha", "", -1.0, -100., 0.);
    RooRealVar zN("zN", "", 1., 0., 50.);
    RooCBShape zCb("zCb", "", simTof, zMu, zSigma, zAlpha, zN);
    
    RooAddPdf model1("model1", "", RooArgList(zCb),RooArgList(zYield));
    
    RooFitResult *mcFit = model1.fitTo(*mcData, NumCPU(3), Save(), 
                                       Range(simLow, simHigh));
    //Do the plots
    RooPlot* frame1 = simTof.frame();
    frame1 = simTof.frame(rng_.second);
    frame1->SetTitle("");
    frame1->SetXTitle("Time-of-Flight (ns)");
    frame1->SetYTitle("Events/ns");
    frame1->GetYaxis()->SetTitleOffset(1.2);
    frame1->SetAxisRange(simLow,simHigh,"X");        
    
    mcData->plotOn(frame1, Name("mcData"));
    model1.plotOn(frame1,Name("model1"));
    
    TCanvas* c1 = new TCanvas("c1","",0,0,700,500);
    c1->cd();
    frame1->Draw();
    c1->SaveAs(mcName.c_str());
    
    convOut << setprecision(6) 
            << atof(name.c_str()) << " " << zMu.getValV() << " " 
            << zSigma.getValV() << " " << zSigma.getError() << " "
            << zAlpha.getValV() << " " << zAlpha.getError() << " " 
            << zN.getValV() << " " << zN.getError() << " " << endl;
    
    if(mcFit->statusCodeHistory(0) == 0) {
        cout << endl << endl << "Oh, Jesus, the fit did not converge for the " 
             << "simulation to the " << name << "keV.dat" << " case." << endl;
        exit(1);
    }else
        cout << endl << endl << "The fit converged successfully." << endl;
}

void SimConvoluter::FitSim(void) {
    string simOutName = "results/"+dir_+"params-sim-b.dat";
    ofstream simOut(simOutName.c_str());
    simOut << "#Energy(keV) ToF(ns) sigma sigmaErr alpha alphaErr n nErr" << endl;

    string convOutName = "results/sim/"+dir_+"conv-b.dat";
    FileChecker result ("dir",convOutName);
    ofstream convOut(convOutName.c_str());

    for(vector<string>::iterator it = names_.begin(); it != names_.end(); it++) {
        string dataName="data/tof/"+dir_+*it+"keV.dat";
        FileChecker dataChk("file", dataName);

        string simName = "pics/tof/"+dir_+*it+"keV.jpg";
        FileChecker simChk("dir", simName);

        //Set the information for the peaks
        PhysConstants consts;
        double mass = consts.GetConstant("neutronMass").GetValue(); //MeV/c^2
        double c = consts.GetConstant("c").GetValue()*(100/1e9); //cm/ns
        double peak = (50.5/c)*sqrt(mass/(2*atof((*it).c_str())/1000.));
        double wiggle = 300.;
        
        //Read in the data and set the variable to fit.
        double low = peak-20.;
        double high = peak+1000.;
        RooRealVar tof("tof","tof", rng_.first, rng_.second);
        RooDataSet *data = RooDataSet::read(dataName.c_str(), 
                                            RooArgList(tof));
        
        RooRealVar yield("yield", "", 1.e4, 0., 1.e7);
        RooRealVar mu("mu","", peak, peak-wiggle, peak+wiggle);
        RooRealVar sigma("sigma", "", 2., 0, 20.);
        RooRealVar alpha("alpha", "", -1., -10., 0.);
        RooRealVar n("n", "", 2., 0., 20.);
        
        RooCBShape cb("cb", "", tof, mu, sigma, alpha, n);
        
        RooAddPdf model("model", "", RooArgList(cb), RooArgList(yield));
        
        RooFitResult* fit = model.fitTo(*data, NumCPU(3), Save(), 
                    Range(low, high));
        
        //Do the plots
        RooPlot* frame = tof.frame();
        frame = tof.frame(high*0.5);
        frame->SetTitle("");
        frame->SetXTitle("Time-of-Flight (ns)");
        frame->SetYTitle("Events/ns");
        frame->GetYaxis()->SetTitleOffset(1.2);
        frame->SetAxisRange(low,peak+180.,"X");        
        
        data->plotOn(frame,Name("data"));
        model.plotOn(frame,Name("model"));
        
        TCanvas* canv = new TCanvas("c","",0,0,700,500);
        canv->cd();
        frame->Draw();
        canv->SaveAs(simName.c_str());

        simOut << setprecision(6) 
               << atof((*it).c_str()) << " " << mu.getValV() << " " 
               << sigma.getValV() << " " << sigma.getError() << " "
               << alpha.getValV() << " " << alpha.getError() << " " 
               << n.getValV() << " " << n.getError() << " " << endl;

        if(fit->statusCodeHistory(0) == 0) {
            cout << endl << endl << "The Fit to the simulated data" << *it 
                 << "  keV.dat converged successufully!!" << endl << endl;
            FitMc(*it, mu.getValV(), sigma.getValV(), alpha.getValV(), n.getValV(), 
                  convOut);
        } else {
            cout << endl << endl << "Oh, Jesus, the fit to the simulated data for " 
                 << *it << "keV.dat did not converge!!" << endl;
            simOut.close();
            exit(1);
        }
    }//for(vector<string>::iterator it = names.begin()
    simOut.close();
    convOut.close();
}
