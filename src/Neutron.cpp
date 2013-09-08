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
    alph_      = CalcAlpha(mu);
    betaEnErr_ = 0.0;
    en_        = CalcEnergy(mu);
    enErr_     = 0.0;
    eff_       = eff.GetSimRollingEff(en_*1000.);
    intYld_    = 0.0;
    intYldErr_ = 0.0;
    mu_        = mu;
    muErr_     = 0.0;
    n_         = CalcN(mu);
    sig_       = CalcSigma(mu);
    yld_       = yld;
    yldErr_    = 0.0;
}

Neutron::Neutron(const double &mu, const double &muErr, 
           const double &yld) {
    EffCalculator eff("vandle");
    alph_      = CalcAlpha(mu);
    en_        = CalcEnergy(mu); 
    enErr_     = CalcEnergyErr(mu,muErr,en_); 
    betaEnErr_ = CalcEnergyErr(mu,CalcSigma(mu),en_);
    eff_       = eff.GetSimRollingEff(en_*1000.);
    intYld_    = 0.0;
    intYldErr_ = 0.0;
    mu_        = mu;
    muErr_     = muErr;
    n_         = CalcN(mu);
    sig_       = CalcSigma(mu);
    yld_       = yld;
    yldErr_    = 0.0;
}

Neutron::Neutron(const double &mu, const double &muErr, 
           const double &yld, const double &yldErr) {
    EffCalculator eff("vandle");
    alph_      = CalcAlpha(mu);
    en_        = CalcEnergy(mu); 
    enErr_     = CalcEnergyErr(mu,muErr,en_); 
    betaEnErr_ = CalcEnergyErr(mu,CalcSigma(mu),en_);
    eff_       = eff.GetSimRollingEff(en_*1000.);
    intYld_    = 0.0;
    intYldErr_ = 0.0;
    mu_        = mu;
    muErr_     = muErr;
    n_         = CalcN(mu);
    sig_       = CalcSigma(mu);
    yld_       = yld;
    yldErr_    = yldErr;
}

double Neutron::CalcAlpha(const double &mu) {
    double aI = 2.97314684100351e-7;
    double aH = -0.000105412912022653;
    double aG = 0.0135441451470589 ;
    double aF = -1.18042124700263;
    return(aI*pow(mu,3)+aH*pow(mu,2)+aG*mu+aF);
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

double Neutron::CalcN(const double &mu) {
    double nJ = -4.38376875421603;
    double nK = -0.000234978549811854;
    double nL = 1.32334100981145;
    return(nJ/mu+nK*mu+nL);
}

double Neutron::CalcSigma(const double &mu) {
    double sA = 2.55056292412568;
    double sB = -0.0192702755935177;
    double sC = 0.000620834380435262;
    double sD = -4.02706921636101e-6;
    double sE = 1.01415462736843e-8;
    return(sE*pow(mu,4)+sD*pow(mu,3)+sC*pow(mu,2)+sB*mu+sA);
}



