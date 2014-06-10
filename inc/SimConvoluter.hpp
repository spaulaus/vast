#ifndef __SIMCONVOLUTER_HPP__
#define __SIMCONVOLUTER_HPP__

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <utility>

//#include <TFile.h>

#include "Configuration.hpp"

class SimConvoluter {
public:
    SimConvoluter(){};
    SimConvoluter(const std::string &cfg);
    ~SimConvoluter(){};
private:
    std::map<double, std::string> energies_;
    std::pair<double,double> rng_, convRng_;
    std::string inputDir_, outputDir_, convHists_, simHists_, fitFile_, convFile_;
    double flightPath_;
    std::string header_ = "#Energy(keV) ToF(ns) sigma sigmaErr alpha alphaErr n nErr";

    double CalcBetaRes(const double &tof);
    void FitMc(const double &en, const double &mu, const double &sigma, 
               const double &alpha, const double &n, std::ofstream &convOut);
    void FitSim(void);
};
#endif //#ifndef __SIMCONVOLUTER_HPP__
