#include <WinSock2.h>

#include "l2logd/network/CServerSocket.h"

#include "l2core/db/CSQLQueue.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/LogDPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"
#include "l2logd/config/Config.h"

// L2LogD 0x004208F0
long CServerSocket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD5438

// L2LogD 0x0042D8A8
const CServerSocket::PacketHandler CServerSocket::s_packetHandlers[CServerSocket::HANDLERS_NUMBER + 1] = {&CServerSocket::packet00_SendLog, &CServerSocket::packet01_SetCheckStatus, &CServerSocket::packet02_CheckLogD, &CServerSocket::packet03_ServerStarted};

const wchar_t* CServerSocket::s_serverTypes[7] = {0, L"authd", L"cached", L"server", L"npc", L"logd", L"updated"};            // L2LogD 0x0042D8DC
const wchar_t* CServerSocket::s_logCategories[8] = {L"system", L"in", L"out", L"db", L"audit", L"err", L"chat", L"chatout"};  // L2LogD 0x0042D8BC

// L2LogD 0x0040F6B0
CServerSocket::CServerSocket(SOCKET socket, size_t buffSize)
    : CIOSocket(socket)
    , m_socket(socket)
    , m_buffSize(buffSize)
    , m_remoteAddr()
    , m_status(SocketStatus_Init)
    //  field_149(0)
    //  field_150(0)
    //  field_151(0)
    //  field_152(0)
    , m_readBuffer(new uint8_t[buffSize])
    // , field_154(0)
    // , field_155(0)
    // , field_156(0)
    // , field_157(0)
    // , field_158(0)
    , m_writeBuffer(new uint8_t[buffSize])
    , m_event(::CreateEventW(0u, TRUE, FALSE, NULL))
    , m_packetHandlers(CServerSocket::s_packetHandlers)
    , m_lock1(0)
    , m_socketWriteLock()
    //, m_socketStatus(SocketStatus_Init)
    , m_packetSize(0)
    // , field_178(0)
    // , field_179(0)
    // , field_180(0)
    // , field_181(0)
    // , field_182(0)
    // , field_183(0)
    // , field_184(0)
    , m_checkStatus(false)
    , m_createdTime(::GetTickCount())
    , m_year(0)
    , m_month(0)
    , m_day(0)
    , m_hour(0)
    , m_half(0)
    , m_worldId(0)
    , m_logComponent(ServerType_Unset)
    , m_fileLock()
// , field_1236(0)
{
    guard(L"CServerSocket::CServerSocket(SOCKET hSocket, int nBufSize=8192)");

    m_remoteAddr.s_addr = 0;

    for (int i = 0; i < FileBuffers_BuffersCount; ++i)
    {
        m_fileBuffers[i] = INVALID_HANDLE_VALUE;
        ::InitializeCriticalSection(&m_bufferLocks[i]);
    }

    ::InitializeCriticalSection(&m_fileLock);

    memset(m_yearMonthDay, 0, sizeof(m_yearMonthDay));
    memset(m_fileNames, 0, sizeof(m_fileNames));

    unguard();
}

// L2LogD 0x0040F890
CServerSocket::~CServerSocket()
{
    guard(L"CServerSocket::~CServerSocket()");

    for (int i = 0; i < FileBuffers_BuffersCount; ++i)
    {
        HANDLE buffer = m_fileBuffers[i];
        if (buffer != INVALID_HANDLE_VALUE)
        {
            ::FlushFileBuffers(buffer);
            ::CloseHandle(buffer);
            m_fileBuffers[i] = INVALID_HANDLE_VALUE;
        }

        ::DeleteCriticalSection(&m_bufferLocks[i]);
    }

    ::CloseHandle(m_event);

    delete[] m_readBuffer;
    delete[] m_writeBuffer;

    ::DeleteCriticalSection(&m_fileLock);

    unguard();
}

// L2LogD 0x0040F9A0
CServerSocket* CServerSocket::Allocate(SOCKET socket)
{
    guard(L"CServerSocket::Allocate()");

    CServerSocket* serverSocket = new CServerSocket(socket, BUFFER_SIZE);

    unguard();

    return serverSocket;
}

