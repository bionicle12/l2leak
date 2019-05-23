#include "l2auth/threads/CIOTimer.h"

// L2AuthD 0x0042C480
CIOTimer::CIOTimer(CIOObject* object, int64_t delay)
    : m_dwTime(delay)
    , m_pObject(object)
{
}

bool CIOTimer::operator<(const CIOTimer& rTimer) const
{
    // FIXED: invalid sorting due to integer overflow!
    int64_t result = (m_dwTime - rTimer.m_dwTime);
    return result > 0;
}
