/** \file EffCalculator.cpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#include <cmath>

#include "EffCalculator.hpp"

using namespace std;

EffCalculator::EffCalculator(const string &type) {
    if(type == "vandle") {
        //Expects the input energy in MeV
        a_ = 4.14143;
        b_ = 0.423852;
        c_ = 0.0;
        d_ = 3.73002;
        e_ = -0.32406;
        f_ = 0.0562497;
        g_ = 23.8918;
        e1_ = 0.05;
        e2_ = 1.;
    }else if(type == "ge") {
        //Expects input energy in keV
        a_ = 2.87464;
        b_ = 1.18405;
        c_ = 0.0;
        d_ = 1.30942;
        e_ = -0.803908;
        f_ = 0.0480939;
        g_ = 5.33374;
        e1_ = 50.;
        e2_ = 1000.;
    }
}

double EffCalculator::GetEff(const double &energy) {
    double x = log(energy/e1_);
    double y = log(energy/e2_);                     
    
    return(exp(pow(pow(a_+b_*x+c_*x*x,-g_) + 
                   pow(d_+e_*y+f_*y*y,-g_), -1/g_)))/100.;
}

double EffCalculator::GetSimRollingEff(const double &energy) {
    //From Sergey's eff_var_thresh
    //Expects neutron energy in keV
    return((52349.3/(energy+572.064)+5.17822)/100.);
}
