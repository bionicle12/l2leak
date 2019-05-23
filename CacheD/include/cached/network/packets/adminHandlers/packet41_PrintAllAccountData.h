#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet41_PrintAllAccountData(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00415E40
}  // namespace adminHandlers
