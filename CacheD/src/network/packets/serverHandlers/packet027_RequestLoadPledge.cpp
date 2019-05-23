#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet027_RequestLoadPledge.h"

#include "cached/model/CPledgeDb.h"
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
// L2CacheD 0x00457990
bool packet027_RequestLoadPledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet027_RequestLoadPledge(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "d", &pledgeId);

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);

    if (pledge == NULL)
    {
        g_winlog.Add(LOG_REQUEST, L"RP_LOAD_PLEDGE[%d], cannot load pledge.", pledgeId);
        unguard();
        return false;
    }

    wchar_t pledgeName[24] = {0};
    ::wcscpy(pledgeName, pledge->name());

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    pledge->SendReplyToLoadPledge(serverSocket);

    g_winlog.Add(LOG_REQUEST, L"RP_LOAD_PLEDGE[%s][%d]", pledgeName, pledgeId);

    unguard();
    return false;
}
}  // namespace serverHandlers
