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

    FileHandler fileHandler;
    cfg.ParseFileNode(configurationNode.child("Files"), fileHandler);

    Decay decay;
    cfg.ParseDecayNode(configurationNode.child("Decay"), decay);

    Experiment experiment;
    cfg.ParseExperimentNode(configurationNode.child("Experiment"), experiment);

    CrystalBallParameters crystalBallParameters;
    cfg.ParseCrystalBallNode(configurationNode.child("CrystalBall"), crystalBallParameters);
    
    ofstream out(fileHandler.GetOutputName("sensitivity").c_str());
    out << setw(7) << "#Ex(MeV) BR BRerr B(GT) B(GT)err" << endl;

    LimitFinder lim;
    double qValue = decay.GetQValue().GetValue();
    double sn = decay.GetNeutronSepEnergy().GetValue();

    for(double i = 0.1; i < qValue - sn; i += 0.1) {
        Neutron n = lim.PerformFit(i, 10., crystalBallParameters);
        Integrator integrate(n,make_pair(0.,200.));
        BGTCalculator bgt(n, decay, experiment);

        out << n.GetExcitationEnergy().GetValue() << " " 
            << n.GetBranchingRatio().GetValue() << " " 
            << n.GetBranchingRatio().GetError() << " " 
            << n.GetBgt().GetValue() << " " 
            << n.GetBgt().GetError() << endl;
    }
    out.close();
}
