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
    yld_       = Variable(yld,0.0,"counts");
    en_        = Variable(CalcEnergy(mu), 0.0, "MeV");
    eff_       = eff.GetEff(en_, EffCalculator::EffTypes::mmfBan);
}

Neutron::Neutron(const double &mu, const double &muErr,
           const double &yld) {
    mu_        = Variable(mu, muErr, "ns");
    yld_       = Variable(yld,0.0,"counts");
    en_        = Variable(CalcEnergy(mu), 0.0, "MeV");
    eff_       = eff.GetEff(en_, EffCalculator::EffTypes::mmfBan);
}

Neutron::Neutron(const double &mu, const double &muErr,
           const double &yld, const double &yldErr) {
    mu_        = Variable(mu, muErr, "ns");
    yld_       = Variable(yld,yldErr,"counts");
    en_        = Variable(CalcEnergy(mu), 0.0, "MeV");
    eff_       = eff.GetEff(en_, EffCalculator::EffTypes::mmfBan);
}

double Neutron::CalcEnergy(const double &mu) {
    PhysConstants consts;
    double c  = consts.GetConstant("c").GetValue()*(100/1e9); // cm / ns
    double mn = consts.GetConstant("neutronMass").GetValue()/c/c; // MeV
    return(0.5*mn*pow(50.5/mu,2.)); // MeV
}

void Neutron::CalcEnEff(void) {
    en_   = Variable(CalcEnergy(mu_.GetValue()), 0.0, "MeV");
    eff_  = eff.GetEff(en_, EffCalculator::EffTypes::mmfBan);
}

void Neutron::CalcEnergyErr(void) {
    ErrorCalculator err;
    en_.SetError(err.CalcEnergyErr(sig_,mu_));
}

Variable Neutron::AdjEff(const Variable &var) {
    return(Variable(var.GetValue()/eff_.GetValue(),
                    var.GetError()/eff_.GetValue(),
                    var.GetUnits()));
}

