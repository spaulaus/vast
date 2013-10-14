/** \file BGTCaluclator.cpp
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
                             const double &betaEff, const double &omega, 
                             const double &eg) {
    eG_ = eg;
    decay_ = decay;
    density_ = density;
    betaEff_ = betaEff;
    omega_ = omega;
    HandleNeutronDensity(density);
}

//Constructor for using the Neutron Class
BGTCalculator::BGTCalculator(Neutron &neutron, const Decay &decay,
                             const double &betaEff, const double &omega,
                             const double &eg) {
    eG_ = eg;
    if(eg != 0) {
        EffCalculator effGe("ge");
        geEff_ = effGe.GetEff(eg*1000.); //needs gamma energy in keV
    }else
        geEff_ = 1.0;
    decay_ = decay;
    betaEff_ = betaEff;
    omega_ = omega;
    HandleNeutronIndividual(neutron);
}

double BGTCalculator::CalcBgt(const double &en, const double &val,
                              const bool &isIndv) {
    double coeff = 3812.413; //D/(ga/gv)**2 in units of s
    double bgt;
    if(isIndv)
        bgt = coeff/ CalcF(en) /
            (decay_.GetHalfLife()/CalcBranchingRatio(val));
    else 
        bgt = coeff/ CalcF(en) /
            (decay_.GetHalfLife()/val);
    return(bgt);
}

double BGTCalculator::CalcBranchingRatio(const double &yld) { 
    double br = yld / decay_.GetNumberDecays() / omega_ / betaEff_ / geEff_;
    return(br);
}

double BGTCalculator::CalcF(const double &en) {
    //------------------------------------------------------------------
    //--------- This routine is adapted from the original basic --------
    //--------- code written by J. Kantele; energies in keV     --------
    //------------------------------------------------------------------
    double betaEp = (decay_.GetQValue()*1000.) - CalcLevelEnergy(en)*1000.;
    double z = decay_.GetDaughterZ();

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

double BGTCalculator::CalcLevelEnergy(const double &en) {
    double lvl = en + decay_.GetNeutronSepEnergy() + eG_;
    return(lvl);
}

double BGTCalculator::CalcLogft(const double &en, const double &val, 
                                const bool &isIndv) {
    double logft;
    if(isIndv)
        logft = log10(CalcF(en)*(decay_.GetHalfLife() / 
                                 CalcBranchingRatio(val)));
    else
        logft = log10(CalcF(en)*(decay_.GetHalfLife() / val));
    return(logft);
}

void BGTCalculator::HandleNeutronDensity(const map<double,double> &density) {
    for(map<double,double>::iterator it = density_.begin();
        it != density_.end(); it++) {
        double ex = CalcLevelEnergy(it->first);
        double bgt = CalcBgt(it->first,it->second, false);
        double logft = CalcLogft(it->first,it->second, false);
        sDensity_.insert(make_pair(ex,it->second));
        bgtMap_.insert(make_pair(ex,bgt));
        logftMap_.insert(make_pair(ex,logft));
    }
}

void BGTCalculator::HandleNeutronIndividual(Neutron &neutron) {
    double en = neutron.GetEnergy();
    double yld = neutron.GetIntegratedYield();
    neutron.SetBgt(CalcBgt(en,yld));
    neutron.SetBranchingRatio(CalcBranchingRatio(yld));
    neutron.SetExitationEnergy(CalcLevelEnergy(en));
    neutron.SetLogft(CalcLogft(en,yld));
}

