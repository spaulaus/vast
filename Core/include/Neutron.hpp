/*! \file Neutron.hpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#ifndef __NEUTRON_HPP__
#define __NEUTRON_HPP__

#include <Variable.hpp>

#include "EffCalculator.hpp"

//!A class that contains all of the information for a neutron peak
class Neutron {
public:
    /*! Default Constructor */
    Neutron() {};

    /*! Constructor assuming no errors
      \param[in] mu  : the mean for the neutron peak
      \param[in] yld : the raw yield of the neutron peak
    */
    Neutron(const double &mu, const double &yld);

    /*! Constructor with error on the mean
      \param[in] mu    : the mean for the neutron peak
      \param[in] muErr : the error on the mean
      \param[in] yld   : the raw yield of the neutron peak
    */
    Neutron(const double &mu, const double &muErr,
            const double &yld);

    /*! Constructor with error on both mean and yield
      \param[in] mu  :   the mean for the neutron peak
      \param[in] muErr  : the error on the mean
      \param[in] yld    : the raw yield of the neutron peak
      \param[in] yldErr : the error on the yield
    */
    Neutron(const double &mu, const double &muErr,
            const double &yld, const double &yldErr);

    /*! Default destructor */
    ~Neutron() {};

    /*! \return The CB parameter alpha */
    Variable GetAlpha(void) { return (alph_); };

    /*! \return The beta resolution for the given neutron peak */
    Variable GetBetaResolution(void) { return (betaRes_); };

    /*! \return the CB parameter n */
    Variable GetN(void) { return (n_); };

    /*! \return the CB parameter sigma */
    Variable GetSigma(void) { return (sig_); };

    /*! \return the energy related to the neutron peak */
    Variable GetEnergy(void) { return (en_); };

    /*! \return the fitted mean of the neutron peak */
    Variable GetMu(void) { return (mu_); };

    /*! \return the fitted yield of the neutron peak */
    Variable GetRawYield(void) { return (yld_); };

    /*! \return the efficiency adjusted yield */
    Variable GetYield(void) { return (AdjEff(yld_)); };

    /*! \return the efficiency adjusted integrated yield */
    Variable GetIntegratedYield(void) { return (AdjEff(intYld_)); };

    /*! \return the raw integrated yield */
    Variable GetRawIntegratedYield(void) { return (intYld_); };

    /*! \return the B(GT) for the peak */
    Variable GetBgt(void) { return (bgt_); };

    /*! \return the Branching ratio for the peak */
    Variable GetBranchingRatio(void) { return (br_); };

    /*! \return the excitation energy of the peak */
    Variable GetExcitationEnergy(void) { return (ex_); };

    /*! \return the log(ft) of the peak */
    Variable GetLogft(void) { return (logft_); };

    /*! \return the efficiency of the peak */
    Variable GetEfficiency(void) { return (eff_); };

    /*! Set the mean of the CB for the peak
    *   \param[in] a The mean of the neutron peak */
    void SetMu(const Variable &a) {
        mu_ = a;
        CalcEnEff();
    };

    /*! Set the yield of the CB
    *   \param[in] a The yield as calculated from the fit */
    void SetYld(const Variable &a) { yld_ = a; };

    /*! Set the alpha parameter of the CB
    *   \param[in] a The alpha of the CB */
    void SetAlpha(const Variable &a) { alph_ = a; };

    /*! Set the n parameter for the CB
    *   \param[in] a The n of the CB */
    void SetN(const Variable &a) { n_ = a; };

    /*! Set the sigma for the CB
    *   \param[in] a The sigma of the Gaussian of the CB */
    void SetSigma(const Variable &a) { sig_ = a; };

    /*! Set the integrated yield
    *   \param[in] a The integrated yield of the CB */
    void SetIntegratedYield(const Variable &a) { intYld_ = a; };

    /*! Set the B(GT)
    *   \param[in] a The Delta Function B(GT) of the neutron */
    void SetBgt(const Variable &a) { bgt_ = a; };

    /*! Set the branching ratio
    *   \param[in] a The Delta Function Branching Ratio of the neutron */
    void SetBranchingRatio(const Variable &a) { br_ = a; };

    /*! Set the Excitation energy
    *   \param[in] a The excitation energy of the state (S_n + E_n) */
    void SetExcitationEnergy(const Variable &a) { ex_ = a; };

    /*! Set the log(ft)
    *   \param[in] a The log(ft) of the neutron */
    void SetLogft(const Variable &a) { logft_ = a; };
private:
    //!Instance of the efficiency and error calculators
    EffCalculator eff;

    Variable betaRes_;
    //!Variables related to the CB
    Variable alph_, n_, sig_;
    //!Variables related to the integration
    Variable intYld_;
    //!Variables related to the B(GT)
    Variable bgt_, br_, ex_, logft_;
    //!Information Related to the Fit
    Variable mu_, en_, yld_;
    //!Miscellaneous Information
    Variable eff_, gammaE_;

    /*! Calculate the energy of the neutron from the ToF
    *   \param[in] mu The ToF of the neutron
    *   \return The energy of the neturon */
    void CalcEnergy(void);

    /*! Adjust the input variable for the intrinsic neutron efficiency
    *   \param[in] var The variable to adjust for the intrinsic efficiency
    *   \return The intrinsic efficiency adjusted variable */
    Variable AdjEff(const Variable &var);

    /*! Calculate the efficiency of the neutron */
    void CalcEnEff(void);

    /*! Calculate the beta resolution for the neutron peak */
    void CalcBetaResolution(void);
};

#endif //__NEUTRON_HPP__
