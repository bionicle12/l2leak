#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet085_RequestPetiSaveMsg.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436010
bool packet085_RequestPetiSaveMsg(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet085_RequestPetiSaveMsg(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    wchar_t message[501] = {0};
    PacketUtils::Disassemble(packet, "dS", &characterId, sizeof(message), message);

    DBConn sql;
    sql.Execute(L"EXEC lin_SetPetitionMsg %d, N'%s'", characterId, message);

    unguard();
    return false;
}
}  // namespace serverHandlers
