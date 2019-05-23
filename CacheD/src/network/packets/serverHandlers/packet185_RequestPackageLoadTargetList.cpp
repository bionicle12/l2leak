#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet185_RequestPackageLoadTargetList.h"

#include "cached/model/CAccount.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
struct AnotherCharactersOnAccountPredicate
{
    AnotherCharactersOnAccountPredicate(uint32_t characterId)
        : characterId(characterId)
        , characterCount(0)
        , packetSize(0)
    {
    }

    bool operator()(CUser* currentUser)
    {
        if (currentUser == NULL)
        {
            return false;
        }

        if (currentUser->GetId() == characterId)
        {
            return false;
        }

        PacketUtils::Assemble(&buffer[packetSize], BUFFER_SIZE - packetSize, "dS", currentUser->GetId(), currentUser->GetCharName());

        return false;
    }

    uint32_t characterId;
    uint32_t packetSize;
    uint32_t characterCount;
    uint8_t buffer[BUFFER_SIZE];
};

// L2CacheD 0x00458300
bool packet185_RequestPackageLoadTargetList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet185_RequestPackageLoadTargetList(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, dbid[%d]", TEXT(__FILE__), __LINE__, characterId);

        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageLoadTargetList, unknownParam1, 0);

        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(character->GetAccountID());
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, dbid[%d]", TEXT(__FILE__), __LINE__, characterId);

        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageLoadTargetList, unknownParam1, 0);

        unguard();
        return false;
    }

    account->ReadLock();

    const CObjectMap<CUser>& charactersMap = account->GetChars();
    if (charactersMap.GetSize() <= 0)
    {
        account->ReadUnlock();  // FIXED move above Send

        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageLoadTargetList, unknownParam1, 0);

        unguard();
        return false;
    }

    AnotherCharactersOnAccountPredicate predicate(characterId);
    charactersMap.ForEach(predicate);

    account->ReadUnlock();

    if (predicate.characterCount == 0)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageLoadTargetList, unknownParam1, 0);
    }
    else
    {
        serverSocket->Send("cddb", CacheToServerPacket_ReplyPackageLoadTargetList, unknownParam1, predicate.characterCount, predicate.packetSize, predicate.buffer);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
