/*! \file LimitFinder.hpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#ifndef __LIMITFINDER_HPP_
#define __LIMITFINDER_HPP_

#include "Neutron.hpp"

//!A class that calculates the sensitivity limit of the detectors
class LimitFinder {
public:
    /*! Default Constructor */
    LimitFinder(){};
    /*! Default Destructor */
    ~LimitFinder(){};

    /*! Perform the fit used to calculate the sensitivity limit
    *  \param[in] edge  : The energy at which to perform the fit
    *  \param[in] yield : The the yield of the neutron peak
    *   \return The neutron information from the fit
    */
    Neutron PerformFit(const double &edge, const double &yield);
};
#endif //__LIMITFINDER_HPP_
