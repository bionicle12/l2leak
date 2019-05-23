#pragma once

#include <windows.h>

#include <l2core/utils/cstdint_support.h>

class CIOObject;

class CIOTimer
{
public:
    CIOTimer(CIOObject* object, unsigned int delay, intptr_t id = 0);  // L2LogD inlined, L2CacheD inlined

    bool operator<(const CIOTimer& rTimer) const;  // L2LogD inlined, L2CacheD inlined

public:
    // DWORD m_dwTime;
    int64_t m_dwTime;  // FIXED: invalid sorting due to integer overflow!
    CIOObject* m_pObject;
    intptr_t m_id;
};
