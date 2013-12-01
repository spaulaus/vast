/** \file Configuration.hpp
 * \brief A class to handle the configuration xml
 * \author S. V. Paulauskas
 * \date 30 November 2013
 */
#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__
#include <string>

#include "Decay.hpp"

#include <pugixml.hpp>

class Configuration {
public:
    Configuration(){};
    Configuration(const std::string &file);
    ~Configuration(){};

    Decay ReadDecay();
private:
    pugi::xml_document doc_;

    std::string file_;
};
#endif //__CONFIGURATION_HPP__
