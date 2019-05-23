#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet186_RequestPackageSendToTarget.h"

#include "cached/model/CUserDb.h"
#include "cached/model/SellItemsResults.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00451350
bool packet186_RequestPackageSendToTarget(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet186_RequestPackageSendToTarget(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t senderCharacterId = 0;
    int unknownParam1 = 0;
    uint32_t targetCharacterId = 0;
    PacketUtils::Disassemble(packet, "ddd", &senderCharacterId, &unknownParam1, &targetCharacterId);

    CUserSP senderCharacter = g_userDb.GetUser(senderCharacterId, true);
    if (senderCharacter == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, dbid[%d]", TEXT(__FILE__), __LINE__, senderCharacterId);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unknownParam1, SellItemsResult_Error);

        unguard();
        return false;
    }

    CUserSP targetCharacter = g_userDb.GetUser(targetCharacterId, true);
    if (targetCharacter == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, dbid[%d]", TEXT(__FILE__), __LINE__, targetCharacterId);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unknownParam1, SellItemsResult_Error);

        unguard();
        return false;
    }

    CWareHouseSP senderInventory = senderCharacter->GetWareHouse(WareHouseType_Inventory);
    CWareHouseSP targetWarehouse = senderCharacter->GetWareHouse(WareHouseType_CharWarehouse);
    if (senderInventory == NULL || targetWarehouse == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestPackageSendToTarget item error. Cannot find warehouse. sender id[%d], receiver id[%d]", senderCharacterId, targetCharacterId);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unknownParam1, SellItemsResult_Error);

        unguard();
        return false;
    }

    if (targetWarehouse->GetLockAddr() == senderInventory->GetLockAddr())
    {
        g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

        targetWarehouse->WriteLock();

        targetWarehouse->GetPackage(serverSocket, packet, senderInventory.get());

        targetWarehouse->WriteUnlock();
    }
    else if (targetWarehouse->GetLockAddr() > senderInventory->GetLockAddr())
    {
        senderInventory->WriteLock();
        targetWarehouse->WriteLock();

        targetWarehouse->GetPackage(serverSocket, packet, senderInventory.get());

        targetWarehouse->WriteUnlock();
        senderInventory->WriteUnlock();
    }
    else
    {
        targetWarehouse->WriteLock();
        senderInventory->WriteLock();

        targetWarehouse->GetPackage(serverSocket, packet, senderInventory.get());

        senderInventory->WriteUnlock();
        targetWarehouse->WriteUnlock();
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
