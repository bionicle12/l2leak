#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet13_DelItemPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00419ED0
}  // namespace adminHandlers
