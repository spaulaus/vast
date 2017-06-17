///@file unittest-StringManipulation.cpp
///@author S. V. Paulauskas
///@date November 16, 2016
///@brief A code to test functions in the StringManipulator namespace.
#include <iostream>

#include <UnitTest++.h>

#include "StringManipulation.hpp"

using namespace std;

///This method is the main, and is used to test manipulating strings
TEST(Test_ReplaceString) {
    string original = "This is the string that we want to test, bro.";
    string replacement = "mate";
    string expected = "This is the string that we want to test, mate.";
    CHECK(StringManipulation::ReplaceString(original, "bro", "mate") == expected);
}

int main(int argc, char *argv[]) {
    return (UnitTest::RunAllTests());
}