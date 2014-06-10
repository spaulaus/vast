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

SimConvoluter::SimConvoluter(const std::string &cfg) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(cfg.c_str());
    if(result) {
        cout << "Successfully opened the configuration file, proceeding to "
             << "fill up all of my naughty bits." << endl << endl;
        pugi::xml_node base = doc.child("Configuration").child("Simulation");

        flightPath_ = 
            doc.child("Configuration").child("Experiment").child("flightPath").
            attribute("value").as_double();

        //Here are the base directories that things will be saved to
        inputDir_ = base.child("inputBase").child_value();
        outputDir_ = base.child("outputBase").child_value();
        
        //check that the output directory exists
        FileChecker result ("dir",outputDir_);

        //Here are all our output filenames
        convHists_ = base.child("output").child("conv").child_value();
        simHists_ = base.child("output").child("sims").child_value();
        convFile_ = base.child("output").child("convData").child_value();
        fitFile_ = base.child("output").child("fitData").child_value();
        
        //Read in the range for the fitting
        rng_ = make_pair(base.child("range").
                         child("low").attribute("value").as_double(),
                         base.child("range").
                         child("high").attribute("value").as_double());

        //Read in the range for the fitting
        convRng_ = make_pair(base.child("convRange").
                         child("low").attribute("value").as_double(),
                         base.child("convRange").
                         child("high").attribute("value").as_double());
        
        //Read in all the energies for fitting and their associated filenames
        for(auto en : base.child("energies").children())
            energies_.insert(make_pair(en.attribute("energy").as_double(),
                                       en.attribute("file").value()));
        
        // //Open up the ROOT file to store the histograms
        // f_.Open((outputDir_+histogramFile_).c_str(),"RECREATE");
        
        //Finally begin to do the fits to the simulation data
        FitSim();
    } else {
        cerr << "We had errors with the config file. " << endl
             << "Error Description: " << result.description() << endl;
        cerr << "This is a fatal problem. Exiting..." << endl;
        exit(2);
    }
}

double SimConvoluter::CalcBetaRes(const double &tof) {
    //These parameters are from Miguel's spreadsheet
    if(tof <= 42.5)
        return(0.071824559*tof+1.5544112228);
    else
        return(0.0168145157*tof+3.7803929763);
}

void SimConvoluter::FitMc(const double &en, const double &mu, 
                          const double &sigma, const double &alpha, 
                          const double &n, ofstream &convOut) {
    convOut << header_ << endl;

    //---------- DO THE CONVOLUTION AND RECALCULATE THE PARAMETERS -------
    double simLow  = mu - rng_.first;
    double simHigh = mu + rng_.second;
    RooRealVar simTof("simTof", "tof for the simulation", 0.0, 4000., "ns");
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
    
    //frame1->Write();

    // TCanvas* c1 = new TCanvas("c1","",0,0,700,500);
    // c1->cd();
    // frame1->Draw();
    // c1->Write("test.eps");
    
    convOut << setprecision(6) 
            << en << " " << zMu.getValV() << " " 
            << zSigma.getValV() << " " << zSigma.getError() << " "
            << zAlpha.getValV() << " " << zAlpha.getError() << " " 
            << zN.getValV() << " " << zN.getError() << " " << endl;
    
    if(mcFit->statusCodeHistory(0) == 0) {
        cout << endl << endl << "Oh, Jesus, the fit did not converge for the " 
             << "simulation to the " << en << " keV" << " case." << endl;
        exit(1);
    }else
        cout << endl << endl << "The fit converged successfully." << endl;
}

void SimConvoluter::FitSim(void) {
    //Prepare the datastreams
    ofstream simOut((outputDir_+fitFile_).c_str());
    simOut << header_ << endl;
    ofstream convOut((outputDir_+convFile_).c_str());

    TFile f((outputDir_+simHists_).c_str(), "RECREATE");

    RooRealVar tof("tof","tof", 0., 4000.);
    RooPlot* frame = tof.frame();
    frame = tof.frame(2000);
    frame->SetTitle("");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    //frame->Write();

    for(const auto it : energies_) {
        string inputName = inputDir_ + it.second;
        FileChecker dataChk("file", inputName);
        
        //Set the information for the peaks
        PhysConstants consts;
        double mass = consts.GetConstant("neutronMass").GetValue(); //MeV/c^2
        double c = consts.GetConstant("c").GetValue()*(100/1e9); //cm/ns
        double peak = (flightPath_/c)*sqrt(mass/(2*it.first/1000.));
        
        //Read in the data and set the variable to fit.
        double low = peak-rng_.first;
        double high = peak+rng_.second;
        RooDataSet *data = RooDataSet::read(inputName.c_str(), 
                                            RooArgList(tof));

        //Setup the CB to fit
        RooRealVar yield("yield", "", 1.e4, 0., 1.e7);
        RooRealVar mu("mu","", peak, peak-300., peak+300.);
        RooRealVar sigma("sigma", "", 2., 0, 20.);
        RooRealVar alpha("alpha", "", -1., -10., 0.);
        RooRealVar n("n", "", 2., 0., 20.);
        RooCBShape cb("cb", "", tof, mu, sigma, alpha, n);
        
        //marry the CB with the yield
        RooAddPdf model("model", it.second.c_str(), RooArgList(cb), RooArgList(yield));
        
        //Perform the fit and store the results in the "fitResult" variable
        RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                              Range(low, high));
        
        data->plotOn(frame,Name("data"));
        model.plotOn(frame,Name("model"));
        
        stringstream canvName;
        canvName << "sim" << it.first;
        TCanvas* canv = new TCanvas(canvName.str().c_str(),"",0,0,700,500);
        canv->cd();
        frame->Draw();
        canv->Write(canvName.str().c_str());
        delete canv;
        frame->remove("data");
        frame->remove("model");
        
        if(fitResult->statusCodeHistory(0) == 0) {
            cout << endl << endl << "The Fit to the simulated data" << it.second 
                 << "  keV.dat converged successufully, proceeding with fit "
                 << "to convoluted function." << endl << endl;
            simOut << setprecision(6) 
                   << it.first << " " << mu.getValV() << " " 
                   << sigma.getValV() << " " << sigma.getError() << " "
                   << alpha.getValV() << " " << alpha.getError() << " " 
                   << n.getValV() << " " << n.getError() << " " << endl;
            // FitMc(it.first, mu.getValV(), sigma.getValV(), alpha.getValV(), n.getValV(), 
            //       convOut);
            FitMc(it.first, mu.getValV(), sigma.getValV(), alpha.getValV(), n.getValV(), 
                  convOut);
        } else {
            cerr << endl << endl << "Oh, Jesus, the fit to the simulated data for " 
                 << it.second << "keV.dat did not converge!!" << endl;
            simOut.close();
            exit(1);
        }
    }//for(const auto &it : energies_)
    simOut.close();
    convOut.close();
    f.Close();
}
