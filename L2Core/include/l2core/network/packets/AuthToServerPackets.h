#pragma once

enum AuthToServerPackets
{
    AuthToServerPacket_AboutToPlayRequest = 0,
    AuthToServerPacket_KickAccountRequest = 1,
    AuthToServerPacket_OnlineUsersRequest = 2,
    AuthToServerPacket_AuthInitPacket = 3,
    AuthToServerPacket_PingPacket = 4,
    AuthToServerPacket_ReconnectReply = 5,
    AuthToServerPacket_Other = 6,            // Not L2 C1
    AuthToServerPacket_Other2 = 7,           // Not L2 C1
    AuthToServerPacket_Other3 = 8,           // Not L2 C1
    AuthToServerPacket_ServerList_other = 9  // Not L2 C1
};
