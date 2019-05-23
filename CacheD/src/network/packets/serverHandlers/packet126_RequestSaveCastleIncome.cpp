#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet126_RequestSaveCastleIncome.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436390
bool packet126_RequestSaveCastleIncome(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet126_RequestSaveCastleIncome(CIOSocket *pSocket, const uint8_t *packet)");

    int cropIncome = 0;
    int isCastle = 0;
    uint32_t castleId = 0;
    int shopIncome = 0;
    int cropIncomeTemp = 0;
    PacketUtils::Disassemble(packet, "ddddd", &castleId, &cropIncome, &shopIncome, &cropIncomeTemp, &isCastle);

    DBConn sql;
    sql.Execute(L"EXEC lin_SaveCastleIncome %d, %d, %d, %d, %d", cropIncome, shopIncome, castleId, cropIncomeTemp, isCastle);
    g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,%d,%d,,,,,,,,,,,", LogId_SaveCastleIncome, castleId, cropIncome, shopIncome, cropIncomeTemp);

    unguard();
    return false;
}
}  // namespace serverHandlers
