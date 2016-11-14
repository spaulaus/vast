///@file Exception.hpp
///@brief A class to handle exceptions.
///@author S. V. Paulauskas
///@date November 12, 2016
#ifndef VAST_EXCEPTION_HPP
#define VAST_EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(const std::string &a) {msg_ = a;};

    ~Exception() {};

    const char* what() const noexcept {return msg_.c_str();}
private:
    std::string msg_; //!< The message to output with the exception
};

#endif //VAST_EXCEPTION_HPP
