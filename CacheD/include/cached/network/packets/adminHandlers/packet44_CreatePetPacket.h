#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet44_CreatePetPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00421280
}  // namespace adminHandlers
