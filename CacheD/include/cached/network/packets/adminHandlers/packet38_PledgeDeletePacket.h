#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet38_PledgeDeletePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041FF60
}  // namespace adminHandlers
