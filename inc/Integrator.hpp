/** \file Integrator.hpp
 *  \brief A class to integrate a CB shape 
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __INTEGRATOR_HPP__
#define __INTEGRATOR_HPP__

#include <vector>
#include <utility>

#include <Variable.hpp>

#include "Neutron.hpp"

///A class that uses and Adaptive Simpsons method to integrate the neutron peaks
class Integrator{
public:
    Integrator(Neutron &neutron, const std::pair<double,double> &range);
    ~Integrator(){};

    double GetValue(const double &t) {return(CrystalBall(t));};
private:
    double alpha_, mu_, n_, sigma_;

    double CalcError(const double &fSimp, const double &uSimp);

    double AdaptiveSimpsons(const double &a, const double &b,  // interval [a,b]
                            const double &epsilon,  // error tolerance
                            const int &maxRecursionDepth);   // recursion cap
    double AdaptiveSimpsonsAux(const double &a, 
                               const double &b, const double &epsilon, 
                               const double &S, const double &fa, 
                               const double &fb, const double &fc, 
                               const int &bottom);
    double CrystalBall(const double &var);
};
#endif //__INTEGRATOR_HPP__
