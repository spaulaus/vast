///@file main.cpp
///@brief The main workhorse for the code.
///@author S. V. Paulauskas
///@date September 4, 2013
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "BGTCalculator.hpp"
#include "ConfigurationReader.hpp"
#include "ezETAProgressBar.hpp"
#include "InputHandler.hpp"
#include "Integrator.hpp"
#include "OutputHandler.hpp"
#include "TofFitter.hpp"
#include "Variable.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "VAST Main : You need to provide the name of the "
                "configuration file. " << endl << endl << "Usage: "
                "./vast /path/to/configuration/file" << endl;
        return 1;
    }

    InputHandler input;
    FileHandler fls;
    Experiment exp;
    OutputHandler output;
    Variable betaEff;
    FlagHandler flags;
    FitHandler fit;
    Decay decay;
    bool basic;

    cout << "vast.cpp : Reading in the configuration file " << argv[1] << endl;
    ConfigurationReader cfg(argv[1]);

    try {
        fls = cfg.ReadFiles();
    } catch(...) {
        cout << "vast.cpp : Exception caught while reading file list. " << endl;
    }

    exp = cfg.ReadExperiment();

    betaEff = exp.GetBetaEff();
    flags = cfg.ReadFlags();
    basic = flags.GetFlag("basic");

    fit = cfg.ReadFit();
    if(flags.GetFlag("doFit")) {
        cout << "Performing the Fit and reading the Fit configuration" << endl;
        TofFitter fitter(fit, fls);
    }

    cout << "Reading the Decay information" << endl;
    decay = cfg.ReadDecay();

    vector<Neutron> singles;
    cout << "We are now reading the fitted data." << endl;
    input.ReadFitOutput(singles, fls.GetOutputName("gsFit"));

    cout << "Integrating neutron peaks and calculating B(GT)" << endl;
    ez::ezETAProgressBar eta((unsigned int) singles.size());
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
