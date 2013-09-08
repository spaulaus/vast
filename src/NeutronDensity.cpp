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
    density_.resize(int(len/res)+1, 0.0);
    CalcDensity();
}

NeutronDensity::NeutronDensity(vector<Neutron> &neutrons, const double &res, 
                               const double &len, const double &gE)  : 
    gE_(gE), len_(len), res_(res) {
    neutrons_ = neutrons;
    density_.resize(int(len/res)+1, 0.0);
    EffCalculator effGe("ge");
    gEff_ = effGe.GetEff(gE);
    CalcDensity();
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
        sig.SetSigma((*it).GetBetaEnergyErr());
        sig.SetDelay((*it).GetEnergy());
        
        sig.GenerateSignal();
        for(double i = 0; i < len_; i+=res_)
            density_.at((unsigned int)(i/res_)) +=  sig.GetSignalValue(i)
                / eff.GetSimRollingEff(i*1000.) / gEff_;
    }

    for(unsigned int i = 0; i < density_.size(); i++)
        cout << i*res_ << " " << density_.at(i) << endl; 
}
