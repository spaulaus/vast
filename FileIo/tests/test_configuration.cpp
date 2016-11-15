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
        cerr << ex.what() << endl;
        return 1;
    }

    cout << "Q Value = " << dky.GetQValue().Output() << endl;
    cout << "Number of Decays = " << dky.GetNumberDecays().Output() << endl;

    cout << endl << "Testing ConfigurationReader::ReadExperiment" << endl;
    try {
        exp = cfg.ReadExperiment();
    } catch (std::exception &ex) {
        cerr << ex.what() << endl;
        return 1;
    }

    cout << "numBars = " << exp.GetNumBars().Output() << endl;
    cout << "betaEff = " << exp.GetBetaEff().Output() << endl;

    cout << endl << "Testing ConfigurationReader::ReadFiles" << endl;
    try {
        files = cfg.ReadFiles();
    }catch(exception &ex) {
        cerr << ex.what() << endl;
        return 1 ;
    }
    cout << "gsTof = " << files.GetInputName("gsTof") << " " << endl
         << "neutrons output = " << files.GetOutputName("neutrons") << endl;

    cout << endl << "Testing ConfigurationReader::ReadFlags : " << endl;
    try {
        flags = cfg.ReadFlags();
    }catch (exception &ex){
        cerr << ex.what() << endl;
        return(1);
    }
    cout << "doFit = " << flags.GetFlag("doFit") << endl
         << "outputDensity = " << flags.GetFlag("density") << endl;

    cout << endl << "Testing ConfigurationReader::ReadFit :" << endl;
    try {
        fitInfo = cfg.ReadFit();
    } catch (exception &ex) {
        cerr << ex.what() << endl;
        return(1);
    }
    vector<double> temp = fitInfo.GetSnglPeaks();
    for(vector<double>::const_iterator it = temp.begin(); it != temp.end();
        it++)
        cout << *it << endl;
}
