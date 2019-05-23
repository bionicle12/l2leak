#pragma once

#include "l2core/CIOObject.h"

static const int CIO_DEADLOCK_CHECKER_INTERVAL = 5 * 1000;

class CIODeadlockChecker : public CIOObject
{
public:
    CIODeadlockChecker();   // L2LogD 0x004092A0, L2CacheD 0x0047FF20, L2NPC 0x0047D300
    ~CIODeadlockChecker();  // L2LogD 0x00409CD0, L2CacheD 0x00480980, L2NPC 0x0047D2F0

    static void operator delete(void* ptr);  // L2LogD inlined inside 0x00409CD0, L2CacheD inlined inside 0x00480980

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2LogD 0x00409330, L2CacheD 0x0047FF80

    void Init();  // L2LogD/L2CacheD/L2NPC inlined

    long lastTick() const;

protected:
    void TimerExpired(intptr_t id) override;  // L2LogD 0x0040BBB0, L2CacheD 0x00482A10

private:
    static long s_nAlloc;  // L2LogD 0x01BD3D78, L2CacheD 0x02684920

    long m_nLastTick;
};

extern CIODeadlockChecker g_deadlock_checker;  // L2LogD 0x01BD3D5C, L2CacheD 0x026846E4, L2NPC 0x0217C5B8
