#pragma once

#include "l2auth/model/FrameType.h"
#include "l2auth/model/WorldServer.h"
#include "l2auth/threads/CRWLock.h"

#include <vector>
#include <l2core/utils/cstdint_support.h>

class ServerPacketList;

class ServerKind
{
public:
    ServerKind();           // L2AuthD 0x00436B4F
    virtual ~ServerKind();  // L2AuthD 0x00436BC3

    void LoadServerList();                                                                     // L2AuthD 0x00436CD0
    int GetServerCount() const;                                                                // L2AuthD 0x00437250
    WorldServer GetAt(int serverId) const;                                                     // L2AuthD 0x00437261
    int SetServerSocket(int IPaddress, SOCKET socket);                                         // L2AuthD 0x004372E1
    void SetServerStatus(int serverId, bool status);                                           // L2AuthD 0x0043738C
    void SetServerUserNum(int serverId, uint16_t usersOnline, uint16_t usersLimit);            // L2AuthD 0x0043741A
    void ReloadServerList();                                                                   // L2AuthD 0x004374A8
    int GetServerMaxKind() const;                                                              // L2AuthD 0x00437F57
    int GetServerPacketList(FrameType frameFormat, int serverKindIndex, char** buffer) const;  // L2AuthD 0x00437F68
    bool GetServerStatus(int serverId) const;                                                  // L2AuthD 0x0043808B

private:
    void MakeServerListFrame();   // L2AuthD 0x00437BB6
    void CheckAllServerStatus();  // L2AuthD 0x00437FCA

private:
    int m_serverKindsCount;
    typedef std::vector<WorldServer> WorldServers;
    WorldServers m_servers;
    ServerPacketList** m_serverFrames[4];
    int m_serverCount;
    mutable CRWLock m_rwLock;
};

extern ServerKind g_serverKind;
