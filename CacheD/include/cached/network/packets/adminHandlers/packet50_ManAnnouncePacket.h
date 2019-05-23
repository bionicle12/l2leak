#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet50_ManAnnouncePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004161A0
}  // namespace adminHandlers
