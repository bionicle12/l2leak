set(HEADERS
    ${CACHED_DIR}/include/cached/network/packets/npcDbHandlers/NpcDbHandlers.h
    ${CACHED_DIR}/include/cached/network/packets/npcDbHandlers/packet00_DummyPacket.h
    ${CACHED_DIR}/include/cached/network/packets/npcDbHandlers/packet01_NpcDbVersion.h
    ${CACHED_DIR}/include/cached/network/packets/npcDbHandlers/packet02_LoadNpcRequest.h
    ${CACHED_DIR}/include/cached/network/packets/npcDbHandlers/packet03_SaveNpcInfo.h
    ${CACHED_DIR}/include/cached/network/packets/npcDbHandlers/packet04_UpdateBossNpcValue.h
)

set(SOURCES
    NpcDbHandlers.cpp
    packet00_DummyPacket.cpp
    packet01_NpcDbVersion.cpp
    packet02_LoadNpcRequest.cpp
    packet03_SaveNpcInfo.cpp
    packet04_UpdateBossNpcValue.cpp
)

add_library(${PROJECT_NAME}_network_packets_npcDbHandlers STATIC ${SOURCES} ${HEADERS})