// L2LogD inlined
void* CServerSocket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CServerSocket");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);

    Allocator::s_classRefNames[CServerSocket::s_nAlloc] = "CServerSocket";
    Allocator::g_allocatedMemory[CServerSocket::s_nAlloc] = sizeof(CServerSocket);

    return memory;
}

// L2LogD 0x0040F470
void CServerSocket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CServerSocket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2LogD 0x004100E0
void CServerSocket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
{
    long refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
    if (refCountAfterRelease > 0)
    {
        return;
    }

    if (refCountAfterRelease != 0)
    {
        if (refCountAfterRelease > -1)
        {
            return;
        }

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CServerSocket(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();

        return;
    }

    if (inTimer())
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CServerSocket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CServerSocket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);
        }
        return;
    }

    this->~CServerSocket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);
}

// L2LogD 0x00410080
void CServerSocket::SetAddress(in_addr addr)
{
    guard(L"void CServerSocket::SetAddress(in_addr addr)");

    m_remoteAddr = addr;

    unguard();
}

// L2LogD 0x004100B0
in_addr CServerSocket::GetAddress() const
{
    guard(L"in_addr CServerSocket::GetAddress() const");

    unguard();

    return m_remoteAddr;
}

// L2LogD 0x004111F0
void CServerSocket::TimerExpired(intptr_t /*timerId*/)
{
    guard(L"void CServerSocket::TimerExpired(intptr_t id)");

    if (!m_checkStatus)
    {
        // Client didn't ask for ping
        unguard();
        return;
    }

    if (m_status != SocketStatus_Closed)
    {
        Send("cd", LogD_SetCheckStatus, 0);  // 0 - don't ask for ping back
        AddTimer(Config::s_serverReportInterval, 0);
    }

    unguard();
}

// L2LogD 0x00411280
void CServerSocket::OnRead()
{
    guard(L"CServerSocket::OnRead()");

    if ((m_status == SocketStatus_Closed) || (m_nPendingWrite > 0x800000))
    {
        Close();
        unguard();
        return;
    }

    const int buffSize = m_pReadBuf->m_dwSize;

    if (buffSize <= 0)
    {
        Read(0);
        unguard();
        return;
    }

    int dwRead = 0;
    while (true)
    {
        // read size only
        while (true)
        {
            if (m_status != SocketStatus_Init)
            {
                break;
            }

            if (dwRead + 2 > buffSize)
            {
                Read(buffSize - dwRead);
                unguard();
                return;
            }

            m_packetSize = (m_pReadBuf->m_Buffer[dwRead + 1] << 8) + m_pReadBuf->m_Buffer[dwRead] - 2;

            if (m_packetSize <= 0 || m_packetSize > BUFFER_SIZE)
            {
                g_winlog.Add(LOG_ERROR, L"%d: bad packet size %d", m_hSocket, m_packetSize);
                m_status = SocketStatus_Closed;
                Close();
                unguard();
                return;
            }

            dwRead += 2;
            m_status = SocketStatus_BytesRead;

            if (dwRead >= buffSize)
            {
                Read(0);
                unguard();
                return;
            }
        }

        if (m_status != SocketStatus_BytesRead)
        {
            Close();
            unguard();
            return;
        }

        if ((dwRead + m_packetSize) > buffSize)
        {
            Read(buffSize - dwRead);
            unguard();
            return;
        }

        // 2 bytes size, 3rd byte is packet type
        int packetId = m_pReadBuf->m_Buffer[dwRead];
        if (packetId >= HANDLERS_NUMBER)
        {
            g_winlog.Add(LOG_ERROR, L"unknown protocol %d", packetId);
            m_status = SocketStatus_Closed;
            Close();
            unguard();
            return;
        }

        CPacket* packet = CPacket::Alloc();

        packet->m_pSocket = this;
        packet->m_pBuf = m_pReadBuf;

        packet->m_pFunc = m_packetHandlers[packetId];

        AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);
        m_pReadBuf->AddRef();

        ::InterlockedIncrement(&CPacket::g_nPendingPacket);

        packet->PostObject(dwRead);
        dwRead += m_packetSize;
        m_status = SocketStatus_Init;
    }

    unguard();
}

