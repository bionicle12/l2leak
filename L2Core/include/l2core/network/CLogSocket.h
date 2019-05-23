#pragma once

#include "l2core/network/CIOSocket.h"
#include "l2core/network/SocketStatus.h"

class CLogSocket : public CIOSocket
{
public:
    typedef bool (*PacketHandler)(CIOSocket*, const uint8_t*);

public:
    CLogSocket(SOCKET socket, const PacketHandler* packetHandlers);  // L2LogD 0x0040D4E0, L2CacheD 0x00484820, L2PNC 0x00485EB0
    ~CLogSocket();                                                   // L2LogD 0x0040D560, L2CacheD 0x004848B0, L2PNC 0x00485F70

    static void* operator new(size_t size);  // L2LogD 0x0040D140, L2CacheD 0x004843B0, L2PNC 0x00485710
    static void operator delete(void* ptr);  // L2LogD 0x0040D190, L2CacheD 0x00484400, L2PNC 0x00485F30

    long AddRef(const char* file, int line, ORTs workType);  // L2PNC 0x00485D60

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2LogD 0x0040D700, L2CacheD 0x00484A50, L2PNC 0x00485D80
    void Send(const char* format, ...);                                            // L2LogD 0x0040D5F0, L2CacheD 0x00484950, L2PNC 0x004862D0

public:
    static const int HANDLERS_NUMBER = 3;
    static const PacketHandler s_packetHandlers[HANDLERS_NUMBER];  // L2LogD 0x0042D89C, L2CacheD 0x004F16AC

protected:
    void OnClose();  // L2LogD 0x0040D570, L2CacheD 0x004848C0, L2PNC 0x004861F0
    void OnRead();   // L2LogD 0x0040D870, L2CacheD 0x00484BC0, L2PNC 0x00485F80

private:
    static bool packet0_SendMsg(CIOSocket* socket, const uint8_t* packet);      // L2LogD 0x0040D430, L2CacheD 0x004846D0, L2PNC 0x00485BF0
    static bool packet1_CheckStatus(CIOSocket* socket, const uint8_t* packet);  // L2LogD 0x0040D450, L2CacheD 0x00484700, L2PNC 0x00485C30
    static bool packet2_TestPacket(CIOSocket* socket, const uint8_t* packet);   // L2LogD 0x0040D4C0, L2CacheD 0x004847F0, L2PNC 0x00485D20

private:
    static long s_nAlloc;  // L2LogD 0x01BD4FC0, L2CacheD 0x02684B28, L2NPC 0x0217C2E4

    SOCKET m_socket;
    int field_2;
    const PacketHandler* m_packetHandlers;
    SocketStatus m_status;
    int m_packetSize;
};
