#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet19_SetBuilderAccountPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004155D0
}  // namespace adminHandlers
