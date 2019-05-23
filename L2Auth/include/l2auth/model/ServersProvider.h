#pragma once

#include <l2core/utils/cstdint_support.h>
#include "l2auth/model/WorldServer.h"

class ServersProvider  // FIXME: wrap all operations from ServerPacketList and ServerKind
{
public:
    static int SetServerSocket(int IPaddress, SOCKET socket);                                                  // L2AuthD 0x004350FC
    static void SetServerStatus(int serverID, bool status);                                                    // L2AuthD 0x00435145
    static bool GetServerStatus(int serverId);                                                                 // L2AuthD 0x0043517B
    static WorldServer GetWorldServer(int serverId);                                                           // L2AuthD 0x004351B9
    static void SetServerUserNum(int outerServerIP, uint16_t usersOnline, uint16_t usersLimit, int serverId);  // L2AuthD 0x0043522B
};
