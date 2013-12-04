/** \file Configuration.hpp
 * \brief A class to handle the configuration xml
 * \author S. V. Paulauskas
 * \date 30 November 2013
 */
#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__
#include <string>

#include "Decay.hpp"
#include "Experiment.hpp"
#include "FileHandler.hpp"
#include "FlagHandler.hpp"
#include "FitHandler.hpp"

#include <pugixml.hpp>

class Configuration {
public:
    Configuration(void){};
    Configuration(const std::string &file);
    ~Configuration(void){};

    Decay ReadDecay(void);
    Experiment ReadExperiment(void);
    FileHandler ReadFiles(void);
    FlagHandler ReadFlags(void);
    FitHandler ReadFit(void);
private:
    pugi::xml_document doc_;
    pugi::xml_node cfg_;
    std::string file_;

    Variable NodeToVar(const pugi::xml_node &node);
    void SpitWarning(const std::string &node, 
                     const std::string &name);
};
#endif //__CONFIGURATION_HPP__
