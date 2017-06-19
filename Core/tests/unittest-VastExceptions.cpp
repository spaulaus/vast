///@file unittest-VastExceptions.cpp
///@author S. V. Paulauskas
///@date June 19, 2017
///@brief A small code to test the behavior of the CrystalBallParameters
#include <iostream>

#include <UnitTest++.h>

#include "VastExceptions.hpp"

using namespace std;

///This method is the main, and is used to test what the crystal ball parameters do
TEST(Test_VastExceptionMessages) {
    std::string exceptionMessage = "We want to know that this message gets passed properly.";
    try {
        throw VastException(exceptionMessage);
    } catch (VastException &ex) {
        CHECK_EQUAL(exceptionMessage, ex.what());
    }

    try {
        throw ConfigurationReaderException(exceptionMessage);
    } catch (ConfigurationReaderException &ex) {
        CHECK_EQUAL(exceptionMessage, ex.what());
    }
}

int main(int argc, char *argv[]) {
    return (UnitTest::RunAllTests());
}