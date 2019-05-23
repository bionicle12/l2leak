#include <WinSock2.h>

#include "l2core/utils/dbg/CExceptionInit.h"

#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CoreDump.h"

#if defined(L2CACHED)
#include "cached/config/Config.h"
#elif defined(L2LOGD)
#include "l2logd/config/Config.h"
#elif defined(L2NPC)
#include "l2npc/config/Config.h"
#else
#error
#endif

#include <cstdio>
#include <cstring>
#include <cwchar>

CExceptionInit g_exeptionHalder;  // L2LogD 0x00441BB0, L2CacheD 0x00AEA210

LPTOP_LEVEL_EXCEPTION_FILTER CExceptionInit::s_oldFilter;  // L2LogD 0x00441960, L2CacheD 0x00AEA050, L2NPC 0x005217B0
wchar_t CExceptionInit::s_logPath[MAX_PATH];               // L2LogD 0x00441968, L2CacheD 0x00AD5610, L2NPC 0x005217B8
time_t CExceptionInit::s_startTime;                        // L2LogD 0x00441B70, L2CacheD 0x00AEA158, L2NPC 0x005219C0
CRITICAL_SECTION CExceptionInit::s_lock;                   // L2LogD 0x00441B74, L2CacheD 0x00AD5818, L2NPC 0x005219C4
int CExceptionInit::s_errorReported;                       // L2LogD 0x00441B90, L2CacheD 0x00AEA20C, L2NPC 0x0217C25C

// L2LogD 0x00403670, L2CacheD 0x004109D0, L2NPC 0x004109D0
CExceptionInit::CExceptionInit()
{
    ::InitializeCriticalSection(&CExceptionInit::s_lock);

    if (!::GetModuleFileNameW(0, CExceptionInit::s_logPath, MAX_PATH))
    {
        CExceptionInit::s_logPath[0] = L'\0';
    }

    wchar_t* exeName = Utils::GetFileName(CExceptionInit::s_logPath);

    // Unused
    wchar_t buffer[MAX_PATH];
    lstrcpyW(buffer, L"Unknown");

    memset(buffer, 0, sizeof(buffer));
    lstrcpyW(buffer, exeName);
    wchar_t* extension = wcsrchr(buffer, '.');
    if (extension)
    {
        *extension = L'\0';
    }
    //

    lstrcpyW(exeName, L"LinError.txt");
    CExceptionInit::s_startTime = std::time(NULL);
    CExceptionInit::InstallTopLevelFilter();
}

// L2LogD 0x00420960, L2CacheD 0x0049D7E0
CExceptionInit::~CExceptionInit()
{
    CExceptionInit::RestoreTopLevelFilter();
    ::DeleteCriticalSection(&CExceptionInit::s_lock);
}

// L2LogD 0x00403630, L2CacheD 0x00410990, L2NPC 0x00410990
void CExceptionInit::InstallTopLevelFilter()
{
    CExceptionInit::s_oldFilter = ::SetUnhandledExceptionFilter(CExceptionInit::RecordExceptionInfo);
}

// L2LogD 0x00403650, L2CacheD 0x004109B0, L2NPC 0x004109B0
void CExceptionInit::RestoreTopLevelFilter()
{
    if (CExceptionInit::s_oldFilter != NULL)
    {
        ::SetUnhandledExceptionFilter(CExceptionInit::s_oldFilter);
    }
}

// L2LogD 0x00402940, L2CacheD 0x0040FB10
bool CExceptionInit::SendFile(SOCKET socket, const wchar_t* fileToSend)
{
    // FIXED: previously method was void, now bool

    HANDLE fileHandle = ::CreateFileW(fileToSend, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        // return true; // FIXED
        return false;
    }

    char buffer[0x2000];
    DWORD bytesRead;
    if (::ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, 0) == TRUE)
    {
        while (bytesRead != 0)
        {
            if (::send(socket, buffer, bytesRead, 0) <= 0)
            {
                return false;
            }
            if (::ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, 0) == FALSE)
            {
                break;
            }
        }
    }

    ::CloseHandle(fileHandle);

    return true;
}

/*!
 * \brief CExceptionInit::sendMail
 * \param mailTo - recepiens, separated by null-characted '\0'
 * \return
 */
