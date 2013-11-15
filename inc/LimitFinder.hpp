/** \file LimitFinder.hpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#ifndef __LIMITFINDER_HPP_
#define __LIMITFINDER_HPP_

#include "Neutron.hpp"

class LimitFinder {
public:
    LimitFinder(){};
    ~LimitFinder(){};

    Neutron PerformFit(const double &edge, const double &yield);
};
#endif //__LIMITFINDER_HPP_
