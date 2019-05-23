#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet40_MoveItem2Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00420690
}  // namespace adminHandlers
