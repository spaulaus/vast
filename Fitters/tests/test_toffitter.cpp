///@file test_toffitter.cpp
///@author S. V. Paulauskas
///@date Nobemver 18, 2016
#include <iostream>

#include "ConfigurationReader.hpp"
#include "TofFitter.hpp"
#include "XmlInterface.hpp"

using namespace std;

///This is used to test that the ToFFitter class is working as expected
int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "test_toffitter : You need to provide the name of the "
                "configuration file. " << endl << endl << "Usage: "
                     "./test_toffitter /path/to/configuration/file" << endl;
        return 1;
    } else {
        XmlInterface::get(argv[1]);
    }

    pugi::xml_node configurationNode = XmlInterface::get()->GetDocument()->child("Configuration");

    ConfigurationReader cfg;
    FitHandler fitHandler;
    cfg.ParseFitNode(configurationNode.child("Fitting"), fitHandler);

    FileHandler fileHandler;
    cfg.ParseFileNode(configurationNode.child("Files"), fileHandler);

    CrystalBallParameters crystalBallParameters;
    cfg.ParseCrystalBallNode(configurationNode.child("CrystalBall"), crystalBallParameters);

    cout << "Performing the Fit" << endl;
    try {
        TofFitter fitter(fitHandler, fileHandler, crystalBallParameters);
    } catch (TofFitterException &ex) {
        cout << "TofFitterException caught : " << ex.what() << endl;
    }
}
