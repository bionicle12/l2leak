#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet109_RequestBBSGetBoardList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00447650
}  // namespace serverHandlers
