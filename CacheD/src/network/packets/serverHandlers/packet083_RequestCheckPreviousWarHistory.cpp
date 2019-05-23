#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet083_RequestCheckPreviousWarHistory.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004386B0
bool packet083_RequestCheckPreviousWarHistory(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet083_RequestCheckPreviousWarHistory(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int unknownParam4 = 0;
    uint32_t challenger = 0;
    uint32_t challengee = 0;
    int unknownParam5 = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &unknownParam4, &challenger, &challengee, &unknownParam5);

    uint32_t warId = 0;
    uint32_t challengerFromDb = 0;
    uint32_t challengeeFromDb = 0;
    int status = 0;
    int beginTime = 0;

    DBConn sql;
    sql.Bind(&warId);
    sql.Bind(&challengerFromDb);
    sql.Bind(&challengeeFromDb);
    sql.Bind(&status);
    sql.Bind(&beginTime);
    if (!sql.Execute(L"EXEC lin_CheckPreviousWarHistory %d, %d, %d, %d", challenger, challengee, challenger, challengee))
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_ReplyCheckPreviousWarHistory, unknownParam1, unknownParam2, unknownParam3, unknownParam4, unknownParam5, 0);

        unguard();
        return false;
    }

    sql.Fetch();

    serverSocket->Send("cdddddddddd", CacheToServerPacket_ReplyCheckPreviousWarHistory, unknownParam1, unknownParam2, unknownParam3, unknownParam4, unknownParam5, warId, challenger, challengee, status, beginTime);

    unguard();
    return false;
}
}  // namespace serverHandlers
