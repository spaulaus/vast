set(CORE_SOURCES Decay.cpp Gamma.cpp Neutron.cpp)

message(STATUS "Building Core Shared Object")
add_library(Core SHARED ${CORE_SOURCES})
install(TARGETS Core DESTINATION lib)

if(BUILD_VAST)
    add_executable(vast vast.cpp)
    target_link_libraries(vast Calculators Core Fitters FileInput
            FileOutput ThirdParty PhysConstants RooFit RooFitCore
            ${ROOT_LIBRARIES})
endif(BUILD_VAST)