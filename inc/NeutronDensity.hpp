/** \file NeutronDensity.hpp
 *  \brief A class that contains information about the neutron density.
 *  \author S. V. Paulauskas
 *  \date 07 September 2013
 */
#ifndef __NEUTRONDENSITY_HPP__
#define __NEUTRONDENSITY_HPP__

#include <map>
#include <vector>

#include "Neutron.hpp"

class NeutronDensity {
public:
    NeutronDensity(){};
    NeutronDensity(std::vector<Neutron> &neutrons, const double &len,
                   const double &res, const double &ge = 0);
    ~NeutronDensity(){};
    
    std::map<double,double>* GetDensity(void){return(&density_);};
private:
    double len_, res_;
    std::map<double,double> density_;
    std::vector<Neutron> neutrons_;

    void CalcDensity(const double &ge, const double &geEff);
};

#endif //__NEUTRONDENSITY_HPP__
