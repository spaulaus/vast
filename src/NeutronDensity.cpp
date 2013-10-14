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
                               const double &res, const double &ge) {
    len_     = len;
    res_     = res;
    neutrons_ = neutrons;
    
    if(ge == 0)
        CalcDensity(0.0, 1.0);
    else {
        EffCalculator effGe("ge");
        double geEff = effGe.GetEff(ge*1000.); //needs gamma energy in keV
        CalcDensity(ge, geEff);
    }
}

void NeutronDensity::CalcDensity(const double &ge, 
                                 const double &geEff) {
    SignalGenerator sig;
    sig.SetSignalType("gaussian");

    for(vector<Neutron>::iterator it = neutrons_.begin(); 
        it != neutrons_.end(); it++) {
        
        sig.SetAmplitude(it->GetBranchingRatio());
        sig.SetSigma(it->GetDensitySigma());
        sig.SetDelay(it->GetEnergy()+ge);
        for(double i = 0; i < len_; i+=res_) {
            double val = sig.GetSignalValue(i) / geEff;
            map<double,double>::iterator en = density_.find(i);
            if(en != density_.end())
                en->second += val;
            else
                density_.insert(make_pair(i,val));
        }
    }
}
