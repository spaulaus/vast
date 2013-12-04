/** \file FitHandler.hpp
 * \brief A class to handle the fitting information (peaks and whatnot)
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __FITHANDLER_HPP__
#define __FITHANDLER_HPP__
#include <vector>
#include <utility>

class FitHandler {
public:
    FitHandler(){};
    ~FitHandler(){};

    std::pair<double,double> GetRange(void){return(rng_);};
    std::vector<double> GetSnglPeaks(void){return(snglPeaks_);};
    std::vector<double> GetGate1Peaks(void){return(g1Peaks_);};
    std::vector<double> GetGate2Peaks(void){return(g2Peaks_);};

    void SetRange(const std::pair<double,double> &a) {rng_ = a;};
    void SetSnglPeaks(const std::vector<double> &a) {snglPeaks_ = a;};
    void SetGate1Peaks(const std::vector<double> &a) {g1Peaks_ = a;};
    void SetGate2Peaks(const std::vector<double> &a) {g2Peaks_ = a;};
private:
    std::pair<double,double> rng_;
    std::vector<double> snglPeaks_, g1Peaks_, g2Peaks_;
};
#endif //__FITHANDLER_HPP__
