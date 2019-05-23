#pragma once

#include <windows.h>

class CRWLock
{
public:
    CRWLock();   // L2CacheD 0x004346B0, L2NPC 0x004674a0
    ~CRWLock();  // L2CacheD 0x00434700, L2NPC 0x00467510

    void ReadLock();     // L2CacheD 0x004347B0, L2NPC 0x00467570
    void ReadUnlock();   // L2CacheD 0x00434990, L2NPC 0x00467640
    void WriteLock();    // L2CacheD 0x00434880, L2NPC 0x00467700
    void WriteUnlock();  // L2CacheD 0x00434A50, L2NPC 0x00467810

private:
    CRITICAL_SECTION m_critSection;
    HANDLE m_semaphore;
    int m_readersCount;
};
