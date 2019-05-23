#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet129_RequestInstallAgitDeco.h"

#include "cached/model/AgitDecors.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x004382B0
bool packet129_RequestInstallAgitDeco(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet129_RequestInstallAgitDeco(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t agitId = 0;
    AgitDecors decor = AgitDecor_Stove;
    int param1 = 0;
    int param2 = 0;
    PacketUtils::Disassemble(packet, "dddd", &agitId, &decor, &param1, &param2);

    bool success = false;
    DBConn sql;
    switch (decor)
    {
        case AgitDecor_Stove:
            success = sql.Execute(L"UPDATE agit SET hp_stove = %d, hp_stove_expire = %d WHERE id = %d", param1, param2, agitId);
            break;
        case AgitDecor_Flame:
            success = sql.Execute(L"UPDATE agit SET mp_flame = %d, mp_flame_expire = %d WHERE id = %d", param1, param2, agitId);
            break;
        case AgitDecor_Hatch:
            success = sql.Execute(L"UPDATE agit SET hatcher = %d WHERE id = %d", param1, agitId);
            break;
        case AgitDecor_Teleport:
            success = sql.Execute(L"UPDATE agit SET teleport_level = %d WHERE id = %d", param1, agitId);
            break;
        default:
            success = false;
            break;
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    if (success)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyInstallAgitDeco, agitId, decor, param1, param2);
        g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,%d,%d,,,,,,,,,,,", LogId_InstallAgitDeco, agitId, decor, param1, param2);
    }
    else
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyInstallAgitDeco, 0, 0, 0, 0);
        g_winlog.Add(LOG_ERROR, L"Cannot Install Agit[%d] Deco(type:%d value:%d expire:%d)", agitId, decor, param1, param2);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
