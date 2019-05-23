#include "l2auth/utils/Utils.h"

#include "l2auth/config/Config.h"
#include "l2auth/logger/CLogdFilelog.h"
#include "l2auth/network/CLogSocket.h"
#include "l2auth/ui/CLog.h"
#include "l2auth/utils/CExceptionInit.h"
#include "l2auth/utils/SendMail.h"
#include "l2auth/utils/Unused.h"
#include "l2core/logger/ServerTypes.h"
#include "l2core/network/packets/LogDPackets.h"

#include <cctype>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

namespace Utils
{

// L2AuthD 0x0043ADF4
int Utils::StdAccount(char* accName)
{
    auth_guard;

    accName[14] = 0;
    int tmp = ::strlen(accName);
    int length_ = tmp;
    if (tmp > 0)
    {
        *accName = std::toupper(*accName);
        for (int i = 1;; ++i)
        {
            tmp = i;
            if (i >= length_)
                break;
            if (accName[i] == ' ')
            {
                tmp = (int)&accName[i];
                accName[i] = 0;
                return tmp;
            }
            accName[i] = std::tolower(accName[i]);
        }
    }
    return tmp;

    auth_vunguard;
    return -1;
}

// L2AuthD 0x0043B7FE
time_t Utils::ConvertSQLToTome(const TIMESTAMP_STRUCT& timeStamp, tm* tmStruct)
{
    tmStruct->tm_sec = timeStamp.second;
    tmStruct->tm_min = timeStamp.minute;
    tmStruct->tm_hour = timeStamp.hour;
    tmStruct->tm_mday = timeStamp.day;
    tmStruct->tm_mon = timeStamp.month - 1;
    tmStruct->tm_year = timeStamp.year - 1900;
    tmStruct->tm_isdst = 0;
    return ::mktime(tmStruct);
}

// L2AuthD 0x0043AFA2
void Utils::WriteLogD(LogId logId, char* accName, in_addr connectedIP, int payStat, int age, int a6, int zero, int variant, int uid)
{
    auth_guard;

    WCHAR accNameW[15];
    SYSTEMTIME systemTime;

    if (g_Config.gameID & 8)
    {
        ::GetLocalTime(&systemTime);
        if (strlen(accName) > 14)
        {
            accName[14] = '\0';
        }

        int wSize = Utils::AnsiToUnicode(accName, 15, accNameW);
        UNUSED(wSize);
        accNameW[14] = 0;
        if (LOBYTE(g_Config.useLogD) && !CLogSocket::isReconnecting && CLogSocket::created)
        {
            wchar_t bufferW[1024];
            memset(bufferW, 0, sizeof(bufferW));
            switch (logId)
            {
                case LogId_Authed:
                    swprintf(
                        bufferW,
                        sizeof(bufferW) / sizeof(*bufferW),  // FIXED
                        L"%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        L",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,%d,%d,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Authed),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        variant,  // users
                        zero,
                        accNameW);
                    break;
                case LogId_Login:
                    swprintf(
                        bufferW,
                        sizeof(bufferW) / sizeof(*bufferW),  // FIXED
                        L"%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        L",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,%d,%d,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Login),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        variant,  // logged users
                        zero,
                        accNameW);
                    break;
                case LogId_Logout:
                    swprintf(
                        bufferW,
                        sizeof(bufferW) / sizeof(*bufferW),  // FIXED
                        L"%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        L",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,%d,%d,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Logout),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        variant,  // total time
                        zero,
                        accNameW);
                    break;
                case LogId_Leaveworld2:
                    swprintf(
                        bufferW,
                        sizeof(bufferW) / sizeof(*bufferW),  // FIXED
                        L"%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        L",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,,,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Leaveworld2),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        accNameW);
                    break;
            }
            CLogSocket::s_lock.ReadLock();
            // g_LogDSocket->Send("cddS", LogD_Send, ServerType_AuthD, 6, bufferW);
            g_LogDSocket->Send("cddS", LogD_Send, ServerType_AuthD, LOG_DB, bufferW);  // FIXED, LOG_DB = 7

            CLogSocket::s_lock.ReadUnlock();
        }
        else
        {
            char buffer[2048];
            memset(buffer, 0, sizeof(buffer));
            switch (logId)
            {
                case LogId_Authed:
                    sprintf(
                        buffer,
                        "%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        ",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,%d,%d,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Authed),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        variant,
                        zero,
                        accName);
                    break;
                case LogId_Login:
                    sprintf(
                        buffer,
                        "%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        ",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,%d,%d,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Login),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        variant,
                        zero,
                        accName);
                    break;
                case LogId_Logout:
                    sprintf(
                        buffer,
                        "%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        ",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,%d,%d,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Logout),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        variant,
                        zero,
                        accName);
                    break;
                case LogId_Leaveworld2:
                    sprintf(
                        buffer,
                        "%02d/%02d/%04d %02d:%02d:%02d.%03d "
                        ",%d,,%d,,,,,,%d.%d.%d.%d,,,%d,%d,%d,,,,,,,,,%s,,,\r\n",
                        systemTime.wMonth,
                        systemTime.wDay,
                        systemTime.wYear,
                        systemTime.wHour,
                        systemTime.wMinute,
                        systemTime.wSecond,
                        systemTime.wMilliseconds,
                        static_cast<int>(LogId_Leaveworld2),
                        uid,
                        connectedIP.S_un.S_un_b.s_b1,
                        connectedIP.S_un.S_un_b.s_b2,
                        connectedIP.S_un.S_un_b.s_b3,
                        connectedIP.S_un.S_un_b.s_b4,
                        payStat,
                        age,
                        a6,
                        accName);
                    break;
            }
            buffer[sizeof(buffer) - 1] = 0;
            g_logdfilelog.AddLog(LOG_INF, "%s", buffer);
        }
    }

    auth_vunguard;
}

