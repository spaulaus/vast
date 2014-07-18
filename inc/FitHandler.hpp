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
    /*! Default constructor */
    FitHandler(){};
    /*! Default Destructor */
    ~FitHandler(){};

    /*! Return the binning of the TOF histograms*/
    double GetBinning(void) const {return(bin_);};
    /*! Return the amount that the neutron peaks are allowed to wiggle in the 
      fit */
    double GetWiggle(void) const {return(wiggle_);};
    /*! Return the range of the fit */
    std::pair<double,double> GetRange(void) const {return(rng_);};
    /*! Return the list of peaks used in the fit */
    std::string GetPeakList(void) const {return(pkLst_);};
    /*! Return the peaks used in the singles fit */
    std::vector<double> GetSnglPeaks(void) const {return(snglPeaks_);};
    /*! Return the peaks used in the gamma gated spectrum */
    std::vector<double> GetGate1Peaks(void) const {return(g1Peaks_);};
    /*! Return the peaks used in the gamma gated spectrum */
    std::vector<double> GetGate2Peaks(void)const {return(g2Peaks_);};

    /*! Set the amount of binning on the TOF histograms */
    void SetBinning(const double &a) {bin_ = a;};
    /*! Set the peaks to be fit in the singles spectrum */
    void SetPeakList(const std::string &a) {pkLst_ = a;};
    /*! Set the fitting range */
    void SetRange(const std::pair<double,double> &a) {rng_ = a;};
    /*! Set the peaks used in the singles fits */
    void SetSnglPeaks(const std::vector<double> &a) {snglPeaks_ = a;};
    /*! Set the peaks used in the gamma gated fit */
    void SetGate1Peaks(const std::vector<double> &a) {g1Peaks_ = a;};
    /*! Set the peaks used in the gamma gated fit */
    void SetGate2Peaks(const std::vector<double> &a) {g2Peaks_ = a;};
    /*! Set the amount that the pekas are allowed to wiggle during the fit */
    void SetWiggle(const double &a) {wiggle_ = a;};

    /*! Calculate the alpha parameter for a given TOF */
    double CalcAlpha(const double &tof);
    /*! Calculate the n parameter for a given TOF */
    double CalcN(const double &tof);
    /*! Calculate the sigma for a given TOF */
    double CalcSigma(const double &tof);
private:
    std::pair<double,double> rng_;
    std::vector<double> snglPeaks_, g1Peaks_, g2Peaks_;

    std::string pkLst_;

    double bin_, wiggle_;
    double aI_, aH_, nJ_, nK_, nL_, sM_, sN_, sO;
};
#endif //__FITHANDLER_HPP__
