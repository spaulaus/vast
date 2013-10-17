/** \file TofFitter.hpp
 * \brief A class to store information about the fitted peaks
 * \author S. V. Paulauskas
 * \date 06 October 2013
 */
#ifndef __TOFFITTER_HPP__
#define __TOFFITTER_HPP__

#include <map>
#include <string>
#include <vector>

#include <Neutron.hpp>

class TofFitter {
public:
    TofFitter(const std::vector<double> &peaks, const std::string &dir, 
              const std::string &file, const std::pair<double,double> &range,
              const bool &isTest = false);
    TofFitter(const std::vector<double> &peaks, const std::string &dir, 
              const std::string &file, const std::string &mod, 
              const std::pair<double,double> &range, const bool &isTest = false);
    ~TofFitter(){};

    std::vector<Neutron> GetFitResults(void){return(neutrons_);};
private:
    bool hasConvergence_, hasHesseCalc_;
    double binning_, wiggle_;
    static constexpr double yStart_=3.e3, yLow_ = 0.0, yHigh_ = 1.e8;
    std::map<std::string,std::pair<double,double> > fit_;
    std::pair<double,double> rng_;
    std::string dataFile_, dir_, eps_, mod_, output_;
    std::vector<double> peaks_;
    std::vector<Neutron> neutrons_;
    std::vector<std::string> components_, yields_, mus_, 
        alphas_, sigmas_, ns_;

    void CheckFileExistance(void);
    void GenerateNames(void);
    void PerformFit(void);
    void PerformMcStudy(void);
    void StartRollin(void);

    double CalcAlpha(const double &tof);
    double CalcN(const double &tof);
    double CalcSigma(const double &tof);
}; //class TofFitter
#endif //ifndef __TOFFITTER_HPP__
