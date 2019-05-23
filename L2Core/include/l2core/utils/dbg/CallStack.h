#pragma once

#include "l2core/threads/ThreadIndices.h"
#include "l2core/utils/dbg/StackFrameList.h"

typedef const wchar_t* FuncList[1000];

class CallStack
{
public:
    static void AddDebugInfo(const wchar_t* format, ...);                                                   // L2CacheD 0x00410E10
    static void Push(const wchar_t* funcName, const wchar_t* exitFuncName, const wchar_t* file, int line);  // L2CacheD 0x00410EE0
    static void Pop();                                                                                      // L2CacheD 0x00410FC0
    static void ReportCallStack();                                                                          // L2CacheD 0x00411080
    static void InitializeGuardStack();                                                                     // L2CacheD inlined

public:
    static int s_threadStackSizes[ThreadIndex_MaxCount];  // L2CacheD 0x00AEA160
    static FuncList s_functions[ThreadIndex_MaxCount];    // L2CacheD 0x00AD5830

    static int s_stackFramesSizes[ThreadIndex_MaxCount];        // L2CacheD 0x00AEA1B8
    static StackFrameList s_stackFrames[ThreadIndex_MaxCount];  // L2CacheD 0x00658F08
};
