#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet087_RequestLogCharInfo.h"

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
// L2CacheD 0x004470C0
bool packet087_RequestLogCharInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet087_RequestLogCharInfo(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t userId = 0;
    PacketUtils::Disassemble(packet, "d", &userId);
    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%u,%u,%u,%u,%d,%u,%u,%d,%s,%s,,,",
            LogId_SaveCharInfo,
            user->GetId(),
            user->GetAccountID(),
            user->GetX(),
            user->GetY(),
            user->GetZ(),
            (uint32_t)user->GetHP(),
            (uint32_t)user->GetMP(),
            user->GetSP(),
            user->GetExp(),
            user->GetLevel(),
            user->GetAlign(),
            user->GetPK(),
            user->GetDuel(),
            user->GetPKPardon(),
            user->GetClass(),
            user->GetCharName(),
            user->GetAccountName());
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
