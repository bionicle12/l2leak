add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/crypt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/db)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/memory)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/network)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/threads)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ipc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geometry)

set(__HEADERS
    ${L2CORE_DIR}/include/l2core/AppInstance.h
    ${L2CORE_DIR}/include/l2core/MemoryObject.h
    ${L2CORE_DIR}/include/l2core/CIOObject.h
    ${L2CORE_DIR}/include/l2core/Orts.h
)

set(__SOURCES
    MemoryObject.cpp
    CIOObject.cpp
)

add_library(cached_${PROJECT_NAME} STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME} PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME} STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME} PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME} STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME} PRIVATE -DL2NPC)
