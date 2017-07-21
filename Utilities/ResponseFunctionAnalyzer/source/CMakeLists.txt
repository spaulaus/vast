add_executable(responseFunctionAnalyzer responseFunctionAnalyzer.cpp ResponseFunctionAnalyzer.cpp)
target_link_libraries(responseFunctionAnalyzer Core FileInput FileOutput SubmoduleStaticLibrary ${ROOT_LIBRARIES}
        RooFit RooFitCore)
install(TARGETS responseFunctionAnalyzer DESTINATION bin)