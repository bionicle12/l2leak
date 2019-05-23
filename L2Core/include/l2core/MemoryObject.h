#pragma once

#include "l2core/Orts.h"

class MemoryObject
{
public:
    virtual ~MemoryObject();  // L2LogD 0x00409210, L2CacheD 0x00401B40

    virtual long AddRef(const char* file, int line, ORTs workType);               // L2LogD 0x00408980, L2CacheD 0x0042A5A0, L2NPC 0x004863D0
    virtual void Release(const char* file, int line, ORTs nWorkType, bool flag);  // L2LogD 0x0040DB20, L2CacheD 0x00485130, L2NPC 0x004863F0
    virtual long RefCount() const;                                                // L2LogD 0x00409200, L2CacheD 0x00401AB0, L2NPC 0x004152A0

    virtual bool vfunc10() const;        // L2LogD 0x00424CC8, L2CacheD 0x00401A90, L2NPC 0x00416B20
    virtual bool IsObject() const;       // L2LogD 0x00424CD0, L2CacheD 0x00401A90, L2NPC 0x00416B50
    virtual void* CastToObject() const;  // L2LogD 0x004091F0, L2CacheD 0x00401AA0, L2NPC 0x00416B40
    virtual bool IsItem() const;         // L2LogD 0x00424CD8, L2CacheD 0x00401A90, L2NPC 0x00416B30

    static long classCount();

protected:
    MemoryObject();                           // L2LogD 0x0040DAB0, L2CacheD 0x004850A0, L2NPC 0x00486520
    MemoryObject(const MemoryObject& other);  // L2NPC 0x004865A0

    void ReportOrt(int a2, int a3);  // L2LogD 0x0040DB00, L2CacheD 0x00485100, L2NPC 0x00486670

    void setInTimer(bool isInTimer);
    bool inTimer() const;

protected:
    static long s_classCounter;  // L2LogD 0x01BD3B60, L2CacheD 0x02684578, L2NPC 0x013FC1C8

private:
    static void operator delete(void* ptr);  // L2LogD/L2CacheD inlined inside deleting destructor

private:
    static long s_instances;  // L2LogD 0x01BD4FC4, L2CacheD 0x02684B30, L2NPC 0x013FC140
    static long s_nAlloc;     // L2LogD 0x01BD4FC8, L2CacheD 0x02684B34, L2NPC 0x0217C2E0

protected:
    volatile long m_nRefCount;
    long m_identity;

private:
    bool m_inTimer;
};
