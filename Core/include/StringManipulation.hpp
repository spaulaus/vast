///@file StringManipulation.hpp
///@author S. V. Paulauskas
///@date November 16, 2016
#ifndef VAST_STRINGMANIPULATION_HPP
#define VAST_STRINGMANIPULATION_HPP

#include <string>

#include "Exception.hpp"

namespace StringManipulation {
    ///@brief A function that will replace all instances of the search
    /// with the replace in the subject. I have adapted this from an answer in
    ///http://stackoverflow.com/a/14678946
    ///I have modified so that we throw when the search string is empty and
    /// so that we do not modify the input string.
    static const std::string ReplaceString(const std::string &subject,
                                           const std::string &search,
                                           const std::string &replace) {
        if (search.empty())
            throw Exception("StringManipulation::ReplaceString - The search "
                                    "string was empty!");
        std::string tmp = subject;
        size_t pos = 0;
        while ((pos = tmp.find(search, pos)) != std::string::npos) {
            tmp.replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return tmp;
    }
}


#endif //VAST_STRINGMANIPULATION_HPP
