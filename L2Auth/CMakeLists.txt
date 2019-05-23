project(L2AuthD)

cmake_minimum_required(VERSION 3.5)

set(LINEAGE_2_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(L2AUTH_DIR ${LINEAGE_2_ROOT_DIR}/L2Auth)

set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /DNDEBUG /MT")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(${LINEAGE_2_ROOT_DIR}/L2Auth/include)
include_directories(${LINEAGE_2_ROOT_DIR}/L2Core/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/etc)

add_executable(${PROJECT_NAME} WIN32
    ${CONFIGS}
    $<TARGET_OBJECTS:${PROJECT_NAME}_network>
    $<TARGET_OBJECTS:${PROJECT_NAME}_model>
    $<TARGET_OBJECTS:${PROJECT_NAME}_main>
    $<TARGET_OBJECTS:${PROJECT_NAME}_config>
    $<TARGET_OBJECTS:${PROJECT_NAME}_db>
    $<TARGET_OBJECTS:${PROJECT_NAME}_crypt>
    $<TARGET_OBJECTS:${PROJECT_NAME}_logger>
    $<TARGET_OBJECTS:${PROJECT_NAME}_model>
    $<TARGET_OBJECTS:${PROJECT_NAME}_network>
    $<TARGET_OBJECTS:${PROJECT_NAME}_threads>
    $<TARGET_OBJECTS:${PROJECT_NAME}_ui>
    $<TARGET_OBJECTS:${PROJECT_NAME}_utils>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_network PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_model PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_main PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_config PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_db PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_crypt PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_logger PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_model PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_threads PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_ui PROPERTY FOLDER "L2AuthD")
set_property(TARGET ${PROJECT_NAME}_utils PROPERTY FOLDER "L2AuthD")

set(_libs
    User32.lib
    Gdi32.lib    # Painting
    Ws2_32.lib   # Sockets
    Advapi32.lib # Regestry
    odbc32.lib   # SQL
    Mswsock.lib  # GetAcceptExSockaddrs
    Dbghelp.lib  # Debug symbol options
)

target_link_libraries(${PROJECT_NAME}
    ${_libs}
    L2Core_crypt
    )

message(STATUS "${PROJECT_NAME} Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "${PROJECT_NAME} General Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "${PROJECT_NAME} Release Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "${PROJECT_NAME} Debug Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "${PROJECT_NAME} Linker Flags: ${CMAKE_EXE_LINKER_FLAGS}")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/install/NewAuth")
install(FILES ${CONFIGS} DESTINATION "${CMAKE_BINARY_DIR}/install/NewAuth/etc")
install(DIRECTORY DESTINATION "${CMAKE_BINARY_DIR}/install/NewAuth/log")
message(STATUS "Install path: ${CMAKE_BINARY_DIR}/install/NewAuth")

