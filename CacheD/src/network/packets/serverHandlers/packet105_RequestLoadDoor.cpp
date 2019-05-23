#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet105_RequestLoadDoor.h"

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
// L2CacheD 0x0043A560
bool packet105_RequestLoadDoor(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet105_RequestLoadDoor(CIOSocket *pSocket, const uint8_t *packet)");

    int defaultHp = 0;
    wchar_t doorName[50] = {0};
    PacketUtils::Disassemble(packet, "Sd", sizeof(doorName), doorName, &defaultHp);

    int hp = 0;
    int maxHp = 0;

    DBConn sql;
    sql.Bind(&hp);
    sql.Bind(&maxHp);
    if (!sql.Execute(L"EXEC lin_LoadDoor N'%s'", doorName) || !sql.Fetch())
    {
        sql.ResetHtmt();
        if (!sql.Execute(L"EXEC lin_CreateDoorDataIfNotExist N'%s', %d", doorName, defaultHp))
        {
            g_winlog.Add(LOG_ERROR, L"Cannot Create Door into DB (%s, %d)", doorName, defaultHp);
        }
        maxHp = defaultHp;
        hp = defaultHp;
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cSdd", CacheToServerPacket_ReplyLoadDoor, doorName, hp, maxHp);

    unguard();
    return false;
}
}  // namespace serverHandlers
