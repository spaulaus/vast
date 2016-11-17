add_executable(efficiency efficiency.cpp)
target_link_libraries(efficiency Calculators Core ThirdParty)
install(TARGETS efficiency DESTINATION bin)

add_executable(sensitivity LimitFinder.cpp sensitivity.cpp)
target_link_libraries(sensitivity ${ROOT_LIBRARIES} Core FileInput FileOutput
        Calculators ThirdParty PhysConstants RooFit RooFitCore)
install(TARGETS sensitivity DESTINATION bin)
