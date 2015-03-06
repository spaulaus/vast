/** \file TofFitter.cpp
 * \brief A class to fit ToF spectra using RooFit
 * \author S. V. Paulauskas
 * \date 06 October 2013
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <cstdio>

#include <RooAddPdf.h>
#include <RooCBShape.h>
#include <RooConstVar.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include <RooMCStudy.h>
#include <RooPlot.h>
#include <RooRealVar.h>

#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>

#include "ParamCalculator.hpp"
#include "TofFitter.hpp"

using namespace std;
using namespace RooFit;

TofFitter::TofFitter(const FitHandler &fit, const FileHandler &fls) {
    fit_ = fit;
    fls_ = fls;

    binning_ = fit.GetBinning();
    peaks_ = fit.GetSnglPeaks();
    rng_ = fit.GetRange();
    wiggle_ = fit.GetWiggle();

    dataFile_ = fls.GetInputName("gsTof");
    eps_ = fls.GetOutputName("picGs");
    picDir_ = fls.GetOutputName("picDir");
    output_ = fls.GetOutputName("gsFit");

    StartRollin();
}

void TofFitter::CheckFileExistance(void) {
    ifstream test(dataFile_.c_str());
    if(test.fail()) {
        cout << "We couldn't open the data file to read"
             << "in the sexy data!!" << endl << "What I got was "
             << dataFile_ << endl << endl;
        exit(1);
    }
    test.close();
}

void TofFitter::GenerateNames(void) {
    for(unsigned int i = 0; i < peaks_.size(); i++) {
        stringstream nameMu, nameYld, nameSig,
            nameAlph, nameN, nameCb;
        if(i < 10) {
            nameMu << "mu0" << i;
            nameYld << "yield0" << i;
            nameSig << "sigma0" << i;
            nameAlph << "alpha0" << i;
            nameN << "n0" << i;
            nameCb << "cb0" << i;
        }else {
            nameMu << "mu" << i;
            nameYld << "yield" << i;
            nameSig << "sigma" << i;
            nameAlph << "alpha" << i;
            nameN << "n" << i;
            nameCb << "cb" << i;
        }
        components_.push_back(nameCb.str());
        yields_.push_back(nameYld.str());
        mus_.push_back(nameMu.str());
        alphas_.push_back(nameAlph.str());
        sigmas_.push_back(nameSig.str());
        ns_.push_back(nameN.str());
    }
}

void TofFitter::PerformFit(void) {
    ParamCalculator params;
    RooRealVar tof("tof","tof", 0.0, rng_.first, rng_.second);
    RooArgList cbs, ylds;

    RooConstVar e("e","",params.GetE().GetValue());
    RooConstVar d("d","",params.GetD().GetValue());
    RooConstVar c("c","",params.GetC().GetValue());
    RooConstVar b("b","",params.GetB().GetValue());
    RooConstVar a("a","",params.GetA().GetValue());
    RooConstVar ci("ci","",params.GetI().GetValue());
    RooConstVar h("h","",params.GetH().GetValue());
    RooConstVar g("g","",params.GetG().GetValue());
    RooConstVar f("f","",params.GetF().GetValue());
    RooConstVar j("j","",params.GetJ().GetValue());
    RooConstVar k("k","",params.GetK().GetValue());
    RooConstVar l("l","",params.GetL().GetValue());

   for(unsigned int i = 0; i < yields_.size(); i++) {
        stringstream fSig, fAlph, fN;
        RooRealVar *yield = new RooRealVar(yields_[i].c_str(), "", yStart_,
                                     yLow_, yHigh_);
        RooRealVar *mu = new RooRealVar(mus_[i].c_str(),"",peaks_[i],
                      peaks_[i]-wiggle_, peaks_[i]+wiggle_);

        fSig << "e*pow(" << mus_[i] << ",4)+ d*pow(" << mus_[i] <<",3) + "
             << "c*pow(" << mus_[i] << ",2) + b*" << mus_[i] << "+a";
        RooFormulaVar *sigma =
            new RooFormulaVar(sigmas_[i].c_str(), fSig.str().c_str(),
                    RooArgList(e,d,c,b,a,*mu));

        fAlph << "ci*pow(" << mus_[i] <<",3) + " << "h*pow(" << mus_[i]
              << ",2) + g*" << mus_[i] << "+f";
        RooFormulaVar *alpha =
            new RooFormulaVar(alphas_[i].c_str(), fAlph.str().c_str(),
                    RooArgList(ci,h,g,f,*mu));

        fN << "j/" << mus_[i] << " + k*" << mus_[i] << "+l";
        RooFormulaVar *n =
            new RooFormulaVar(ns_[i].c_str(), fN.str().c_str(),
                    RooArgList(j,k,l,*mu));

        RooCBShape *cb = new RooCBShape(components_[i].c_str(), "", tof, *mu,
                                        *sigma, *alpha, *n);
        cbs.add(*cb);
        ylds.add(*yield);
    }

    RooAddPdf model("model", "", cbs, ylds);
    RooDataSet *data = RooDataSet::read(dataFile_.c_str(), RooArgList(tof));
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(),
                                          Range(rng_.first, rng_.second));

    hasConvergence_ = fitResult->statusCodeHistory(0) == 0;
    hasHesseCalc_   = fitResult->statusCodeHistory(1) == 0;

    if(hasConvergence_ && hasHesseCalc_) {
        cout << "The Fit converged, and HESSE had no issues" << endl;

        RooArgList finals = fitResult->floatParsFinal();
        for(unsigned int i = 0; i < yields_.size()*2; i++) {
            RooRealVar tmp = *((RooRealVar*)finals.at(i));
            fitRes_.insert(make_pair(tmp.GetName(),
                                  make_pair(tmp.getValV(), tmp.getError())));
        }

        ofstream results(output_.c_str());
        results << "#Num Mu(ns) MuErr(ns) Yld YldErr Sigma Alpha N StatSig" << endl;
        for(unsigned int i = 0; i < yields_.size(); i++) {
            pair<double,double> mew=fitRes_.find(mus_[i])->second;
            pair<double,double> y = fitRes_.find(yields_[i])->second;

            results << i << " " << mew.first << " " << mew.second << " "
                    << y.first << " " << y.second << " "
                    << par_.CalcSigma(mew.first) << " "
                    << par_.CalcAlpha(mew.first) << " "
                    << par_.CalcN(mew.first) << " "
                    << y.first/y.second << endl;
        }
        results.close();
    }else {
        if(!hasConvergence_)
            cout << endl << endl << "Hey, bro!! The fit did not converge."
                 << endl;
        if(!hasHesseCalc_)
            cout << "Hesse FAILED to calculate things properly."
                 << endl << endl;
        exit(1);
    }

    RooPlot* frame = tof.frame();
    frame = tof.frame((rng_.second-rng_.first)*binning_);
    frame->SetTitle("");
    frame->SetAxisRange(rng_.first,rng_.second,"X");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);

    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));

    int lineColor = 36;
    for(unsigned int i = 0; i < components_.size(); i++, lineColor++) {
        model.plotOn(frame,Components(components_.at(i).c_str()),
                     LineColor(lineColor), LineStyle(2));
    }

    TCanvas* canvas = new TCanvas("canvas","",0,0,700,500);
    canvas->cd();
    frame->Draw();
    canvas->SaveAs(eps_.c_str());
    delete(canvas);
}

void TofFitter::PerformMcStudy(void) {
    RooRealVar tof("tof","tof", 0.0, rng_.first, rng_.second);

    RooConstVar sM("sM","", -0.000121210451962825);
    RooConstVar sN("sN","", 0.0416568757021418);
    RooConstVar sO("sO","", 0.550158923590531);

    RooConstVar aI("aI","", 0.0130289072593045);
    RooConstVar aH("aH","", -0.641803483244778);

    RooConstVar nJ("nJ","", 2.21591018795502e-06);
    RooConstVar nK("nK","", 0.00189178692442985);
    RooConstVar nL("nL","", 1.33190840921066);

    cout << endl << endl << "Starting to do the MC Study" << endl << endl;
    RooArgList newcb, newyld;
    for(unsigned int i = 0; i < yields_.size(); i++) {
        stringstream fAlph, fN, fSig;

        RooRealVar *yield = new RooRealVar(yields_[i].c_str(), "",
                                           fitRes_.find(yields_[i])->second.first,
                                           0.0, 1.e8);
        RooConstVar *mu = new RooConstVar(mus_[i].c_str(),"",
                                          fitRes_.find(mus_[i])->second.first);

        fSig << "sM*pow(" << mus_[i] << ",2)+sN*" << mus_[i] << "+sO";
        RooFormulaVar *sigma = new RooFormulaVar(sigmas_[i].c_str(),
                                                 fSig.str().c_str(),
                                                 RooArgList(sM,sN,sO,*mu));

        fAlph << "aI/pow(" << mus_[i] << ",2)+aH";
        RooFormulaVar *alpha = new RooFormulaVar(alphas_[i].c_str(),
                                                 fAlph.str().c_str(),
                                                 RooArgList(aI,aH,*mu));

        fN << "nJ*pow(" << mus_[i] << ",2)+nK*" << mus_[i] << "+nL";
        RooFormulaVar *n = new RooFormulaVar(ns_[i].c_str(),
                                             fN.str().c_str(),
                                             RooArgList(nJ,nK,nL,*mu));

        RooCBShape *cb = new RooCBShape(components_[i].c_str(), "", tof, *mu,
                                        *sigma, *alpha, *n);
        newcb.add(*cb);
        newyld.add(*yield);
    }

    RooAddPdf model1("model1", "", newcb, newyld);

    RooMCStudy mcstudy(model1,tof,Binned(kTRUE),Silence(), Extended(),
                       FitOptions(Save(kTRUE),Range(rng_.first,rng_.second),
                                  PrintEvalErrors(0)));
    mcstudy.generateAndFit(200);
    for(unsigned int i = 0; i < yields_.size(); i++) {
        RooPlot* frame1 = mcstudy.plotNLL(Bins(40));

        RooRealVar subject = *((RooRealVar*)newyld.at(i));
        RooPlot* frame2 = mcstudy.plotParam(subject,Bins(40));
        RooPlot* frame3 = mcstudy.plotError(subject,Bins(40));
        RooPlot* frame4 = mcstudy.plotPull(subject,Bins(40),FitGauss(kTRUE));

        TCanvas* cc = new TCanvas("cc","",900,900);
        cc->Divide(2,2);
        cc->cd(1); frame1->GetYaxis()->SetTitleOffset(1.4); frame1->Draw();
        cc->cd(2); frame2->GetYaxis()->SetTitleOffset(1.4); frame2->Draw();
        cc->cd(3); frame3->GetYaxis()->SetTitleOffset(1.4); frame3->Draw();
        cc->cd(4); frame4->GetYaxis()->SetTitleOffset(1.4); frame4->Draw();

        stringstream name;
        name << picDir_+"/mcStudy" << mod_ << "/"
             << yields_.at(i) <<".jpg";
        cc->SaveAs(name.str().c_str());
        delete(cc);
    }
}

void TofFitter::StartRollin(void) {
    CheckFileExistance();
    GenerateNames();
    PerformFit();
    PerformMcStudy();
}
