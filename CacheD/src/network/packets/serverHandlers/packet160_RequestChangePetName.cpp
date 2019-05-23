#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet160_RequestChangePetName.h"

#include "cached/model/CPetDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00450260
bool packet160_RequestChangePetName(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet160_RequestChangePetName(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t petId = 0;
    wchar_t newName[25] = {0};
    uint32_t characterId = 0;
    PacketUtils::Disassemble(packet, "ddSd", &unknownParam1, &petId, sizeof(newName), newName, &characterId);

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestSavePet failed. invalid pet[%d]", TEXT(__FILE__), __LINE__, petId);

        unguard();
        return false;
    }

    int setNameResult = 0;
    if (!pet->SetName(newName, &setNameResult))
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplyPetNameChange, 0, unknownParam1, setNameResult);

        unguard();
        return false;
    }

    serverSocket->Send("cddS", CacheToServerPacket_ReplyPetNameChange, 1, unknownParam1, newName);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (characterId == NULL)
    {
        unguard();
        return false;
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
        LogId_ChangePetName,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        newName,
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        petId,
        pet->NpcClassId(),
        pet->Exp(),
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
