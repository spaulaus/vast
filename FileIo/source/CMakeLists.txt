set(FILE_INPUT_SOURCES ConfigurationReader.cpp FileChecker.cpp FileHandler.cpp InputHandler.cpp)
message(STATUS "Building FileInput Shared Object")
add_library(FileInput SHARED ${FILE_INPUT_SOURCES})
install(TARGETS FileInput DESTINATION lib)

set(FILE_OUTPUT_SOURCES OutputHandler.cpp)
message(STATUS "Building FileOutput Shared Object")
add_library(FileOutput SHARED ${FILE_OUTPUT_SOURCES})
install(TARGETS FileOutput DESTINATION lib)
