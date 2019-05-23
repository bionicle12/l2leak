project(L2LogD)
cmake_minimum_required(VERSION 3.5)

set(LINEAGE_2_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(L2LOGD_DIR ${LINEAGE_2_ROOT_DIR}/L2LogD)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DL2LOGD)

include_directories(${LINEAGE_2_ROOT_DIR}/L2LogD/include)
include_directories(${LINEAGE_2_ROOT_DIR}/L2Core/include)

set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /DNDEBUG /MT")

add_subdirectory(./etc)
add_subdirectory(./src)

add_executable(${PROJECT_NAME} WIN32
    ${CONFIGS}
    $<TARGET_OBJECTS:${PROJECT_NAME}_config>
    $<TARGET_OBJECTS:${PROJECT_NAME}_network>
    $<TARGET_OBJECTS:${PROJECT_NAME}_data>
    $<TARGET_OBJECTS:${PROJECT_NAME}_threads>
    $<TARGET_OBJECTS:${PROJECT_NAME}_ui>
    $<TARGET_OBJECTS:${PROJECT_NAME}_main>
)

target_link_libraries(${PROJECT_NAME}
    User32.lib
    Gdi32.lib    # Painting
    Ws2_32.lib   # Sockets
    Advapi32.lib # Regestry
    odbc32.lib   # SQL
    Mswsock.lib  # GetAcceptExSockaddrs
    Dbghelp.lib  # Debug symbol options
    pdh.lib      # Performance
    Psapi.lib    # Process Status API (GetProcessMemoryInfo)

    l2logd_L2Core
    l2logd_L2Core_db
    l2logd_L2Core_logger
    l2logd_L2Core_memory
    l2logd_L2Core_network
    l2logd_L2Core_network_packets
    l2logd_L2Core_threads
    l2logd_L2Core_utils
    l2logd_L2Core_utils_dbg
)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "L2LogD")
set_property(TARGET ${PROJECT_NAME}_config PROPERTY FOLDER "L2LogD")
set_property(TARGET ${PROJECT_NAME}_data PROPERTY FOLDER "L2LogD")
set_property(TARGET ${PROJECT_NAME}_network PROPERTY FOLDER "L2LogD")
set_property(TARGET ${PROJECT_NAME}_threads PROPERTY FOLDER "L2LogD")
set_property(TARGET ${PROJECT_NAME}_ui PROPERTY FOLDER "L2LogD")
set_property(TARGET ${PROJECT_NAME}_main PROPERTY FOLDER "L2LogD")

message(STATUS "${PROJECT_NAME} Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "${PROJECT_NAME} General Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "${PROJECT_NAME} Release Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "${PROJECT_NAME} Debug Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "${PROJECT_NAME} Linker Flags: ${CMAKE_EXE_LINKER_FLAGS}")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/install/L2LogD")
install(FILES ${CONFIGS} DESTINATION "${CMAKE_BINARY_DIR}/install/L2LogD")
message(STATUS "${PROJECT_NAME} Install path: ${CMAKE_BINARY_DIR}/install/L2LogD")

