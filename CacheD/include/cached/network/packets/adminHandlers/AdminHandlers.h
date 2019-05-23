#pragma once

class CAdminSocket;

typedef bool (*PacketHandler)(CAdminSocket*, const char*);

namespace adminHandlers
{

static const int HANDLERS_NUMBER = 56;
extern const PacketHandler s_packetHandlers[adminHandlers::HANDLERS_NUMBER];  // L2CacheD 0x004F03F8

}  // namespace adminHandlers
