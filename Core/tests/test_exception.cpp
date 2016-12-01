///@file exception_test.cpp
///@brief A small program to test functionality of the exception class.
///@author S. V. Paulauskas
///@date November 12, 2016
#include <iostream>

#include "Exception.hpp"

///This method is the main, and is used to test error catching/exception throwing
int main(int argc, char** argv) {
    try{
        throw Exception("exception_test.cpp : Throwing an exception.");
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}