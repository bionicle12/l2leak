#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet002_CreateCharacterPacket.h"

#include "cached/config/Config.h"
#include "cached/model/CAccount.h"
#include "cached/model/CUserDb.h"
#include "cached/model/CharacterCreationResults.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

static const uint32_t MAX_CHARACTERS_PER_ACCOUNT = 7;

// L2CacheD 0x0043E670
bool packet002_CreateCharacterPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet002_CreateCharacterPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    wchar_t name[25];
    memset(name, 0, sizeof(name));
    wchar_t accountNameOfOwner[25];
    memset(accountNameOfOwner, 0, sizeof(accountNameOfOwner));
    uint32_t accountIdOfOwner = 0;
    uint32_t gender = 0;
    uint32_t race = 0;
    uint32_t classOfCharacter = 0;
    uint32_t worldId = 0;
    uint32_t locX = 0;
    uint32_t locY = 0;
    uint32_t locZ = 0;
    double hp = 0;
    double mp = 0;
    uint32_t faceIndex = 0;
    uint32_t hairShapeIndex = 0;
    uint32_t hairColorIndex = 0;
    uint32_t userSocketId = 0;

    PacketUtils::Disassemble(packet, "SSddddddddffdddd", sizeof(name), name, sizeof(accountNameOfOwner), accountNameOfOwner, &accountIdOfOwner, &gender, &race, &classOfCharacter, &worldId, &locX, &locY, &locZ, &hp, &mp, &faceIndex, &hairShapeIndex, &hairColorIndex, &userSocketId);
    if (!Utils::CheckCharacterName(name, Config::s_country))
    {
        g_winlog.Add(LOG_REQUEST, L"Uncreatable name. [%s]", name);
        serverSocket->Send("cdd", CacheToServerPacket_CreateCharacterFailurePacket, CharacterCreationResult_CharLimitExceededOrNameInvalid, userSocketId);

        unguard();
        return false;
    }

    CAccountSP loadedAccount = CAccount::Load(accountIdOfOwner);
    if (loadedAccount != NULL)
    {
        uint32_t amountOfCharacter = loadedAccount->GetCharCount();
        if (amountOfCharacter >= MAX_CHARACTERS_PER_ACCOUNT)
        {
            g_winlog.Add(LOG_ERROR, L"can not create char. too many chars [%d]", amountOfCharacter);
            serverSocket->Send("cdd", CacheToServerPacket_CreateCharacterFailurePacket, CharacterCreationResult_CharLimitExceededOrNameInvalid, userSocketId);

            unguard();
            return false;
        }
    }

    DBConn sql;
    uint32_t defaultBuilderLevelOnAccount;
    sql.Bind(&defaultBuilderLevelOnAccount);
    if (!sql.Execute(L"EXEC lin_GetBuilderAccount N'%s'", accountNameOfOwner) || !sql.Fetch())
    {
        defaultBuilderLevelOnAccount = 0;
    }

    uint32_t newCharacterId = g_userDb.CreateUser(name, accountNameOfOwner, accountIdOfOwner, 0, defaultBuilderLevelOnAccount, gender, race, classOfCharacter, worldId, locX, locY, locZ, hp, mp, 0, 0, 1, 0, 0, 0, 0, faceIndex, hairShapeIndex, hairColorIndex);
    if (newCharacterId == 0)
    {
        g_winlog.Add(LOG_REQUEST, L"Create character fail~ %s", name);
        serverSocket->Send("cdd", CacheToServerPacket_CreateCharacterFailurePacket, CharacterCreationResult_CreationFailed, userSocketId);

        unguard();
        return false;
    }

    CUserSP newCharacter = g_userDb.GetUser(newCharacterId, true);
    if (newCharacter == NULL)
    {
        g_winlog.Add(LOG_REQUEST, L"Create character fail~ %s", name);
        serverSocket->Send("cdd", CacheToServerPacket_CreateCharacterFailurePacket, CharacterCreationResult_CreationFailed, userSocketId);

        unguard();
        return false;
    }

    if (loadedAccount != NULL)
    {
        loadedAccount->SetCharacter(newCharacter.get());
    }

    newCharacterId = newCharacter->GetId();
    g_winlog.Add(LOG_REQUEST, L"Create character Success~ %d", newCharacterId);
    serverSocket->Send("cddd", CacheToServerPacket_CreateCharacterSuccessPacket, newCharacterId, classOfCharacter, userSocketId);

    unguard();
    return false;
}
}  // namespace serverHandlers
