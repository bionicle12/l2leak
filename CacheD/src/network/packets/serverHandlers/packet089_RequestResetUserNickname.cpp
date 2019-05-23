#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet089_RequestResetUserNickname.h"

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
// L2CacheD 0x004431C0
bool packet089_RequestResetUserNickname(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet089_RequestResetUserNickname(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "d", &characterId);

    if (!g_userDb.SetUserNickname(characterId, NULL))
    {
        unguard();
        return false;
    }

    serverSocket->Send("cd", CacheToServerPacket_ReplyResetUserNickname, characterId);

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

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%u,,,,,,%s,%s,,,",
        LogId_NicknamePledge,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        NULL,
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
