/** \file Configuration.cpp
 * \brief A class to handle the confiruation xml file
 * \author S. V. Paulauskas
 * \date 30 November 2013
 */
#include <iostream>
#include <map>

#include <pugixml.hpp>
#include <Variable.hpp>

#include "Configuration.hpp"

using namespace std; 

Configuration::Configuration(const string &file) {
    pugi::xml_parse_result result = doc_.load_file(file.c_str());
    
    if(result) {
        cout << "Fuck yeah, we opened that bitch" << endl;
    } else {
        cout << "We had errors with the config file. " << endl
             << "Error Description: " << result.description() << endl;
    }
}

Decay Configuration::ReadDecay() {
    Decay decay;

    //Get the File information
    pugi::xml_node cfg = doc_.child("Configuration");
    for(pugi::xml_node files : cfg.children("Files")) {
        cout << "Files:" << endl;
        for(pugi::xml_node ionode: files.children()) {
            cout << "   " << ionode.name() << ":" << endl;

            for(pugi::xml_node attr: ionode.children())
                cout << " " << attr.name() << " = " << attr.child_value() << endl;
        }
        cout << endl;

        for(pugi::xml_node dky : cfg.children("Decay")) {
            cout << "Decay:" << endl;
            //The First level of nodes
            for(pugi::xml_node node1: dky.children()) {
                string name = node1.name();
                Variable tmp;
                cout << "   " << node1.name() << ":";
                //Attributes of the first level nodes
                for(pugi::xml_attribute attr : node1.attributes()) {
                    string temp = attr.name();
                    if(temp == "value")
                        tmp.SetValue(atof(attr.value()));
                    else if(temp == "error")
                        tmp.SetError(atof(attr.value()));
                    else if(temp == "unit")
                        tmp.SetUnits(attr.value());
                    cout << attr.name() << " = " << attr.value() << "   ";
                }
                if(tmp.GetValue() != 0.0)
                    decay.insert(make_pair(name,tmp));
                cout << endl;
                //Loop over the second level nodes
                for(pugi::xml_node node2: node1.children()) {
                    cout << "      " << node2.name() << "  ";
                    //Loop over the attributes of the sec lvl nodes
                    for(pugi::xml_attribute attr : node2.attributes())
                        cout << attr.name() << " = " << attr.value() << " " ;
                    cout << endl;
                }
            }
        }
    }
    return(Decay());
} 
