/** \file Neutron.cpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include <PhysConstants.hpp>

#include "Neutron.hpp"
#include "EffCalculator.hpp"

using namespace std;

Neutron::Neutron(const double &mu, const double &yld) {
    EffCalculator eff("vandle");
    en_        = CalcEnergy(mu);
    enErr_     = 0.0;
    eff_       = eff.GetSimRollingEff(en_*1000.);
    intYld_    = 0.0;
    intYldErr_ = 0.0;
    mu_        = mu;
    muErr_     = 0.0;
    yld_       = yld;
    yldErr_    = 0.0;
}

Neutron::Neutron(const double &mu, const double &muErr, 
           const double &yld) {
    EffCalculator eff("vandle");
    en_        = CalcEnergy(mu); 
    enErr_     = CalcEnergyErr(mu,muErr,en_); 
    eff_       = eff.GetSimRollingEff(en_*1000.);
    intYld_    = 0.0;
    intYldErr_ = 0.0;
    mu_        = mu;
    muErr_     = muErr;
    yld_       = yld;
    yldErr_    = 0.0;
}

Neutron::Neutron(const double &mu, const double &muErr, 
           const double &yld, const double &yldErr) {
    EffCalculator eff("vandle");
    en_        = CalcEnergy(mu); 
    enErr_     = CalcEnergyErr(mu,muErr,en_); 
    eff_       = eff.GetSimRollingEff(en_*1000.);
    intYld_    = 0.0;
    intYldErr_ = 0.0;
    mu_        = mu;
    muErr_     = muErr;
    yld_       = yld;
    yldErr_    = yldErr;
}

void Neutron::CalcDensitySigma(void){
    double sig  = sig_*0.5;
    double high  = CalcEnergy(mu_-sig);
    double low = CalcEnergy(mu_+sig);
    denSig_ = high - low;
}

double Neutron::CalcEnergy(const double &mu) {
    PhysConstants consts;
    double c  = consts.GetConstant("c").GetValue()*(100/1e9); // cm / ns
    double mn = consts.GetConstant("neutronMass").GetValue()/c/c; // MeV
    return(0.5*mn*pow(50.5/mu,2.)); // MeV
}

double Neutron::CalcEnergyErr(const double &mu, const double &muErr, 
                              const double &en) {
    return( en * (2*muErr/mu) ); // MeV
}
