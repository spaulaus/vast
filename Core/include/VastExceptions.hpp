///@file Exception.hpp
///@brief A class to handle exceptions.
///@author S. V. Paulauskas
///@date November 12, 2016
#ifndef VAST_EXCEPTION_HPP
#define VAST_EXCEPTION_HPP

#include <exception>
#include <string>
#include <stdexcept>

///A class that tells us that we had an exception with VAST itself.
class VastException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit VastException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception with VAST itself.
class ConfigurationReaderException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit ConfigurationReaderException (const std::string &what) noexcept {}
};


#endif //VAST_EXCEPTION_HPP
