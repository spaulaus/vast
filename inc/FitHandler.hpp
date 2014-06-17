/** \file FitHandler.hpp
 * \brief A class to handle the fitting information (peaks and whatnot)
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __FITHANDLER_HPP__
#define __FITHANDLER_HPP__
#include <string>
#include <utility>
#include <vector>

///A class that handles the input fitting information for the neutron spectra
class FitHandler {
public:
    FitHandler(){};
    ~FitHandler(){};

    double GetBinning(void) const {return(bin_);};
    double GetWiggle(void) const {return(wiggle_);};
    std::pair<double,double> GetRange(void) const {return(rng_);};
    std::string GetPeakList(void) const {return(pkLst_);};
    std::vector<double> GetSnglPeaks(void) const {return(snglPeaks_);};
    std::vector<double> GetGate1Peaks(void) const {return(g1Peaks_);};
    std::vector<double> GetGate2Peaks(void)const {return(g2Peaks_);};

    void SetBinning(const double &a) {bin_ = a;};
    void SetPeakList(const std::string &a) {pkLst_ = a;};
    void SetRange(const std::pair<double,double> &a) {rng_ = a;};
    void SetSnglPeaks(const std::vector<double> &a) {snglPeaks_ = a;};
    void SetGate1Peaks(const std::vector<double> &a) {g1Peaks_ = a;};
    void SetGate2Peaks(const std::vector<double> &a) {g2Peaks_ = a;};
    void SetWiggle(const double &a) {wiggle_ = a;};

    double CalcAlpha(const double &tof);
    double CalcN(const double &tof);
    double CalcSigma(const double &tof);
private:
    std::pair<double,double> rng_;
    std::vector<double> snglPeaks_, g1Peaks_, g2Peaks_;

    std::string pkLst_;

    double bin_, wiggle_;
    double aI_, aH_, nJ_, nK_, nL_, sM_, sN_, sO;
};
#endif //__FITHANDLER_HPP__
