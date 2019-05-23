#include "l2core/threads/CIOTimer.h"

CIOTimer::CIOTimer(CIOObject* object, unsigned int delay, intptr_t id)
    : m_dwTime(delay)
    , m_pObject(object)
    , m_id(id)
{
}

bool CIOTimer::operator<(const CIOTimer& rTimer) const
{
    // FIXED: invalid sorting due to integer overflow!
    int64_t result = (m_dwTime - rTimer.m_dwTime);
    return result > 0;
}
