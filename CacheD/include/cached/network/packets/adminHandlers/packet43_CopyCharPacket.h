#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet43_CopyCharPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00420CB0
}  // namespace adminHandlers
