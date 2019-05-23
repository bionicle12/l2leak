#pragma once

#include <l2core/utils/cstdint_support.h>

#define BUFFER_SIZE 8192  // L2AuthD 0x2000

class CIOBuffer
{
public:
    CIOBuffer();           // L2AuthD 0x00417D00
    virtual ~CIOBuffer();  // L2AuthD 0x00417D17

    static CIOBuffer* Alloc();  // L2AuthD 0x00417DD3
    static void FreeAll();      // L2AuthD 0x00417F14

    void AddRef();   // L2AuthD 0x004116D0
    void Release();  // L2AuthD 0x0041E170
    void Free();     // L2AuthD 0x00417EC2

public:
    uint8_t m_Buffer[BUFFER_SIZE];
    int m_dwSize;
    CIOBuffer* m_pNext;
    volatile long m_nRefCount;
};
