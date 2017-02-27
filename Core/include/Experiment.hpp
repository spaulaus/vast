/** \file Experiment.hpp
 * \brief A class to handle information about the experiment
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __EXPERIMENT_HPP__
#define __EXPERIMENT_HPP__

#include <Variable.hpp>

#include "EffCalculator.hpp"

///A class that describes the various components of the experimental setup
class Experiment {
public:
    /*! Default Constructor */
    Experiment() {};

    /*! Default Destructor */
    ~Experiment() {};

    /*! \return the beta efficiency */
    Variable GetBetaEff(void) const { return (betaEff_); };

    /*! \return the resolution of the neutron density spikes */
    Variable GetDensityRes(void) const { return (denRes_); };

    /*! \return the number of bars in the experiment (analysis) */
    Variable GetNumBars(void) const { return (numBars_); };

    /*! \return the solid angle covered by a single bar */
    Variable GetOmegaPerBar(void) const { return (omegaPerBar_); };

    /*! \return the flight path for the neutrons */
    Variable GetFlightPath(void) const { return (flightPath_); };

    /*! \return the efficiency curved used in the analysis */
    EffCalculator::EffTypes
    GetEfficiencyCurveName(void) const { return (effType_); };

    /*! Set the efficiency of the beta detector
    *   \param [in] a the beta efficiency */
    void SetBetaEff(const Variable &a) { betaEff_ = a; };

    /*! Set the resolution of the density spikes
    *   \param [in] a The resolution */
    void SetDensityRes(const Variable &a) { denRes_ = a; };

    /*! Set the number of bars in the experiment (analysis)
    *   \param [in] a The number of bars */
    void SetNumBars(const Variable &a) { numBars_ = a; };

    /*! Set the solid angle covered by a single bar
    *   \param [in] a The solid angle */
    void SetOmegaPerBar(const Variable &a) { omegaPerBar_ = a; };

    /*! Set the flight path of the neutron
    *   \param [in] a : the flight path */
    void SetFlightPath(const Variable &a) { flightPath_ = a; };

    /*! Set the efficiency curve that we used in the analysis
    *   \param [in] a : The name of the efficiency curve to use */
    void
    SetEfficiencyCurveName(const EffCalculator::EffTypes &a) { effType_ = a; };
private:
    Variable betaEff_, denRes_, numBars_, omegaPerBar_, flightPath_;
    EffCalculator::EffTypes effType_;
};

#endif //__EXPERIMENT_HPP__
