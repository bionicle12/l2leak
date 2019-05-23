#pragma once

#include "l2core/network/CIOServer.h"

class CServerSocket;

class CCacheDServer : public CIOServer
{
public:
    typedef CServerSocket* (*SocketFactory)(SOCKET socket);

public:
    CCacheDServer();   // L2CacheD 0x00434B10
    ~CCacheDServer();  // L2CacheD 0x00434B90

    static void operator delete(void* ptr);  // L2CacheD inlined inside 0x00434F00

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x00434DD0

    void Run(int port, SocketFactory allocator, bool restricted, int reader, int worker);  // L2CacheD 0x00434C20

    HANDLE thread() const;
    void setThread(HANDLE thread);

protected:
    CIOSocket* CreateSocket(SOCKET newSocket, sockaddr_in* address) override;  // L2CacheD 0x00434CC0

private:
    static long s_nAlloc;  // L2CacheD 0x021E6F18

    HANDLE m_thread;
    int field2;
    SOCKET m_socket;
    HANDLE m_someHandle;
    CRITICAL_SECTION m_lock;
    SocketFactory m_allocator;
    bool m_restrict;
};

extern CCacheDServer g_gameDbServer;  // L2CacheD 0x026845D0
extern CCacheDServer g_npcDbServer;   // L2CacheD 0x02684588
