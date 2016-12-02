/** \file Gamma.hpp
 * \brief A class to store information about a gamma
 * \author S. V. Paulauskas
 * \date 24 September 2014
 */
#ifndef __GAMMA_HPP__
#define __GAMMA_HPP__

#include <Variable.hpp>

//!A class to hold information about gammas
class Gamma {
public:
    /*! Default Constructor */
    Gamma() {};

    /*! Constructor setting the energy and calculating efficiency
    *   \param[in] en The gamma energy
    */
    Gamma(const Variable &en);

    /*! Default Destructor */
    ~Gamma() {};

    /*! Set method for gamma energy
    *   \param[in] a Gamma energy
    */
    void SetEnergy(const Variable &a) { en_ = a; };

    /*! Set method for absolute branching ratio
    *   \param[in] a The absolute branching ratio
    */
    void SetAbsoluteBranching(const Variable &a) { abr_ = a; };

    /*! Set method for the gamma detection efficiency
    *   \param[in] a The efficiency
    */
    void SetEfficiency(const Variable &a) { eff_ = a; };

    /*! Set method for the number of singles counts of the gamma line
    *   \param[in] a counts in singles of the line
    */
    void SetArea(const Variable &a) { area_ = a; };
private:
    Variable abr_, area_, eff_, en_;
};

#endif // __GAMMA_HPP__
