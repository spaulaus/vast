 /***************************************************************************
  *  Copyright S. V. Paulauskas 2012-2014                                  *
  *                                                                        *
  *  This program is free software: you can redistribute it and/or modify  *
  *  it under the terms of the GNU General Public License as published by  *
  *  the Free Software Foundation, version 3.0 License.                    *
  *                                                                        *
  *  This program is distributed in the hope that it will be useful,       *
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
  *  GNU General Public License for more details.                          *
  *                                                                        *
  *  You should have received a copy of the GNU General Public License     *
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
  **************************************************************************
*/
/** \file SimConvoluter.hpp
 * \brief Class to calculate the convoluted simulations from Sergey
 * \author S. V. Paulauskas
 * \date November 01 2013
 * \modified June 09 2014
 */
#ifndef __SIMCONVOLUTER_HPP__
#define __SIMCONVOLUTER_HPP__

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Configuration.hpp"

class SimConvoluter {
public:
    /*! The default constructor */
    SimConvoluter(){};
    /*! Constructor taking the configuration file as input */
    SimConvoluter(const std::string &cfg);
    /*! Destructor for the class (does nothing) */
    ~SimConvoluter(){};
private:
    std::map<double, std::string> energies_;
    std::pair<double,double> rng_, convRng_;
    std::string inputDir_, outputDir_, convHists_, simHists_, fitFile_, convFile_;
    double flightPath_;
    std::string header_ = "#Energy(keV) ToF(ns) sigma sigmaErr alpha alphaErr n nErr";

    /*! Calculate the beta Resoultion as a function of the time of flight */
    double CalcBetaRes(const double &tof);
    /*! Calculate the Convoulted CB parameters */
    void FitMc(const double &en, const double &mu, const double &sigma, 
               const double &alpha, const double &n, std::ofstream &convOut);
    /*! Calculate the fit to the simulated data */
    void FitSim(void);
};
#endif //#ifndef __SIMCONVOLUTER_HPP__
