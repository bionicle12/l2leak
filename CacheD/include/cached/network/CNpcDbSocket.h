#pragma once

#include "cached/network/CServerSocket.h"
#include "l2core/network/CIOBuffer.h"
#include "l2core/network/SocketStatus.h"

class CNpcDbSocket : public CServerSocket
{
public:
    typedef bool (*PacketHandler)(CIOSocket*, const uint8_t*);

public:
    CNpcDbSocket(SOCKET socket, size_t buffSize = BUFFER_SIZE);  // L2CacheD 0x00427B60
    ~CNpcDbSocket();                                             // L2CacheD 0x00427BE0

    static CServerSocket* Allocate(SOCKET socket);  // L2CacheD 0x00427C60
    static void* operator new(size_t size);         // L2CacheD inlined
    static void operator delete(void* ptr);         // L2CacheD inlined in 0x00428220

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x004280F0
    void SetAddress(in_addr addr) override;                                        // L2CacheD 0x00427D30

    void Send(const char* format, ...);  // L2CacheD 0x00428530

protected:
    void OnCreate();  // L2CacheD 0x00427D70
    void OnClose();   // L2CacheD 0x00427DE0
    void OnRead();    // L2CacheD 0x00428260

private:
    static long s_nAlloc;  // L2CacheD 0x0187E36C
};
