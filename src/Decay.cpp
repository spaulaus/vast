/** \file Decay.cpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */

#include "Decay.hpp"
#include "ErrorCalculator.hpp"

Decay::Decay(const Variable &z, const Variable&q, const Variable &sn, 
             const Variable &qbn, const Variable &t) : 
    parZ_(z), q_(q), qbn_(qbn), sn_(sn), t_(t) {
}

void Decay::SetNormInfo(const Variable &rawG, const Variable &gEff,
                         const Variable &br) {
    rawG_=rawG; 
    gEff_=gEff; 
    gBr_=br;
    CalcNumberDecays();
}

void Decay::CalcNumberDecays(void){
    double numDky = rawG_.GetValue() / gEff_.GetValue() / gBr_.GetValue();
         
    ErrorCalculator err;
    double numDkyErr = err.CalcNumDkyErr(numDky, rawG_, gEff_, gBr_);

    numDecay_ = Variable(numDky, numDkyErr, "");
}
