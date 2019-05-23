#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet065_GetPunishPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00445750
bool packet065_GetPunishPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet065_GetPunishPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "d", &characterId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    uint32_t punishId = 0;
    int punishOn = 0;
    int remainGame = 0;
    int remainReal = 0;
    SQLLEN indicator = -1;

    DBConn sql;
    sql.Bind(&punishId);
    sql.BindNullable(&punishOn, &indicator);
    sql.BindNullable(&remainGame, &indicator);
    sql.BindNullable(&remainReal, &indicator);

    if (!sql.Execute(L"EXEC lin_DeleteFriends %d", characterId))
    {
        serverSocket->Send("cdd", CacheToServerPacket_GetPunishPacket, characterId, 0);

        unguard();
        return false;
    }

    uint32_t packetSize = 0;
    uint32_t punishCount = 0;
    uint8_t buff[BUFFER_SIZE] = {0};
    while (sql.Fetch())
    {
        int punishValue = remainReal;
        if (punishOn != 0)
        {
            punishValue = remainGame;
        }
        int assembledBytes = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "ddd", punishId, punishOn, punishValue);
        if (assembledBytes)
        {
            packetSize += packetSize;
            ++punishCount;
        }

        punishOn = 0;
        remainGame = 0;
        remainReal = 0;
    }

    serverSocket->Send("cddb", CacheToServerPacket_GetPunishPacket, characterId, punishCount, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
