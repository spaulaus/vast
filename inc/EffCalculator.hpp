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

    /*! An enum that contains all of the various efficiencies that we are
     *  currently investigating in the code. \n
     *  + ge      : The Ge efficiency for gamma rays.
     *  + svpBan4 : The new parameterization is from the data provided
     *    to Sergey for my 077cu.ban banana 4, he provided these to me on
     *    09-10-2014, it was updated on 09-17-2014.
     *  + mmfBan  : The parameterization of the simulation results from
     *    Miguel's values sent to Sergey on 03-12-2014
     *  + vandle  : The efficiency taken from the LG Cf data (~ 6 keVee)
     *  + rolling : The original efficiency from Sergey - BAD, kept for legacy
     *  + beta    : The beta efficiency from Miguel's Calculations - UNUSED
     */
    enum class EffTypes {ge, svpBan4, mmfBan, vandle, rolling, beta};

    /*! Return the efficiency for the requested efficiency curve. The options
     *  for the different curves are documented in the enum, EffTypes.
     * \param[in] energy : expects the energy in MeV
     * \param[in] curve : The efficiency curve that you would like
     * \return The efficiency based off of the banana curve
     */
    Variable GetEff(const Variable &energy, const EffTypes &curve);

    /*! Return the beta efficiency calculated from Q_eff. The parameter energy
     * should also include the gamma ray energy if the neutron state is in
     * coincidence with a gamma line.
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
