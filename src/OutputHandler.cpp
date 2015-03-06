/** \file OutputHandler.cpp
 *  \brief Handles the outputting of information for various formats/files
 *  \author S. V. Paulauskas
 *  \date 10 December 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>

#include "BGTCalculator.hpp"
#include "ErrorCalculator.hpp"
#include "NeutronDensity.hpp"
#include "OutputHandler.hpp"

using namespace std;

void OutputHandler::OutputBasics(vector<Neutron> &nvec, Decay &dky,
                  Experiment &exp, const string &file) {
    ofstream out(file.c_str());
    if(out.fail()) {
        cerr << endl << endl
             << "Woah! Could not open up the output file. Check this  "
             << file << endl << endl;
        exit(1);
    }

    Variable omega = exp.GetOmegaPerBar() * exp.GetNumBars();
    double totN  = 0., rawN = 0., intN = 0;
    out << setw(7) << "#Mu(ns) MuErr(ns) E(MeV) EErr(MeV) IntYld IntYldErr "
        << "BR BRerr B(GT) B(GT)err log(ft) log(ft)err" << endl;
    EffCalculator eff;
    for(auto it = nvec.begin();
        it != nvec.end(); it++) {
        intN += it->GetRawIntegratedYield().GetValue();
        totN += it->GetIntegratedYield().GetValue() /
            eff.GetBetaEff(it->GetEnergy(), dky).GetValue() /
            omega.GetValue();
        rawN += it->GetRawYield().GetValue();

        out << setprecision(5) << it->GetMu().OutputData() << " "
            << it->GetEnergy().OutputData() << " "
            << it->GetIntegratedYield().OutputData() << " "
            << it->GetBranchingRatio().OutputData() << " "
            << it->GetBgt().OutputData() << " "
            << it->GetLogft().OutputData() << " " << endl;

    }
    double pn = totN / dky.GetNumberDecays().GetValue();
    ErrorCalculator err;
    double pnErr = err.CalcPnErr(pn,nvec,dky);
    out << "#Pn = " << totN << " / " << dky.GetNumberDecays().GetValue()
        << " = " << pn << " +- " << pnErr << "  RawN = "
        << rawN << " " << "  RawIntN = " << intN << endl;
    out.close();
}

void OutputHandler::OutputDensity(vector<Neutron> &nvec, Decay &dky,
                                  Experiment &exp, const string &file) {
    NeutronDensity nden(nvec, dky.GetQBetaN().GetValue(),
                        exp.GetDensityRes().GetValue());
    auto ndenRes = *nden.GetDensity();
    auto ndenLow = *nden.GetDensityLow();
    auto ndenHigh = *nden.GetDensityHigh();

    BGTCalculator ndenBgt(ndenRes, dky, exp);
    BGTCalculator ndenBgtLow(ndenLow, dky, exp, "low");
    BGTCalculator ndenBgtHigh(ndenHigh, dky, exp, "high");

    auto bgtMap = *ndenBgt.GetBgtMap();
    auto bgtSden = *ndenBgt.GetSDensity();

    auto bgtMapLow = *ndenBgtLow.GetBgtMap();
    auto bgtMapLowSden = *ndenBgtLow.GetSDensity();

    auto bgtMapHigh = *ndenBgtHigh.GetBgtMap();
    auto bgtMapHighSden = *ndenBgtHigh.GetSDensity();

    ofstream outNDenBgt(file.c_str());
    outNDenBgt << "#Ex(MeV) BR BR(LOW) BR(HIGH) B(GT) B(GT)(LOW)"
               << " B(GT)(HIGH)" << endl;
    for(auto it = bgtMap.begin(); it != bgtMap.end(); it++) {
        auto itS = bgtSden.find(it->first);

        auto itLow = bgtMapLow.find(it->first);
        auto itLowS = bgtMapLowSden.find(it->first);

        auto itHigh = bgtMapHigh.find(it->first);
        auto itHighS = bgtMapHighSden.find(it->first);

        outNDenBgt.setf(ios::fixed);
        outNDenBgt << setprecision (8) << setw (10) << it->first << " "
                   << itS->second << " " <<  itLowS->second << " "
                   << itHighS->second << " " << it->second << " "
                   << itLow->second << " " << itHigh->second << endl;
    }
    outNDenBgt.close();
}

void OutputHandler::OutputTheory(vector<Neutron> &nvec, const string &file) {
    ofstream outTheory(file.c_str());
    for(auto it = nvec.begin(); it != nvec.end(); it++) {
        outTheory << it->GetExcitationEnergy().GetValue() << "  "
                  << it->GetBgt().GetValue() << " "
                  << it->GetEnergy().GetError();
        auto itNext = it;
        itNext++;
        if(itNext != nvec.end())
            outTheory << endl;
    }
    outTheory.close();
}
