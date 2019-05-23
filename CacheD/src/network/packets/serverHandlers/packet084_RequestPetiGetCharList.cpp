#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet084_RequestPetiGetCharList.h"

#include "cached/model/CAccount.h"
#include "cached/model/CUser.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
struct CharactersOnAccountPredicate
{
    CharactersOnAccountPredicate()
        : characterCount(0)
        , packetSize(0)
    {
    }

    bool operator()(CUser* currentUser)
    {
        if (currentUser == NULL)
        {
            return true;
        }

        int assembledSize = PacketUtils::Assemble(&buffer[packetSize], BUFFER_SIZE - packetSize, "Shd", currentUser->GetCharName(), currentUser->GetBuilder(), currentUser->GetId());
        if (assembledSize > 0)
        {
            packetSize += packetSize;
            ++characterCount;
        }

        return false;
    }

    uint32_t packetSize;
    uint32_t characterCount;
    uint8_t buffer[BUFFER_SIZE];
};

// L2CacheD 0x00457C80
bool packet084_RequestPetiGetCharList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet084_RequestPetiGetCharList(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    char accountName[15] = {0};
    PacketUtils::Disassemble(packet, "s", sizeof(accountName), &accountName);
    uint32_t accountId = CAccount::AccountNameToId(accountName);
    if (accountId == 0)
    {
        serverSocket->Send("csd", CacheToServerPacket_ReplyPetiGetCharList, accountName, 0);

        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(accountId);
    if (account == NULL)
    {
        serverSocket->Send("csd", CacheToServerPacket_ReplyPetiGetCharList, accountName, 0);

        unguard();
        return false;
    }

    CharactersOnAccountPredicate predicate;
    account->GetChars().ForEach(predicate);

    serverSocket->Send("csdb", CacheToServerPacket_ReplyPetiGetCharList, accountName, predicate.characterCount, predicate.packetSize, predicate.buffer);

    unguard();
    return false;
}
}  // namespace serverHandlers
