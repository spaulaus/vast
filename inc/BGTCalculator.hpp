/** \file BGTCaluclator.hpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __BGTCALCULATOR_HPP__
#define __BGTCALCULATOR_HPP__
#include <map>
#include <string>

#include <Variable.hpp>

#include "Decay.hpp"
#include "ErrorCalculator.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"

class BGTCalculator {
public:
    BGTCalculator(){};
    BGTCalculator(std::map<double,double> &density, const Decay &decay,
                  const Variable &betaEff, const Variable &omega,
                  const std::string &band = "",
                  const Variable &eg = Variable(0.0,1.0,""));
                  
    BGTCalculator(Neutron &neutron, const Decay &decay,
                  const Variable &betaEff, const Variable &omega,
                  const Variable &eg = Variable(0.0,0.0,""));
    ~BGTCalculator(){};

    std::map<double,double>* GetBgtMap(void){return(&bgtMap_);};
    std::map<double,double>* GetLogftMap(void){return(&logftMap_);};
    std::map<double,double>* GetSDensity(void){return(&sDensity_);};
private:
    Decay decay_;
    Neutron neutron_; 
    ErrorCalculator err;

    Variable betaEff_, geEff_, eG_, eN_, f_, omega_, yld_; 
    std::string band_;
    std::map<double,double> density_, bgtMap_, logftMap_, sDensity_;
    
    Variable CalcBgt(const Variable &en, const Variable &val,
                   const bool &isIndv = true);
    Variable CalcBranchingRatio(const Variable &yld);
    double CalcF(const Variable &en);
    Variable CalcLevelEnergy(const Variable &en);
    Variable CalcLogft(const Variable &en, const Variable &val,
                     const bool &isIndv = true);

    void HandleNeutronDensity(const std::map<double,double> &density);
    void HandleNeutronIndividual(Neutron &neutron);
};
#endif //__BGTCALCULATOR_HPP__
