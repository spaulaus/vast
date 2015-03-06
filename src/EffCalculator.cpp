/** \file EffCalculator.cpp
 *  \brief A class to calculate efficiencies
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#include<iostream>

#include <cmath>

#include <PhysConstants.hpp>

#include "Decay.hpp"
#include "EffCalculator.hpp"
#include "ErrorCalculator.hpp"

using namespace std;

Variable EffCalculator::CalcEff(const Variable &energy, std::map<std::string,
                                Variable> &coeffs) {
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

double EffCalculator::CalcTof(const double &en) {
    PhysConstants consts;
    double c  = consts.GetConstant("c").GetValue()*(100/1e9);
    double mn = consts.GetConstant("neutronMass").GetValue()/c/c;
    return(distance_ * sqrt(mn/2/en));
}

Variable EffCalculator::CalcMmfAdjusted(const Variable &en) {
    double eff = 0.0;
    double tof = CalcTof(en.GetValue());
    if (tof < 26.25) {
        eff = pow(10,-0.56779 - 0.30214*log10(en.GetValue())
                    + 0.06163*pow(log10(en.GetValue()),2)
                    + 8.6109*pow(log10(en.GetValue()),3)
                    - 26.803*pow(log10(en.GetValue()),4)
                    + 5.6116*pow(log10(en.GetValue()),5)
                    + 53.225*pow(log10(en.GetValue()),6)
                    - 48.326*pow(log10(en.GetValue()),7));
        eff = eff * (tof*0.04847845-0.2069092); //banana correction
    }else if (tof >= 26.25 && tof <= 30.0) {
        eff = pow(10, -0.4887-0.50485*log10(en.GetValue())
                    +0.31886*pow(log10(en.GetValue()),2)
                    +4.7401*pow(log10(en.GetValue()),3)
                    -4.1318*pow(log10(en.GetValue()),4)
                    -19.607*pow(log10(en.GetValue()),5)
                    +4.0407*pow(log10(en.GetValue()),6)
                    +28.821*pow(log10(en.GetValue()),7));
        eff = eff * (tof*0.030117+0.109063); //banana correction
    }else if (tof > 30.9) {
        eff= pow(10, -0.38866-0.31627*log10(en.GetValue())
                    +0.322206*pow(log10(en.GetValue()),2)
                    +0.04875*pow(log10(en.GetValue()),3)
                    -0.41693*pow(log10(en.GetValue()),4)
                    -0.13806*pow(log10(en.GetValue()),5));
        if (tof <= 34)
            eff = eff * (tof*0.122664 - 3.2250166667); //ban correction
        else if (tof > 34 && tof <= 55)
            eff = eff * (tof*0.0033386667 + 0.8055463333); //ban correction
    }else
        eff = 0.0;
    return(Variable(eff, 0.0, " / 100"));
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
            coeffs.insert(make_pair("a",  Variable(3.16156, 0.6946, "")));
            coeffs.insert(make_pair("b",  Variable(0.547724, 0.3057, "")));
            coeffs.insert(make_pair("c",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("d",  Variable(3.44128, 0.01617, "")));
            coeffs.insert(make_pair("e",  Variable(-0.206794, 0.03284, "")));
            coeffs.insert(make_pair("f",  Variable(0.0520048, 0.01448, "")));
            coeffs.insert(make_pair("g",  Variable(27.0, 0.0, "")));
            coeffs.insert(make_pair("e1", Variable(0.01, 0.0, "MeV")));
            coeffs.insert(make_pair("e2", Variable(3.0, 0.0, "MeV")));
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
        case(EffTypes::svpTestBan1) :
            coeffs.insert(make_pair("a",  Variable(4.4967, 0.3058,"")));
            coeffs.insert(make_pair("b",  Variable(-0.658414, 0.0657,"")));
            coeffs.insert(make_pair("c",  Variable(0.0, 0.0, "")));
            coeffs.insert(make_pair("d",  Variable(6.21952, 0.5401, "")));
            coeffs.insert(make_pair("e",  Variable(4.89239, 0.3106, "")));
            coeffs.insert(make_pair("f",  Variable(-1.49588, 0.08555, "")));
            coeffs.insert(make_pair("g",  Variable(1.43805, 0.2167, "")));
            coeffs.insert(make_pair("e1", Variable(1.0, 0.0, "MeV")));
            coeffs.insert(make_pair("e2", Variable(0.1, 0.0, "MeV")));
        case(EffTypes::mmfTheory) :
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
        case(EffTypes::mmfCalc) :
            return(CalcMmfAdjusted(energy));
        case(EffTypes::rolling) :
            return(CalcSimRollingEff(energy));
        default :
            return(Variable(0.0,0.0,""));
            break;
    }
    return(CalcEff(en, coeffs));
}
