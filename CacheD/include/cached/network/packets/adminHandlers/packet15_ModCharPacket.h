#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet15_ModCharPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041A9B0
}  // namespace adminHandlers
