///@file Configuration.hpp
///@brief A class to handle the configuration xml
///@author S. V. Paulauskas
///@date November 30, 2013
#ifndef __CONFIGURATION_READER_HPP__
#define __CONFIGURATION_READER_HPP__

#include <string>

#include "Decay.hpp"
#include "EffCalculator.hpp"
#include "Experiment.hpp"
#include "FileHandler.hpp"
#include "FlagHandler.hpp"
#include "FitHandler.hpp"
#include "ParamCalculator.hpp"
#include "pugixml.hpp"

//! A class that handles the parsing of the xml configuration file.
class ConfigurationReader {
public:
    ///The default constructor
    ConfigurationReader(void) {};

    ///@brief A constructor taking the configuration file as input
    ///@param [in] file The name of the configuration
    ConfigurationReader(const std::string &file);

    ///The default destructor
    ~ConfigurationReader(void) {};

    ///@return A pointer to the opened configuration document
    pugi::xml_document *GetDocument(void) { return (&doc_); };

    ///@brief A method that parses the decay information
    ///@return Decay information from config file
    Decay ReadDecay(void);

    ///@brief A method that parses the experimental information
    ///@return Experimental information from config file
    Experiment ReadExperiment(void);

    ///@brief A method that parses the input and output files
    ///@return File lists from the config file
    FileHandler ReadFiles(void);

    ///@brief A method that parses the fitting information
    ///@return information necessary for the fit from the config file
    FitHandler ReadFit(void);

    ///@brief A method that parses the logic handling flags
    ///@return Logic handling flags
    FlagHandler ReadFlags(void);

    ///@brief A method that handles the reading of the Crystal Ball
    /// ParamCalculator
    ParamCalculator ReadCrystalBallParameters(void);

    ///@brief This setter provides the program with the configuration file.
    ///@param[in] file Path and file name that we are goign to be using as
    /// the input to the program.
    void SetConfigurationFile(const std::string &file) { file_ = file; }

private:
    pugi::xml_document doc_;//!< internal name of the document that we opened
    pugi::xml_node cfg_; //!< the node for the configuration
    std::string file_;//!< the name of the file that we are going to open.

    ///@brief Method that converts a string read in from the configuration file into
    /// an efficiency type
    ///@param[in] a : The string value that we are going to convert
    EffCalculator::EffTypes StringToEffType(const std::string &a);

    ///@brief Method that will convert a number read in from the node to a Variable
    /// type
    ///@param[in] node : The node that we are going to convert
    Variable NodeToVar(const pugi::xml_node &node);

    ///@brief Method that will actually open up the configuration file and throw
    /// some errors if we did not successfully do so.
    void OpenConfigurationFile(const std::string &file);

    ///@brief A method to format an exception for an empty node.
    ///@param[in] method : The name of the method throwing the exception
    ///@param[in] node : The name of the node where the exception occured.
    std::string EmptyNodeExceptionMessage(const std::string &method,
                                          const std::string &node);
    ///@brief A method to format an exception for an unrecognized entry into
    /// a node.
    ///@param[in] method : The name of the method that throws the exception
    ///@param[in] node : The name of the node where the exception occured
    ///@param[in] name : The name of the unrecognized value.
    std::string UnknownEntryExceptionMessage(const std::string &method,
        const std::string &node, const std::string &name);
};

#endif //__CONFIGURATION_READER_HPP__
