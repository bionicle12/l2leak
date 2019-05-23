#pragma once

#include "l2core/threads/ThreadIndices.h"

#include <windows.h>

#include <l2core/utils/cstdint_support.h>

class CThreadManager
{
public:
    static void RegisterThisThread(ThreadIndices threadIndex);  // L2LogD 0x00406050, L2CacheD 0x0045B330
    static void SetThisThreadAsMainThread();                    // L2LogD 0x00405FD0, L2CacheD 0x0045B2B0, L2NPC inlined in main
    static bool isMainThread();                                 // L2LogD 0x00405FF0, L2CacheD 0x0045B2D0
    static bool isListenThread();                               // L2LogD 0x00406010, L2CacheD 0x0045B2F0

    static uint32_t GetIOThreadNumber();                        // L2LogD 0x00406030, L2CacheD 0x0045B310
    static void SetIOThreadNumber(uint32_t maxIOThreadNumber);  // L2LogD 0x00406040, L2CacheD 0x0045B320, L2NPC inlined in main
    static uint32_t GetMaxIOThreadNumber();                     // L2LogD 0x004086B0, L2CacheD 0x0047F3A0, L2NPC inlined in main

    static void SetThread(ThreadIndices index, HANDLE threadId);  // L2LogD 0x00406070, L2CacheD 0x0045B350
    static HANDLE GetThread(ThreadIndices index);                 // L2LogD 0x00406080, L2CacheD 0x0045B360

private:
    static HANDLE s_threads[ThreadIndex_MaxCount];  // L2LogD 0x019D6934, L2CacheD 0x021E6F50
    static uint32_t s_IOThreadNumber;               // L2LogD 0x019D6968, L2CacheD 0x021E6FA4
};
