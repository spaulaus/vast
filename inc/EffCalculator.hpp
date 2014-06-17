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

///A class that calculates the efficiency of the detectors in the analysis.
class EffCalculator{
public:
    /*! Default constructor */
    EffCalculator(){};
    /*! Constructor taking the type of efficiency to calculate
     * \param[in] type : The type of detector for the efficiency calculation. It can 
     * either be "vandle" or "ge". 
     */
    EffCalculator(const std::string &type){SetVariables(type);};
    /*!  Default destructor */
    ~EffCalculator(){};

    /*!  Return the efficiency for the set detector type 
     * \param[in] energy : The energy in keV for the ge and MeV for vandle
     */
    Variable GetEff(const Variable &energy);
    /*! Return the efficiency that was simulated by Sergey following the rolling
     * threshold of the banana gate. We are currently assuming zero error on this 
     * calculation. 
     * \param[in] energy : expects the energy in MeV */
    Variable GetSimRollingEff(const Variable &energy);
    
    /*! A method to set the detector type for the efficiency calculation. 
     * \param[in] type : The detector type, either "ge" or "vandle". */
    void SetEfficiencyType(const std::string &type) {SetVariables(type);};
private:
    std::map<std::string, Variable> vals_;
    void SetVariables(const std::string &type);
};

#endif //__EFFCALCULATOR_HPP__
