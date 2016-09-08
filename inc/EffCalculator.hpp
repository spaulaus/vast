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

    /*! Sets the distance to calculate the ToF from the energy
     * \param [in] a : the distance */
    void SetDistance(const double &a){distance_ = a;};

    /*! An enum that contains all of the various efficiencies that we are
     *  currently investigating in the code. \n
     *  + beta    : The beta efficiency from Miguel's Calculations, currently
     *                  UNUSED due to the requirement for Q effective for the
     *                  calculation.
     *  + ge      : The Ge efficiency for gamma rays.
     *  + mmfCalc  : The parameterization taken from Miguel's code that adjusts
     *                  the efficiency based off of his banana gate.
     *  + mmfTheory  : The parameterization of the simulation results from
     *                  Miguel's values sent to Sergey on 03-12-2014
     *  + rolling : The original efficiency from Sergey - BAD, kept for legacy
     *  + svpBan4 : The new parameterization is from the data provided to Sergey
     *                  for my 077cu.ban banana 4, he provided these to me on
     *                  09-10-2014, it was updated on 09-17-2014.
     *  + svpTestBan1 : Banana that is a little wider than the previous one.
     *  + vandle  : The efficiency taken from the LG Cf data (~ 6 keVee) */
    enum EffTypes {beta, ge, mmfCalc, mmfTheory, rolling, svpBan4,
                            svpTestBan1, vandle};

    /*! Return the efficiency for the requested efficiency curve. The options
     *  for the different curves are documented in the enum, EffTypes.
     * \param[in] energy : expects the energy in MeV
     * \param[in] curve : The efficiency curve that you would like
     * \return The efficiency based off of the banana curve */
    Variable GetEff(const Variable &energy, const EffTypes &curve);

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
    Variable CalcEff(const Variable &energy, std::map<std::string,
                     Variable> &coeffs);
};
#endif //__EFFCALCULATOR_HPP__
