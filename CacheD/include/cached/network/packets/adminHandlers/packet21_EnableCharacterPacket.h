#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet21_EnableCharacterPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041C1C0
}  // namespace adminHandlers
