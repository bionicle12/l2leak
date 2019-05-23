#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet060_RequestLoadFriendList.h"

#include "cached/model/CFriendsDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043A000
bool packet060_RequestLoadFriendList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet060_RequestGetBookMarkPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    uint8_t buff[BUFFER_SIZE];
    int packetSize = g_friendsDb.LoadFriendsList(characterId, buff, BUFFER_SIZE);
    serverSocket->Send("cdb", CacheToServerPacket_ReplyLoadFriendList, unknownParam1, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
