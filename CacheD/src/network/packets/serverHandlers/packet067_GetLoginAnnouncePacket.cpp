#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet067_GetLoginAnnouncePacket.h"

#include "cached/model/CAnnounce.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00445BA0
bool packet067_GetLoginAnnouncePacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet067_GetLoginAnnouncePacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "d", &characterId);

    uint8_t* buff[BUFFER_SIZE] = {0};

    g_announce.Lock();

    g_announce.ReadAnnounce(false);

    int annoncesNumber = g_announce.GetLoginAnnoncesNumber();
    int annoncesPacketSize = g_announce.GetPacketSize();
    ::memcpy(buff, g_announce.GetLoginAnnoncesPacket(), annoncesPacketSize);

    g_announce.Unlock();

    serverSocket->Send("cddb", CacheToServerPacket_GetLoginAnnouncePacket, characterId, annoncesNumber, annoncesPacketSize, buff);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character != NULL)
    {
        character->ShowPetiMsg(serverSocket);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