// L2AuthD 0x0043B6A8
int Utils::AnsiToUnicode(const char* multiByteStr, int, wchar_t* wideCharStr)
{
    int size = ::MultiByteToWideChar(0, 0, multiByteStr, -1, 0, 0);
    ::MultiByteToWideChar(0, 0, multiByteStr, -1, wideCharStr, size);
    wideCharStr[size - 1] = 0;
    return size;
}

// L2AuthD 0x0043B878
bool Utils::CheckAccount(char* accName)
{
    auth_guard;

    bool result;
    if (accName != NULL)
    {
        if (std::isalpha(*accName))
        {
            for (int i = 1; i <= 14; ++i)
            {
                if (accName[i] == '\0')
                {
                    return true;
                }
                if (!std::isalpha(accName[i]) && !std::isdigit(accName[i]))
                {
                    return false;
                }
            }
            result = false;
        }
        else
        {
            result = false;
        }
    }
    else
    {
        result = false;
    }
    return result;

    auth_vunguard;
    return false;
}

// L2AuthD 0x0043B9BA
bool Utils::IsValidNumeric(char* str, int size)
{
    if (str && size > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                return false;
            }
        }
        return true;
    }

    return false;
}

// L2AuthD 0x0043BA17
bool Utils::CheckDiskSpace(LPCSTR lpDirectoryName, uint64_t limit)
{
    ULARGE_INTEGER TotalNumberOfFreeBytes;
    if (::GetDiskFreeSpaceExA(lpDirectoryName, 0, 0, &TotalNumberOfFreeBytes))
    {
        if (limit <= TotalNumberOfFreeBytes.QuadPart)
        {
            return true;
        }

        char errorMessage[1024];
        sprintf(errorMessage, "Insufficient FreeSpace!!!!, %s", lpDirectoryName);
        if (g_Config.mailTo && g_Config.mailFrom)
        {
            g_MailService.SendMessageA(g_Config.mailTo, "AuthD Insufficient FreeSpace", errorMessage);
        }
        g_winlog.AddLog(LOG_NORMAL, errorMessage);
    }
    else
    {
        int errorCode = ::GetLastError();
        g_winlog.AddLog(LOG_ERROR, "CheckDiskFreeSpace ErrorCode %d", errorCode);
    }

    return false;
}

const char* getFileName(const char* str)
{
    const char* backSlash = ::strrchr(str, '\\');
    if (backSlash != NULL)
    {
        return backSlash + 1;
    }

    return str;
}

}  // namespace Utils
