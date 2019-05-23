#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet05_KickCharacterPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00417AC0
}  // namespace adminHandlers
