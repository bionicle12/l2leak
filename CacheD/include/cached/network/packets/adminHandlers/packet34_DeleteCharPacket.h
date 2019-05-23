#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet34_DeleteCharPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041EEE0
}  // namespace adminHandlers
