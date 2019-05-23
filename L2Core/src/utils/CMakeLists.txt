add_subdirectory(dbg)

set(__HEADERS
    ${L2CORE_DIR}/include/l2core/utils/CBCPLogFile.h
    ${L2CORE_DIR}/include/l2core/utils/Utils.h
    ${L2CORE_DIR}/include/l2core/utils/PerfMonitor.h
    ${L2CORE_DIR}/include/l2core/utils/CQsCheck.h
    ${L2CORE_DIR}/include/l2core/utils/cstdint_support.h
    ${L2CORE_DIR}/include/l2core/utils/Unused.h
    ${L2CORE_DIR}/include/l2core/utils/FileUtils.h
)

set(__SOURCES
    CBCPLogFile.cpp
    Utils.cpp
    PerfMonitor.cpp
    CQsCheck.cpp
    FileUtils.cpp
)

add_library(cached_${PROJECT_NAME}_utils STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_utils PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_utils STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_utils PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_utils STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_utils PRIVATE -DL2NPC)
