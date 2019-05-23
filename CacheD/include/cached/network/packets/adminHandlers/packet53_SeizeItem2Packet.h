#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet53_SeizeItem2Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00423010
}  // namespace adminHandlers
