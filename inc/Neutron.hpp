/** \file Neutron.hpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#ifndef __NEUTRON_HPP__
#define __NEUTRON_HPP__

#include <Variable.hpp>

#include "EffCalculator.hpp"

///A class that contains all of the information for a neutron peak
class Neutron {
public:
    /*! Default Constructor */
    Neutron(){};
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
    ~Neutron(){};
    
    /*! Return the CB parameter alpha */
    Variable GetAlpha(void) {return{alph_};};
    /*! Return the CB parameter n */
    Variable GetN(void) {return(n_);};
    /*! Return the CB parameter sigma */
    Variable GetSigma(void){return(sig_);};
    /*! Return the energy related to the neutron peak */
    Variable GetEnergy(void){return(en_);};
    /*! Return the fitted mean of the neutron peak */
    Variable GetMu(void){return(mu_);};
    /*! Return the fitted yield of the neutron peak */
    Variable GetRawYield(void){return(yld_);};
    /*! Return the efficiency adjusted yield */
    Variable GetYield(void){return(AdjEff(yld_));};
    /*! Return the efficiency adjusted integrated yield */
    Variable GetIntegratedYield(void){return(AdjEff(intYld_));};
    /*! Return the raw integrated yield */
    Variable GetRawIntegratedYield(void){return(intYld_);};
    /*! Return the B(GT) for the peak */
    Variable GetBgt(void){return(bgt_);};
    /*! Return the Branching ratio for the peak */
    Variable GetBranchingRatio(void){return(br_);};
    /*! Return the excitation energy of the peak */
    Variable GetExcitationEnergy(void){return(ex_);};
    /*! Return the log(ft) of the peak */
    Variable GetLogft(void){return(logft_);};
    /*! Return the efficiency of the peak */
    Variable GetEfficiency(void){return(eff_);};

    /*! Set the mean of the CB for the peak */
    void SetMu(const Variable &a) {mu_ = a; CalcEnEff();};
    /*! Set the yield of the CB */
    void SetYld(const Variable &a) {yld_ = a;};
    /*! Set the alpha parameter of the CB */
    void SetAlpha(const Variable &a){alph_ = a;};
    /*! Set the n parameter for the CB */
    void SetN(const Variable &a){n_ = a;};
    /*! Set the sigma for the CB */
    void SetSigma(const Variable &a){sig_ = a; CalcEnergyErr();};
    /*! Set the integrated yield */
    void SetIntegratedYield(const Variable &a){intYld_ = a;};
    /*! Set the B(GT) */
    void SetBgt(const Variable &a){bgt_ = a;};
    /*! Set the branching ratio */
    void SetBranchingRatio(const Variable &a){br_ = a;};
    /*! Set the Excitation energy */
    void SetExcitationEnergy(const Variable &a){ex_ = a;};
    /*! Set the log(ft) */
    void SetLogft(const Variable &a){logft_ = a;};
private:
    //Instance of the efficiency and error calculators
    EffCalculator eff;

    //Variables related to the CB
    Variable alph_, n_, sig_;
    //Variables related to the integration
    Variable intYld_;
    //Variables related to the B(GT)
    Variable bgt_, br_, ex_, logft_;
    //Information Related to the Fit
    Variable mu_, en_, yld_;
    //Miscellaneous Information
    Variable eff_, gammaE_;

    //Some Miscellaneous functions
    double CalcEnergy(const double &mu);

    Variable AdjEff(const Variable &var);
    void CalcEnEff(void);
    void CalcEnergyErr(void);
};
#endif //__NEUTRON_HPP__
