/***************************************************************************
  *  Copyright S. V. Paulauskas 2012-2014                                  *
  *                                                                        *
  *  This program is free software: you can redistribute it and/or modify  *
  *  it under the terms of the GNU General Public License as published by  *
  *  the Free Software Foundation, version 3.0 License.                    *
  *                                                                        *
  *  This program is distributed in the hope that it will be useful,       *
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
  *  GNU General Public License for more details.                          *
  *                                                                        *
  *  You should have received a copy of the GNU General Public License     *
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
  **************************************************************************
*/
/*! \file Variable.hpp
 *  \brief A class for variables in equations. 
 *  \author S. V. Paulauskas
 *  \date 09 November 2012
 */
#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__
#include <iostream>
#include <string>
#include <sstream>

#include <cmath>

class Variable {
public:
    Variable(){};
    Variable(const double &value, const double &error, 
             const std::string &units) {
        value_ = value;
        error_ = error;
        units_ = units;
    };
    ~Variable(){};

    //Overloading the comparison operators here
    inline bool operator== (const Variable &v) const {
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() == v.GetValue());
        else
            return(false);
    }; const
    inline bool operator!= (const Variable &v) const {
        return(!(*this==v));
    };
    inline bool operator> (const Variable &v2) const {
        if(UnitCheck(this->GetUnits(), v2.GetUnits()))
            return(this->GetValue() > v2.GetValue());
        else
            return(false);
    }; const
    inline bool operator< (const Variable &v) const {
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() < v.GetValue());
        else
            return(false);
    }; const
    inline bool operator<= (const Variable &v) const {
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() <= v.GetValue());
        else
            return(false);
    }; const
    inline bool operator>= (const Variable &v) const {
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() >= v.GetValue());
        else
            return(false);
    }; const

    //Overloading the Unitary operators here
    inline Variable operator+(const Variable&v) const {
        if(!UnitCheck(this->GetUnits(), v.GetUnits()))
            return(Variable(0.0,0.0,""));
        double val = this->GetValue() + v.GetValue();
        double err = PmError(this->GetError(),v.GetError());
        std::string unit = this->GetUnits();
        return(Variable(val,err,unit));
    };
    inline Variable operator-(const Variable&v) const {
        if(!UnitCheck(this->GetUnits(), v.GetUnits()))
            return(Variable(0.0,0.0,""));
        double val = this->GetValue() - v.GetValue();
        double err = PmError(this->GetError(),v.GetError());
        std::string unit = this->GetUnits();
        return(Variable(val,err,unit));
    };
    inline Variable operator*(const Variable&v) const {
        double val = this->GetValue() * v.GetValue();
        double err = MdError(val,*this,v);
        std::stringstream ss;
        ss << this->GetUnits() << "*" << v.GetUnits();
        return(Variable(val,err,ss.str()));
    };
    inline Variable operator/(const Variable&v) const {
        double val = this->GetValue() / v.GetValue();
        double err = MdError(val,*this,v);
        std::stringstream ss;
        ss << this->GetUnits() << "/" << v.GetUnits();
        std::string unit = this->GetUnits();
        return(Variable(val,err,ss.str()));
    };
        
    inline void SetValue(const double &a) {value_ = a;};
    inline void SetError(const double &a) {error_ = a;};
    inline void SetUnits(const std::string &a) {units_ = a;};
    
    inline double GetValue(void) const {return(value_);};
    inline double GetError(void) const {return(error_);};
    inline std::string GetUnits(void) const {return(units_);};

    inline std::string Output(void) const {
        std::stringstream ss;
        ss << value_ << " +- " << error_ << " " << units_; 
        return(ss.str());
    };

    inline std::string OutputData(void) const {
        std::stringstream ss;
        ss << value_ << " " << error_; 
        return(ss.str());
    };
private:
    double value_, error_;
    std::string units_;
    
    bool UnitCheck(const std::string &u1, const std::string &u2) const {
        if(u1 == u2)
            return(true);
        else {
            // std::cerr << "WARNING!!!!! You are trying to operate on " 
            //           << "two variables that have different units!!!" 
            //           << std::endl << u1 << " != " << u2 << std::endl;
            return(false);
        }
    };

    double PmError(const double &val1, const double &val2) const {
        return(sqrt(val1*val1+val2*val2));
    };
    double MdError(const double &val, const Variable &v1, 
                   const Variable &v2) const {
        return(val*
               sqrt(v1.GetError()*v1.GetError()/v1.GetValue()/v1.GetValue() +
                    v2.GetError()*v2.GetError()/v2.GetValue()/v2.GetValue()));
    }
}; //class Variable
#endif //__VARIABLE_HPP__
