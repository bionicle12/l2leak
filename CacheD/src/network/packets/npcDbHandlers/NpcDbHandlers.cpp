#include <WinSock2.h>

#include "cached/network/packets/npcDbHandlers/npcDbHandlers.h"

#include "cached/network/packets/npcDbHandlers/packet00_DummyPacket.h"
#include "cached/network/packets/npcDbHandlers/packet01_NpcDbVersion.h"
#include "cached/network/packets/npcDbHandlers/packet02_LoadNpcRequest.h"
#include "cached/network/packets/npcDbHandlers/packet03_SaveNpcInfo.h"
#include "cached/network/packets/npcDbHandlers/packet04_UpdateBossNpcValue.h"

const PacketHandler npcDbHandlers::s_packetHandlers[npcDbHandlers::HANDLERS_NUMBER + 1] = {
    &npcDbHandlers::packet00_DummyPacket, &npcDbHandlers::packet01_NpcDbVersion, &npcDbHandlers::packet02_LoadNpcRequest, &npcDbHandlers::packet03_SaveNpcInfo, &npcDbHandlers::packet04_UpdateBossNpcValue, &npcDbHandlers::packet00_DummyPacket};
