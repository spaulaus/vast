/** \file CrystalBallParameters.cpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */

#include "CrystalBallParameters.hpp"

///For more info on crystal ball function:
///https://en.wikipedia.org/wiki/Crystal_Ball_function.

///@TODO Update this to use TF1?

///This method calculates the Crystal Ball Parameter Alpha
double CrystalBallParameters::CalcAlpha(const double &tof) const {
    return alphaCoeff_[3].GetValue() * tof * tof * tof +
           alphaCoeff_[2].GetValue() * tof * tof +
           alphaCoeff_[1].GetValue() * tof +
           alphaCoeff_[0].GetValue();
}

///This method calculates the Crystal Ball Parameter N
double CrystalBallParameters::CalcN(const double &tof) const {
    return nCoeff_[2].GetValue() * tof +
           nCoeff_[1].GetValue() +
           nCoeff_[0].GetValue() / tof;
}

///This method calculates the Crystal Ball Parameter Sigma
double CrystalBallParameters::CalcSigma(const double &tof) const {
    return sigmaCoeff_[4].GetValue() * tof * tof * tof * tof +
           sigmaCoeff_[3].GetValue() * tof * tof * tof +
           sigmaCoeff_[2].GetValue() * tof * tof +
           sigmaCoeff_[1].GetValue() * tof +
           sigmaCoeff_[0].GetValue();
}
