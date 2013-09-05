/** \file EffCalculator.hpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#ifndef __EFFCALCULATOR_HPP__
#define __EFFCALCULATOR_HPP__
#include <string>

class EffCalculator{
public:
    EffCalculator(){};
    EffCalculator(const std::string &type);
    ~EffCalculator(){};

    double GetEff(const double &energy);
    double GetSimRollingEff(const double &energy);

private:
    double a_, b_, c_, d_, e_, f_, g_, e1_, e2_;
};

#endif //__EFFCALCULATOR_HPP__
