#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet02_SetCharacterLocationPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00416C10
}  // namespace adminHandlers
