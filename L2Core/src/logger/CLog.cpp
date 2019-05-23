#include "l2core/logger/CLog.h"

#include "l2core/network/CLogCli.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/threads/Threads.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#if defined(L2CACHED)
#include "cached/config/Config.h"
#elif defined(L2LOGD)
#include "l2logd/config/Config.h"
#elif defined(L2NPC)
#include "l2npc/config/Config.h"
#endif

#include <process.h>  // _beginthreadex

#include <cstdio>
#include <cwchar>

CLog g_winlog(128);  // L2LogD 0x01BD3E50, L2CacheD 0x0026849B8

const wchar_t* CLog::s_serverTypes[7] = {0, L"authd", L"cached", L"server", L"npc", L"logd", L"updated"};            // L2LogD 0x0042D860, L2CacheD 0x004F15FC
const wchar_t* CLog::s_logCategories[8] = {L"system", L"in", L"out", L"db", L"audit", L"err", L"chat", L"chatout"};  // L2LogD 0x0042D87C, L2CacheD 0x004F15DC
int CLog::s_stackSizes[ThreadIndex_MaxCount + 1];                                                                    // L2LogD 0x01BD3E18, L2CacheD 0x02684960

struct CLog::LogEntry
{
    LogType logType;
    wchar_t log[1000];
    int logSize;
};

// L2LogD 0x0040CF20, L2CacheD 0x00484190, L2NPC 0x00483E60
CLog::CLog(int size)
    : m_window(0)
    , m_enabled(0)
    , m_sendable(0)
    , m_bufferLength(size)
    , m_currentLine(0)
    , m_outputBuffer(new LogEntry[size])
    , m_criticalSection()
    , m_loginWndRect()
    , m_textSize()
    , m_font(0)
    , m_brush(0)
    , m_threadAddr(0)
    , m_logThread(0)
    , m_year(0)
    , m_month(0)
    , m_day(0)
    , m_hour(0)
    , m_half(0)
    , m_worldID(0)
    , m_logComponent(ServerType_Unset)
    , m_createNewFile(true)
{
    guard(L"CLog::CLog");

    for (int i = 0; i < size; ++i)
    {
        LogEntry* logEntry = &m_outputBuffer[i];
        logEntry->log[0] = L'\0';
    }

    memset(m_outputBuffer, 0, sizeof(LogEntry) * size);
    ::InitializeCriticalSection(&m_criticalSection);

    m_logThread = (HANDLE)_beginthreadex(0, 0, &Threads::CliLogThread, 0, CREATE_SUSPENDED, &m_threadAddr);
    CThreadManager::SetThread(ThreadIndex_CliLog, m_logThread);

    for (int i = 0; i < FileBuffers_BuffersCount; ++i)
    {
        m_fileBuffers[i] = INVALID_HANDLE_VALUE;
        ::InitializeCriticalSection(&m_bufferLocks[i]);
    }

#ifdef L2LOG
    ::memset(m_fileNames, 0, sizeof(m_fileNames));
#endif

    unguard();
}

// L2LogD 0x00420A20, L2CacheD 0x00482F00
CLog::~CLog()
{
    guard(L"CLog::~CLog");

    delete[] m_outputBuffer;
    ::DeleteCriticalSection(&m_criticalSection);

    for (int i = 0; i < FileBuffers_BuffersCount; ++i)
    {
        HANDLE buffer = m_fileBuffers[i];
        if (buffer != INVALID_HANDLE_VALUE)
        {
            ::FlushFileBuffers(buffer);
            ::CloseHandle(buffer);
            m_fileBuffers[i] = INVALID_HANDLE_VALUE;  // FIXED
        }

        ::DeleteCriticalSection(&m_bufferLocks[i]);
    }

    unguard();
}

// L2LogD 0x0040D060, L2CacheD 0x004842D0
void CLog::Add(LogType severity, const char* format, ...)
{
    guard(L"CLog::Add");

    va_list va;
    va_start(va, format);

    AddV(severity, format, va);

    va_end(va);

    unguard();
}

// L2LogD 0x0040D0D0, L2CacheD 0x00484340
void CLog::Add(LogType severity, const wchar_t* format, ...)
{
    guard(L"CLog::Add");

    va_list va;
    va_start(va, format);

    AddV(severity, format, va);

    va_end(va);

    unguard();
}

