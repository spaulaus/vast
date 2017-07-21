///@file CrystalBallParameters.hpp
///@brief Class to handle the parameterization of a crystal ball function.
///@author S. V. Paulauskas
///@date November 12, 2013
#ifndef __CRYSTALBALLPARAMETERS_HPP_
#define __CRYSTALBALLPARAMETERS_HPP_

#include <vector>

#include <TF1.h>

#include "StringManipulation.hpp"
#include "Variable.hpp"
#include "VastExceptions.hpp"

///A class to calculate the parameterized alpha, n, and sigma for Crystal Balls
class CrystalBallParameters {
public:
    ///@brief Default constructor
    CrystalBallParameters() {}

    ///@brief Default destructor
    ~CrystalBallParameters() {}

    ///@brief Calculate the alpha parameter from the CB
    ///@param[in] tof the time of flight
    ///@return The break point for the Gaussian and Power parts of the CB
    double CalcAlpha(const double &tof) const { return alphaRootFunction_(tof); }

    ///@brief Calculate the n parameter for the CB
    ///@param[in] tof the time of flight
    ///@return The power parameter of the CB
    double CalcN(const double &tof) const { return nRootFunction_(tof); }

    ///@brief Calculate the sigma parameter for the CB
    ///@param[in] tof the time of flight
    ///@return The width of the Gaussian part of the CB
    double CalcSigma(const double &tof) const { return sigmaRootFunction_(tof); }

    ///@brief A method that gets the coefficients for alpha
    ///@return A vector of Variables for the coefficients in ascending power
    std::vector<Variable> GetAlphaCoefficients(void) const { return alphaCoeff_; }

    ///@brief A method to return the functional form of alpha(ToF) with the tof variable replaced by the input argument.
    ///@param[in] a : The argument to replace tof with
    ///@return The functional form of the parameter with the new tof variable
    std::string GetAlphaFunctionString(const std::string &tof) const {
        return StringManipulation::ReplaceString(alphaFunction_, "tof", tof);
    }

    ///@brief A method that gets Alpha's ROOT function
    ///@return A TF1 that's used for alpha
    TF1 GetAlphaRootFunction() const { return alphaRootFunction_; }

    ///@brief A method that gets the coefficients for n
    ///@return A vector of Variables for the coefficients in ascending power
    std::vector<Variable> GetNCoefficients(void) const { return nCoeff_; }

    ///@brief A method to return the functional form of n(ToF) with the tof variable replaced by the input argument.
    ///@param[in] a : The argument to replace tof with
    ///@return The functional form of the parameter with the new tof variable
    std::string GetNFunctionString(const std::string &tof) const {
        return StringManipulation::ReplaceString(nFunction_, "tof", tof);
    }

    ///@brief A method that gets N's ROOT function
    ///@return A TF1 that's used for n
    TF1 GetNRootFunction() const { return nRootFunction_; }

    ///@brief A method that gets the coefficients for sigma
    ///@return A vector of Variables for the coefficients in ascending power
    std::vector<Variable> GetSigmaCoefficients(void) const { return sigmaCoeff_; }

    ///@brief A method to return the functional form of sigma(ToF) with the tof variable replaced by the input argument.
    ///@param[in] a : The argument to replace tof with
    ///@return The functional form of the parameter with the new tof variable
    std::string GetSigmaFunctionString(const std::string &tof) const {
        return StringManipulation::ReplaceString(sigmaFunction_, "tof", tof);
    }

    ///@brief A method that gets Sigma's ROOT function
    ///@return A TF1 that's used for sigma
    TF1 GetSigmaRootFunction() const { return sigmaRootFunction_; }

    ///@brief A method to setup the functional form of alpha(tof)
    ///@param[in] a : The functional form that we want to set, function of the form alpha(tof)
    ///@param[in] b : A vector of Variables for the coefficients in ascending power order.
    ///@throw invalid_argument if we try to set an empty function or if the number of coefficients is wrong.
    void SetupAlphaFunction(const std::string &a, const std::vector<Variable> &b) {
        VerifyInputs("alpha", a, b);
        alphaFunction_ = a;
        alphaCoeff_ = b;
        alphaRootFunction_ = GenerateRootFunction("alpha", a, b);
    }

    ///@brief A method to setup the functional form of n(tof)
    ///@param[in] a : The functional form that we want to set, function of the form n(tof)
    ///@param[in] b : A vector of Variables for the coefficients in ascending power order.
    ///@throw invalid_argument if we try to set an empty function or if the number of coefficients is wrong.
    void SetupNFunction(const std::string &a, const std::vector<Variable> &b) {
        VerifyInputs("n", a, b);
        nFunction_ = a;
        nCoeff_ = b;
        nRootFunction_ = GenerateRootFunction("n", a, b);
    }

    ///@brief A method to setup the functional form of sigma(tof)
    ///@param[in] a : The functional form that we want to set, function of the form sigma(tof)
    ///@param[in] b : A vector of Variables for the coefficients in ascending power order.
    ///@throw invalid_argument if we try to set an empty function or if the number of coefficients is wrong.
    void SetupSigmaFunction(const std::string &a, const std::vector<Variable> &b) {
        VerifyInputs("sigma", a, b);
        sigmaFunction_ = a;
        sigmaCoeff_ = b;
        sigmaRootFunction_ = GenerateRootFunction("sigma", a, b);
    }

private:
    void VerifyInputs(const std::string &name, const std::string &function, const std::vector<Variable> &coeffs);

    TF1 GenerateRootFunction(const std::string &name, const std::string &originalString,
                             const std::vector<Variable> &coeffs);

    std::string alphaFunction_; //!< The functional form of alpha(ToF)
    std::string nFunction_; //!< The functional form of n(ToF)
    std::string sigmaFunction_; //!< The functional form of sigma(ToF)

    TF1 alphaRootFunction_;
    TF1 nRootFunction_;
    TF1 sigmaRootFunction_;

    std::vector<Variable> alphaCoeff_; //!<The vector containing alpha coefficients.
    std::vector<Variable> nCoeff_; //!< The vector containing n coefficients.
    std::vector<Variable> sigmaCoeff_; //!<The vector containing sigma coefficients.
};

#endif //__CRYSTALBALLPARAMETERS_HPP_
