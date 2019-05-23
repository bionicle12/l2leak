#pragma once

#include <windows.h>

#include <l2core/utils/cstdint_support.h>

class CIOCriticalSection
{
public:
    CIOCriticalSection();                             // L2LogD 0x0040BC00, L2CacheD 0x00482A60
    explicit CIOCriticalSection(uint32_t spinCount);  // L2LogD 0x0040BC30, L2CacheD 0x00482AA0

    ~CIOCriticalSection();  // L2LogD 0x0040BC70, L2CacheD 0x00482AE0

    void Enter(const wchar_t* lockName, intptr_t line);    // L2LogD 0x0040BCA0, L2CacheD 0x00482B20
    void Leave(const wchar_t* unlockName, intptr_t line);  // L2LogD 0x0040BD00, L2CacheD 0x00482B80

private:
    CRITICAL_SECTION m_criticalSection;
    bool m_bActive;
};
