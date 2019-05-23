#pragma once

#include "l2core/network/CIOBuffer.h"
#include "l2core/network/CIOSocket.h"
#include "l2core/network/SocketStatus.h"

class CServerSocket : public CIOSocket
{
public:
    typedef bool (*PacketHandler)(CIOSocket*, const uint8_t*);

public:
    CServerSocket(SOCKET socket, size_t buffSize = BUFFER_SIZE);  // L2CacheD 0x00437410
    ~CServerSocket();                                             // L2CacheD 0x00437550

    static CServerSocket* Allocate(SOCKET socket);  // L2CacheD 0x00437610
    static void* operator new(size_t size);         // L2CacheD inlined
    static void operator delete(void* ptr);         // L2CacheD inlined in 0x0043C2A0

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x004372E0
    virtual void SetAddress(in_addr addr);                                         // L2CacheD 0x004376E0

    void Send(const char* format, ...);  // L2CacheD 0x00437870

protected:
    void OnCreate() override;  // L2CacheD 0x00437720
    void OnRead() override;    // L2CacheD 0x0043C2E0
    void OnClose() override;   // L2CacheD 0x00437790

public:
    static CServerSocket* s_gameServerSocket;  // L2CacheD 0x021E6F1C

private:
    static long s_nAlloc;  // L2CacheD 0x021E6F2C

protected:
    SOCKET m_socket;
    // int unused296;
    int m_buffSize;
    // int m_remoteAddr_wrong; UNUSED
    // int unused211;    UNUSED
    // int unused216;    UNUSED
    // int unused2;      UNUSED
    // int unused1;      UNUSED
    // int unused3;      UNUSED
    uint8_t* m_readBuffer;
    // int unused232; UNUSED
    // int unused223; UNUSED
    // int unused4;   UNUSED
    // int unused5;   UNUSED
    // int unused6;   UNUSED
    uint8_t* m_writeBuffer;
    HANDLE m_event;
    const PacketHandler* m_packetHandlers;
    in_addr m_remoteAddr;
    // CIOCriticalSection m_lock1; UNUSED
    CIOCriticalSection m_socketWriteLock;
    SocketStatus m_socketStatus;
    int m_packetSize;
    // int m_unused2;
    // int unused7;
    // int unused28;
    uint64_t m_key;
    int m_createdTime;
    // int unused299;
};
