#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet090_RequestManageBattleCamp.h"

#include "cached/model/BattleCampOperations.h"
#include "cached/model/CBattleCampDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00459F80
bool packet090_RequestManageBattleCamp(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet090_RequestManageBattleCamp(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int operationType = 0;
    const uint8_t* restOfThePacket = PacketUtils::Disassemble(packet, "d", &operationType);
    if (operationType == BattleCampOperation_Install)
    {
        uint32_t pledgeId = 0;
        uint32_t castleId = 0;
        int maxHp = 0;
        int locX = 0;
        int locY = 0;
        int locZ = 0;
        PacketUtils::Disassemble(restOfThePacket, "dddddd", &pledgeId, &castleId, &maxHp, &locX, &locY, &locZ);
        uint32_t battleCampId = g_battleCampDb.InstallBattleCamp(castleId, pledgeId, maxHp, locX, locY, locZ);

        if (battleCampId == 0)
        {
            serverSocket->Send("cdddddddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, battleCampId, pledgeId, castleId, maxHp, locX, locY, locZ);

            unguard();
            return false;
        }

        CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
        if (pledge == NULL)
        {
            serverSocket->Send("cdddddddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, battleCampId, pledgeId, castleId, maxHp, locX, locY, locZ);

            unguard();
            return false;
        }

        CUserSP character = g_userDb.GetUser(pledge->rullerId(), true);
        if (character == NULL)
        {
            serverSocket->Send("cdddddddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, battleCampId, pledgeId, castleId, maxHp, locX, locY, locZ);

            unguard();
            return false;
        }

        wchar_t pledgeName[25] = {0};
        ::wcscpy(pledgeName, pledge->name());

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%u,%u,%u,%d,%d,%d,%s,%s,,,",
            LogId_InstallBattleCamp,
            character->GetId(),
            character->GetAccountID(),
            character->GetX(),
            character->GetY(),
            character->GetZ(),
            pledgeName,
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            character->GetLevel(),
            pledge->id(),
            battleCampId,
            maxHp,
            locX,
            locY,
            locZ,
            character->GetCharName(),
            character->GetAccountName());

        serverSocket->Send("cdddddddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, battleCampId, pledgeId, castleId, maxHp, locX, locY, locZ);
    }
    else if (operationType == BattleCampOperation_Uninstall)
    {
        uint32_t pledgeId = 0;
        PacketUtils::Disassemble(restOfThePacket, "d", &pledgeId);
        uint32_t deletedBattleCampId = g_battleCampDb.UninstallBattleCamp(pledgeId);

        CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
        if (pledge != NULL)
        {
            serverSocket->Send("cddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, pledgeId, deletedBattleCampId);

            unguard();
            return false;
        }

        CUserSP character = g_userDb.GetUser(pledge->rullerId(), true);
        if (character != NULL)
        {
            serverSocket->Send("cddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, pledgeId, deletedBattleCampId);

            unguard();
            return false;
        }
        wchar_t pledgeName[25] = {0};
        ::wcscpy(pledgeName, pledge->name());

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%u,,,,,,%s,%s,,,",
            LogId_UninstallBattleCamp,
            character->GetId(),
            character->GetAccountID(),
            character->GetX(),
            character->GetY(),
            character->GetZ(),
            pledgeName,
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            character->GetLevel(),
            pledgeId,
            character->GetCharName(),
            character->GetAccountName());

        serverSocket->Send("cddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, pledgeId, deletedBattleCampId);
    }
    else if (operationType == BattleCampOperation_UninstallAll)
    {
        uint32_t castleId = 0;
        PacketUtils::Disassemble(restOfThePacket, "d", &castleId);

        std::vector<uint32_t> uninstallBattleCamp;
        g_battleCampDb.UninstallAllBattleCamp(castleId, &uninstallBattleCamp);
        if (uninstallBattleCamp.empty())
        {
            serverSocket->Send("cddd", CacheToServerPacket_ReplyManageBattleCamp, operationType, castleId, 0);

            unguard();
            return false;
        }

        uint32_t battleCampCount = 0;
        uint32_t buffSize = 0;
        uint8_t buff[BUFFER_SIZE];
        for (std::vector<uint32_t>::const_iterator it = uninstallBattleCamp.begin(); it != uninstallBattleCamp.end(); ++it)
        {
            buffSize += PacketUtils::Assemble(&buff[buffSize], BUFFER_SIZE - buffSize, "d", *it);

            g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,,,,,,,,,,,,,", LogId_UninstallAllBattleCamp, castleId, *it);
        }

        serverSocket->Send("cdddb", CacheToServerPacket_ReplyManageBattleCamp, operationType, castleId, battleCampCount, buffSize, buff);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
