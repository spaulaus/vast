/** \file BGTCalculator.hpp
 *  \brief A class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __BGTCALCULATOR_HPP__
#define __BGTCALCULATOR_HPP__
#include <map>
#include <string>

#include <Variable.hpp>

#include "Decay.hpp"
#include "ErrorCalculator.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"
#include "Experiment.hpp"

///A class that calculates the B(GT) and log(ft) for a given neutron peak or density
class BGTCalculator {
public:
    /*! The default constructor */
    BGTCalculator(){};
    /*! The constructor used for calculating the neutron densities */
    BGTCalculator(std::map<double,double> &density, const Decay &decay,
                  const Experiment &exp, const std::string &band = "",
                  const Variable &eg = Variable(0.0,1.0,""));
    /*! The constructor used when calculating for a single neutron peak */
    BGTCalculator(Neutron &neutron, const Decay &decay,
                  const Experiment &exp,
                  const Variable &eg = Variable(0.0,0.0,""));
    /*! The default destructor */
    ~BGTCalculator(){};

    /*! Return the map containing the B(GT) */
    std::map<double,double>* GetBgtMap(void){return(&bgtMap_);};
    /*! Return the map containing the Log(ft) */
    std::map<double,double>* GetLogftMap(void){return(&logftMap_);};
    /*! Return the map containing the neutron density */
    std::map<double,double>* GetSDensity(void){return(&sDensity_);};
private:
    Decay decay_;
    Neutron neutron_; 
    ErrorCalculator err;

    Variable betaEff_, geEff_, eG_, eN_, f_, omega_, yld_; 
    std::string band_;
    std::map<double,double> density_, bgtMap_, logftMap_, sDensity_;
    
    Variable CalcBgt(const Variable &en, const Variable &val,
                   const bool &isIndv = true);
    Variable CalcBranchingRatio(const Variable &yld);
    double CalcF(const Variable &en);
    Variable CalcLevelEnergy(const Variable &en);
    Variable CalcLogft(const Variable &en, const Variable &val,
                     const bool &isIndv = true);

    void HandleNeutronDensity(const std::map<double,double> &density);
    void HandleNeutronIndividual(Neutron &neutron);
};
#endif //__BGTCALCULATOR_HPP__
