#include "l2auth/network/IPSessionDB.h"

#include "l2auth/config/Config.h"
#include "l2auth/model/AccountDB.h"
#include "l2auth/model/LoginUser.h"
#include "l2auth/network/CAuthServer.h"
#include "l2auth/network/CAuthSocket.h"
#include "l2auth/network/IPSocket.h"
#include "l2auth/utils/CExceptionInit.h"
#include "l2auth/utils/Unused.h"
#include "l2core/network/packets/AuthToClientPackets.h"

#include <algorithm>

IPSessionDB g_IPSessionDB;

// L2AuthD 0x0042485B
IPSessionDB::IPSessionDB()
    : m_sessionKeys()
    , m_users()
    , m_usersLock(LockType_CritSection, 0)
    , m_sessionsLock(LockType_CritSection, 0)
{
}

// L2AuthD 0x004248ED
IPSessionDB::~IPSessionDB()
{
}

// L2AuthD 0x00424962
bool IPSessionDB::DelUserWait(int uid, LoginUser** userInfo)
{
    m_usersLock.Enter();

    LoginUsers::const_iterator it = m_users.find(uid);
    if (it != m_users.end())
    {
        *userInfo = it->second;
        m_users.erase(it);

        m_usersLock.Leave();
        return true;
    }

    m_usersLock.Leave();

    return false;
}

// L2AuthD 0x00424A7D
bool IPSessionDB::AddUserWait(int uid, LoginUser* userInfo)
{
    m_usersLock.Enter();
    std::pair<std::map<int, LoginUser*>::iterator, bool> inserted = m_users.insert(std::make_pair(uid, userInfo));
    m_usersLock.Leave();

    if (!inserted.second)
    {
        LoginUser* user = NULL;
        IPSessionDB::DelUserWait(uid, &user);  // FIXME mem leak
    }

    return inserted.second;
}

// L2AuthD 0x00424B6D
int IPSessionDB::FindSessionID(int uid) const
{
    int sessionKey = 0;

    m_sessionsLock.Enter();

    Sessions::const_iterator it = m_sessionKeys.find(uid);
    if (it != m_sessionKeys.end())
    {
        sessionKey = it->second;
    }

    m_sessionsLock.Leave();
    return sessionKey;
}

// L2AuthD 0x00424C58
int IPSessionDB::DelSessionID(int uid)
{
    int sessionKey = 0;
    m_sessionsLock.Enter();

    Sessions::const_iterator it = m_sessionKeys.find(uid);
    if (it != m_sessionKeys.end())
    {
        sessionKey = it->second;
        m_sessionKeys.erase(it);
    }

    m_sessionsLock.Leave();
    return sessionKey;
}

// L2AuthD 0x00424D56
void IPSessionDB::DellAllWaitingSessionID()
{
    m_usersLock.Enter();

    for (LoginUsers::const_iterator it = m_users.begin(); it != m_users.end(); it = m_users.erase(it))
    {
        const LoginUser* userInfo = it->second;
        delete userInfo;
    }

    m_usersLock.Leave();
}

// L2AuthD 0x00424E66
int IPSessionDB::AddSessionID(int uid, int sessionKey)
{
    if (sessionKey == 0)
    {
        return 0;
    }

    m_sessionsLock.Enter();
    std::pair<std::map<int, int>::iterator, bool> inserted = m_sessionKeys.insert(std::make_pair(uid, sessionKey));
    m_sessionsLock.Leave();

    if (inserted.second)
    {
        return sessionKey;
    }

    return 0;
}

// L2AuthD 0x00424F76
char IPSessionDB::AcquireSessionRequest(LoginUser* userInfo, int uid)
{
    if (!AddUserWait(uid, userInfo))
    {
        return 11;  // fail
    }

    if (g_IPSocket != NULL && !IPSocket::isReconnecting && g_Config.useIPServer)
    {
        if (!g_IPSocket->Send("csddd", 2, userInfo->accountName, userInfo->connectedIP, g_Config.gameID, uid))
        {
            LoginUser* user = NULL;
            DelUserWait(uid, &user);  // mem leak? Caller deletes it
            return 10;                // FIXME: CAuthSocket doesn't handle 10
        }

        return 0;
    }

    LoginUser* user = NULL;
    DelUserWait(uid, &user);
    return 10;
}

// L2AuthD 0x004250BF
void IPSessionDB::ReleaseSessionRequest(int sessionKey, in_addr clientIP, int payStat)
{
    if (sessionKey == 0)
    {
        return;
    }

    if (g_Config.useIPServer && !IPSocket::isReconnecting)
    {
        if (g_IPSocket != NULL)
        {
            IPSocket::s_lock.ReadLock();
            g_IPSocket->Send("cddddd", 3, sessionKey, g_IPSocket->m_connectSessionKey, g_Config.gameID, clientIP, payStat);
            IPSocket::s_lock.ReadUnlock();
        }
    }
}

