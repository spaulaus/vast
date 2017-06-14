///@file test_crystalballparameters.cpp
///@author S. V. Paulauskas
///@date November 16, 2016
///@brief A small code to test the behavior of the CrystalBallParameters
#include <iostream>

#include <UnitTest++.h>

#include "CrystalBallParameters.hpp"
#include "UnittestConfigurations.hpp"

using namespace std;
using namespace UnitTestVariables::CrystalBallParameters;
using namespace UnitTestVariables::TimeOfFlight;

///This method is the main, and is used to test what the crystal ball parameters do
TEST_FIXTURE(CrystalBallParameters, Test_SettingParameters) {
    SetAlphaCoefficients(test_alphaCoeffs);
    SetNCoefficients(test_nCoeffs);
    SetSigmaCoefficients(test_sigmaCoeffs);

    CHECK_ARRAY_EQUAL(GetAlphaCoefficients(), test_alphaCoeffs, test_alphaCoeffs.size());
    CHECK_ARRAY_EQUAL(GetNCoefficients(), test_nCoeffs, test_nCoeffs.size());
    CHECK_ARRAY_EQUAL(GetSigmaCoefficients(), test_sigmaCoeffs, test_sigmaCoeffs.size());

    vector<Variable> tooShort;
    CHECK_THROW(SetAlphaCoefficients(tooShort), invalid_argument);
    CHECK_THROW(SetNCoefficients(tooShort), invalid_argument);
    CHECK_THROW(SetSigmaCoefficients(tooShort), invalid_argument);

    vector<Variable> tooLong(test_alphaCoeffs.begin(), test_alphaCoeffs.end());
    tooLong.insert(tooLong.end(), test_nCoeffs.begin(), test_nCoeffs.end());
    CHECK_THROW(SetAlphaCoefficients(tooLong), invalid_argument);
    CHECK_THROW(SetNCoefficients(tooLong), invalid_argument);
    CHECK_THROW(SetSigmaCoefficients(tooLong), invalid_argument);
}

TEST(Test_SettingViaConstructor) {
    CrystalBallParameters crystalBallParameters(test_alphaCoeffs, test_nCoeffs, test_sigmaCoeffs);
    CHECK_ARRAY_EQUAL(crystalBallParameters.GetAlphaCoefficients(), test_alphaCoeffs, test_alphaCoeffs.size());
    CHECK_ARRAY_EQUAL(crystalBallParameters.GetNCoefficients(), test_nCoeffs, test_nCoeffs.size());
    CHECK_ARRAY_EQUAL(crystalBallParameters.GetSigmaCoefficients(), test_sigmaCoeffs, test_sigmaCoeffs.size());
}

TEST(Test_Calculations) {
    CrystalBallParameters crystalBallParameters(test_alphaCoeffs, test_nCoeffs, test_sigmaCoeffs);
    CHECK_CLOSE(crystalBallParameters.CalcAlpha(test_tofInNs), test_alphaValue, 0.0001);
    CHECK_CLOSE(crystalBallParameters.CalcN(test_tofInNs), test_nValue, 0.0001);
    CHECK_CLOSE(crystalBallParameters.CalcSigma(test_tofInNs), test_sigmaValue, 0.0001);
}

TEST_FIXTURE(CrystalBallParameters, Test_FunctionReplacements) {
    SetAlphaFunction(test_alphaFunctionInput);
    CHECK_EQUAL(GetAlphaFunction(test_replacementString), test_alphaFunctionOutput);

    SetNFunction(test_nFunctionInput);
    CHECK_EQUAL(GetNFunction(test_replacementString), test_nFunctionOutput);

    SetSigmaFunction(test_sigmaFunctionInput);
    CHECK_EQUAL(GetSigmaFunction(test_replacementString), test_sigmaFunctionOutput);

    CHECK_THROW(SetAlphaFunction(""), invalid_argument);
    CHECK_THROW(SetNFunction(""), invalid_argument);
    CHECK_THROW(SetSigmaFunction(""), invalid_argument);
}

int main(int argv, char *argc[]) {
    return (UnitTest::RunAllTests());
}