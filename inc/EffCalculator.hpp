/** \file EffCalculator.hpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#ifndef __EFFCALCULATOR_HPP__
#define __EFFCALCULATOR_HPP__
#include <string>
#include <utility>

#include <PhysConstants.hpp>

class EffCalculator{
public:
    EffCalculator(){};
    EffCalculator(const std::string &type);
    ~EffCalculator(){};

    Variable GetEff(const Variable &energy);
    Variable GetSimRollingEff(const Variable &energy);

private:
    std::map<std::string, Variable> vals_;
};

#endif //__EFFCALCULATOR_HPP__
