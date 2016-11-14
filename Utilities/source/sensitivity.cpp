/** \file main.cpp
 *  \brief A code to determine the sensitivity limit of the measurement
 *  \author S. V. Paulauskas
 *  \date 15 November 2013
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "BGTCalculator.hpp"
#include "ConfigurationReader.hpp"
#include "Decay.hpp"
#include "FileHandler.hpp"
#include "Integrator.hpp"
#include "LimitFinder.hpp"
#include "Neutron.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    ConfigurationReader cfg("Config.xml");
    FileHandler fls = cfg.ReadFiles();
    LimitFinder lim;
    Decay dky = cfg.ReadDecay();
    Experiment exp = cfg.ReadExperiment();
    
    ofstream out(fls.GetOutputName("sensitivity").c_str());
    out << setw(7) << "#Ex(MeV) BR BRerr B(GT) B(GT)err" << endl;

    double qValue = dky.GetQValue().GetValue();
    double sn = dky.GetNeutronSepEnergy().GetValue();
    for(double i = 0.1; i < qValue - sn; i += 0.1) {
        Neutron n = lim.PerformFit(i, 10.);
        Integrator integrate(n,make_pair(0.,200.));
        BGTCalculator bgt(n,dky,exp);

        out << n.GetExcitationEnergy().GetValue() << " " 
            << n.GetBranchingRatio().GetValue() << " " 
            << n.GetBranchingRatio().GetError() << " " 
            << n.GetBgt().GetValue() << " " 
            << n.GetBgt().GetError() << endl;
    }
    out.close();
}
