#pragma once

#include "l2core/logger/FileBuffers.h"
#include "l2core/logger/LogType.h"
#include "l2core/logger/ServerTypes.h"
#include "l2core/threads/ThreadIndices.h"

#include <windows.h>
#include <varargs.h>

class CLog
{
public:
    explicit CLog(int size);  // L2LogD 0x0040CF20, L2CacheD 0x00484190, L2NPC 0x00483E60
    ~CLog();                  // L2LogD 0x00420A20, L2CacheD 0x00482F00

    void ConnectToLogD();  // L2CacheD 0x00483300, L2NPC 0x004851A0

    void Set(HWND logWnd);                                   // L2LogD 0x0040BDE0  L2CacheD 0x00482FD0
    void Redraw();                                           // L2LogD 0x0040BF30  L2CacheD 0x004830E0, L2NPC 0x00484ED0
    void Enable(bool enable);                                // L2LogD 0x0040C0A0  L2CacheD 0x00483270
    void Sendable(bool sendable);                            // L2LogD 0x0040C0E0  L2CacheD 0x004832C0
    bool IsSendable() const;                                 // L2LogD inlined     L2CacheD, inlined
    void FlushLogFile();                                     // L2LogD 0x0040C110  L2CacheD 0x00483340
    void Add(LogType severity, const char* format, ...);     // L2LogD 0x0040D060  L2CacheD 0x004842D0
    void Add(LogType severity, const wchar_t* format, ...);  // L2LogD 0x0040D0D0  L2CacheD 0x00484340

    void ForceNewFile();  // L2LogD inlined in binary, L2CacheD inlined in binary
    HANDLE cliLogThread() const;

private:
    bool CanAppend(int year, int month, int day, int hour, bool half) const;   // L2LogD 0x0040BE80, L2CacheD 0x00482F80
    void CreateNewLogFile(int year, int month, int day, int hour, bool half);  // L2LogD 0x0040C180, L2CacheD 0x004833C0
    void LockBuffer(int bufferIndex);                                          // L2LogD 0x0040BEF0, L2CacheD 0x00483010
    void UnlockBuffer(int bufferIndex);                                        // L2LogD 0x0040BF10, L2CacheD 0x00483030
    void AddV(LogType severity, const char* format, va_list params);           // L2LogD 0x0040C4C0, L2CacheD 0x004836B0
    void AddV(LogType severity, const wchar_t* format, va_list params);        // L2LogD 0x0040CA10, L2CacheD 0x00483C30

private:
    struct LogEntry;
    struct FileName
    {
        wchar_t path[MAX_PATH];
    };

private:
    static const wchar_t* s_serverTypes[7];             // L2LogD 0x0042D860, L2CacheD 0x004F15FC
    static const wchar_t* s_logCategories[8];           // L2LogD 0x0042D87C, L2CacheD 0x004F15DC
    static int s_stackSizes[ThreadIndex_MaxCount + 1];  // L2LogD 0x01BD3E18, L2CacheD 0x02684960

    HWND m_window;
    bool m_enabled;
    bool m_sendable;
    // bool m_enabled3; unused
    const int m_bufferLength;
    int m_currentLine;
    LogEntry* m_outputBuffer;
    CRITICAL_SECTION m_criticalSection;
    RECT m_loginWndRect;
    SIZE m_textSize;
    HGDIOBJ m_font;
    HBRUSH m_brush;
    unsigned int m_threadAddr;
    HANDLE m_logThread;
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    bool m_half;
    int m_worldID;
    ServerTypes m_logComponent;
    HANDLE m_fileBuffers[FileBuffers_BuffersCount];
    CRITICAL_SECTION m_bufferLocks[FileBuffers_BuffersCount];
#ifdef L2LOG
    FileName m_fileNames[FileBuffers_BuffersCount];
#endif
    bool m_createNewFile;
};

extern CLog g_winlog;  // L2LogD 0x01BD3E50, L2CacheD 0x026849B8
