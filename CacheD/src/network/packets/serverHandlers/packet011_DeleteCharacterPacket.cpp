#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet011_DeleteCharacterPacket.h"

#include "cached/model/CAccount.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/model/CharacterDeletetionResults.h"
#include "cached/network/CServerSocket.h"
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
// L2CacheD 0x0043EB00
bool packet011_DeleteCharacterPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet011_DeleteCharacterPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t accountId = 0;
    uint32_t characterId = 0;
    uint32_t userSocketId = 0;
    PacketUtils::Disassemble(packet, "ddd", &accountId, &characterId, &userSocketId);
    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", __FILE__, __LINE__, characterId);
        serverSocket->Send("cdd", CacheToServerPacket_DeleteCharacterFailurePacket, userSocketId, CharacterDeletetionResults_DeletetionFailed);

        unguard();
        return false;
    }

    uint32_t characterPledgeId = character->GetPledgeID();
    if (characterPledgeId != 0)
    {
        CPledgeSP characterPledge = g_pledgeDb.GetPledge(characterPledgeId);
        if (characterPledge == NULL)
        {
            serverSocket->Send("cdd", CacheToServerPacket_DeleteCharacterFailurePacket, userSocketId, CharacterDeletetionResults_CantDeleteMemberOfPledge);
            unguard();
            return false;
        }

        if (character->GetId() == characterPledge->rullerId())
        {
            serverSocket->Send("cdd", CacheToServerPacket_DeleteCharacterFailurePacket, userSocketId, CharacterDeletetionResults_CantDeleteRullerOfPledge);
            unguard();
            return false;
        }
    }

    if (character->GetBuilder() <= 0)
    {
        if (character->SetDeleted())
        {
            serverSocket->Send("cd", CacheToServerPacket_DeleteCharacterSuccessPacket, userSocketId);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot delete, id[%d]", __FILE__, __LINE__, characterId);
            serverSocket->Send("cdd", CacheToServerPacket_DeleteCharacterFailurePacket, userSocketId, CharacterDeletetionResults_DeletetionFailed);
        }
    }
    else
    {
        CAccountSP accound = CAccount::Load(accountId);
        if (accound != NULL)
        {
            accound->DeleteCharacter(characterId, true);
            serverSocket->Send("cd", CacheToServerPacket_DeleteCharacterSuccessPacket, userSocketId);
        }
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
