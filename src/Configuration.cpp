/** \file Configuration.cpp
 * \brief A class to handle the confiruation xml file
 * \author S. V. Paulauskas
 * \date 30 November 2013
 */
#include <iostream>
#include <map>
#include <vector>

#include <pugixml.hpp>
#include <Variable.hpp>

#include "Configuration.hpp"

using namespace std; 

Configuration::Configuration(const string &file) {
    pugi::xml_parse_result result = doc_.load_file(file.c_str());
    
    if(result) {
        cout << "Fuck yeah, we opened that bitch" << endl;
        cfg_ = doc_.child("Configuration");
    } else {
        cout << "We had errors with the config file. " << endl
             << "Error Description: " << result.description() << endl;
    }
}

Experiment Configuration::ReadExperiment(void) {
    Experiment exp;
    string nodeName = "Experiment";
    pugi::xml_node expInfo = cfg_.child(nodeName.c_str());

    for(pugi::xml_node node : expInfo.children()) {
        string name = node.name();
        Variable temp = NodeToVar(node);
        if(name == "betaEff") 
            exp.SetBetaEff(temp);
        else if(name == "numBars")
            exp.SetNumBars(temp);
        else if(name == "omegaPerBar")
            exp.SetOmegaPerBar(temp);
        else if(name =="denRes")
            exp.SetDensityRes(temp);
        else
            SpitWarning(nodeName, name);
    }
    return(exp);
}

FileHandler Configuration::ReadFiles(void) {
    FileHandler fhandle;
    pugi::xml_node inode = cfg_.child("Files").child("Input");
    pugi::xml_node onode = cfg_.child("Files").child("Output");

    for(pugi::xml_node attr : inode.children())
        fhandle.SetInputNames(attr.name(), attr.child_value());
    for(pugi::xml_node attr : onode.children())
        fhandle.SetOutputNames(attr.name(), attr.child_value());
    return(fhandle);
}

FitHandler Configuration::ReadFit(void) {
    FitHandler fit;
    pugi::xml_node ft = cfg_.child("Fitting");
    vector<double> snglPeaks, g1Peaks, g2Peaks;
    for(pugi::xml_node pks : ft.child("peaks").child("sngl").children())
        snglPeaks.push_back(pks.attribute("value").as_double());
    fit.SetSnglPeaks(snglPeaks);

    for(pugi::xml_node pks : ft.child("peaks").child("g1").children())
        g1Peaks.push_back(pks.attribute("value").as_double());
    fit.SetGate1Peaks(g1Peaks);
    
    for(pugi::xml_node pks : ft.child("peaks").child("g2").children())
        g2Peaks.push_back(pks.attribute("value").as_double());
    fit.SetGate2Peaks(g2Peaks);

    fit.SetBinning(ft.child("binning").attribute("value").as_double());
    fit.SetPeakList(ft.child("pkList").attribute("value").as_string());
    fit.SetWiggle(ft.child("wiggle").attribute("value").as_double());

    double low = 
        ft.child("range").child("low").attribute("value").as_double();
    double high = 
        ft.child("range").child("high").attribute("value").as_double();
    fit.SetRange(make_pair(low,high));
    return(fit);
}

FlagHandler Configuration::ReadFlags(void) {
    FlagHandler flags;
    for(pugi::xml_node chld : cfg_.child("Flags").children())
        flags.SetFlag(chld.name(), chld.attribute("value").as_bool());
    return(flags);
}

Decay Configuration::ReadDecay(void) {
    Decay decay;
    string nodeName = "Decay";
    pugi::xml_node dky = cfg_.child(nodeName.c_str());
    
    for(pugi::xml_node node1 : dky.children()) {
        string name = node1.name();
        Variable temp = NodeToVar(node1);
        if(name == "z")
            decay.SetParentZ(temp);
        else if (name == "q")
            decay.SetQValue(temp);
        else if (name == "sn")
            decay.SetNeutronSepEnergy(temp);
        else if (name == "qbn")
            decay.SetQBetaN(temp);
        else if (name == "t12")
            decay.SetHalfLife(temp);
        else if (name == "gn") {
            Variable area = NodeToVar(node1.child("area"));
            Variable eff = NodeToVar(node1.child("eff"));
            Variable abr = NodeToVar(node1.child("abr"));
            decay.SetNormInfo(area,eff,abr);
        } else if (name == "g1") {
            //unused for now
        } else if (name == "g2") {
            //unused for now
        } else
            SpitWarning(nodeName,name);
    }
    return(decay);
} 

Variable Configuration::NodeToVar(const pugi::xml_node &node) {
    Variable var = Variable(node.attribute("value").as_double(),
                            node.attribute("error").as_double(),
                            node.attribute("unit").value());
    return(var);
}

void Configuration::SpitWarning(const string &node, 
                                const string &name) {
    cerr << endl << "WARNING!!!!  " 
         << "You put something in the " << node 
         << " node that confused the shit out of me." << endl 
         << "If you need access to the information in " 
         << name << "; add it yourself." << endl << endl;
}
