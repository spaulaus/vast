#Set the utility sources that we will make a lib out of
set(SubmoduleSources PhysConstants/src/PhysConstants.cpp pugixml/source/pugixml.cpp
        Signal-Generator/src/SignalGenerator.cpp)

#Add the sources to the library
add_library(SubmoduleObjects OBJECT ${SubmoduleSources})
add_library(SubmoduleStaticLibrary STATIC $<TARGET_OBJECTS:SubmoduleObjects>)

message(STATUS "Building Utility Shared Objects")
add_library(SubmoduleLibrary SHARED $<TARGET_OBJECTS:SubmoduleObjects>)
target_link_libraries(SubmoduleLibrary SubmoduleStaticLibrary)
install(TARGETS SubmoduleLibrary DESTINATION lib)
