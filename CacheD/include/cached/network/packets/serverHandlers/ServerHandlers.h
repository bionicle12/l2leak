#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

typedef bool (*PacketHandler)(CIOSocket*, const uint8_t*);

namespace serverHandlers
{

static const int HANDLERS_NUMBER = 224;
extern const PacketHandler s_packetHandlers[serverHandlers::HANDLERS_NUMBER + 1];  // L2CacheD 0x004F0DD8

}  // namespace serverHandlers
