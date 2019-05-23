#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet218_RequestLoadLastResidenceTax.h"

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
// L2CacheD 0x0043BF90
bool packet218_RequestLoadLastResidenceTax(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet218_RequestLoadLastResidenceTax(CIOSocket *pSocket, const uint8_t *packet)");

    int incomeUpdateMonth = 1;
    int incomeUpdateDay = 1;
    int taxChangeMonth = 1;
    int taxChangeDay = 1;
    int incomeUpdateYear = 100;
    int taxChangeYear = 100;
    int incomeUpdateHour = 0;
    int incomeUpdateMinute = 0;
    int incomeUpdateSecond = 0;
    int taxChangeHour = 0;
    int taxChangeMinute = 0;
    int taxChangeSecond = 0;

    DBConn sql;
    sql.Bind(&incomeUpdateYear);
    sql.Bind(&incomeUpdateMonth);
    sql.Bind(&incomeUpdateDay);
    sql.Bind(&incomeUpdateHour);
    sql.Bind(&incomeUpdateMinute);
    sql.Bind(&incomeUpdateSecond);
    sql.Bind(&taxChangeYear);
    sql.Bind(&taxChangeMonth);
    sql.Bind(&taxChangeDay);
    sql.Bind(&taxChangeHour);
    sql.Bind(&taxChangeMinute);
    sql.Bind(&taxChangeSecond);

    time_t taxChange = 0;
    tm taxChangeTime = {0};

    time_t incomeUpdate = 0;
    tm incomeUpdateTime = {0};

    if (sql.Execute(L"EXEC lin_LoadLastTaxUpdate") && sql.Fetch())
    {
        incomeUpdateTime.tm_year = incomeUpdateYear - 1900;
        incomeUpdateTime.tm_hour = incomeUpdateHour;
        incomeUpdateTime.tm_mon = incomeUpdateMonth;
        incomeUpdateTime.tm_mday = incomeUpdateDay;
        incomeUpdateTime.tm_min = incomeUpdateMinute;
        incomeUpdateTime.tm_sec = incomeUpdateSecond;
        incomeUpdateTime.tm_isdst = 0;

        incomeUpdate = ::mktime(&incomeUpdateTime);

        taxChangeTime.tm_year = taxChangeYear - 1900;
        taxChangeTime.tm_mon = taxChangeMonth;
        taxChangeTime.tm_mday = taxChangeDay;
        taxChangeTime.tm_hour = taxChangeHour;
        taxChangeTime.tm_min = taxChangeMinute;
        taxChangeTime.tm_sec = taxChangeSecond;
        taxChangeTime.tm_isdst = 0;

        taxChange = ::mktime(&taxChangeTime);
    }
    else
    {
        taxChangeTime.tm_year = incomeUpdateYear;
        taxChangeTime.tm_hour = incomeUpdateHour;
        taxChangeTime.tm_mon = incomeUpdateMonth;
        taxChangeTime.tm_mday = incomeUpdateDay;
        taxChangeTime.tm_min = incomeUpdateMinute;
        taxChangeTime.tm_sec = incomeUpdateSecond;

        incomeUpdate = ::mktime(&taxChangeTime);

        incomeUpdateTime.tm_year = taxChangeYear;
        incomeUpdateTime.tm_mon = taxChangeMonth;
        incomeUpdateTime.tm_mday = taxChangeDay;
        incomeUpdateTime.tm_hour = taxChangeHour;
        incomeUpdateTime.tm_min = taxChangeMinute;
        incomeUpdateTime.tm_sec = taxChangeSecond;

        taxChange = ::mktime(&incomeUpdateTime);
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdd", CacheToServerPacket_ReplyLoadLastChangeResidence, incomeUpdate, taxChange);

    unguard();
    return false;
}
}  // namespace serverHandlers
