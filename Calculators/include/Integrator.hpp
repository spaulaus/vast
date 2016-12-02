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
    /*! Default Constructor */
    Integrator(){};
    /*! Constructor taking arguments to perform integration on
     \param[in] neutron : the neutron event of interest
     \param[in] range   : the fitting range used for the neutron event
    */
    Integrator(Neutron &neutron, const std::pair<double,double> &range);
    /*! Default destructor */
    ~Integrator(){};

    /*! Get the value of the CrystalBall function at a given TOF
    *   \param[in] t The ToF to calculate the value of the CB
    *   \return The value of the CB at the given ToF
    */
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