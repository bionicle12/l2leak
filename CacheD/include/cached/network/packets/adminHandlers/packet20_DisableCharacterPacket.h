#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet20_DisableCharacterPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041BC70
}  // namespace adminHandlers
