/** \file BGTCalculator.cpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include "BGTCalculator.hpp"
#include "EffCalculator.hpp"

using namespace std;

//Constructor for using the Neutron Density
BGTCalculator::BGTCalculator(map<double,double> &density, const Decay &decay,
                             const Experiment &exp, const string &band, 
                             const Variable &eg) {
    eG_ = eg;
    decay_ = decay;
    density_ = density;
    betaEff_ = exp.GetBetaEff();
    omega_ = exp.GetOmegaPerBar()*exp.GetNumBars();
    band_ = band;
    HandleNeutronDensity(density);
}

//Constructor for using the Neutron Class
BGTCalculator::BGTCalculator(Neutron &neutron, const Decay &decay,
                             const Experiment &exp, const Variable &eg) {
    eG_ = eg;
    if(eg.GetValue() != 0.0) {
        EffCalculator effGe("ge");
        geEff_ = effGe.GetEff(eg); //needs gamma energy in keV
    }else
        geEff_ = Variable(1.0,0.0,"");

    decay_ = decay;
    betaEff_ = exp.GetBetaEff();
    omega_ = exp.GetOmegaPerBar()*exp.GetNumBars();
    HandleNeutronIndividual(neutron);
}

Variable BGTCalculator::CalcBgt(const Variable &en, const Variable &val,
                              const bool &isIndv) {
    double coeff = 3812.413; //D/(ga/gv)**2 in units of s
    Variable br, hl = decay_.GetHalfLife();
    if(isIndv)
        br=CalcBranchingRatio(val);
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
        
    double bgt = coeff/ CalcF(en) /(halfLife/br.GetValue());
    return(Variable(bgt,err.CalcBgtErr(bgt,br,hl),""));
}

Variable BGTCalculator::CalcBranchingRatio(const Variable &yld) { 
    double br = yld.GetValue() / decay_.GetNumberDecays().GetValue() / 
        omega_.GetValue() / betaEff_.GetValue() / geEff_.GetValue();
    return(Variable(br,err.CalcBrErr(br,yld,decay_.GetNumberDecays(),
                                     geEff_,betaEff_), "/100"));
}

double BGTCalculator::CalcF(const Variable &en) {
    //------------------------------------------------------------------
    //--------- This routine is adapted from the original basic --------
    //--------- code written by J. Kantele; energies in keV     --------
    //------------------------------------------------------------------
    double betaEp = (decay_.GetQValue().GetValue()*1000.) - 
        CalcLevelEnergy(en).GetValue()*1000.;
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

Variable BGTCalculator::CalcLevelEnergy(const Variable &en) {
    double lvl = en.GetValue() + decay_.GetNeutronSepEnergy().GetValue() 
        + eG_.GetValue();
    return(Variable(lvl,0.0,"MeV"));
}

Variable BGTCalculator::CalcLogft(const Variable &en, const Variable &val, 
                                const bool &isIndv) {
    Variable br;
    if(isIndv)
        br = CalcBranchingRatio(val);
    else
        br = val;
    double logft = log10(CalcF(en)*(decay_.GetHalfLife().GetValue() 
                                    / br.GetValue()));
    return(Variable(logft, err.CalcLogftErr(br,decay_.GetHalfLife()), ""));
}

void BGTCalculator::HandleNeutronDensity(const map<double,double> &density) {
    for(auto it = density_.begin(); it != density_.end(); it++) {
        Variable en = Variable(it->first, 0.0,"MeV");
        Variable den = Variable(it->second,0.0,"MeV");

        double ex = CalcLevelEnergy(en).GetValue();
        double bgt = CalcBgt(en,den,false).GetValue();
        double logft = CalcLogft(en,den,false).GetValue();

        sDensity_.insert(make_pair(ex,it->second));
        bgtMap_.insert(make_pair(ex,bgt));
        logftMap_.insert(make_pair(ex,logft));
    }
}

void BGTCalculator::HandleNeutronIndividual(Neutron &neutron) {
    Variable en = neutron.GetEnergy();
    Variable yld = neutron.GetIntegratedYield();
    neutron.SetBgt(CalcBgt(en,yld));
    neutron.SetBranchingRatio(CalcBranchingRatio(yld));
    neutron.SetExcitationEnergy(CalcLevelEnergy(en));
    neutron.SetLogft(CalcLogft(en,yld));
}
