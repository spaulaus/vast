/** \file FileHandler.hpp
 * \brief A class to handle the various filenames
 * \author S. V. Paulauskas
 * \date 01 December 2013
 */
#ifndef __FILEHANDLER_HPP__
#define __FILEHANDLER_HPP__
#include <map>
#include <string>

class FileHandler {
public:
    FileHandler(){};
    ~FileHandler(){};

    std::string GetInputName(const std::string &name) const;
    std::string GetOutputName(const std::string &name) const;

    void SetInputNames(const std::string &name, 
                 const std::string &val);
    void SetOutputNames(const std::string &name, 
                 const std::string &val);
private:
    std::map<std::string, std::string> input_, output_;
    
    void EndError(const std::string &name) const;
};
#endif //__FILEHANDLER_HPP__
