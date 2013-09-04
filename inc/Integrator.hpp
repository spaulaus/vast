/** \file Integrator.hpp
 *  \brief A class to integrate a CB shape 
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __INTEGRATOR_HPP__
#define __INTEGRATOR_HPP__

#include <vector>

#include "Neutron.hpp"

class Integrator{
public:
    Integrator(Neutron &neutron, const double &fitLow, const double &fitHigh);
    ~Integrator(){};

    double GetValue(const double &t) {return(CrystalBall(t));};
private:
    Neutron neutron_; 
    double alpha_, mu_, n_, sigma_;

    //double (Integrator::*CB) (double);

    double AdaptiveSimpsons(double (*f)(double),   // ptr to function
                            const double &a, const double &b,  // interval [a,b]
                            const double &epsilon,  // error tolerance
                            const int &maxRecursionDepth);   // recursion cap
    double AdaptiveSimpsonsAux(double (*f)(double), const double &a, 
                               const double &b, const double &epsilon, 
                               const double &S, const double &fa, 
                               const double &fb, const double &fc, 
                               const int &bottom);
    double CrystalBall(double var);
};
#endif //__INTEGRATOR_HPP__
