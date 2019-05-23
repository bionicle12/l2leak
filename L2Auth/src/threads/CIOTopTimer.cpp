#include "l2auth/threads/CIOTopTimer.h"

#include "l2auth/utils/Unused.h"

// L2AuthD 0x0042C4D0
CIOTopTimer::CIOTopTimer()
    : CIOObject()
{
    m_nRefCount = 1;
}

// L2AuthD 0x0042C550
CIOTopTimer::~CIOTopTimer()
{
}

// L2AuthD 0x0042ABFF
void CIOTopTimer::OnTimerCallback()
{
    if (RegisterTimer(24 * 60 * 60 * 1000, 1))
    {
        ReleaseRef();  // hack, RegisterTimer does AddRef
    }
}

// L2AuthD 0x0042C500
void CIOTopTimer::OnEventCallback()
{
}

// L2AuthD 0x0042C510
void CIOTopTimer::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)
{
    UNUSED(bSuccess);
    UNUSED(dwTransferred);
    UNUSED(lpOverlapped);
}