// L2LogD 0x0040FA60
void CServerSocket::OnCreate()
{
    guard(L"void CServerSocket::OnCreate()");

    AddTimer(Config::s_serverReportInterval, 0);
    OnRead();

    unguard();
}

// L2LogD 0x0040FAD0
void CServerSocket::OnClose()
{
    guard(L"CServerSocket::OnClose()");

    m_status = SocketStatus_Closed;
#if defined _WIN64
    ::InterlockedExchange64((LONGLONG*)&m_socket, INVALID_SOCKET);
#else
    ::InterlockedExchange((LONG*)&m_socket, INVALID_SOCKET);
#endif

    for (int i = 0; i < FileBuffers_BuffersCount; ++i)
    {
        HANDLE buffer = m_fileBuffers[i];
        if (buffer != INVALID_HANDLE_VALUE)
        {
            ::FlushFileBuffers(buffer);
            ::CloseHandle(buffer);
            m_fileBuffers[i] = INVALID_HANDLE_VALUE;
        }
    }

    if ((signed int)m_logComponent > 0)
    {
        SYSTEMTIME systemTime;
        ::GetLocalTime(&systemTime);

        wchar_t format[2048];
        wsprintfW(
            format,
            L"insert into %slog_realtime_%d(act_time, log_id, etc_num1, etc_num2) values('%d/%d/%d %d:%d:%d.%d',%d, %d, %d)\r\n",
            m_yearMonthDay,
            m_worldId,
            systemTime.wYear,
            systemTime.wMonth,
            systemTime.wDay,
            systemTime.wHour,
            systemTime.wMinute,
            systemTime.wSecond,
            systemTime.wMilliseconds,
            1305,
            m_logComponent,
            m_worldId);

        g_sqlPollingQueue.PushSQL(format);

        int error = ::WSAGetLastError();
        g_winlog.Add(LOG_NORMAL, L"CServerSocket::OnClose. servertype(%s), m_nWorld(%d), Disconnected (%x). WSAGetLastError(%d)", CServerSocket::s_serverTypes[m_logComponent], m_worldId, this, error);
    }

    in_addr addr = GetAddress();
    g_winlog.Add(LOG_NORMAL, L"Log connection closed from (%d.%d.%d.%d)", addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);

    unguard();
}

// L2LogD 0x0040F520
const wchar_t* CServerSocket::ParseLogData(const wchar_t* logMessage, const char* format, ...)
{
    guard(L"const unsigned char *ParseLogData(WCHAR* packet, const char* format, ...)");

    if (format == NULL)
    {
        unguard();
        return logMessage;
    }

    char formatToken = *format;
    const wchar_t* tokenIterator = logMessage;
    const char** outputIterator = &format;  // points to output parameters

    while (*format != '\0')
    {
        wchar_t separatorSymbol = *tokenIterator;
        ++outputIterator;
        ++format;

        wchar_t* outputParam = (wchar_t*)*outputIterator;

        const wchar_t* logMessageIterator = tokenIterator;
        if (separatorSymbol == NULL)
        {
            wcscpy(outputParam, L"NULL");
            formatToken = *format;
            tokenIterator += 1;
            continue;
        }

        size_t tokenLength = 0;
        // Looking for separator
        while (separatorSymbol != NULL)
        {
            if (separatorSymbol == ',')
            {
                break;
            }
            if (!separatorSymbol)
            {
                break;
            }
            if (separatorSymbol == '\r')
            {
                break;
            }
            if (separatorSymbol == '\n')
            {
                break;
            }
            separatorSymbol = logMessageIterator[1];
            ++logMessageIterator;
            ++tokenLength;
        }

        if (tokenLength != 0)
        {
            if (formatToken == 'd')
            {
                ::wcsncpy(outputParam, tokenIterator, tokenLength);
            }
            else
            {
                ::wcscpy(outputParam, L"'");
                ::wcsncat(outputParam, tokenIterator, tokenLength);
                ::wcscat(outputParam, L"'");
            }
            tokenIterator += (tokenLength + 1);
        }
        else
        {
            wcscpy(outputParam, L"NULL");
            tokenIterator += 1;
        }

        formatToken = *format;
    }

    unguard();

    return tokenIterator;
}

