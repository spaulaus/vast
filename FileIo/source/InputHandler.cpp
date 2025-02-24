/*! \file InputHandler.hpp
 * \brief A class to handle various text file inputs to the program.
 * \author S. V. Paulauskas
 * \date March 10, 2015
 *
 * Copyright S. V. Paulauskas 2013-2015
 * stanpaulauskasATgmailDOTcom
 * Distributed under GNU General Public Licence v3
 */
#include <fstream>

#include "InputHandler.hpp"
#include "StringManipulators.hpp"
#include "VastExceptions.hpp"

using namespace std;
using namespace StringManipulators;

///This function reads the data from the fit output
void InputHandler::ReadFitOutput(vector<Neutron> &nvec, const string &file) {
    string line;
    ifstream data(file.c_str());
    if(data.is_open()) {
        while(data.good()) {
            if(isdigit(data.peek())) {
                getline(data,line);
                const vector<string> tokens = TokenizeString(line, " ");
                nvec.push_back(Neutron(atof(tokens.at(1).c_str()), atof(tokens.at(2).c_str()),
                                       atof(tokens.at(3).c_str()), atof(tokens.at(4).c_str())));
                nvec.back().SetSigma(Variable(atof(tokens.at(5).c_str()), 0.0, "ns"));
                nvec.back().SetAlpha(Variable(atof(tokens.at(6).c_str()), 0.0,""));
                nvec.back().SetN(Variable(atof(tokens.at(7).c_str()), 0.0,""));
            } else {
                data.ignore(1000,'\n');
            }
        }
    } else
        throw InputHandlerException("InputHandler::ReadFitOutput - could not open " + file);

    data.close();
}
