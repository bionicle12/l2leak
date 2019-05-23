#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOObject;

class CIOTimer
{
public:
    CIOTimer(CIOObject* object, int64_t delay);  // L2AuthD 0x0042C480

    bool operator<(const CIOTimer& rTimer) const;  // L2AuthD 0x0042C4B0

public:
    // DWORD m_dwTime;
    int64_t m_dwTime;  // FIXED: invalid sorting due to integer overflow!
    CIOObject* m_pObject;
};
