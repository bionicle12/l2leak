set(__HEADERS
    ${L2CORE_DIR}/include/l2core/network/packets/ClientToServerPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/NpcToCachePackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/NpcToServerPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/ServerToCachePackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/CacheToServerPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/CacheToNpcPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/LogDPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/AuthToClientPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/AuthToServerPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/ServerToAuthPackets.h
    ${L2CORE_DIR}/include/l2core/network/packets/ServerToNpcPackets.h
)

set(__SOURCES
    ClientToServerPackets.cpp
    NpcToCachePackets.cpp
    NpcToServerPackets.cpp
    ServerToCachePackets.cpp
    CacheToServerPackets.cpp
    CacheToNpcPackets.cpp
    LogDPackets.cpp
    AuthToClientPackets.cpp
    AuthToServerPackets.cpp
    ServerToAuthPackets.cpp
    ServerToNpcPackets.cpp
)

add_library(cached_${PROJECT_NAME}_network_packets STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(cached_${PROJECT_NAME}_network_packets PRIVATE -DL2CACHED)

add_library(l2logd_${PROJECT_NAME}_network_packets STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2logd_${PROJECT_NAME}_network_packets PRIVATE -DL2LOGD)

add_library(l2npc_${PROJECT_NAME}_network_packets STATIC ${__SOURCES} ${__HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_network_packets PRIVATE -DL2NPC)
