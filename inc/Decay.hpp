/*! \file Decay.hpp
 *  \brief A class that handles all the information about the beta decay
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __DECAY_HPP__
#define __DECAY_HPP__
#include <Variable.hpp>

/*! \brief A class that contains all of the information for the beta decay being
 *  studied.
 *
 * This includes things like the parent nucleus information, the Q value of the
 * reaction and the neutron separation energy.
*/
class Decay{
public:
    /*! The default constructor */
    Decay(){};
    /*! The constructor taking some of the variables as input
     \param [in] z   :  Z of the parent isotope
     \param [in] q   :  Q value of the beta decay
     \param [in] sn  :  neutron separation energy of the decay
     \param [in] qbn :  Qbeta-Sn value for the decay
     \param [in] t   :  half life of the decay
    */
    Decay(const Variable &z, const Variable&q, const Variable &sn,
          const Variable &qbn, const Variable &t);
    /*! The default destructor */
    ~Decay(){};

    /*! \returns the Z of the beta decay daughter */
    Variable GetDaughterZ(void) const {return(dauZ_);};
    /*! \returns the calculated number of decays */
    Variable GetNumberDecays(void) const {return(numDecay_);};
    /*! \returns the Z of the parent nucleus */
    Variable GetParentZ(void) const {return(parZ_);};
    /*! \returns the half-life of the decay */
    Variable GetHalfLife(void) const {return(t_);};
    /*! \returns the neutron branching ratio  */
    Variable GetNeutronBR(void) const {return(pn_);};
    /*! \returns the neutron separation energy (S_n) */
    Variable GetNeutronSepEnergy(void) const {return(sn_);};
    /*! \returns the Q value for the reaction */
    Variable GetQValue(void) const {return(q_);};
    /*! \returns the Q value minus the neutron separation energy */
    Variable GetQBetaN(void) const {return(qbn_);};

    /*! Set the information for the normalization gamma line.
     *
     * The normalizaton gamma line is important so that you can accurately
     * calculate the total number of decays that you had in the run.
     * These are measured quantities for the experiment and will vary from
     * dataset to dataset
     *
     * \param[in] rawG : The raw gamma energy in keV
     * \param[in] gEff : The efficiency for the gamma used to normalize
     * \param[in] br   : The absolute branching ratio for the normalization gamma
     */
    void SetNormInfo(const Variable &rawG, const Variable &gEff,
                      const Variable &br);
    /*!  Set the half-life of the parent nucleus
    * \param[in] a The half-life of the nucleus
    */
    void SetHalfLife(const Variable &a){t_ = a;};
    /*!  Set the neutron branching ratio
    * \param[in] a The neutron branching ratio
    */
    void SetNeutronBR(const Variable &a){pn_ = a;};
    /*!  Set the neutron separation energy
    * \param[in] a The Sn
    */
    void SetNeutronSepEnergy(const Variable &a){sn_ = a;};
    /*!  Set the parent Z
    * \param[in] a The elemental number
    */
    void SetParentZ(const Variable &a){parZ_ = a; SetDaughterZ();};
    /*!  Set the Q value for the reaction
    * \param[in] a The Q value
    */
    void SetQValue(const Variable &a){q_ = a;};
    /*!  Set the Q value minus the neutron separation energy
    * \param[in] a The Qbeta-Sn
    */
    void SetQBetaN(const Variable &a){qbn_ = a;};
private:
    Variable gBr_, dauZ_, numDecay_, parZ_, pn_,
        q_, qbn_, sn_, t_, rawG_, gEff_;

    void CalcNumberDecays(void);
    void SetDaughterZ(void) {dauZ_ = Variable(parZ_.GetValue()+1,0.0,"");};
};
#endif //__DECAY_HPP__
