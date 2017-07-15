///@file TofFitter.cpp
///@brief A program that tests the simulation convoluter
///@author S. V. Paulauskas
///@date October 6, 2013
///@copyright Copyright (c) 2013-2017 S. V. Paulauskas.
///@copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include <iostream>

#include "ResponseFunctionAnalyzer.hpp"
#include "VastExceptions.hpp"

using namespace std;

///This is used to test that the SimConvoluter is working as expected
int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "You must provide the name of the configuration file!!"
             << endl;
        cerr << "Usage: ./simtest /path/to/configuration/file" << endl;
        return 0;
    }

    try {
        XmlInterface::get(argv[1]);
        ResponseFunctionAnalyzer rfa(XmlInterface::get()->GetDocument()->child("Configuration").child("ResponseFunctionAnalysis"));
    } catch (VastIoException &ex) {
        cout << ex.what() << endl;
    } catch (ResponseFunctionAnalyzerException &ex) {
        cout << ex.what() << endl;
    } catch (invalid_argument &ex) {
        cout << ex.what() << endl;
    }
}
