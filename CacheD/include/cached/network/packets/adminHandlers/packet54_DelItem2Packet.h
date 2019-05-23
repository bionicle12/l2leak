#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet54_DelItem2Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004235D0
}  // namespace adminHandlers
