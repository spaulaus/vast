/** \file eff.cpp
 *  \brief A simple file to output the efficiency for a given energy
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#include <iostream>
#include <string>
#include <utility>

#include <cmath>
#include <cstdlib>

#include <unistd.h>

#include "EffCalculator.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    int opt = -1;
    double temp, temp1 = 0.;
    string name;
    while((opt = getopt (argc, argv, "e:g:v:")) != -1) {
        switch(opt) {
        case 'e': {
            temp1 = atof(optarg);
            break;
        } case 'g': {
            name = "ge";
            temp = atof(optarg);
            break;
        } case 'v': {
            name = "vandle";
            temp = atof(optarg);
            break;
        } case '?': {
              return 1;
        } default: {
            abort();
          }
        }
    }

    Variable energy(temp, temp1, "keV");
    EffCalculator eff(name);
    Variable effRes;
    if(name == "ge")
        effRes = eff.GetEff(energy);
    else if(name == "vandle")
        effRes = eff.GetSimRollingEff(energy);
    else
        cout << "You didn't specify a known type" << endl;

    if(std::isnan(effRes.GetValue()))
        cout << "The Efficiency calculation reported an efficiency of " 
             << "NaN. " << endl << "This is usually a problem with the "
             << "energy." << endl << "Make sure you entered it in MeV !!" 
             << endl;
    else
        cout << "Eff for " << name << " = " << effRes.GetValue() << " +- " 
             << effRes.GetError() << endl;
}
