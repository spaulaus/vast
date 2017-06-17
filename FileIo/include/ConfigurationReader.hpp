///@file Configuration.hpp
///@brief A class to handle the configuration xml
///@author S. V. Paulauskas
///@date November 30, 2013
#ifndef __CONFIGURATION_READER_HPP__
#define __CONFIGURATION_READER_HPP__

#include <string>

#include "CrystalBallParameters.hpp"
#include "Decay.hpp"
#include "EffCalculator.hpp"
#include "Experiment.hpp"
#include "FileHandler.hpp"
#include "FitHandler.hpp"
#include "FlagHandler.hpp"
#include "pugixml.hpp"

/// A class that handles the parsing of the xml configuration file.
class ConfigurationReader {
public:
    ///The default constructor
    ConfigurationReader(void) {};

    ///The default destructor
    ~ConfigurationReader(void) {};

    ///@brief A method that parses the decay information
    ///@param[in] decayNode : The node that we want to parse
    ///@param[in] decay : The class that we are going to fill with the goodness
    void ParseDecayNode(const pugi::xml_node &decayNode, Decay &decay);

    ///@brief A method that parses the experimental information
    ///@param[in] experimentNode : The node that we want to parse
    ///@param[in] experiment : The class that we are going to fill with the goodness
    void ParseExperimentNode(const pugi::xml_node &experimentNode, Experiment &experiment);

    ///@brief A method that parses the input and output files
    ///@param[in] fileHandlerNode : The node that we want to parse
    ///@param[in] fileHandler : The class that we are going to fill with the goodness
    void ParseFileNode(const pugi::xml_node &fileHandlerNode, FileHandler &fileHandler);

    ///@brief A method that parses the fitting information
    ///@param[in] fitHandlerNode : The node that we want to parse
    ///@param[in] fitHandler : The class that we are going to fill with the goodness
    void ParseFitNode(const pugi::xml_node &fitHandlerNode, FitHandler &fitHandler);

    ///@brief A method that parses the logic handling flags
    ///@param[in] flagHandlerNode : The node that we want to parse
    ///@param[in] flagHandler : The class that we are going to fill with the goodness
    void ParseFlagsNode(const pugi::xml_node &flagHandlerNode, FlagHandler &flagHandler);

    ///@brief A method that handles the reading of the Crystal Ball ParamCalculator
    ///@param[in] crystalBallNode : The node that we want to parse
    ///@param[in] crystalBall : The class that we are going to fill with the goodness
    void ParseCrystalBallNode(const pugi::xml_node &crystalBallNode, CrystalBallParameters &crystalBall);

private:
    ///@brief Method that will convert a number read in from the node to a Variable type
    ///@param[in] node : The node that we are going to convert
    Variable NodeToVar(const pugi::xml_node &node);

    ///@brief Method that will actually open up the configuration file and throw
    /// some errors if we did not successfully do so.
    void OpenConfigurationFile(const std::string &file);

    ///@brief A method to format an exception for an empty node.
    ///@param[in] method : The name of the method throwing the exception
    ///@param[in] node : The name of the node where the exception occured.
    std::string EmptyNodeExceptionMessage(const std::string &method, const std::string &node);

    ///@brief A method to format an exception for an unrecognized entry into a node.
    ///@param[in] method : The name of the method that throws the exception
    ///@param[in] node : The name of the node where the exception occured
    ///@param[in] name : The name of the unrecognized value.
    std::string UnknownEntryExceptionMessage(const std::string &method, const std::string &node,
                                             const std::string &name);
};

#endif //__CONFIGURATION_READER_HPP__
