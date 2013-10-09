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
                  const double &betaEff, const double &omega);
                  
    BGTCalculator(Neutron &neutron, const Decay &decay,
                  const double &betaEff, const double &omega);
    ~BGTCalculator(){};

    std::map<double,double> GetBgtMap(void){return(bgtMap_);};
    std::map<double,double> GetLogftMap(void){return(logftMap_);};
    void SetGammaEnergy(const double &a){eG_ = a;};

private:
    Decay decay_;
    Neutron neutron_; 

    double betaEff_, eG_, eN_, f_, omega_, yld_; 
    //Variables to be passed to Neutron
    double bgt_, br_, logft_, lvl_;
    std::map<double,double> density_, bgtMap_, logftMap_;
    
    double CalcBranchingRatio(const double &yld);
    double CalcF(const double &en);
    double CalcLevelEnergy(const double &en);
    void CalcBgt(void);
    void CalcLogft(void);
    void StuffNeutronInfo(Neutron &neutron);
};
#endif //__BGTCALCULATOR_HPP__
