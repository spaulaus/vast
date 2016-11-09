/*! \file InputHandler.hpp
 * \brief A class to handle various text file inputs to the program.
 * \author S. V. Paulauskas
 * \date March 10, 2015
 *
 * Copyright S. V. Paulauskas 2013-2015
 * stanpaulauskasATgmailDOTcom
 * Distributed under GNU General Public Licence v3
 */
#ifndef __INPUTHANDLER_HPP__
#define __INPUTHANDLER_HPP__

#include <string>
#include <vector>

#include "Neutron.hpp"

class InputHandler {
public:
    /** Default Constructor */
    InputHandler (){};
    /** Default Destructor */
    ~InputHandler(){};

    ///A function to read the data from an input file
    void ReadFitOutput(std::vector<Neutron> &nvec, const std::string &file);
private:
};
#endif //__INPUTHANDLER_HPP__
