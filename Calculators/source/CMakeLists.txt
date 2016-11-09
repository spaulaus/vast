set(CALCULATOR_SOURCES BGTCalculator.cpp EffCalculator.cpp ErrorCalculator.cpp
        Integrator.cpp NeutronDensity.cpp ParamCalculator.cpp)

message(STATUS "Building Calculator Shared Object")
add_library(Calculator SHARED ${CALCULATOR_SOURCES})
install(TARGETS Calculator DESTINATION lib)