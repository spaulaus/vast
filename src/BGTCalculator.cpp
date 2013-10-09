/** \file BGTCaluclator.cpp
 *  \brief A Class to calculate the B(GT) and log(ft) for a given energy
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <iostream>

#include <cmath>

#include "BGTCalculator.hpp"

using namespace std;

//Constructor for using the Neutron Density
BGTCalculator::BGTCalculator(map<double,double> &density, const Decay &decay,
                             const double &betaEff, const double &omega) {
    eG_ = 0.0;
    decay_ = decay;
    density_ = density;
    betaEff_ = betaEff;
    omega_ = omega;
    CalcBgt();
    CalcLogft();
}

//Constructor for using the Neutron Class
BGTCalculator::BGTCalculator(Neutron &neutron, const Decay &decay,
                             const double &betaEff, const double &omega) {
    eG_ = 0.0;
    eN_ = neutron.GetEnergy();
    yld_ = neutron.GetIntegratedYield();
    decay_ = decay;
    neutron_ = neutron;
    betaEff_ = betaEff;
    omega_ = omega;
    CalcBgt();
    CalcLogft();
    StuffNeutronInfo(neutron);
}

void BGTCalculator::CalcBgt(void) {
    double coeff = 3812.413; //D/(ga/gv)**2 in units of s
    if(density_.empty()) {
        bgt_ = coeff/CalcF(eN_)/
            (decay_.GetHalfLife()/CalcBranchingRatio(yld_));
    }else {
        for(map<double,double>::iterator it = density_.begin();
            it != density_.end(); it++) {
            double bgt = coeff/CalcF(it->first)/
                (decay_.GetHalfLife()/CalcBranchingRatio(it->second));
            bgtMap_.insert(make_pair(CalcLevelEnergy(it->first),bgt));
        }
    }
}

double BGTCalculator::CalcBranchingRatio(const double &yld) { 
    double br = yld / decay_.GetNumberDecays() / omega_ / betaEff_;
    br_ = br;
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
    lvl_ = lvl;
    return(lvl);
}

void BGTCalculator::CalcLogft(void) {
    if(density_.empty())
        logft_ = log10(CalcF(eN_)*(decay_.GetHalfLife() / 
                                   CalcBranchingRatio(yld_)));
    else {
        for(map<double,double>::iterator it = density_.begin();
            it != density_.end(); it++) {
            double logft = log10(CalcF(eN_)*(decay_.GetHalfLife() / 
                                   CalcBranchingRatio(yld_)));
            logftMap_.insert(make_pair(CalcLevelEnergy(it->first),logft));
        }
    }
}

void BGTCalculator::StuffNeutronInfo(Neutron &neutron) {
    neutron.SetBgt(bgt_);
    neutron.SetBranchingRatio(br_);
    neutron.SetExitationEnergy(lvl_);
    neutron.SetLogft(logft_);
}
