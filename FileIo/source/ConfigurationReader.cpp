/** \file ConfigurationReader.cpp
 * \brief A class to handle the confiruation xml file
 * \author S. V. Paulauskas
 * \date 30 November 2013
 */
#include <iostream>
#include <map>
#include <vector>

#include "ConfigurationReader.hpp"

using namespace std;

///Constructor that takes the full path to the configuration file and tries
/// to open it for parsing. This attempt is made inside a try/catch block for
/// proper error handling.
ConfigurationReader::ConfigurationReader(const std::string &file) {
    try {
        OpenConfigurationFile(file);
    } catch (std::exception &ex) {
        throw Exception(ex.what());
    }
}

///This method sets the configuration file to be used by the program
void ConfigurationReader::SetConfigurationFile(const std::string &file) {
    try {
        OpenConfigurationFile(file);
    } catch (std::exception &ex) {
        throw Exception(ex.what());
    }
}

///This method opens the configuration file to be used by the program.  It
/// also prvides error messages if it couldn't open the configuration.
void ConfigurationReader::OpenConfigurationFile(const std::string &file) {
    if (doc_.load_file(file.c_str())) {
        cout << "Using configuration file : " << file << endl;
        cfg_ = doc_.child("Configuration");
    } else
        throw Exception("ConfigurationReader::OpenConfigurationFile : The "
                                "configuration file was not opened properly, "
                                "check the path and try again. ");
}

///This method parses the configuration file using pugiXML to fill
/// experimental information.
Experiment ConfigurationReader::ReadExperiment(void) {
    Experiment exp;
    pugi::xml_node expInfo = cfg_.child("Experiment");
    if (expInfo.empty())
        throw Exception(EmptyNodeExceptionMessage("ReadExperiment",
                                                  "Experiment"));

    for (pugi::xml_node node : expInfo.children()) {
        string name = node.name();
        Variable temp = NodeToVar(node);
        if (name == "NumberOfBars")
            exp.SetNumBars(temp);
        else if (name == "OmegaPerBar")
            exp.SetOmegaPerBar(temp);
        else if (name == "DensityResolution")
            exp.SetDensityRes(temp);
        else if (name == "FlightPath")
            exp.SetFlightPath(temp);
        else if (name == "EfficiencyCurve")
            exp.SetEfficiencyCurveName(StringToEffType(node.child_value()));
        else
            throw Exception(UnknownEntryExceptionMessage("ReadExperiment",
                                                         "Experiment", name));
    }
    return (exp);
}

///This method parses the configuration file using pugiXML for the input and
/// output files.
FileHandler ConfigurationReader::ReadFiles(void) {
    FileHandler fhandle;
    if (cfg_.child("Files").empty())
        throw Exception(EmptyNodeExceptionMessage("ReadFiles", "Files"));

    pugi::xml_node inode = cfg_.child("Files").child("Input");
    pugi::xml_node onode = cfg_.child("Files").child("Output");

    for (pugi::xml_node attr : inode.children())
        fhandle.SetInputNames(attr.name(), attr.child_value());
    for (pugi::xml_node attr : onode.children())
        fhandle.SetOutputNames(attr.name(), attr.child_value());
    return (fhandle);
}

///This method parses the configuration file using pugiXML getting the
/// fitting information.
FitHandler ConfigurationReader::ReadFit(void) {
    FitHandler fit;
    pugi::xml_node ft = cfg_.child("Fitting");

    if (ft.empty())
        throw Exception(EmptyNodeExceptionMessage("ReadFit", "Fitting"));

    string pklist = ft.child("pkList").attribute("value").as_string();
    fit.SetPeakList(pklist);

    vector<double> snglPeaks, g1Peaks, g2Peaks;

    for (pugi::xml_node pks : ft.child("peaks").child("sngl").children())
        snglPeaks.push_back(pks.attribute("value").as_double());

    if (snglPeaks.empty() && pklist == "sngl")
        throw Exception("ConfigurationReader::ReadFit - The singles peak list"
                                " is empty. You will have to add peaks for "
                                "fitting.");
    fit.SetSnglPeaks(snglPeaks);

    for (pugi::xml_node pks : ft.child("peaks").child("g1").children())
        g1Peaks.push_back(pks.attribute("value").as_double());
    if (g1Peaks.empty() && pklist == "g1")
        throw Exception("ConfigurationReader::ReadFit - The gamma 1 gated  "
                                "peak list is empty. You will have to add "
                                "peaks for fitting.");
    fit.SetGate1Peaks(g1Peaks);

    for (pugi::xml_node pks : ft.child("peaks").child("g2").children())
        g2Peaks.push_back(pks.attribute("value").as_double());
    if (g2Peaks.empty() && pklist == "g2")
        throw Exception("ConfigurationReader::ReadFit - The gamma 2 gated  "
                                "peak list is empty. You will have to add "
                                "peaks for fitting.");
    fit.SetGate2Peaks(g2Peaks);

    fit.SetBinning(ft.child("binning").attribute("value").as_double(0.5));
    fit.SetPrintLevel(ft.child("PrintLevel").attribute("value").as_int(1));

    double low =
            ft.child("range").child("low").attribute("value").as_double();
    double high =
            ft.child("range").child("high").attribute("value").as_double();
    fit.SetRange(make_pair(low, high));
    return (fit);
}

