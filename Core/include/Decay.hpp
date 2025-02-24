/*! \file Decay.hpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __DECAY_HPP__
#define __DECAY_HPP__

#include "HelperEnumerations.hpp"
#include "Variable.hpp"

/*! \brief A class that contains all of the information for the beta decay being
 *  studied.
 *
 * This includes things like the parent nucleus information, the Q value of the
 * reaction and the neutron separation energy.
*/
class Decay {
public:
    /*! The default constructor */
    Decay() {};

    /*! The constructor taking some of the variables as input
     \param [in] z   :  Z of the parent isotope
     \param [in] q   :  Q value of the beta decay
     \param [in] sn  :  neutron separation energy of the decay
     \param [in] qbn :  Qbeta-Sn value for the decay
     \param [in] t   :  half life of the decay
    */
    Decay(const Variable &z, const Variable &q, const Variable &sn, const Variable &qbn, const Variable &t)
            : parentZ_(z), q_(q), qbn_(qbn), neutronSeparationEnergy_(sn), halfLife_(t) {}

    /*! The default destructor */
    ~Decay() {}

    /*! \returns the Z of the beta decay daughter */
    Variable GetDaughterZ(void) const { return daughterZ_; }

    /*! \returns the calculated number of decays */
    Variable GetNumberOfDecays(void) const { return (numDecay_); }

    /*! \returns the Z of the parent nucleus */
    Variable GetParentZ(void) const { return (parentZ_); }

    /*! \returns the half-life of the decay */
    Variable GetHalfLife(void) const { return (halfLife_); }

    /*! \returns the neutron branching ratio  */
    Variable GetNeutronBranchingRatio(void) const { return (neutronBranchingRatio_); }

    /*! \returns the neutron separation energy (S_n) */
    Variable GetNeutronSepEnergy(void) const { return (neutronSeparationEnergy_); }

    /*! \returns the Q value for the reaction */
    Variable GetQValue(void) const { return (q_); }

    /*! \returns the Q value minus the neutron separation energy */
    Variable GetQBetaN(void) const { return (qbn_); }

    /*! Set the information for the normalization gamma line.
     *
     * The normalization gamma line is important so that you can accurately
     * calculate the total number of decays that you had in the run.
     * These are measured quantities for the experiment and will vary from
     * dataset to dataset
     *
     * \param[in] energy: The raw gamma energy in MeV
     * \param[in] yield : Energy of the normalization line
     * \param[in] br : The absolute branching ratio for the normalization gamma
     */
    ///@TODO We need to clean this up so that it's not as ugly.
    void SetNumDecay(const Variable &energy, const Variable &yield, const Variable &br);

    /*!  Set the half-life of the parent nucleus
    * \param[in] a The half-life of the nucleus
    */
    void SetHalfLife(const Variable &a) { halfLife_ = a; }

    /*!  Set the neutron branching ratio
    * \param[in] a The neutron branching ratio
    */
    void SetNeutronBranchingRatio(const Variable &a) { neutronBranchingRatio_ = a; }

    /*!  Set the neutron separation energy
    * \param[in] a The Sn
    */
    void SetNeutronSepEnergy(const Variable &a) { neutronSeparationEnergy_ = a; }

    /*!  Set the parent Z
    * \param[in] a The elemental number
    */
    void SetParentZ(const Variable &a) {
        parentZ_ = a;
        SetDaughterZ();
    }

    /*!  Set the Q value for the reaction
    * \param[in] a The Q value
    */
    void SetQValue(const Variable &a) { q_ = a; }

    /*!  Set the Q value minus the neutron separation energy
    * \param[in] a The Qbeta-Sn
    */
    void SetQBetaN(const Variable &a) { qbn_ = a; }
private:
    Variable daughterZ_, numDecay_, parentZ_, neutronBranchingRatio_, q_, qbn_, neutronSeparationEnergy_, halfLife_;

    ///@brief Sets the Z value of the daughter
    void SetDaughterZ(void) { daughterZ_ = Variable(parentZ_.GetValue() + 1, 0.0, ""); }
};

#endif //__DECAY_HPP__
