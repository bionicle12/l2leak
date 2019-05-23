#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet03_SetBuilderCharacterPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00417130
}  // namespace adminHandlers
