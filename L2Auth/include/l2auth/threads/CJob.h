#pragma once

#include <queue>
#include <vector>
#include "l2auth/threads/CIOTimer.h"
#include "l2auth/threads/CLock.h"

#include <l2core/utils/cstdint_support.h>

class CIOObject;
class CIOTopTimer;

class CJob
{
public:
    CJob();   // L2AuthD 0x0042A9F7
    ~CJob();  // L2AuthD 0x0042AB4A

    void RunTimer();                                                         // L2AuthD 0x0042A5FC
    void RunEvent();                                                         // L2AuthD 0x0042A7A4
    bool PushTimer(CIOObject* m_timerInstance, unsigned int delay, int id);  // L2AuthD 0x0042A8C8
    bool PushEvent(HANDLE event, CIOObject* client);                         // L2AuthD 0x0042A96A
    void SetTerminate();                                                     // L2AuthD 0x0042ABD0

private:
    void clean();

private:
    CIOTopTimer* m_timerInstance;
    CLock m_lock;
    // DWORD m_nextTimer;
    int64_t m_nextTimer;  // FIXED
    HANDLE m_event1;
    HANDLE m_manualResetEvent;
    std::vector<HANDLE> m_events;
    std::vector<CIOObject*> m_clients;
    std::priority_queue<CIOTimer> m_timerQueue;
    bool m_stopThread;
    int m_isCompleted;
};

extern CJob g_job;
