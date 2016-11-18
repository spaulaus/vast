///@file test_toffitter.cpp
///@author S. V. Paulauskas
///@date Nobemver 18, 2016
#include <iostream>

#include "ConfigurationReader.hpp"
#include "TofFitter.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "test_toffitter : You need to provide the name of the "
                "configuration file. " << endl << endl << "Usage: "
                     "./test_toffitter /path/to/configuration/file" << endl;
        return 1;
    }

    cout << "vast.cpp : Reading in the configuration file " << argv[1] << endl;
    ConfigurationReader cfg(argv[1]);

    cout << "Performing the Fit and reading the Fit configuration" << endl;
    try {
        TofFitter fitter(cfg.ReadFit(), cfg.ReadFiles(),
                         cfg.ReadCrystalBallParameters());
    } catch (exception &ex) {
        cout << ex.what() << endl;
    }
}
