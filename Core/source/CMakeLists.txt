set(CORE_SOURCES Decay.cpp Gamma.cpp Neutron.cpp CrystalBallParameters.cpp)
add_library(Core STATIC ${CORE_SOURCES})
target_link_libraries(Core SubmoduleStaticLibrary Calculators)

if(BUILD_VAST)
    add_executable(vast vast.cpp)
    target_link_libraries(vast Calculators Core Fitters FileInput FileOutput SubmoduleStaticLibrary RooFit RooFitCore
            ${ROOT_LIBRARIES})
    install(TARGETS vast DESTINATION bin)
endif(BUILD_VAST)