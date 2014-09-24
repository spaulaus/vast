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

    /*! \return The binning of the ToF histograms */
    double GetBinning(void) const {return(bin_);};
    /*! \return The acceptable wiggle (in ns) of the neutron peaks */
    double GetWiggle(void) const {return(wiggle_);};
    /*! \return the range of the fit */
    std::pair<double,double> GetRange(void) const {return(rng_);};
    /*! \return the list of peaks used in the fit */
    std::string GetPeakList(void) const {return(pkLst_);};
    /*! \return the peaks used in the singles fit */
    std::vector<double> GetSnglPeaks(void) const {return(snglPeaks_);};
    /*! \return the peaks used in the gamma gated spectrum */
    std::vector<double> GetGate1Peaks(void) const {return(g1Peaks_);};
    /*! \return the peaks used in the gamma gated spectrum */
    std::vector<double> GetGate2Peaks(void)const {return(g2Peaks_);};

    /*! Set the amount of binning on the TOF histograms
    *   \param[in] a The binning of the histograms
    */
    void SetBinning(const double &a) {bin_ = a;};
    /*! Set the peaks to be fit in the singles spectrum
    *   \param[in] a The peak list to use for the fits
    */
    void SetPeakList(const std::string &a) {pkLst_ = a;};
    /*! Set the fitting range
    *   \param[in] a The range that the fit should be performed in
    */
    void SetRange(const std::pair<double,double> &a) {rng_ = a;};
    /*! Set the peaks used in the singles fits
    *   \param[in] a The peaks that should be used to perform the singles fit
    */
    void SetSnglPeaks(const std::vector<double> &a) {snglPeaks_ = a;};
    /*! Set the peaks used in the gamma gated fit
    *   \param[in] a The peaks that should be used for the gated fit
    */
    void SetGate1Peaks(const std::vector<double> &a) {g1Peaks_ = a;};
    /*! Set the peaks used in the gamma gated fit
    *   \param[in] a The peaks to be used in the gated fit
    */
    void SetGate2Peaks(const std::vector<double> &a) {g2Peaks_ = a;};
    /*! Set the amount that the pekas are allowed to wiggle during the fit
    *   \param[in] a The wiggle of the neutron peak
    */
    void SetWiggle(const double &a) {wiggle_ = a;};

    /*! Calculate the alpha parameter for a given TOF
    *   \param[in] tof The ToF
    *   \return The alpha parameter for the CB
    */
    double CalcAlpha(const double &tof);
    /*! Calculate the n parameter for a given TOF
    *   \param[in] tof The ToF
    *   \return The n parameter of the CB
    */
    double CalcN(const double &tof);
    /*! Calculate the sigma for a given TOF
    *   \param[in] tof The ToF
    *   \return The sigma of the Gaussian from the CB
    */
    double CalcSigma(const double &tof);
private:
    std::pair<double,double> rng_;
    std::vector<double> snglPeaks_, g1Peaks_, g2Peaks_;

    std::string pkLst_;

    double bin_, wiggle_;
    double aI_, aH_, nJ_, nK_, nL_, sM_, sN_, sO;
};
#endif //__FITHANDLER_HPP__
