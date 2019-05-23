#pragma once

#include "l2auth/network/CIOServer.h"

#include <map>

class WorldSrvSocket;

class WorldSrvServer : public CIOServer
{
public:
    typedef WorldSrvSocket* (*WorldSrvSocketFactory)(SOCKET socket);

public:
    WorldSrvServer();   // L2AuthD 0x0041865F
    ~WorldSrvServer();  // L2AuthD 0x004186D9

    static bool SendSocket(int ipAddress, const char* format, ...);  // L2AuthD 0x00439142

    bool Run(int port, WorldSrvSocketFactory factoryMethod);  // L2AuthD 0x004188A6

    bool GetServerStatus(int ipAddress) const;  // L2AuthD 0x00418976
    void RemoveSocket(int ipAddress);           // L2AuthD 0x004189DE

protected:
    CIOSocket* CreateSocket(SOCKET socket, sockaddr_in* clientAddress) override;  // L2AuthD 0x0041873A

private:
    WorldSrvSocket* FindSocket(int ipAddress) const;  // L2AuthD 0x004188F9

private:
    typedef std::map<int, WorldSrvSocket*> Sockets;
    Sockets m_sockets;
    mutable CRITICAL_SECTION m_lock;
    WorldSrvSocketFactory m_factoryMethod;
};

extern WorldSrvServer g_worldServServer;