// FIXED: For CacheD, SendMail is taken from LogD
// L2LogD 0x00402A00, L2CacheD 0x0040FBE0
bool CExceptionInit::SendMail(const char* mailTo, const char* mailServer, const char* mailFrom, const wchar_t* errorLogPath)
{
    WSAData wsaData;
    if (::WSAStartup(WINSOCK_VERSION, &wsaData))
    {
        return false;
    }

    SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socket == INVALID_SOCKET)
    {
        ::WSACleanup();
        return false;
    }

    int optval = 5000;
    int sockOptRes = ::setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&optval, sizeof(optval));
    if (sockOptRes == SOCKET_ERROR)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    optval = 5000;
    sockOptRes = ::setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&optval, sizeof(optval));
    if (sockOptRes == SOCKET_ERROR)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    sockaddr_in name;
    name.sin_family = SOCK_DGRAM;
    name.sin_addr.s_addr = 0;
    name.sin_port = 0;
    if (::bind(socket, (const struct sockaddr*)&name, sizeof(name)) == SOCKET_ERROR)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    name.sin_family = SOCK_DGRAM;

    if (mailServer[0] < '0' || '9' < mailServer[0])  // FIXME: isalpha/isnum
    {
        // mailFrom is hostname, not ip
        hostent* host = gethostbyname(mailServer);
        if (host == NULL)
        {
            ::closesocket(socket);
            ::WSACleanup();
            return false;
        }
        memcpy(&name.sin_addr, *(const void**)host->h_addr_list, host->h_length);
        ::inet_ntoa(name.sin_addr);
    }
    else
    {
        // mailFrom is ip
        name.sin_addr.s_addr = ::inet_addr(mailServer);
    }

    name.sin_port = htons(25u);
    if (::connect(socket, (const struct sockaddr*)&name, 16) == SOCKET_ERROR)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    char buf[0x800];
    ::recv(socket, buf, sizeof(buf), 0);

    char header[256];
    ::sprintf(header, "HELO %s\r\n", Config::s_mailServer);
    if (::send(socket, header, strlen(header), 0) <= 0)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    char mailFromBuff[256];
    ::recv(socket, mailFromBuff, sizeof(mailFromBuff), 0);
    ::sprintf(mailFromBuff, "MAIL From: <%s>\r\n", mailFrom);
    if (::send(socket, mailFromBuff, strlen(mailFromBuff), 0) <= 0)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    ::recv(socket, buf, sizeof(buf), 0);
    while (*mailTo)
    {
        char mailToBuff[256];
        ::sprintf(mailToBuff, "RCPT To: <%s>\r\n", mailTo);
        int rcptLen = ::strlen(mailToBuff);
        if (::send(socket, mailToBuff, rcptLen, 0) <= 0)
        {
            ::closesocket(socket);
            ::WSACleanup();
            return false;
        }
        ::recv(socket, buf, sizeof(buf), 0);
        mailTo += ::strlen(mailTo) + 1;
    }

    const char data[] = "DATA\r\n";
    if (::send(socket, data, ::strlen(data), 0) <= 0)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    ::recv(socket, buf, sizeof(buf), 0);

    sockaddr_in localAddress;
    memset(&localAddress, 0, sizeof(localAddress));
    int namelen = sizeof(localAddress);

    ::getsockname(socket, (sockaddr*)&localAddress, &namelen);
    char pcName[16];
    DWORD pcNameSize = sizeof(pcName);
    ::GetComputerNameA(pcName, &pcNameSize);
    std::time_t currentTime = std::time(NULL);
    const char* now = Utils::TimeToStr(&currentTime);

    char subjectTemplate[256];
    ::sprintf(subjectTemplate, "Subject: LogD [%d][%s](%d.%d.%d.%d) crashed at %s\r\n", 1, pcName, localAddress.sin_addr.S_un.S_un_b.s_b1, localAddress.sin_addr.S_un.S_un_b.s_b2, localAddress.sin_addr.S_un.S_un_b.s_b3, localAddress.sin_addr.S_un.S_un_b.s_b4, now);

    if (::send(socket, subjectTemplate, strlen(subjectTemplate), 0) <= 0)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    if (!CExceptionInit::SendFile(socket, errorLogPath))
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    const char newLine[] = "\r\n.\r\n";
    if (::send(socket, newLine, ::strlen(newLine), 0) <= 0)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    ::recv(socket, buf, sizeof(buf), 0);
    const char quit[] = "QUIT\r\n";
    if (::send(socket, quit, ::strlen(quit), 0) <= 0)
    {
        ::closesocket(socket);
        ::WSACleanup();
        return false;
    }

    ::recv(socket, buf, sizeof(buf), 0);

    closesocket(socket);
    ::WSACleanup();

    return true;
}

