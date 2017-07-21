add_executable(unittest-ConfigurationReader unittest-ConfigurationReader.cpp ../source/ConfigurationReader.cpp)
target_link_libraries(unittest-ConfigurationReader UnitTest++ Core Calculators FileInput SubmoduleStaticLibrary
        ${ROOT_LIBRARIES})
install(TARGETS unittest-ConfigurationReader DESTINATION bin/unittests)