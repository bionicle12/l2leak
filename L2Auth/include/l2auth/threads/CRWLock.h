#pragma once

#include <windows.h>

class CRWLock
{
public:
    CRWLock();   // L2AuthD 0x0042D5C4
    ~CRWLock();  // L2AuthD 0x0042D5FA

    void ReadLock();     // L2AuthD 0x0042D61C
    void ReadUnlock();   // L2AuthD 0x0042D67A
    void WriteLock();    // L2AuthD 0x0042D6C6
    void WriteUnlock();  // L2AuthD 0x0042D6FF

private:
    CRITICAL_SECTION m_critSection;
    HANDLE m_semaphore;
    int m_readersCount;
};
