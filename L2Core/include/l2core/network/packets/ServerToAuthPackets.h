#pragma once

enum ServerToAuthPackets
{
    ServerToAuthPacket_PlayOk = 0,
    ServerToAuthPacket_PlayFail = 1,
    ServerToAuthPacket_UserLoggedToGame = 2,
    ServerToAuthPacket_UserQuitGame = 3,
    ServerToAuthPacket_UserDropped = 4,
    ServerToAuthPacket_SetUserLimit_And_Version = 5,  // bug in GS server - both packets have same ID
    ServerToAuthPacket_UnknownPacket1 = 6,
    ServerToAuthPacket_UnknownPacket2 = 7,
    ServerToAuthPacket_PingAck = 8,
    ServerToAuthPacket_UpdateUserData = 9,
    ServerToAuthPacket_ServerConnectedReply = 10,
    ServerToAuthPacket_ReconnectedPlayerList = 11,
    ServerToAuthPacket_NewCharCreated = 12,
    ServerToAuthPacket_CharDeleted = 13,
    ServerToAuthPacket_CharManipulation = 14,
    ServerToAuthPacket_ServerSelected = 15,
    ServerToAuthPacket_UnknownPacket3 = 16,
    ServerToAuthPacket_UserDropped2 = 17,
    ServerToAuthPacket_UpdateGSStatus = 18,
    ServerToAuthPacket_UpdateUsersNumber = 19,
    ServerToAuthPacket_GetServerList = 20,
    ServerToAuthPacket_MoveCharToGS = 21
};
