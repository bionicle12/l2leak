#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet111_RequestBBSDelBoard(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00447D50
}  // namespace serverHandlers
