/** \file NeutronDensity.cpp
 *  \brief A class that contains information about the neutron density
 *  \author S. V. Paulauskas
 *  \date 07 September 2013
 */
#include <iostream> 

#include <SignalGenerator.hpp>

#include "EffCalculator.hpp"
#include "NeutronDensity.hpp"

using namespace std;

NeutronDensity::NeutronDensity(vector<Neutron> &neutrons, const double &res,
                               const double &len) : 
    gE_(0.0), gEff_(1.0), len_(len), res_(res) {
    neutrons_ = neutrons;
    CalcDensity();
}

NeutronDensity::NeutronDensity(vector<Neutron> &neutrons, const double &res, 
                               const double &len, const double &gE)  : 
    gE_(gE), len_(len), res_(res) {
    neutrons_ = neutrons;
    EffCalculator effGe("ge");
    gEff_ = effGe.GetEff(gE*1000.); //needs gamma energy in keV
    CalcDensity();
    CalcGshiftedDensity();
}

void NeutronDensity::CalcDensity(void) {
    SignalGenerator sig;
    EffCalculator eff("vandle");
    sig.SetSignalType("gaussian");
    sig.SetSignalResolution(res_);
    sig.SetSignalLength(len_);
        
    for(vector<Neutron>::iterator it = neutrons_.begin(); 
        it != neutrons_.end(); it++) {
        sig.SetAmplitude((*it).GetIntegratedYield());
        sig.SetSigma((*it).GetDensitySigma());
        sig.SetDelay((*it).GetEnergy());
        sig.GenerateSignal();
        
        for(double i = 0; i < len_; i+=res_) {
            double val = sig.GetSignalValue(i)
                / eff.GetSimRollingEff(i*1000.) / gEff_;
            map<double,double>::iterator en = density_.find(i);
            if(en == density_.end())
                density_.insert(make_pair(i,val));
            else
                (*en).second += val;
        }
    }
}

void NeutronDensity::CalcGshiftedDensity(void) {
    SignalGenerator sig;
    EffCalculator eff("vandle");
    sig.SetSignalType("gaussian");
    sig.SetSignalResolution(res_);
    sig.SetSignalLength(len_);
        
    for(vector<Neutron>::iterator it = neutrons_.begin(); 
        it != neutrons_.end(); it++) {
        sig.SetAmplitude((*it).GetIntegratedYield());
        sig.SetSigma((*it).GetDensitySigma());
        sig.SetDelay((*it).GetEnergy()+gE_);
        sig.GenerateSignal();
        
        for(double i = 0; i < len_; i+=res_) {
            double val = sig.GetSignalValue(i)
                / eff.GetSimRollingEff(i*1000.) / gEff_;
            map<double,double>::iterator en = gshiftDensity_.find(i);
            if(en == gshiftDensity_.end())
                gshiftDensity_.insert(make_pair(i,val));
            else
                (*en).second += val;
        }
    }
}

