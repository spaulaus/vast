/** \file ex.cpp
 *  \brief Just a simple code to test and play with the classes
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "BGTCalculator.hpp"
#include "Decay.hpp"
#include "DensityCalculator.hpp"
#include "Integrator.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    double numBars = 9;
    double omega = numBars*0.0061; // solid angle from Sergey's simulation
    //double omega = numBars*4.727e-3; // the calculation for the solid angle
    double betaEff = 0.22;

    //---------- SET THE DECAY INFORMATION HERE ---------
    Decay decay(29,10.490,4.558,0.4679); //ParentZ, Q(MeV), Sn(MeV), T1/2(s)
    decay.SetGammaInfo(350311,0.0655391,0.191); //RawNumGammas, eff_gamma, absBr

    //---------- SET THE NEUTRON INFORMATION HERE ----------
    vector<Neutron> neutrons;
    ifstream data("data/077cu-ban4-lower/077cu-ban4-lower-tof-noConv.out");
    if(data.is_open()) {
        while(data.good()) {
            if(isdigit(data.peek())) {
                double junk, temp0, temp1, temp2, temp3;
                data >> junk >> temp0 >> temp1 >> temp2 >> temp3 >> junk;
                neutrons.push_back(Neutron(temp0,temp1,temp2,temp3));
            }else {
                data.ignore(1000,'\n');
            }
        }
    }
    data.close();

    //---------- SET THE OUTPUT FILES ----------
    ofstream outTheory("results/noConv/077cu-ban4-lower-noConv.inp");
    ofstream outExp("results/noConv/077cu-ban4-lower-noConv.dat");

    double totN  = 0., rawN = 0.;
    for(vector<Neutron>::iterator it = neutrons.begin(); 
        it != neutrons.end(); it++) {
        //---------- INTEGRATE THE NEUTRON PEAKS HERE ----------
        Integrator integrator(*it, 0, 200.);
        //---------- CALCULATE THE TOTAL NUMBER OF NEUTRONS --------
        totN += (*it).GetIntegratedYield() / betaEff / omega;
        rawN += (*it).GetRawYield();
    }
    outExp << "#Pn = " << totN << " / " << decay.GetNumberDecays() << " = " 
           << totN / decay.GetNumberDecays() << "  RawN = " << rawN << endl;
    outExp << "Ex(MeV) ExErr(MeV) B(GT) log(FT) Yield" 
           << endl;

    //---------- HANDLE THE NEUTRON DENSITY STUFF HERE ---------
    double res = 0.250, res1 = 0.05, len = 10.; // res and len in Mev
    // vector<double> sumDen250(int(len/res)+1);
    // vector<double> sumDen001(int(len/res)+1);

    //NeutronDensity den250(neutrons,res,len);
    NeutronDensity den100(neutrons,res1,len);

    // vector<double> *density = denCalc.GetDensity();
    // for(unsigned int i = 0; i < density->size(); i++)
    //     sumDen250.at(i) += density->at(i);
    // for(unsigned int i = 0; i < sumDen250.size(); i++)
    //     cout << i*res << " " << sumDen250[i] << endl;
    // outExp << (*it).GetMu() << " " << (*it).GetMuErr() << " " 
    //        << bgt.GetLevelEnergy() << " " << (*it).GetEnergyErr() 
    //        << " " << bgt.GetBgt() << " " << bgt.GetLogft() 
    //        << " " << (*it).GetIntegratedYield() << endl;
    
    // outTheory << bgt.GetLevelEnergy() << " " << bgt.GetBgt() << endl;
}
