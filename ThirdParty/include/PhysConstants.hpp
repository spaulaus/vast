/*
* Copyright S.V. Paulauskas 2012
* stanpaulauskas@gmail.com
* Distributed under GNU General Public Licence v3
*/

/*! \file PhysConstants.hpp
 *  \brief A class to handle physical constants
 *  \author S.V. Paulauskas
 *  \date 09 November 2012
 */
#ifndef __PHYSCONSTANTS_HPP__
#define __PHYSCONSTANTS_HPP__
#include <map>
#include <string>

#include <Variable.hpp>

class PhysConstants {
public:
    PhysConstants() {Init();};
    ~PhysConstants(){};
    
    Variable GetConstant(const std::string &name) const;
private:
    void Init(void);
    void SetConstant(const std::string &name,  const double &val,
                     const double &error, const std::string &unit);

    std::map<std::string, Variable> consts_;
};//class PhysConstants
#endif //__PHYSCONSTANTS_HPP__
