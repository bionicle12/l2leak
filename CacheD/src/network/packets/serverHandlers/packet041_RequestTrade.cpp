#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet041_RequestTrade.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00445220
bool packet041_RequestTrade(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet041_RequestTrade(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t vendorCharacterId = 0;
    uint32_t targetCharacterId = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &vendorCharacterId, &targetCharacterId);

    CUserSP vendorCharacter = g_userDb.GetUser(vendorCharacterId, true);
    CUserSP targetCharacter = g_userDb.GetUser(targetCharacterId, true);
    if (vendorCharacter == NULL || targetCharacter == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, vendorCharacterId);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, targetCharacterId);

        unguard();
        return false;
    }

    CWareHouseSP vendorInventory = vendorCharacter->GetWareHouse(WareHouseType_Inventory);
    CWareHouseSP targetInventory = targetCharacter->GetWareHouse(WareHouseType_Inventory);
    if (vendorInventory == NULL || targetInventory == NULL)
    {
        unguard();
        return false;
    }

    if (vendorInventory->GetLockAddr() == targetInventory->GetLockAddr())
    {
        g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

        vendorInventory->WriteLock();

        vendorInventory->TradeItems(serverSocket, restOfPacket, targetInventory.get());

        vendorInventory->WriteUnlock();
    }
    else if (vendorInventory->GetLockAddr() > targetInventory->GetLockAddr())
    {
        targetInventory->WriteLock();
        vendorInventory->WriteLock();

        vendorInventory->TradeItems(serverSocket, restOfPacket, targetInventory.get());

        vendorInventory->WriteUnlock();
        targetInventory->WriteUnlock();
    }
    else
    {
        vendorInventory->WriteLock();
        targetInventory->WriteLock();

        vendorInventory->TradeItems(serverSocket, restOfPacket, targetInventory.get());

        targetInventory->WriteUnlock();
        vendorInventory->WriteUnlock();
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
