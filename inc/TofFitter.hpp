/** \file ToFFitter.hpp
 *
 *  A class to handle fitting the ToF spectra from VANDLE data
 *
 *  \author S. V. Paulauskas
 *  \date 24 June 2013
 *
 */
#ifndef __TOFFITTER_HPP__
#define __TOFFITTER_HPP__

#include <vector>
#include <map>
#include <string>

#include "RooRealVar.h"

#include <Neutron.hpp>

class TofFitter {
public:
    TofFitter(const std::vector<double> &peaks, const std::string &dir, 
              const std::string &file, const bool &isTest);
    TofFitter(const std::vector<double> &peaks, const std::string &dir, 
              const std::string &file, const std::string &mod, 
              const bool &isTest);
    ~TofFitter(){};
private:
    bool hasConvergence_, hasHesseCalc_;

    std::vector<double> peaks_;

    double low_, high_, wiggle_, detRes_;
    int numPeaks_;
    std::string eps_, output_, dataFile_;

    void CheckFileExistance(void);
    void PerformFit(void);
    void PerformMcStudy(void);

    double CalcAlpha(const double &tof);
    double CalcN(const double &tof);
    double CalcSigma(const double &tof);
}; //class TofFitter
#endif //ifndef __TOFFITTER_HPP__
