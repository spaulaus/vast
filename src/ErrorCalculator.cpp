/** \file ErrorCalculator.cpp
 *  \brief A class that calculates the errors on variables.
 *  \author S. V. Paulauskas
 *  \date 29 October 2013
 */
#include <iostream>
#include <random>
#include <vector>

#include "ErrorCalculator.hpp"

using namespace std;

double ErrorCalculator::GetEffErr(const map<string,Variable> &vars, 
                                  const Variable &energy) {
    default_random_engine generator;
    map<string, normal_distribution<double> > randDists;
    vector<double> mcEffs;

    for(map<string,Variable>::const_iterator it = vars.begin(); 
        it != vars.end(); it++) {
        if(it->second.GetError() == 0.0)
            continue;
        normal_distribution<double> dist(it->second.GetValue(),
                                            it->second.GetError());
        randDists.insert(make_pair(it->first, dist));
    }
    normal_distribution<double> eDist(energy.GetValue(),
                                      energy.GetError());

    for(unsigned int i = 0; i < numSamples; i++) {
        double a  = randDists["a"](generator);
        double b  = randDists["b"](generator);
        double c  = vars.at("c").GetValue();
        double d  = randDists["d"](generator);
        double e  = randDists["e"](generator);
        double f  = vars.at("f").GetValue();
        double g  = vars.at("g").GetValue();
        double e1 = vars.at("e1").GetValue();
        double e2 = vars.at("e2").GetValue();
        double energy = eDist(generator);

        double x = log(energy/e1);
        double y = log(energy/e2);

        //--------- DEBUGGING -----------
        // cout << a << " " << b << " " << c << " " << d << " " << d << " " 
        //      << e << " " << f << " " << g << " " << e1 << " " << e2 << " " 
        //      << energy << " " << x << " " << y << endl;
        double eff = exp(pow(pow(a+b*x+c*x*x,-g) + 
                             pow(d+e*y+f*y*y,-g), -1/g))/100.;
        mcEffs.push_back(eff);
    }
    
    auto mean = CalcMean(mcEffs);
    auto var  = CalcVariance(mcEffs, mean);
    return(sqrt(var));
}

double ErrorCalculator::CalcMean(const vector<double> &mcVals) {
    double sum = 0;
    for(const auto &i : mcVals)
        sum += i;
    return(sum / mcVals.size());        
}

double ErrorCalculator::CalcVariance(const vector<double> &mcVals,
                                     const double &mean) {
    double var = 0;
    for(const auto &i : mcVals)
        var += pow(i-mean,2);
    return(var/mcVals.size());
}
