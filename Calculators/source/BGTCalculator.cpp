/** \file BGTCalculator.cpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include "BGTCalculator.hpp"

using namespace std;
using namespace EfficiencyEnums;

static const double bgtCoeff_ = 3812.413; //!< D/(ga/gv)**2 in units of s

///This constructor is used for calculating B(GT)
BGTCalculator::BGTCalculator(const std::map<double, double> &density,
                             const Decay &decay, const Experiment &exp,
                             const std::string &band, const Variable &eg) {
    eG_ = eg;
    decay_ = decay;
    density_ = density;
    omega_ = exp.GetOmegaPerBar()*exp.GetNumBars();
    band_ = band;
    HandleNeutronDensity();
}

///This constructor is used for calculations for a single neutron peak
BGTCalculator::BGTCalculator(Neutron &neutron, const Decay &decay,
                             const Experiment &exp, const Variable &eg) {
    eG_ = eg;
    if(eg.GetValue() != 0.0) {
        geEff_ = eff_.GetEff(eg, EffTypes ::ge);
    }else
        geEff_ = Variable(1.0,0.0,"/100");

    decay_ = decay;
    omega_ = exp.GetOmegaPerBar()*exp.GetNumBars();
    HandleNeutronIndividual(neutron);
}

///This method calculates the B(GT)
///@TODO Change val to something more meaningful
Variable BGTCalculator::CalcBgt(const Variable &en, const Variable &val,
                                const bool &isIndv) {
    Variable br, hl = decay_.GetHalfLife();
    if(isIndv)
        br = CalcBranchingRatio(en, val);
    else
        br = val;

    double halfLife;
    if(band_ == "")
        halfLife = hl.GetValue();
    else if(band_ == "high")
        halfLife = hl.GetValue()-hl.GetError();
    else if(band_ == "low")
        halfLife = hl.GetValue()+hl.GetError();
    else
        halfLife = hl.GetValue();
    double bgt = bgtCoeff_ / CalcF(en) / (halfLife / br.GetValue());
    if(std::isnan(bgt))
        bgt = 0;
    return(Variable(bgt,err_.CalcBgtErr(bgt,br,hl),""));
}

///This method calculates the branching ratio
Variable BGTCalculator::CalcBranchingRatio(const Variable & en,
                                           const Variable &yld) {
    Variable betaEff = eff_.GetBetaEff(en, decay_);

    double br = yld.GetValue() / decay_.GetNumberOfDecays().GetValue() /
        omega_.GetValue() / betaEff.GetValue() / geEff_.GetValue();
    double err = err_.CalcBrErr(br, yld, decay_.GetNumberOfDecays(),
                                geEff_, betaEff);
    return(Variable(br, err, "/100"));
}

///This method calculates the Fermi integral
double BGTCalculator::CalcF(const Variable &en) {
    //------------------------------------------------------------------
    //--------- This routine is adapted from the original basic --------
    //--------- code written by J. Kantele; energies in keV     --------
    //------------------------------------------------------------------
    double betaEp = (decay_.GetQValue().GetValue() - currentEx_.GetValue())*1000.;
    double z = decay_.GetDaughterZ().GetValue();

    double coeff[4][4] = { {-17.2, 7.9015, -2.54, 0.28482,},
                           {3.31368, -2.06273, 0.703822, -0.075039,},
                           {-0.364018, 0.387961, -0.142528, 0.016,},
                           {0.0278071, -0.026519, 0.0098854, -0.00113772} };

    double evalCoeff[4];
    for(int i = 0; i < 4; i++) {
        evalCoeff[i] = coeff[i][0] + log(z) * coeff[i][1] +
            coeff[i][2]*pow(log(z),2.) + coeff[i][3]*pow(log(z),3.);
    }

    double logf = evalCoeff[0] + evalCoeff[1]*log(betaEp) +
        evalCoeff[2]*pow(log(betaEp),2.) + evalCoeff[3]*pow(log(betaEp),3.);

    return(pow(10,logf));
}


///This method calculates the level energy
Variable BGTCalculator::CalcLevelEnergy(const Variable &en) {
    double lvl = en.GetValue() + decay_.GetNeutronSepEnergy().GetValue()
        + eG_.GetValue();
    return(Variable(lvl,0.0,"MeV"));
}

///This method calculates the Log(ft) value
///@TODO Update the name of val so that it reflects something actually useful.
Variable BGTCalculator::CalcLogft(const Variable &en, const Variable &val,
                                  const bool &isIndv) {
    Variable br;
    if(isIndv)
        br = CalcBranchingRatio(en, val);
    else
        br = val;

    double logft = log10(CalcF(en)*(decay_.GetHalfLife().GetValue()
                                    / br.GetValue()));
    return(Variable(logft, err_.CalcLogftErr(br,decay_.GetHalfLife()), ""));
}

///This method fills neutron density map variables
void BGTCalculator::HandleNeutronDensity(void) {
    for(auto it = density_.begin(); it != density_.end(); it++) {
        Variable en = Variable(it->first, 0.0,"MeV");
        Variable den = Variable(it->second,0.0,"MeV");

        currentEx_ = CalcLevelEnergy(en);

        sDensity_.insert(make_pair(currentEx_.GetValue(),it->second));
        bgtMap_.insert(make_pair(currentEx_.GetValue(),
                                 CalcBgt(en,den,false).GetValue()));
        logftMap_.insert(make_pair(currentEx_.GetValue(),
                                   CalcLogft(en,den,false).GetValue()));
    }
}

///This method the fills the info about the neutron into the neutron class
void BGTCalculator::HandleNeutronIndividual(Neutron &neutron) {
    Variable en = neutron.GetEnergy();
    Variable yld = neutron.GetIntegratedYield();

    currentEx_ = CalcLevelEnergy(en);

    neutron.SetBgt(CalcBgt(en,yld));
    neutron.SetBranchingRatio(CalcBranchingRatio(en, yld));
    neutron.SetExcitationEnergy(currentEx_);
    neutron.SetLogft(CalcLogft(en,yld));
}
