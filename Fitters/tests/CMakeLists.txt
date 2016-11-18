add_executable(test_toffitter test_toffitter.cpp)
target_link_libraries(test_toffitter Calculators Core Fitters FileInput
        FileOutput ThirdParty PhysConstants RooFit RooFitCore
        ${ROOT_LIBRARIES})