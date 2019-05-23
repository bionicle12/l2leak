#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet07_DelSkillPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00418340
}  // namespace adminHandlers
