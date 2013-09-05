/** \file BGTCaluclator.hpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __BGTCALCULATOR_HPP__
#define __BGTCALCULATOR_HPP__

#include "Neutron.hpp"
#include "Decay.hpp"

class BGTCalculator {
public:
    BGTCalculator(Neutron &neutron, const Decay &decay);
    ~BGTCalculator();

private:
    double bgt_, eLvl_, f_, logft_; 
    
    double CalcBranchingRatio(const double &area, const double &energy);
    double CalcF(const double &energy);
};
#endif //__BGTCALCULATOR_HPP__
