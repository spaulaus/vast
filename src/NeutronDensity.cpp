/** \file NeutronDensity.cpp
 *  \brief A class that contains information about the neutron density
 *  \author S. V. Paulauskas
 *  \date 07 September 2013
 */
#include <iostream>

#include <cmath>

#include <SignalGenerator.hpp>

#include "EffCalculator.hpp"
#include "NeutronDensity.hpp"

using namespace std;

NeutronDensity::NeutronDensity(std::vector<Neutron> &neutrons, const double &len,
                               const double &res, const Variable &ge) {
    len_     = len;
    res_     = res;
    neutrons_ = neutrons;

    if(ge.GetValue() == 0)
        CalcDensity(ge, Variable(1.0,0.0,""));
    else {
        EffCalculator eff;
        CalcDensity(ge, eff.GetEff(ge, EffCalculator::EffTypes::ge));
    }
}

void NeutronDensity::CalcDensity(const Variable &ge, const Variable &geEff) {
    SignalGenerator sig, sigLow, sigHigh;
    sig.SetSignalType("gaussian");
    sigLow.SetSignalType("gaussian");
    sigHigh.SetSignalType("gaussian");

    for(vector<Neutron>::iterator it = neutrons_.begin();
        it != neutrons_.end(); it++) {
        double br = it->GetBranchingRatio().GetValue();
        double brErr = it->GetBranchingRatio().GetError();

        sig.SetDelay(it->GetEnergy().GetValue()+ge.GetValue());
        sig.SetSigma(it->GetEnergy().GetError());

        vector<double> brList = {br-brErr,br,br+brErr};
        for(auto const &i : brList) {
            sig.SetAmplitude(i*res_);

            map<double,double> *tempMap;
            if(i == br-brErr)
                tempMap = &denLow_;
            else if (i == br)
                tempMap = &denMean_;
            else if (i == br+brErr)
                tempMap = &denHigh_;

            for(double j = 0; j < len_; j+=res_) {
                double val = sig.GetSignalValue(j) / geEff.GetValue();
                auto temp = tempMap->find(j);
                if(temp != tempMap->end())
                    temp->second += val;
                else
                    tempMap->insert(make_pair(j,val));
            }
        }
    }
}
