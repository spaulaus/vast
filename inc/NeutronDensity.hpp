/*! \file NeutronDensity.hpp
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

//! A class that contains information about the neutron density.
class NeutronDensity {
public:
    /*! Default Constructor */
    NeutronDensity(){};
    /*! Constructor taking the vector of neutrons and other info
      \param[in] neutrons : the vector of neutron peaks
      \param[in] len      : the length of the vector for the density
      \param[in] res      : the resolution of the density
      \param[in] ge       : the energy of the gamma for gamma gated peaks */
    NeutronDensity(std::vector<Neutron> &neutrons, const double &qbetan,
                   const Variable &ge = Variable(0.0,0.0,""));
    /*! Default destructor */
    ~NeutronDensity(){};

    /*! \return Returns the neutron density */
    const std::map<double,double>* GetDensity(void) const {return(&denMean_);};
    /*! \return Returns the lower error bar for the neutron density */
    const std::map<double,double>* GetDensityLow(void) const {return(&denLow_);};
    /*! \return Returns the upper error bar for the neutron density */
    const std::map<double,double>* GetDensityHigh(void) const {return(&denHigh_);};
private:
    double qbetan_;//!< The maximum energy value to calculate up to
    double amplitude_;//!< the amplitude of the Gaussian Function
    double mu_;//!< The mean of the Gaussian Function
    double sigma_;//! The Sigma of the Gaussian Function
    std::map<double,double> denMean_, denLow_, denHigh_;
    std::vector<Neutron> neutrons_;

    void CalcDensity(const Variable &ge, const Variable &geEff);
    double Gaussian(const double &x);
};

#endif //__NEUTRONDENSITY_HPP__
