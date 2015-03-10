/** \file main.cpp
 *  \brief The main workhorse for the code.
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
#include <ezETAProgressBar.hpp>

#include "BGTCalculator.hpp"
#include "Configuration.hpp"
#include "Decay.hpp"
#include "Integrator.hpp"
#include "Neutron.hpp"
#include "OutputHandler.hpp"
#include "TofFitter.hpp"

using namespace std;

///A function to read the data from an input file
void ReadData(vector<Neutron> &nvec, const string &file);

///The main program function
int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "You must provide the name of the configuration file!!"
             << endl;
        cerr << "Usage: ./vast /path/to/configuration/file" << endl;
        exit(0);
    }

    Configuration cfg(argv[1]);
    FileHandler fls = cfg.ReadFiles();
    Experiment exp = cfg.ReadExperiment();
    OutputHandler output;
    Variable betaEff = exp.GetBetaEff();
    FlagHandler flags = cfg.ReadFlags();
    bool basic = flags.GetFlag("basic");

    FitHandler fit = cfg.ReadFit();
    if(flags.GetFlag("doFit")) {
        cout << "Performing the Fit and reading the Fit configuration" << endl;
        TofFitter fitter(fit, fls);
    }

    cout << "Reading the Decay information" << endl;
    Decay decay = cfg.ReadDecay();

    vector<Neutron> singles;
    cout << "We are now reading the fitted data." << endl;
    ReadData(singles, fls.GetOutputName("gsFit"));

    cout << "Integrating neutron peaks and calculating B(GT)" << endl;
    ez::ezETAProgressBar eta(singles.size());
    eta.start();
    for(vector<Neutron>::iterator it = singles.begin(); it!= singles.end();
        it++, ++eta) {
        Integrator integrator(*it, fit.GetRange());
        BGTCalculator bgt(*it, decay, exp);
    }

    if(basic) {
        cout << "Outputting the basic neutron information" << endl;
        output.OutputBasics(singles, decay, exp, fls.GetOutputName("neutrons"));
    }

    if(flags.GetFlag("theory")) {
        cout << "Outputting the information for the CGM calculations"
             << endl;
        output.OutputTheory(singles, fls.GetOutputName("cgm"));
    }

    if(flags.GetFlag("density")) {
        cout << "Calculating the neutron density " << endl;
        NeutronDensity nden(singles, decay.GetQBetaN().GetValue());
        output.OutputDensity(nden, decay, exp, fls.GetOutputName("density"));
    }
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
        cerr << "Oh, Jesus! We could no open the file: "
             << file << endl << "Please check the name and try again."
             << endl << endl;
        exit(1);
    }
    data.close();
}
