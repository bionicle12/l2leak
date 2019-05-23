#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet157_RequestLoadPetItems.h"

#include "cached/model/CPetDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"
namespace serverHandlers
{
// L2CacheD 0x00455FB0
bool packet157_RequestLoadPetItems(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet157_RequestLoadPetItems(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int userSocket = 0;
    uint32_t petId = 0;
    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "ddd", &userSocket, &petId, &characterId);

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestLoadPetItems failed. invalid pet [%d]", TEXT(__FILE__), __LINE__, petId);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyLoadPetItems, 0, userSocket, 0, 0, 0);

        unguard();
        return false;
    }

    pet->LoadItems(characterId);

    CPetWareHouseSP petInventory = pet->GetWarehouse();
    petInventory->WriteLock();

    petInventory->SendPetItems(serverSocket, userSocket);

    petInventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
