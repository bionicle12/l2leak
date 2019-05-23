#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet42_PrintAllItemData(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00415FF0
}  // namespace adminHandlers
