add_executable(test_toffitter test_toffitter.cpp)
target_link_libraries(test_toffitter Fitters Core FileInput FileOutput Calculators SubmoduleStaticLibrary
        ${ROOT_LIBRARIES} RooFit RooFitCore)