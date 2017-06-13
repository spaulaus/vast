/*! \file Tokenizer.hpp
 * \brief Tokenizes a string
 * \author S. V. Paulauskas
 * \date February 11, 2015
 *
 * Copyright S. V. Paulauskas 2015
 * stanpaulauskasATgmailDOTcom
 * Distributed under GNU General Public Licence v3
 */
#ifndef __TOKENIZER_HPP__
#define __TOKENIZER_HPP__

#include <string>
#include <vector>

class Tokenizer {
public:
    /** Default Constructor */
    Tokenizer (){};
    /** Constructor taking an argument
     * \param[in] a : the string to tokenize
     * \param[in] d : the string to use as the delimiter */
    Tokenizer(const std::string &a, const std::string &d){
        str_ = a;
        delim_ = d;
        Tokenize();
    }
    /** Default Destructor */
    ~Tokenizer(){};

    /** \return the tokenized string */
    const std::vector<std::string>* GetTokenizedString(void) const {return(&tokenized_);};
    /** Sets the string to use as a delimiter
     * \param[in] a : The value to set*/
    void SetDelimiter(const std::string &a) {delim_ = a; Tokenize();};
    /** Sets Parameter str_ to the value
     * \param[in] a : The value to set*/
    void SetString(const std::string &a) {str_ = a; Tokenize();};
private:
    std::string str_;//!< The string to tokenize
    std::string delim_; //!< The character to use as a delimiter
    std::vector<std::string> tokenized_;//!< The tokenized string

    /** \brief Tokenizes the string that's been set */
    void Tokenize(void) {
        tokenized_.clear();
        size_t current, next = -1;
        do {
            current = next + 1;
            next = str_.find_first_of(delim_, current);
            tokenized_.push_back(str_.substr( current, next - current ));
        } while (next != std::string::npos);
    }
};
#endif //__TOKENIZER_HPP__
