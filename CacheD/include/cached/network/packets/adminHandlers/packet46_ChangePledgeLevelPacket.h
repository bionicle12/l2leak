#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet46_ChangePledgeLevelPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00421B20
}  // namespace adminHandlers
