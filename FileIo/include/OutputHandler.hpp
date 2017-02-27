/*! \file OutputHandler.hpp
 *  \brief Handles the outputting of information for various formats/files
 *  \author S. V. Paulauskas
 *  \date 10 December 2013
 */
#ifndef __OUTPUTHANDLER_HPP_
#define __OUTPUTHANDLER_HPP_
#include <vector>
#include <string>

#include <Variable.hpp>

#include <TH1D.h>

#include "Decay.hpp"
#include "Experiment.hpp"
#include "Neutron.hpp"

///A class that handles outputting information from the various classes
class OutputHandler {
public:
    /*! Default constructor */
    OutputHandler(){};
    /*! Default destructor */
    ~OutputHandler(){};

    /*! Output the basic information
      \param[in] nvec : the vector of neutron events to output
      \param[in] dky  : the decay information
      \param[in] exp  : the experimental information
      \param[in] file : the output filename */
    void OutputBasics(std::vector<Neutron> &nvec, Decay &dky,
                      Experiment &exp, const std::string &file);
    /*! Output the neutron density information
      \param[in] nvec : the vector of neutron events to output
      \param[in] dky  : the decay information
      \param[in] exp  : the experimental information
      \param[in] file : the output filename */
    void OutputDensity(const NeutronDensity &nden, const Decay &dky,
                      const Experiment & exp, const std::string &file);
    /*! Output in the format for the CGM calculations
      \param[in] nvec : the vector of neutron events to output
      \param[in] file : the output filename     */
    void OutputTheory(std::vector<Neutron> &nvec, const std::string &file);
private:
    double resolution_; //!< The resolution of the histograms
    static constexpr double minEnergy_ = 0.; //!<The Minimum energy that we'll use for the hists
    static constexpr double maxEnergy_ = 15.; //!<The Maximum energy that we'll use for the hists

    ///@brief This method returns if the value is not nan or infinity
    ///@param[in] val   : value to be checked
    ///@TODO Rename val to something more descriptive
    bool NotInfOrNan(const double &val);
    ///@brief This method fills the ROOT histogram
    ///@param[in] data  : Data to fill the histogram
    ///@param[in] hist  : 1D ROOT histogram
    ///@TODO Better description for what data variable is
    void FillHistogram(TH1D &hist, const std::map<double,double> &data);
    ///@brief This method sets various options for the ROOT histgram
    ///@param[in] hist  : 1D ROOT histogram
    ///@param[in] type  : variable to hold histogram type
    void SetHistOptions(TH1D &hist, const std::string &type);
};
#endif //__OUTPUTHANDLER_HPP__
