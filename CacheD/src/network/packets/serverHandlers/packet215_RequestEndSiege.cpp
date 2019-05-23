#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet215_RequestEndSiege.h"

#include "cached/model/CAllianceDb.h"
#include "cached/model/CPledgeDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0045A9A0
bool packet215_RequestEndSiege(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet215_RequestEndSiege(CIOSocket *pSocket, const uint8_t *packet)");

    int unknownParam1 = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dd", &unknownParam1, &pledgeId);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeleteMasterRelatedCastleWar %d", pledgeId))
    {
        g_winlog.Add(LOG_ERROR, L"cannot delete winner[%d] related castle war", pledgeId);
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        unguard();
        return false;
    }

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,,,,,,,,,,,,", LogId_WinSiege, &pledgeName, unknownParam1, pledge->id(), pledge->allianceId());

    CAllianceSP alliance = g_allianceDb.GetAlliance(pledge->allianceId());
    if (alliance == NULL)
    {
        unguard();
        return false;
    }

    PledgeIdList pledgeIdList;
    alliance->GetAllMemberPledgeId(pledgeIdList);

    for (PledgeIdList::const_iterator it = pledgeIdList.begin(); it != pledgeIdList.end(); ++it)
    {
        uint32_t pledgeIdInAlliance = *it;
        CPledgeSP pledgeInAlliance = g_pledgeDb.GetPledge(pledgeIdInAlliance);
        if (pledgeInAlliance == NULL)
        {
            continue;
        }

        ::memset(pledgeName, 0, sizeof(pledgeName));
        ::wcscpy(pledgeName, pledge->name());

        g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,,,,,,,,,,,,", LogId_WinSiegeAlliance, &pledgeName, unknownParam1, pledge, pledge->allianceId());
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
