///@file CrystalBallParameters.cpp
///@brief A class that handles setup and calculation of the crystal ball parameters.
///@author S. V. Paulauskas
///@date November 12, 2013
#include <iostream>

#include "CrystalBallParameters.hpp"

using namespace std;

void CrystalBallParameters::VerifyInputs(const string &name, const string &function, const vector<Variable> &coeffs) {
    if (function == "")
        throw invalid_argument("CrystalBallParameters::VerifyInputs - The functional string for "
                                    + name + " was empty!");
    if (coeffs.empty())
        throw invalid_argument("CrystalBallParameters::VerifyInputs - The coefficients vector for "
                                    + name + " was empty!");

    size_t foundCoefficient = function.find(name.at(0));

    if(foundCoefficient == string::npos)
        throw invalid_argument("CrystalBallParameters::VerifyInputs - We didn't find any coefficients listed"
                                            " in the function!!");

    unsigned long coefficientOrder = stoul(&function.at(foundCoefficient + 1));

    while (foundCoefficient != string::npos) {
        foundCoefficient = function.find("c", foundCoefficient + 1);

        if(foundCoefficient == string::npos)
            break;

        if (stoul(&function.at(foundCoefficient + 1)) > coefficientOrder)
            coefficientOrder = stoul(&function.at(foundCoefficient + 1));
        foundCoefficient++;
    }

    if (coeffs.size() != coefficientOrder + 1)
        throw invalid_argument("CrystalBallParameters::SetupFunction - The coefficients vector for "
                                    + name + " did not contain all coefficients defined in the function!");
}

TF1 CrystalBallParameters::GenerateRootFunction(const string &name, const string &originalString,
                                                const vector<Variable> &coeffs) {
    string functionString = StringManipulation::ReplaceString(originalString, "tof", "x");
    for (unsigned int i = 0; i < coeffs.size(); i++) {
        string toReplace = name.at(0) + to_string(i);
        string replaceWith = "[" + to_string(i) + "]";
        functionString = StringManipulation::ReplaceString(functionString, toReplace, replaceWith);
    }

    TF1 function = TF1(name.c_str(), functionString.c_str(), -100, 100);

    for (unsigned int i = 0; i < coeffs.size(); i++)
        function.SetParameter(i, coeffs[i].GetValue());

    return function;
}
