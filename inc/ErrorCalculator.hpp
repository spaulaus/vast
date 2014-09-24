/*! \file ErrorCalculator.hpp
 *  \brief A class that calculates the error on variables.
 *  \author S. V. Paulauskas
 *  \date 29 October 2013
 */
#ifndef __ERRORCALCULATOR_HPP__
#define __ERRORCALCULATOR_HPP__
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <Variable.hpp>

#include "Decay.hpp"
#include "Neutron.hpp"

/*! \brief A class that propagates the error on the various variables
 *
 * It's possible that some of these methods are no longer necessary due to
 * the updates that were made to the Variable class. As long as everything is
 * consistently updated, a lot of this stuff should be automatically handled
 * by the Variable type.
 */
class ErrorCalculator{
public:
    /*!  Default constructor */
    ErrorCalculator(){};
    /*!  Default destructor */
    ~ErrorCalculator(){};

    /*! Calculates the error on the B(GT)
    *   \param[in] bgt : the bgt for the calculation
    *   \param[in] br  : the branching ratio of the gamma line
    *   \param[in] halfLife : the halflife of the decay
    *   \return The B(GT) error
    */
    double CalcBgtErr(const double &bgt, const Variable &br,
                      const Variable &halfLife);
    /*! Calculates the error on the neutron branching ratio
    *   \param[in] br       : the neutron branching ratio
    *   \param[in] yld      : the total yield of the neutron peak
    *   \param[in] ndky     : the total number of decays for the run
    *   \param[in] gammaEff : the gamma efficiency for the gating gamma ray
    *   \param[in] betaEff  : the beta efficiency for the beta detector
    *   \return The branching ratio error
    */
    double CalcBrErr(const double &br, const Variable &yld, const Variable &ndky,
                     const Variable &gammaEff, const Variable &betaEff);
    /*! Calculate the error on the gamma efficiency using MC technique
     *  \param[in] vars   : the coefficiencts for the fitting function
     *  \param[in] energy : The gamma ray energy in units of keV
     *  \return The efficiency error
     */
    double CalcEffErr(const std::map<std::string,Variable> &vars,
                      const Variable &energy);
    /*!  Calculate the error on the energy of the neutron peak
     * \param[in] sig : The sigma for the neutron peak
     * \param[in] mu  : the mean value for the neutron peak
     *  \return The error on the energy calculation
     */
    double CalcEnergyErr(const Variable &sig, const Variable &mu);
    /*! Calculate the error on the integrated yield of the neutron peak.
    * \param[in] fitYld  : the yield from the fitting routines
    * \param[in] fitSimp : The value of the integration in the fitting region
    * \param[in] infSimp : The value of the integration from the end of
    * the fitting region to infinity.
    * \return The error on the integrated yield
    */
    double CalcIntegratedYldErr(const double &fitYld, const double &fitSimp,
                                const double &infSimp);
    /*! Calculate the error on the log(ft)
     * \param[in] br       : the branching ratio of the neutron peak
     * \param[in] halfLife : the half-life of the decay
     * \return The error on the log(ft)
     */
    double CalcLogftErr(const Variable &br, const Variable &halfLife);
    /*! Calculate the error on the total number of decays
     * \param[in] numDky         : the total number of decays
     * \param[in] rawGammaCounts : the raw number of gammas in the normalization line
     * \param[in] gammaEff       : the efficiency for the normalization gamma line
     * \param[in] gammaBr        : the absolute branching ratio for the normalization
     * gamma
     * \return The error on the number of decays
     */
    double CalcNumDkyErr(const double &numDky, const Variable &rawGammaCounts,
                         const Variable &gammaEff, const Variable &gammaBr);
    /*! Calculat the error on the neutron branching ratio
    * \param[in] pn       : the neutron branching ratio
    * \param[in] neutrons : the vector of neutron peaks from the fit
    * \param[in] dky      : the decay information
    * \return The error on the neutron branching ratio
    */
    double CalcPnErr(const double &pn, std::vector<Neutron> &neutrons,
                     const Decay &dky);
private:
    static const int numSamples=1e5;  // number of experiments

    double CalcMean(const std::vector<double> &mcVals);
    double CalcVariance(const std::vector<double> &mcVals,
                              const double &mean);
};
#endif //__ERRORCALCULATOR_HPP__
