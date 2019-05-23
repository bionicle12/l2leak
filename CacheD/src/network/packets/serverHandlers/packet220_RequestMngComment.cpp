#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet220_RequestMngComment.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00454F10
bool packet220_RequestMngComment(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet220_RequestMngComment(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int isCommentWrite = 0;
    uint32_t writerCharacterId = 0;
    int unknownParam1 = 0;
    wchar_t unknownName[25] = {0};
    uint32_t characterId = 0;
    wchar_t comment[256] = {0};
    PacketUtils::Disassemble(packet, "dddSdS", &isCommentWrite, &writerCharacterId, &unknownParam1, sizeof(unknownName), unknownName, &characterId, sizeof(comment), comment);

    int commentCount = 0;
    uint32_t buffSize = 0;
    uint8_t buff[BUFFER_SIZE] = {0};

    CUserSP writerCharacter = g_userDb.GetUser(writerCharacterId, true);
    CUserSP character = g_userDb.GetUser(characterId, true);
    if (writerCharacter == NULL || character == NULL)
    {
        wchar_t characterName[25] = {0};  // FIXED crash when character is null
        // serverSocket->Send("cddddSb", CacheToServerPacket_ReplyMngComment, isCommentWrite, unknownParam1, writerCharacterId, commentCount, character->GetCharName(), buffSize, buff);
        serverSocket->Send("cddddSb", CacheToServerPacket_ReplyMngComment, isCommentWrite, unknownParam1, writerCharacterId, commentCount, characterName, buffSize, buff);

        unguard();
        return false;
    }

    DBConn sql;
    if (isCommentWrite == 1)
    {
        sql.Execute(L"EXEC lin_CommentWrite N'%s', %d, N'%s', N'%s'", character->GetCharName(), character->GetId(), comment, writerCharacter->GetCharName());
        sql.ResetHtmt();
    }

    uint32_t commentId = 0;
    wchar_t characterName[25] = {0};
    uint32_t characterIdFromDb = 0;
    wchar_t commentFromDb[256] = {0};
    wchar_t writerNameFromDb[25] = {0};
    SQLLEN indicator = 0;

    sql.BindNullable(&commentId, &indicator);
    sql.BindNullable(characterName, sizeof(characterName), &indicator);
    sql.BindNullable(&characterIdFromDb, &indicator);
    sql.BindNullable(commentFromDb, sizeof(commentFromDb), &indicator);
    sql.BindNullable(writerNameFromDb, sizeof(writerNameFromDb), &indicator);
    if (sql.Execute(L"EXEC lin_CommentSearch %d, %d", character->GetId(), 1))
    {
        buffSize = 0;
        while (sql.Fetch())
        {
            if (commentCount >= 4)
            {
                break;
            }

            int assembledSize = PacketUtils::Assemble(&buff[buffSize], 2048 - buffSize, "SS", &commentFromDb, writerNameFromDb);
            if (assembledSize > 0)
            {
                buffSize += assembledSize;
                ++commentCount;
            }

            ::memset(&commentFromDb, 0, sizeof(commentFromDb));
            ::memset(writerNameFromDb, 0, sizeof(writerNameFromDb));
        }
    }

    serverSocket->Send("cddddSb", CacheToServerPacket_ReplyMngComment, isCommentWrite, unknownParam1, writerCharacterId, commentCount, characterName, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
