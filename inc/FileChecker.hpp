#ifndef __FILECHECKER_HPP__
#define __FILECHECKER_HPP__

#include <string>

///A class that checks if a file or directory exists on the filesystem.
class FileChecker {
public:
    FileChecker(const std::string &flag, const std::string &name);
    ~FileChecker(){};
private:
    void CheckDirExistance(const std::string &name);
    void CheckFileExistance(const std::string &name);
};
#endif //__FILECHECKER_HPP__
