#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet10_SetQuestPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00419040
}  // namespace adminHandlers
