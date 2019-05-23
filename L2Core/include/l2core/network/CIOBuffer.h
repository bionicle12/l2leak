#pragma once

#include <windows.h>
#include <l2core/utils/cstdint_support.h>

#define BUFFER_SIZE 8192

class CIOBuffer
{
public:
    CIOBuffer();  // L2LogD 0x00408950
    ~CIOBuffer();

    static CIOBuffer* Alloc();  // L2LogD 0x00409460, L2CacheD 0x004800B0

    void AddRef();   // L2LogD inlined
    void Release();  // L2LogD 0x00409CB0, L2CacheD 0x00427E90, L2NPC 0x00470490
    long RefCount() const;

    void Free();  // L2LogD 0x00409500, L2CacheD 0x004801A0, L2NPC inlined

public:
    char pad1[16];
    uint8_t m_Buffer[BUFFER_SIZE];
    int m_dwSize;
    CIOBuffer* m_pNext;

private:
    long m_nRefCount;

public:
    char pad2[16];
    int m_threadIndex;
};
