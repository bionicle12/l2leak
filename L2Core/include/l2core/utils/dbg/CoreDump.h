#pragma once

#include "l2core/threads/CIOCriticalSection.h"
#include "l2core/threads/ThreadIndices.h"

#include <windows.h>

class CoreDump
{
public:
    static void CreateReport(EXCEPTION_POINTERS* exceptionInfo);  // L2LogD 0x00402F30, L2CacheD 0x00410130

private:
    static void WriteToFile(HANDLE fileHandle, wchar_t* format, ...);                                     // L2LogD 0x004026E0, L2CacheD 0x0040F8B0
    static const char* ExceptionToString(int exceptionCode);                                              // L2LogD 0x00402740, L2CacheD 0x0040F910
    static void WriteCallStack(ThreadIndices threadIndex, HANDLE fileHandle, const wchar_t* threadName);  // L2LogD 0x00402E10, L2CacheD 0x00410010

private:
    static CIOCriticalSection s_lock;  // L2LogD 0x00441B94, L2CacheD 0x000AEA214
};
