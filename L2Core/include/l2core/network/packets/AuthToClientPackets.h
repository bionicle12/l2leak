#pragma once

enum AuthToClientPackets
{
    AuthToClientPacket_Init = 0x0,
    AuthToClientPacket_LoginFail = 0x1,
    AuthToClientPacket_AccountKicked = 0x2,
    AuthToClientPacket_LoginOk = 0x3,
    AuthToClientPacket_ServerList = 0x4,
    AuthToClientPacket_ServerListFail = 0x5,
    AuthToClientPacket_PlayFail = 0x6,
    AuthToClientPacket_PlayOk = 0x7,
    AuthToClientPacket_KickedFromGS = 0x8,
    AuthToClientPacket_AccountBlocked = 0x9,
    AuthToClientPacket_CharManipulation = 0xA,
    AuthToClientPacket_CharSelection = 0xB,
    AuthToClientPacket_CharDeleted = 0xC,
    AuthToClientPacket_ServerSelection = 0xD
};
