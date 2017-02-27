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

#include "CrystalBallParameters.hpp"
#include "FileHandler.hpp"
#include "FitHandler.hpp"
#include "Neutron.hpp"

///A class that handles fitting of the neutron time-of-flight spectra
class TofFitter {
public:
    /*! Default constructor */
    TofFitter() {};

    /*! Perform the fit to the TOF spectrum
     * \param [in] fit : The parameters for the fitting
     * \param [in] fls : the files that will be used for the fitting
     * \param[in] pars : The parameterization for the Crystal Ball */
    TofFitter(const FitHandler &fit, const FileHandler &fls,
              const CrystalBallParameters &pars);

    /*! Default destructor */
    ~TofFitter() {};

    /*! Get the vector of fitted neutrons
    *   \return Vector of neutron peaks */
    std::vector<Neutron> GetFitResults(void) { return (neutrons_); };
private:
    CrystalBallParameters cbPars_;
    FitHandler fit_;
    FileHandler fls_;

    bool hasConvergence_, hasHesseCalc_;
    static constexpr double yStart_ = 3.e3, yLow_ = 0.0, yHigh_ = 1.e8;
    double binning_, wiggle_;
    std::map<std::string, std::pair<double, double> > fitRes_;
    std::pair<double, double> rng_;

    std::string dataFile_, picDir_, eps_, mod_, output_;
    std::vector<double> peaks_;
    std::vector<Neutron> neutrons_;
    std::vector<std::string> components_, yields_, mus_,
            alphas_, sigmas_, ns_;

    ///@brief This method checks that the file needed exists
    void CheckFileExistance(void);
    ///@brief This method generates names of each fit parameter associated
    /// with each peak fit.
    void GenerateNames(void);
    ///@brief This method performs the fit of the ToF
    void PerformFit(void);
    ///@brief This method does a Monte Carlo style study of the fit
    void PerformMcStudy(void);
    ///@brief This method calls the others to mke the fitter run
    void StartRollin(void);
}; //class TofFitter
#endif //ifndef __TOFFITTER_HPP__
