#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet31_MoveCharacterPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041E230
}  // namespace adminHandlers
