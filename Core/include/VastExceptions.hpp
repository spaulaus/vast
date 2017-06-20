///@file Exception.hpp
///@brief A class to handle exceptions.
///@author S. V. Paulauskas
///@date November 12, 2016
#ifndef VAST_EXCEPTION_HPP
#define VAST_EXCEPTION_HPP

#include <stdexcept>

///A generic VAST exception.
class VastException : public std::exception {
public:
    ///@brief Constructor that sets the value of what_
    ///@param[in] what : The string that we want to assign to what
    explicit VastException (const std::string &what) noexcept : what_(what) {}
    virtual const char* what() const noexcept { return what_.c_str(); }
private:
    std::string what_;
};

///A class that tells us that we had an exception when reading the configuration file.
class ConfigurationReaderException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit ConfigurationReaderException (const std::string &what) noexcept : VastException(what) {}
};

///A class that tells us that we had an exception when using the TofFittter.
class TofFitterException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit TofFitterException (const std::string &what) noexcept : VastException(what) {}
};

///A class that tells us that we had an exception when using the InputHandler.
class InputHandlerException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit InputHandlerException (const std::string &what) noexcept : VastException(what) {}
};

///A class that tells us that we had an exception when using the OuptutHandler.
class OutputHandlerException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit OutputHandlerException (const std::string &what) noexcept : VastException(what) {}
};

///A class that tells us that we had an exception when doing IO operations with files.
class VastIoException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit VastIoException (const std::string &what) noexcept : VastException(what) {}
};

///A class that tells us that we had an exception when using the SimConvoluter.
class SimConvoluterException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit SimConvoluterException (const std::string &what) noexcept : VastException(what) {}
};

///A class that tells us that we had an exception when using the FileHandler.
class FileHandlerException : public VastException {
public:
    ///@brief Constructor that sets the value of what
    ///@param[in] what : The string that we want to assign to what
    explicit FileHandlerException (const std::string &what) noexcept : VastException(what) {}
};


#endif //VAST_EXCEPTION_HPP
