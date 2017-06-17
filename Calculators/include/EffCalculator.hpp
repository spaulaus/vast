/*! \file EffCalculator.hpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#ifndef __EFFCALCULATOR_HPP__
#define __EFFCALCULATOR_HPP__
#include <map>
#include <string>
#include <utility>

#include "Decay.hpp"
#include "HelperEnumerations.hpp"
#include "Variable.hpp"

//!A class that calculates the efficiency of the detectors in the analysis.
class EffCalculator{
public:
    /*! Default constructor */
    EffCalculator(){};
    /*!  Default destructor */
    ~EffCalculator(){};

    /*! Sets the distance to calculate the ToF from the energy
     * \param [in] a : the distance */
    void SetDistance(const double &a){distance_ = a;};

    /*! Return the efficiency for the requested efficiency curve. The options
     *  for the different curves are documented in the enum, EfficiencyEnums::EffTypes.
     * \param[in] energy : expects the energy in MeV
     * \param[in] curve : The efficiency curve that you would like
     * \return The efficiency based off of the banana curve */
    Variable GetEff(const Variable &energy, const EfficiencyEnums::EffTypes &curve);

    /*! Return the beta efficiency calculated from Q_eff. The parameter energy
     * should also include the gamma ray energy if the neutron state is in
     * coincidence with a gamma line.
     * \param[in] energy : The excitation energy of the daughter state
     * \param[in] dky : decay information for calculation of Q_eff
     * \return The efficiency of the beta */
    Variable GetBetaEff(const Variable &energy, const Decay &dky);
private:
    double distance_; //!< the distance from the bar

    /*! Calculate the time-of-flight
     * \param [in] en : The energy to use
     * \return the calculated time of flight */
    double CalcTof(const double &en);
    /*! Calculates the Simulated Rolling efficiency for small VANDLE. This is
     *  legacy and should not be used in any way
     *  \return The efficiency */
    Variable CalcSimRollingEff(const Variable &energy);
    /*! Calculates the efficiency from Miguel's banana for small VANDLE.
     *  \param [in] energy : the energy to calculate the efficiency
     *  \return The efficiency */
    Variable CalcMmfAdjusted(const Variable &energy);
    /*! Calculates the efficiency from Miguel's banana for small VANDLE.
     *  \param [in] energy : The energy to calculate the efficiency
     *  \param [in] coeffs : The coeffs the coefficients for the calculation
     *  \return The calculated efficiency */
    Variable CalcEff(const Variable &energy, std::map<std::string, Variable> &coeffs);
};
#endif //__EFFCALCULATOR_HPP__