HANDLE CLog::cliLogThread() const
{
    return m_logThread;
}

// L2LogD 0x0040BDE0, L2CacheD 0x00482FD0
void CLog::Set(HWND logWnd)
{
    guard(L"CLog::Set");

    m_window = logWnd;

    unguard();
}

// L2LogD 0x0040BF30, L2CacheD 0x004830E0, L2NPC 0x00484ED0
void CLog::Redraw()
{
    guard(L"CLog::Redraw");
    if (!m_enabled)
    {
        unguard();
        return;
    }

    ::GetClientRect(m_window, &m_loginWndRect);
    tagPAINTSTRUCT painter;
    HDC hdc = ::BeginPaint(m_window, &painter);
    if (m_font)
    {
        ::SelectObject(hdc, m_font);
    }
    else
    {
        m_font = ::GetStockObject(SYSTEM_FIXED_FONT);
        ::SelectObject(hdc, m_font);
        m_brush = (HBRUSH)::GetStockObject(WHITE_BRUSH);
        ::GetTextExtentPoint32W(hdc, L"H", 1, &m_textSize);
    }

    int y = m_loginWndRect.bottom;
    int currLine = m_currentLine;

    while (true)
    {
        long lineHeight = m_textSize.cy;
        long right = m_loginWndRect.right;
        y -= lineHeight;

        RECT rc;
        rc.bottom = y + lineHeight;
        rc.left = 0;
        rc.right = right;
        rc.top = y;

        ::FillRect(hdc, &rc, m_brush);
        currLine = (m_bufferLength - 1) & (currLine - 1);

        LogEntry* logEntry = &m_outputBuffer[currLine];
        if (logEntry != (LogEntry*)-4)
        {
            // L2LogD 0x0042D844, L2CacheD 0x004F1618
            static const COLORREF color[] = {0x00000000, 0x00FF0000, 0x000000FF, 0x00008CFF, 0x00008CFF, 0x00008CFF, 0x00008CFF};
            // FIXME: Log types are 0..9, while colors only 7
            ::SetTextColor(hdc, color[logEntry->logType]);
            ::TextOutW(hdc, 0, y, logEntry->log, logEntry->logSize);
        }

        if (y < 0)
        {
            break;
        }
    }

    ::EndPaint(m_window, &painter);

    unguard();
}

// L2LogD 0x0040C0A0, L2CacheD 0x00483270
void CLog::Enable(bool enable)
{
    guard(L"CLog::Enable");

    m_enabled = enable;
    if (enable)
    {
        ::InvalidateRect(m_window, 0, 0);
    }

    unguard();
}

// L2LogD 0x0040C0E0, L2CacheD 0x004832C0
void CLog::Sendable(bool sendable)
{
    guard(L"void CLog::Sendable(bool flag)");

    m_sendable = sendable;

    unguard();
}

bool CLog::IsSendable() const
{
    return m_sendable;
}

// L2LogD 0x0040C110, L2CacheD 0x00483340
void CLog::FlushLogFile()
{
    guard(L"CLog::FlushLogFile");

    DWORD written;
    const char errMsg[] = "\nException occured. Flush Flush!!!\n";
    ::WriteFile(m_fileBuffers[FileBuffers_Error], errMsg, ::strlen(errMsg), &written, 0);

    for (int i = 0; i < FileBuffers_BuffersCount; ++i)
    {
        ::FlushFileBuffers(m_fileBuffers[i]);
    }

    unguard();
}

// L2LogD 0x0040BE80, L2CacheD 0x00482F80
bool CLog::CanAppend(int year, int month, int day, int hour, bool half) const
{
    if (m_createNewFile)
    {
        return false;
    }

    if (half != m_half || m_hour != hour || m_year != year || m_month != month || m_day != day)
    {
        return false;
    }

    return true;
}

// L2LogD 0x0040BEF0, L2CacheD 0x00483010
void CLog::LockBuffer(int bufferIndex)
{
    ::EnterCriticalSection(&m_bufferLocks[bufferIndex]);
}

// L2LogD 0x0040BF10, L2CacheD 0x00483030
void CLog::UnlockBuffer(int bufferIndex)
{
    ::LeaveCriticalSection(&m_bufferLocks[bufferIndex]);
}

