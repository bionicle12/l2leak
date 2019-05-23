#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet107_RequestSaveDoorStatus.h"

#include "cached/model/CCastleDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436230
bool packet107_RequestSaveDoorStatus(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet107_RequestSaveDoorStatus(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t name[50] = {0};
    int hp = 0;
    int maxHp = 0;
    PacketUtils::Disassemble(packet, "Sdd", sizeof(name), name, &hp, &maxHp);

    DBConn sql;
    if (sql.Execute(L"EXEC lin_SaveDoorStatus %d, %d, N'%s'", hp, maxHp, name))
    {
        g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,,,,,,,,,,,,,,", LogId_DoorHpChanged, name, hp);
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Saving Door Status");
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
