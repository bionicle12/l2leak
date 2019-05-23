set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/threads/CIOTimer.h
    ${L2AUTH_DIR}/include/l2auth/threads/CIOTopTimer.h
    ${L2AUTH_DIR}/include/l2auth/threads/CJob.h
    ${L2AUTH_DIR}/include/l2auth/threads/CLock.h
    ${L2AUTH_DIR}/include/l2auth/threads/CRWLock.h
    ${L2AUTH_DIR}/include/l2auth/threads/IOCP.h
    ${L2AUTH_DIR}/include/l2auth/threads/Threading.h
)

set(__SOURCES
    CIOTimer.cpp
    CIOTopTimer.cpp
    CJob.cpp
    CLock.cpp
    CRWLock.cpp
    IOCP.cpp
    Threading.cpp
)

add_library(${PROJECT_NAME}_threads OBJECT ${__SOURCES} ${__HEADERS})
