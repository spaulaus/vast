/** \file EffCalculator.cpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#include<iostream> 

#include <cmath>

#include "EffCalculator.hpp"
#include "ErrorCalculator.hpp"

using namespace std;

EffCalculator::EffCalculator(const string &type) {
    if(type == "vandle") {
        //Expects the input energy in MeV
        vals_.insert(make_pair("a",  Variable(4.14143,0.0,"")));
        vals_.insert(make_pair("b",  Variable(0.423852, 0.0,"")));
        vals_.insert(make_pair("c",  Variable(0.0, 0.0, "")));
        vals_.insert(make_pair("d",  Variable(3.73002, 0.0, "")));
        vals_.insert(make_pair("e",  Variable(-0.32406, 0.0, "")));
        vals_.insert(make_pair("f",  Variable(0.0562497, 0.0, "")));
        vals_.insert(make_pair("g",  Variable(23.8918, 0.0, "")));
        vals_.insert(make_pair("e1", Variable(0.05, 0.0, "MeV")));
        vals_.insert(make_pair("e2", Variable(1., 0.0, "MeV")));
    }else if(type == "ge") {
        //Expects input energy in keV
        vals_.insert(make_pair("a",  Variable(2.84408,0.02047,"")));
        vals_.insert(make_pair("b",  Variable(1.07362, 0.1042,"")));
        vals_.insert(make_pair("c",  Variable(0.0, 0.0, "")));
        vals_.insert(make_pair("d",  Variable(1.30245, 0.04402, "")));
        vals_.insert(make_pair("e",  Variable(-0.874817, 0.0285, "")));
        vals_.insert(make_pair("f",  Variable(0.0, 0.0, "")));
        vals_.insert(make_pair("g",  Variable(7., 0.0, "")));
        vals_.insert(make_pair("e1", Variable(50., 0.0, "keV")));
        vals_.insert(make_pair("e2", Variable(1000., 0.0, "keV")));
    }
}

Variable EffCalculator::GetEff(const Variable &energy) {
    double x = log(energy.GetValue()/vals_["e1"].GetValue());
    double y = log(energy.GetValue()/vals_["e2"].GetValue());
    double g = vals_["g"].GetValue();

    double xPart = vals_["a"].GetValue() + vals_["b"].GetValue()*x + 
        vals_["c"].GetValue()*x*x;
    double yPart = vals_["d"].GetValue() + vals_["e"].GetValue()*y + 
        vals_["f"].GetValue()*y*y;
    double eff = exp(pow(pow(xPart, -g) + pow(yPart, -g), -1/g) ) /100.;

    ErrorCalculator err;
    return(Variable(eff,err.GetEffErr(vals_,energy),""));
}

Variable EffCalculator::GetSimRollingEff(const Variable &energy) {
    //From Sergey's eff_var_thresh
    //Expects neutron energy in keV
    double a = 29508.583014511;
    double b = -360.519617657447;
    double c = -0.0020863546616623;
    double d = 19.665798880457;
    double eff = (a/(energy.GetValue()-b))+c*energy.GetValue()+d;
    if(eff > 100.)
        return(Variable(1.0, 0.0, ""));
    else
        return(Variable(eff/100., 0.0, ""));
}
