/** \file EffCalculator.hpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#ifndef __EFFCALCULATOR_HPP__
#define __EFFCALCULATOR_HPP__
#include <map>
#include <string>
#include <utility>

#include <Variable.hpp>

class EffCalculator{
public:
    EffCalculator(){};
    EffCalculator(const std::string &type){SetVariables(type);};
    ~EffCalculator(){};

    Variable GetEff(const Variable &energy);
    Variable GetSimRollingEff(const Variable &energy);
    
    void SetEfficiencyType(const std::string &type) {SetVariables(type);};
private:
    std::map<std::string, Variable> vals_;
    void SetVariables(const std::string &type);
};

#endif //__EFFCALCULATOR_HPP__
