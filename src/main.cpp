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
#include "InputHandler.hpp"
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

    InputHandler input;
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

    input.ReadFitOutput(singles, fls.GetOutputName("gsFit"));

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
