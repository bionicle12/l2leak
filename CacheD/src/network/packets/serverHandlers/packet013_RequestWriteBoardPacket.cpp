#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet013_RequestWriteBoardPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x004350B0
bool packet013_RequestWriteBoardPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet013_RequestWriteBoardPacket(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam1 = 0;
    int unkParam2 = 0;
    wchar_t writerFull[1024] = {0};
    wchar_t contentFull[5120] = {0};
    PacketUtils::Disassemble(packet, "ddSS", &unkParam1, &unkParam2, sizeof(writerFull), writerFull, sizeof(contentFull), contentFull);

    if (unkParam1)
    {
        wchar_t writer[1024] = {0};
        wchar_t contentReduced[1024] = {0};

        DBConn sql;

        ::wcsncpy(writer, writerFull, 8u);
        ::wcsncpy(contentReduced, contentFull, 60u);
        sql.Execute(L"EXEC lin_WriteBbsTGS N'%s', N'%s', N'%s'", L"None", contentReduced, writer);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
