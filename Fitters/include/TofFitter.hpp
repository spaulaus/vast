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

#include "FileHandler.hpp"
#include "FitHandler.hpp"
#include "Neutron.hpp"
#include "ParamCalculator.hpp"

///A class that handles fitting of the neutron time-of-flight spectra
class TofFitter {
public:
    /*! Default constructor */
    TofFitter() {};

    /*! Perform the fit to the TOF spectrum
     * \param [in] fit : The parameters for the fitting
     * \param [in] fls : the files that will be used for the fitting
     * \param[in] params : The parameterization for the Crystal Ball */
    TofFitter(const FitHandler &fit, const FileHandler &fls);

    /*! Default destructor */
    ~TofFitter() {};

    /*! Get the vector of fitted neutrons
    *   \return Vector of neutron peaks */
    std::vector<Neutron> GetFitResults(void) { return (neutrons_); };
private:
    ParamCalculator par_;
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

    void CheckFileExistance(void);

    void GenerateNames(void);

    void PerformFit(void);

    void PerformMcStudy(void);

    void StartRollin(void);
}; //class TofFitter
#endif //ifndef __TOFFITTER_HPP__
