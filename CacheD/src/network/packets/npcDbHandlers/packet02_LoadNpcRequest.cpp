#include <WinSock2.h>

#include "cached/network/packets/npcDbHandlers/packet02_LoadNpcRequest.h"

#include "cached/network/CNpcDbSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToNpcPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace npcDbHandlers
{
// L2CacheD 0x00428670
bool packet02_LoadNpcRequest(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool npcDbHandlers::packet02_LoadNpcRequest(CIOSocket *pSocket, const uint8_t *packet)");

    intptr_t spawnDefine = 0;  // x64_port
    wchar_t npcName[128] = {0};
    PacketUtils::Disassemble(packet, "Sd", sizeof(npcName), npcName, &spawnDefine);

    CNpcDbSocket* npcSocket = static_cast<CNpcDbSocket*>(pSocket);

    int timeHigh = 0;
    int timeLow = 0;
    int locZ = 0;
    int locY = 0;
    int locX = 0;
    int mp = 0;
    int hp = 0;
    int alive = false;
    int i0 = 0;

    DBConn sql;
    sql.Bind(&alive);
    sql.Bind(&hp);
    sql.Bind(&mp);
    sql.Bind(&locX);
    sql.Bind(&locY);
    sql.Bind(&locZ);
    sql.Bind(&timeLow);
    sql.Bind(&timeHigh);
    sql.Bind(&i0);
    if (sql.Execute(L"EXEC lin_LoadNpcBoss N'%s'", npcName) && sql.Fetch())
    {
        if (alive)
        {
            npcSocket->Send("cSdcdddddd", CacheToNpcPacket_NpcSpawnResponse, npcName, spawnDefine, alive == 1 ? true : false, i0, hp, mp, locX, locY, locZ);
        }
        else
        {
            npcSocket->Send("cSdcdd", CacheToNpcPacket_NpcSpawnResponse, npcName, spawnDefine, false, timeLow, timeHigh);
        }
    }
    else
    {
        npcSocket->Send("cSdcdd", CacheToNpcPacket_NpcSpawnResponse, npcName, spawnDefine, false, 0, 0);
    }

    unguard();
    return false;
}
}  // namespace npcDbHandlers
