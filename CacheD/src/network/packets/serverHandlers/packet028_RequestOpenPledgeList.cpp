#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet028_RequestOpenPledgeList.h"

#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435310
bool packet028_RequestOpenPledgeList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet028_RequestOpenPledgeList(CIOSocket *pSocket, const uint8_t *packet)");

    g_winlog.Add(LOG_ERROR, L"RequestOpenPledgeList is coming from the main server");

    unguard();
    return false;
}
}  // namespace serverHandlers
