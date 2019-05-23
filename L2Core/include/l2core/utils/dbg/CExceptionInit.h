#pragma once

#include "l2core/logger/CLog.h"

#include <windows.h>

class CExceptionInit
{
public:
    CExceptionInit();   // L2LogD 0x00403670, L2CacheD 0x004109D0, L2NPC 0x04109D0
    ~CExceptionInit();  // L2LogD 0x00420960, L2CacheD 0x0049D7E0

    static void LogException(const wchar_t* format, ...);  // L2LogD 0x00403760, L2CacheD 0x00410AE0
    static LONG ExceptionFilter(void* ex)
    {
        return ExceptionFilter((_EXCEPTION_POINTERS*)(ex));
    }
    static int ExceptionFilter(EXCEPTION_POINTERS* ex);  // L2LogD 0x00403920, L2CacheD 0x00410CC0
    static void SendExceptionLog(bool fatal);            // L2LogD 0x00403970, L2CacheD 0x00410D10

public:
    static wchar_t s_logPath[MAX_PATH];  // L2LogD 0x00441968, L2CacheD 0x00AD5610, L2NPC 0x005217B8
    static time_t s_startTime;           // L2LogD 0x00441B70, L2CacheD 0x00AEA158, L2NPC 0x005219C0

private:
    static LONG WINAPI RecordExceptionInfo(struct _EXCEPTION_POINTERS* exceptionInfo);                                       // L2LogD 0x00403540, L2CacheD 0x004108A0, , L2NPC 0x0041D110
    static void RestoreTopLevelFilter();                                                                                     // L2LogD 0x00403650, L2CacheD 0x004109B0
    static void InstallTopLevelFilter();                                                                                     // L2LogD 0x00403630, L2CacheD 0x00410990
    static bool SendMail(const char* ipAddress, const char* mailServer, const char* mailFrom, const wchar_t* errorLogPath);  // L2LogD 0x00402A00, L2CacheD 0x0040FBE0
    static bool SendFile(SOCKET socket, const wchar_t* fileToSend);                                                          // L2LogD 0x00402940, L2CacheD 0x0040FB10

private:
    static LPTOP_LEVEL_EXCEPTION_FILTER s_oldFilter;  // L2LogD 0x00441960, L2CacheD 0x00AEA050, L2NPC 0x005217B0
    static CRITICAL_SECTION s_lock;                   // L2LogD 0x00441B74, L2CacheD 0x00AD5818, L2NPC 0x005219C4
    static int s_errorReported;                       // L2LogD 0x00441B90, L2CacheD 0x00AEA20C, L2NPC 0x0217C25C
};

extern CExceptionInit g_exeptionHalder;  // L2LogD 0x00441BB0, L2CacheD 0x00AEA210

#define _BEFORE                                                                                                                                                                                                                                                                                                                \
    __try                                                                                                                                                                                                                                                                                                                      \
    {

#define _AFTER_FIN                                                                                                                                                                                                                                                                                                             \
    }                                                                                                                                                                                                                                                                                                                          \
    __except (CExceptionInit::ExceptionFilter(_exception_info()))                                                                                                                                                                                                                                                              \
    {                                                                                                                                                                                                                                                                                                                          \
        CExceptionInit::LogException(L"*%S:%d(%S) exception\n", __FILE__, __LINE__, __TIMESTAMP__);                                                                                                                                                                                                                            \
        g_winlog.FlushLogFile();                                                                                                                                                                                                                                                                                               \
        CExceptionInit::SendExceptionLog(true);                                                                                                                                                                                                                                                                                \
    }
