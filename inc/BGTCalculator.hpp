/** \file BGTCaluclator.hpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __BGTCALCULATOR_HPP__
#define __BGTCALCULATOR_HPP__

#include <map>

#include "Decay.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"

class BGTCalculator {
public:
    BGTCalculator(){};
    BGTCalculator(std::map<double,double> &density, const Decay &decay,
                  const double &betaEff, const double &omega,
                  const double &eg = 0.0);
                  
    BGTCalculator(Neutron &neutron, const Decay &decay,
                  const double &betaEff, const double &omega,
                  const double &eg = 0.0);
    ~BGTCalculator(){};

    std::map<double,double>* GetBgtMap(void){return(&bgtMap_);};
    std::map<double,double>* GetLogftMap(void){return(&logftMap_);};
    std::map<double,double>* GetSDensity(void){return(&sDensity_);};
private:
    Decay decay_;
    Neutron neutron_; 

    double betaEff_, geEff_, eG_, eN_, f_, omega_, yld_; 
    std::map<double,double> density_, bgtMap_, logftMap_, sDensity_;
    
    double CalcBgt(const double &en, const double &val,
                   const bool &isIndv = true);
    double CalcBranchingRatio(const double &yld);
    double CalcF(const double &en);
    double CalcLevelEnergy(const double &en);
    double CalcLogft(const double &en, const double &val,
                     const bool &isIndv = true);

    void HandleNeutronDensity(const std::map<double,double> &density);
    void HandleNeutronIndividual(Neutron &neutron);
};
#endif //__BGTCALCULATOR_HPP__
