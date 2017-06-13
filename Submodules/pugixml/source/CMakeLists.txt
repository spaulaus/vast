set(THIRD_PARTY_SOURCES pugixml.cpp)

message(STATUS "Building ThirdParty Shared Object")
add_library(ThirdParty SHARED ${THIRD_PARTY_SOURCES})
install(TARGETS ThirdParty DESTINATION lib)