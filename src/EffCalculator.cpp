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

Variable EffCalculator::CalcEff(const Variable &energy,
                                std::map<std::string, Variable> &coeffs) {
    double en = energy.GetValue();
    double x = log(en/coeffs["e1"].GetValue());
    double y = log(en/coeffs["e2"].GetValue());
    double g = coeffs["g"].GetValue();

    double xPart = coeffs["a"].GetValue() + coeffs["b"].GetValue()*x +
        coeffs["c"].GetValue()*x*x;
    double yPart = coeffs["d"].GetValue() + coeffs["e"].GetValue()*y +
        coeffs["f"].GetValue()*y*y;

    double eff = exp(pow(pow(xPart, -g) + pow(yPart, -g), -1/g) ) /100.;

    ErrorCalculator err;
    return(Variable(eff,err.CalcEffErr(coeffs,energy),"/100"));
}

Variable EffCalculator::CalcSimRollingEff(const Variable &en) {
    //From Sergey's eff_var_thresh; we currently assume 0 error.
    Variable a = Variable(29508.583014511, 2323, "");
    Variable b = Variable(-360.519617657447, 24.19, "");
    Variable c = Variable(-0.0020863546616623, 0.000257, "");
    Variable d = Variable(19.665798880457, 1.703, "");
    Variable eff = (a/(en-b))+c*en+d;

    if(eff.GetValue() > 100.)
        return(Variable(1.0, 0.0, " / 100"));

    return(Variable(eff.GetValue()/100., 0.0, " / 100"));
}

Variable EffCalculator::GetBetaEff(const Variable &energy, const Decay &dky) {
    Variable qeff = dky.GetQBetaN() - energy;
    qeff = Variable(qeff.GetValue()*1000., qeff.GetError()*1000., "keV");
    double a = 0.0000237963;
    double b = 0.1767496566;
    return(Variable(a*qeff.GetValue()+b, a*qeff.GetError()+b, "/100"));
}

Variable EffCalculator::GetEff(const Variable &energy, const EffTypes &curve) {
    map<string,Variable> coeffs;
    Variable en = energy;
    switch(curve) {
        case(EffTypes::vandle) :
            coeffs.insert(make_pair("a",  Variable(4.14143,0.0,"")));
            coeffs.insert(make_pair("b",  Variable(0.423852, 0.0,"")));
            coeffs.insert(make_pair("c",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("d",  Variable(3.73002, 0.0, "")));
            coeffs.insert(make_pair("e",  Variable(-0.32406, 0.0, "")));
            coeffs.insert(make_pair("f",  Variable(0.0562497, 0.0, "")));
            coeffs.insert(make_pair("g",  Variable(23.8918, 0.0, "")));
            coeffs.insert(make_pair("e1", Variable(0.05, 0.0, "MeV")));
            coeffs.insert(make_pair("e2", Variable(1., 0.0, "MeV")));
            break;
        case(EffTypes::ge) :
            coeffs.insert(make_pair("a",  Variable(2.84408,0.02047,"")));
            coeffs.insert(make_pair("b",  Variable(1.07362, 0.1042,"")));
            coeffs.insert(make_pair("c",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("d",  Variable(1.30245, 0.04402, "")));
            coeffs.insert(make_pair("e",  Variable(-0.874817, 0.0285, "")));
            coeffs.insert(make_pair("f",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("g",  Variable(7., 0.0, "")));
            coeffs.insert(make_pair("e1", Variable(50., 0.0, "keV")));
            coeffs.insert(make_pair("e2", Variable(1000., 0.0, "keV")));
            en = en * Variable(1000, 0.0, "");
            break;
        case(EffTypes::svpBan4) :
            //This new parameterization is from the data provided to Sergey for
            //my 077cu.ban banana 4, he provided these to me on 09-10-2014
            coeffs.insert(make_pair("a",  Variable(-2.55462, 0.1936,"")));
            coeffs.insert(make_pair("b",  Variable(0.556012, 0.09609,"")));
            coeffs.insert(make_pair("c",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("d",  Variable(2.86312, 0.2041, "")));
            coeffs.insert(make_pair("e",  Variable(1.53446, 0.2981, "")));
            coeffs.insert(make_pair("f",  Variable(-0.471158, 0.07326, "")));
            coeffs.insert(make_pair("g",  Variable(50., 0.0, "")));
            coeffs.insert(make_pair("e1", Variable(5.0, 0.0, "MeV")));
            coeffs.insert(make_pair("e2", Variable(0.1, 0.0, "MeV")));
            break;
        case(EffTypes::mmfBan) :
            //The parameterization of the simulation results from Miguel's
            //values sent to Sergey on 03-12-2014
            coeffs.insert(make_pair("a",  Variable(4.78289, 0.09881, "")));
            coeffs.insert(make_pair("b",  Variable(-0.868005, 0.05189, "")));
            coeffs.insert(make_pair("c",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("d",  Variable(2.47813, 0.05167, "")));
            coeffs.insert(make_pair("e",  Variable(-1.98622, 0.7421, "")));
            coeffs.insert(make_pair("f",  Variable(-0.643086, 2.372, "")));
            coeffs.insert(make_pair("g",  Variable(50., 0.0, "")));
            coeffs.insert(make_pair("e1", Variable(0.3, 0.0, "MeV")));
            coeffs.insert(make_pair("e2", Variable(4.0, 0.0, "MeV")));
            break;
        case(EffTypes::rolling) :
            return(CalcSimRollingEff(energy));
        default :
            return(Variable(0.0,0.0,""));
            break;
    }
    return(CalcEff(en, coeffs));
}

