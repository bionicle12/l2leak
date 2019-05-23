set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/logger/CFileLog.h
    ${L2AUTH_DIR}/include/l2auth/logger/CLogdFilelog.h
    ${L2AUTH_DIR}/include/l2auth/logger/LogType.h
    ${L2AUTH_DIR}/include/l2auth/logger/LogId.h
)

set(__SOURCES
    CFileLog.cpp
    CLogdFilelog.cpp
    LogType.cpp
    LogId.cpp
)

add_library(${PROJECT_NAME}_logger OBJECT ${__SOURCES} ${__HEADERS})
