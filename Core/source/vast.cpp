///@file main.cpp
///@brief The main workhorse for the code. This program will initialize all
/// of the necessary classes and start the main work that needs to be
/// accomplished.
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
#include "XmlInterface.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "VAST Main : You need to provide the name of the "
                "configuration file. " << endl << endl << "Usage: "
                "./vast /path/to/configuration/file" << endl;
        return 1;
    } else {
        XmlInterface::get(argv[1]);
    }

    pugi::xml_node configurationNode = XmlInterface::get()->GetDocument()->child("Configuration");
    ConfigurationReader cfg;

    InputHandler input;
    FileHandler fls;
    Experiment exp;
    OutputHandler output;
    FlagHandler flags;
    FitHandler fit;
    Decay decay;
    CrystalBallParameters cbpars;

    try {
        cfg.ParseFileNode(configurationNode.child("Files"), fls);
        cfg.ParseDecayNode(configurationNode.child("Decay"), decay);
        cfg.ParseExperimentNode(configurationNode.child("Experiment"), exp);
        cfg.ParseCrystalBallNode(configurationNode.child("CrystalBall"), cbpars);
        cfg.ParseDecayNode(configurationNode.child("Decay"), decay);
        cfg.ParseFlagsNode(configurationNode.child("Flags"), flags);
    } catch(ConfigurationReaderException &ex) {
        cout << "vast.cpp : " << ex.what() << endl;
    }

    Variable betaEff = exp.GetBetaEff();
    bool basic = flags.GetFlag("basic");

    if(flags.GetFlag("doFit")) {
        cout << "Performing the Fit and reading the Fit configuration" << endl;
        TofFitter fitter(fit, fls, cbpars);
    }

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
