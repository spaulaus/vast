/*! \file FileChecker.hpp
 *  \brief A class to check the existence of files and directories
 *  \author S. V. Paulauskas
 *  \date 04 September 2013
 */
#ifndef __FILECHECKER_HPP__
#define __FILECHECKER_HPP__

#include <string>

///A class that checks if a file or directory exists on the filesystem.
class FileChecker {
public:
    /*! Default constructor*/
    FileChecker(){};
    /*! Constructor for checking directory or file
      \param[in] flag : tells us whether we're testing a "dir" or a "file"
      \param[in] name : the directory path or file that we're going to check
     */
    FileChecker(const std::string &flag, const std::string &name);
    /*! Default destructor */
    ~FileChecker(){};
private:
    void CheckDirExistance(const std::string &name);
    void CheckFileExistance(const std::string &name);
};
#endif //__FILECHECKER_HPP__
