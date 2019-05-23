#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet16_ModChar2Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041AE60
}  // namespace adminHandlers
