cmake_minimum_required(VERSION 2.8.8)

project(VAST)

#Compile with c++11 or c++0x depending on the compiler version
if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER "4.3" AND
            ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "4.7")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    elseif (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER "4.6")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER "4.3" AND
            ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "4.7")

    #Make compiler messages nice with colored tags.
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER "4.9")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
    endif ()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fPIC")
endif ()

#if user does not specify prefix we assign it to the exec directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Install Prefix not specified.")
    file(MAKE_DIRECTORY install)
    get_filename_component(INSTALL_DIR ${CMAKE_SOURCE_DIR}/install REALPATH)
    set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR} CACHE PATH "Install Prefix" FORCE)
endif ()
message(STATUS "Installing to ${CMAKE_INSTALL_PREFIX}")

#Define the default build type to be Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Build type, options are: None Debug Release RelWithDebInfo MinSizeRel."
            FORCE)
    message(STATUS "Build type not defined, using default: ${CMAKE_BUILD_TYPE}")
endif (NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#Add additional CXX flags if we use the Debug option
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

#------------------------------------------------------------------------------

#Install options
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_UTILITIES "Build Useful Calculators" ON)
option(BUILD_VAST "Build Vandle Analaysis Software Toolkit VAST" OFF)

#------------------------------------------------------------------------------

#Definitions without options
#Adds the install prefix for referencing in the source code
add_definitions(-D INSTALL_PREFIX="\\"${CMAKE_INSTALL_PREFIX}\\"")

#------------------------------------------------------------------------------

#Find packages
#Load additional find_package scripts.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#Find ROOT since we need it
find_package (ROOT REQUIRED)
mark_as_advanced(FORCE GENREFLEX_EXECUTABLE ROOTCINT_EXECUTABLE
        ROOT_CONFIG_EXECUTABLE)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

#We are going to find the third party libraries at this time most of the
#submodules are going to need at least one of these
link_directories(${CMAKE_SOURCE_DIR}/ThirdParty/libs/)
find_library(PhysConstants PhysConstants PATH
        ${CMAKE_SOURCE_DIR}/ThirdParty/libs/)
find_library(SignalGenerator SignalGenerator PATH
        ${CMAKE_SOURCE_DIR}/ThirdParty/libs/)

#------------------------------------------------------------------------------

#We add a number of include directory since everybody will need parts of them.
include_directories(Calculators/include Core/include FileIo/include
        Fitters/include ThirdParty/include)

add_subdirectory(Calculators/source)
add_subdirectory(Core/source)
add_subdirectory(FileIo)
add_subdirectory(Fitters)
add_subdirectory(ThirdParty)

if(BUILD_UTILITIES)
    add_subdirectory(Utilities)
endif(BUILD_UTILITIES)