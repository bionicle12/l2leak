#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet012_RequestListBoardPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435290
}  // namespace serverHandlers
