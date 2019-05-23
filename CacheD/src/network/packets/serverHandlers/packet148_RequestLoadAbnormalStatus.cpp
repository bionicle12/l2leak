#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet148_RequestLoadAbnormalStatus.h"

#include "cached/model/AbnormalEffect.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044E120
bool packet148_RequestLoadAbnormalStatus(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet148_RequestLoadAbnormalStatus(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);
    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyLoadAbnormalStatus, unknownParam1, 0);

        unguard();
        return false;
    }

    uint32_t packetSize = 0;
    uint32_t skillCount = 0;
    uint8_t buff[BUFFER_SIZE] = {0};
    const AbnormalEffect* abnormalEffects = character->GetAbnormalEffects();
    for (uint32_t i = 0; i < CUser::ABNORMAL_EFFECT_SIZE; ++i)
    {
        if (abnormalEffects[i].id == 0)
        {
            continue;
        }

        const AbnormalEffect& abnormalEffect = abnormalEffects[i];
        int32_t assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddd", abnormalEffect.id, abnormalEffect.level, abnormalEffect.duration, abnormalEffect.selfCast);
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++skillCount;
        }
    }

    serverSocket->Send("cddb", CacheToServerPacket_ReplyLoadAbnormalStatus, unknownParam1, skillCount, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
