#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet055_RequestLoadSkill.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004450C0
bool packet055_RequestLoadSkill(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet055_RequestLoadSkill(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (characterId == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        serverSocket->Send("cddd", CacheToServerPacket_AquiredSkillList, unknownParam1, characterId, 0);

        unguard();
        return false;
    }

    character->SendBlockList(serverSocket, unknownParam1);
    character->SendAquireSkill(serverSocket, unknownParam1);

    unguard();
    return false;
}
}  // namespace serverHandlers
