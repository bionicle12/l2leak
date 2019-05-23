add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/packets)

set(__HEADERS
    ${L2CORE_DIR}/include/l2core/network/CIOBuffer.h
    ${L2CORE_DIR}/include/l2core/network/CIOBufferPool.h
    ${L2CORE_DIR}/include/l2core/network/CIOSocket.h
    ${L2CORE_DIR}/include/l2core/network/CIOServer.h
    ${L2CORE_DIR}/include/l2core/network/PacketUtils.h
    ${L2CORE_DIR}/include/l2core/network/CLogSocket.h
    ${L2CORE_DIR}/include/l2core/network/SocketStatus.h
    ${L2CORE_DIR}/include/l2core/network/CPacketPool.h
    ${L2CORE_DIR}/include/l2core/network/CPacket.h
    ${L2CORE_DIR}/include/l2core/network/CSlot.h
    ${L2CORE_DIR}/include/l2core/network/CLogCli.h
    ${L2CORE_DIR}/include/l2core/network/CIOCPMessage.h
)

set(__SOURCES
    PacketUtils.cpp
    CIOBuffer.cpp
    CIOBufferPool.cpp
    CIOSocket.cpp
    CIOServer.cpp
    CLogSocket.cpp
    SocketStatus.cpp
    CPacketPool.cpp
    CPacket.cpp
    CSlot.cpp
    CLogCli.cpp
    CIOCPMessage.cpp
)

add_library(cached_${PROJECT_NAME}_network STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_network PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_network STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_network PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_network STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_network PRIVATE -DL2NPC -DNEW_SOCKET_SYSTEM)
