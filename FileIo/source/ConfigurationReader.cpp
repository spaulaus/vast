///@file ConfigurationReader.cpp
///@brief A class to handle the configuration xml file
///@author S. V. Paulauskas
///@date November 30, 2013
#include <iostream>
#include <map>
#include <vector>

#include "ConfigurationReader.hpp"
#include "HelperEnumerations.hpp"
#include "IoHelperFunctions.hpp"
#include "VastExceptions.hpp"

using namespace std;

///This method parses the configuration file using pugixml to fill experimental information.
void ConfigurationReader::ParseExperimentNode(const pugi::xml_node &experimentNode, Experiment &experiment) {
    if (experimentNode.empty())
        throw ConfigurationReaderException(EmptyNodeExceptionMessage("ParseExperimentNode", "Experiment"));

    for (pugi::xml_node node : experimentNode.children()) {
        string name = node.name();
        Variable temp = NodeToVar(node);
        if (name == "NumberOfBars")
            experiment.SetNumBars(temp);
        else if (name == "OmegaPerBar")
            experiment.SetOmegaPerBar(temp);
        else if (name == "DensityResolution")
            experiment.SetDensityRes(temp);
        else if (name == "FlightPath")
            experiment.SetFlightPath(temp);
        else if (name == "EfficiencyCurve")
            experiment.SetEfficiencyCurveName(EfficiencyEnums::ConvertStringToEfficiencyType(node.child_value()));
        else
            throw ConfigurationReaderException(UnknownEntryExceptionMessage("ParseExperimentNode", "Experiment", name));
    }
}

///This method parses the configuration file using pugixml for the input and output files.
void ConfigurationReader::ParseFileNode(const pugi::xml_node &fileHandlerNode, FileHandler &fileHandler) {
    if (fileHandlerNode.empty())
        throw ConfigurationReaderException(EmptyNodeExceptionMessage("ReadFiles", "Files"));

    for (pugi::xml_node attr : fileHandlerNode.child("Input").children()) {
        if(!IoHelpers::HasWritePermission(attr.child_value()))
            throw VastIoException("ConfigurationReader::ParseFileNode - We don't have permission to write to " 
                                  + string(attr.child_value()));
        fileHandler.SetInputNames(attr.name(), attr.child_value());
    }

    for (pugi::xml_node attr : fileHandlerNode.child("Output").children()) {
        if(!IoHelpers::HasWritePermission(attr.child_value()))
            throw VastIoException("ConfigurationReader::ParseFileNode - We don't have permission to write to " 
                                  + string(attr.child_value()));
        fileHandler.SetOutputNames(attr.name(), attr.child_value());
    }
}

///This method parses the configuration file using pugixml getting the fitting information.
void ConfigurationReader::ParseFitNode(const pugi::xml_node &fitHandlerNode, FitHandler &fitHandler) {
    if (fitHandlerNode.empty())
        throw ConfigurationReaderException(EmptyNodeExceptionMessage("ReadFit", "Fitting"));

    string pklist = fitHandlerNode.child("pkList").attribute("value").as_string();
    fitHandler.SetPeakList(pklist);

    vector<double> snglPeaks, g1Peaks, g2Peaks;

    for (pugi::xml_node pks : fitHandlerNode.child("peaks").child("sngl").children())
        snglPeaks.push_back(pks.attribute("value").as_double());

    if (snglPeaks.empty() && pklist == "sngl")
        throw ConfigurationReaderException("ConfigurationReader::ReadFit - The singles peak list is empty. You will "
                                                   "have to add peaks for fitting.");
    fitHandler.SetSnglPeaks(snglPeaks);

    for (pugi::xml_node pks : fitHandlerNode.child("peaks").child("g1").children())
        g1Peaks.push_back(pks.attribute("value").as_double());
    if (g1Peaks.empty() && pklist == "g1")
        throw ConfigurationReaderException("ConfigurationReader::ReadFit - The gamma 1 gated peak list is empty. You "
                                                   "will have to add peaks for fitting.");
    fitHandler.SetGate1Peaks(g1Peaks);

    for (pugi::xml_node pks : fitHandlerNode.child("peaks").child("g2").children())
        g2Peaks.push_back(pks.attribute("value").as_double());
    if (g2Peaks.empty() && pklist == "g2")
        throw ConfigurationReaderException("ConfigurationReader::ReadFit - The gamma 2 gated peak list is empty. You "
                                                   "will have to add peaks for fitting.");
    fitHandler.SetGate2Peaks(g2Peaks);

    fitHandler.SetBinning(fitHandlerNode.child("binning").attribute("value").as_double(0.5));
    fitHandler.SetPrintLevel(fitHandlerNode.child("PrintLevel").attribute("value").as_int(1));

    double low = fitHandlerNode.child("range").child("low").attribute("value").as_double();
    double high = fitHandlerNode.child("range").child("high").attribute("value").as_double();
    fitHandler.SetRange(make_pair(low, high));
}

