#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet14_ModItemPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041A3C0
}  // namespace adminHandlers
