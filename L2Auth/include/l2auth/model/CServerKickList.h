#pragma once

#include "l2auth/threads/CLock.h"

#include <map>
#include <string>

class WorldSrvSocket;

class CServerKickList
{
public:
    CServerKickList();   // L2AuthD 0x004115B0
    ~CServerKickList();  // L2AuthD 0x00411680

    void AddKickUser(int uid, char* accName);  // L2AuthD 0x004112BF
    void PopKickUser(WorldSrvSocket* socket);  // L2AuthD 0x0041136F

private:
    std::map<int, std::string> m_users;
    CLock m_lock;
};
