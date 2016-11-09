/** \file Decay.cpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <iostream>

#include "Decay.hpp"
#include "ErrorCalculator.hpp"

Decay::Decay(const Variable &z, const Variable&q, const Variable &sn,
             const Variable &qbn, const Variable &t) :
    parZ_(z), q_(q), qbn_(qbn), sn_(sn), t_(t) {
}

void Decay::SetNumDecay(const Variable &energy, const Variable &yield,
                        const Variable &br) {
    EffCalculator eff;
    numDecay_ = yield / eff.GetEff(energy, EffCalculator::EffTypes::ge)
        / br;
}
