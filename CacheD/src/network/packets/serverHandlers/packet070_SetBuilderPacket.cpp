#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet070_SetBuilderPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00445D40
bool packet070_SetBuilderPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet070_SetBuilderPacket(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t characterName[50] = {0};
    int builderLevel = 0;
    PacketUtils::Disassemble(packet, "Sd", sizeof(characterName), characterName, &builderLevel);

    wchar_t copyOfCharacterName[50] = {0};
    Utils::CopyStrInLowerCase(characterName, copyOfCharacterName);

    CUserSP character = g_userDb.GetUser(copyOfCharacterName);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", TEXT(__FILE__), __LINE__, copyOfCharacterName);

        unguard();
        return false;
    }

    character->SetBuilderLevExtern(copyOfCharacterName, builderLevel);

    unguard();
    return false;
}
}  // namespace serverHandlers
