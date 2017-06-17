set(CALCULATOR_SOURCES BGTCalculator.cpp EffCalculator.cpp ErrorCalculator.cpp Integrator.cpp NeutronDensity.cpp)
add_library(Calculators STATIC ${CALCULATOR_SOURCES})
target_link_libraries(Calculators Core)
