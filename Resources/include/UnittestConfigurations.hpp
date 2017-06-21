/// @file UnittestConfigurations.hpp
/// @brief A header file that contains all of the definitions that we'll be using to UnitTest
/// @author S. V. Paulauskas
/// @date June 14, 2017
/// @copyright Copyright (c) 2017 S. V. Paulauskas. 
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#ifndef VANDLEANALYSISSOFTWARETOOLKIT_UNITTESTCONFIGURATIONS_HPP
#define VANDLEANALYSISSOFTWARETOOLKIT_UNITTESTCONFIGURATIONS_HPP

#include <string>
#include <vector>

#include "HelperEnumerations.hpp"
#include "Variable.hpp"

namespace UnitTestVariables {
    /// @brief A namespace that defines things that are useful for testing Crystal Ball Parameters.
    namespace CrystalBallParameters {
        /// The parameterization of the
        static const std::vector<Variable> test_alphaCoeffs =
                {Variable(-0.73110, 0.10206, ""), Variable(-0.00101, 0.00574, ""),
                 Variable(2.52616e-05, 8.81266e-05, ""), Variable(-1.07220e-07, 3.89451e-07, "")};
        static const std::vector<Variable> test_nCoeffs =
                {Variable(-4.33787, 1.60649, ""), Variable(1.65099, 0.09231, ""), Variable(0.00179, 0.00095, "")};
        static const std::vector<Variable> test_sigmaCoeffs =
                {Variable(0.18205, 0.120600, ""), Variable(0.070225, 0.010693, ""), Variable(0.00075, 0.00029, ""),
                 Variable(4.90374e-06, 3.14410e-06, ""), Variable(-1.19754e-08, 1.09884e-08, "")};

        /// Strings that contain the functional information for the parameterization.
        static const std::string test_alphaFunctionInput = "a3*pow(tof,3)+a2*pow(tof,2)+a1*tof+a0";
        static const std::string test_nFunctionInput = "n2*tof+n1+n0/tof";
        static const std::string test_sigmaFunctionInput = "s4*pow(tof,4)+s3*pow(tof,3)+s2*pow(tof,2)+s1*tof+s0";

        /// The string we are going to use to replace "tof" in the function input strings.
        static const std::string test_replacementString = "mu0";

        /// These strings are what we expect to get once the replacement string is input.
        static const std::string test_alphaFunctionOutput = "a3*pow(mu0,3)+a2*pow(mu0,2)+a1*mu0+a0";
        static const std::string test_nFunctionOutput = "n2*mu0+n1+n0/mu0";
        static const std::string test_sigmaFunctionOutput = "s4*pow(mu0,4)+s3*pow(mu0,3)+s2*pow(mu0,2)+s1*mu0+s0";

        ///The expected values for a, n, and sigma with a ToF given by TimeOfFlight::test_tofInNs
        static const double test_alphaValue = -0.676082;
        static const double test_nValue = 1.89057;
        static const double test_sigmaValue = 38.0784;
    }

    namespace TimeOfFlight {
        static const double test_tofInNs = 150;
    }

    ///Namespace to hold variables necessary to test the ConfigurationReader class. There is a lot of code smell to
    /// setup the XML that we use to test the parsing methods.
    namespace ConfigurationReader {
        static const Variable test_numberOfBars(9, 0, "");
        static const Variable test_omegaPerBar(0.0061, 0., "");
        static const Variable test_densityResolution(0.001, 0, "MeV");
        static const Variable test_flightPath(50.5, 0, "cm");
        static const std::string test_efficiencyCurve = "mmfCalc";
        static const EfficiencyEnums::EffTypes expected_EfficiencyCurve = EfficiencyEnums::EffTypes::mmfCalc;

