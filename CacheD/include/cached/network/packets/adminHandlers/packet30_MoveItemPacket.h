#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet30_MoveItemPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041DD20
}  // namespace adminHandlers
