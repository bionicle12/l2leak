#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet066_ChangePosPacket.h"

#include "cached/model/CUserDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00445A00
bool packet066_ChangePosPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet066_ChangePosPacket(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t characterName[50] = {0};
    uint32_t worldId = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    PacketUtils::Disassemble(packet, "Sdddd", sizeof(characterName), characterName, &worldId, &x, &y, &z);

    wchar_t characterNameLowerCase[50] = {0};
    Utils::CopyStrInLowerCase(characterName, characterNameLowerCase);

    CUserSP character = g_userDb.GetUser(characterNameLowerCase);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", TEXT(__FILE__), __LINE__, characterNameLowerCase);

        unguard();
        return false;
    }

    character->ChangeLocationExtern(characterName, worldId, x, y, z, false);

    unguard();
    return false;
}
}  // namespace serverHandlers
