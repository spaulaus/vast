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
      \param[in] file : the output filename
    */
    void OutputBasics(std::vector<Neutron> &nvec, Decay &dky,
                      Experiment &exp, const std::string &file);
    /*! Output the neutrond density information
      \param[in] nvec : the vector of neutron events to output
      \param[in] dky  : the decay information
      \param[in] exp  : the experimental information
      \param[in] file : the output filename
    */
    void OutputDensity(std::vector<Neutron> &nvec, Decay &dky,
                       Experiment &exp, const std::string &file);
    /*! Output in the format for the CGM calculations
      \param[in] nvec : the vector of neutron events to output
      \param[in] file : the output filename
    */
    void OutputTheory(std::vector<Neutron> &nvec, const std::string &file);
};
#endif //__OUTPUTHANDLER_HPP__
