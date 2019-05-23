#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet00_NoPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00415560
}  // namespace adminHandlers
