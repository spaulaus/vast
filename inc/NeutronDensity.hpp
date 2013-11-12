/** \file NeutronDensity.hpp
 *  \brief A class that contains information about the neutron density.
 *  \author S. V. Paulauskas
 *  \date 07 September 2013
 */
#ifndef __NEUTRONDENSITY_HPP__
#define __NEUTRONDENSITY_HPP__

#include <map>
#include <vector>

#include <Variable.hpp>

#include "Neutron.hpp"

class NeutronDensity {
public:
    NeutronDensity(){};
   NeutronDensity(std::vector<Neutron> &neutrons, const double &len,
                  const double &res, 
                  const Variable &ge = Variable(0.0,0.0,""));
    ~NeutronDensity(){};
    
    std::map<double,double>* GetDensity(void){return(&denMean_);};
    std::map<double,double>* GetDensityLow(void){return(&denLow_);};
    std::map<double,double>* GetDensityHigh(void){return(&denHigh_);};
private:
    double len_, res_;
    std::map<double,double> denMean_, denLow_, denHigh_;
    std::vector<Neutron> neutrons_;

    void CalcDensity(const Variable &ge, const Variable &geEff);
};

#endif //__NEUTRONDENSITY_HPP__
