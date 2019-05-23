cmake_minimum_required(VERSION 3.5)

project(L2Core_tests)

include_directories(${LINEAGE_2_ROOT_DIR}/L2Core/include)
include_directories(${LINEAGE_2_ROOT_DIR}/tests/L2Core)

add_subdirectory(geometry)
add_subdirectory(network)
