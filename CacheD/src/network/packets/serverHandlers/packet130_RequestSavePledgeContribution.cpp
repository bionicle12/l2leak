#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet130_RequestSavePledgeContribution.h"

#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00441B80
bool packet130_RequestSavePledgeContribution(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet130_RequestSavePledgeContribution(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t residenceId = 0;
    int unknownParam1 = 0;
    int contributionCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "ddd", &residenceId, &unknownParam1, &contributionCount);

    DBConn sql;
    for (int i = 0; i < contributionCount; ++i)
    {
        uint32_t pledgeId = 0;
        int contribution = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dd", &pledgeId, &contribution);
        if (!sql.Execute(L"UPDATE pledge_contribution SET contribution = contribution + %d WHERE pledge_id = %d AND residence_id = %d", contribution, pledgeId, residenceId))
        {
            g_winlog.Add(LOG_ERROR, L"Failed to Save Pledge Contribution PledgeId[%d], Contribute[%d], Residence[%d]", pledgeId, contribution, residenceId);
            continue;
        }

        if (sql.GetRowCount() <= 0)
        {
            g_winlog.Add(LOG_ERROR, L"Failed to Save Pledge Contribution PledgeId[%d], Contribute[%d], Residence[%d]", pledgeId, contribution, residenceId);
            continue;
        }

        if (!sql.Execute(L"INSERT INTO pledge_contribution (contribution, pledge_id, residence_id) VALUES (%d, %d, %d)", contribution, pledgeId, residenceId))
        {
            g_winlog.Add(LOG_ERROR, L"Failed to Save Pledge Contribution PledgeId[%d], Contribute[%d], Residence[%d]", pledgeId, contribution, residenceId);
            continue;
        }

        CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
        if (pledge == NULL)
        {
            continue;
        }

        wchar_t pledgeName[25] = {0};
        ::wcscpy(pledgeName, pledge->name());

        g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,%d,,,,,,,,,,,", LogId_SetPledgeContribution, pledgeName, residenceId, pledgeId, unknownParam1, contribution);
    }

    uint32_t winnerPledgeId = 0;
    sql.Bind(&winnerPledgeId);

    if (!sql.Execute(L"EXEC lin_GetContributionWinnerPledge %d, %d", residenceId, residenceId))
    {
        if (sql.Fetch())
        {
            CPledgeSP pledge = g_pledgeDb.GetPledge(winnerPledgeId);
            if (pledge != NULL)
            {
                wchar_t pledgeName[25] = {0};
                ::wcscpy(pledgeName, pledge->name());

                g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,,,,,,,,,,,,", LogId_SetWinnerPledgeContribution, pledgeName, residenceId, winnerPledgeId, unknownParam1);
            }
        }
        else
        {
            g_winlog.Add(LOG_INF, L"No Contribution Winner Exists[%d]", residenceId);
        }
    }
    else
    {
        g_winlog.Add(LOG_INF, L"Cannot Get Contribution Winner[%d]", residenceId);
    }

    serverSocket->Send("cddd", CacheToServerPacket_ReplyContributionWinnerPledge, residenceId, unknownParam1, winnerPledgeId);

    if (unknownParam1 <= 0)
    {
        unguard();
        return false;
    }

    sql.ResetHtmt();
    if (!sql.Execute(L"EXEC lin_DeletePledgeContribution %d", residenceId))
    {
        g_winlog.Add(LOG_ERROR, L"Failed to Delete Pledge Contribution[%d]", residenceId);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
