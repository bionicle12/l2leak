#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

typedef bool (*PacketHandler)(CIOSocket*, const uint8_t*);

namespace npcDbHandlers
{

static const int HANDLERS_NUMBER = 5;
extern const PacketHandler s_packetHandlers[npcDbHandlers::HANDLERS_NUMBER + 1];  // L2CacheD 0x004F03F8

}  // namespace npcDbHandlers
