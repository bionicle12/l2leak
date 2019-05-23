#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet198_RequestLoadControlTower.h"

#include "cached/model/CCastleDb.h"
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
// L2CacheD 0x0043B460
bool packet198_RequestLoadControlTower(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet198_RequestLoadControlTower(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t name[128] = {0};
    uint32_t defaultResidenceId = 0;
    int defaultControlLevel = 0;
    int defaultHp = 0;
    int defaultStatus = 0;
    PacketUtils::Disassemble(packet, "Sdddd", sizeof(name), name, &defaultResidenceId, &defaultControlLevel, &defaultHp, &defaultStatus);

    uint32_t residenceId = 0;
    int controlLevel = 0;
    int hp = 0;
    int status = 0;

    DBConn sql;
    sql.Bind(&residenceId);
    sql.Bind(&controlLevel);
    sql.Bind(&hp);
    sql.Bind(&status);
    if (!sql.Execute(L"EXEC lin_LoadControlTowerByName '%s'", name) || !sql.Fetch())
    {
        sql.ResetHtmt();
        if (!sql.Execute(L"EXEC lin_InsertIntoControlTower '%s', %d, %d, %d, %d", name, defaultResidenceId, defaultControlLevel, defaultHp, defaultStatus))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in Execute lin_InsertIntoControlTower [%s]", name);
        }

        residenceId = defaultResidenceId;
        controlLevel = defaultControlLevel;
        hp = defaultHp;
        status = defaultStatus;
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cSdddd", CacheToServerPacket_ReplyLoadControlTower, name, residenceId, controlLevel, hp, status);

    unguard();
    return false;
}
}  // namespace serverHandlers
