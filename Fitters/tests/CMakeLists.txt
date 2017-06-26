add_executable(test_toffitter test_toffitter.cpp)
target_link_libraries(test_toffitter Calculators Core Fitters FileInput FileOutput SubmoduleStaticLibrary
        ${ROOT_LIBRARIES} RooFit RooFitCore)