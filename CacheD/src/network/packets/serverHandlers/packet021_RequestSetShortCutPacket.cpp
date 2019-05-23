#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet021_RequestSetShortCutPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435390
bool packet021_RequestSetShortCutPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet021_RequestSetShortCutPacket(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int32_t shortcutSlotNumber = 0;
    int32_t shortcutType = 0;
    uint32_t shortcutId = 0;
    int32_t unknownParam1 = 0;
    wchar_t shortcutMacro[512] = {0};
    PacketUtils::Disassemble(packet, "dddddS", &characterId, &shortcutSlotNumber, &shortcutType, &shortcutId, &unknownParam1, sizeof(shortcutMacro), shortcutMacro);

    DBConn sql;
    shortcutType |= unknownParam1 << 16;
    if (!sql.Execute(L"EXEC lin_SetShortCut %d, %d, %d, %d, N'%s'", characterId, shortcutSlotNumber, shortcutType, shortcutId, shortcutMacro))
    {
        DBConn sql2;
        sql2.Execute(L"EXEC lin_SetShortCut %d, %d, %d, %d, N'%s'", characterId, shortcutSlotNumber, shortcutType, shortcutId, shortcutMacro);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
