/** \file ErrorCalculator.hpp
 *  \brief A class that calculates the error on variables.
 *  \author S. V. Paulauskas
 *  \date 29 October 2013
 */
#ifndef __ERRORCALCULATOR_HPP__
#define __ERRORCALCULATOR_HPP__
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <Variable.hpp>

#include "Decay.hpp"
#include "Neutron.hpp"

class ErrorCalculator{
public:
    ErrorCalculator(){};
    ~ErrorCalculator(){};

    double CalcBgtErr(const double &bgt, const Variable &br, 
                      const Variable &halfLife);
    double CalcBrErr(const double &br, const Variable &yld, const Variable &ndky,
                     const Variable &gammaEff, const Variable &betaEff);
    double CalcEffErr(const std::map<std::string,Variable> &vars, 
                      const Variable &energy);
    double CalcEnergyErr(const Variable &sig, const Variable &mu);
    double CalcIntegratedYldErr(const double &fitYld, const double &fitSimp,
                                const double &infSimp); 
    double CalcLogftErr(const Variable &br, const Variable &halfLife);
    double CalcNumDkyErr(const double &numDky, const Variable &rawGammaCounts, 
                         const Variable &gammaEff, const Variable &gammaBr);
    double CalcPnErr(const double &pn, std::vector<Neutron> &neutrons,
                     const Decay &dky);
private:
    static const int numSamples=1e5;  // number of experiments

    double CalcMean(const std::vector<double> &mcVals);
    double CalcVariance(const std::vector<double> &mcVals,
                              const double &mean);
};
#endif //__ERRORCALCULATOR_HPP__
