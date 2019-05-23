#include "l2auth/model/ServersProvider.h"

#include "l2auth/config/Config.h"
#include "l2auth/model/CServerList.h"
#include "l2auth/model/ServerKind.h"

// L2AuthD 0x004350FC
int ServersProvider::SetServerSocket(int IPaddress, SOCKET socket)
{
    if (g_Config.newServerList)
    {
        return g_serverKind.SetServerSocket(IPaddress, socket);
    }
    return g_serverList.SetServerSocket(IPaddress, socket);
}

// L2AuthD 0x00435145
void ServersProvider::SetServerStatus(int serverID, bool status)
{
    if (g_Config.newServerList)
    {
        g_serverKind.SetServerStatus(serverID, status);
    }
    else
    {
        g_serverList.SetServerStatus(serverID, status);
    }
}

// L2AuthD 0x0043517B
bool ServersProvider::GetServerStatus(int serverId)
{
    if (g_Config.newServerList)
    {
        return g_serverKind.GetServerStatus(serverId);
    }

    return g_serverList.GetServerStatus(serverId);
}

// L2AuthD 0x004351B9
WorldServer ServersProvider::GetWorldServer(int serverId)
{
    if (g_Config.newServerList)
    {
        return g_serverKind.GetAt(serverId);
    }

    return g_serverList.GetAt(serverId);
}

// L2AuthD 0x0043522B
void ServersProvider::SetServerUserNum(int outerServerIP, uint16_t usersOnline, uint16_t usersLimit, int serverId)
{
    if (g_Config.newServerList)
    {
        g_serverKind.SetServerUserNum(serverId, usersOnline, usersLimit);
    }
    else
    {
        g_serverList.SetServerUserNum(outerServerIP, usersOnline, usersLimit, serverId);
    }
}
