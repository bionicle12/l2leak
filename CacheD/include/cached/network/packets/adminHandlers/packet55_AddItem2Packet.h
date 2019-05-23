#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet55_AddItem2Packet(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00423BE0
}  // namespace adminHandlers
