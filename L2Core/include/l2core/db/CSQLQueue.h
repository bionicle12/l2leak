#pragma once

#include <deque>
#include <string>
#include <windows.h>

#include <l2core/utils/cstdint_support.h>

class CSQLQueue
{
public:
    CSQLQueue();   // L2LogD 0x00411C90
    ~CSQLQueue();  // L2LogD 0x00420A60

    void SpaceUsed(bool force);                // L2LogD 0x004114E0
    bool ExecSQL();                            // L2LogD 0x00411850
    bool PushSQL(const wchar_t* format, ...);  // L2LogD 0x00411D00

    static void Job();  // L2LogD 0x00403D60

    static int getDbSize();        // L2LogD inlined
    static int getUnusedDbSize();  // L2LogD inlined

private:
    static uint64_t s_lastSpaceCheck;  // L2LogD 0x019D6988
    static int s_dbSize;               // L2LogD 0x019D698C
    static int s_dbUnusedSize;         // L2LogD 0x019D6990

    CRITICAL_SECTION m_lock;
    std::deque<std::wstring> m_queue;  // TODO PORT ME: string with custom allocator
};

extern CSQLQueue g_sqlPollingQueue;  // L2LogD 0x01BD543C
