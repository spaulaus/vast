/** \file Decay.cpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include "Decay.hpp"
#include "ErrorCalculator.hpp"

///This method sets the number of decays based on the normalization gamma line
void Decay::SetNumDecay(const Variable &energy, const Variable &yield, const Variable &br) {
    EffCalculator eff;
    numDecay_ = yield / eff.GetEff(energy, EfficiencyEnums::EffTypes::ge) / br;
}