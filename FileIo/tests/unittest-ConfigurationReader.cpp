///@file test_configuration.cpp
///@brief Performs unit tests on the methods in the ConfigurationReader class.
///@author S. V. Paulauskas
///@date November 17, 2016
#include <iostream>
#include <string>

#include "pugixml.hpp"
#include <UnitTest++.h>

#include "ConfigurationReader.hpp"
#include "UnittestConfigurations.hpp"

using namespace std;
using namespace UnitTestVariables::ConfigurationReader;

TEST_FIXTURE(ConfigurationReader, Test_ParseExperimentNode) {
    pugi::xml_document doc;
    doc.load_string(test_experimentNode.c_str());

    Experiment experiment;
    ParseExperimentNode(doc.child("Configuration").child("Experiment"), experiment);

    CHECK_EQUAL(test_numberOfBars, experiment.GetNumBars());
    CHECK_EQUAL(test_flightPath, experiment.GetFlightPath());
    CHECK_EQUAL(test_densityResolution, experiment.GetDensityRes());
    CHECK_EQUAL(test_omegaPerBar, experiment.GetOmegaPerBar());
    CHECK(expected_EfficiencyCurve == experiment.GetEfficiencyCurveName());
}

TEST_FIXTURE(ConfigurationReader, Test_ParseDecayNode) {
    pugi::xml_document doc;
    doc.load_string(test_decayNode.c_str());

    Decay decay;
    ParseDecayNode(doc.child("Configuration").child("Decay"), decay);

    CHECK_THROW(ParseDecayNode(doc.child("Empty"), decay), ConfigurationReaderException);

    CHECK_EQUAL(test_daughterZ, decay.GetDaughterZ());
    CHECK_EQUAL(test_parentZ, decay.GetParentZ());
    CHECK_EQUAL(test_halfLife, decay.GetHalfLife());
    ///@TODO We need to actually test this but the method is not conducive to testing at the moment.
    //CHECK_EQUAL(test_numberOfDecays, decay.GetNumberOfDecays());
    CHECK_EQUAL(test_neutronSeparationEnergy, decay.GetNeutronSepEnergy());
    CHECK_EQUAL(test_qValue, decay.GetQValue());
    CHECK_EQUAL(test_qBetaN, decay.GetQBetaN());
}

TEST_FIXTURE(ConfigurationReader, Test_ParseFileNode) {
    pugi::xml_document doc;
    doc.load_string(test_fileNode.c_str());

    FileHandler files;
    ParseFileNode(doc.child("Configuration").child("Files"), files);
    CHECK_THROW(ParseFileNode(doc.child("Empty"), files), ConfigurationReaderException);
    CHECK_EQUAL(test_inputFilePath, files.GetInputName(test_inputFileName));
    CHECK_EQUAL(test_outputFilePath, files.GetOutputName(test_outputFileName));
}

TEST_FIXTURE(ConfigurationReader, Test_ParseFlagNode) {
    pugi::xml_document doc;
    doc.load_string(test_flagNode.c_str());

    FlagHandler flags;
    ParseFlagsNode(doc.child("Configuration").child("Flags"), flags);

    CHECK_THROW(ParseFlagsNode(doc.child("Empty"), flags), ConfigurationReaderException);
    CHECK(flags.GetFlag(test_flagName));
}

TEST_FIXTURE(ConfigurationReader, Test_ParseFitNode) {
    pugi::xml_document doc;
    doc.load_string(test_fitNode.c_str());

    FitHandler fit;
    //ParseFitNode(doc.child("Configuration").child("Fit"), fit);

    CHECK_THROW(ParseFitNode(doc.child("Empty"), fit), ConfigurationReaderException);

}

TEST_FIXTURE(ConfigurationReader, Test_ParseCrystalBallNode) {
    pugi::xml_document doc;
    doc.load_string(test_crystalBallNode.c_str());

    CrystalBallParameters params;
    //ParseCrystalBallNode(doc.child("Configuration").child("CrystalBall"), params);

    CHECK_THROW(ParseCrystalBallNode(doc.child("Empty"), params), ConfigurationReaderException);
}

int main(int argc, char **argv) {
    return (UnitTest::RunAllTests());
}