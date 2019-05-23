set(__HEADERS
    ${L2LOGD_DIR}/include/l2logd/network/CServerSocket.h
    ${L2LOGD_DIR}/include/l2logd/network/CServer.h
)

set(__SOURCES
    CServerSocket.cpp
    CServer.cpp
)

add_library(${PROJECT_NAME}_network OBJECT ${__SOURCES} ${__HEADERS})
