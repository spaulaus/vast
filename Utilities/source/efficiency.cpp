/*! \file eff.cpp
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

//! A function used to output the usage of the program in the event of an error.
void usage(void) {
    cout << "You got it all wrong man. We need the following info:" << endl
         << "./eff <flag>" << endl
         << "Flags: " << endl
         << "   -e <val> = (required) Energy of the neutron" << endl
         << "   -s <val> = (optional) Uncertainty in the energy of the neutron" << endl
         << "   -b = Beta Efficiency for the provided energy" << endl
         << "   -g = Ge Efficiency" << endl
         << "   -m = Vandle Efficiency using MMF Banana 1" << endl
         << "   -c = Vandle Efficiency using SVP Banana 4" << endl
         << "   -v = Basic Vandle Efficiency" << endl
         << "   -t = VANDLE Efficiency using Sergey's Simulation for MMF Banana 1" << endl
         << "   -d <val> = The distance to be used for ToF Calculation. " <<
            "Used in conjunction with the -m flag" << endl
         << "Now let's try this again." << endl;
}

//!The main function for the efficiency calculation
int main(int argc, char* argv[]) {
    if(argc == 1) {
        usage();
        return 0;
    }

    EffCalculator eff;
    int opt = -1;
    EffCalculator::EffTypes curve;
    double distance = 0.0, energy = 0.0, sigma = 0.0;

    while((opt = getopt (argc, argv, "e:s:bgmcvtd:")) != -1) {
        switch(opt) {
        case 'b': {
            curve = EffCalculator::EffTypes::beta;
            break;
        } case 'e': {
            energy = atof(optarg);
            break;
        } case 's': {
            sigma = atof(optarg);
            break;
        } case 'g': {
            curve = EffCalculator::EffTypes::ge;
            break;
        } case 'v': {
            curve = EffCalculator::EffTypes::vandle;
            break;
        }  case 'c': {
            curve = EffCalculator::EffTypes::svpBan4;
            break;
        } case 'm': {
            curve = EffCalculator::EffTypes::mmfCalc;
            break;
        } case 't' : {
            curve = EffCalculator::EffTypes::mmfTheory;
            break;
        } case 'd' : {
            distance = atof(optarg);
            break;
        } case '?': {
            usage();
        } default: {
            usage();
          }
        }
    }

    if(distance != 0)
        eff.SetDistance(distance);
    Variable en(energy, sigma, "MeV");
    Variable result = eff.GetEff(en, curve);

    if(std::isnan(result.GetValue()))
        cout << "The Efficiency calculation reported an efficiency of "
             << "NaN. " << endl << "This is usually a problem with the "
             << "energy." << endl << "Make sure you entered it in MeV !!"
             << endl;
    else
        cout << "The efficiency for " << en.Output() << " is "
             << result.Output() << endl;

    return 0;
}
