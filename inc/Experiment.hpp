/** \file Experiment.hpp
 * \brief A class to handle information about the experiment
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __EXPERIMENT_HPP__
#define __EXPERIMENT_HPP__

#include <Variable.hpp>

///A class that describes the various components of the experimental setup
class Experiment {
public:
    /*! Default Constructor */
    Experiment(){};
    /*! Default Destructor */
    ~Experiment(){};

    /*! Returns the beta efficiency */
    Variable GetBetaEff(void) const {return(betaEff_);};
    /*! Returns the resolution of the neutron density spikes */
    Variable GetDensityRes(void) const {return (denRes_);};
    /*! Returns the number of bars in the experiment (analysis) */
    Variable GetNumBars(void) const {return(numBars_);};
    /*! Returns the solid angle covered by a single bar */
    Variable GetOmegaPerBar(void) const {return(omegaPerBar_);};

    /*! Set the efficiency of the beta detector */
    void SetBetaEff(const Variable &a) {betaEff_ = a;};
    /*! Set the resolution of the density spikes */
    void SetDensityRes(const Variable &a) {denRes_ = a;};
    /*! Set the number of bars in the experiment (analysis)*/
    void SetNumBars(const Variable &a) {numBars_ = a;};
    /*! Set the solid angle covered by a single bar */
    void SetOmegaPerBar(const Variable &a) {omegaPerBar_ = a;};
private:
    Variable betaEff_, denRes_, numBars_, omegaPerBar_;
};
#endif //__EXPERIMENT_HPP__
