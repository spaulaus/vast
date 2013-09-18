/** \file ex.cpp
 *  \brief Just a simple code to test and play with the classes
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "BGTCalculator.hpp"
#include "Decay.hpp"
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
    ofstream outExp("results/noConv/077cu-ban4-lower-noConv.dat");
    double totN  = 0., rawN = 0.;
    outExp << "Ex(MeV) ExErr(MeV) B(GT) log(FT) Yield" 
           << endl;
   for(vector<Neutron>::iterator it = neutrons.begin(); 
        it != neutrons.end(); it++) {
        //---------- INTEGRATE THE NEUTRON PEAKS HERE ----------
        Integrator integrator(*it, 0, 200.);
        //---------- CALCULATE THE TOTAL NUMBER OF NEUTRONS --------
        totN += (*it).GetIntegratedYield() / betaEff / omega;
        rawN += (*it).GetRawYield();

        // outExp << (*it).GetMu() << " " << (*it).GetMuErr() << " " 
        //        << bgt.GetLevelEnergy() << " " << (*it).GetEnergyErr() 
        //        << " " << bgt.GetBgt() << " " << bgt.GetLogft() 
        //        << " " << (*it).GetIntegratedYield() << endl;
    }
    outExp << "#Pn = " << totN << " / " << decay.GetNumberDecays() << " = " 
           << totN / decay.GetNumberDecays() << "  RawN = " << rawN << endl;
 
    //---------- HANDLE THE NEUTRON DENSITY STUFF HERE ---------
    double res[] = {0.250, 0.100, 0.001}; //in MeV
    double len = 10.; // in Mev

    stringstream outname;
    map<double,double> fullDensity;

    for(int i = 0; i < 3; i++) {
        NeutronDensity denGs(neutrons,res[i],len);
        map<double,double> *densityGs = denGs.GetDensity();

        NeutronDensity den2p(neutrons,res[i],len,0.59856); //pass GE in MeV
        map<double,double> *density2p = den2p.GetDensity();
        map<double,double> *density2pShift = den2p.GetGshiftedDensity();

        if(res[i] == 0.001) {
        for(map<double,double>::iterator it = densityGs->begin(); 
            it != densityGs->end(); it++) {
            map<double,double>::iterator pos2p = density2p->find((*it).first);
            map<double,double>::iterator posS2p = 
                density2pShift->find((*it).first);
            double val = (*it).second-(*pos2p).second+(*posS2p).second;
            // if(val < 0)
            //     val = 0.0;
            fullDensity.insert(make_pair((*it).first,val));
        // denGsOut.close();
        // outname << "results/noConv/077cu-ban5-lower-denGS-" 
        //         << res[i] << ".dat";

        // ofstream denOut(outname.str().c_str());
        // outname.str("");
        } //for(map<double,double>
        } //if(res[i]
    }//for(int i = 0; i < 3
    
    //ofstream outTheory("results/noConv/077cu-ban4-lower-noConv.inp");
    // outTheory << bgt.GetLevelEnergy() << " " << bgt.GetBgt() << endl;

    for(map<double,double>::iterator it = fullDensity.begin();
        it != fullDensity.end(); it++)
        cout << (*it).first << " " << (*it).second << endl;
}
