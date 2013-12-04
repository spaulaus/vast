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

    Variable GetBetaEff(void){return(betaEff_);};
    Variable GetNumBars(void){return(numBars_);};
    Variable GetOmegaPerBar(void){return(omegaPerBar_);};

    void SetBetaEff(const Variable &a) {betaEff_ = a;};
    void SetNumBars(const Variable &a) {numBars_ = a;};
    void SetOmegaPerBar(const Variable &a) {omegaPerBar_ = a;};
private:
    Variable betaEff_, numBars_, omegaPerBar_;
};
#endif //__EXPERIMENT_HPP__
