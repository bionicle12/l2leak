#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet36_PledgeOustPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041F7E0
}  // namespace adminHandlers