// L2LogD 0x0040F490
bool CServerSocket::CanAppend(int year, int month, int day, int hour, bool half) const
{
    if (m_fileBuffers[0] == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    if (half != m_half || m_hour != hour || m_year != year || m_month != month || m_day != day)
    {
        return false;
    }

    return true;
}

// L2LogD 0x0040F4E0
void CServerSocket::LockBuffer(int bufferIndex)
{
    ::EnterCriticalSection(&m_bufferLocks[bufferIndex]);
}

// L2LogD 0x0040F500
void CServerSocket::UnlockBuffer(int bufferIndex)
{
    ::LeaveCriticalSection(&m_bufferLocks[bufferIndex]);
}

// L2LogD 0x0040FD00
void CServerSocket::WriteLogFile(LogType logType, const wchar_t* msg)
{
    ::guard(L"void CServerSocket::WriteLogFile (LogType nLogType, WCHAR* sMsg)");

    char buffer[2174];
    memset(buffer, 0, sizeof(buffer));

    char* narrowBuff = Utils::UnicodeToMultibyte2(msg);
    sprintf(buffer, "%s", narrowBuff);
    delete[] narrowBuff;

    DWORD bytesWritten;
    switch (logType)
    {
        case LOG_IN:
            LockBuffer(FileBuffers_In);
            ::WriteFile(m_fileBuffers[FileBuffers_In], buffer, ::strlen(buffer), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_In);
            if (Config::s_makeOut == true)
            {
                LockBuffer(FileBuffers_Out);
                ::WriteFile(m_fileBuffers[FileBuffers_Out], buffer, ::strlen(buffer), &bytesWritten, 0);
                UnlockBuffer(FileBuffers_Out);
            }
            break;
        case LOG_DB:
            LockBuffer(FileBuffers_Db);
            ::WriteFile(m_fileBuffers[FileBuffers_Db], buffer, ::strlen(buffer), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Db);
            break;
        case LOG_AUDIT:
            LockBuffer(FileBuffers_Audit);
            ::WriteFile(m_fileBuffers[FileBuffers_Audit], buffer, ::strlen(buffer), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Audit);
            break;
        case LOG_ERROR:
            LockBuffer(FileBuffers_Error);
            ::WriteFile(m_fileBuffers[FileBuffers_Error], buffer, ::strlen(buffer), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Error);
            break;
        case LOG_CHAT:
            LockBuffer(FileBuffers_Chat);
            ::WriteFile(m_fileBuffers[FileBuffers_Chat], buffer, ::strlen(buffer), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_Chat);
            if (Config::s_makeOut == true)
            {
                LockBuffer(FileBuffers_ChatOut);
                ::WriteFile(m_fileBuffers[FileBuffers_ChatOut], buffer, ::strlen(buffer), &bytesWritten, 0);
                UnlockBuffer(FileBuffers_ChatOut);
            }
            break;
        default:
            LockBuffer(FileBuffers_System);
            ::WriteFile(m_fileBuffers[FileBuffers_System], buffer, ::strlen(buffer), &bytesWritten, 0);
            UnlockBuffer(FileBuffers_System);
            break;
    }

    unguard();
}

// L2LogD 0x0040FFC0
bool CServerSocket::CheckLogTimeTable(int worldId)
{
    guard(L"bool CServerSocket::CheckLogTimeTable(int nWorld)");

    if (worldId < 0)
    {
        g_winlog.Add(LOG_ERROR, L"CServerSocket CheckLogTimeTable(%d) world is below 0", worldId);  // FIXED: added
        unguard();
        return false;
    }

    g_sqlPollingQueue.PushSQL(L"EXECUTE lin_CheckLogTimeTable2 '%s', %d", m_yearMonthDay, worldId);
    g_winlog.Add(LOG_INF, L"CServerSocket::CheckLogTimeTable %s, %d", m_yearMonthDay, worldId);

    unguard();

    return true;
}

// L2LogD 0x00410250
void CServerSocket::CreateNewLogFile(int year, int month, int day, int hour, bool half)
{
    guard(L"void CServerSocket::CreateNewLogFile(int nYear, int nMonth, int nDay, int nHour, int nHalf)");

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

    wsprintfW(m_yearMonthDay, L"L%04d_%02d_%02d_", year, month, day);
    m_hour = hour;
    m_year = year;
    m_month = month;
    m_day = day;
    m_half = half;

    CheckLogTimeTable(m_worldId);

    for (int i = 0; i < (sizeof(CServerSocket::s_logCategories) / sizeof(CServerSocket::s_logCategories[0])); ++i)
    {
        FilePath& fileBufferName = m_fileNames[i];
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
            if (fileSize == 0)
            {
                ::DeleteFileW(fileBufferName.path);
            }
        }

        const wchar_t* logCategory = CServerSocket::s_logCategories[i];
        //::swprintf(fileName.path, L"log\\%s\\%04d-%02d-%02d-%02d-%02d-%s-%s%d.log", logCategory, m_year, m_month, m_day, m_hour, m_worldId, CServerSocket::s_serverTypes[m_logComponent], logCategory, m_half); FIXED
        ::swprintf(fileBufferName.path, sizeof(fileBufferName.path) / sizeof(*fileBufferName.path), L"log\\%s\\%04d-%02d-%02d-%02d-%02d-%s-%s%d.log", logCategory, m_year, m_month, m_day, m_hour, m_worldId, CServerSocket::s_serverTypes[m_logComponent], logCategory, m_half);

        ::CreateDirectoryW(L"log", NULL);

        wchar_t pathName[50];
        ::wsprintfW(pathName, L"log\\%s", logCategory);
        ::CreateDirectoryW(pathName, NULL);

        const HANDLE newFileBuffer = ::CreateFileW(fileBufferName.path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        ::wcscpy(fileBufferName.path, fileName);
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

// L2LogD 0x004104F0
void CServerSocket::Send(const char* format, ...)
{
    guard(L"void CServerSocket::Send(const char* format, ...)");

    if ((format == NULL) || (m_status == SocketStatus_Closed))
    {
        unguard();
        return;
    }

    CIOBuffer* buffer = CIOBuffer::Alloc();

    va_list va;
    va_start(va, format);
    int packetSize = PacketUtils::VAssemble(&buffer->m_Buffer[2], BUFFER_SIZE - 2, format, va);
    va_end(va);

    if (packetSize != 0)
    {
        packetSize += 2;
        buffer->m_Buffer[0] = char(packetSize & 0xFF);
        buffer->m_Buffer[1] = char((packetSize >> 8) & 0xFF);

        m_socketWriteLock.Enter(0, 0);
        buffer->m_dwSize = packetSize;
        Write(buffer);
        m_socketWriteLock.Leave(0, 0);
    }
    else
    {
        g_winlog.Add(LOG_ERROR, "%d: assemble too large packet. format %s", m_hSocket, format);
        buffer->Release();
    }

    unguard();
}

// L2LogD 0x00410620
bool CServerSocket::packet00_SendLog(CIOSocket* socket, const uint8_t* packet)
{
    guard(L"static bool LogSendLogPacket(CServerSocket* pSocket, const unsigned char* packet)");

    CServerSocket* servSocket = static_cast<CServerSocket*>(socket);

    wchar_t logMessage[0x1100u];
    memset(logMessage, 0, sizeof(logMessage));

    LogType logType;
    int serverType;
    PacketUtils::Disassemble(packet, "ddS", &serverType, &logType, sizeof(logMessage), logMessage);

    if (logType == LOG_DB)
    {
        char actTime[512];
        memset(actTime, 0, sizeof(actTime));

        char logId[64];
        memset(logId, 0, sizeof(logId));

        char actor[512];
        memset(actor, 0, sizeof(actor));

        char actorAccount[512];
        memset(actorAccount, 0, sizeof(actorAccount));

        char target[512];
        memset(target, 0, sizeof(target));

        char targetAccount[512];
        memset(targetAccount, 0, sizeof(targetAccount));

        char locationX[64];
        memset(locationX, 0, sizeof(locationX));

        char locationY[64];
        memset(locationY, 0, sizeof(locationY));

        char locationZ[64];
        memset(locationZ, 0, sizeof(locationZ));

        char etcStr1[512];
        memset(etcStr1, 0, sizeof(etcStr1));

        char etcStr2[512];
        memset(etcStr2, 0, sizeof(etcStr2));

        char etcStr3[512];
        memset(etcStr3, 0, sizeof(etcStr3));

        char etcNum1[64];
        memset(etcNum1, 0, sizeof(etcNum1));

        char etcNum2[64];
        memset(etcNum2, 0, sizeof(etcNum2));

        char etcNum3[64];
        memset(etcNum3, 0, sizeof(etcNum3));

        char etcNum4[64];
        memset(etcNum4, 0, sizeof(etcNum4));

        char etcNum5[64];
        memset(etcNum5, 0, sizeof(etcNum5));

        char etcNum6[64];
        memset(etcNum6, 0, sizeof(etcNum6));

        char etcNum7[64];
        memset(etcNum7, 0, sizeof(etcNum7));

        char etcNum8[64];
        memset(etcNum8, 0, sizeof(etcNum8));

        char etcNum9[64];
        memset(etcNum9, 0, sizeof(etcNum9));

        char etcNum10[64];
        memset(etcNum10, 0, sizeof(etcNum10));

        char actorStr[64];
        memset(actorStr, 0, sizeof(actorStr));

        char actorAccountStr[64];
        memset(actorAccountStr, 0, sizeof(actorAccountStr));

        char targetStr[64];
        memset(targetStr, 0, sizeof(targetStr));

        char targetAccountStr[64];
        memset(targetAccountStr, 0, sizeof(targetAccountStr));

        CServerSocket::ParseLogData(
            logMessage,
            "sddddddddsssddddddddddssss",
            actTime,
            logId,
            actor,
            actorAccount,
            target,
            targetAccount,
            locationX,
            locationY,
            locationZ,
            etcStr1,
            etcStr2,
            etcStr3,
            etcNum1,
            etcNum2,
            etcNum3,
            etcNum4,
            etcNum5,
            etcNum6,
            etcNum7,
            etcNum8,
            etcNum9,
            etcNum10,
            actorStr,
            actorAccountStr,
            targetStr,
            targetAccountStr);

        wchar_t sql[0x1000];
        memset(sql, 0, sizeof(sql));

        wsprintfW(
            sql,
            L"insert into %slog_realtime_%d(act_time, log_id, actor, actor_account, target, target_account, location_x, location_y, location_z, etc_str1, etc_str2, etc_str3, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10, STR_actor, STR_actor_account, STR_target, "
            L"STR_target_account) values(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\r\n",
            servSocket->m_yearMonthDay,
            servSocket->m_worldId,
            actTime,
            logId,
            actor,
            actorAccount,
            target,
            targetAccount,
            locationX,
            locationY,
            locationZ,
            etcStr1,
            etcStr2,
            etcStr3,
            etcNum1,
            etcNum2,
            etcNum3,
            etcNum4,
            etcNum5,
            etcNum6,
            etcNum7,
            etcNum8,
            etcNum9,
            etcNum10,
            actorStr,
            actorAccountStr,
            targetStr,
            targetAccountStr);

        SYSTEMTIME systemTime;
        ::GetLocalTime(&systemTime);
        if (!servSocket->CanAppend(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u))
        {
            ::EnterCriticalSection(&servSocket->m_fileLock);
            servSocket->CreateNewLogFile(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u);
            ::LeaveCriticalSection(&servSocket->m_fileLock);
        }

        // servSocket->WriteLogFile(logType, sql); FIXED
        servSocket->WriteLogFile(logType, logMessage);
        g_sqlPollingQueue.PushSQL(sql);
    }
    else if (logType == LOG_AUDIT)
    {
        char actTime[512];
        memset(actTime, 0, sizeof(actTime));

        char logId[64];
        memset(logId, 0, sizeof(logId));

        char actor[512];
        memset(actor, 0, sizeof(actor));

        char actorAccount[512];
        memset(actorAccount, 0, sizeof(actorAccount));

        char target[512];
        memset(target, 0, sizeof(target));

        char targetAccount[512];
        memset(targetAccount, 0, sizeof(targetAccount));

        char locationX[64];
        memset(locationX, 0, sizeof(locationX));

        char locationY[64];
        memset(locationY, 0, sizeof(locationY));

        char locationZ[64];
        memset(locationZ, 0, sizeof(locationZ));

        char etcStr1[512];
        memset(etcStr1, 0, sizeof(etcStr1));

        char etcStr2[512];
        memset(etcStr2, 0, sizeof(etcStr2));

        char etcStr3[512];
        memset(etcStr3, 0, sizeof(etcStr3));

        char etcNum1[64];
        memset(etcNum1, 0, sizeof(etcNum1));

        char etcNum2[64];
        memset(etcNum2, 0, sizeof(etcNum2));

        char etcNum3[64];
        memset(etcNum3, 0, sizeof(etcNum3));

        char etcNum4[64];
        memset(etcNum4, 0, sizeof(etcNum4));

        char etcNum5[64];
        memset(etcNum5, 0, sizeof(etcNum5));

        char etcNum6[64];
        memset(etcNum6, 0, sizeof(etcNum6));

        char etcNum7[64];
        memset(etcNum7, 0, sizeof(etcNum7));

        char etcNum8[64];
        memset(etcNum8, 0, sizeof(etcNum8));

        char etcNum9[64];
        memset(etcNum9, 0, sizeof(etcNum9));

        char etcNum10[64];
        memset(etcNum10, 0, sizeof(etcNum10));

        char actorStr[64];
        memset(actorStr, 0, sizeof(actorStr));

        char actorAccountStr[64];
        memset(actorAccountStr, 0, sizeof(actorAccountStr));

        char targetStr[64];
        memset(targetStr, 0, sizeof(targetStr));

        char targetAccountStr[64];
        memset(targetAccountStr, 0, sizeof(targetAccountStr));

        CServerSocket::ParseLogData(
            logMessage,
            "sddddddddsssddddddddddssss",
            actTime,
            logId,
            actor,
            actorAccount,
            target,
            targetAccount,
            locationX,
            locationY,
            locationZ,
            etcStr1,
            etcStr2,
            etcStr3,
            etcNum1,
            etcNum2,
            etcNum3,
            etcNum4,
            etcNum5,
            etcNum6,
            etcNum7,
            etcNum8,
            etcNum9,
            etcNum10,
            actorStr,
            actorAccountStr,
            targetStr,
            targetAccountStr);

        wchar_t sql[0x1000];
        memset(sql, 0, sizeof(sql));

        wsprintfW(
            sql,
            L"insert into %slog_audit_%d(act_time, log_id, actor, actor_account, target, target_account, location_x, location_y, location_z, etc_str1, etc_str2, etc_str3, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10, STR_actor, STR_actor_account, STR_target, "
            L"STR_target_account) values(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s, %s,%s,%s,%s)\r\n",
            servSocket->m_yearMonthDay,
            servSocket->m_worldId,
            actTime,
            logId,
            actor,
            actorAccount,
            target,
            targetAccount,
            locationX,
            locationY,
            locationZ,
            etcStr1,
            etcStr2,
            etcStr3,
            etcNum1,
            etcNum2,
            etcNum3,
            etcNum4,
            etcNum5,
            etcNum6,
            etcNum7,
            etcNum8,
            etcNum9,
            etcNum10,
            actorStr,
            actorAccountStr,
            targetStr,
            targetAccountStr);

        SYSTEMTIME systemTime;
        ::GetLocalTime(&systemTime);
        if (!servSocket->CanAppend(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u))
        {
            ::EnterCriticalSection(&servSocket->m_fileLock);
            servSocket->CreateNewLogFile(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u);
            ::LeaveCriticalSection(&servSocket->m_fileLock);
        }

        // servSocket->WriteLogFile(logType, sql); FIXED
        servSocket->WriteLogFile(logType, logMessage);
        g_sqlPollingQueue.PushSQL(sql);
    }
    else
    {
        SYSTEMTIME systemTime;
        ::GetLocalTime(&systemTime);
        if (!servSocket->CanAppend(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u))
        {
            ::EnterCriticalSection(&servSocket->m_fileLock);
            servSocket->CreateNewLogFile(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u);
            ::LeaveCriticalSection(&servSocket->m_fileLock);
        }

        servSocket->WriteLogFile(logType, logMessage);
    }

    unguard();
    return false;
}

// L2LogD 0x0040F610
bool CServerSocket::packet01_SetCheckStatus(CIOSocket* socket, const uint8_t* packet)
{
    guard(L"static bool SetCheckStatusPacket(CServerSocket* pSocket, const unsigned char* packet)");

    int checkStatus = 0;
    PacketUtils::Disassemble(packet, "d", &checkStatus);

    CServerSocket* servSocket = static_cast<CServerSocket*>(socket);
    servSocket->m_checkStatus = (checkStatus == 1);

    unguard();

    return false;
}
// L2LogD 0x00410F70
bool CServerSocket::packet02_CheckLogD(CIOSocket* socket, const uint8_t* packet)
{
    guard(L"static bool CheckLogDPacket(CServerSocket* pSocket, const unsigned char* packet)");

    int value = 0;
    PacketUtils::Disassemble(packet, "d", &value);

    int result = 0;
    if ((CSQLQueue::getDbSize() == 0))
    {
        result = 1;
    }
    else
    {
        int freeSpace = (CSQLQueue::getUnusedDbSize() / CSQLQueue::getDbSize()) * 100;
        result = freeSpace < 1;
    }

    CServerSocket* servSocket = static_cast<CServerSocket*>(socket);
    servSocket->Send("cd", LogD_CheckLog, result);

    unguard();

    return false;
}

// L2LogD 0x00411020
bool CServerSocket::packet03_ServerStarted(CIOSocket* socket, const uint8_t* packet)
{
    guard(L"static bool ServerStartedPacket(CServerSocket* pSocket, const unsigned char* packet)");

    int worldId = 0;
    ServerTypes serverType = ServerType_Unset;

    PacketUtils::Disassemble(packet, "dd", &worldId, &serverType);
    if (serverType < ServerType_AuthD)
    {
        unguard();
        return false;
    }

    CServerSocket* servSocket = static_cast<CServerSocket*>(socket);
    SYSTEMTIME systemTime;
    ::GetLocalTime(&systemTime);
    if (!servSocket->CanAppend(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u))
    {
        ::EnterCriticalSection(&servSocket->m_fileLock);

        servSocket->m_worldId = worldId;
        servSocket->m_logComponent = serverType;
        servSocket->CreateNewLogFile(systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute >= 30u);

        ::LeaveCriticalSection(&servSocket->m_fileLock);
    }

    wchar_t format[0x1000];
    wsprintfW(
        format,
        L"insert into %slog_realtime_%d(act_time, log_id, etc_num1, etc_num2) values('%d/%d/%d %d:%d:%d.%d',%d, %d, %d)\r\n",
        servSocket->m_yearMonthDay,
        worldId,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour,
        systemTime.wMinute,
        systemTime.wSecond,
        systemTime.wMilliseconds,
        1306,
        serverType,
        worldId);

    g_sqlPollingQueue.PushSQL(format);
    in_addr remoteAddr = servSocket->GetAddress();
    g_winlog.Add(LOG_NORMAL, L"Log connection from (%d.%d.%d.%d)", remoteAddr.S_un.S_un_b.s_b1, remoteAddr.S_un.S_un_b.s_b2, remoteAddr.S_un.S_un_b.s_b3, remoteAddr.S_un.S_un_b.s_b4);

    unguard();

    return false;
}

// L2LogD 0x0040F690
bool CServerSocket::packet04_DummyPacket(CIOSocket* /*socket*/, const uint8_t* /*packet*/)
{
    guard(L"static bool DummyPacket(CServerSocket* pSocket, const unsigned char* packet)");
    unguard();
    return false;
}
