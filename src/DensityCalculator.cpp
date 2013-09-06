/** \file DensityCalculator.cpp
 *  \brief A code to calculate the neutron density spectrum
 *  \author S. V. Paulauskas
 *  \date 06 September 2013
 */
#include <iostream>

#include "DensityCalculator.hpp"

using namespace std;

DensityCalculator::DensityCalculator(Neutron &neutron, const double &res, 
                                     const double &len) {
    sig_.SetSignalType("gaussian");
    sig_.SetAmplitude(neutron.GetIntegratedYield());
    sig_.SetSigma(neutron.GetEnergyErr());
    sig_.SetDelay(neutron.GetEnergy());
    sig_.SetSignalResolution(res);
    sig_.SetSignalLength(len);
    sig_.GenerateSignal();
    signal_ = sig_.GetSignal();
}
