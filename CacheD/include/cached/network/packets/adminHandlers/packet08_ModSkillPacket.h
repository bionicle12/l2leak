#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet08_ModSkillPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00418790
}  // namespace adminHandlers
