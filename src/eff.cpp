/** \file eff.cpp
 *  \brief A simple file to output the efficiency for a given energy
 *  \author S. V. Paulauskas
 *  \date 05 September 2013
 */
#include <iostream>
#include <string>

#include <cstdlib>

#include <unistd.h>

#include "EffCalculator.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    int opt = -1;
    double eff = 0.0;
    string name;
    while((opt = getopt (argc, argv, "g:v:")) != -1)
        switch(opt) {
        case 'g': {
            EffCalculator ge("ge");
            eff = ge.GetEff(atof(optarg));
            name = "Ge";
            break;
        } case 'v': {
            EffCalculator vandle("vandle");
            eff = vandle.GetSimRollingEff(atof(optarg));
            name = "VANDLE";
            break;
        } case '?':
            return 1;
        default:
            abort();
        }
    cout << "Eff for " << name << " = " << eff << endl;
}
