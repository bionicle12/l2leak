#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet26_ModPledgeNamePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041D030
}  // namespace adminHandlers
