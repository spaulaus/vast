set(CALCULATOR_SOURCES BGTCalculator.cpp EffCalculator.cpp ErrorCalculator.cpp
        Integrator.cpp NeutronDensity.cpp ParamCalculator.cpp)

message(STATUS "Building Calculators Shared Object")
add_library(Calculators SHARED ${CALCULATOR_SOURCES})
install(TARGETS Calculators DESTINATION lib)