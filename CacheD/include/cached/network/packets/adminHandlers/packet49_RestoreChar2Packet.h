#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet49_RestoreChar2Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x004225A0
}  // namespace adminHandlers
