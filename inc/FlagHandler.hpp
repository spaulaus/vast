/** \file FlagHandler.hpp
 * \brief A class to handle information about the experiment
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __FLAGHANDLER_HPP__
#define __FLAGHANDLER_HPP__
#include <map>
#include <string>

class FlagHandler {
public:
    FlagHandler(){};
    ~FlagHandler(){};
    
    //Don't normally do this (bad practice, but lazy and it's simple stuff)
    bool GetFlag(const std::string &name){
        auto it = flags_.find(name);
        if(it == flags_.end()) 
            EndError(name);
        return(it->second);
    };
    void SetFlag(const std::string &name, const bool &val) {
        flags_.insert(make_pair(name,val));
    };
private:
    std::map<std::string, bool> flags_;
    void EndError(const std::string &name) { 
        std::cerr << "We could not find the requested flag name: " 
                  << name << std::endl;
        exit(2);
    };
};
#endif //__FLAGHANDLER_HPP__
