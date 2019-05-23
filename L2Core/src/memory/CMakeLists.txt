set(__HEADERS
    ${L2CORE_DIR}/include/l2core/memory/Allocator.h
)

set(__SOURCES
    Allocator.cpp
)

add_library(cached_${PROJECT_NAME}_memory STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_memory PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_memory STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_memory PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_memory STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_memory PRIVATE -DL2NPC)
