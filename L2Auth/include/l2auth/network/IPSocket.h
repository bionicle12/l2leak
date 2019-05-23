#pragma once

#include "l2auth/network/CIOSocket.h"
#include "l2auth/network/SocketStatus.h"
#include "l2auth/threads/CRWLock.h"

#include <l2core/utils/cstdint_support.h>

class IPSocket : public CIOSocket
{
public:
    explicit IPSocket(SOCKET socket);  // L2AuthD 0x00425EF9
    ~IPSocket();                       // L2AuthD 0x00425FC4

    static IPSocket* Allocate(SOCKET socket);  // L2AuthD 0x00425E8B

    void OnTimerCallback() override;  // L2AuthD 0x0045F7E8
    void OnClose() override;          // L2AuthD 0x00426021
    void OnCreate() override;         // L2AuthD 0x004260C2
    void OnRead() override;           // L2AuthD 0x00426100

    void SetAddress(in_addr ipAddress);  // L2AuthD 0x00428610

    bool Send(const char* format, ...);             // L2AuthD 0x004262FA
    void SetConnectSessionKey(int connectSession);  // L2AuthD 0x00428630

public:
    static bool isReconnecting;
    static CRWLock s_lock;

private:
    static void NTAPI IPSocketTimerRoutine(PVOID param, BOOLEAN);  // L2AuthD 0x0042440E
    static bool packet00_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x0042593E
    static bool packet_dummy_handler(IPSocket*, uint8_t* buffer);  // L2AuthD 0x00425485
    static bool packet02_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x004257A1
    static bool packet03_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x004255CA
    static bool packet04_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x004254A0
    static bool packet05_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x00425880
    static bool packet09_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x004259DF
    static bool packet11_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x00425ADF
    static bool packet10_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x00425CC7
    static bool packet13_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x00425D86
    static bool packet15_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x00425DBA
    static bool packet14_handler(IPSocket*, uint8_t* buffer);      // L2AuthD 0x00425E53

    char* IP() const;  // L2AuthD 0x004260AA

private:
    typedef bool (*PacketHandler)(IPSocket*, uint8_t*);
    static const PacketHandler handlers[16];

    static HANDLE s_timer;

public:
    int m_connectSessionKey;

private:
    int m_packetSize;
    SocketStatus m_status;
    const PacketHandler* m_packetHandlers;
    in_addr m_serverIP;
    int16_t m_socketFamily;
    int16_t m_port;
    in_addr m_ipsocIP;
};

extern IPSocket* g_IPSocket;
