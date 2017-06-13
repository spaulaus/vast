add_executable(test_exception test_exception.cpp)

add_executable(tests_stringmanipulation test_stringmanipulation.cpp)

add_executable(unittest-CrystalBallParameters unittest-CrystalBallParameters.cpp ../source/CrystalBallParameters.cpp)
target_link_libraries(unittest-CrystalBallParameters UnitTest++)
install(TARGETS unittest-CrystalBallParameters DESTINATION bin/unittests)