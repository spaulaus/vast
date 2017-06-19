/*! \file FileHandler.hpp
 * \brief A class to handle the various filenames
 * \author S. V. Paulauskas
 * \date 01 December 2013
 */
#ifndef __FILEHANDLER_HPP__
#define __FILEHANDLER_HPP__
#include <map>
#include <string>

//!A class to handle the input and output filenames
class FileHandler {
public:
    /*! Default constructor */
    FileHandler(){};
    /*! Default destructor */
    ~FileHandler(){};

    /*! Get the name of the input file
     *  \param[in] name : The name of the input file that you want. This was
     *  specified in the Config.xml
     *  \return The file name
    */
    std::string GetInputName(const std::string &name) const;
    /*! Get the name of the output file
    *   \param[in] name : The name of the output file that you want. This was
    *   specified in the Config.xml
    *   \return The file name
    */
    std::string GetOutputName(const std::string &name) const;

    /*! Set the name of an input file
      \param[in] name : The internal name of the file
      \param[in] val  : The name that will be given to the file on disk
    */
    void SetInputNames(const std::string &name,
                 const std::string &val);
    /*! Set the name of an output file
      \param[in] name : The internal name of the file
      \param[in] val  : The name that will be given to the file on disk
    */
    void SetOutputNames(const std::string &name,
                 const std::string &val);
private:
    std::map<std::string, std::string> input_, output_;

    ///@brief This method produces the error message when file names can't be found
    ///@param[in] name  : The internal name of the file
    std::string EndError(const std::string &name) const;
};
#endif //__FILEHANDLER_HPP__
