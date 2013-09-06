/** \file DensityCalculator.hpp
 *  \brief A code to calculate the neutron density spectrum
 *  \author S. V. Paulauskas
 *  \date 06 September 2013
 */
#ifndef __DENSITYCALCULATOR_HPP__
#define __DENSITYCALCULATOR_HPP__

#include <vector>

#include <SignalGenerator.hpp>

#include "Neutron.hpp"

class DensityCalculator {
public:
    DensityCalculator(){};
    DensityCalculator(Neutron &neutron, const double &res,
                      const double &len);
    ~DensityCalculator(){};
    
    std::vector<double>* GetDensity(void) {return(signal_);};

private:
    SignalGenerator sig_;
    std::vector<double> *signal_;
};
#endif //__DENSITYCALCULATOR_HPP__
