#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet35_RestoreCharPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041F360
}  // namespace adminHandlers
