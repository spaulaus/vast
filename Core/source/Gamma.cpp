/** \file Gamma.cpp
 * \brief A class to store information about a gamma
 * \author S. V. Paulauskas
 * \date 24 September 2014
 */
#include <iostream>

#include "Gamma.hpp"

using namespace std;

///This constructor sets the energy and calculates the efficiency
Gamma::Gamma(const Variable &en) {
    en_ = en;
}
