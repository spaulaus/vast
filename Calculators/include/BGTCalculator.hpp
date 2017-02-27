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
#include "EffCalculator.hpp"
#include "ErrorCalculator.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"
#include "Experiment.hpp"

///A class that calculates the B(GT) and log(ft) for a given neutron peak or density
class BGTCalculator {
public:
    /*! The default constructor */
    BGTCalculator(){};
    /*! The constructor used for calculating the B(GT)
    *   \param[in] density A map containing the neutron density
    *   \param[in] decay An object of the Decay class
    *   \param[in] exp An object of the Experiment class
    *   \param[in] band The error band that we are calculating
    *   \param[in] eg The energy of the gating gamma (if there is one)
    */
    BGTCalculator(const std::map<double,double> &density, const Decay &decay,
                  const Experiment &exp, const std::string &band = "",
                  const Variable &eg = Variable(0.0,1.0,"MeV"));
    /*! The constructor used when calculating for a single neutron peak
    *   \param[in] neutron An object of Neutron class
    *   \param[in] decay An object of Decay class
    *   \param[in] exp An object of Experiment Class
    *   \param[in] eg The energy of the gating gamma (if there is one)
    */
    BGTCalculator(Neutron &neutron, const Decay &decay,
                  const Experiment &exp,
                  const Variable &eg = Variable(0.0,0.0,""));
    /*! The default destructor */
    ~BGTCalculator(){};

    /*! \return the map containing the B(GT) */
    std::map<double,double>* GetBgtMap(void){return(&bgtMap_);};
    /*! \return the map containing the Log(ft) */
    std::map<double,double>* GetLogftMap(void){return(&logftMap_);};
    /*! \return the map containing the neutron density */
    std::map<double,double>* GetSDensity(void){return(&sDensity_);};
private:
    Decay decay_;
    Neutron neutron_;
    ErrorCalculator err_;
    EffCalculator eff_;

    Variable currentEx_; //!< The excitation energy for the current calculation.

    Variable geEff_, eG_, eN_, f_, omega_, yld_;
    std::string band_;
    std::map<double,double> density_, bgtMap_, logftMap_, sDensity_;

    ///@brief This method calculates the B(GT)
    ///@param[in] en         :Neutron energy
    ///@param[in] isIndv     :bool for specifying single peak
    ///@param[in] val        :variable to hold B(GT) value to be combined with error
    Variable CalcBgt(const Variable &en, const Variable &val,
                   const bool &isIndv = true);
    ///@brief This method calculates the branching ratio
    ///@param[in] en        :Neutron energy
    ///@param[in] yld       :yield
    Variable CalcBranchingRatio(const Variable &en, const Variable &yld);
    ///@brief This method calculates the Fermi integral
    ///@param[in] en        :Neutron Energy
    double CalcF(const Variable &en);
    ///@brief This method calculates the level energy
    ///@param[in] en        :Neutron Energy
    Variable CalcLevelEnergy(const Variable &en);
    ///@brief This method calculates the Log(ft)
    ///@param[in] en : Neutron energy
    ///@param[in] val : Variable to hold Log(ft) value to be combined with error
    ///@param[in] isIndv : Bool for specifying single peak
    Variable CalcLogft(const Variable &en, const Variable &val,
                     const bool &isIndv = true);
    ///@brief This method fills neutron density map variables
    void HandleNeutronDensity(void);
    ///@brief This method fills in info about the neutron into the neutron class
    ///@param[in] neutron   :An object of the neutron class
    void HandleNeutronIndividual(Neutron &neutron);
};
#endif //__BGTCALCULATOR_HPP__