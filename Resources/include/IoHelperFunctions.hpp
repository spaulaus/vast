/// @file IoHelperFunctions.hpp
/// @brief
/// @author S. V. Paulauskas
/// @date June 20, 2017
/// @copyright Copyright (c) 2017 S. V. Paulauskas. 
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License

#ifndef VANDLEANALYSISSOFTWARETOOLKIT_IOHELPERFUNCTIONS_HPP
#define VANDLEANALYSISSOFTWARETOOLKIT_IOHELPERFUNCTIONS_HPP

#include <sys/stat.h>

namespace IoHelpers {
    /// A POSIX compliant way to check if we have write permisisons to a file or directory. Taken from the following
    /// forum : https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    ///@param[in] name : The name of the file or directory we want to try writing to.
    inline bool HasWritePermission(const std::string &name) {
        struct stat buffer;
        return stat(name.c_str(), &buffer) == 0;
    }
}

#endif //VANDLEANALYSISSOFTWARETOOLKIT_IOHELPERFUNCTIONS_HPP
