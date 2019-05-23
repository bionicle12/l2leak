#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet33_CommentDeletePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00415BF0
}  // namespace adminHandlers
