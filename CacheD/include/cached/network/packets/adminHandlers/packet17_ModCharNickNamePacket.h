#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet17_ModCharNickNamePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041B330
}  // namespace adminHandlers
