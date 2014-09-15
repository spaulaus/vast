/** \file EffCalculator.cpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#include<iostream> 

#include <cmath>

#include "Decay.hpp"
#include "EffCalculator.hpp"
#include "ErrorCalculator.hpp"

using namespace std;

Variable EffCalculator::GetEff(const Variable &energy) {
    double en = energy.GetValue()*1000.;
    double x = log(en/vals_["e1"].GetValue());
    double y = log(en/vals_["e2"].GetValue());
    double g = vals_["g"].GetValue();

    double xPart = vals_["a"].GetValue() + vals_["b"].GetValue()*x + 
        vals_["c"].GetValue()*x*x;
    double yPart = vals_["d"].GetValue() + vals_["e"].GetValue()*y + 
        vals_["f"].GetValue()*y*y;

    double eff = exp(pow(pow(xPart, -g) + pow(yPart, -g), -1/g) ) /100.;

    ErrorCalculator err;
    return(Variable(eff,err.CalcEffErr(vals_,energy),"/100"));
}

Variable EffCalculator::GetSimRollingEff(const Variable &energy) {
    //Expects neutron energy in keV
    double en = energy.GetValue() * 1000.;

    //From Sergey's eff_var_thresh; we currently assume 0 error.
     // double a = 29508.583014511;
     // double b = -360.519617657447;
     // double c = -0.0020863546616623;
     // double d = 19.665798880457;
     // double eff = (a/(en-b))+c*en+d;

     // if(eff > 100.)
     //     return(Variable(1.0, 0.0, " / 100"));
     // else
     //     return(Variable(eff/100., 0.0, " / 100"));

    //The parameterization of the simulation results from Miguel's 
    //values sent to Sergey on 03-12-2014
    // Variable a = Variable(-3.449922e-10, 1.561986e-10, "");
    // Variable b = Variable(4.477057e-06 ,1.692577e-06,"");
    // Variable c = Variable(-2.302741e-02 ,5.748920e-03,""); 
    // Variable d = Variable(5.416032e+01 ,6.028794e+00,"");
    // double eff = a.GetValue()*pow(en,3) + b.GetValue()*pow(en,2) +
    //     c.GetValue()*en+d.GetValue();

    //This new parameterization is from the data provided to Sergey for 
    //my 077cu.ban banana number 4, he provided these to me on 09-10-2014 
    //and the calculation only went through 1.5 MeV, points below that are 
    //extrapolation.
    Variable a = Variable(-0.409366, 0.2148, ""); 
    Variable b = Variable(-2.25262, 1.407, "");
    Variable c = Variable(24.6331, 2.112, "");
    double eff = a.GetValue()*pow(en/1000.,2) +
        b.GetValue()*en/1000.+c.GetValue();

    return(Variable(eff/100.,0.0,"/100"));
}

Variable EffCalculator::GetBetaEff(const Variable &energy, const Decay &dky) {
    Variable qeff = dky.GetQBetaN() - energy;
    qeff = Variable(qeff.GetValue()*1000., qeff.GetError()*1000., "keV");
    double a = 0.0000237963;
    double b = 0.1767496566;
    return(Variable(a*qeff.GetValue()+b, a*qeff.GetError()+b, "/100"));
}

void EffCalculator::SetVariables(const string &type) {
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