// L2LogD 0x00403540, L2CacheD 0x004108A0, L2NPC 0x0041D110
LONG WINAPI CExceptionInit::RecordExceptionInfo(struct _EXCEPTION_POINTERS* exceptionInfo)
{
    static bool bBeenHere = false;
    if (bBeenHere)
    {
        if (CExceptionInit::s_oldFilter)
        {
            return CExceptionInit::s_oldFilter(exceptionInfo);
        }
        return EXCEPTION_CONTINUE_SEARCH;
    }

    bBeenHere = true;

    // if ( !CExceptionInit::s_errorReported  && (exceptionInfo->ExceptionRecord->ExceptionCode !=
    // ERR_NO_DISK_SPACE )) // WinXP only
    if (!CExceptionInit::s_errorReported)  // FIXED
    {
        ::EnterCriticalSection(&CExceptionInit::s_lock);

        CoreDump::CreateReport(exceptionInfo);
        if (Config::s_mailServer)
        {
#if defined(L2LOGD)
            CExceptionInit::SendMail("narcasse@ncsoft.net", Config::s_mailServer, "l2logd@ncsoft.co.kr", CExceptionInit::s_logPath);
#elif defined(L2CACHED)
            // FIXED: taken from LogD
            CExceptionInit::SendMail("narcasse@ncsoft.net", Config::s_mailServer, "l2cached@ncsoft.co.kr", CExceptionInit::s_logPath);
#elif defined(L2NPC)
            CExceptionInit::SendMail("narcasse@ncsoft.net", Config::s_mailServer, "l2npc@ncsoft.co.kr", CExceptionInit::s_logPath);
#else

#error "Unhandled!";
#endif
        }

        ::LeaveCriticalSection(&CExceptionInit::s_lock);
    }

    if (CExceptionInit::s_oldFilter)
    {
        return CExceptionInit::s_oldFilter(exceptionInfo);
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

// L2LogD 0x00403760, L2CacheD 0x00410AE0
void CExceptionInit::LogException(const wchar_t* format, ...)
{
    if (CExceptionInit::s_errorReported)
    {
        return;
    }

    ::EnterCriticalSection(&CExceptionInit::s_lock);

    SYSTEMTIME now;
    ::GetLocalTime(&now);

    HANDLE fileHandle = ::CreateFileW(CExceptionInit::s_logPath, GENERIC_WRITE | GENERIC_READ, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        ::LeaveCriticalSection(&CExceptionInit::s_lock);
        return;
    }

#if defined _WIN64
    LARGE_INTEGER offset = {0};
    ::SetFilePointerEx(fileHandle, offset, 0, FILE_END);
#else
    ::SetFilePointer(fileHandle, FILE_BEGIN, 0, FILE_END);
#endif

    DWORD currentThread = ::GetCurrentThreadId();
    wchar_t bufferW[0x4000];

    int len = _snwprintf(bufferW, 0x4000u, L"[(%d) %04d/%02d/%02d %02d:%02d:%02d]: ", currentThread, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
    if (len >= 0)
    {
        char* buffer = Utils::UnicodeToMultibyte_WithoutAllocation(bufferW);

        DWORD bytesWritten;
        ::WriteFile(fileHandle, buffer, strlen(buffer), &bytesWritten, 0);

        va_list va;
        va_start(va, format);
        len = _vsnwprintf(bufferW, 0x4000u, format, va);
        va_end(va);

        if (len >= 0)
        {
            for (int i = 0; i < len; i += 2)
            {
                char* newLine = (char*)std::memchr(&bufferW[i], '\n', len - i);
                if (newLine == NULL)
                {
                    break;
                }

                if (len < 0x4000)
                {
                    ++len;
                }

                // inserting \r near to  \n
                int distanse = newLine - (const char*)bufferW;
                memcpy(newLine + 1, newLine, len - distanse - 1);
                i = distanse + 2;
                *newLine = '\r';
            }

            const char* narrowBuff = Utils::UnicodeToMultibyte_WithoutAllocation(bufferW);
            ::WriteFile(fileHandle, narrowBuff, strlen(narrowBuff), &bytesWritten, 0);
        }
    }

    ::CloseHandle(fileHandle);

    ::LeaveCriticalSection(&CExceptionInit::s_lock);
}

// L2LogD 0x00403920, L2CacheD 0x00410CC0
int CExceptionInit::ExceptionFilter(EXCEPTION_POINTERS* ex)
{
    ::EnterCriticalSection(&CExceptionInit::s_lock);
    CoreDump::CreateReport(ex);
    ::LeaveCriticalSection(&CExceptionInit::s_lock);
    return EXCEPTION_EXECUTE_HANDLER;
}

// L2LogD 0x00403970, L2CacheD 0x00410D10
void CExceptionInit::SendExceptionLog(bool fatal)
{
    if (CExceptionInit::s_errorReported)
    {
        return;
    }

    ::EnterCriticalSection(&CExceptionInit::s_lock);

    if (Config::s_mailServer != NULL)
    {
#if defined(L2LOGD)
        CExceptionInit::SendMail("narcasse@ncsoft.net", Config::s_mailServer, "l2logd@ncsoft.co.kr", CExceptionInit::s_logPath);
#elif defined(L2CACHED)
        // FIXED: taken from LogD
        CExceptionInit::SendMail("narcasse@ncsoft.net", Config::s_mailServer, "l2cached@ncsoft.co.kr", CExceptionInit::s_logPath);
#elif defined(L2NPC)
        CExceptionInit::SendMail("narcasse@ncsoft.net", Config::s_mailServer, "l2npc@ncsoft.co.kr", CExceptionInit::s_logPath);
#else
#error "Unhandled!";
#endif
    }

    ::LeaveCriticalSection(&CExceptionInit::s_lock);

    if (fatal)
    {
        CExceptionInit::s_errorReported = true;
        ::ExitProcess(0);
    }
}
