#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet12_AddItemPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00419910
}  // namespace adminHandlers
