#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet094_RequestApproveBattle.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435AF0
bool packet094_RequestApproveBattle(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet094_RequestApproveBattle(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    void* userSocket = 0;
    uint32_t castleId = 0;
    wchar_t htmlMsg[256] = {0};
    PacketUtils::Disassemble(packet, "ddS", &userSocket, &castleId, sizeof(htmlMsg), htmlMsg);
    g_castleDb.SendReplyToApproveBattle(serverSocket, userSocket, castleId, htmlMsg);

    unguard();
    return false;
}
}  // namespace serverHandlers
