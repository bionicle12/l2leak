set(__HEADERS
    ${L2CORE_DIR}/include/l2core/db/DBConn.h
    ${L2CORE_DIR}/include/l2core/db/SqlConnection.h
    ${L2CORE_DIR}/include/l2core/db/CSQLQueue.h
    ${L2CORE_DIR}/include/l2core/db/Pools.h
)

set(__SOURCES
    DBConn.cpp
    CSQLQueue.cpp
)

add_library(cached_${PROJECT_NAME}_db STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_db PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_db STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_db PRIVATE -DL2LOGD)