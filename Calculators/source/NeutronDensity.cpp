/** \file NeutronDensity.cpp
 *  \brief A class that contains information about the neutron density
 *  \author S. V. Paulauskas
 *  \date 07 September 2013
 */
#include <iostream>

#include <cmath>

#include "EffCalculator.hpp"
#include "NeutronDensity.hpp"

using namespace std;

static const double stepSize_ = 0.001; //! The step size for sampling the Gaussian

NeutronDensity::NeutronDensity(std::vector<Neutron> &neutrons,
                               const double &qbetan, const Variable &ge) {
    qbetan_  = qbetan;
    neutrons_ = neutrons;

    if(ge.GetValue() == 0)
        CalcDensity(ge, Variable(1.0,0.0,""));
    else {
        EffCalculator eff;
        CalcDensity(ge, eff.GetEff(ge, EffCalculator::EffTypes::ge));
    }
}

void NeutronDensity::CalcDensity(const Variable &ge, const Variable &geEff) {
    for(vector<Neutron>::iterator it = neutrons_.begin();
        it != neutrons_.end(); it++) {
        double br = it->GetBranchingRatio().GetValue();
        double brErr = it->GetBranchingRatio().GetError();
        vector<double> brList = {br-brErr,br,br+brErr};

        mu_ = it->GetEnergy().GetValue()+ge.GetValue();
        sigma_ = it->GetEnergy().GetError();

        for(auto const &i : brList) {
            amplitude_ = i*stepSize_;

            map<double,double> *tempMap;
            if(i == br-brErr)
                tempMap = &denLow_;
            else if (i == br)
                tempMap = &denMean_;
            else if (i == br+brErr)
                tempMap = &denHigh_;

            for(double j = 0.0; j <= qbetan_; j+=stepSize_) {
                auto temp = tempMap->find(j);
                double val = Gaussian(j) / geEff.GetValue();
                if(temp != tempMap->end())
                    temp->second += val;
                else
                    tempMap->insert(make_pair(j,val));
            }
        }
    }
}

double NeutronDensity::Gaussian(const double &x) {
    double coeff = amplitude_/(sigma_*sqrt(2*M_PI));
    double exponent = -pow((x-mu_)/sigma_,2)*0.5;
    return( coeff * exp(exponent) );
}
