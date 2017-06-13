set(CALCULATOR_SOURCES BGTCalculator.cpp EffCalculator.cpp ErrorCalculator.cpp Integrator.cpp NeutronDensity.cpp)
add_library(Calculators SHARED ${CALCULATOR_SOURCES})
install(TARGETS Calculators DESTINATION lib)