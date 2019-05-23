#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet034_RequestLoadAllCastleData.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435520
bool packet034_RequestLoadAllCastleData(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet034_RequestLoadAllCastleData(CIOSocket *pSocket, const uint8_t *packet)");

    int castleCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &castleCount);
    for (int i = 0; i < castleCount; ++i)
    {

        uint32_t castleId = 0;
        wchar_t castleName[256] = {0};
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dS", &castleId, sizeof(castleName), castleName);

        CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
        g_castleDb.SendReplyToLoadCastle(serverSocket, castleId, castleName);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
