#pragma once

#include <l2core/utils/cstdint_support.h>

class CAdminSocket;

namespace adminHandlers
{
bool packet52_ModWeekPlayPacket(CAdminSocket* pSocket, const char* packet);  // L2CacheD 0x00422AC0
}  // namespace adminHandlers
