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

/// A class that handles the parsing of the xml configuration file.
class Configuration {
public:
    /*! The default constructor */
    Configuration(void){};
    /*! A constructor taking the configuration file as input */
    Configuration(const std::string &file);
    /*! The default destructor */
    ~Configuration(void){};

    /*!A method that returns a pointer to the opened configuration document */
    pugi::xml_document *GetDocument(void){return(&doc_);};

    /*!A method that parses the decay information */
    Decay ReadDecay(void);
    /*!A method that parses the experimental information */
    Experiment ReadExperiment(void);
    /*!A method that parses the input and output files */
    FileHandler ReadFiles(void);
    /*!A method that parses the fitting information */
    FitHandler ReadFit(void);
    /*!A method that parses the logic handling flags */
    FlagHandler ReadFlags(void);
private:
    pugi::xml_document doc_;
    pugi::xml_node cfg_;
    std::string file_;    

    Variable NodeToVar(const pugi::xml_node &node);
    void SpitWarning(const std::string &node, 
                     const std::string &name);
};
#endif //__CONFIGURATION_HPP__
