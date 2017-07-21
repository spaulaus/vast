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

TEST_FIXTURE(CrystalBallParameters, Test_SetupAlphaFunction) {
    CHECK_THROW(SetupAlphaFunction("", test_alphaCoeffs), invalid_argument);
    CHECK_THROW(SetupAlphaFunction(test_alphaFunctionInput, emptyCoefficients), invalid_argument);
    CHECK_THROW(SetupAlphaFunction(test_alphaFunctionInput, test_sigmaCoeffs), invalid_argument);

    SetupAlphaFunction(test_alphaFunctionInput, test_alphaCoeffs);
    CHECK_EQUAL(GetAlphaFunctionString(test_replacementString), test_alphaFunctionOutput);
    CHECK_ARRAY_EQUAL(GetAlphaCoefficients(), test_alphaCoeffs, test_alphaCoeffs.size());
    CHECK_CLOSE(CalcAlpha(test_tofInNs), test_alphaValue, 0.0001);

    TF1 alpha = GetAlphaRootFunction();
    CHECK_EQUAL(test_alphaRootFunction, alpha.GetExpFormula());
}

TEST_FIXTURE(CrystalBallParameters, Test_SetupNFunction) {
    CHECK_THROW(SetupNFunction("", test_nCoeffs), invalid_argument);
    CHECK_THROW(SetupNFunction(test_nFunctionInput, emptyCoefficients), invalid_argument);
    CHECK_THROW(SetupNFunction(test_nFunctionInput, test_sigmaCoeffs), invalid_argument);

    SetupNFunction(test_nFunctionInput, test_nCoeffs);
    CHECK_EQUAL(GetNFunctionString(test_replacementString), test_nFunctionOutput);
    CHECK_ARRAY_EQUAL(GetNCoefficients(), test_nCoeffs, test_nCoeffs.size());
    CHECK_CLOSE(CalcN(test_tofInNs), test_nValue, 0.0001);

    TF1 n = GetNRootFunction();
    CHECK_EQUAL(test_nRootFunction, n.GetExpFormula());
}

TEST_FIXTURE(CrystalBallParameters, Test_SetupSigmaFunction) {
    CHECK_THROW(SetupSigmaFunction("", test_sigmaCoeffs), invalid_argument);
    CHECK_THROW(SetupSigmaFunction(test_sigmaFunctionInput, emptyCoefficients), invalid_argument);
    CHECK_THROW(SetupSigmaFunction(test_sigmaFunctionInput, test_nCoeffs), invalid_argument);

    SetupSigmaFunction(test_sigmaFunctionInput, test_sigmaCoeffs);
    CHECK_EQUAL(GetSigmaFunctionString(test_replacementString), test_sigmaFunctionOutput);
    CHECK_ARRAY_EQUAL(GetSigmaCoefficients(), test_sigmaCoeffs, test_sigmaCoeffs.size());
    CHECK_CLOSE(CalcSigma(test_tofInNs), test_sigmaValue, 0.0001);

    TF1 sigma = GetSigmaRootFunction();
    CHECK_EQUAL(test_sigmaRootFunction, sigma.GetExpFormula());
}

int main(int argc, char *argv[]) {
    return (UnitTest::RunAllTests());
}