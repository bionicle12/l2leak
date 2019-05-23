#pragma once

#include "l2core/logger/LogType.h"

#include <windows.h>

class CLogSocket;

// Transfers logs L2LogD Server
class CLogCli
{
public:
    CLogCli();   // L2LogD 0x0040D1B0, L2CacheD 0x00484420
    ~CLogCli();  // L2LogD 0x00420A30, L2CacheD 0x0049D9D0

    static void Job();  // L2LogD 0x0040C3F0, L2CacheD 0x004835E0, L2NPC 0x00485470

    void LogSendMsg(LogType logType, const wchar_t* msg);  // L2LogD 0x0040D350, L2CacheD 0x004845E0, L2NPC 0x00485B40

private:
    bool Connect();  // // L2LogD 0x0040D1F0, L2CacheD 0x00484470, L2NPC 0x00485870
    bool Init();     // L2LogD 0x0040D3C0, L2CacheD 0x00484660, L2NPC inlined inside 0x00485470

private:
    CLogSocket* m_logSocket;
    CRITICAL_SECTION m_lock;
};

extern CLogCli g_cliLog;  // L2LogD 0x01BD4FA4, L2CacheD 0x02684B0C
