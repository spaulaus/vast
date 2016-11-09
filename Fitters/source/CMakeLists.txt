set(FITTERS_SOURCES SimConvoluter.cpp TofFitter.cpp)

message(STATUS "Building Fitters Shared Object")
add_library(FittersObjects OBJECT ${FITTERS_SOURCES})
add_library(Fitters SHARED $<TARGET_OBJECTS:FittersObjects>)
install(TARGETS Fitters DESTINATION lib)