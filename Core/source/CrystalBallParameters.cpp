/** \file CrystalBallParameters.cpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#include <cmath>

#include "CrystalBallParameters.hpp"

double CrystalBallParameters::CalcAlpha(const double &tof) {
    return alphaCoeff_[3].GetValue() * tof * tof * tof +
           alphaCoeff_[2].GetValue() * tof * tof +
           alphaCoeff_[1].GetValue() * tof +
           alphaCoeff_[0].GetValue();
}

double CrystalBallParameters::CalcN(const double &tof) {
    return nCoeff_[2].GetValue() * tof +
           nCoeff_[1].GetValue() +
           nCoeff_[0].GetValue() / tof;
}

double CrystalBallParameters::CalcSigma(const double &tof) {
    return sigmaCoeff_[4].GetValue() * tof * tof * tof * tof +
           sigmaCoeff_[3].GetValue() * tof * tof * tof +
           sigmaCoeff_[2].GetValue() * tof * tof +
           sigmaCoeff_[1].GetValue() * tof +
           sigmaCoeff_[0].GetValue();
}
