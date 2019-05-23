#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet162_RequestPetGetItem.h"

#include "cached/model/CPetDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00456160
bool packet162_RequestPetGetItem(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet162_RequestPetGetItem(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t petId = 0;
    int unknownParam1 = 0;
    int unknownParam2 = 0;
    PacketUtils::Disassemble(packet, "ddd", &petId, &unknownParam1, &unknownParam2);

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] RequestPetGetItem failed. Cannot find pet, id[%d]", TEXT(__FILE__), __LINE__, petId);

        unguard();
        return false;
    }

    CPetWareHouseSP petInventory = pet->GetWarehouse();
    petInventory->WriteLock();

    if (!petInventory->PetGetItem(serverSocket, packet))
    {
        petInventory->WriteUnlock();

        serverSocket->Send("cddd", CacheToServerPacket_ReplyPetGetItem, 0, unknownParam2, unknownParam1);

        unguard();
        return false;
    }

    petInventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
