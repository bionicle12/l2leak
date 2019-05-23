#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet39_BanCharPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004201C0
}  // namespace adminHandlers
