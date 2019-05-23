#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet23_SetBookMarkPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041C690
}  // namespace adminHandlers
