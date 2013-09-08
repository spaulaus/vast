/** \file BGTCaluclator.hpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __BGTCALCULATOR_HPP__
#define __BGTCALCULATOR_HPP__

#include "Decay.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"

class BGTCalculator {
public:
    BGTCalculator(){};
    BGTCalculator(NeutronDensity &density, const Decay &decay,
                  const double &betaEff, const double &omega);
                  
    BGTCalculator(Neutron &neutron, const Decay &decay,
                  const double &betaEff, const double &omega);
    ~BGTCalculator(){};

    
    double GetBgt(void){return(bgt_);};
    double GetBranchingRatio(void){return(br_);};
    double GetLevelEnergy(void){return(eLvl_);};
    double GetLogft(void){return(logft_);};

    void SetGammaEnergy(const double &a){eG_ = a;};

private:
    Decay decay_;
    double br_, bgt_, eG_, eLvl_, eN_, f_, logft_; 
    Neutron neutron_; 
    NeutronDensity density_;

    void CalcBgt(void);
    void CalcBranchingRatio(const double &betaEff, const double &omega);
    void CalcF(void);
    void CalcLevelEnergy(void);
    void CalcLogft(void);
};
#endif //__BGTCALCULATOR_HPP__
