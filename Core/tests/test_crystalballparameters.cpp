///@file test_crystalballparameters.cpp
///@author S. V. Paulauskas
///@date November 16, 2016
///@brief A small code to test the behavior of the CrystalBallParameters
#include <iostream>

#include "CrystalBallParameters.hpp"

using namespace std;

///This method is the main, and is used to test what CB parameters do
int main() {
    CrystalBallParameters params;
    vector<Variable> alpha_init = {Variable(-0.73110,0.10206,""),
                                   Variable(-0.00101,0.00574,""),
                                   Variable(2.52616e-05,8.81266e-05,""),
                                   Variable(-1.07220e-07,3.89451e-07,"")};
    vector<Variable> n_init = {Variable(-4.33787,1.60649,""),
                               Variable(1.65099,0.09231,""),
                               Variable(0.00179,0.00095,"")};
    vector<Variable> sigma_init = {Variable(0.18205,0.120600,""),
                                   Variable(0.070225,0.010693,""),
                                   Variable(0.00075,0.00029,""),
                                   Variable(4.90374e-06,3.14410e-06,""),
                                   Variable(-1.19754e-08,1.09884e-08,"")};

    //--------------------------------------------------------------------------
    cout << "Testing the set methods for SetXXXCoefficients" << endl;
    try {
        params.SetAlphaCoefficients(alpha_init);
        params.SetNCoefficients(n_init);
        params.SetSigmaCoefficients(sigma_init);
    } catch (exception &ex) {
        cout << ex.what() << endl;
        return 1;
    }

    vector<Variable> alpha_coefficients = params.GetAlphaCoefficients();
    for(const auto i : alpha_coefficients)
        cout << i.Output();
    cout << endl;

    vector<Variable> n_coefficients = params.GetNCoefficients();
    for(const auto i : n_coefficients)
        cout << i.Output();
    cout << endl;

    vector<Variable> sigma_coefficients = params.GetSigmaCoefficients();
    for(const auto i : sigma_coefficients)
        cout << i.Output();
    cout << endl;

    //--------------------------------------------------------------------------
    cout << endl << "Testing the constructor accepting the vector of coeff"
         << endl;
    try{
        CrystalBallParameters crystalBallParameters(alpha_init, n_init, sigma_init);
        alpha_coefficients = crystalBallParameters.GetAlphaCoefficients();
        for(const auto i : alpha_coefficients)
            cout << i.Output();
        cout << endl;

        n_coefficients = crystalBallParameters.GetNCoefficients();
        for(const auto i : n_coefficients)
            cout << i.Output();
        cout << endl;

        sigma_coefficients = crystalBallParameters.GetSigmaCoefficients();
        for(const auto i : sigma_coefficients)
            cout << i.Output();
        cout << endl;
    } catch (exception &ex) {
        cout << ex.what() << endl;
        return 1;
    }

    //--------------------------------------------------------------------------
    cout << endl << "Testing the calculation of the parameters." << endl;
    double tof = 150;
    cout << params.CalcAlpha(tof) << " " << params.CalcN(tof) << " "
         << params.CalcSigma(tof) << endl;

    cout << endl << "Testing the function replacement features." << endl;
    string alphaFunction = "a4*pow(tof,4)+a3*pow(tof,3)+a2*pow(tof,2)"
            "+a1*tof+a0";
    params.SetAlphaFunction(alphaFunction);
    cout << "Original Function: " << alphaFunction << endl
         << "New Function : " << params.GetAlphaFunction("mu0") << endl << endl;

    string nFunction = "n2*tof + n1 + n0/tof";
    params.SetNFunction(nFunction);
    cout << "Original Function: " << nFunction << endl
         << "New Function : " << params.GetNFunction("mu0") << endl << endl;

    string sigmaFunction = "s4*pow(tof,4)+ s3*pow(tof,3) + s2*pow(tof,2) + "
            "s1*tof+s0";
    params.SetSigmaFunction(sigmaFunction);
    cout << "Original Function: " << sigmaFunction << endl
         << "New Function : " << params.GetSigmaFunction("mu0") << endl << endl;
}