/** \file FitHandler.cpp
 *  \brief A class to handle stuff related to the fit
 *  \author S. V. Paulauskas
 *  \date 10 December 2013
 */
#include <cmath>

#include "FitHandler.hpp"

double FitHandler::CalcAlpha(const double &tof) {
    double aI = 0.0130289072593045;
    double aH = -0.641803483244778;
    return(aI/tof/tof+aH);
}

double FitHandler::CalcN(const double &tof) {
    double nJ = 2.21591018795502e-06;
    double nK = 0.00189178692442985;
    double nL = 1.33190840921066;
    return(nJ*tof*tof+nK*tof+nL);
}

double FitHandler::CalcSigma(const double &tof) {
    double sM = -0.000121210451962825;
    double sN = 0.0416568757021418;
    double sO = 0.550158923590531;
    return(sM*tof*tof+sN*tof+sO);
}
