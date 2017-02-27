#include <fstream>
#include <iostream>
#include <string>

#include <cstdio>

#include "FileChecker.hpp"

using namespace std;

///This constructor checks to make sure file operations can be performed.
FileChecker::FileChecker(const std::string &flag, const std::string &name){
    if(flag == "file")
        CheckFileExistance(name);
    else if(flag == "dir")
        CheckDirExistance(name);
    else {
        cout << "You didn't give the FileChecker a type" << endl
             << "The only info I have to go on is the name: "
             << name << flag << endl << endl;
        exit(2);
    }
}

///This method checks if a directory already exists
void FileChecker::CheckDirExistance(const string &name) {
    string temp = name+"out.temp";
    ofstream test(temp.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the following directory for "
             << "i/o operations : " << endl << "\"" << name << "\"." << endl
             << "This is an issue with me." << endl << endl;
        exit(1);
    }
    test.close();
    //this may be system specific, I don't like using it but
    //not really anything better that I can think of
    remove(temp.c_str());
}

///This method checks if a file already exists
void FileChecker::CheckFileExistance(const string &name) {
    ifstream test(name.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the following file for "
             << "i/o operations : " << endl << "\"" << name << "\"." << endl
             << "This is an issue with me." << endl << endl;
        exit(1);
    }
    test.close();
}
