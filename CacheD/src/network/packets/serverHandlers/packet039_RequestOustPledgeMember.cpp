#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet039_RequestOustPledgeMember.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00442480
bool packet039_RequestOustPledgeMember(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet039_RequestOustPledgeMember(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int32_t unknownParam1 = 0;
    int32_t unknownParam2 = 0;
    uint32_t pledgeId = 0;
    wchar_t charName[24] = {0};
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dddS", &unknownParam1, &unknownParam2, &pledgeId, sizeof(charName), charName);

    uint32_t oustMemberId = g_pledgeDb.OustPledgeMember(pledgeId, charName);
    if (oustMemberId == 0)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, oustMemberId);

        serverSocket->Send("cdddS", CacheToServerPacket_ReplyOustPledgeMemberPacket, unknownParam1, unknownParam2, 0, charName);

        unguard();
        return false;
    }

    CUserSP oustMember = g_userDb.GetUser(oustMemberId, true);
    if (oustMember == NULL)
    {
        serverSocket->Send("cdddS", CacheToServerPacket_ReplyOustPledgeMemberPacket, unknownParam1, unknownParam2, oustMemberId, charName);

        unguard();
        return false;
    }

    wchar_t pledgeName[24] = {0};
    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->ReadLock();

        ::wcscpy(pledgeName, pledge->name());

        pledge->ReadUnlock();
    }

    oustMember = g_userDb.GetUser(oustMemberId, true);
    if (oustMember == NULL)
    {
        serverSocket->Send("cdddS", CacheToServerPacket_ReplyOustPledgeMemberPacket, unknownParam1, unknownParam2, oustMemberId, &charName);

        unguard();
        return false;
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
        LogId_OustPledge,
        oustMember->GetId(),
        oustMember->GetAccountID(),
        oustMember->GetX(),
        oustMember->GetY(),
        oustMember->GetZ(),
        pledgeName,
        oustMember->GetRace(),
        oustMember->GetGender(),
        oustMember->GetClass(),
        oustMember->GetLevel(),
        pledgeId,
        oustMember->GetCharName(),
        oustMember->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
