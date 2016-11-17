/** \file LimitFinder.cpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#include <cmath>

#include "ParamCalculator.hpp"

double ParamCalculator::CalcAlpha(const double &tof) {
    return alphaCoeff_[3].GetValue() * tof * tof * tof +
           alphaCoeff_[2].GetValue() * tof * tof +
           alphaCoeff_[1].GetValue() * tof +
           alphaCoeff_[0].GetValue();
}

double ParamCalculator::CalcN(const double &tof) {
    return nCoeff_[2].GetValue() * tof +
           nCoeff_[1].GetValue() +
           nCoeff_[0].GetValue() / tof;
}

double ParamCalculator::CalcSigma(const double &tof) {
    return sigmaCoeff_[4].GetValue() * tof * tof * tof * tof +
           sigmaCoeff_[3].GetValue() * tof * tof * tof +
           sigmaCoeff_[2].GetValue() * tof * tof +
           sigmaCoeff_[1].GetValue() * tof +
           sigmaCoeff_[0].GetValue();
}
