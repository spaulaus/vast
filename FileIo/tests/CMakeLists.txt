add_executable(test_configuration test_configuration.cpp
        ../source/ConfigurationReader.cpp)
target_link_libraries(test_configuration ThirdParty Core Calculators
        PhysConstants FileInput)