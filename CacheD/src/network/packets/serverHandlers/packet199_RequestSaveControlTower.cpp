#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet199_RequestSaveControlTower.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x00436A30
bool packet199_RequestSaveControlTower(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet199_RequestSaveControlTower(CIOSocket *pSocket, const uint8_t *packet)");

    int towerLevel = 0;
    int hp = 0;
    int status = 0;
    wchar_t towerName[128] = {0};
    PacketUtils::Disassemble(packet, "Sddd", sizeof(towerName), towerName, &towerLevel, &hp, &status);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_UpdateControlTower %d, %d, %d, '%s'", towerLevel, hp, status, towerName))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Execute lin_UpdateControlTower [%s]", towerName);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
