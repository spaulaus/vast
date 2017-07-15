///@file ResponseFunctionAnalyzer.hpp
///@brief Class to calculate the convoluted simulations from Sergey
///@author S. V. Paulauskas
///@date November 1, 2013
///@copyright Copyright (c) 2013-2017 S. V. Paulauskas.
///@copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#ifndef __RESPONSEFUNCTIONANALYZER_HPP__
#define __RESPONSEFUNCTIONANALYZER_HPP__

#include <map>
#include <string>

#include "XmlInterface.hpp"

///A class to perform the analysis and convolution of the simulated data.
class ResponseFunctionAnalyzer {
public:
    ///Constructor
    ResponseFunctionAnalyzer() {};

    ///Constructor taking the configuration node
    ///@param[in] cfg : The name of the configuration file to use for the fitting
    ResponseFunctionAnalyzer(const pugi::xml_node &base);

    ///Destructor
    ~ResponseFunctionAnalyzer() {};
private:
    std::map<double, std::string> energies_;
    std::pair<double, double> rng_, convRng_;
    std::string inputDir_, outputDir_, simHists_, fitFile_, convFile_;
    double flightPath_;
    std::string header_ = "#Energy(keV) ToF(ns) sigma sigmaErr alpha alphaErr n nErr";

    ///Calculate the beta Resolution as a function of the time of flight
    double CalcBetaRes(const double &tof);

    ///Calculate the convoluted CB parameters
    void FitMc(const double &en, const double &mu, const double &sigma,
               const double &alpha, const double &n, std::ofstream &convOut);

    ///Calculate the fit to the simulated data
    void FitSim(void);
};

#endif //#ifndef __ResponseFunctionAnalyzer_HPP__
