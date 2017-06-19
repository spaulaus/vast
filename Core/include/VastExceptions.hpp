///@file Exception.hpp
///@brief A class to handle exceptions.
///@author S. V. Paulauskas
///@date November 12, 2016
#ifndef VAST_EXCEPTION_HPP
#define VAST_EXCEPTION_HPP

#include <exception>
#include <string>
#include <stdexcept>

///A generic VAST exception.
class VastException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit VastException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when reading the configuration file.
class ConfigurationReaderException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit ConfigurationReaderException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when using the TofFittter.
class TofFitterException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit TofFitterException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when using the InputHandler.
class InputHandlerException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit InputHandlerException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when using the OuptutHandler.
class OutputHandlerException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit OutputHandlerException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when using the FileChecker.
class FileCheckerException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit FileCheckerException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when using the SimConvoluter.
class SimConvoluterException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit SimConvoluterException (const std::string &what) noexcept {}
};

///A class that tells us that we had an exception when using the FileHandler.
class FileHandlerException : public std::exception {
public:
    ///@brief Constructor that sets the value of msg_
    ///@param[in] a : The string that we want to assign to what
    explicit FileHandlerException (const std::string &what) noexcept {}
};


#endif //VAST_EXCEPTION_HPP
