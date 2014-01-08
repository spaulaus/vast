/** \file Decay.hpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __DECAY_HPP__
#define __DECAY_HPP__
#include <Variable.hpp>

class Decay{
public:
    Decay(){};
    Decay(const Variable &z, const Variable&q, const Variable &sn, 
          const Variable &qbn, const Variable &t);
    ~Decay(){};
    
    Variable GetDaughterZ(void) const {return(dauZ_);};
    Variable GetNumberDecays(void) const {return(numDecay_);};
    Variable GetParentZ(void) const {return(parZ_);};
    Variable GetHalfLife(void) const {return(t_);};
    Variable GetNeutronBR(void) const {return(pn_);};
    Variable GetNeutronSepEnergy(void) const {return(sn_);};
    Variable GetQValue(void) const {return(q_);};
    Variable GetQBetaN(void) const {return(qbn_);};

    void SetNormInfo(const Variable &rawG, const Variable &gEff,
                      const Variable &br);
    void SetHalfLife(const Variable &a){t_ = a;};
    void SetNeutronBR(const Variable &a){pn_ = a;};
    void SetNeutronSepEnergy(const Variable &a){sn_ = a;};
    void SetParentZ(const Variable &a){parZ_ = a; SetDaughterZ();};
    void SetQValue(const Variable &a){q_ = a;};
    void SetQBetaN(const Variable &a){qbn_ = a;};

private:
    Variable gBr_, dauZ_, numDecay_, parZ_, pn_, 
        q_, qbn_, sn_, t_, rawG_, gEff_;
    
    void CalcNumberDecays(void);
    void SetDaughterZ(void) {dauZ_ = Variable(parZ_.GetValue()+1,0.0,"");};
};
#endif //__DECAY_HPP__
