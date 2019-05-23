add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/packets)

set(HEADERS
    ${CACHED_DIR}/include/cached/network/CBBSPacket.h
    ${CACHED_DIR}/include/cached/network/CServerSocket.h
    ${CACHED_DIR}/include/cached/network/CCacheDServer.h
    ${CACHED_DIR}/include/cached/network/CNpcDbSocket.h
    ${CACHED_DIR}/include/cached/network/CAdminSocket.h
    ${CACHED_DIR}/include/cached/network/CAdminServer.h
)

set(SOURCES
    CBBSPacket.cpp
    CServerSocket.cpp
    CCacheDServer.cpp
    CNpcDbSocket.cpp
    CAdminSocket.cpp
    CAdminServer.cpp
)

add_library(${PROJECT_NAME}_network STATIC ${SOURCES} ${HEADERS})
