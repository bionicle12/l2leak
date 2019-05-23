#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet091_RequestLoadBattleCamp.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00438C80
bool packet091_RequestLoadBattleCamp(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet091_RequestLoadBattleCamp(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);

    uint32_t battleCampId = 0;
    uint32_t ownerId = 0;
    uint32_t residenceIdFromDb = 0;
    int maxHP = 0;
    int hp = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;

    DBConn sql;
    sql.Bind(&battleCampId);
    sql.Bind(&ownerId);
    sql.Bind(&residenceIdFromDb);
    sql.Bind(&maxHP);
    sql.Bind(&hp);
    sql.Bind(&locX);
    sql.Bind(&locY);
    sql.Bind(&locZ);

    bool isSuccess = false;
    if (residenceId > 0)
    {
        isSuccess = sql.Execute(L"SELECT id, owner_id, residence_id, max_hp, hp, x_pos, y_pos, z_pos FROM object_data WHERE residence_id = %d AND type = %d", residenceId, 0);
    }
    else
    {
        isSuccess = sql.Execute(L"SELECT id, owner_id, residence_id, max_hp, hp, x_pos, y_pos, z_pos FROM object_data WHERE type = %d", 0);
    }

    if (!isSuccess)
    {
        unguard();
        return false;
    }

    uint32_t battleCampCount = 0;
    uint32_t buffSize = 0;
    uint8_t buff[BUFFER_SIZE];
    while (sql.Fetch())
    {
        buffSize += PacketUtils::Assemble(&buff[buffSize], BUFFER_SIZE - buffSize, "dddddddd", battleCampId, ownerId, residenceIdFromDb, maxHP, hp, locX, locY, locZ);
        ++battleCampCount;

        if (battleCampCount == 250)
        {
            break;
        }
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdb", CacheToServerPacket_ReplyLoadBattleCamp, battleCampCount, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
