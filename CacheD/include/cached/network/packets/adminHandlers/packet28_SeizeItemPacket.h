#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet28_SeizeItemPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041D3E0
}  // namespace adminHandlers
