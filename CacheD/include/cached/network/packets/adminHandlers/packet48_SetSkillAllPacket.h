#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet48_SetSkillAllPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00422270
}  // namespace adminHandlers
