#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet175_RequestIncreaseUserDuelCount.h"

#include "cached/model/CUserDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x00450B80
bool packet175_RequestIncreaseUserDuelCount(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet175_RequestIncreaseUserDuelCount(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t userId = 0;
    PacketUtils::Disassemble(packet, "d", &userId);
    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        user->IncreaseDuelCount();
        user->Save();
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestIncreaseUserDuelCount failed. invalid user[%d]", TEXT(__FILE__), __LINE__, userId);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