        static const std::string test_experimentNode =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                        "<Configuration>"
                        "    <Experiment>\n"
                        "    <NumberOfBars value=\"" + std::to_string(test_numberOfBars.GetValue()) + "\" error='"
                + std::to_string(test_numberOfBars.GetError()) + "' unit=\"" + test_numberOfBars.GetUnits() + "\"/>\n"
                        "        <OmegaPerBar value=\"" + std::to_string(test_omegaPerBar.GetValue()) + "\" error='"
                + std::to_string(test_omegaPerBar.GetError()) + "' unit=\"" + test_omegaPerBar.GetUnits() + "\"/>\n"
                        "        <DensityResolution value=\"" + std::to_string(test_densityResolution.GetValue())
                + "\" error='" + std::to_string(test_densityResolution.GetError()) + "' unit=\""
                + test_densityResolution.GetUnits() + "\"/>\n"
                        "        <FlightPath value=\"" + std::to_string(test_flightPath.GetValue()) + "\" error='"
                + std::to_string(test_flightPath.GetError()) + "' unit=\"" + test_flightPath.GetUnits() + "\"/>\n"
                        "        <EfficiencyCurve>" + test_efficiencyCurve + "</EfficiencyCurve>\n"
                        "    </Experiment>"
                        "</Configuration>";

        static const Variable test_daughterZ(32, 0, "");
        static const Variable test_parentZ(31, 0, "");
        static const Variable test_halfLife(0.085, 0.010, "s");
        static const Variable test_numberOfDecays(0, 0, "");
        static const Variable test_neutronSeparationEnergy(5.243, 0.004, "MeV");
        static const Variable test_qValue(13.690, 0.5, "MeV");
        static const Variable test_qBetaN(8.600, 0.006, "MeV");

        static const std::string test_decayNode =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                        "<Configuration>"
                        "    <Decay>\n"
                        "        <z value='" + std::to_string(test_parentZ.GetValue()) + "' error='"
                + std::to_string(test_parentZ.GetError()) + "' unit=\"" + test_parentZ.GetUnits() + "\"/>\n"
                        "        <q value='" + std::to_string(test_qValue.GetValue()) + "' error='"
                + std::to_string(test_qValue.GetError()) + "' unit=\"" + test_qValue.GetUnits() + "\"/>\n"
                        "        <sn value='" + std::to_string(test_neutronSeparationEnergy.GetValue()) + "' error='"
                + std::to_string(test_neutronSeparationEnergy.GetError()) + "' unit=\""
                + test_neutronSeparationEnergy.GetUnits() + "\"/>\n"
                        "        <qbn value='" + std::to_string(test_qBetaN.GetValue()) + "' error='"
                + std::to_string(test_qBetaN.GetError()) + "' unit=\"" + test_qBetaN.GetUnits() + "\"/>\n"
                        "        <t12 value='" + std::to_string(test_halfLife.GetValue()) + "' error='"
                + std::to_string(test_halfLife.GetError()) + "' unit=\"" + test_halfLife.GetUnits() + "\"/>\n"
                        "        <gn>\n"
                        "            <area value=\"7208\" error=\"0.0\" unit=\"counts\"/>\n"
                        "            <en value=\"0.2473\" error=\"0.0005\" unit=\"MeV\"/>\n"
                        "            <abr value=\"0.086\" error=\"0.008\" unit=\"/100\"/>\n"
                        "        </gn>\n"
                        "    </Decay>"
                        "</Configuration>";

        static const std::string test_flag = "true";
        static const std::string test_flagName = "unittest";
        static const std::string test_flagNode =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                        "<Configuration>"
                        "    <Flags>\n"
                        "        <" + test_flagName + " value=\"" + test_flag + "\"/>\n"
                        "    </Flags>"
                        "</Configuration>";

        static const std::string test_fileName = "input";
        static const std::string test_goodFilePath = "/tmp";
        static const std::string test_badFilePath = "/testing/output/file/path";

        static const std::string FormatFileNodeForUnittest(const std::string &name, const std::string &inputPath,
                                                           const std::string &outputPath) {
            return "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
                           "<Configuration>"
                           "    <Files>"
                           "        <Input>"
                           "            <" + name + ">" + inputPath + "</" + name + ">"
                           "        </Input>"
                           "        <Output>"
                           "            <OutputPath>" + outputPath + "</OutputPath>"
                           "            <" + name + ">" + outputPath + "</" + name + ">"
                           "        </Output>"
                           "    </Files>"
                           "</Configuration>";
        }

        static const std::string test_fitNode =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                        "<Configuration>"

                        "</Configuration>";

        static const std::string test_crystalBallNode =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                        "<Configuration>"

                        "</Configuration>";
    }
}

#endif //VANDLEANALYSISSOFTWARETOOLKIT_UNITTESTCONFIGURATIONS_HPP