// L2CacheD 0x00483300, L2NPC 0x004851A0
void CLog::ConnectToLogD()
{
    guard(L"CLog::ConnectToLogD()");

    ::ResumeThread(m_logThread);

    unguard();
}

// L2LogD 0x0040C180, L2CacheD 0x004833C0
void CLog::CreateNewLogFile(int year, int month, int day, int hour, bool half)
{
    guard(L"void CLog::CreateNewLogFile(int nYear, int nMonth, int nDay, int nHour, int nHalf )");

    if (m_logComponent == ServerType_Unset)
    {
        unguard();
        return;
    }

    if (CanAppend(year, month, day, hour, half))
    {
        unguard();
        return;
    }

    wchar_t fileName[256];
    memset(fileName, 0, sizeof(fileName));

    m_year = year;
    m_half = half;
    m_day = day;
    m_hour = hour;
    m_month = month;
    m_createNewFile = false;

    for (int i = 0; i < (sizeof(CLog::s_logCategories) / sizeof(CLog::s_logCategories[0])); ++i)
    {
#ifdef L2LOG
        FileName& fileBufferName = m_fileNames[i];
#endif
        ::EnterCriticalSection(&m_bufferLocks[i]);
        const HANDLE fileBuffer = m_fileBuffers[i];
        if (fileBuffer != INVALID_HANDLE_VALUE)
        {
            ::FlushFileBuffers(fileBuffer);
#if defined _WIN64
            LARGE_INTEGER fileSizeLarge = {0};
            ::GetFileSizeEx(fileBuffer, &fileSizeLarge);
            LONGLONG fileSize = fileSizeLarge.QuadPart;
#else
            DWORD fileSize = ::GetFileSize(fileBuffer, 0);
#endif
            ::CloseHandle(fileBuffer);
#ifdef L2LOG
            DWORD fileSize = ::GetFileSize(fileBuffer, 0);
            if (fileSize == 0)
            {
                ::DeleteFileW(fileBufferName.path);
            }
#endif
        }

        const wchar_t* logCategory = CLog::s_logCategories[i];
        //::swprintf(fileName, L"log\\%s\\%04d-%02d-%02d-100%02d-%02d-%s-%s%d.log", logCategory, m_year, m_month, m_day, m_hour, m_worldID, CLog::s_serverTypes[m_logComponent], logCategory, m_half); FIXED
        ::swprintf(fileName, sizeof(fileName) / sizeof(*fileName), L"log\\%s\\%04d-%02d-%02d-100%02d-%02d-%s-%s%d.log", logCategory, m_year, m_month, m_day, m_hour, m_worldID, CLog::s_serverTypes[m_logComponent], logCategory, m_half);

        ::CreateDirectoryW(L"log", NULL);

        wchar_t pathName[50];
        ::wsprintfW(pathName, L"log\\%s", logCategory);
        ::CreateDirectoryW(pathName, NULL);

        const HANDLE newFileBuffer = ::CreateFileW(fileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#ifdef L2LOG
        ::wcscpy(fileBufferName.path, fileName);
#endif
        if (newFileBuffer != INVALID_HANDLE_VALUE)
        {
#if defined _WIN64
            LARGE_INTEGER offset = {0};
            ::SetFilePointerEx(newFileBuffer, offset, 0, FILE_END);
#else
            ::SetFilePointer(newFileBuffer, FILE_BEGIN, 0, FILE_END);
#endif
        }

        m_fileBuffers[i] = newFileBuffer;
        ::LeaveCriticalSection(&m_bufferLocks[i]);
    }

    unguard();
}

// L2LogD 0x0040C4C0, L2CacheD 0x004836B0
void CLog::AddV(LogType severity, const char* format, va_list params)
{
    guard(L"CLog::AddV");

    uint32_t threadIndex = tls::GetCurrentThreadIndex();

    int funcCount = CLog::s_stackSizes[threadIndex] + 1;
    CLog::s_stackSizes[threadIndex] = funcCount;

    if ((funcCount > 1) || (m_outputBuffer == NULL) || (severity == LOG_REQUEST))
    {
        CLog::s_stackSizes[threadIndex] = funcCount - 1;
        unguard();
        return;
    }

    char messageBuffAnsi[1000];
    memset(messageBuffAnsi, 0, sizeof(messageBuffAnsi));

    wchar_t messageBuff[1000];
    memset(messageBuff, 0, sizeof(messageBuff));

    bool invalidateWindow = false;

    int msgLength = ::vsprintf(messageBuffAnsi, format, params);
    if (msgLength <= 0)
    {
        CLog::s_stackSizes[threadIndex] = funcCount - 1;
        unguard();
        return;
    }

    int buffLen = ::strlen(messageBuffAnsi);
    for (int i = 0; i < buffLen; ++i)
    {
        messageBuff[i] = messageBuffAnsi[i];  // FIXME: AnsiToWideChar
    }

    if (severity < LOG_REQUEST)
    {
        ::EnterCriticalSection(&m_criticalSection);
        m_outputBuffer[m_currentLine].logType = severity;
        ::wcscpy(m_outputBuffer[m_currentLine].log, messageBuff);
        m_outputBuffer[m_currentLine].logSize = msgLength;
        m_currentLine = (m_currentLine + 1) & (m_bufferLength - 1);
        ::LeaveCriticalSection(&m_criticalSection);
        invalidateWindow = true;
    }

    SYSTEMTIME systemTime;
    ::GetLocalTime(&systemTime);
    if (m_sendable)
    {
        wchar_t msg[0x1100];
        memset(msg, 0, sizeof(msg));
        //::swprintf(msg, L"%02d/%02d/%04d %02d:%02d:%02d.%03d, %s\r\n", systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, messageBuff); FIXED
        ::swprintf(msg, sizeof(msg) / sizeof(*msg), L"%02d/%02d/%04d %02d:%02d:%02d.%03d, %s\r\n", systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, messageBuff);
        g_cliLog.LogSendMsg(severity, msg);

        if (m_enabled && invalidateWindow)
        {
            ::InvalidateRect(m_window, 0, 0);
        }

        CLog::s_stackSizes[threadIndex] = funcCount - 1;
        unguard();
        return;
    }

    if (!CanAppend(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u))
    {
        ::EnterCriticalSection(&m_criticalSection);
        m_worldID = Config::s_worldId;
#if defined(L2CACHED)
        m_logComponent = ServerType_CacheD;
#elif defined(L2LOGD)
        m_logComponent = ServerType_LogD;
#elif defined(L2NPC)
        m_logComponent = ServerType_NPC;
#else
#error
#endif
        CreateNewLogFile(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u);
        ::LeaveCriticalSection(&m_criticalSection);
    }

    char msg[0x1100];
    memset(msg, 0, sizeof(msg));

    char* message = Utils::UnicodeToMultibyte(messageBuff);
    sprintf(msg, "%02d/%02d/%04d %02d:%02d:%02d.%03d, %s\r\n", systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, message);
    delete[] message;

    DWORD bytesWritten;
    switch (severity)
    {
        case LOG_IN:
            LockBuffer(FileBuffers_In);
            ::WriteFile(m_fileBuffers[FileBuffers_In], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_In);
            break;
        case LOG_DB:
            LockBuffer(FileBuffers_Db);
            ::WriteFile(m_fileBuffers[FileBuffers_Db], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Db);
            break;
        case LOG_AUDIT:
            LockBuffer(FileBuffers_Audit);
            ::WriteFile(m_fileBuffers[FileBuffers_Audit], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Audit);
            break;
        case LOG_ERROR:
            LockBuffer(FileBuffers_Error);
            ::WriteFile(m_fileBuffers[FileBuffers_Error], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Error);
            break;
        case LOG_CHAT:
            LockBuffer(FileBuffers_Chat);
            ::WriteFile(m_fileBuffers[FileBuffers_Chat], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Chat);
            break;
        default:
            LockBuffer(FileBuffers_System);
            ::WriteFile(m_fileBuffers[FileBuffers_System], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_System);
            break;
    }

    if (m_enabled && invalidateWindow)
    {
        ::InvalidateRect(m_window, 0, 0);
    }

    CLog::s_stackSizes[threadIndex] = funcCount - 1;

    unguard();
}

// L2LogD 0x0040CA10, L2CacheD 0x00483C30
void CLog::AddV(LogType severity, const wchar_t* format, va_list params)
{
    guard(L"CLog::AddV");

    uint32_t threadIndex = tls::GetCurrentThreadIndex();

    int funcCount = CLog::s_stackSizes[threadIndex] + 1;
    CLog::s_stackSizes[threadIndex] = funcCount;

    if ((funcCount > 1) || (m_outputBuffer == NULL) || (severity == LOG_REQUEST))
    {
        CLog::s_stackSizes[threadIndex] = funcCount - 1;
        unguard();
        return;
    }

    wchar_t messageBuff[1000];
    memset(messageBuff, 0, sizeof(messageBuff));
    bool invalidateWindow = false;

    guard(L"Log::AddV - vswprintf");
    // msgLength = ::vswprintf(messageBuff, format, params); // FIXED
    int msgLength = ::vswprintf(messageBuff, sizeof(messageBuff) / sizeof(*messageBuff), format, params);
    unguard();

    if (msgLength <= 0)
    {
        CLog::s_stackSizes[threadIndex] = funcCount - 1;
        unguard();
        return;
    }

    if (severity < LOG_REQUEST)
    {
        ::EnterCriticalSection(&m_criticalSection);

        m_outputBuffer[m_currentLine].logType = severity;
        ::wcscpy(m_outputBuffer[m_currentLine].log, messageBuff);
        m_outputBuffer[m_currentLine].logSize = msgLength;
        m_currentLine = (m_currentLine + 1) & (m_bufferLength - 1);

        ::LeaveCriticalSection(&m_criticalSection);
        invalidateWindow = true;
    }

    SYSTEMTIME systemTime;
    ::GetLocalTime(&systemTime);
    if (m_sendable)
    {
        wchar_t msg[0x1100];
        memset(msg, 0, sizeof(msg));
        //::swprintf(msg, L"%02d/%02d/%04d %02d:%02d:%02d.%03d, %s\r\n", systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, messageBuff); // FIXED
        ::swprintf(msg, sizeof(msg) / sizeof(*msg), L"%02d/%02d/%04d %02d:%02d:%02d.%03d, %s\r\n", systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, messageBuff);
        g_cliLog.LogSendMsg(severity, msg);

        if (m_enabled && invalidateWindow)
        {
            ::InvalidateRect(m_window, 0, 0);
        }

        CLog::s_stackSizes[threadIndex] = funcCount - 1;
        unguard();
        return;
    }

    if (!CanAppend(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u))
    {
        ::EnterCriticalSection(&m_criticalSection);
        m_worldID = Config::s_worldId;
#if defined(L2CACHED)
        m_logComponent = ServerType_CacheD;
#elif defined(L2LOGD)
        m_logComponent = ServerType_LogD;
#elif defined(L2NPC)
        m_logComponent = ServerType_NPC;
#else
#error
#endif
        CreateNewLogFile(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u);
        ::LeaveCriticalSection(&m_criticalSection);
    }

    char msg[0x1100];
    memset(msg, 0, sizeof(msg));

    char* message = Utils::UnicodeToMultibyte(messageBuff);
    sprintf(msg, "%02d/%02d/%04d %02d:%02d:%02d.%03d, %s\r\n", systemTime.wMonth, systemTime.wDay, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, message);
    delete[] message;

    DWORD bytesWritten;
    switch (severity)
    {
        case LOG_IN:
            LockBuffer(FileBuffers_In);
            ::WriteFile(m_fileBuffers[FileBuffers_In], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_In);
            break;
        case LOG_DB:
            LockBuffer(FileBuffers_Db);
            ::WriteFile(m_fileBuffers[FileBuffers_Db], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Db);
            break;
        case LOG_AUDIT:
            LockBuffer(FileBuffers_Audit);
            ::WriteFile(m_fileBuffers[FileBuffers_Audit], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Audit);
            break;
        case LOG_ERROR:
            LockBuffer(FileBuffers_Error);
            ::WriteFile(m_fileBuffers[FileBuffers_Error], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Error);
            break;
        case LOG_CHAT:
            LockBuffer(FileBuffers_Chat);
            ::WriteFile(m_fileBuffers[FileBuffers_Chat], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Chat);
            break;
        default:
            LockBuffer(FileBuffers_System);
            ::WriteFile(m_fileBuffers[FileBuffers_System], msg, ::strlen(msg), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_System);
            break;
    }

    if (m_enabled && invalidateWindow)
    {
        ::InvalidateRect(m_window, 0, 0);
    }

    CLog::s_stackSizes[threadIndex] = funcCount - 1;
    unguard();
}

void CLog::ForceNewFile()
{
    m_createNewFile = true;
}
