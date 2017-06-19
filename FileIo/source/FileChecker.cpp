///@file FileChecker.cpp
///@brief Checks that we can write to a file or directory
///@author S. V. Paulauskas
///@date September 4, 2013
#include <fstream>
#include <iostream>
#include <string>

#include <cstdio>

#include "FileChecker.hpp"
#include "VastExceptions.hpp"

using namespace std;

///This constructor checks to make sure file operations can be performed.
FileChecker::FileChecker(const std::string &flag, const std::string &name){
    if(flag == "file")
        CheckFileExistance(name);
    else if(flag == "dir")
        CheckDirExistance(name);
    else
        throw FileCheckerException("FileChecker::FileChecker - You didn't provide a flag. Expected either "
                                           "file or dir.");
}

///This method checks if a directory already exists
void FileChecker::CheckDirExistance(const string &name) {
    string temp = name+"out.temp";
    ofstream test(temp.c_str());

    if(test.fail())
        throw FileCheckerException("FileChecker::CheckDirExistance - Couldn't write to " + name);

    test.close();

    //this may be system specific, I don't like using it but
    //not really anything better that I can think of
    remove(temp.c_str());
}

///This method checks if a file already exists
void FileChecker::CheckFileExistance(const string &name) {
    ifstream test(name.c_str());
    if(test.fail())
        throw FileCheckerException("FileChecker::CheckFileExistance - Couldn't write to " + name);
    test.close();
}
