#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet11_DelQuestPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004194B0
}  // namespace adminHandlers
