#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet45_SendHomePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004217F0
}  // namespace adminHandlers