///This method parses the configuration file using pugixml getting the crystal ball parameters.
void ConfigurationReader::ParseCrystalBallNode(const pugi::xml_node &crystalBallNode,
                                               CrystalBallParameters &crystalBall) {
    if (crystalBallNode.empty())
        throw ConfigurationReaderException(EmptyNodeExceptionMessage("ReadCrystalBallParameters",
                                                                     "CrystalBallParameters"));
    string var_name = "", function = "";
    vector<Variable> coefficients;
    for (const auto vars : crystalBallNode.children()) {
        var_name = vars.name();

        function = vars.child("function").attribute("value").as_string("");

        if (function == "")
            throw ConfigurationReaderException("ConfigurationReader::ReadCrystalBallParameters - The function for "
                                               + var_name + " was empty.");

        if (vars.child("coefficients").empty())
            throw ConfigurationReaderException("ConfigurationReader::ReadCrystalBallParameters - The coefficients for "
                                               + var_name + "were not input.");

        for (const auto &coeffs : vars.child("coefficients").children())
            coefficients.push_back(NodeToVar(coeffs));

        try {
            if (var_name == "alpha") {
                crystalBall.SetAlphaFunction(function);
                crystalBall.SetAlphaCoefficients(coefficients);
            } else if (var_name == "n") {
                crystalBall.SetNFunction(function);
                crystalBall.SetNCoefficients(coefficients);
            } else if (var_name == "sigma") {
                crystalBall.SetSigmaFunction(function);
                crystalBall.SetSigmaCoefficients(coefficients);
            }
        } catch (invalid_argument &invalidArgument) {
            cout << "ConfigurationReader::ParseCrystalBallNode - Intercepted invalid argument when setting the "
                    "information from the " + var_name + " node." << endl;
            throw invalid_argument(invalidArgument.what());
        }

        coefficients.clear();
        function = "";
    }
}

///This method parses the configuration file for logic flags.
void ConfigurationReader::ParseFlagsNode(const pugi::xml_node &flagHandlerNode, FlagHandler &flagHandler) {
    if (flagHandlerNode.empty())
        throw ConfigurationReaderException(EmptyNodeExceptionMessage("ReadFlags", "Flags"));
    for (pugi::xml_node &chld : flagHandlerNode.children())
        flagHandler.SetFlag(chld.name(), chld.attribute("value").as_bool());
}

///This method parses the configuration file for the decay information.
void ConfigurationReader::ParseDecayNode(const pugi::xml_node &decayNode, Decay &decay) {
    if (decayNode.empty())
        throw ConfigurationReaderException(EmptyNodeExceptionMessage("ReadDecay", "Decay"));

    for (const auto &node1 : decayNode.children()) {
        string name = node1.name();
        Variable temp = NodeToVar(node1);
        if (name == "z")
            decay.SetParentZ(temp);
        else if (name == "q")
            decay.SetQValue(temp);
        else if (name == "sn")
            decay.SetNeutronSepEnergy(temp);
        else if (name == "qbn")
            decay.SetQBetaN(temp);
        else if (name == "t12")
            decay.SetHalfLife(temp);
        else if (name == "gn") {
            ///@TODO This should be removed from this node and the Gamma class should be used.
            decay.SetNumDecay(NodeToVar(node1.child("en")), NodeToVar(node1.child("area")),
                              NodeToVar(node1.child("abr")));
        } else if (name == "g1") {
            //unused for now
        } else if (name == "g2") {
            //unused for now
        } else
            throw ConfigurationReaderException(UnknownEntryExceptionMessage("ParseDecayNode", "Decay", name));
    }
}



///This method converts a node with the value, error, and unit attributes into a Variable.
Variable ConfigurationReader::NodeToVar(const pugi::xml_node &node) {
    return Variable(node.attribute("value").as_double(0.0), node.attribute("error").as_double(0.0),
                     node.attribute("unit").as_string(""));
}

///This method produces an error message for an empty node.
string ConfigurationReader::EmptyNodeExceptionMessage(const std::string &method, const std::string &node) {
    return "ConfigurationReader::" + method + " - The " + node + " node does not exist! It's critical!";
}

///This method produces an error message for an unrecognized entry in a node
string ConfigurationReader::UnknownEntryExceptionMessage(const std::string &method, const std::string &node,
                                                         const std::string &name) {
    return "ConfigurationReader::" + method + " - " + "There was an unrecognized entry into the " + node
           + " node with the name: " + name
           + ". If you need access to this variable you will need to edit the source code.";
}