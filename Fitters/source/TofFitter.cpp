/** \file TofFitter.cpp
 * \brief A class to fit ToF spectra using RooFit
 * \author S. V. Paulauskas
 * \date 06 October 2013
 */
#include <fstream>
#include <iostream>
#include <sstream>

#include <RooAddPdf.h>
#include <RooCBShape.h>
#include <RooConstVar.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooMCStudy.h>
#include <RooPlot.h>
#include <RooRealVar.h>

#include <TAxis.h>
#include <TCanvas.h>

#include "CrystalBallParameters.hpp"
#include "TofFitter.hpp"

using namespace std;
using namespace RooFit;

///This constructor perfroms the fit of the ToF
TofFitter::TofFitter(const FitHandler &fit, const FileHandler &fls, const
CrystalBallParameters &pars) {
    cbPars_ = pars;
    fit_ = fit;
    fls_ = fls;

    binning_ = fit.GetBinning();
    peaks_ = fit.GetSnglPeaks();
    rng_ = fit.GetRange();

    dataFile_ = fls.GetInputName("gsTof");
    eps_ = fls.GetOutputName("picGs");
    picDir_ = fls.GetOutputName("picDir");
    output_ = fls.GetOutputName("gsFit");

    StartRollin();
}

///This method throws an error message if the file needed doesn't exist
void TofFitter::CheckFileExistance(void) {
    ifstream test(dataFile_.c_str());
    if (test.fail())
        throw Exception("We couldn't open the data file to read in the sexy "
                                "data!! What I got was " + dataFile_);
    test.close();
}

