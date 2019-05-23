#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet001_LoadCharacterPacket.h"
#include "cached/network/packets/serverHandlers/packet073_RequestRestoreCharacter.h"

#include "cached/model/CUserDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0045A5B0
bool packet073_RequestRestoreCharacter(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet073_RequestRestoreCharacter(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterIdToDelete = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &characterIdToDelete);
    CUserSP characterToDelete = g_userDb.GetUser(characterIdToDelete, true);
    if (characterToDelete == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char id[%d]", TEXT(__FILE__), __LINE__, characterIdToDelete);

        unguard();
        return false;
    }

    characterToDelete->RestoreDeleted();
    serverHandlers::packet001_LoadCharacterPacket(pSocket, restOfPacket);

    unguard();
    return false;
}
}  // namespace serverHandlers
