/** \file Decay.hpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __DECAY_HPP__
#define __DECAY_HPP__

class Decay{
public:
    Decay(){};
    Decay(const double &z, const double&q, const double &sn, 
          const double &t);
    ~Decay(){};
    
    double GetDaughterZ(void) {return(CalcDaughterZ());};
    double GetNumberDecays(void) {return(CalcNumberDecays());};
    double GetParentZ(void) {return(parZ_);};

    double GetHalfLife(void) {return(t_);};
    double GetNeutronBR(void){return(pn_);};
    double GetNeutronSepEnergy(void) {return(sn_);};
    double GetQValue(void) {return(q_);};
    double GetQBetaN(void) {return(qbn_);};

    void SetGammaInfo(const double &rawG, const double &gEff,
                      const double &br){rawG_=rawG; gEff_=gEff; gBr_=br;};

private:
    double gBr_, dauZ_, numDecay_, parZ_, pn_, q_, qbn_, sn_, t_, rawG_, gEff_;
    
    double CalcDaughterZ(){return(parZ_+1);};
    double CalcNumberDecays(void){return(rawG_/gEff_/gBr_);};
};
#endif //__DECAY_HPP__
