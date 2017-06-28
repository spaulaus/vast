/** \file Neutron.cpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include "ErrorCalculator.hpp"
#include "HelperEnumerations.hpp"
#include "PhysicalConstants.hpp"

using namespace std;
using namespace PhysicalConstants;

///This constructor provides the neutron efficiency, beta resolution and
/// neutron energy with no error values
Neutron::Neutron(const double &mu, const double &yld) {
    mu_ = Variable(mu, 0.0, "ns");
    yld_ = Variable(yld, 0.0, "counts");

    CalcBetaResolution();
    CalcEnergy();
    eff_ = eff.GetEff(en_, EfficiencyEnums::EffTypes::svpBan4);
}

///This constructor provides the neutron efficiency, beta resolution and
/// neutron energy with error only on the mean
Neutron::Neutron(const double &mu, const double &muErr,
                 const double &yld) {
    mu_ = Variable(mu, muErr, "ns");
    yld_ = Variable(yld, 0.0, "counts");

    CalcBetaResolution();
    CalcEnergy();
    eff_ = eff.GetEff(en_, EfficiencyEnums::EffTypes::svpBan4);
}

///This constructor provides the neutron efficiency, beta resolution and
/// neutron energy with error on the mean and the yield
Neutron::Neutron(const double &mu, const double &muErr,
                 const double &yld, const double &yldErr) {
    mu_ = Variable(mu, muErr, "ns");
    yld_ = Variable(yld, yldErr, "counts");

    CalcBetaResolution();
    CalcEnergy();
    eff_ = eff.GetEff(en_, EfficiencyEnums::EffTypes::svpBan4);
}

///This method calculates the neutron energy from the time of flight
///@TODO This has a hard coded distance in it. We need to update this using the experiment node.
void Neutron::CalcEnergy(void) {
    double c = General::SpeedOfLight.GetValue() * (100 / 1e9);
    double mn = Masses::Neutron.GetValue() / c / c;
    double energy = 0.5 * mn * pow(50.5 / mu_.GetValue(), 2.);

    en_ = Variable(energy, 0.0, "MeV");

    ErrorCalculator errcalc;
    double err = errcalc.CalcEnergyErr(*this);
    en_ = Variable(energy, err, "MeV");
}

///This method calculates the detection efficiency of the neutron at its energy
void Neutron::CalcEnEff(void) {
    eff_ = eff.GetEff(en_, EfficiencyEnums::EffTypes::svpBan4);
}

///This method adjusts the input variable to account for intrinsic neutron efficiency
///@TODO rename var to something more descriptive
Variable Neutron::AdjEff(const Variable &var) {
    return (var / eff_);
}

///This method calculates the beta resolution for the neutron peak
void Neutron::CalcBetaResolution(void) {
    double val = 0.;
    double fwhmToSigma = 2 * sqrt(2  *log(2));
  
    ///@TODO Why does a mu=42.5 value matter?
    if(mu_.GetValue() <= 42.5)
        val = (0.071824559 * mu_.GetValue() + 1.5544112228) / fwhmToSigma;
    else
        val = (0.0168145157 * mu_.GetValue() + 3.7803929763) / fwhmToSigma;
    betaRes_ = Variable(val, 0.0, "ns");
}
