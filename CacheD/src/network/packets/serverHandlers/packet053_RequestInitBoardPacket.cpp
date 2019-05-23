#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet053_RequestInitBoardPacket.h"

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

// L2CacheD 0x00439510
bool packet053_RequestInitBoardPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet053_RequestInitBoardPacket(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam2 = 0;
    int unkParam1 = 0;
    int unkParam3 = 0;
    PacketUtils::Disassemble(packet, "ddd", &unkParam1, &unkParam2, &unkParam3);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    if (unkParam1 == 0)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_InitBoardPacket, unkParam1, 0, 0, 0);
        unguard();
        return false;
    }

    uint32_t boardId = 0;
    wchar_t boardName[20] = {0};
    wchar_t boardDescription[20] = {0};
    int boardOrder = 0;

    DBConn sql;
    sql.Bind(&boardId);
    sql.Bind(boardName, 40);
    sql.Bind(boardDescription, 40);
    sql.Bind(&boardOrder);

    if (!sql.Execute(L"EXEC lin_GetInitBoard", unkParam3, 6))
    {
        serverSocket->Send("cdddd", CacheToServerPacket_InitBoardPacket, unkParam1, 0, 0, 0);
        unguard();
        return false;
    }

    uint8_t buff[BUFFER_SIZE];

    int packetSize = 0;
    int itemCount = 0;
    while (sql.Fetch())
    {
        ++itemCount;
        int assembleSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dSSd", boardId, boardName, boardDescription, boardOrder);
        if (assembleSize > 0)
        {
            packetSize += assembleSize;
        }

        boardId = 0;
        ::memset(boardName, 0, sizeof(boardName));
        ::memset(boardDescription, 0, sizeof(boardDescription));
        boardOrder = 0;
    }

    serverSocket->Send("cddddb", CacheToServerPacket_InitBoardPacket, unkParam1, unkParam2, unkParam3, itemCount, packetSize, buff);

    unguard();
    return false;
}

}  // namespace serverHandlers
