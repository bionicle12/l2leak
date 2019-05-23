#pragma once

#include "l2core/network/CIOServer.h"

class CServerSocket;

class CAdminServer : public CIOServer
{
public:
    CAdminServer();   // L2CacheD 0x00426AE0
    ~CAdminServer();  // L2CacheD 0x00426B50

    static void operator delete(void* ptr);  // L2CacheD inlined inside 0x00426C90

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD FIXED: added

    void Run(int port);  // L2CacheD 0x00426BC0

protected:
    CIOSocket* CreateSocket(SOCKET newSocket, sockaddr_in* address) override;  // L2CacheD 0x00426CD0

private:
    static long s_nAlloc;  // L2CacheD FIXED: added

    HANDLE m_thread;
    SOCKET m_socket;
};

extern CAdminServer g_adminServer;  // L2CacheD 0x00AFE330
