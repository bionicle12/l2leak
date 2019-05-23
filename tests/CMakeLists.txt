cmake_minimum_required(VERSION 3.5)

if (CMAKE_BUILD_TYPE MATCHES "RELEASE")
    message(STATUS "gtest_force_shared_crt FALSE")
    set(gtest_force_shared_crt FALSE)
else()
    message(STATUS "gtest_force_shared_crt TRUE")
    set(gtest_force_shared_crt TRUE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /DNDEBUG /MT")

include_directories(./googletest/googlemock/include)
include_directories(./googletest/googletest/include)

add_subdirectory(googletest)

set(LINEAGE_2_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_subdirectory(L2Core)
