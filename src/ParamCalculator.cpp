/** \file LimitFinder.cpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#include <cmath>

#include "ParamCalculator.hpp"

ParamCalculator::ParamCalculator() {
    a_ = Variable(0.182054785299905,0.120600342017301, "");
    b_ = Variable(0.0702251563856091,0.0106934660040812, "");
    c_ = Variable(-0.000758484151770592,0.000297874842708119, "");
    d_ = Variable(4.9037446067281e-06,3.14410168660413e-06, "");
    e_ = Variable(-1.19754032045065e-08,1.09884987835696e-08, "");
    f_ = Variable(-0.731102982540993,0.102067053316365, "");
    g_ = Variable(-0.00101154263287747,0.00574583321704663, "");
    h_ = Variable(2.52616634112643e-05,8.81266428149048e-05, "");
    i_ = Variable(-1.07220006090512e-07,3.89451241944696e-07, "");
    j_ = Variable(-4.3378707812973,1.60649197907772, "");
    k_ = Variable(0.00179493445312942,0.000954820140979053, "");
    l_ = Variable(1.65099132803374,0.0923163248869663, "");
}

double ParamCalculator::CalcAlpha(const double &tof) {
    return(i_.GetValue()*tof*tof*tof + h_.GetValue()*tof*tof +
           g_.GetValue()*tof + f_.GetValue());
}

double ParamCalculator::CalcN(const double &tof) {
    return(j_.GetValue()/tof + k_.GetValue()*tof + l_.GetValue());
}

double ParamCalculator::CalcSigma(const double &tof) {
    return(e_.GetValue()*pow(tof,4) + d_.GetValue()*pow(tof,3) +
           c_.GetValue()*tof*tof + b_.GetValue()*tof + a_.GetValue());
}
