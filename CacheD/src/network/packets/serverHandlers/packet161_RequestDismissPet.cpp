#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet161_RequestDismissPet.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004505F0
bool packet161_RequestDismissPet(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet161_RequestDismissPet(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    uint32_t petId = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &petId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] RequestDismissPet failed. Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeletePet %d", petId))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestDismissPet failed", TEXT(__FILE__), __LINE__);

        unguard();
        return false;
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
        LogId_DismissPet,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        petId,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
