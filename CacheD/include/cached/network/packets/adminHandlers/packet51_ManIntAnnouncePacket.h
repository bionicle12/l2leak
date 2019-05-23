#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet51_ManIntAnnouncePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00416490
}  // namespace adminHandlers
