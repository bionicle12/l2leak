#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet104_RequestBuilderAccountList.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
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
// L2CacheD 0x0043A400
bool packet104_RequestBuilderAccountList(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet104_RequestBuilderAccountList(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    uint8_t packetBuffer[BUFFER_SIZE];

    char builderAccountName[20];
    DBConn sql;
    sql.Bind(builderAccountName, 20);

    int allAssembledBytesCount = 0;
    int entryCount = 0;
    if (!sql.Execute(L"select distinct top 200  account_name from builder_account"))
    {
        serverSocket->Send("cd", CacheToServerPacket_ReplyBuilderAccountListPacket, 0);

        unguard();
        return false;
    }

    while (entryCount <= 200 && sql.Fetch())
    {
        int assembledSize = PacketUtils::Assemble(packetBuffer + allAssembledBytesCount, BUFFER_SIZE - allAssembledBytesCount, "s", builderAccountName);
        if (assembledSize > 0)
        {
            ++entryCount;
            allAssembledBytesCount += assembledSize;
        }
    }

    serverSocket->Send("cdb", CacheToServerPacket_ReplyBuilderAccountListPacket, entryCount, allAssembledBytesCount, packetBuffer);

    unguard();
    return false;
}
}  // namespace serverHandlers
