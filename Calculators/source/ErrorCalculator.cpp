/** \file ErrorCalculator.cpp
 *  \brief A class that calculates the errors on variables.
 *  \author S. V. Paulauskas
 *  \date 29 October 2013
 */
#include <chrono>
#include <iostream>
#include <random>

#include "ErrorCalculator.hpp"
#include "PhysicalConstants.hpp"

using namespace std;
using namespace PhysicalConstants;


///This method calculates the error on the gamma efficiency using MC method
double ErrorCalculator::CalcEffErr(const map<string,Variable> &vars, const Variable &energy) {
    static const unsigned int numSamples = 1e5;  //!< The number of MC tries for Eff calc

    long seed1 = chrono::system_clock::now().time_since_epoch().count();

    mt19937_64 generator(seed1);
    map<string, normal_distribution<double> > randDists;
    vector<double> mcEffs;

    for(const auto &it : vars) {
        normal_distribution<double> dist(it.second.GetValue(), it.second.GetError());
        randDists.insert(make_pair(it.first, dist));
    }
    normal_distribution<double> eDist(energy.GetValue(), energy.GetError());

    for(unsigned int i = 0; i < numSamples; i++) {
        double a  = randDists["a"](generator);
        double b  = randDists["b"](generator);
        double c  = vars.at("c").GetValue();
        double d  = randDists["d"](generator);
        double e  = randDists["e"](generator);
        double f  = vars.at("f").GetValue();
        double g  = vars.at("g").GetValue();
        double e1 = vars.at("e1").GetValue();
        double e2 = vars.at("e2").GetValue();
        double energy = eDist(generator);

        double x = log(energy/e1);
        double y = log(energy/e2);

        double eff = exp(pow(pow(a+b*x+c*x*x,-g) +
                             pow(d+e*y+f*y*y,-g), -1/g))/100.;
        if(std::isnan(eff)) {
            i--;
            continue;
        }
        mcEffs.push_back(eff);
    }

    auto mean = CalcMean(mcEffs);
    auto var  = CalcVariance(mcEffs, mean);
    return(sqrt(var));
}

///This method calculates the error of the energy of the neutron peak
double ErrorCalculator::CalcEnergyErr(Neutron &neutron) {
    double tofPart = pow(2 * neutron.GetBetaResolution().GetValue() / neutron.GetMu().GetValue(), 2);
    double physicalPart = pow(2 * 3 / 50.5, 2);
    double sqrtPart = sqrt(tofPart + physicalPart);
    double err = sqrtPart * neutron.GetEnergy().GetValue();
    return(err);
}

///This method calculates the log(ft) error
double ErrorCalculator::CalcLogftErr(const Variable &br, const Variable &halfLife) {
    double brPart = br.GetError() / br.GetValue() / log(10);
    double hlPart = halfLife.GetError() / halfLife.GetValue() / log(10);
    return(sqrt(pow(brPart,2)+pow(hlPart,2)));
}

///This method calculates the error on the number of decays
double ErrorCalculator::CalcNumDkyErr(const double &numDky, const Variable &rawGammaCounts, const Variable &gammaEff,
                                      const Variable &gammaBr){
    double areaPart = rawGammaCounts.GetError()/ rawGammaCounts.GetValue();
    double effPart  = gammaEff.GetError() / gammaEff.GetValue();
    double brPart  = gammaBr.GetError() / gammaBr.GetValue();
    return(numDky*sqrt(pow(areaPart,2)+pow(effPart,2)+pow(brPart,2)));
}

///This method calculates the error of the neutron branching ratio
double ErrorCalculator::CalcPnErr(const double &pn, vector<Neutron> &neutrons, const Decay &dky) {
    double yldPart;
    for(auto &i : neutrons)
        yldPart += pow(i.GetIntegratedYield().GetError()/
                       i.GetIntegratedYield().GetValue(),2);
    double ndkyPart = pow(dky.GetNumberOfDecays().GetError() /
                          dky.GetNumberOfDecays().GetValue(),2);
    return(pn*sqrt(yldPart+ndkyPart));
}

///This method calculates the mean
double ErrorCalculator::CalcMean(const vector<double> &mcVals) {
    double sum = 0;
    for(const auto &i : mcVals)
        sum += i;
    return(sum / mcVals.size());
}

///This method calculates the variance
double ErrorCalculator::CalcVariance(const vector<double> &mcVals, const double &mean) {
    double var = 0;
    for(const auto &i : mcVals)
        var += pow(i-mean,2);
    return(var/mcVals.size());
}
