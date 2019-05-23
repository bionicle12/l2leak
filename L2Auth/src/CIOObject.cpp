#include "l2auth/CIOObject.h"

#include "l2auth/threads/CJob.h"
#include "l2auth/utils/Unused.h"

// L2AuthD 0x00418060
CIOObject::CIOObject()
    : m_nRefCount(0)
{
}

// L2AuthD 0x00418081
CIOObject::~CIOObject()
{
}

// L2AuthD 0x00418095
#if defined _WIN64
LONGLONG CIOObject::AddRef()  // L2AuthD 0x00418095
#else
LONG CIOObject::AddRef()  // L2AuthD 0x00418095
#endif
{

#if defined _WIN64
    ::InterlockedIncrement64(&m_nRefCount);
#else
    ::InterlockedIncrement(&m_nRefCount);
#endif

    return m_nRefCount;
}

// L2AuthD 0x004180B3
void CIOObject::ReleaseRef()
{
#if defined _WIN64
    ::InterlockedDecrement64(&m_nRefCount);
#else
    ::InterlockedDecrement(&m_nRefCount);
#endif

    if (m_nRefCount == 0)
    {
        if (this != NULL)
        {
            delete this;
        }
    }
}

// L2AuthD 0x0041811C
bool CIOObject::RegisterTimer(unsigned int delay, int id)
{
    if (g_job.PushTimer(this, delay, id))
    {
        AddRef();
        return true;
    }
    return false;
}

// L2AuthD 0x00418154
bool CIOObject::RegisterEvent(HANDLE eventObject)
{
    return g_job.PushEvent(eventObject, this);
}

// L2AuthD 0x0041817D
void CIOObject::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)
{
    UNUSED(bSuccess);
    UNUSED(dwTransferred);
    UNUSED(lpOverlapped);
}

// L2AuthD 0x0041818A
void CIOObject::OnTimerCallback()
{
    ReleaseRef();
}

// L2AuthD 0x0041819D
void CIOObject::OnEventCallback()
{
}

// L2AuthD 0x004180FB
BOOL CIOObject::PostObject(DWORD id, HANDLE completionPort)
{
    return ::PostQueuedCompletionStatus(completionPort, id, (ULONG_PTR)this, NULL);
}
