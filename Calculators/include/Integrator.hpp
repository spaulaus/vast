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

    ///@brief  This method calculates the error associated with the Simpson's
    /// Method integration.
    ///@param[in] fSimp : ?
    ///@param[in] uSimp : ?
    ///@TODO Implement this(needed?).
    double CalcError(const double &fSimp, const double &uSimp);

    ///@brief This method implements Simpson's rule to integrate the neutron
    /// peak.
    ///@param[in] a : Start of interval
    ///@param[in] b : End of interval
    ///@param[in] epsilon   : Error tolerance
    ///@param[in] maxRecursionDepth : recursion cap(Max number of iterations)
    double AdaptiveSimpsons(const double &a, const double &b,
                            const double &epsilon,
                            const int &maxRecursionDepth);
    ///@brief This method is the adaptive Simpson's method used for
    /// integrating the neutron peak.
    ///@param[in] a : Start of interval
    ///@param[in] b : End of interval
    ///@param[in] epsilon   : Error tolerance
    ///@param[in] S : ?
    ///@param[in] fa    : function evaluated at a
    ///@param[in] fb    : function evaluated at b
    ///@param[in] fc    : function evaluated at midpoint c
    ///@param[in] bottom    : ?
    ///@TODO Better explain what S and bottom are.
    double AdaptiveSimpsonsAux(const double &a,
                               const double &b, const double &epsilon,
                               const double &S, const double &fa,
                               const double &fb, const double &fc,
                               const int &bottom);
    ///@brief This method performs a crystal ball fit of the neutron peak
    ///@param[in] var   : neutron energy value???
    ///@TODO Rename var into something more descriptive.
    double CrystalBall(const double &var);
};
#endif //__INTEGRATOR_HPP__