// L2AuthD 0x004251D0
char IPSessionDB::AcquireSessionSuccess(int uid, int sessionKey, bool defaultResut, int totalTime, int payStat)
{
    LoginUser* userInfo = NULL;
    DelUserWait(uid, &userInfo);

    if (userInfo == NULL)
    {
        in_addr addr;
        addr.s_addr = 0;
        ReleaseSessionRequest(sessionKey, addr, payStat);
        return true;
    }

    CAuthSocket* gameClient = g_authServer.FindSocket(userInfo->gameSocket);
    if (gameClient == NULL)
    {
        ReleaseSessionRequest(sessionKey, userInfo->connectedIP, payStat);
        delete userInfo;
        return false;
    }

    userInfo->payStat = payStat;
    if (g_accountDb.RegAccount(*userInfo, uid, gameClient, totalTime, 0))
    {
        if (!AddSessionID(uid, sessionKey))
        {
            g_accountDb.logoutAccount(uid);
            ReleaseSessionRequest(sessionKey, userInfo->connectedIP, payStat);
        }
    }
    else
    {
        ReleaseSessionRequest(sessionKey, userInfo->connectedIP, payStat);
    }

    gameClient->ReleaseRef();
    delete userInfo;

    return defaultResut;
}

// L2AuthD 0x004253A2
LoginFailReason IPSessionDB::AcquireSessionFail(int uid, int a3, LoginFailReason status)
{
    UNUSED(a3);

    LoginUser* userInfo = NULL;
    DelUserWait(uid, &userInfo);

    if (userInfo == NULL)
    {
        return REASON_SYSTEM_ERROR_LOGIN_LATER;
    }

    CAuthSocket* gameClient = g_authServer.FindSocket(userInfo->gameSocket);
    if (gameClient == NULL)
    {
        delete userInfo;
        return status;
    }

    if (status == REASON_PASS_WRONG)
    {
        gameClient->Send("cc", AuthToClientPacket_KickedFromGS, REASON_ACCESS_FAILED);
        gameClient->ReleaseRef();

        delete userInfo;
        return status;
    }

    LoginFailReason errorCode = gameClient->CheckPersonalPayStat(userInfo, uid);
    gameClient->ReleaseRef();

    delete userInfo;
    return errorCode;
}

// L2AuthD 0x004263E8
char IPSessionDB::StartIPCharge(int uid, int a2, int a3, char a4)
{
    int sessionKey = FindSessionID(uid);
    if (g_IPSocket != NULL && !IPSocket::isReconnecting && g_Config.useIPServer && sessionKey != 0)
    {
        IPSocket::s_lock.ReadLock();
        bool success = g_IPSocket->Send("cdddcdd", 4, sessionKey, g_IPSocket->m_connectSessionKey, uid, a4, a2, a3);
        IPSocket::s_lock.ReadUnlock();
        if (!success)
        {
            return 10;
        }

        return 0;
    }

    return 10;
}

// L2AuthD 0x0042651E
char IPSessionDB::StopIPCharge(int uid, in_addr connectedIp, int payStatus, time_t usedTime, time_t loginTime, int serverId, char* accName)
{
    int sessionKey = FindSessionID(uid);
    if (sessionKey == 0)
    {
        return 10;
    }

    if (g_Config.useIPServer && (sessionKey != 0) && (g_IPSocket != NULL) && !IPSocket::isReconnecting)
    {
        IPSocket::s_lock.ReadLock();
        bool success = g_IPSocket->Send("cddddcddsd", 5, g_IPSocket->m_connectSessionKey, sessionKey, connectedIp, payStatus, serverId, usedTime, (int)loginTime, accName, g_Config.gameID);

        IPSocket::s_lock.ReadUnlock();

        if (!success)
        {
            return 10;
        }

        return 0;
    }

    return 0;
}

// L2AuthD 0x0042666C
char IPSessionDB::ReadyToIPCharge(int uid, in_addr ipAddress, int payStat, char serverId)
{
    int sessionKey = FindSessionID(uid);
    if (sessionKey == 0)  // FIXED
    {                     // FIXED
        return 10;        // FIXED
    }

    if ((g_IPSocket != NULL) && !IPSocket::isReconnecting && g_Config.useIPServer && (sessionKey != 0))
    {
        IPSocket::s_lock.ReadLock();
        bool success = g_IPSocket->Send("cdddcdd", 9, sessionKey, g_IPSocket->m_connectSessionKey, uid, serverId, ipAddress, payStat);
        IPSocket::s_lock.ReadUnlock();
        if (!success)
        {
            return 10;
        }
        return 0;
    }

    return 10;
}

// L2AuthD 0x004267A2
char IPSessionDB::ConfirmIPCharge(int uid, in_addr connectedIP, int payStat, char serverId)
{
    int sessionKey = FindSessionID(uid);
    if (sessionKey == 0)  // FIXED
    {                     // FIXED
        return 10;        // FIXED
    }

    if ((g_IPSocket != NULL) && !IPSocket::isReconnecting && g_Config.useIPServer && (sessionKey != 0))
    {
        IPSocket::s_lock.ReadLock();
        bool success = g_IPSocket->Send("cdddcdd", 10, sessionKey, g_IPSocket->m_connectSessionKey, uid, serverId, connectedIP, payStat);
        IPSocket::s_lock.ReadUnlock();
        if (!success)
        {
            return 10;
        }
        return 0;
    }

    return 10;
}
