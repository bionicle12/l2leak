#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet06_AddSkillPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00417EE0
}  // namespace adminHandlers
