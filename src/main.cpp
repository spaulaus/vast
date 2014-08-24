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

#include "Configuration.hpp"
#include "BGTCalculator.hpp"
#include "Decay.hpp"
#include "Integrator.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"
#include "OutputHandler.hpp"
#include "TofFitter.hpp"

using namespace std;

///A function to read the data from an input file
void ReadData(vector<Neutron> &nvec, const string &file);

///The main program function
int main(int argc, char* argv[]) {
    Configuration cfg("Config.xml");
    FileHandler fls = cfg.ReadFiles();
    Experiment exp = cfg.ReadExperiment();
    OutputHandler output;
    Variable betaEff = exp.GetBetaEff();
    FlagHandler flags = cfg.ReadFlags();
    bool basic = flags.GetFlag("basic");

    //---------- SET FIT INFORMATION AND PERFORM FIT HERE ----------
    FitHandler fit = cfg.ReadFit();
    if(flags.GetFlag("doFit"))
        TofFitter fitter(fit, fls);
    
    //---------- READ IN THE DECAY INFORMATION HERE ----------
    Decay decay = cfg.ReadDecay();

    //---------- SET THE NEUTRON INFORMATION AND OUTPUT ----------
    vector<Neutron> singles;
    if(basic) {
        ReadData(singles, fls.GetOutputName("gsFit"));
        for(vector<Neutron>::iterator it = singles.begin(); it!= singles.end();
            it++) {
            //---------- INTEGRATE THE NEUTRON PEAKS HERE ----------
            Integrator integrator(*it, fit.GetRange());
            //---------- Calculate the B(GT) for the Line ---------
            BGTCalculator bgt(*it, decay, exp);
        }
        output.OutputBasics(singles, decay, exp, fls.GetOutputName("neutrons"));

        //---------- Output B(GT) for the simulations -------
        if(flags.GetFlag("theory"))
            output.OutputTheory(singles, fls.GetOutputName("cgm"));
        
        //---------- Calculate the Neutron Density and B(GT) ---------
        if(flags.GetFlag("density"))
            output.OutputDensity(singles, decay, exp, fls.GetOutputName("density"));
        
    }//if(basic)
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
