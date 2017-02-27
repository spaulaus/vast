/** \file FileHandler.cpp
 * \brief A class to handle the various filenames
 * \author S. V. Paulauskas
 * \date 01 December 2013
 */
#include <iostream>

#include "FileHandler.hpp"

using namespace std;

///This method gets the name of the input file from the configuration file
string FileHandler::GetInputName(const string &name) const {
    const map<string,string>::const_iterator it = input_.find(name);
    if(it == input_.end())
        EndError(name);
    return(it->second);
}

///This method gets the output name for the file from the configuration file
string FileHandler::GetOutputName(const string &name) const {
    const map<string,string>::const_iterator it = output_.find(name);
    if(it == output_.end())
        EndError(name);
    return(it->second);
}

///This method produces the errr message for missing file names
void FileHandler::EndError(const string &name) const {
    cerr << "In File Handler: We could not find the requested file name: " 
         << name << endl << "This is a major issue with me. "
         << "I am going to give up." << endl;
    exit(2);
}

///This method sets the input file name
void FileHandler::SetInputNames(const string &name, const string &val) {
    input_.insert(make_pair(name,val));
}

///This method sets the output file name
void FileHandler::SetOutputNames(const string &name, const string &val) {
    output_.insert(make_pair(name,val));
}


