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

#include <Variable.hpp>

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
Variable omega = Variable(numBars*0.0061,0.0,""); //solid angle from Sergey's sim
//double omega = numBars*4.727e-3; // the calculation for the solid angle
Variable betaEff = Variable(0.23, 0.03, "/100"); // the error needs recalculated.
pair<Variable,Variable> effs = make_pair(betaEff,omega);

int main(int argc, char* argv[]) {
    bool doesFit = true;
    bool outputBasic = true;
    bool outputTheory = true;
    bool outputNdenBgt = true;
    //---------- SET THE DECAY INFORMATION HERE ---------
    //ParentZ, Q(MeV), Sn(MeV), Qbetan(MeV), T1/2(s)
    Decay decay(Variable(29,0.0,""),Variable(10.490,0.500,"MeV"),
                Variable(4.5575,0.00025,"MeV"), Variable(5.720,0.015,"MeV"),
                Variable(0.4679,0.00021, "s")); 
    //RawNumGammas, eff_gamma, absBr
    decay.SetGammaInfo(Variable(351222,14751.324,"counts"),
                       Variable(0.0668422,0.003,"/100"),
                       Variable(0.191, 0.006, "/100")); 

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
            outTheory << it->GetExcitationEnergy().GetValue() << "  " 
                      << it->GetBgt().GetValue() << " " 
                      << it->GetEnergy().GetError();
            auto itNext = it;
            if(itNext++ != singles.end())
                cout << endl;
        }
        outTheory.close();
    }//if(outputsBasic && outputsBgt)
    
    //---------- Calculate the B(GT) Using the Neutron Density ---------
    if(outputBasic && outputNdenBgt) {
        double res = 0.001; // MeV
        NeutronDensity nden(singles, decay.GetQBetaN().GetValue(), res);
        
        auto ndenRes = *nden.GetDensity();
        auto ndenLow = *nden.GetDensityLow();
        auto ndenHigh = *nden.GetDensityHigh();
        
        BGTCalculator ndenBgt(ndenRes, decay, betaEff, omega);
        BGTCalculator ndenBgtLow(ndenLow, decay, 
                                 betaEff, omega, "low");
        BGTCalculator ndenBgtHigh(ndenHigh, decay, 
                                  betaEff, omega, "high");
        
        auto bgtMap = *ndenBgt.GetBgtMap();
        auto bgtSden = *ndenBgt.GetSDensity();

        auto bgtMapLow = *ndenBgtLow.GetBgtMap();
        auto bgtMapLowSden = *ndenBgtLow.GetSDensity();
        
        auto bgtMapHigh = *ndenBgtHigh.GetBgtMap();
        auto bgtMapHighSden = *ndenBgtHigh.GetSDensity();
        
        ofstream outNDenBgt(files[6]);
        outNDenBgt << "#Ex(MeV) BR BR(LOW) BR(HIGH) B(GT) B(GT)(LOW)" 
                   << " B(GT)(HIGH)" << endl;
        for(auto it = bgtMap.begin(); it != bgtMap.end(); it++) {
            auto itS = bgtSden.find(it->first);
            
            auto itLow = bgtMapLow.find(it->first);
            auto itLowS = bgtMapLowSden.find(it->first);

            auto itHigh = bgtMapHigh.find(it->first);
            auto itHighS = bgtMapHighSden.find(it->first);

            outNDenBgt.setf(ios::fixed);
            outNDenBgt << setprecision (8) << setw (10) << it->first << " " 
                       << itS->second << " " <<  itLowS->second << " " 
                       << itHighS->second << " " << it->second << " " 
                       << itLow->second << " " << itHigh->second << endl;
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
                nvec.back().SetSigma(Variable(s,0.0,"ns"));
                nvec.back().SetAlpha(Variable(a,0.0,""));
                nvec.back().SetN(Variable(n,0.0,""));
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
    out << setw(7) << "#Mu(ns) MuErr(ns) E(MeV) EErr(MeV) IntYld IntYldErr "
        << "BR BRerr B(GT) B(GT)err log(ft) log(ft)err" << endl;
    for(vector<Neutron>::iterator it = nvec.begin(); 
        it != nvec.end(); it++) {
        //---------- CALCULATE THE TOTAL NUMBER OF NEUTRONS --------
        intN += it->GetRawIntegratedYield().GetValue();
        totN += it->GetIntegratedYield().GetValue() / betaEff.GetValue() / 
            omega.GetValue();
        rawN += it->GetRawYield().GetValue();
        
        out << setprecision(5) << setw(7) << it->GetMu().GetValue() << " " 
            << it->GetMu().GetError() << " "
            << it->GetEnergy().GetValue() << " " << it->GetEnergy().GetError() 
            << it->GetIntegratedYield().GetValue() << " " 
            << it->GetIntegratedYield().GetError() << " " 
            << it->GetBranchingRatio().GetValue() << " " 
            << it->GetBranchingRatio().GetError() << " " 
            << it->GetBgt().GetValue() << " " << it->GetBgt().GetError() 
            << " " << it->GetLogft().GetValue() << " "
            << it->GetLogft().GetError() << endl;
    }
    double pn = totN / dky.GetNumberDecays().GetValue();
    ErrorCalculator err;
    double pnErr = err.CalcPnErr(pn,nvec,dky);
    out << "#Pn = " << totN << " / " << dky.GetNumberDecays().GetValue() 
        << " = " << pn << " +- " << pnErr << "  RawN = " 
        << rawN << " " << "  RawIntN = " << intN << endl;
    out.close();
}
