add_executable(unittest-CrystalBallParameters unittest-CrystalBallParameters.cpp ../source/CrystalBallParameters.cpp)
target_link_libraries(unittest-CrystalBallParameters UnitTest++)
install(TARGETS unittest-CrystalBallParameters DESTINATION bin/unittests)

add_executable(unittest-StringManipulation unittest-StringManipulation.cpp)
target_link_libraries(unittest-StringManipulation UnitTest++)
install(TARGETS unittest-StringManipulation DESTINATION bin/unittests)

