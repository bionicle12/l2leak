#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet048_RequestTGSBoardPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435BE0
}  // namespace serverHandlers
