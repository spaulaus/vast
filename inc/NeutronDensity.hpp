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

/// A class that contains information about the neutron density.
class NeutronDensity {
public:
    /*! Default Constructor */
    NeutronDensity(){};
    /*! Constructor taking the vector of neutrons and other info 
      \param[in] neutrons : the vector of neutron peaks
      \param[in] len      : the length of the vector for the density
      \param[in] res      : the resolution of the density 
      \param[in] ge       : the energy of the gamma for gamma gated peaks 
    */
    NeutronDensity(std::vector<Neutron> &neutrons, const double &len,
                   const double &res, 
                   const Variable &ge = Variable(0.0,0.0,""));
    /*! Default destructor */
    ~NeutronDensity(){};
    
    /*! Returns the neutron density */
    const std::map<double,double>* GetDensity(void) const {return(&denMean_);};
    /*! Returns the lower bound of the neutron density error band */
    const std::map<double,double>* GetDensityLow(void) const {return(&denLow_);};
    /*! returns the upper bound of the neutron density error band */
    const std::map<double,double>* GetDensityHigh(void) const {return(&denHigh_);};
private:
    double len_, res_;
    std::map<double,double> denMean_, denLow_, denHigh_;
    std::vector<Neutron> neutrons_;

    void CalcDensity(const Variable &ge, const Variable &geEff);
};

#endif //__NEUTRONDENSITY_HPP__
