#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet000_CacheVersionPacket.h"

#include "cached/network/CServerSocket.h"
#include "cached/network/packets/serverHandlers/packet104_RequestBuilderAccountList.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <stdio.h>

namespace serverHandlers
{
// L2CacheD 0x0043C6A0
bool packet000_CacheVersionPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet000_CacheVersionPacket(CIOSocket *pSocket, const uint8_t *packet)");

    int clientProtocolVersion;
    PacketUtils::Disassemble(packet, "d", &clientProtocolVersion);

    int cachedProtocolVersion;
    char tmpString[80];
    ::sscanf("$Revision: 311 $", "%s %d", tmpString, &cachedProtocolVersion);

    int isEqualProtocols = clientProtocolVersion == cachedProtocolVersion;

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cd", CacheToServerPacket_CacheVersionPacket, isEqualProtocols);
    if (!isEqualProtocols)
    {
        g_winlog.Add(LOG_ERROR, L"Cache protocol [SERVER:%d] [CACHED:%d], ", clientProtocolVersion, cachedProtocolVersion);

        unguard();
        return true;
    }

    CServerSocket::s_gameServerSocket = serverSocket;
    serverHandlers::packet104_RequestBuilderAccountList(pSocket, NULL);

    unguard();
    return false;
}
}  // namespace serverHandlers