///This method parses the configuration file using pugiXML getting the
/// crystal ball parameters.
CrystalBallParameters ConfigurationReader::ReadCrystalBallParameters() {
    CrystalBallParameters cbpar;
    string var_name = "", function = "";
    vector<Variable> coefficients;
    if (cfg_.child("CrystalBallParameters").empty())
        throw Exception(EmptyNodeExceptionMessage("ReadCrystalBallParameters",
                                                  "CrystalBallParameters"));
    for (const auto vars : cfg_.child("CrystalBallParameters").children()) {
        var_name = vars.name();

        function = vars.child("function").attribute("value").as_string("");
        if (function == "")
            throw Exception("ConfigurationReader::ReadCrystalBallParameters -"
                                    " The function for " + var_name + " was "
                                    "empty.");

        if (vars.child("coefficients").empty())
            throw Exception("ConfigurationReader::ReadCrystalBallParameters -"
                                    " The coefficients for " + var_name +
                            "were not input.");
        for (const auto coeffs : vars.child("coefficients").children())
            coefficients.push_back(NodeToVar(coeffs));
        if (var_name == "alpha") {
            try {
                cbpar.SetAlphaFunction(function);
                cbpar.SetAlphaCoefficients(coefficients);
            } catch (exception &ex) {
                throw Exception(ex.what());
            }
        } else if (var_name == "n") {
            try {
                cbpar.SetNFunction(function);
                cbpar.SetNCoefficients(coefficients);
            } catch (exception &ex) {
                throw Exception(ex.what());
            }
        } else if (var_name == "sigma") {
            try {
                cbpar.SetSigmaFunction(function);
                cbpar.SetSigmaCoefficients(coefficients);
            } catch (exception &ex) {
                throw Exception(ex.what());
            }
        }
        coefficients.clear();
        function = "";
    }
    return cbpar;
}

///This method parses the configuration file for logic flags.
FlagHandler ConfigurationReader::ReadFlags(void) {
    FlagHandler flags;
    if (cfg_.child("Flags").empty())
        throw Exception(EmptyNodeExceptionMessage("ReadFlags", "Flags"));
    for (pugi::xml_node chld : cfg_.child("Flags").children())
        flags.SetFlag(chld.name(), chld.attribute("value").as_bool());
    return (flags);
}

///This method parses the configuration file for the decay information.
Decay ConfigurationReader::ReadDecay(void) {
    Decay decay;
    pugi::xml_node dky = cfg_.child("Decay");

    if (dky.empty())
        throw Exception(EmptyNodeExceptionMessage("ReadDecay", "Decay"));

    for (auto node1 : dky.children()) {
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
            Variable area = NodeToVar(node1.child("area"));
            Variable en = NodeToVar(node1.child("en"));
            Variable abr = NodeToVar(node1.child("abr"));
            decay.SetNumDecay(en, area, abr);
        } else if (name == "g1") {
            //unused for now
        } else if (name == "g2") {
            //unused for now
        } else
            throw Exception(UnknownEntryExceptionMessage("ReadDecay",
                                                         "Decay", name));
    }
    return (decay);
}

///This method converts string reads from the configuration file into
/// efficiency types.
EffCalculator::EffTypes
ConfigurationReader::StringToEffType(const std::string &a) {
    if (a == "mmfCalc")
        return (EffCalculator::EffTypes::mmfCalc);
    if (a == "mmfTheory")
        return (EffCalculator::EffTypes::mmfTheory);
    if (a == "rolling")
        return (EffCalculator::EffTypes::rolling);
    if (a == "svpBan4")
        return (EffCalculator::EffTypes::svpBan4);
    if (a == "svpTestBan1")
        return (EffCalculator::EffTypes::svpTestBan1);
    if (a == "vandle")
        return (EffCalculator::EffTypes::vandle);
    return (EffCalculator::EffTypes::svpBan4);
}

///This method conversts numbers read from configuration nodes into the
/// c++ data types needed.
Variable ConfigurationReader::NodeToVar(const pugi::xml_node &node) {
    Variable var = Variable(node.attribute("value").as_double(),
                            node.attribute("error").as_double(),
                            node.attribute("unit").value());
    return (var);
}

///This method produces an error message for an empty node.
string ConfigurationReader::EmptyNodeExceptionMessage(const std::string &method,
                                                      const std::string &node) {
    stringstream ss;
    ss << "ConfigurationReader::" << method << " - The " << node
       << " node does not exist!";
    return ss.str();
}

///This method produces an error message for an unrecognized entry in a node
string ConfigurationReader::UnknownEntryExceptionMessage(
        const std::string &method, const std::string &node,
        const std::string &name) {
    stringstream ss;
    ss << "ConfigurationReader::" << method << " - " << "There was an "
            "unrecognized entry into the " << node << " node with the name: "
       << name << ". If you need access to this variable you will need to "
               "edit the source code.";
    return ss.str();
}