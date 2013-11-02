/** \file ErrorCalculator.hpp
 *  \brief A class that calculates the error on variables.
 *  \author S. V. Paulauskas
 *  \date 29 October 2013
 */
#ifndef __ERRORCALCULATOR_HPP__
#define __ERRORCALCULATOR_HPP__
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <PhysConstants.hpp>

class ErrorCalculator{
public:
    ErrorCalculator(){};
    ~ErrorCalculator(){};

    double GetEffErr(const std::map<std::string,Variable> &vars, 
                     const Variable &energy);
private:
    static const int numSamples=1e5;  // number of experiments

    double CalcMean(const std::vector<double> &mcVals);
    double CalcVariance(const std::vector<double> &mcVals,
                              const double &mean);
};
#endif //__ERRORCALCULATOR_HPP__
