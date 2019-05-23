#pragma once

#include "l2auth/network/CIOSocket.h"
#include "l2auth/network/SocketStatus.h"
#include "l2auth/threads/CRWLock.h"

#include <l2core/utils/cstdint_support.h>

class CLogPacket;

class CLogSocket : public CIOSocket
{
public:
    explicit CLogSocket(SOCKET socket);  // L2AuthD 0x0042EB84
    ~CLogSocket();                       // L2AuthD 0x0042EB23

    static CLogSocket* Allocate(SOCKET socket);  // L2AuthD 0x0042EC33

    void OnTimerCallback() override;  // L2AuthD 0x0042F2C6
    void OnClose() override;          // L2AuthD 0x0042F2D1
    void OnCreate() override;         // L2AuthD 0x0042EEE1
    void OnRead() override;           // L2AuthD 0x0042ECA1

    void SetAddress(in_addr ipAddress);  // L2AuthD 0x0042D3E0
    void Send(const char* format, ...);  // L2AuthD 0x0042EFA9

public:
    static CRWLock s_lock;
    static bool created;
    static bool isReconnecting;

private:
    static void NTAPI onTimeout(void* param, BOOLEAN);  // L2AuthD 0x0042E6CF

    char* IP() const;                     // L2AuthD 0x0042F2AE
    void Send2(const char* format, ...);  // L2AuthD 0x0042F131

    static bool packet0_dummy_handler(CLogSocket*, uint8_t* buffer);  // L2AuthD 0x0042EB08

private:
    typedef bool (*PacketHandler)(CLogSocket*, uint8_t*);
    static const PacketHandler handlers[1];

    static HANDLE s_timer;

    int m_field_92;
    int m_field_96;
    int m_packetSize;
    SocketStatus m_status;
    const PacketHandler* m_packetHandlers;
    in_addr m_logdServIp;
    uint16_t m_socketFamily;
    uint16_t m_logdport;
    in_addr m_logdIP;
};

extern CLogSocket* g_LogDSocket;
