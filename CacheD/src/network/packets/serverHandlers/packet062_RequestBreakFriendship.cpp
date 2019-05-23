#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet062_RequestBreakFriendship.h"

#include "cached/model/CFriendsDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043A220
bool packet062_RequestBreakFriendship(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet062_RequestBreakFriendship(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    uint32_t friendCharacterId = 0;
    PacketUtils::Disassemble(packet, "ddd", &characterId, &unknownParam1, &friendCharacterId);

    bool result = g_friendsDb.BreakFriendship(characterId, friendCharacterId);
    serverSocket->Send("cddd", CacheToServerPacket_ReplyBreakFriendship, result, unknownParam1, friendCharacterId);

    unguard();
    return false;
}
}  // namespace serverHandlers
