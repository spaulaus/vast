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

#include "Variable.hpp"

namespace UnitTests {
    /// @brief A namespace that defines things that are useful for testing Crystal Ball Parameters.
    namespace CrystalBallParameters {
        /// The parameterization of the
        static const std::vector <Variable> test_alpha =
                {Variable(-0.73110, 0.10206, ""), Variable(-0.00101, 0.00574, ""),
                 Variable(2.52616e-05, 8.81266e-05, ""), Variable(-1.07220e-07, 3.89451e-07, "")};
        static const std::vector <Variable> test_n =
                {Variable(-4.33787, 1.60649, ""), Variable(1.65099, 0.09231, ""), Variable(0.00179, 0.00095, "")};
        static const std::vector <Variable> test_sigma =
                {Variable(0.18205, 0.120600, ""), Variable(0.070225, 0.010693, ""), Variable(0.00075, 0.00029, ""),
                 Variable(4.90374e-06, 3.14410e-06, ""), Variable(-1.19754e-08, 1.09884e-08, "")};

        /// Strings that contain the functional information for the parameterization.
        static const std::string test_alphaFunctionInput = "a4*pow(tof,4)+a3*pow(tof,3)+a2*pow(tof,2)+a1*tof+a0";
        static const std::string test_nFunctionInput = "n2*tof+n1+n0/tof";
        static const std::string test_sigmaFunctionInput = "s4*pow(tof,4)+s3*pow(tof,3)+s2*pow(tof,2)+s1*tof+s0";

        /// The string we are going to use to replace "tof" in the function input strings.
        static const std::string test_replacementString = "mu0";

        /// These strings are what we expect to get once the replacement string is input.
        static const std::string test_alphaFunctionOutput = "a4*pow(mu0,4)+a3*pow(mu0,3)+a2*pow(mu0,2)+a1*mu0+a0";
        static const std::string test_nFunctionOutput = "n2*mu0+n1+n0/mu0";
        static const std::string test_sigmaFunctionOutput = "s4*pow(mu0,4)+s3*pow(mu0,3)+s2*pow(mu0,2)+s1*mu0+s0";
    }

    namespace TimeOfFlight {
        static const double test_tofInNs = 150;
    }
}

#endif //VANDLEANALYSISSOFTWARETOOLKIT_UNITTESTCONFIGURATIONS_HPP
