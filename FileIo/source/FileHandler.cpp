/** \file FileHandler.cpp
 * \brief A class to handle the various filenames
 * \author S. V. Paulauskas
 * \date 01 December 2013
 */
#include <iostream>

#include "FileHandler.hpp"
#include "VastExceptions.hpp"

using namespace std;

///This method gets the name of the input file from the configuration file
string FileHandler::GetInputName(const string &name) const {
    const map<string,string>::const_iterator it = input_.find(name);
    if(it == input_.end())
        throw FileHandlerException(EndError(name));
    return(it->second);
}

///This method gets the output name for the file from the configuration file
string FileHandler::GetOutputName(const string &name) const {
    const map<string,string>::const_iterator it = output_.find(name);
    if(it == output_.end())
        throw FileHandlerException(EndError(name));
    return(it->second);
}

///This method produces the error message for missing file names
string FileHandler::EndError(const string &name) const {
    return "In File Handler: We could not find the requested file name: " + name
           + "\nIf you need this file define it in the configuration file.";
}

///This method sets the input file name
void FileHandler::SetInputNames(const string &name, const string &val) {
    input_.insert(make_pair(name,val));
}

///This method sets the output file name
void FileHandler::SetOutputNames(const string &name, const string &val) {
    output_.insert(make_pair(name,val));
}


