#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet219_RequestSetLastResidenceTaxUpdate.h"

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
// L2CacheD 0x00437150
bool packet219_RequestSetLastResidenceTaxUpdate(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet219_RequestSetLastResidenceTaxUpdate(CIOSocket *pSocket, const uint8_t *packet)");

    time_t incomeTime = 0;
    time_t taxTime = 0;
    PacketUtils::Disassemble(packet, "dd", &incomeTime, &taxTime);

    tm* incodeLocalTime = std::localtime(&incomeTime);
    tm* taxLocalTime = std::localtime(&taxTime);

    DBConn sql;
    bool result = sql.Execute(
        L"EXEC lin_SetLastTaxUpdate '%d-%d-%d %d:%d:%d', '%d-%d-%d %d:%d:%d'",  // FIXME! SQL erros. There is fix inside SQL from smeli. Probably code should be fixed
        incodeLocalTime->tm_year + 1900,
        incodeLocalTime->tm_mon,
        incodeLocalTime->tm_mday,
        incodeLocalTime->tm_hour,
        incodeLocalTime->tm_min,
        incodeLocalTime->tm_sec,
        taxLocalTime->tm_year + 1900,
        taxLocalTime->tm_mon,
        taxLocalTime->tm_mday,
        taxLocalTime->tm_hour,
        taxLocalTime->tm_min,
        taxLocalTime->tm_sec);

    if (!result)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] cannot update last tax change date.", TEXT(__FILE__), __LINE__);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
