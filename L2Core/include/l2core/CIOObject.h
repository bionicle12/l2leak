#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CIOCriticalSection.h"

#include <windows.h>

class CIOObject : public MemoryObject
{
public:
    ~CIOObject();  // L2LogD 0x0040A450, L2CacheD 0x00427E80, L2PNC 0x004178C0

    static void* operator new(size_t size);  // L2PNC 0x00417770
    static void operator delete(void* ptr);  // L2PNC 0x004178F0

    bool vfunc10() const override;                                                 // L2PNC 0x004152E0
    long AddRef(const char* file, int line, ORTs workType) override;               // L2PNC 0x00477C70
    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2PNC 0x00477C90

    virtual void OnTimer(intptr_t id);                                                      // L2LogD 0x00409260, L2CacheD 0x00414B40, L2PNC 0x00415280
    virtual void OnTimerCallback(int id);                                                   // L2LogD 0x004087B0, L2CacheD 0x0047F4A0, L2PNC 0x00478250
    virtual void OnWaitCallback();                                                          // L2LogD 0x00409270, L2CacheD 0x00401070, L2PNC 0x00415270
    virtual void OnIOCallback(BOOL success, DWORD transferred, LPOVERLAPPED lpOverlapped);  // L2LogD 0x00408840, L2CacheD 0x0047F540, L2PNC 0x00478300
    virtual BOOL PostObject(DWORD id);                                                      // L2LogD 0x00409280, L2CacheD 0x00414B50, L2PNC 0x00415250

    static bool SetShortTimeStamp(long* pTimeVar, DWORD nAdditional);  // L2LogD 0x004088C0, L2CacheD 0x0047F5D0, L2PNC 0x00478450
    static void TimerDispatch();                                       // L2LogD 0x0040A9F0, L2CacheD 0x00481710, L2NPC 0x00477F50

protected:
    CIOObject();

    virtual void TimerExpired(intptr_t id);  // L2LogD 0x00409250, L2CacheD 0x00426C50, L2PNC 0x00415290

    bool RegisterWait(HANDLE handle);               // L2LogD 0x0040B810, L2CacheD 0x00482650, L2PNC 0x00477DC0
    bool AddTimer(unsigned int time, intptr_t id);  // L2LogD 0x0040BA70, L2CacheD 0x004828C0, L2PNC 0x00478140

private:
    static long s_nAlloc;                         // L2PNC 0x0217C5B4
    static CIOCriticalSection g_globalLockTimer;  // L2LogD 0x01BD3C18, L2CacheD 0x026846B0
    static volatile LONG s_objectInTimer;         // L2LogD 0x01BD3C0C, L2CacheD 0x02684698, L2NPC 0x013FC1B8
};
