#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet046_RequestSetUserNickname.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00442EE0
bool packet046_RequestSetUserNickname(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet046_RequestSetUserNickname(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t characterId = 0;
    wchar_t newNickname[24] = {0};

    PacketUtils::Disassemble(packet, "dddS", &unknownParam1, &unknownParam2, &characterId, sizeof(newNickname), newNickname);

    if (!g_userDb.SetUserNickname(characterId, newNickname))
    {
        serverSocket->Send("cddSd", CacheToServerPacket_ReplySetUserNickname, unknownParam1, unknownParam2, newNickname, 0);

        unguard();
        return false;
    }

    serverSocket->Send("cddSd", CacheToServerPacket_ReplySetUserNickname, unknownParam1, unknownParam2, newNickname, 1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(character->GetPledgeID());
    if (pledge == NULL)
    {
        unguard();
        return false;
    }

    wchar_t pledgeName[31] = {0};
    wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%u,,,,,,%s,%s,,,",
        LogId_NicknamePledge,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        newNickname,
        pledgeName,
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        pledge->id(),
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
