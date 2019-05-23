#pragma once

#include "l2auth/model/LoginFailReason.h"
#include "l2auth/threads/CLock.h"

#include <ctime>
#include <map>

class LoginUser;

class IPSessionDB
{
public:
    IPSessionDB();           // L2AuthD 0x0042485B
    virtual ~IPSessionDB();  // L2AuthD 0x004248ED

    int DelSessionID(int uid);                                                                                                       // L2AuthD 0x00424C58
    void DellAllWaitingSessionID();                                                                                                  // L2AuthD 0x00424D56
    int AddSessionID(int uid, int sessionKey);                                                                                       // L2AuthD 0x00424E66
    char AcquireSessionRequest(LoginUser* userInfo, int uid);                                                                        // L2AuthD 0x00424F76
    void ReleaseSessionRequest(int sessionKey, in_addr clientIP, int payStat);                                                       // L2AuthD 0x004250BF
    char AcquireSessionSuccess(int uid, int sessionKey, bool defaultResut, int totalTime, int payStat);                              // L2AuthD 0x004251D0
    LoginFailReason AcquireSessionFail(int uid, int a3, LoginFailReason status);                                                     // L2AuthD 0x004253A2
    char StopIPCharge(int uid, in_addr connectedIp, int payStatus, time_t usedTime, time_t loginTime, int serverId, char* accName);  // L2AuthD 0x0042651E
    char ReadyToIPCharge(int uid, in_addr ipAddress, int payStat, char serverId);                                                    // L2AuthD 0x0042666C
    char ConfirmIPCharge(int uid, in_addr connectedIP, int payStat, char serverId);                                                  // L2AuthD 0x004267A2

private:
    char StartIPCharge(int uid, int a2, int a3, char a4);  // L2AuthD 0x004263E8

    bool DelUserWait(int uid, LoginUser** userInfo);  // L2AuthD 0x00424962
    bool AddUserWait(int uid, LoginUser* userInfo);   // L2AuthD 0x00424A7D
    int FindSessionID(int uid) const;                 // L2AuthD 0x00424B6D

private:
    typedef std::map<int, int> Sessions;
    Sessions m_sessionKeys;

    typedef std::map<int, LoginUser*> LoginUsers;
    LoginUsers m_users;
    mutable CLock m_usersLock;
    mutable CLock m_sessionsLock;
};

extern IPSessionDB g_IPSessionDB;
