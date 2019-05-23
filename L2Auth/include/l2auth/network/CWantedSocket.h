#pragma once

#include "l2auth/network/CIOSocket.h"
#include "l2auth/network/SocketStatus.h"
#include "l2auth/threads/CRWLock.h"

#include <l2core/utils/cstdint_support.h>

class CWantedPacket;

class CWantedSocket : public CIOSocket
{
public:
    explicit CWantedSocket(SOCKET socket);  // L2AuthD 0x0043C0E0
    ~CWantedSocket();                       // L2AuthD 0x0043C16A

    static CWantedSocket* Allocate(SOCKET socket);  // L2AuthD 0x0043C072

    void OnTimerCallback() override;  // L2AuthD 0x0043C23B
    void OnClose() override;          // L2AuthD 0x0043C1C7
    void OnCreate() override;         // L2AuthD 0x0043C25E
    void OnRead() override;           // L2AuthD 0x0043C27C

    void SetAddress(in_addr ipAddress);  // L2AuthD 0x0042D400

    bool Send(const char* format, ...);  // L2AuthD 0x0043C476

public:
    static bool isReconnecting;
    static CRWLock s_lock;

private:
    static void NTAPI WantedSocketTimerRoutine(void* param, BOOLEAN);  // L2AuthD 0x0043BB3F
    char* IP() const;                                                  // L2AuthD 0x0043C246

    static bool packet0_getVersion(CWantedSocket*, uint8_t* buffer);    // L2AuthD 0x0043BF93
    static bool packet1(CWantedSocket*, uint8_t* buffer);               // L2AuthD 0x0043BFC4
    static bool packet2(CWantedSocket*, uint8_t* buffer);               // L2AuthD 0x0043BFDD
    static bool packet3_dummy_packet(CWantedSocket*, uint8_t* buffer);  // L2AuthD 0x0043BF78

private:
    typedef bool (*PacketHandler)(CWantedSocket*, uint8_t*);
    static const int HANDLERS_NUMBER = 4;
    static const PacketHandler handlers[HANDLERS_NUMBER];

    static HANDLE s_timer;

    int m_packetSize;
    SocketStatus m_status;

    const PacketHandler* m_packetHandlers;

    in_addr m_ipAddress;
    char m_allign[8];
};

extern CWantedSocket* g_SocketWanted;
