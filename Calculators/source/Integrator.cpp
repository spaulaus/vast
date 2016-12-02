/** \file Integrator.cpp
 *  \brief A class to integrate a CB shape
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include "ErrorCalculator.hpp"
#include "Integrator.hpp"

using namespace std;

///This constructor takes ar
Integrator::Integrator(Neutron &neutron,
                       const std::pair<double,double> &range) {
    alpha_ = neutron.GetAlpha().GetValue();
    mu_    = neutron.GetMu().GetValue();
    n_     = neutron.GetN().GetValue();
    sigma_ = neutron.GetSigma().GetValue();

    Variable yld = neutron.GetRawYield();

    double fSimp = AdaptiveSimpsons(range.first, range.second, 1.e-20, 30);
    double uSimp = AdaptiveSimpsons(range.second, 1.e8, 1.e-20, 30);
    double intYld = (yld.GetValue()/fSimp)*uSimp + yld.GetValue();

    ErrorCalculator err;
    double intYldErr = err.CalcIntegratedYldErr(yld.GetError(), fSimp, uSimp);
    neutron.SetIntegratedYield(Variable(intYld, intYldErr, "counts"));
}

///Uses the AdaptiveSimpsons algorithm
/// (https://en.wikipedia.org/wiki/Adaptive_Simpson's_method)
/// to integrate a neutron peak in the range provided by a and b.
double Integrator::AdaptiveSimpsons(const double &a, const double &b,
                                    const double &epsilon,
                                    const int &maxRecursionDepth){
    double c = (a + b)/2, h = b - a;
    double fa = CrystalBall(a), fb = CrystalBall(b), fc = CrystalBall(c);
    double S = (h/6)*(fa + 4*fc + fb);
    return AdaptiveSimpsonsAux(a, b, epsilon, S, fa, fb, fc, maxRecursionDepth);
}

double Integrator::AdaptiveSimpsonsAux(const double &a,
                                       const double &b, const double &epsilon,
                                       const double &S, const double &fa,
                                       const double &fb, const double &fc,
                                       const int &bottom) {
    double c = (a + b)/2, h = b - a;
    double d = (a + c)/2, e = (c + b)/2;
    double fd = CrystalBall(d), fe = CrystalBall(e);
    double Sleft = (h/12)*(fa + 4*fd + fc);
    double Sright = (h/12)*(fc + 4*fe + fb);
    double S2 = Sleft + Sright;
    if (bottom <= 0 || fabs(S2 - S) <= 15*epsilon)
        return( S2 + (S2 - S)/15 );
    return( AdaptiveSimpsonsAux(a, c, epsilon/2, Sleft,  fa, fc, fd, bottom-1) +
            AdaptiveSimpsonsAux(c, b, epsilon/2, Sright, fc, fb, fe, bottom-1) );
}

double Integrator::CrystalBall(const double &var){
    double t = (var-mu_)/sigma_;

    if (alpha_ < 0)
        t = -t;

    double absAlpha = fabs(alpha_);

    if (t >= -absAlpha) {
        return( exp(-0.5*t*t) );
    }
    else {
        double a = pow(n_/absAlpha,n_)*exp(-0.5*absAlpha*absAlpha);
        double b = n_/absAlpha - absAlpha;
        return( a/pow(b - t, n_) );
    }
}
