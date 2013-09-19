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

    double GetAlpha(void){return(alph_);};
    double GetBranchingRatio(void){return(br_);};
    double GetDensitySigma(void){return(denSig_);};
    double GetEfficiency(void){return(eff_);};
    double GetEnergy(void){return(en_);};
    double GetEnergyErr(void){return(enErr_);};
    double GetIntegratedYield(void){return(intYld_);};
    double GetIntegratedYieldErr(void){return(intYldErr_);};
    double GetMu(void){return(mu_);};
    double GetMuErr(void){return(muErr_);};
    double GetN(void){return(n_);};
    double GetRawYield(void){return(yld_);};
    double GetRawYieldErr(void){return(yldErr_);};
    double GetSigma(void){return(sig_);};
    double GetYield(void){return(yld_/eff_);};
    double GetYieldErr(void){return(yldErr_/eff_);};
    
    void SetBranchingRatio(const double &a){br_ = a;};
    void SetIntegratedYield(const double &a){intYld_ = a;};
    void SetIntegratedYieldErr(const double &a){intYldErr_ = a;};
private:
    double mu_, muErr_, en_, enErr_;
    double yld_, yldErr_, intYld_, intYldErr_;
    double alph_, br_, denSig_, eff_, gammaE_, n_, sig_;

    double CalcAlpha(const double &mu);
    double CalcDensitySigma(const double &mu);
    double CalcEfficiency(const double &mu);
    double CalcEnergy(const double &mu);
    double CalcEnergyErr(const double &mu, const double &muErr,
                         const double &en);
    double CalcN(const double &mu);
    double CalcSigma(const double &mu);
};
#endif //__NEUTRON_HPP__
