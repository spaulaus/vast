///@file test_crystalballparameters.cpp
///@author S. V. Paulauskas
///@date November 16, 2016
///@brief A small code to test the behavior of the CrystalBallParameters
#include <iostream>

#include <UnitTest++.h>

#include "CrystalBallParameters.hpp"
#include "UnittestConfigurations.hpp"

using namespace std;
using namespace UnitTests::CrystalBallParameters;

///This method is the main, and is used to test what the crystal ball parameters do
TEST_FIXTURE(CrystalBallParameters, Test_SettingParameters) {
    SetAlphaCoefficients(test_alpha);
    SetNCoefficients(test_n);
    SetSigmaCoefficients(test_sigma);

    CHECK_ARRAY_EQUAL(GetAlphaCoefficients(), test_alpha, test_alpha.size());
    CHECK_ARRAY_EQUAL(GetNCoefficients(), test_n, test_n.size());
    CHECK_ARRAY_EQUAL(GetSigmaCoefficients(), test_sigma, test_sigma.size());
}

TEST(Test_SettingViaConstructor) {
    CrystalBallParameters crystalBallParameters(test_alpha, test_n, test_sigma);
    CHECK_ARRAY_EQUAL(crystalBallParameters.GetAlphaCoefficients(), test_alpha, test_alpha.size());
    CHECK_ARRAY_EQUAL(crystalBallParameters.GetNCoefficients(), test_n, test_n.size());
    CHECK_ARRAY_EQUAL(crystalBallParameters.GetSigmaCoefficients(), test_sigma, test_sigma.size());
}

TEST_FIXTURE(CrystalBallParameters, Test_Calculations) {
//   cout << params.CalcAlpha(tof) << " " << params.CalcN(tof) << " "
//        << params.CalcSigma(tof) << endl;
}

TEST_FIXTURE(CrystalBallParameters, Test_FunctionReplacements) {
    SetAlphaFunction(test_alphaFunctionInput);
    CHECK_EQUAL(GetAlphaFunction(test_replacementString), test_alphaFunctionOutput);

    SetNFunction(test_nFunctionInput);
    CHECK_EQUAL(GetNFunction(test_replacementString), test_nFunctionOutput);

    SetSigmaFunction(test_sigmaFunctionInput);
    CHECK_EQUAL(GetSigmaFunction(test_replacementString), test_sigmaFunctionOutput);
}

int main(int argv, char *argc[]) {
    return (UnitTest::RunAllTests());
}