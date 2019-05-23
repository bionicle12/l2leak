#include "l2core/utils/dbg/Debug.h"

#include "l2core/MemoryObject.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <windows.h>

#include <stdio.h>
#include <string.h>

struct ReportLine
{
    char buffer[1024];
};

// L2CacheD 0x00409F2
void Debug::ReportClassWorkRefCount()
{
    guard(L"ReportClassWorkRefCount");

    g_winlog.Add(LOG_INF, "============  RefCount Report START ============");

    ReportLine headBuffer = {0};

    const int MAX_WORK_TYPE = 50;
    for (int i = 1; i <= MAX_WORK_TYPE; ++i)
    {
        ::sprintf(headBuffer.buffer, "%s%15ld", headBuffer.buffer, i);
    }

    g_winlog.Add(LOG_INF, "[%30s]\t[%d]\t%s", "", 0, headBuffer.buffer);

    const long refClassCount = MemoryObject::classCount();
    ReportLine dataBuffer[0x200] = {0};
    for (int i = 0; i < refClassCount; ++i)
    {
        ReportLine& reportLine = dataBuffer[i];
        const char* classRefNames = Allocator::s_classRefNames[i];
        // v3 = dword_BBE428; In CacheD it's always 0. Check in L2Server or in NPC.
        sprintf(
            reportLine.buffer,
            "%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld%15ld",
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0);

        g_winlog.Add(LOG_INF, "[%30s]\t[%d]\t%s", classRefNames, i, reportLine.buffer);
    }

    g_winlog.Add(LOG_INF, "============  RefCount Report END ============");
    unguard();
}
