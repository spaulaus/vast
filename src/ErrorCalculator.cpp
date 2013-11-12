/** \file ErrorCalculator.cpp
 *  \brief A class that calculates the errors on variables.
 *  \author S. V. Paulauskas
 *  \date 29 October 2013
 */
#include <iostream>
#include <random>

#include <PhysConstants.hpp>

#include "ErrorCalculator.hpp"

using namespace std;

double ErrorCalculator::CalcBgtErr(const double &bgt, const Variable &br, 
                  const Variable &halfLife) {
    double brPart = br.GetError() / br.GetValue();
    double hlPart = halfLife.GetError() / halfLife.GetValue();
    double sqrtPart = sqrt(pow(brPart,2)+pow(hlPart,2));
    return(bgt*sqrtPart);
}

double ErrorCalculator::CalcBrErr(const double &br, const Variable &yld, const Variable &ndky,
                     const Variable &gammaEff, const Variable &betaEff)
{
    double yldPart = yld.GetError() / yld.GetValue();
    double dkyPart = ndky.GetError() / ndky.GetValue();
    double gammaPart = gammaEff.GetError() / gammaEff.GetValue();
    double betaPart = betaEff.GetError() / betaEff.GetValue();
    double sqrtPart = sqrt(pow(yldPart,2) + pow(dkyPart,2) +
                           pow(gammaPart,2) + pow(betaPart,2));
    return(br*sqrtPart);
}

double ErrorCalculator::CalcEffErr(const map<string,Variable> &vars, 
                                  const Variable &energy) {
    default_random_engine generator;
    map<string, normal_distribution<double> > randDists;
    vector<double> mcEffs;

    for(map<string,Variable>::const_iterator it = vars.begin(); 
        it != vars.end(); it++) {
        if(it->second.GetError() == 0.0)
            continue;
        normal_distribution<double> dist(it->second.GetValue(),
                                            it->second.GetError());
        randDists.insert(make_pair(it->first, dist));
    }
    normal_distribution<double> eDist(energy.GetValue()*1000.,
                                      energy.GetError());

    for(unsigned int i = 0; i < numSamples; i++) {
        double a  = randDists["a"](generator);
        double b  = randDists["b"](generator);
        double c  = vars.at("c").GetValue();
        double d  = randDists["d"](generator);
        double e  = randDists["e"](generator);
        double f  = vars.at("f").GetValue();
        double g  = vars.at("g").GetValue();
        double e1 = vars.at("e1").GetValue();
        double e2 = vars.at("e2").GetValue();
        double energy = eDist(generator);

        double x = log(energy/e1);
        double y = log(energy/e2);

        //--------- DEBUGGING -----------
        // cout << a << " " << b << " " << c << " " << d << " " << d << " " 
        //      << e << " " << f << " " << g << " " << e1 << " " << e2 << " " 
        //      << energy << " " << x << " " << y << endl;
        double eff = exp(pow(pow(a+b*x+c*x*x,-g) + 
                             pow(d+e*y+f*y*y,-g), -1/g))/100.;
        mcEffs.push_back(eff);
    }
    
    auto mean = CalcMean(mcEffs);
    auto var  = CalcVariance(mcEffs, mean);
    return(sqrt(var));
}

double ErrorCalculator::CalcEnergyErr(const Variable &sig, const Variable &mu) {
    PhysConstants consts;
    double c  = consts.GetConstant("c").GetValue()*(100/1e9); // cm / ns
    double mn = consts.GetConstant("neutronMass").GetValue()/c/c; // MeV

    double frac = 0.25;
    double high = 0.5*mn*pow(50.5/(mu.GetValue()-sig.GetValue()*frac),2.);
    double low  = 0.5*mn*pow(50.5/(mu.GetValue()+sig.GetValue()*frac),2.);
    return(high-low);
}

double ErrorCalculator::CalcIntegratedYldErr(const double &fitYldErr, 
                                             const double &fitSimp,
                                             const double &infSimp){
    double xErr = (fitYldErr/fitSimp) * infSimp;
    return(sqrt(xErr*xErr+fitYldErr*fitYldErr));
}

double ErrorCalculator::CalcLogftErr(const Variable &br, const Variable &halfLife) {
    double brPart = br.GetError() / br.GetValue() / log(10);
    double hlPart = halfLife.GetError() / halfLife.GetValue() / log(10);
    return(sqrt(pow(brPart,2)+pow(hlPart,2)));
}

double ErrorCalculator::CalcNumDkyErr(const double &numDky, 
                                        const Variable &rawGammaCounts, 
                                        const Variable &gammaEff, 
                                        const Variable &gammaBr){
    double areaPart = rawGammaCounts.GetError()/ rawGammaCounts.GetValue();
    double effPart  = gammaEff.GetError() / gammaEff.GetValue();
    double brPart  = gammaBr.GetError() / gammaBr.GetValue();
    return(numDky*sqrt(pow(areaPart,2)+pow(effPart,2)+pow(brPart,2)));
}

double ErrorCalculator::CalcPnErr(const double &pn, 
                                  vector<Neutron> &neutrons,
                                  const Decay &dky) {
    double yldPart;
    for(auto &i : neutrons)
        yldPart += pow(i.GetIntegratedYield().GetError()/ 
                       i.GetIntegratedYield().GetValue(),2);
    double ndkyPart = pow(dky.GetNumberDecays().GetError() / 
                          dky.GetNumberDecays().GetValue(),2);
    return(pn*sqrt(yldPart+ndkyPart));
}
                          
//---------- CalcMean
double ErrorCalculator::CalcMean(const vector<double> &mcVals) {
    double sum = 0;
    for(const auto &i : mcVals)
        sum += i;
    return(sum / mcVals.size());        
}

//---------- CalcVariance
double ErrorCalculator::CalcVariance(const vector<double> &mcVals,
                                     const double &mean) {
    double var = 0;
    for(const auto &i : mcVals)
        var += pow(i-mean,2);
    return(var/mcVals.size());
}

