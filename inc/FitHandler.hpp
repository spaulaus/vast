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
    std::vector<double> GetPeaks(void){return(peaks_);};

    void SetRange(const std::pair<double,double> &a) {rng_ = a;};
    void SetPeaks(const std::vector<double> &a) {peaks_ = a;};
private:
    std::pair<double,double> rng_;
    std::vector<double> peaks_;
};
#endif //__FITHANDLER_HPP__
