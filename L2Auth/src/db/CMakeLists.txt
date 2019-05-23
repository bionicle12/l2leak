set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/db/CAccount.h
    ${L2AUTH_DIR}/include/l2auth/db/CDBConn.h
    ${L2AUTH_DIR}/include/l2auth/db/CServerUserCountStatus.h
    ${L2AUTH_DIR}/include/l2auth/db/DBEnv.h
    ${L2AUTH_DIR}/include/l2auth/db/SqlConnection.h
)

set(__SOURCES
    CAccount.cpp
    CDBConn.cpp
    CServerUserCountStatus.cpp
    DBEnv.cpp
)

add_library(${PROJECT_NAME}_db OBJECT ${__SOURCES} ${__HEADERS})
