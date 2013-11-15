/** \file LimitFinder.cpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#include <cmath>

#include "ParamCalculator.hpp"

double ParamCalculator::CalcAlpha(const double &tof) {
    double aI = 0.0130289072593045;
    double aH = -0.641803483244778;
    return(aI/tof/tof+aH);
}

double ParamCalculator::CalcN(const double &tof) {
    double nJ = 2.21591018795502e-06;
    double nK = 0.00189178692442985;
    double nL = 1.33190840921066;
    return(nJ*tof*tof+nK*tof+nL);
}

double ParamCalculator::CalcSigma(const double &tof) {
    double sM = -0.000121210451962825;
    double sN = 0.0416568757021418;
    double sO = 0.550158923590531;
    return(sM*tof*tof+sN*tof+sO);
}
