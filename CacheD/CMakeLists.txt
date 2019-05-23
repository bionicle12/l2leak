project(CacheD)
cmake_minimum_required(VERSION 3.5)

set(LINEAGE_2_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CACHED_DIR ${LINEAGE_2_ROOT_DIR}/CacheD)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DL2CACHED)

include_directories(${LINEAGE_2_ROOT_DIR}/CacheD/include)
include_directories(${LINEAGE_2_ROOT_DIR}/L2Core/include)

set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /DNDEBUG /MT")

message(STATUS "${PROJECT_NAME} Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "${PROJECT_NAME} General Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "${PROJECT_NAME} Release Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "${PROJECT_NAME} Debug Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "${PROJECT_NAME} Linker Flags: ${CMAKE_EXE_LINKER_FLAGS}")

add_subdirectory(./etc)
add_subdirectory(./src)

set(RESOURCES
    src/ui/Icon_1.ico
    src/ui/Icon_2.ico
)

set(RC_FILE
    src/ui/resources.rc
)

add_executable(${PROJECT_NAME} WIN32
    ${CONFIGS}
    src/main.cpp
    ${RC_FILE} ${RESOURCES}
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

    L2Core_crypt
    cached_L2Core
    cached_L2Core_db
    cached_L2Core_logger
    cached_L2Core_memory
    cached_L2Core_network
    cached_L2Core_network_packets
    cached_L2Core_threads
    cached_L2Core_utils
    cached_L2Core_utils_dbg

    ${PROJECT_NAME}_config
    ${PROJECT_NAME}_threads
    ${PROJECT_NAME}_network
    ${PROJECT_NAME}_network_packets_adminHandlers
    ${PROJECT_NAME}_network_packets_serverHandlers
    ${PROJECT_NAME}_network_packets_npcDbHandlers
    ${PROJECT_NAME}_ui
    ${PROJECT_NAME}_data
    ${PROJECT_NAME}_model
)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_config PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_network PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_network_packets_adminHandlers PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_network_packets_serverHandlers PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_network_packets_npcDbHandlers PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_threads PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_ui PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_data PROPERTY FOLDER "CacheD")
set_property(TARGET ${PROJECT_NAME}_model PROPERTY FOLDER "CacheD")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/install/CacheD")
install(FILES ${CONFIGS} DESTINATION "${CMAKE_BINARY_DIR}/install/CacheD")
message(STATUS "${PROJECT_NAME} Install path: ${CMAKE_BINARY_DIR}/install/")

