#include <iostream>
#include <string>

#include "Configuration.hpp"

using namespace std;

int main() {
    string cfgFile = "Config.xml";
    cout << "Reading in the config file : " << cfgFile << endl;
    Configuration cfg(cfgFile);

    cout << endl << "Outputting info from the Decay :" << endl;
    Decay dky = cfg.ReadDecay();
    cout << "Q Value = " << dky.GetQValue().GetValue() << " +- " 
         << dky.GetQValue().GetError() << " " 
         << dky.GetQValue().GetUnits() << " " << endl;
    cout << "Number of Decays = " << dky.GetNumberDecays().GetValue() 
         << " +- " << dky.GetNumberDecays().GetError() << " " 
         << dky.GetNumberDecays().GetUnits() << endl;

    cout << endl << "Outputting info for the Experiment : " << endl;
    Experiment exp = cfg.ReadExperiment();
    cout << "numBars = " << exp.GetNumBars().GetValue() << endl;
    cout << "betaEff = " << exp.GetBetaEff().GetValue() << " +- " 
         << exp.GetBetaEff().GetError() << " " 
         << exp.GetBetaEff().GetUnits() << endl;

    cout << endl << "Outputting info from the FileHandler : " << endl;
    FileHandler files = cfg.ReadFiles();
    cout << "gsTof = " << files.GetInputName("gsTof") << " " << endl
         << "neutrons output = " << files.GetOutputName("neutrons") << endl;

    cout << endl << "Outputting info from the FlagHandler : " << endl;
    FlagHandler flags = cfg.ReadFlags();
    cout << "doFit = " << flags.GetFlag("doFit") << endl
         << "outputDensity = " << flags.GetFlag("outputDensity") << endl;

    cout << endl << "Outputting info from the FitHandler: " << endl;
    FitHandler fitInfo = cfg.ReadFit();
    vector<double> temp = fitInfo.GetSnglPeaks();
    for(const auto it : temp)
        cout << it << endl;
}
