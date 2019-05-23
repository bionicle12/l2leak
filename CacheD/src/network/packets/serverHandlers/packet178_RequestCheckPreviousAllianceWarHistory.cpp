#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet178_RequestCheckPreviousAllianceWarHistory.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043AA00
bool packet178_RequestCheckPreviousAllianceWarHistory(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet178_RequestCheckPreviousAllianceWarHistory(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t challengerAllianceId = 0;
    uint32_t challengeeAllianceId = 0;
    int unknownParam3 = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unknownParam1, &unknownParam2, &challengerAllianceId, &challengeeAllianceId, &unknownParam3);

    uint32_t allianceWarId = 0;
    uint32_t challengerAllianceIdFromDb = 0;
    uint32_t challengeeAllianceIdFromDb = 0;
    uint32_t status = 0;
    uint32_t beginTime = 0;

    DBConn sql;
    sql.Bind(&allianceWarId);
    sql.Bind(&challengerAllianceIdFromDb);
    sql.Bind(&challengeeAllianceIdFromDb);
    sql.Bind(&status);
    sql.Bind(&beginTime);

    if (!sql.Execute(L"EXEC lin_CheckPreviousAllianceWarHistory %d, %d", challengerAllianceId, challengeeAllianceId))
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCheckPreviousAllianceWarHistory, unknownParam1, unknownParam2, unknownParam3, 0);

        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCheckPreviousAllianceWarHistory, unknownParam1, unknownParam2, unknownParam3, 0);

        unguard();
        return false;
    }

    if (allianceWarId == 0)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCheckPreviousAllianceWarHistory, unknownParam1, unknownParam2, unknownParam3, 0);

        unguard();
        return false;
    }

    serverSocket->Send("cdddddddd", CacheToServerPacket_ReplyCheckPreviousAllianceWarHistory, unknownParam1, unknownParam2, unknownParam3, allianceWarId, challengerAllianceIdFromDb, challengeeAllianceIdFromDb, status, beginTime);

    unguard();
    return false;
}
}  // namespace serverHandlers
