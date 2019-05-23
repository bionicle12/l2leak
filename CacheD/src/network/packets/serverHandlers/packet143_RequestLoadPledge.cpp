#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet143_RequestLoadPledge.h"

#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00457B10
bool packet143_RequestLoadPledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet143_RequestLoadPledge(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t pledgeName[24] = {0};
    PacketUtils::Disassemble(packet, "S", sizeof(pledgeName), pledgeName);

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeName);
    if (pledge == NULL)
    {
        g_winlog.Add(LOG_REQUEST, L"RP_LOAD_PLEDGE[%s], cannot load pledge.", pledgeName);

        unguard();
        return false;
    }

    ::wcscpy(pledgeName, pledge->name());

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    pledge->SendReplyToLoadPledge(serverSocket);

    g_winlog.Add(LOG_REQUEST, L"RP_LOAD_PLEDGE[%s][%d]", pledgeName, pledge->id());

    unguard();
    return false;
}
}  // namespace serverHandlers
