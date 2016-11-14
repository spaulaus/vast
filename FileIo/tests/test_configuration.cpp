#include <iostream>
#include <string>

#include "ConfigurationReader.hpp"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2) {
        cerr << "test_configuration : You need to provide the name of the "
                "configuration file. " << endl << "Usage: "
                     "test_configuration /path/to/configuration/file" << endl;
        return 1;
    }

    //We are first going to instance all of the different classes we need...
    //To make this a better test we should try to remove some of these
    // dependencies since we now have to setup a rather large test space.
    Decay dky;
    Experiment exp;
    FileHandler files;
    FlagHandler flags;
    FitHandler fitInfo;
    ConfigurationReader cfg(argv[1]);

    cout << "Testing ConfigurationReader::ReadDecay" << endl;
    try {
        dky = cfg.ReadDecay();
    } catch (std::exception &ex) {
        cout << ex.what() << endl;
    }

//    cout << "Q Value = " << dky.GetQValue().GetValue() << " +- "
//         << dky.GetQValue().GetError() << " "
//         << dky.GetQValue().GetUnits() << " " << endl;
//    cout << "Number of Decays = " << dky.GetNumberDecays().GetValue()
//         << " +- " << dky.GetNumberDecays().GetError() << " "
//         << dky.GetNumberDecays().GetUnits() << endl;
//
//    cout << endl << "Outputting info for the Experiment : " << endl;
//    exp = cfg.ReadExperiment();
//    cout << "numBars = " << exp.GetNumBars().GetValue() << endl;
//    cout << "betaEff = " << exp.GetBetaEff().GetValue() << " +- "
//         << exp.GetBetaEff().GetError() << " "
//         << exp.GetBetaEff().GetUnits() << endl;
//
//    cout << endl << "Outputting info from the FileHandler : " << endl;
//    files = cfg.ReadFiles();
//    cout << "gsTof = " << files.GetInputName("gsTof") << " " << endl
//         << "neutrons output = " << files.GetOutputName("neutrons") << endl;
//
//    cout << endl << "Outputting info from the FlagHandler : " << endl;
//    flags = cfg.ReadFlags();
//    cout << "doFit = " << flags.GetFlag("doFit") << endl
//         << "outputDensity = " << flags.GetFlag("density") << endl;
//
//    cout << endl << "Outputting info from the FitHandler: " << endl;
//    fitInfo = cfg.ReadFit();
//    vector<double> temp = fitInfo.GetSnglPeaks();
//    for(vector<double>::const_iterator it = temp.begin(); it != temp.end();
//        it++)
//        cout << *it << endl;
}
