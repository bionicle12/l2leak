#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet27_SetProhibitedPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004158F0
}  // namespace adminHandlers
