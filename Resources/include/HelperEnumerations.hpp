/// @file HelperEnumerations.hpp
/// @brief
/// @author S. V. Paulauskas
/// @date June 15, 2017
/// @copyright Copyright (c) 2017 S. V. Paulauskas. 
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License

#ifndef VANDLEANALYSISSOFTWARETOOLKIT_HELPERENUMERATIONS_HPP
#define VANDLEANALYSISSOFTWARETOOLKIT_HELPERENUMERATIONS_HPP

#include <stdexcept>

namespace EfficiencyEnums {
    /*! An enum that contains all of the efficiencies that we are
     *  currently investigating in the code. \n
     *  + beta    : The beta efficiency from Miguel's Calculations, currently
     *                  UNUSED due to the requirement for Q effective for the
     *                  calculation.
     *  + ge      : The Ge efficiency for gamma rays.
     *  + mmfCalc  : The parameterization taken from Miguel's code that adjusts
     *                  the efficiency based off of his banana gate.
     *  + mmfTheory  : The parameterization of the simulation results from
     *                  Miguel's values sent to Sergey on 03-12-2014
     *  + rolling : The original efficiency from Sergey - BAD, kept for legacy
     *  + svpBan4 : The new parameterization is from the data provided to Sergey
     *                  for my 077cu.ban banana 4, he provided these to me on
     *                  09-10-2014, it was updated on 09-17-2014.
     *  + svpTestBan1 : Banana that is a little wider than the previous one.
     *  + vandle  : The efficiency taken from the LG Cf data (~ 6 keVee) */
    enum class EffTypes {beta, ge, mmfCalc, mmfTheory, rolling, svpBan4, svpTestBan1, vandle};

    ///This method converts string reads from the configuration file into efficiency types.
    static EffTypes ConvertStringToEfficiencyType(const std::string &a) {
        if (a == "mmfCalc")
            return (EffTypes::mmfCalc);
        if (a == "mmfTheory")
            return (EffTypes::mmfTheory);
        if (a == "rolling")
            return (EffTypes::rolling);
        if (a == "svpBan4")
            return (EffTypes::svpBan4);
        if (a == "svpTestBan1")
            return (EffTypes::svpTestBan1);
        if (a == "vandle")
            return EffTypes::vandle;
        throw std::invalid_argument("StringToEffType - Unknown efficiency type requested : " + a);
    }
}

#endif //VANDLEANALYSISSOFTWARETOOLKIT_HELPERENUMERATIONS_HPP
