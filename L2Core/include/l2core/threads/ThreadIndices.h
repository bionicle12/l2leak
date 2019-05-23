#pragma once

enum ThreadIndices
{
#ifdef L2CACHED
    ThreadIndex_IO1 = 0x0,
    ThreadIndex_IO2 = 0x1,
    ThreadIndex_IO3 = 0x2,
    ThreadIndex_IO4 = 0x3,
    ThreadIndex_IO5 = 0x4,
    ThreadIndex_IO6 = 0x5,
    ThreadIndex_IO7 = 0x6,
    ThreadIndex_IO8 = 0x7,
    ThreadIndex_IO9 = 0x8,
    ThreadIndex_IO10 = 0x9,
    ThreadIndex_IO11 = 0xA,
    ThreadIndex_IO12 = 0xB,
    ThreadIndex_IO13 = 0xC,
    ThreadIndex_IO14 = 0xD,
    ThreadIndex_IO15 = 0xE,
    ThreadIndex_IO16 = 0xF,
    ThreadIndex_IO_MAX = 0x10,
    ThreadIndex_SqlQueue = 0x10,
    ThreadIndex_CliLog = 0x11,
    ThreadIndex_PerfMonitor = 0x12,
    ThreadIndex_Main = 0x13,
    ThreadIndex_ListenThread = 0x14,
    ThreadIndex_MaxCount = 0x15,
#elif defined L2LOGD
    ThreadIndex_IO1 = 0x0,
    ThreadIndex_IO2 = 0x1,
    ThreadIndex_IO3 = 0x2,
    ThreadIndex_IO4 = 0x3,
    ThreadIndex_IO5 = 0x4,
    ThreadIndex_IO6 = 0x5,
    ThreadIndex_IO7 = 0x6,
    ThreadIndex_IO8 = 0x7,
    ThreadIndex_IO_MAX = 0x8,
    ThreadIndex_SqlQueue = 0x8,  // FIXED
    ThreadIndex_CliLog = 0x9,
    ThreadIndex_PerfMonitor = 0xA,
    ThreadIndex_Main = 0xB,
    ThreadIndex_ListenThread = 0xC,
    ThreadIndex_MaxCount
#elif defined L2NPC
    ThreadIndex_IO1 = 0x0,
    ThreadIndex_IO2 = 0x1,
    ThreadIndex_IO3 = 0x2,
    ThreadIndex_IO4 = 0x3,
    ThreadIndex_IO_MAX = 0x4,
    ThreadIndex_SqlQueue = 0x8,  // FIXED
    ThreadIndex_CliLog = 0x9,
    ThreadIndex_PerfMonitor = 0xA,
    ThreadIndex_Main = 0xB,
    ThreadIndex_ListenThread = 0xC,
    ThreadIndex_MaxCount
#endif
};
