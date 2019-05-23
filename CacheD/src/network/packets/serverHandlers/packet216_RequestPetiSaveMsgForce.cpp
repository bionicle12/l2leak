#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet216_RequestPetiSaveMsgForce.h"

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

// L2CacheD 0x0043BE10
bool packet216_RequestPetiSaveMsgForce(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet216_RequestPetiSaveMsgForce(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t charName[50] = {0};
    int unkParam1 = 0;
    wchar_t message[502] = {0};
    PacketUtils::Disassemble(packet, "SdS", sizeof(charName), charName, &unkParam1, sizeof(message), message);

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    if (!sql.Execute(L"EXEC lin_GetDBIDByCharName N'%s'", charName))
    {
        serverSocket->Send("cdSdS", CacheToServerPacket_ReplyGetCharDBIDByName, -1, charName, unkParam1, message);
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        serverSocket->Send("cdSdS", CacheToServerPacket_ReplyGetCharDBIDByName, -1, charName, unkParam1, message);
        unguard();
        return false;
    }

    serverSocket->Send("cdSdS", CacheToServerPacket_ReplyGetCharDBIDByName, charId, charName, unkParam1, message);

    unguard();
    return false;
}

}  // namespace serverHandlers
