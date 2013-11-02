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
                  const string &file);

vector<string> files = {"077cu-ban4-lower", "077cu-ban4-lower", "-8b", 
                        "results/tof/working/working.fit", 
                        "results/vast/working/working.dat",
                        "results/vast/working/working.mgb",
                        "results/vast/working/working.bgt"};

//---------- SET SOME DETAILS ABOUT THE EXP HERE ----------
//---------- HANDLE THIS BETTER LATER ----------
double numBars = 9;
double omega = numBars*0.0061; // solid angle from Sergey's simulation
//double omega = numBars*4.727e-3; // the calculation for the solid angle
double betaEff = 0.23;
pair<double,double> effs = make_pair(betaEff,omega);

int main(int argc, char* argv[]) {
    bool doesFit = true;
    bool outputBasic = true;
    bool outputTheory = true;
    bool outputNdenBgt = true;
    //---------- SET THE DECAY INFORMATION HERE ---------
    Decay decay(29,10.490,4.558,0.4679); //ParentZ, Q(MeV), Sn(MeV), T1/2(s)
    decay.SetGammaInfo(350311,0.0655391,0.191); //RawNumGammas, eff_gamma, absBr

    //---------- SET FIT INFORMATION AND PERFORM FIT HERE ----------
    pair<double,double> fitRange = make_pair(0.,200.0);
    if(doesFit) {
        //Set the information for the peaks
        vector<double> peaks ={24., 30., 38.128, 40, 44.917,
                               50.181, 56.835, 65.151, 70.826, 80.,
                               87.198, 94.690, 100., 104.69, 110.0, 115.,
                               135.0};
        //peaklist, directory (without data modifier), filename(without .dat), 
        //modifier for file name, fitRange, isTesting
        TofFitter fitter(peaks, files[0], files[1], files[2], fitRange, true);
    }//if(doesFit)
    
    //---------- SET THE NEUTRON INFORMATION AND OUTPUT ----------
    vector<Neutron> singles;
    if(outputBasic) {
        ReadData(singles, files[3]);
        for(vector<Neutron>::iterator it = singles.begin(); it!= singles.end();
            it++) {
            //---------- INTEGRATE THE NEUTRON PEAKS HERE ----------
            Integrator integrator(*it, fitRange);
            //---------- Calculate the B(GT) for the Line ---------
            BGTCalculator bgt(*it, decay, betaEff, omega);
        }
        OutputBasics(singles, decay, files[4]);
    }//if(outputsBasic)
    //---------- B(GT) for the simulations -------
    if(outputBasic && outputTheory) {
        ofstream outTheory(files[5]);
        for(vector<Neutron>::iterator it = singles.begin(); it != singles.end();
            it++) {
            outTheory.setf(ios::fixed);
            outTheory << setprecision(8) << setw(10) 
                      << it->GetExcitationEnergy() << "  " 
                      << it->GetBgt() << endl;
        }
        outTheory.close();
    }//if(outputsBasic && outputsBgt)
    
    //---------- Calculate the B(GT) Using the Neutron Density ---------
    if(outputBasic && outputNdenBgt) {
        NeutronDensity nden(singles, decay.GetQBetaN(), 0.001);
        BGTCalculator ndenBgt(*nden.GetDensity(), decay, betaEff, omega);
        map<double,double> bgtMap = *ndenBgt.GetBgtMap();
        map<double,double> logftMap = *ndenBgt.GetLogftMap();
        map<double,double> sdensityMap = *ndenBgt.GetSDensity();
        
        ofstream outNDenBgt(files[6]);
        outNDenBgt << "#Ex(MeV) BR B(GT) log(ft)" << endl;
        for(map<double,double>::iterator it = bgtMap.begin(); it != bgtMap.end();
            it++) {
            double logft = logftMap.find(it->first)->second;
            double density = sdensityMap.find(it->first)->second;
            outNDenBgt << it->first << " " << density << " " 
                       << it->second << " " << logft << endl;
        }
        outNDenBgt.close();
    }//if(outputsBasic && outputsNdenBgt)
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

                //Set the information for the CB from the fit
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

void OutputBasics(vector<Neutron> &nvec, Decay &dky, const string &file) {
    ofstream out(file.c_str());
    if(out.fail()) {
        cout << endl << endl 
             << "Woah! Could not open up the output file. Check this  " 
             << file << endl << endl;
        exit(1);
    }
            
    double totN  = 0., rawN = 0., intN = 0;
    out << "#Mu(ns) MuErr(ns) E(MeV) EErr(MeV) Yld IntYld BR B(GT) log(ft)" 
            << endl;
    for(vector<Neutron>::iterator it = nvec.begin(); 
        it != nvec.end(); it++) {
        //---------- CALCULATE THE TOTAL NUMBER OF NEUTRONS --------
        intN += it->GetRawIntegratedYield();
        totN += it->GetIntegratedYield() / betaEff / omega;
        rawN += it->GetRawYield();
        
        out << setprecision(12) << it->GetMu() << " " << it->GetMuErr() << " "
            << it->GetEnergy() << " " << it->GetEnergyErr() << " " 
            << it->GetYield() << " " << it->GetIntegratedYield() << " " 
            << it->GetBranchingRatio() << " " 
            << it->GetBgt() << " " << it->GetLogft() << endl;
    }
    out << "#Pn = " << totN << " / " << dky.GetNumberDecays() << " = " 
        << totN / dky.GetNumberDecays() << "  RawN = " << rawN 
        << " " << "  RawIntN = " << intN << endl;
    out.close();
}
