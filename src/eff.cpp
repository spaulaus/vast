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

void usage(void) {
    cout << "You got it all wrong man. We need the following info:" << endl
         << "./eff <flag> <energy in MeV> <err Energy> " << endl
         << "Flags: " << endl
         << "   -v = Basic Vandle Efficiency" << endl
         << "   -g = Ge Efficiency" << endl
         << "   -s = Vandle Efficiency using SVP Banana 4" << endl
         << "   -m = Vandle Efficiency using MMF Banana 1" << endl
         //<< "   -b = Beta Efficiency for the provided Qeff" << endl
         << "Now let's try this again." << endl;
    exit(2);
}


//!The main function for the efficiency calculation
int main(int argc, char* argv[]) {
    if(argc < 2 || argc > 4)
        usage();

    int opt = -1;
    Variable en;
    EffCalculator::EffTypes curve;

    while((opt = getopt (argc, argv, "b:g:m:s:v:")) != -1) {
        switch(opt) {
        case 'b': {
            curve = EffCalculator::EffTypes::beta;
            en = Variable(atof(optarg), atof(argv[3]), "MeV");
            break;
        } case 'g': {
            en = Variable(atof(optarg), atof(argv[3]), "MeV");
            curve = EffCalculator::EffTypes::ge;
            break;
        } case 'v': {
            en = Variable(atof(optarg), atof(argv[3]), "MeV");
            curve = EffCalculator::EffTypes::vandle;
            break;
        }  case 's': {
            en = Variable(atof(optarg), atof(argv[3]), "MeV");
            curve = EffCalculator::EffTypes::vandle;
            break;
        } case 'm': {
            en = Variable(atof(optarg), atof(argv[3]), "MeV");
            curve = EffCalculator::EffTypes::vandle;
            break;
        } case '?': {
            usage();
        } default: {
            usage();
          }
        }
    }

    EffCalculator eff;
    Variable result = eff.GetEff(en, curve);

    if(std::isnan(result.GetValue()))
        cout << "The Efficiency calculation reported an efficiency of "
             << "NaN. " << endl << "This is usually a problem with the "
             << "energy." << endl << "Make sure you entered it in MeV !!"
             << endl;
    else
        cout << "The efficiency for " << en.Output() << " is "
             << result.Output() << endl;
}
