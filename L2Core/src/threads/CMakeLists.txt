set(__HEADERS
    ${L2CORE_DIR}/include/l2core/threads/CThreadManager.h
    ${L2CORE_DIR}/include/l2core/threads/CIODeadlockChecker.h
    ${L2CORE_DIR}/include/l2core/threads/ThreadIndices.h
    ${L2CORE_DIR}/include/l2core/threads/ThreadLocalStorage.h
    ${L2CORE_DIR}/include/l2core/threads/CIOCriticalSection.h
    ${L2CORE_DIR}/include/l2core/threads/IOCP.h
    ${L2CORE_DIR}/include/l2core/threads/IODummyLock.h
    ${L2CORE_DIR}/include/l2core/threads/Threads.h
    ${L2CORE_DIR}/include/l2core/threads/CIOTimer.h
    ${L2CORE_DIR}/include/l2core/threads/SpinLock.h
    ${L2CORE_DIR}/include/l2core/threads/CRWLock.h
    ${L2CORE_DIR}/include/l2core/threads/CObjectMap.h
    ${L2CORE_DIR}/include/l2core/threads/CObjectStorage.h
    ${L2CORE_DIR}/include/l2core/threads/CShardingObjectMap.h
    ${L2CORE_DIR}/include/l2core/threads/CStringObjectMap.h
    ${L2CORE_DIR}/include/l2core/threads/CSPointer.h
    ${L2CORE_DIR}/include/l2core/threads/CExecutionSerializerFast.h
)

set(__SOURCES
    CThreadManager.cpp
    CIODeadlockChecker.cpp
    ThreadLocalStorage.cpp
    CIOCriticalSection.cpp
    IOCP.cpp
    IODummyLock.cpp
    Threads.cpp
    CIOTimer.cpp
    SpinLock.cpp
    CRWLock.cpp
    CObjectMap.cpp
    CObjectStorage.cpp
    CShardingObjectMap.cpp
    CStringObjectMap.cpp
    CSPointer.cpp
    CExecutionSerializerFast.cpp
)

add_library(cached_${PROJECT_NAME}_threads STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_threads PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_threads STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_threads PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_threads STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_threads PRIVATE -DL2NPC)
