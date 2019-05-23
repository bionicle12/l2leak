#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet134_RequestSaveDieDropExp(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044C0B0
}  // namespace serverHandlers
