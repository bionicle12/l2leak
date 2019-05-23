#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet22_GetCharactersPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00424390
}  // namespace adminHandlers
