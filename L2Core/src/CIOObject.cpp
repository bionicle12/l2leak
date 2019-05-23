#include "l2core/CIOObject.h"

#include "l2core/Orts.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/threads/CIOTimer.h"
#include "l2core/threads/IOCP.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/threads/Threads.h"
#include "l2core/utils/dbg/Assert.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <queue>
#include <vector>

// L2PNC 0x004C6F50
long CIOObject::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2PNC 0x0217C5B4

CIOCriticalSection CIOObject::g_globalLockTimer;  // L2LogD 0x01BD3C18, L2CacheD 0x026846B0
volatile LONG CIOObject::s_objectInTimer;         // L2LogD 0x01BD3C0C, L2CacheD 0x02684698, L2NPC 0x013FC1B8

typedef std::vector<CIOTimer> TimerVector;
typedef std::priority_queue<CIOTimer, TimerVector> TimerQueue;
static TimerQueue g_timerQueues[ThreadIndex_MaxCount];  // L2LogD 0x01BD3C38, L2CacheD 0x26846F8, L2NPC 0x0x217C478

CIOObject::CIOObject()
    : MemoryObject()
{
}

// L2LogD 0x0040A450, L2CacheD 0x00427E80, L2PNC 0x004178C0
CIOObject::~CIOObject()
{
}

// L2PNC 0x00417770
void* CIOObject::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CIOObject");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CIOObject::s_nAlloc]);

    Allocator::s_classRefNames[CIOObject::s_nAlloc] = "CIOObject";
    Allocator::g_allocatedMemory[CIOObject::s_nAlloc] = sizeof(CIOObject);

    return memory;
}

// L2PNC 0x004178F0
void CIOObject::operator delete(void* ptr)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CIOObject at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2PNC 0x004152E0
bool CIOObject::vfunc10() const
{
    return false;
}

// L2PNC 0x00477C70
long CIOObject::AddRef(const char* file, int line, ORTs workType)
{
    ::InterlockedIncrement(&m_nRefCount);
    return m_nRefCount;
}

// L2PNC 0x00477C90
void CIOObject::Release(const char* file, int line, ORTs nWorkType, bool flag)
{
    long refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
    if (refCountAfterRelease > 0)
    {
        return;
    }

    if (refCountAfterRelease != 0)
    {
        if (refCountAfterRelease > -1)
        {
            return;
        }

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CIOObject(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();

        return;
    }

    if (inTimer())
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOObject] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOObject::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOObject]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOObject::s_nAlloc]);
        }
        return;
    }

    this->~CIOObject();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOObject::s_nAlloc]);
}

// L2LogD 0x00409250, L2CacheD 0x00426C50, L2PNC 0x00415290
void CIOObject::TimerExpired(intptr_t /*id*/)
{
}

// L2LogD 0x00409260, L2CacheD 0x00414B40, L2PNC 0x00415280
void CIOObject::OnTimer(intptr_t id)
{
    setInTimer(false);
    TimerExpired(id);
}

// L2LogD 0x004087B0, L2CacheD 0x0047F4A0, L2PNC 0x00478250
void CIOObject::OnTimerCallback(int id)
{
    guard(L"void CIOObject::OnTimerCallback(int id)");

    if (::PostQueuedCompletionStatus(IOCP::g_hCompletionPort, id, (ULONG_PTR)this, NULL) == FALSE)
    {
        EASSERT();
        Release(__FILE__, __LINE__, ORT_TIMER, 0);
    }

    unguard();
}

// L2LogD 0x00409270, L2CacheD 0x00401070, L2PNC 0x00415270
void CIOObject::OnWaitCallback()
{
}

// L2LogD 0x00408840, L2CacheD 0x0047F540, L2PNC 0x00478300
void CIOObject::OnIOCallback(BOOL /*success*/, DWORD transferred, LPOVERLAPPED /*lpOverlapped*/)
{
    guard(L"void CIOObject::OnIOCallback(BOOL success, DWORD transferred, LPOVERLAPPED lpOverlapped)");

    OnTimer(transferred);
    Release(__FILE__, __LINE__, ORT_TIMER, 0);

    unguard();
}

