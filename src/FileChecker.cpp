#include <fstream>
#include <iostream>

#include <cstdio>

#include "FileChecker.hpp"

using namespace std;

FileChecker::FileChecker(const string &flag, const string &name){
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

void FileChecker::CheckDirExistance(const string &name) {
    ofstream test(name.c_str());
    if(test.fail()) {
        cout << endl << endl 
             << "Holy fuck!!! We couldn't open the following file for " 
             << "i/o operations. This is an issue with me." << endl 
             << "What I got was " << name
             << "  You may consider the option that the path does not" 
             << "exist" << endl << endl;
        exit(1);
    }
    test.close();
}

void FileChecker::CheckFileExistance(const string &name) {
    ifstream test(name.c_str());
    if(test.fail()) {
        cout << endl << endl 
             << "Holy fuck!!! We couldn't open the following file for " 
             << "i/o operations. This is an issue with me." << endl 
             << "What I got was " << name
             << "  You may consider the option that the path does not" 
             << "exist" << endl << endl;
        exit(1);
    }
    test.close();
}
