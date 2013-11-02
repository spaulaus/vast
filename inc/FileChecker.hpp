#ifndef __FILECHECKER_HPP__
#define __FILECHECKER_HPP__

#include <string>

class FileChecker {
public:
    FileChecker(const std::string &flag, const std::string &name);
    ~FileChecker(){};
private:
    void CheckDirExistance(const std::string &name);
    void CheckFileExistance(const std::string &name);
};
#endif //__FILECHECKER_HPP__
