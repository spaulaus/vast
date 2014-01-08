/** \file Experiment.hpp
 * \brief A class to handle information about the experiment
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __EXPERIMENT_HPP__
#define __EXPERIMENT_HPP__

#include <Variable.hpp>

class Experiment {
public:
    Experiment(){};
    ~Experiment(){};

    Variable GetBetaEff(void) const {return(betaEff_);};
    Variable GetDensityRes(void) const {return (denRes_);};
    Variable GetNumBars(void) const {return(numBars_);};
    Variable GetOmegaPerBar(void) const {return(omegaPerBar_);};

    void SetBetaEff(const Variable &a) {betaEff_ = a;};
    void SetDensityRes(const Variable &a) {denRes_ = a;};
    void SetNumBars(const Variable &a) {numBars_ = a;};
    void SetOmegaPerBar(const Variable &a) {omegaPerBar_ = a;};
private:
    Variable betaEff_, denRes_, numBars_, omegaPerBar_;
};
#endif //__EXPERIMENT_HPP__
