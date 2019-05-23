#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet47_CreatePledgePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00421E40
}  // namespace adminHandlers
