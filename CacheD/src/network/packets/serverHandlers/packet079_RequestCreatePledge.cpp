#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet079_RequestCreatePledge.h"

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
// L2CacheD 0x0043FD10
bool packet079_RequestCreatePledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet079_RequestCreatePledge(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    wchar_t pledgeName[50] = {0};
    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "ddSd", &unknownParam1, &unknownParam2, sizeof(pledgeName), pledgeName, &characterId);

    int newPledgeId = g_pledgeDb.CreatePledge(pledgeName, characterId);
    serverSocket->Send("cdddS", CacheToServerPacket_ReplyCreatePledge2, unknownParam1, unknownParam2, newPledgeId, pledgeName);

    if (newPledgeId <= 0)
    {
        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        unguard();
        return false;
    }

    character->SetPledge(newPledgeId);

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
        LogId_CreatePledge,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        pledgeName,
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        newPledgeId,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
