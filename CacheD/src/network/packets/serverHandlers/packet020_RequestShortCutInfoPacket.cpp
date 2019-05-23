#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet020_RequestShortCutInfoPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00437CA0
bool packet020_RequestShortCutInfoPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet020_RequestShortCutInfoPacket(CIOSocket *pSocket, const uint8_t *packet)");

    int32_t unknownParam1 = 0;
    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "dd", &unknownParam1, &characterId);

    int32_t shortcutSlotNumber = 0;
    int32_t shortcutType = 0;
    uint32_t shortcutId = 0;
    wchar_t shortcutMacro[514] = {0};

    DBConn sql;
    sql.Bind(&shortcutSlotNumber);
    sql.Bind(&shortcutType);
    sql.Bind(&shortcutId);
    sql.Bind(shortcutMacro, sizeof(shortcutMacro));

    sql.Execute(L"EXEC lin_GetShortCut %d", characterId);

    uint32_t packetSize = 0;
    uint8_t buff[BUFFER_SIZE];
    uint32_t shortcutCount = 0;
    while (sql.Fetch())
    {
        int32_t assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "ddddS", shortcutSlotNumber, shortcutType & 0xffff, shortcutId, shortcutType >> 16, shortcutMacro);
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++shortcutCount;
        }
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cddb", CacheToServerPacket_ShortCutInfoPacket, unknownParam1, shortcutCount, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
