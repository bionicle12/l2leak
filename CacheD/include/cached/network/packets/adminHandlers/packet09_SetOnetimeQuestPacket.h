#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet09_SetOnetimeQuestPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00418BF0
}  // namespace adminHandlers
