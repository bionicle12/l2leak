set(__HEADERS
    ${L2CORE_DIR}/include/l2core/ipc/CSharedRWLock.h
)

set(__SOURCES
    CSharedRWLock.cpp
)

add_library(l2npc_${PROJECT_NAME}_ipc STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_ipc PRIVATE)
