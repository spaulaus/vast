/*! \file FlagHandler.hpp
 * \brief A class to handle information about the experiment
 * \author S. V. Paulauskas
 * \date 03 December 2013
 */
#ifndef __FLAGHANDLER_HPP__
#define __FLAGHANDLER_HPP__
#include <map>
#include <string>

//!A class that handles the various flags for program control
class FlagHandler {
public:
    /*! Default Constructor */
    FlagHandler(){};
    /*! Default Destructor */
    ~FlagHandler(){};

    /*! Get method for flag values
      \param[in] name : the name of the flag you want
      \return The value of the provided flag
    */
    bool GetFlag(const std::string &name){
        const auto it = flags_.find(name);
        if(it == flags_.end())
            EndError(name);
        return(it->second);
    };
    /*! Set the name and value of a flag
     \param[in] name : the name of the flag
     \param[in] val  : the value of the flag (true/false)
    */
    void SetFlag(const std::string &name, const bool &val) {
        flags_.insert(make_pair(name,val));
    };
private:
    std::map<std::string, bool> flags_;
    ///@brief Method that handles flag handling errors
    void EndError(const std::string &name) {
        std::cerr << "We could not find the requested flag name: "
                  << name << std::endl;
        exit(2);
    };
};
#endif //__FLAGHANDLER_HPP__
