/** \file NeutronDensity.hpp
 *  \brief A class that contains information about the neutron density.
 *  \author S. V. Paulauskas
 *  \date 07 September 2013
 */
#ifndef __NEUTRONDENSITY_HPP__
#define __NEUTRONDENSITY_HPP__

#include <vector>

#include "Neutron.hpp"

class NeutronDensity {
public:
    NeutronDensity(){};
    NeutronDensity(std::vector<Neutron> &neutrons, const double &res, 
                   const double &len);
    NeutronDensity(std::vector<Neutron> &neutrons, const double &res,
                   const double &len, const double &ge);
    ~NeutronDensity(){};
    
    std::vector<double>* GetDensity(void){return(&density_);};

    unsigned int GetDensitySize(void){return(density_.size());};

private:
    double gE_, gEff_, len_, res_;
    std::vector<double> density_;
    std::vector<Neutron> neutrons_;
    
    void CalcDensity(void);
};

#endif //__NEUTRONDENSITY_HPP__
