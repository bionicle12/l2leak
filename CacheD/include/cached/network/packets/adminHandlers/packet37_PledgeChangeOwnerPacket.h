#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet37_PledgeChangeOwnerPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041FC40
}  // namespace adminHandlers
