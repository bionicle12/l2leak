#include <WinSock2.h>

#include "cached/network/packets/npcDbHandlers/packet03_SaveNpcInfo.h"

#include "cached/network/CNpcDbSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace npcDbHandlers
{

// L2CacheD 0x00427890
bool packet03_SaveNpcInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool npcDbHandlers::packet03_SaveNpcInfo(CIOSocket *pSocket, const uint8_t *packet)");

    bool alive = false;
    wchar_t npcName[128] = {0};
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "Sc", sizeof(npcName), npcName, &alive);

    int timeHigh = 0;
    int timeLow = 0;
    int locZ = 0;
    int locY = 0;
    int locX = 0;
    int mp = 0;
    int hp = 0;

    if (alive)
    {
        PacketUtils::Disassemble(restOfPacket, "ddddd", &hp, &mp, &locX, &locY, &locZ);
    }
    else
    {
        PacketUtils::Disassemble(restOfPacket, "dd", &timeLow, &timeHigh);
    }

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SaveNpcBoss N'%s',%d,%d,%d,%d,%d,%d,%d,%d", npcName, alive, hp, mp, locX, locY, locZ, timeLow, timeHigh))
    {
        g_winlog.Add(LOG_ERROR, "Save NpcBoss failed!");
    }

    unguard();
    return false;
}

}  // namespace npcDbHandlers
