/** \file ex.cpp
 *  \brief Just a simple code to test and play with the classes
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Decay.hpp"
#include "Integrator.hpp"
#include "Neutron.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    int numBars = 9;

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

    double totN  = 0.;
    for(vector<Neutron>::iterator it = neutrons.begin(); 
        it != neutrons.end(); it++) {
        //---------- INTEGRATE THE NEUTRON PEAKS HERE ----------
        Integrator integrator(*it, 0, 200.);

        totN+=(*it).GetIntegratedYield()/0.22/numBars/0.0061;

        // cout << (*it).GetMu() << " " << (*it).GetMuErr() << " "
        //      << (*it).GetEnergy() << " " << (*it).GetEnergyErr() << " " 
        //      << (*it).GetYield() << " " << (*it).GetYieldErr() << " " 
        //      << (*it).GetEfficiency() << " " << (*it).GetAlpha() << " " 
        //      << (*it).GetN() << " " << (*it).GetSigma() << " " 
        //      << (*it).GetIntegratedYield() << " " 
        //      << (*it).GetIntegratedYieldErr() << " " << endl;
    }
    cout << totN << " " << decay.GetNumberDecays() << " " 
         << totN / decay.GetNumberDecays() << endl;
}
