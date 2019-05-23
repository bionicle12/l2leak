#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet01_CheckCharacterPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004167D0
}  // namespace adminHandlers
