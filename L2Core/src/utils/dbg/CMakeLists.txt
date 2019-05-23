set(__HEADERS
    ${L2CORE_DIR}/include/l2core/utils/dbg/CExceptionInit.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/CoreDump.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/CallStack.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/LockStack.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/StackFrame.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/StackFrameList.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/StackGuard.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/Crash.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/Assert.h
    ${L2CORE_DIR}/include/l2core/utils/dbg/Debug.h
)

set(__SOURCES
    CExceptionInit.cpp
    CoreDump.cpp
    CallStack.cpp
    LockStack.cpp
    StackGuard.cpp
    Assert.cpp
    Debug.cpp
)

add_library(cached_${PROJECT_NAME}_utils_dbg STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_utils_dbg PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_utils_dbg STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_utils_dbg PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_utils_dbg STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_utils_dbg PRIVATE -DL2NPC)