// L2LogD 0x00409280, L2CacheD 0x00414B50, L2PNC 0x00415250
BOOL CIOObject::PostObject(DWORD id)
{
    return ::PostQueuedCompletionStatus(IOCP::g_hCompletionPort, id, (ULONG_PTR)this, NULL);
}

// L2LogD 0x004088C0, L2CacheD 0x0047F5D0, L2PNC 0x00478450
bool CIOObject::SetShortTimeStamp(long* pTimeVar, DWORD nAdditional)
{
    guard(L"CIOObject::SetShortTimeStamp()");

    long now = nAdditional + ::GetTickCount();
    if (now <= *pTimeVar)
    {
        unguard();
        return false;
    }

    ::InterlockedExchange(pTimeVar, now);

    unguard();

    return true;
}

// L2LogD 0x0040A9F0, L2CacheD 0x00481710, L2PNC 0x00477F50
void CIOObject::TimerDispatch()
{
    guard(L"void CIOObject::TimerDispatch(bool bRootLoop)");

    DWORD tick = ::GetTickCount();
    uint32_t threadIndex = tls::GetCurrentThreadIndex();

    TimerQueue& timerQueue = g_timerQueues[threadIndex];

    while (!timerQueue.empty())
    {
        const CIOTimer& top = timerQueue.top();
        if (top.m_dwTime > tick)
        {
            break;
        }

        int id = top.m_id;
        CIOObject* object = top.m_pObject;
        timerQueue.pop();

        ::InterlockedDecrement(&CIOObject::s_objectInTimer);

        if (threadIndex == ThreadIndex_ListenThread)
        {
            object->OnTimerCallback(id);
        }
        else
        {
            object->OnIOCallback(true, id, NULL);
        }
    }

    unguard();
}

#define MAXIMUM_WAIT_OBJECTS 64

// L2LogD 0x0040B810, L2CacheD 0x00482650, L2PNC 0x00477DC0
bool CIOObject::RegisterWait(HANDLE handle)
{
    guard(L"BOOL CIOObject::RegisterWait(HANDLE handle)");

    g_globalLockTimer.Enter(0, 0);
    if (Threads::g_vHandle.size() >= MAXIMUM_WAIT_OBJECTS)
    {
        g_globalLockTimer.Leave(0, 0);
        unguard();
        return false;
    }

    Threads::g_vHandle.push_back(handle);
    Threads::g_vObject.push_back(this);

    g_globalLockTimer.Leave(0, 0);

    unguard();

    return true;
}

// L2LogD 0x0040BA70, L2CacheD 0x004828C0, L2PNC 0x00478140
bool CIOObject::AddTimer(unsigned int time, intptr_t id)
{
    guard(L"bool CIOObject::AddTimer(unsigned time, int id)");

#if defined(L2LOGD) || (L2CACHED)
    if (time < 80)
    {
        // small timers limit
        static int s_count = 0;
        if (s_count++ < 30)  // TODO: double check me! Logic looks buggy
        {
            g_winlog.Add(LOG_ERROR, L"dwTime[%d] < 80 !!!!!!!", time);
            CallStack::ReportCallStack();
        }
        time = 80;
    }
#endif

    ::InterlockedIncrement(&CIOObject::s_objectInTimer);

    AddRef(__FILE__, __LINE__, ORT_TIMER);

    setInTimer(true);

    uint32_t threadIndex = tls::GetCurrentThreadIndex();
    DWORD timeout = time + ::GetTickCount();

    TimerQueue& timerQueue = g_timerQueues[threadIndex];
    timerQueue.push(CIOTimer(this, timeout, id));

    unguard();

    return true;
}
