///@file test_stringmanipulation.cpp
///@author S. V. Paulauskas
///@date November 16, 2016
///@brief A code to test functions in the StringManipulator namespace.
#include <iostream>

#include "StringManipulation.hpp"

using namespace std;
int main() {
    string original = "This is the string that we want to test, bro.";
    cout << "Here is the original string: " << original << endl;

    cout << "We are going to replace 'bro' with 'mate'. " << endl;

    cout << StringManipulation::ReplaceString(original, "bro", "mate") << endl;
}