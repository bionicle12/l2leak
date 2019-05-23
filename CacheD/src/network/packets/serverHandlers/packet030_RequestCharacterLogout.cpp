#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet030_RequestCharacterLogout.h"

#include "cached/model/CAccount.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004412C0
bool packet030_RequestCharacterLogout(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet030_RequestCharacterLogout(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int32_t unknownParam1 = 0;
    int32_t weekPlayTime = 0;
    SYSTEMTIME lastSaveTime = {0};
    PacketUtils::Disassemble(packet, "dddb", &characterId, &unknownParam1, &weekPlayTime, sizeof(SYSTEMTIME), &lastSaveTime);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d][%d]", TEXT(__FILE__), __LINE__, characterId, unknownParam1);

        unguard();
        return false;
    }

    character->WriteLogout(characterId, unknownParam1);
    CAccountSP account = CAccount::Load(character->GetAccountID());
    if (account == NULL)
    {
        unguard();
        return false;
    }

    account->SaveWeekPlayTime(weekPlayTime, &lastSaveTime);

    unguard();
    return false;
}
}  // namespace serverHandlers
