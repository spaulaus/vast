#Going to do a slight no-no and reference just the class I need to test. We
#will not be moving the directory structure and this should be all right.
add_executable(test_paramcalculator test_paramcalculator.cpp
        ../source/ParamCalculator.cpp)