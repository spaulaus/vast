/** \file FileHandler.cpp
 * \brief A class to handle the various filenames
 * \author S. V. Paulauskas
 * \date 01 December 2013
 */
#include <iostream>

#include "FileHandler.hpp"

using namespace std;

string FileHandler::GetInputName(const string &name) const {
    auto it = input_.find(name);
    if(it == input_.end())
        EndError(name);
    return(it->second);
}

string FileHandler::GetOutputName(const string &name) const {
    auto it = output_.find(name);
    if(it == output_.end())
        EndError(name);
    return(it->second);
}

void FileHandler::EndError(const string &name) const {
    cerr << "In File Handler: We could not find the requested file name: " 
         << name << endl << "This is a major issue with me. "
         << "I am going to give up." << endl;
    exit(2);
}

void FileHandler::SetInputNames(const string &name, const string &val) {
    input_.insert(make_pair(name,val));
}

void FileHandler::SetOutputNames(const string &name, const string &val) {
    output_.insert(make_pair(name,val));
}


