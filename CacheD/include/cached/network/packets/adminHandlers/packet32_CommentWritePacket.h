#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet32_CommentWritePacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x0041E9B0
}  // namespace adminHandlers
