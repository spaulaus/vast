add_executable(unittest-ConfigurationReader unittest-ConfigurationReader.cpp ../source/ConfigurationReader.cpp)
target_link_libraries(unittest-ConfigurationReader UnitTest++ Core Calculators FileInput SubmoduleStaticLibrary)
install(TARGETS unittest-ConfigurationReader DESTINATION bin/unittests)