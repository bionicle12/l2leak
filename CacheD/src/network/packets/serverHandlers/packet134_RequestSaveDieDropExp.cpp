#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet134_RequestSaveDieDropExp.h"

#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044C0B0
bool packet134_RequestSaveDieDropExp(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet134_RequestSaveDieDropExp(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int dropExp = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &dropExp);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    character->SetDropExp(dropExp);

    DBConn sql;
    sql.Execute(L"EXEC lin_SaveDropExp %d, %d", dropExp, characterId);

    unguard();
    return false;
}
}  // namespace serverHandlers
