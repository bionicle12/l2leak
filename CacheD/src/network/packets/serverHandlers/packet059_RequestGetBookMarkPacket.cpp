#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet059_RequestGetBookMarkPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439E30
bool packet059_RequestGetBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet059_RequestGetBookMarkPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    if (unknownParam1 <= 0)
    {
        unguard();
        return false;
    }

    wchar_t bookmarkList[1024] = {0};
    wchar_t bookmarkName[52] = {0};

    DBConn sql;
    sql.Bind(bookmarkName, 50);
    if (!sql.Execute(L"EXEC lin_GetListBookMark %d", characterId))
    {
        serverSocket->Send("cdS", CacheToServerPacket_GetBookMarkPacket, unknownParam1, bookmarkList);

        unguard();
        return false;
    }

    while (sql.Fetch())
    {
        if ((::wcslen(bookmarkName) + ::wcslen(bookmarkList) + 10) >= 1024)
        {
            break;
        }

        ::wcscat(bookmarkList, L",");
        ::wcscat(bookmarkList, bookmarkName);

        ::memset(bookmarkName, 0, sizeof(bookmarkName));
    }

    serverSocket->Send("cdS", CacheToServerPacket_GetBookMarkPacket, unknownParam1, bookmarkList);

    unguard();
    return false;
}
}  // namespace serverHandlers