///This method generates the names of each of the fit parameters and
/// associated numbers corresponding to the fit peak number.
void TofFitter::GenerateNames(void) {
    for (unsigned int i = 0; i < peaks_.size(); i++) {
        stringstream nameMu, nameYld, nameSig,
                nameAlph, nameN, nameCb;
        if (i < 10) {
            nameMu << "mu0" << i;
            nameYld << "yield0" << i;
            nameSig << "sigma0" << i;
            nameAlph << "alpha0" << i;
            nameN << "n0" << i;
            nameCb << "cb0" << i;
        } else {
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

///This method performs a fit of the time of flight using built it ROOT fitting.
void TofFitter::PerformFit(void) {
    RooRealVar tof("tof", "tof", 0.0, rng_.first, rng_.second);
    RooArgList cbs, ylds;

    ///Could we make this a little cleaner like we do below? Make a loop that
    /// way we don't have to worry about setting all these by hand?
    vector<Variable> alphaCoefficients = cbPars_.GetAlphaCoefficients();
    RooConstVar a3("a3", "", alphaCoefficients[3].GetValue());
    RooConstVar a2("a2", "", alphaCoefficients[2].GetValue());
    RooConstVar a1("a1", "", alphaCoefficients[1].GetValue());
    RooConstVar a0("a0", "", alphaCoefficients[0].GetValue());

    vector<Variable> nCoefficients = cbPars_.GetNCoefficients();
    RooConstVar n2("n2", "", nCoefficients[2].GetValue());
    RooConstVar n1("n1", "", nCoefficients[1].GetValue());
    RooConstVar n0("n0", "", nCoefficients[0].GetValue());

    vector<Variable> sigmaCoefficients = cbPars_.GetSigmaCoefficients();
    RooConstVar s4("s4", "", sigmaCoefficients[4].GetValue());
    RooConstVar s3("s3", "", sigmaCoefficients[3].GetValue());
    RooConstVar s2("s2", "", sigmaCoefficients[2].GetValue());
    RooConstVar s1("s1", "", sigmaCoefficients[1].GetValue());
    RooConstVar s0("s0", "", sigmaCoefficients[0].GetValue());

    for (unsigned int i = 0; i < yields_.size(); i++) {
        RooRealVar *yield = new RooRealVar(yields_[i].c_str(), "", yStart_,
                                           yLow_, yHigh_);
        RooRealVar *mu = new RooRealVar(mus_[i].c_str(), "", peaks_[i],
                                        rng_.first, rng_.second);
        RooFormulaVar *alpha =
                new RooFormulaVar(alphas_[i].c_str(),
                                  cbPars_.GetAlphaFunction(mus_[i]).c_str(),
                                  RooArgList(a3, a2, a1, a0, *mu));
        RooFormulaVar *n =
                new RooFormulaVar(ns_[i].c_str(),
                                  cbPars_.GetNFunction(mus_[i]).c_str(),
                                  RooArgList(n2, n1, n0, *mu));
        RooFormulaVar *sigma =
                new RooFormulaVar(sigmas_[i].c_str(),
                                  cbPars_.GetSigmaFunction(mus_[i]).c_str(),
                                  RooArgList(s4, s3, s2, s1, s0, *mu));
        RooCBShape *cb = new RooCBShape(components_[i].c_str(), "", tof, *mu,
                                        *sigma, *alpha, *n);
        cbs.add(*cb);
        ylds.add(*yield);
    }

    RooAddPdf model("model", "", cbs, ylds);
    RooDataSet *data = RooDataSet::read(dataFile_.c_str(), RooArgList(tof));
    RooFitResult *fitResult = model.fitTo(*data, NumCPU(3), Save(),
                                          Offset(kTRUE),
                                          PrintLevel(fit_.GetPrintLevel()),
                                          Minimizer("Minuit2"),
                                          Range(rng_.first, rng_.second));

    hasConvergence_ = fitResult->statusCodeHistory(0) == 0;
    hasHesseCalc_ = fitResult->statusCodeHistory(1) == 0;

    if (hasConvergence_ && hasHesseCalc_) {
        cout << "The Fit converged, and HESSE had no issues" << endl;

        RooArgList finals = fitResult->floatParsFinal();
        for (unsigned int i = 0; i < yields_.size() * 2; i++) {
            RooRealVar tmp = *((RooRealVar *) finals.at(i));
            fitRes_.insert(make_pair(tmp.GetName(),
                                     make_pair(tmp.getValV(), tmp.getError())));
        }

        ofstream results(output_.c_str());
        results << "#Num Mu(ns) MuErr(ns) Yld YldErr Sigma Alpha N StatSig"
                << endl;
        for (unsigned int i = 0; i < yields_.size(); i++) {
            pair<double, double> mew = fitRes_.find(mus_[i])->second;
            pair<double, double> y = fitRes_.find(yields_[i])->second;

            results << i << " " << mew.first << " " << mew.second << " "
                    << y.first << " " << y.second << " "
                    << cbPars_.CalcSigma(mew.first) << " "
                    << cbPars_.CalcAlpha(mew.first) << " "
                    << cbPars_.CalcN(mew.first) << " "
                    << y.first / y.second << endl;
        }
        results.close();
    } else {
        if (!hasConvergence_)
            cout << endl << endl << "Hey, bro!! The fit did not converge."
                 << endl;
        if (!hasHesseCalc_)
            cout << "Hesse FAILED to calculate things properly."
                 << endl << endl;
        exit(1);
    }

    RooPlot frame("frame", "", tof, rng_.first, rng_.second,
                  (rng_.second - rng_.first) * binning_);
    frame.SetTitle("");
    frame.SetAxisRange(rng_.first, rng_.second, "X");
    frame.SetXTitle("Time-of-Flight (ns)");
    stringstream ylabel;
    ylabel << "Events / " << (int) (1. / binning_) << "ns" << endl;
    frame.SetYTitle(ylabel.str().c_str());
    frame.GetYaxis()->SetTitleOffset(1.2);

    data->plotOn(&frame, Name("data"));
    model.plotOn(&frame, Name("model"));

    TCanvas *canvas = new TCanvas("canvas", "", 0, 0, 700, 500);
    canvas->cd();
    frame.Draw();
    canvas->SaveAs(eps_.c_str());
    delete (canvas);
}

///This method performs a Monte Carlo style study of the ToF fit.
///@TODO Add more details of how this is done.
void TofFitter::PerformMcStudy(void) {
    RooRealVar tof("tof", "tof", 0.0, rng_.first, rng_.second);

    ///Could we make this a little cleaner like we do below? Make a loop that
    /// way we don't have to worry about setting all these by hand?
    vector<Variable> alphaCoefficients = cbPars_
            .GetAlphaCoefficients();
    RooConstVar a3("a3", "", alphaCoefficients[3].GetValue());
    RooConstVar a2("a2", "", alphaCoefficients[2].GetValue());
    RooConstVar a1("a1", "", alphaCoefficients[1].GetValue());
    RooConstVar a0("a0", "", alphaCoefficients[0].GetValue());

    vector<Variable> nCoefficients = cbPars_.GetNCoefficients();
    RooConstVar n2("n2", "", nCoefficients[2].GetValue());
    RooConstVar n1("n1", "", nCoefficients[1].GetValue());
    RooConstVar n0("n0", "", nCoefficients[0].GetValue());

    vector<Variable> sigmaCoefficients = cbPars_.GetSigmaCoefficients();
    RooConstVar s4("s4", "", sigmaCoefficients[4].GetValue());
    RooConstVar s3("s3", "", sigmaCoefficients[3].GetValue());
    RooConstVar s2("s2", "", sigmaCoefficients[2].GetValue());
    RooConstVar s1("s1", "", sigmaCoefficients[1].GetValue());
    RooConstVar s0("s0", "", sigmaCoefficients[0].GetValue());


    cout << endl << endl << "Starting to do the MC Study" << endl << endl;
    RooArgList newcb, newyld;
    for (unsigned int i = 0; i < yields_.size(); i++) {
        RooRealVar *yield = new RooRealVar(yields_[i].c_str(), "", yStart_,
                                           yLow_, yHigh_);
        RooRealVar *mu = new RooRealVar(mus_[i].c_str(), "", peaks_[i],
                                        rng_.first, rng_.second);
        RooFormulaVar *alpha =
                new RooFormulaVar(alphas_[i].c_str(),
                                  cbPars_.GetAlphaFunction(mus_[i]).c_str(),
                                  RooArgList(a3, a2, a1, a0, *mu));
        RooFormulaVar *n =
                new RooFormulaVar(ns_[i].c_str(),
                                  cbPars_.GetNFunction(mus_[i]).c_str(),
                                  RooArgList(n2, n1, n0, *mu));
        RooFormulaVar *sigma =
                new RooFormulaVar(sigmas_[i].c_str(),
                                  cbPars_.GetSigmaFunction(mus_[i]).c_str(),
                                  RooArgList(s4, s3, s2, s1, s0, *mu));
        RooCBShape *cb = new RooCBShape(components_[i].c_str(), "", tof, *mu,
                                        *sigma, *alpha, *n);
        newcb.add(*cb);
        newyld.add(*yield);
    }

    RooAddPdf model1("model1", "", newcb, newyld);

    RooMCStudy mcstudy(model1, tof, Binned(kTRUE), Silence(), Extended(),
                       FitOptions(Save(kTRUE), Range(rng_.first, rng_.second),
                                  PrintEvalErrors(0)));
    mcstudy.generateAndFit(200);
    for (unsigned int i = 0; i < yields_.size(); i++) {
        RooPlot *frame1 = mcstudy.plotNLL(Bins(40));

        RooRealVar subject = *((RooRealVar *) newyld.at(i));
        RooPlot *frame2 = mcstudy.plotParam(subject, Bins(40));
        RooPlot *frame3 = mcstudy.plotError(subject, Bins(40));
        RooPlot *frame4 = mcstudy.plotPull(subject, Bins(40), FitGauss(kTRUE));

        TCanvas *cc = new TCanvas("cc", "", 900, 900);
        cc->Divide(2, 2);
        cc->cd(1);
        frame1->GetYaxis()->SetTitleOffset(1.4);
        frame1->Draw();
        cc->cd(2);
        frame2->GetYaxis()->SetTitleOffset(1.4);
        frame2->Draw();
        cc->cd(3);
        frame3->GetYaxis()->SetTitleOffset(1.4);
        frame3->Draw();
        cc->cd(4);
        frame4->GetYaxis()->SetTitleOffset(1.4);
        frame4->Draw();

        stringstream name;
        name << picDir_ + "/mcStudy" << mod_ << "/"
             << yields_.at(i) << ".jpg";
        cc->SaveAs(name.str().c_str());
        delete (cc);
    }
}

///This method calls the others to make the fitter run
void TofFitter::StartRollin(void) {
    CheckFileExistance();
    GenerateNames();
    PerformFit();
    PerformMcStudy();
}
