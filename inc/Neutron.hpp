/** \file Neutron.hpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 04 September 2013
 */
#ifndef __NEUTRON_HPP__
#define __NEUTRON_HPP__

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
    double GetAlpha(void){return(alph_);};
    double GetN(void){return(n_);};
    double GetSigma(void){return(sig_);};
    //Gets Related to the Fit
    double GetEnergy(void){return(en_);};
    double GetEnergyErr(void){return(enErr_);};
    double GetMu(void){return(mu_);};
    double GetMuErr(void){return(muErr_);};
    double GetRawYield(void){return(yld_);};
    double GetRawYieldErr(void){return(yldErr_);};
    double GetYield(void){return(yld_/eff_);};
    double GetYieldErr(void){return(yldErr_/eff_);};
    //Gets Related to the Integration
    double GetIntegratedYield(void){return(intYld_/eff_);};
    double GetIntegratedYieldErr(void){return(intYldErr_/eff_);};
    double GetRawIntegratedYield(void){return(intYld_);};
    double GetRawIntegratedYieldErr(void){return(intYldErr_);};
    //Gets Related to the B(GT)
    double GetBgt(void){return(bgt_);};
    double GetBranchingRatio(void){return(br_);};
    double GetExcitationEnergy(void){return(ex_);};
    double GetLogft(void){return(logft_);};
    //Miscellaneous Gets
    double GetDensitySigma(void){return(denSig_);};
    double GetEfficiency(void){return(eff_);};

    //Sets related to the parameterization of the CB
    void SetAlpha(const double &a){alph_ = a;};
    void SetN(const double &a){n_ = a;};
    void SetSigma(const double &a){sig_ = a; CalcDensitySigma();};
    //Sets related to the Integration
    void SetIntegratedYield(const double &a){intYld_ = a;};
    void SetIntegratedYieldErr(const double &a){intYldErr_ = a;};
    //Sets related to the B(GT) Calculation
    void SetBgt(const double &a){bgt_ = a;};
    void SetBranchingRatio(const double &a){br_ = a;};
    void SetExitationEnergy(const double &a){ex_ = a;};
    void SetLogft(const double &a){logft_ = a;};
private:
    //Variables related to the CB
    double alph_, n_, sig_;
    //Variables related to the integration
    double intYld_, intYldErr_;
    //Variables related to the B(GT)
    double bgt_, br_, ex_, logft_;
    //Information Related to the Fit
    double mu_, muErr_, en_, enErr_, yld_, yldErr_;
    //Miscellaneous Information
    double denSig_, eff_, gammaE_;

    //Some Miscellaneous functions
    double CalcEnergy(const double &mu);
    double CalcEnergyErr(const double &mu, const double &muErr,
                         const double &en);
    void CalcDensitySigma(void);
};
#endif //__NEUTRON_HPP__
