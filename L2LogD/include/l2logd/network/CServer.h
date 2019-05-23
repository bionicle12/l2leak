#pragma once

#include "l2core/network/CIOServer.h"

class CServerSocket;

class CServer : public CIOServer
{
public:
    typedef CServerSocket* (*SocketFactory)(SOCKET socket);

public:
    CServer();   // L2LogD 0x0040F080
    ~CServer();  // L2LogD 0x0040F0F0

    static void operator delete(void* ptr);  // L2LogD inlined inside 0x0040F430

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2LogD 0x0040F300

    void Run(int port, SocketFactory allocator, bool restricted, int reader, int worker);  // L2LogD 0x0040F170

    HANDLE thread() const;
    void setThread(HANDLE thread);

protected:
    CIOSocket* CreateSocket(SOCKET newSocket, sockaddr_in* address) override;  // L2LogD 0x0040F200

private:
    static long s_nAlloc;  // L2LogD 0x01BD5028

    HANDLE m_thread;
    int field2;
    SOCKET m_socket;
    HANDLE m_someHandle;
    CRITICAL_SECTION m_lock;
    SocketFactory m_allocator;
    bool m_restrict;
};

extern CServer g_logServer;  // L2LogD 0x01BD3B68
