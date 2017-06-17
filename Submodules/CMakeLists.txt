set(SubmoduleSources PhysConstants/src/PhysConstants.cpp pugixml/source/pugixml.cpp
        Signal-Generator/src/SignalGenerator.cpp)
add_library(SubmoduleStaticLibrary STATIC ${SubmoduleSources})

