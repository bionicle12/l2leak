#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet061_RequestEstablishFriendship.h"

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
// L2CacheD 0x0043A100
bool packet061_RequestEstablishFriendship(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet061_RequestEstablishFriendship(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    wchar_t characterName[24] = {0};
    int unknownParam1 = 0;
    uint32_t friendCharacterId = 0;
    wchar_t friendCharacterName[24] = {0};
    int unknownParam2 = 0;
    PacketUtils::Disassemble(packet, "dSddSd", &characterId, sizeof(characterName), characterName, &unknownParam1, &friendCharacterId, sizeof(characterName), friendCharacterName, &unknownParam2);

    bool result = g_friendsDb.EstablishFriendship(characterId, characterName, friendCharacterId, friendCharacterName);
    serverSocket->Send("cddd", CacheToServerPacket_ReplyEstablishFriendship, result, unknownParam1, unknownParam2);

    unguard();
    return false;
}
}  // namespace serverHandlers
