set(FILE_INPUT_SOURCES ConfigurationReader.cpp FileHandler.cpp InputHandler.cpp XmlInterface.cpp)
add_library(FileInput STATIC ${FILE_INPUT_SOURCES})

set(FILE_OUTPUT_SOURCES OutputHandler.cpp)
add_library(FileOutput STATIC ${FILE_OUTPUT_SOURCES})
