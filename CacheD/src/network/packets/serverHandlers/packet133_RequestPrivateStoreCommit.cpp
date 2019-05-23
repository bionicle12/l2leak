#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet133_RequestPrivateStoreCommit.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044BC80
bool packet133_RequestPrivateStoreCommit(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet133_RequestPrivateStoreCommit(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t vendorCharacterId = 0;     // vendor might be a char, who sets private store for selling, as well as char, who sells to other's private store
    uint32_t purchaserCharacterId = 0;  // purchaser might be a char, who sets private store for buying, as well as char, who buys from private store
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &vendorCharacterId, &purchaserCharacterId);

    CUserSP vendorCharacter = g_userDb.GetUser(vendorCharacterId, true);
    CUserSP purchaserCharacter = g_userDb.GetUser(purchaserCharacterId, true);
    if (vendorCharacter == NULL || purchaserCharacter == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, vendorCharacterId);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, purchaserCharacterId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, vendorCharacterId, purchaserCharacterId, 0, 0);

        unguard();
        return false;
    }

    CWareHouseSP vendorWarehouse = vendorCharacter->GetWareHouse(WareHouseType_Inventory);
    CWareHouseSP purchaserWarehouse = purchaserCharacter->GetWareHouse(WareHouseType_Inventory);
    if (vendorWarehouse == NULL || purchaserWarehouse == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find warehouse, user id[%d]", TEXT(__FILE__), __LINE__, vendorCharacterId);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find warehouse, user id[%d]", TEXT(__FILE__), __LINE__, purchaserCharacterId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, vendorCharacterId, purchaserCharacterId, 0, 0);

        unguard();
        return false;
    }

    if (purchaserWarehouse->GetLockAddr() == vendorWarehouse->GetLockAddr())
    {
        g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

        purchaserWarehouse->WriteLock();

        vendorWarehouse->PrivateStoreCommit(serverSocket, restOfPacket, purchaserWarehouse.get());

        purchaserWarehouse->WriteUnlock();
    }
    else if (purchaserWarehouse->GetLockAddr() > vendorWarehouse->GetLockAddr())
    {
        vendorWarehouse->WriteLock();
        purchaserWarehouse->WriteLock();

        vendorWarehouse->PrivateStoreCommit(serverSocket, restOfPacket, purchaserWarehouse.get());

        purchaserWarehouse->WriteUnlock();
        vendorWarehouse->WriteUnlock();
    }
    else
    {
        purchaserWarehouse->WriteLock();
        vendorWarehouse->WriteLock();

        vendorWarehouse->PrivateStoreCommit(serverSocket, restOfPacket, purchaserWarehouse.get());

        vendorWarehouse->WriteUnlock();
        purchaserWarehouse->WriteUnlock();
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
