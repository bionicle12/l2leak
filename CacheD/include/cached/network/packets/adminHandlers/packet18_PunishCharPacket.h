#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet18_PunishCharPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041B7C0
}  // namespace adminHandlers
