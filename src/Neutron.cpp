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
    denSig_    = CalcDensitySigma(mu);
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
    denSig_    = CalcDensitySigma(mu);
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
    denSig_    = CalcDensitySigma(mu);
    en_        = CalcEnergy(mu); 
    enErr_     = CalcEnergyErr(mu,muErr,en_); 
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

// double Neutron::CalcAlpha(const double &mu) {
//     double aI = 2.97314684100351e-7;
//     double aH = -0.000105412912022653;
//     double aG = 0.0135441451470589 ;
//     double aF = -1.18042124700263;
//     return(aI*pow(mu,3)+aH*pow(mu,2)+aG*mu+aF);
// }

double Neutron::CalcDensitySigma(const double &mu){
    double sig  = CalcSigma(mu)*0.25;
    double low  = CalcEnergy(mu-sig);
    double high = CalcEnergy(mu+sig);
    return(low-high);
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

// double Neutron::CalcN(const double &mu) {
//     double nJ = -4.38376875421603;
//     double nK = -0.000234978549811854;
//     double nL = 1.32334100981145;
//     return(nJ/mu+nK*mu+nL);
// }

// double Neutron::CalcSigma(const double &mu) {
//     double sA = 2.55056292412568;
//     double sB = -0.0192702755935177;
//     double sC = 0.000620834380435262;
//     double sD = -4.02706921636101e-6;
//     double sE = 1.01415462736843e-8;
//     return(sE*pow(mu,4)+sD*pow(mu,3)+sC*pow(mu,2)+sB*mu+sA);
// }

double Neutron::CalcSigma(const double &mu){
    double sM = -0.000121210451962825;
    double sN = 0.0416568757021418;
    double sO = 0.550158923590531;
    return(sM*mu*mu+sN*mu+sO);
}

double Neutron::CalcAlpha(const double &mu) {
//Parameterization Parameters for Alpha 
    double aI = 0.0130289072593045;
    double aH = 0.641803483244778;
    return(aI/mu/mu+aH);
}

double Neutron::CalcN(const double &mu) {
//Parameterization Parameters for N 
    double nJ = 2.21591018795502e-06;
    double nK = 0.00189178692442985;
    double nL = 1.33190840921066;
    return(nJ*mu*mu+nK*mu+nL);
}

