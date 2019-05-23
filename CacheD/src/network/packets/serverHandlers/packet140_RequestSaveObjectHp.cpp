#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet140_RequestSaveObjectHp.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004366F0
bool packet140_RequestSaveObjectHp(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet140_RequestSaveObjectHp(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t chatacterId = 0;
    int hp;
    PacketUtils::Disassemble(packet, "dd", &chatacterId, &hp);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SaveObjectHp %d, %d", hp, chatacterId))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Save Object[%d] Hp[%d]", chatacterId, hp);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
