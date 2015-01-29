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
        cerr << "You must provide me the name of the configuration file!!"
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

    cout << "Performing the Fit and reading the Fit configuration" << endl;
    FitHandler fit = cfg.ReadFit();
    if(flags.GetFlag("doFit"))
        TofFitter fitter(fit, fls);

    cout << "Reading the Decay information" << endl;
    Decay decay = cfg.ReadDecay();

    vector<Neutron> singles;
    if(basic) {
        cout << "We are now reading the fitted data." << endl;
        ReadData(singles, fls.GetOutputName("gsFit"));
        for(vector<Neutron>::iterator it = singles.begin(); it!= singles.end();
            it++) {
            cout << "Integrating the neutron peak" << endl;
            Integrator integrator(*it, fit.GetRange());
            cout << "Calculating the B(GT)" << endl;
            BGTCalculator bgt(*it, decay, exp);
        }
        output.OutputBasics(singles, decay, exp, fls.GetOutputName("neutrons"));

        if(flags.GetFlag("theory")) {
            cout << "Outputting the information for the CGM calculations"
                 << endl;
            output.OutputTheory(singles, fls.GetOutputName("cgm"));
        }

        if(flags.GetFlag("density")) {
            cout << "Calculate the neutron density " << endl;
            cout << "We are starting to calculate the neutron density + B(GT)"
                 << endl;
            output.OutputDensity(singles, decay, exp,
                                 fls.GetOutputName("density"));
        }
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
