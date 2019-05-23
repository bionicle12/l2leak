#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet029_RequestCharacterLogin.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004411C0
bool packet029_RequestCharacterLogin(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet029_RequestCharacterLogin(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "d", &characterId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    character->WriteLogin(characterId);

    unguard();
    return false;
}
}  // namespace serverHandlers
