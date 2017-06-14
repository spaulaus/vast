/** \file CrystalBallParameters.hpp
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#ifndef __CRYSTALBALLPARAMETERS_HPP_
#define __CRYSTALBALLPARAMETERS_HPP_

#include <vector>

#include "Exception.hpp"
#include "StringManipulation.hpp"
#include "Variable.hpp"

///A class to calculate the parameterized alpha, n, and sigma for Crystal Balls
class CrystalBallParameters {
public:
    ///@brief Default constructor
    CrystalBallParameters() {}

    ///@brief A constructor directly setting the values of the coefficients
    ///@param[in] a : A vector of variables to assign to the private variable alphaCoeff_
    ///@param[in] n : A vector of variables to assign to the private variable nCoeff_
    ///@param[in] s : A vector of variables to assign to the private variable sigmaCoeff_
    CrystalBallParameters(const std::vector<Variable> &a, const std::vector<Variable> &n,
                          const std::vector<Variable> &s) : alphaCoeff_(a), nCoeff_(n), sigmaCoeff_(s)  { }

    ///@brief Default destructor
    ~CrystalBallParameters() {}

    ///@brief Calculate the alpha parameter from the CB
    ///@param[in] tof the time of flight
    ///@return The break point for the Gaussian and Power parts of the CB
    double CalcAlpha(const double &tof) const;

    ///@brief Calculate the n parameter for the CB
    ///@param[in] tof the time of flight
    ///@return The power parameter of the CB */
    double CalcN(const double &tof) const;

    ///@brief Calculate the sigma parameter for the CB
    ///@param[in] tof the time of flight
    ///@return The width of the Gaussian part of the CB
    double CalcSigma(const double &tof) const;

    ///@brief A method that gets the coeffieicnts for alpha
    ///@return A vector of Variables for the coefficients in ascending power
    std::vector<Variable> GetAlphaCoefficients(void) const { return alphaCoeff_; }

    ///@brief A method to return the functional form of alpha(ToF) with the tof variable replaced by the input argument.
    ///@param[in] a : The argument to replace tof with
    ///@return The functional form of the parameter with the new tof variable
    std::string GetAlphaFunction(const std::string &tof) const {
        return StringManipulation::ReplaceString(alphaFunction_, "tof", tof);
    }

    ///@brief A method that gets the coeffieicnts for n
    ///@return A vector of Variables for the coefficients in ascending power
    std::vector<Variable> GetNCoefficients(void) const { return nCoeff_; }

    ///@brief A method to return the functional form of n(ToF) with the tof variable replaced by the input argument.
    ///@param[in] a : The argument to replace tof with
    ///@return The functional form of the parameter with the new tof variable
    std::string GetNFunction(const std::string &tof) const {
        return StringManipulation::ReplaceString(nFunction_, "tof", tof);
    }

    ///@brief A method that gets the coeffieicnts for sigma
    ///@return A vector of Variables for the coefficients in ascending power
    std::vector<Variable> GetSigmaCoefficients(void) const { return sigmaCoeff_; }

    ///@brief A method to return the functional form of sigma(ToF) with the tof variable replaced by the input argument.
    ///@param[in] a : The argument to replace tof with
    ///@return The functional form of the parameter with the new tof variable
    std::string GetSigmaFunction(const std::string &tof) const {
        return StringManipulation::ReplaceString(sigmaFunction_, "tof", tof);
    }

    ///@brief A method that sets the coeffieicnts for alpha
    ///@param[in] a : A vector of Variables for the coefficients in ascending power order.
    ///@throws invalid_argument if the vector size isn't 4
    void SetAlphaCoefficients(const std::vector<Variable> &a) {
        if (a.size() != 4)
            throw std::invalid_argument("CrystalBallParameters::SetAlphaCoefficients - alpha(ToF) needs to have 4 "
                                       "coefficients!");
        alphaCoeff_ = a;
    }

    ///@brief A method to set the functional form of alpha(tof)
    ///@param[in] a : The functional form that we want to set, function of the form alpha(tof)
    ///@throws invalid_argument if the function string is empty
    void SetAlphaFunction(const std::string &a) {
        if (a == "")
            throw std::invalid_argument("CrystalBallParameters::SetAlphaFunction - The functional string was empty!");
        alphaFunction_ = a;
    }

    ///@brief A method that sets the coeffieicnts for n
    ///@param[in] a : A vector of Variables for the coefficients in ascending power order.
    ///@throws invalid_argument if the vector size isn't 3
    void SetNCoefficients(const std::vector<Variable> &a) {
        if (a.size() != 3)
            throw std::invalid_argument("CrystalBallParameters::SetNCoefficients - n(ToF) needs to have 3 coefficients!");
        nCoeff_ = a;
    }

    ///@brief A method to set the functional form of n(tof)
    ///@param[in] a : The functional form that we want to set, function of the form n(tof)
    ///@throws invalid_argument if we try to set an empty argument
    void SetNFunction(const std::string &a) {
        if (a == "")
            throw std::invalid_argument("CrystalBallParameters::SetNFunction - The functional string was empty!");
        nFunction_ = a;
    }

    ///@brief A method that sets the coefficients for sigma
    ///@param[in] a : A vector of Variables for the coefficients in ascending power order.
    ///@throws invalid_argument if the size of the vector isn't 5
    void SetSigmaCoefficients(const std::vector<Variable> &a) {
        if (a.size() != 5)
            throw std::invalid_argument("CrystalBallParameters::SetSigmaCoefficients - sigma(ToF) needs to have 5 coefficients!");
        sigmaCoeff_ = a;
    }

    ///@brief A method to set the functional form of sigma(tof)
    ///@param[in] a : The functional form that we want to set, function of the form sigma(tof)
    ///@throws invalid_argument if we try to set an empty function
    void SetSigmaFunction(const std::string &a) {
        if (a == "")
            throw std::invalid_argument("CrystalBallParameters::SetSigmaFunction - The functional string was empty!");
        sigmaFunction_ = a;
    }

private:
    std::string alphaFunction_; //!< The fucntional form of alpha(ToF)
    std::string nFunction_; //!< The fucntional form of n(ToF)
    std::string sigmaFunction_; //!< The fucntional form of sigma(ToF)

    std::vector<Variable> alphaCoeff_; //!<The vector containing alpha coeff.
    std::vector<Variable> nCoeff_; //!< The vector containing n coefficients.
    std::vector<Variable> sigmaCoeff_; //!<The vector containing sigma coeff.
};

#endif //__CrystalBallParameters_HPP_
