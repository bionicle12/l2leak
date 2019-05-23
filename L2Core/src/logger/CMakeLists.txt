set(__HEADERS
    ${L2CORE_DIR}/include/l2core/logger/FileBuffers.h
    ${L2CORE_DIR}/include/l2core/logger/LogType.h
    ${L2CORE_DIR}/include/l2core/logger/ServerTypes.h
    ${L2CORE_DIR}/include/l2core/logger/LogId.h
    ${L2CORE_DIR}/include/l2core/logger/CLog.h
)

set(__SOURCES
    FileBuffers.cpp
    LogType.cpp
    ServerTypes.cpp
    LogId.cpp
    CLog.cpp
)

add_library(cached_${PROJECT_NAME}_logger STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_logger PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_logger STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_logger PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_logger STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_logger PRIVATE -DL2NPC)
