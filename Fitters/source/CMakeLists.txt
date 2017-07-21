set(FITTERS_SOURCES TofFitter.cpp)
add_library(Fitters STATIC ${FITTERS_SOURCES})
target_link_libraries(Fitters Core)