///@file TofFitter.cpp
///@brief Convolutes the simulation response functions.
///@author S. V. Paulauskas
///@date October 6, 2013

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

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

#include "IoHelperFunctions.hpp"
#include "SimConvoluter.hpp"

using namespace std;
using namespace RooFit;

SimConvoluter::SimConvoluter(const std::string &cfg) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(cfg.c_str());
    if(result) {
        cout << "Successfully opened the configuration file, proceeding to "
             << "fill up all of my naughty bits." << endl << endl;
        pugi::xml_node base = doc.child("ConfigurationReader").child("Simulation");

        flightPath_ = base.child("flightPath").attribute("value").as_double();

        inputDir_ = base.child("inputBase").child_value();
        if(!IoHelpers::HasWritePermission(inputDir_))
            throw VastIoException("SimConvoluter::SimConvoluter - We couldn't open the input directory ("
                                  + inputDir_ + " )!!");

        outputDir_ = base.child("outputBase").child_value();
        if(!IoHelpers::HasWritePermission(outputDir_))
            throw VastIoException("SimConvoluter::SimConvoluter - We couldn't open the output directory ("
                                  + outputDir_ + " )!!");


        simHists_ = base.child("output").child("sims").child_value();
        convFile_ = base.child("output").child("convData").child_value();
        fitFile_ = base.child("output").child("fitData").child_value();

        rng_ = make_pair(base.child("range").child("low").attribute("value").as_double(),
                         base.child("range").child("high").attribute("value").as_double());

        for(auto en : base.child("energies").children())
            energies_.insert(make_pair(en.attribute("energy").as_double(), en.attribute("file").value()));
        FitSim();
    } else
        throw SimConvoluterException("SimConvoluter::SimConvoluter - There was an error in the config file: " + cfg);
}

///This method calculates the beta resolution as a function of ToF
double SimConvoluter::CalcBetaRes(const double &tof) {
    ///@TODO What is this 42.5?
    if(tof <= 42.5)
        return((0.071824559*tof+1.5544112228)/(2*sqrt(2*log(2))));
    else
        return((0.0168145157*tof+3.7803929763)/(2*sqrt(2*log(2))));
}

///This method calculates the convoluted Crystal ball parameters of the Monte Carlo fit
void SimConvoluter::FitMc(const double &en, const double &mu, const double &sigma, const double &alpha,
                          const double &n, ofstream &convOut) {
    double simLow  = mu - rng_.first;
    double simHigh = mu + rng_.second;
    RooRealVar tof("tof", "tof for the simulation", 0.0, 4000., "ns");
    tof.setBins(1e5,"cache");

    RooRealVar res("res", "res for gauss model", CalcBetaRes(mu));
    RooRealVar x("x", "mean for gauss model", 0.0);

    RooRealVar simMu("simMu","", mu);
    RooRealVar simSigma("simSigma", "", sigma);
    RooRealVar simAlpha("simAlpha", "", alpha);
    RooRealVar simN("simN", "", n);
    RooCBShape simCb("simCb", "", tof, simMu, simSigma, simAlpha, simN);

    RooGaussModel gauss("gauss", "", tof, x, res);
    RooFFTConvPdf pk("pk","",tof,simCb,gauss);
    RooDataSet* mcData = pk.generate(tof,1.e6);

    RooRealVar zYield("zYield", "", 1.e6, 0., 1.e8);
    RooRealVar zMu("zMu","", mu);
    RooRealVar zSigma("zSigma", "", 2., 0., 100.);
    RooRealVar zAlpha("zAlpha", "", -1.0, -100., 0.);
    RooRealVar zN("zN", "", 1., 0., 500.);
    RooCBShape zCb("zCb", "", tof, zMu, zSigma, zAlpha, zN);

    RooAddPdf model1("model1", "", RooArgList(zCb),RooArgList(zYield));

    RooFitResult *mcFit = model1.fitTo(*mcData, NumCPU(3), Save(), Range(simLow, simHigh));
    if(mcFit->statusCodeHistory(0) == 0) {
        stringstream dataName, modelName;
        dataName << "mc-data-" << en;
        mcData->Write(dataName.str().c_str());
        modelName << "conv-" << en;
        model1.Write(modelName.str().c_str());

        convOut << setprecision(6) << en << " " << zMu.getValV() << " " << zSigma.getValV() << " "
                << zSigma.getError() << " " << zAlpha.getValV() << " " << zAlpha.getError() << " "
                << zN.getValV() << " " << zN.getError() << " " << endl;
    } else
        throw SimConvoluterException("SimConvoluter::FitMc - The fit didn't converge. This is problematic...");
}

///This method calculates the fit of the simulated data.  This fit is used
/// to know how large the neutron tails are in the real data.
void SimConvoluter::FitSim(void) {
    PhysConstants consts;
    double c = consts.GetConstant("c").GetValue()*(100/1e9); //cm/ns
    double mass = consts.GetConstant("neutronMass").GetValue()/c/c; //MeV

    ofstream simOut((outputDir_+fitFile_).c_str());
    simOut << header_ << endl;
    ofstream convOut((outputDir_+convFile_).c_str());
    convOut << header_ << endl;
    TFile f((outputDir_+simHists_).c_str(), "RECREATE");

    RooRealVar tof("tof","tof", 0., 4000.);
    RooPlot* frame = tof.frame();
    frame = tof.frame(2000);
    frame->SetName("frame");
    frame->SetTitle("");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    tof.Write();
    frame->Write();

    for(const auto it : energies_) {
        string inputName = inputDir_ + it.second;

        if(!IoHelpers::HasWritePermission(inputName))
            throw VastIoException("SimConvoluter::FitSim - We couldn't open the input file : " + inputName + "!!");

        double peak = (flightPath_)*sqrt(mass/(2*it.first/1000.));

        double low = peak-rng_.first;
        double high = peak+rng_.second;
        RooDataSet *data = RooDataSet::read(inputName.c_str(),
                                            RooArgList(tof));

        RooRealVar yield("yield", "", 1.e4, 0., 1.e8);
        RooRealVar mu("mu","", peak, peak-30., peak+30.);
        RooRealVar sigma("sigma", "", 2., 0, 200.);
        RooRealVar alpha("alpha", "", -1., -10., 0.);
        RooRealVar n("n", "", 2., 0., 200.);
        RooCBShape cb("cb", "", tof, mu, sigma, alpha, n);

        RooAddPdf model("model", it.second.c_str(), RooArgList(cb), RooArgList(yield));
        RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(),
                                              Range(low, high));

        if(fitResult->statusCodeHistory(0) == 0) {
            stringstream dataName, modelName;

            dataName << "sim-data-" << it.first;
            data->Write(dataName.str().c_str());

            modelName << "sim-model-" << it.first;
            model.Write(modelName.str().c_str());

            simOut << setprecision(6)
                   << it.first << " " << mu.getValV() << " "
                   << sigma.getValV() << " " << sigma.getError() << " "
                   << alpha.getValV() << " " << alpha.getError() << " "
                   << n.getValV() << " " << n.getError() << " " << endl;
            FitMc(it.first, mu.getValV(), sigma.getValV(), alpha.getValV(),
                  n.getValV(), convOut);
        } else {
            simOut.close();
            f.Close();
            throw SimConvoluterException("SimConvoluter::FitSim - The fit didn't converge. This is problematic...");
        }
    }//for(const auto &it : energies_)
    simOut.close();
    convOut.close();
    f.Close();
}
