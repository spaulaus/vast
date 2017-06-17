set(FITTERS_SOURCES SimConvoluter.cpp TofFitter.cpp)
add_library(Fitters STATIC ${FITTERS_SOURCES})
target_link_libraries(Fitters Core)