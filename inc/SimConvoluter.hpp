#ifndef __SIMCONVOLUTER_HPP__
#define __SIMCONVOLUTER_HPP__

#include <fstream>
#include <string>
#include <vector>
#include <utility>

class SimConvoluter {
public:
    SimConvoluter(const std::vector<std::string> &names, 
                  const std::string &dir, const std::pair<double,double> &rng);
    ~SimConvoluter(){};
private:
    std::pair<double,double> rng_;
    std::string dir_, header_;
    std::vector<std::string> names_;

    double CalcBetaRes(const double &tof);
    
    void FitMc(const std::string &name, const double &mu, const double &sigma, 
                   const double &alpha, const double &n, std::ofstream &convOut);
    void FitSim(void);
};
#endif //#ifndef __SIMCONVOLUTER_HPP__
