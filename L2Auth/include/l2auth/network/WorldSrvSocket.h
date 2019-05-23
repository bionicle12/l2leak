#pragma once

#include "l2auth/model/CServerKickList.h"
#include "l2auth/network/CIOSocket.h"
#include "l2auth/network/SocketStatus.h"
#include "l2auth/threads/CRWLock.h"

#include <l2core/utils/cstdint_support.h>

class WorldSrvPacket;

class WorldSrvSocket : public CIOSocket
{
public:
    WorldSrvSocket(SOCKET socket);  // L2AuthD 0x00410BAB
    ~WorldSrvSocket();              // L2AuthD 0x00410C4F

    static WorldSrvSocket* Allocate(SOCKET socket);  // L2AuthD 0x00410CA3

    void OnClose() override;   // L2AuthD 0x00410D11
    void OnCreate() override;  // L2AuthD 0x00411123
    void OnRead() override;    // L2AuthD 0x00410E7A

    void SetAddress(in_addr ipAddress);  // L2AuthD 0x0041115C

    void Send(const char* format, ...);  // L2AuthD 0x004111F6

    void setServerId(int serverId)
    {
        m_serverID = serverId;
    }

private:
    static bool packet00_playOk(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);                 // L2AuthD 0x0040F680
    static bool packet01_playFail(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);               // L2AuthD 0x0040F7B1
    static bool packet02_userLoggedToGame(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);       // L2AuthD 0x0040F8B2
    static bool packet03_userQuitGame(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);           // L2AuthD 0x0040F900
    static bool packet04_userDropped(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);            // L2AuthD 0x0040FA11
    static bool packet05_setUserLimit(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);           // L2AuthD 0x0040FAF4
    static bool packet06_stub(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);                   // L2AuthD 0x0040FB53
    static bool packet07_stub(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);                   // L2AuthD 0x0040FB7E
    static bool packet08_pingAck(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);                // L2AuthD 0x0040FB97
    static bool packet09_updateUserData(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);         // L2AuthD 0x0040FBBE
    static bool packet10_serverConnectedReply(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);   // L2AuthD 0x0040FC7A
    static bool packet11_ReconnectedPlayerList(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);  // L2AuthD 0x0040FD0D
    static bool packet12_newCharCreated(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);         // L2AuthD 0x004101AC
    static bool packet13_charDeleted(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);            // L2AuthD 0x0041026C
    static bool packet14_charManipulation(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);       // L2AuthD 0x00410307
    static bool packet15_serverSelected(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);         // L2AuthD 0x00410448
    static bool packet16_handler(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);                // L2AuthD 0x004105CD
    static bool packet17_userDropped(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);            // L2AuthD 0x00410653
    static bool packet18_updateGSStatus(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);         // L2AuthD 0x0041070C
    static bool packet19_updateUsersNumber(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);      // L2AuthD 0x0041085B
    static bool packet20_getServerList(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);          // L2AuthD 0x00410970
    static bool packet21_moveCharToGS(WorldSrvSocket* worldSrvSocket, uint8_t* buffer);           // L2AuthD 0x004103AD

private:
    char* IP() const;     // L2AuthD 0x00411108
    int getaddr() const;  // L2AuthD 0x00411510

private:
    typedef bool (*PacketHandler)(WorldSrvSocket*, uint8_t*);
    static const int HANDLERS_NUMBER = 22;
    static const PacketHandler handlers[HANDLERS_NUMBER];

    SOCKET m_socket;
    int m_serverID;
    int m_status_unused;
    bool m_worldStatus;
    CServerKickList m_accsInUseMap;
    int m_packetSize;
    SocketStatus m_socketStatus;
    const PacketHandler* m_packetHandlers;
    in_addr m_worldSrvIP;
};
