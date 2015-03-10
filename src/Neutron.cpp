/** \file Neutron.cpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include <PhysConstants.hpp>

#include "ErrorCalculator.hpp"
#include "Neutron.hpp"

using namespace std;

Neutron::Neutron(const double &mu, const double &yld) {
    mu_        = Variable(mu, 0.0, "ns");
    yld_       = Variable(yld, 0.0, "counts");

    CalcBetaResolution();
    CalcEnergy();
    eff_       = eff.GetEff(en_, EffCalculator::EffTypes::svpBan4);
}

Neutron::Neutron(const double &mu, const double &muErr,
           const double &yld) {
    mu_        = Variable(mu, muErr, "ns");
    yld_       = Variable(yld, 0.0, "counts");

    CalcBetaResolution();
    CalcEnergy();
    eff_       = eff.GetEff(en_, EffCalculator::EffTypes::svpBan4);
}

Neutron::Neutron(const double &mu, const double &muErr,
           const double &yld, const double &yldErr) {
    mu_        = Variable(mu, muErr, "ns");
    yld_       = Variable(yld, yldErr, "counts");

    CalcBetaResolution();
    CalcEnergy();
    eff_       = eff.GetEff(en_, EffCalculator::EffTypes::svpBan4);
}

void Neutron::CalcEnergy(void) {
    PhysConstants consts;
    double c  = consts.GetConstant("c").GetValue()*(100/1e9);
    double mn = consts.GetConstant("neutronMass").GetValue()/c/c;
    double energy = 0.5*mn*pow(50.5/mu_.GetValue(),2.);

    en_ = Variable(energy, 0.0, "MeV");

    ErrorCalculator errcalc;
    double err = errcalc.CalcEnergyErr(*this);
    en_ = Variable(energy, err, "MeV");
}

void Neutron::CalcEnEff(void) {
    eff_  = eff.GetEff(en_, EffCalculator::EffTypes::svpBan4);
}

Variable Neutron::AdjEff(const Variable &var) {
    return(var/eff_);
}

void Neutron::CalcBetaResolution(void) {
    double val = 0.;
    double fwhmToSigma = 2*sqrt(2*log(2));
    if(mu_.GetValue() <= 42.5)
        val = (0.071824559*mu_.GetValue()+1.5544112228)/fwhmToSigma;
    else
        val = (0.0168145157*mu_.GetValue()+3.7803929763)/fwhmToSigma;
    betaRes_ = Variable(val,0.0,"ns");
}
