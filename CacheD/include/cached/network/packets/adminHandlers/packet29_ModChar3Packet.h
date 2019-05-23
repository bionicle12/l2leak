#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet29_ModChar3Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041D8B0
}  // namespace adminHandlers
