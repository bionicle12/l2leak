#pragma once

#include <windows.h>
#include <l2core/utils/cstdint_support.h>

class CServerUserCountStatus
{
public:
    CServerUserCountStatus();   // L2AuthD 0x00434E0F
    ~CServerUserCountStatus();  // L2AuthD 0x00434ECF

    void UpdateUserNum(int serverId, uint16_t users, uint16_t socketLimit);  // L2AuthD 0x00434EFD

private:
    static void NTAPI TimerRoutine(void* table, BOOLEAN);  // L2AuthD 0x00434DF7
    void SetCounter();                                     // L2AuthD 0x00434F73
    void UpdateAllServerNumToDB();                         // L2AuthD 0x00434FCA

private:
    struct UsersPerServer
    {
        int serverId;
        int usersLimit;
        int users;
    };

    UsersPerServer m_users[100];
    CRITICAL_SECTION m_criticalSection;
    int m_tickCount;
    HANDLE m_timerHandle;
};

extern CServerUserCountStatus g_userCount;
