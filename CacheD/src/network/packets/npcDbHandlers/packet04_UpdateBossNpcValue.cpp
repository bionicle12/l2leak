#include <WinSock2.h>

#include "cached/network/packets/npcDbHandlers/packet04_UpdateBossNpcValue.h"

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
// L2CacheD 0x00427A40
bool packet04_UpdateBossNpcValue(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool npcDbHandlers::packet04_UpdateBossNpcValue(CIOSocket *pSocket, const uint8_t *packet)");

    int i0 = 0;
    wchar_t npcName[128] = {0};
    PacketUtils::Disassemble(packet, "Sd", sizeof(npcName), npcName, &i0);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_UpdateNpcBossVariable N'%s', %d", npcName, i0))
    {
        g_winlog.Add(LOG_ERROR, L"UpdateBossNpcValue failed");
    }

    unguard();
    return false;
}
}  // namespace npcDbHandlers
