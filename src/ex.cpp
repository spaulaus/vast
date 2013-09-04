#include <fstream>
#include <iostream>
#include <vector>

#include "Integrator.hpp"
#include "Neutron.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    vector<Neutron> neutrons;

    ifstream data("data/077cu-ban4-lower/077cu-ban4-lower-tof.out");
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

    // for(vector<Neutron>::iterator it = neutrons.begin(); 
    //     it != neutrons.end(); it++) {
    //     cout << (*it).GetMu() << " " << (*it).GetMuErr() << " "
    //          << (*it).GetEnergy() << " " << (*it).GetEnergyErr() << " " 
    //          << (*it).GetYield() << " " << (*it).GetYieldErr() << " " 
    //          << (*it).GetEfficiency() << " " << (*it).GetAlpha() << " " 
    //          << (*it).GetN() << " " << (*it).GetSigma() << endl;
    // }

    Neutron num0 = neutrons.at(0);
    Integrator integrator(num0, 0, 200.);
    
    cout << "---------------IN THE EXAMPLE CODE HERE -------------" << endl;
    cout << num0.GetMu() << " " << num0.GetMuErr() << " "
         << num0.GetEnergy() << " " << num0.GetEnergyErr() << " " 
         << num0.GetYield() << " " << num0.GetYieldErr() << " " 
         << num0.GetEfficiency() << " " << num0.GetAlpha() << " " 
         << num0.GetN() << " " << num0.GetSigma() << " " 
         << num0.GetIntegratedYield() << " " << endl;
}
