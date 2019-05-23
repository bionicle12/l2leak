#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet214_RequestSurrenderPersonally.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00454DC0
bool packet214_RequestSurrenderPersonally(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet214_RequestSurrenderPersonally(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    uint32_t warId = 0;
    PacketUtils::Disassemble(packet, "ddd", &unknownParam1, &characterId, &warId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cddd", CacheToServerPacket_ReplySurrenderPersonally, unknownParam1, warId, 0);

        unguard();
        return false;
    }

    bool isSurrenderSuccess = character->SurrenderPersonally(warId);
    serverSocket->Send("cddd", CacheToServerPacket_ReplySurrenderPersonally, unknownParam1, warId, isSurrenderSuccess ? 1 : 0);

    unguard();
    return false;
}
}  // namespace serverHandlers
