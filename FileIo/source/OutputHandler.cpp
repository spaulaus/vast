/** \file OutputHandler.cpp
 *  \brief Handles the outputting of information for various formats/files
 *  \author S. V. Paulauskas
 *  \date 10 December 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>

#include <TFile.h>
#include <TGraphAsymmErrors.h>

#include "BGTCalculator.hpp"
#include "OutputHandler.hpp"

using namespace std;

///This method checks if val is nan or infinity
bool OutputHandler::NotInfOrNan(const double &val) {
    return (!std::isnan(val) && !std::isinf(val));
}

///This method fills the 1D ROOT histogram
void OutputHandler::FillHistogram(TH1D &hist,
                                  const std::map<double, double> &data) {
    for (const auto &it : data)
        hist.Fill(it.first, it.second);
}

///This method ouputs basic information
void OutputHandler::OutputBasics(vector<Neutron> &nvec, Decay &dky,
                                 Experiment &exp, const string &file) {
    ofstream out(file.c_str());
    if (out.fail()) {
        cerr << endl << endl
             << "Woah! Could not open up the output file. Check this  "
             << file << endl << endl;
        exit(1);
    }

    Variable omega = exp.GetOmegaPerBar() * exp.GetNumBars();
    double totN = 0., rawN = 0., intN = 0;
    out << setw(7) << "#Mu(ns) MuErr(ns) E(MeV) EErr(MeV) IntYld IntYldErr "
        << "BR BRerr B(GT) B(GT)err log(ft) log(ft)err" << endl;
    EffCalculator eff;
    for (auto it = nvec.begin();
         it != nvec.end(); it++) {
        intN += it->GetRawIntegratedYield().GetValue();
        totN += it->GetIntegratedYield().GetValue() /
                eff.GetBetaEff(it->GetEnergy(), dky).GetValue() /
                omega.GetValue();
        rawN += it->GetRawYield().GetValue();

        ///@TODO Check this works.  Clion says "binary type operator << can't
        /// be applied to expressions of types wostream and string"
        out << setprecision(5) << it->GetMu().OutputData() << " "
            << it->GetEnergy().OutputData() << " "
            << it->GetIntegratedYield().OutputData() << " "
            << it->GetBranchingRatio().OutputData() << " "
            << it->GetBgt().OutputData() << " "
            << it->GetLogft().OutputData() << " " << endl;

    }
    double pn = totN / dky.GetNumberDecays().GetValue();
    ErrorCalculator err;
    double pnErr = err.CalcPnErr(pn, nvec, dky);
    out << "#Pn = " << totN << " / " << dky.GetNumberDecays().GetValue()
        << " = " << pn << " +- " << pnErr << "  RawN = "
        << rawN << " " << "  RawIntN = " << intN << endl;
    out.close();
}

///This method outputs information about the neutron density
void OutputHandler::OutputDensity(const NeutronDensity &nden, const Decay &dky,
                                  const Experiment &exp, const string &file) {
    BGTCalculator ndenBgt(*nden.GetDensity(), dky, exp);
    BGTCalculator ndenBgtLow(*nden.GetDensityLow(), dky, exp, "low");
    BGTCalculator ndenBgtHigh(*nden.GetDensityHigh(), dky, exp, "high");

    resolution_ = exp.GetDensityRes().GetValue();
    int nbins = maxEnergy_ / resolution_;

    TFile f(file.c_str(), "RECREATE");

    TH1D density("density", "", nbins, minEnergy_, maxEnergy_);
    SetHistOptions(density, "den");
    FillHistogram(density, *ndenBgt.GetSDensity());

    TH1D densityErrLow("densityLow", "", nbins, minEnergy_, maxEnergy_);
    SetHistOptions(densityErrLow, "den");
    FillHistogram(densityErrLow, *ndenBgtLow.GetSDensity());

    TH1D densityErrHigh("densityHigh", "", nbins, minEnergy_, maxEnergy_);
    SetHistOptions(densityErrHigh, "den");
    FillHistogram(densityErrHigh, *ndenBgtHigh.GetSDensity());

    TH1D bgt("bgt", "", nbins, minEnergy_, maxEnergy_);
    SetHistOptions(bgt, "bgt");
    FillHistogram(bgt, *ndenBgt.GetBgtMap());

    TH1D bgtErrLow("bgtLow", "", nbins, minEnergy_, maxEnergy_);
    SetHistOptions(bgtErrLow, "bgt");
    FillHistogram(bgtErrLow, *ndenBgtLow.GetBgtMap());

    TH1D bgtErrHigh("bgtHigh", "", nbins, minEnergy_, maxEnergy_);
    SetHistOptions(bgtErrHigh, "bgt");
    FillHistogram(bgtErrHigh, *ndenBgtHigh.GetBgtMap());

    f.Write();
    f.Close();
}
///This method outputs in the format needed for the CGM calculations
///@TODO Describe what this CGM calculation is.
void OutputHandler::OutputTheory(vector<Neutron> &nvec, const string &file) {
    ofstream outTheory(file.c_str());
    for (auto it = nvec.begin(); it != nvec.end(); it++) {
        outTheory << it->GetExcitationEnergy().GetValue() << "  "
                  << it->GetBgt().GetValue() << " "
                  << it->GetEnergy().GetError();
        auto itNext = it;
        itNext++;
        if (itNext != nvec.end())
            outTheory << endl;
    }
    outTheory.close();
}

///This method sets various options for the ROOT histogram
void OutputHandler::SetHistOptions(TH1D &hist, const std::string &type) {
    stringstream label;
    if (type == "bgt")
        label << "B(GT) / ";
    if (type == "den")
        label << "Intensity / ";
    label << "(" << resolution_ << " MeV)";

    hist.SetYTitle(label.str().c_str());
    hist.SetTitleOffset(1.5, "Y");
    hist.SetXTitle("Excitation Energy (MeV)");
    hist.SetLineColor(2002);
    hist.SetOption("HIST");
}
