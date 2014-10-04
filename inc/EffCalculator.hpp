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

#include <Decay.hpp>
#include <Variable.hpp>

//!A class that calculates the efficiency of the detectors in the analysis.
class EffCalculator{
public:
    /*! Default constructor */
    EffCalculator(){};
    /*!  Default destructor */
    ~EffCalculator(){};

    enum class EffTypes {ge, svpBan4, mmfBan, vandle, rolling, beta};

    Variable GetEff(const Variable &energy, const EffTypes &curve);

    /*! Return the efficiency that was simulated by Sergey following the rolling
     * threshold of the banana gate. We are currently assuming zero error on
     * this calculation.
     * \param[in] energy : expects the energy in MeV
     * \return The efficiency based off of the banana curve
     */


    /*! Return the beta efficiency calculated from Q_eff. The parameter ex
     * should also include the gamma ray energy if the neutron state is in
     * coincidencewith a gamma line.
     * \param[in] energy : The excitation energy of the daughter state
     * \param[in] dky : decay information for calculation of Q_eff
     * \return The efficiency of the beta
     */
    Variable GetBetaEff(const Variable &energy, const Decay &dky);
private:
    Variable CalcSimRollingEff(const Variable &energy);

    Variable CalcEff(const Variable &energy,
                     std::map<std::string, Variable> &coeffs);
};
#endif //__EFFCALCULATOR_HPP__
