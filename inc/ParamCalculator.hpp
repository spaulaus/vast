/** \file ParamCalculator.hpp
 *  \brief A class to calculate the parameterized alpha,n, and sigma for CBs
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#ifndef __PARAMCALCULATOR_HPP_
#define __PARAMCALCULATOR_HPP_

///A class to calculate the parameterized alpha, n, and sigma for CBs
class ParamCalculator {
public:
    /*! Default constructor */
    ParamCalculator(){};
    /*! Default destructor */
    ~ParamCalculator(){};

    /*! Calculate the alpha parameter from the CB */
    double CalcAlpha(const double &tof);
    /*! Calculate the n parameter for the CB */
    double CalcN(const double &tof);
    /*! Calculate the sigma parameter for the CB */
    double CalcSigma(const double &tof);
private:
    double aI_, aH_, nJ_, nK_, nL_, sM_, sN_, sO;
};

#endif //__PARAMCALCULATOR_HPP_
