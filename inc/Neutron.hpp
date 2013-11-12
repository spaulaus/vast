/** \file Neutron.hpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#ifndef __NEUTRON_HPP__
#define __NEUTRON_HPP__

#include <Variable.hpp>

#include "EffCalculator.hpp"

class Neutron {
public:
    Neutron(){};
    Neutron(const double &mu, const double &yld);
    Neutron(const double &mu, const double &muErr, 
         const double &yld);
    Neutron(const double &mu, const double &muErr, 
         const double &yld, const double &yldErr);
    ~Neutron(){};
    
    //Gets For the CB variables
    Variable GetAlpha(void) {return{alph_};};
    Variable GetN(void) {return(n_);};
    Variable GetSigma(void){return(sig_);};
    //Gets Related to the Fit
    Variable GetEnergy(void){return(en_);};
    Variable GetMu(void){return(mu_);};
    Variable GetRawYield(void){return(yld_);};
    Variable GetYield(void){return(AdjEff(yld_));};
    //Gets Related to the Integration
    Variable GetIntegratedYield(void){return(AdjEff(intYld_));};
    Variable GetRawIntegratedYield(void){return(intYld_);};
    //Gets Related to the B(GT)
    Variable GetBgt(void){return(bgt_);};
    Variable GetBranchingRatio(void){return(br_);};
    Variable GetExcitationEnergy(void){return(ex_);};
    Variable GetLogft(void){return(logft_);};
    //Miscellaneous Gets
    Variable GetEfficiency(void){return(eff_);};

    //Sets related to the parameterization of the CB
    void SetAlpha(const Variable &a){alph_ = a;};
    void SetN(const Variable &a){n_ = a;};
    void SetSigma(const Variable &a){sig_ = a; CalcEnergyErr();};
    //Sets related to the Integration
    void SetIntegratedYield(const Variable &a){intYld_ = a;};
    //Sets related to the B(GT) Calculation
    void SetBgt(const Variable &a){bgt_ = a;};
    void SetBranchingRatio(const Variable &a){br_ = a;};
    void SetExitationEnergy(const Variable &a){ex_ = a;};
    void SetLogft(const Variable &a){logft_ = a;};
private:
    //Instance of the efficiency and error calculators
    EffCalculator eff;

    //Variables related to the CB
    Variable alph_, n_, sig_;
    //Variables related to the integration
    Variable intYld_, intYldErr_;
    //Variables related to the B(GT)
    Variable bgt_, br_, ex_, logft_;
    //Information Related to the Fit
    Variable mu_, muErr_, en_, enErr_, yld_, yldErr_;
    //Miscellaneous Information
    Variable denSig_, eff_, gammaE_;

    //Some Miscellaneous functions
    double CalcEnergy(const double &mu);
    void CalcEnergyErr(void);
    Variable AdjEff(const Variable &var);
};
#endif //__NEUTRON_HPP__
