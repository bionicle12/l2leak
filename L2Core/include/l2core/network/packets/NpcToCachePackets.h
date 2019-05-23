#pragma once

enum NpcToCachePackets
{
    NpcToCachePacket_DummyPacket = 0,
    NpcToCachePacket_NpcDbVersion = 1,
    NpcToCachePacket_LoadNpcRequest = 2,
    NpcToCachePacket_SaveNpcInfo = 3,
    NpcToCachePacket_UpdateBossNpcValue = 4
};
