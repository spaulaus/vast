/** \file ex.cpp
 *  \brief Just a simple code to test and play with the classes
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include "BGTCalculator.hpp"
#include "Decay.hpp"
#include "Integrator.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"
#include "TofFitter.hpp"

using namespace std;

void ReadData(vector<Neutron> &nvec, const string &file);
void OutputBasics(vector<Neutron> &nvec, Decay &dky, 
                  const string &file, const pair<double,double> &rng);

int main(int argc, char* argv[]) {
    //---------- SET THE DECAY INFORMATION HERE ---------
    Decay decay(29,10.490,4.558,0.4679); //ParentZ, Q(MeV), Sn(MeV), T1/2(s)
    decay.SetGammaInfo(350311,0.0655391,0.191); //RawNumGammas, eff_gamma, absBr

    //---------- SET FIT INFORMATION AND PERFORM FIT HERE ----------
    pair<double,double> fitRange = make_pair(0.,200.0);
   //Set the information for the peaks
    vector<double> peaks ={24., 30., 38.128, 40, 44.917,
                           50.181, 56.835, 65.151, 70.826, 80.,
                           87.198, 94.690, 100., 104.69, 110.0, 115.,
                           135.0};
    //peaklist, directory (without data modifier), filename(without .dat), 
    //modifier for file name, fitRange, isTesting
    TofFitter fitter(peaks, "tof/077cu-ban4-lower", "077cu-ban4-lower", 
                     "-8keVee-b", fitRange, true);
    
    //---------- SET THE NEUTRON INFORMATION HERE ----------
    vector<Neutron> singles;
    ReadData(singles,"results/tof/working/working.fit");
    OutputBasics(singles, decay,
                 "results/vast/working/working.dat", fitRange);
    //ReadData(singles,"data/077cu-ban4-lower/077cu-ban4-lower-8keVee-b.fit");
    // OutputBasics(singles, decay,
    //              "results/vast/077cu-ban4-lower/077cu-ban4-lower-8keVee-b.dat", 
    //              fitRange);
    
    // vector<Neutron> twoPlus;
    // ReadData(twoPlus, 
    //          "data/077cu-ban4-lower/077cu-ban4-lower-02Plus-noConv.out");
    // OutputBasics(twoPlus, decay,
    //              "results/vast/077cu-ban4-lower/077cu-ban4-lower-2p.dat");

    //---------- HANDLE THE NEUTRON DENSITY STUFF HERE ---------
    // double res[] = {0.250, 0.100, 0.001}; //in MeV
    // double len = 10.; // in Mev
    
    // stringstream outname;
    // map<double,double> fullDensity;
    // for(int i = 0; i < 3; i++) {
    //     outname << "results/noConv/077cu-ban4-lower-nDensity-" 
    //             << res[i] << ".dat";
    //     ofstream denOut(outname.str().c_str());
    //     denOut << "#Energy(MeV) Sngl 2Plus Shft2Plus Full" << endl;
    //     NeutronDensity denGs(singles,res[i],len);
    //     map<double,double> *densityGs = denGs.GetDensity();
        
    //     NeutronDensity den2p(twoPlus,res[i],len,0.59856); //pass GE in MeV
    //     map<double,double> *density2p = den2p.GetDensity();
    //     map<double,double> *density2pShift = den2p.GetGshiftedDensity();
        
    //     for(map<double,double>::iterator it = densityGs->begin(); 
    //         it != densityGs->end(); it++) {
    //         map<double,double>::iterator pos2p = 
    //             density2p->find((*it).first);
    //         map<double,double>::iterator posS2p = 
    //             density2pShift->find((*it).first);
            
    //         double val = (*it).second-(*pos2p).second+(*posS2p).second;
    //         fullDensity.insert(make_pair((*it).first,val));
    //         denOut << (*it).first << " " << (*it).second << " " 
    //                << (*pos2p).second << " " 
    //                << (*posS2p).second << " " 
    //                << val << endl;
    //     } //for(map<double,double>
    //     outname.str("");
    //     denOut.close();
    // }//for(int i = 0; i < 3

    //ofstream outTheory("results/noConv/077cu-ban4-lower-noConv.inp");
    // outTheory << bgt.GetLevelEnergy() << " " << bgt.GetBgt() << endl;
}

void ReadData(vector<Neutron> &nvec, const string &file) {
    ifstream data(file.c_str());
    if(data.is_open()) {
        while(data.good()) {
            if(isdigit(data.peek())) {
                double junk, temp0, temp1, temp2, temp3, a, s, n;
                data >> junk >> temp0 >> temp1 >> temp2 >> temp3 >> s
                     >> a >> n;
                nvec.push_back(Neutron(temp0,temp1,temp2,temp3));
                nvec.back().SetSigma(s);
                nvec.back().SetAlpha(a);
                nvec.back().SetN(n);
            }else {
                data.ignore(1000,'\n');
            }
        }
    } else{
        cout << "Oh, Jesus! We could no open the file: " 
             << file << endl << "Please check the name and try again."
             << endl << endl;
        exit(1);
    }
    data.close();
}

void OutputBasics(vector<Neutron> &nvec, Decay &dky, 
                  const string &file, const pair<double,double> &rng) {
    double numBars = 9;
    double omega = numBars*0.0061; // solid angle from Sergey's simulation
    //double omega = numBars*4.727e-3; // the calculation for the solid angle
    double betaEff = 0.23;
    
    ofstream out(file.c_str());
    if(out.fail()) {
        cout << endl << endl 
             << "Woah! Could not open up the output file. Check this  " 
             << file << endl << endl;
        exit(1);
    }
            
    double totN  = 0., rawN = 0., intN = 0;
    out << "#Mu(ns) MuErr(ns) E(MeV) EErr(MeV) RawYld RawIntYld EffYld EffIntYld" 
            << endl;
    for(vector<Neutron>::iterator it = nvec.begin(); 
        it != nvec.end(); it++) {
        //---------- INTEGRATE THE NEUTRON PEAKS HERE ----------
        Integrator integrator(*it, rng);
        //---------- CALCULATE THE TOTAL NUMBER OF NEUTRONS --------
        intN += (*it).GetRawIntegratedYield();
        totN += (*it).GetIntegratedYield() / betaEff / omega;
        rawN += (*it).GetRawYield();
        
        out << setprecision(12) << (*it).GetMu() << " " << (*it).GetMuErr() << " "
            << (*it).GetEnergy() << " " << (*it).GetEnergyErr() << " " 
            << " " << (*it).GetRawYield() << " " << (*it).GetRawIntegratedYield() 
            << " " << (*it).GetYield() 
            << " " << (*it).GetIntegratedYield() << endl;
    }
    out << "#Pn = " << totN << " / " << dky.GetNumberDecays() << " = " 
        << totN / dky.GetNumberDecays() << "  RawN = " << rawN 
        << " " << "  RawIntN = " << intN << endl;
    out.close();
}
