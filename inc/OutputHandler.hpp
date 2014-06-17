/** \file OutputHandler.cpp
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
    OutputHandler(){};
    ~OutputHandler(){};

    void OutputBasics(std::vector<Neutron> &nvec, Decay &dky, 
                      Experiment &exp, const std::string &file);
    void OutputDensity(std::vector<Neutron> &nvec, Decay &dky,
                       Experiment &exp, const std::string &file);
    void OutputTheory(std::vector<Neutron> &nvec, const std::string &file);
};
#endif //__OUTPUTHANDLER_HPP__
