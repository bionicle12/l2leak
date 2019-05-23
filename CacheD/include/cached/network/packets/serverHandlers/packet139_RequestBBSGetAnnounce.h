#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet139_RequestBBSGetAnnounce(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044CB00
}  // namespace serverHandlers
