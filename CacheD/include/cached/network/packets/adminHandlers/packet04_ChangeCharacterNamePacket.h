#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet04_ChangeCharacterNamePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004175B0
}  // namespace adminHandlers
