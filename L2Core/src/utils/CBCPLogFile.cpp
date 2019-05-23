#include "l2core/utils/CBCPLogFile.h"

#if defined(L2LOGD)

#include "l2logd/config/Config.h"

#include "l2core/db/CSQLQueue.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <cstring>
#include <wchar.h>

CBCPLogFile g_bcpFiles[10];       // L2LogD 0x019D6998
int CBCPLogFile::s_worldIds[10];  // L2LogD 0x00455C20

CRITICAL_SECTION CBCPLogFile::s_lock;  // L2LogD 0x019D6970

// L2LogD 0x00407800
CBCPLogFile::CBCPLogFile()
    : m_slot(0)
    , field_1(0)
{
    guard(L"CBCPLogFile::CBCPLogFile()");

    ::InitializeCriticalSection(&CBCPLogFile::s_lock);

    memset(m_dirPath, 0, sizeof(m_dirPath));

    // To be moved to Init, since constructor is called during static object initialization, where runtime might not be ready yet
    CBCPLogFile::CheckFmtFile();

    m_slot = 0;

    unguard();
}

// L2LogD 0x00406CF0
CBCPLogFile::~CBCPLogFile()
{
    guard(L"CBCPLogFile::~CBCPLogFile()");

    ::DeleteCriticalSection(&CBCPLogFile::s_lock);

    unguard();
}

// L2LogD 0x00403D90
void CBCPLogFile::Job(int bcpSlot)
{
    CBCPLogFile& bcpFile = g_bcpFiles[bcpSlot];
    bcpFile.Init(bcpSlot);

    wchar_t chatDirPath[512];
    memset(chatDirPath, 0, sizeof(chatDirPath));

    wchar_t inDirPath[512];
    memset(inDirPath, 0, sizeof(inDirPath));

    wchar_t currDirectory[512];
    memset(currDirectory, 0, sizeof(currDirectory));

    ::GetCurrentDirectoryW(sizeof(currDirectory), currDirectory);
    ::wsprintfW(chatDirPath, L"%s\\log\\chat\\", currDirectory);
    ::wsprintfW(inDirPath, L"%s\\log\\in\\", currDirectory);

    while (true)
    {
        bcpFile.InsertLogFiles(chatDirPath);
        bcpFile.InsertLogFiles(inDirPath);

        uint32_t interval = Config::s_BCPLogFileInterval;
        uint32_t threadId = ::GetCurrentThreadId();
        g_winlog.Add(LOG_INF, L"[%d]Sleep %d milliseconds", threadId, interval);

        ::Sleep(interval);
    }
}

// L2LogD 0x00406D20
bool CBCPLogFile::Init(int slot)
{
    guard(L"bool CBCPLogFile::Init(int nSlot)");

    m_slot = slot;

    // CBCPLogFile::CheckFmtFile();  // To be moved from constructor

    unguard();

    return true;
}

// L2LogD 0x00406EB0
bool CBCPLogFile::CheckFmtFile()
{
    ::guard(L"CBCPLogFile::CheckFmtFile()");

    ::EnterCriticalSection(&CBCPLogFile::s_lock);

    WIN32_FIND_DATAW findFileData;  // [sp+1018h] [bp-250h]@1
    HANDLE logDataFile = ::FindFirstFileW(L"log_data.fmt", &findFileData);
    if (logDataFile == INVALID_HANDLE_VALUE)
    {
        HANDLE newLogDataFile = ::CreateFileW(L"log_data.fmt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (newLogDataFile != INVALID_HANDLE_VALUE)
        {
            // clang-format off
            char buffer []= "8.0\r\n"
                     "27\r\n"
                     "1       SQLCHAR	      0       50      \",\"                       1     act_time           \"\"\r\n"
                     "2       SQLCHAR       0       50      \",\"                       2     log_id             \"\"\r\n"
                     "3       SQLCHAR       0       50      \",\"                       3     actor              \"\"\r\n"
                     "4       SQLCHAR       0       50      \",\"                       4     actor_account      \"\"\r\n"
                     "5       SQLCHAR       0       50      \",\"                       5     target             \"\"\r\n"
                     "6       SQLCHAR       0       50      \",\"                       6     target_account     \"\"\r\n"
                     "7       SQLCHAR       0       50       \",\"                       7     location_x         \"\"\r\n"
                     "8       SQLCHAR       0       50       \",\"                       8     location_y         \"\"\r\n"
                     "9       SQLCHAR       0       50       \",\"                       9     location_z         \"\"\r\n"
                     "10      SQLCHAR       0       50      \",\"                       10    etc_str1           Korean_Wansung_CI_AS\r\n"
                     "11      SQLCHAR       0       50      \",\"                       11    etc_str2           Korean_Wansung_CI_AS\r\n"
                     "12      SQLCHAR       0       50      \",\"                       12    etc_str3           Korean_Wansung_CI_AS\r\n"
                     "13      SQLCHAR       0       50       \",\"                       13    etc_num1           \"\"\r\n"
                     "14      SQLCHAR       0       50       \",\"                       14    etc_num2           \"\"\r\n"
                     "15      SQLCHAR       0       50       \",\"                       15    etc_num3           \"\"\r\n"
                     "16      SQLCHAR       0       50       \",\"                       16    etc_num4           \"\"\r\n"
                     "17      SQLCHAR       0       50       \",\"                       17    etc_num5           \"\"\r\n"
                     "18      SQLCHAR       0       50       \",\"                       18    etc_num6           \"\"\r\n"
                     "19      SQLCHAR       0       50       \",\"                       19    etc_num7           \"\"\r\n"
                     "20      SQLCHAR       0       50       \",\"                       20    etc_num8           \"\"\r\n"
                     "21      SQLCHAR       0       50       \",\"                       21    etc_num9           \"\"\r\n"
                     "22      SQLCHAR       0       50       \",\"                    22    etc_num10          \"\"\r\n"
                     "23       SQLCHAR       0       50      \",\"                       23     STR_actor              Korean_Wansung_CI_AS\r\n"
                     "24       SQLCHAR       0       50      \",\"                       24     STR_actor_account      Korean_Wansung_CI_AS\r\n"
                     "25       SQLCHAR       0       50      \",\"                       25     STR_target             Korean_Wansung_CI_AS\r\n"
                     "26       SQLCHAR       0       50      \",\"                       26     STR_target_account     Korean_Wansung_CI_AS\r\n"
                     "27       SQLCHAR       0       50      \"\\r\\n\"                  27     item_id     \"\"\r\n";
            // clang-format on

            DWORD bytesWritten;
            ::WriteFile(newLogDataFile, buffer, strlen(buffer), &bytesWritten, 0);
            ::FlushFileBuffers(newLogDataFile);
            ::CloseHandle(newLogDataFile);
        }
    }
    else
    {
        ::FindClose(logDataFile);
    }

    HANDLE chatDataFile = ::FindFirstFileW(L"chat_data.fmt", &findFileData);
    if (chatDataFile == INVALID_HANDLE_VALUE)
    {
        HANDLE newChatDataFile = ::CreateFileW(L"chat_data.fmt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (newChatDataFile != INVALID_HANDLE_VALUE)
        {
            // clang-format off
            char buffer[] = "8.0\r\n"
                    "10\r\n"
                    "1       SQLCHAR	      0       50      \",\"                       1     act_time           \"\"\r\n"
                    "2       SQLCHAR       0       50      \",\"                       2     log_id             \"\"\r\n"
                    "3       SQLCHAR       0       50      \",\"                       3     actor              \"\"\r\n"
                    "4       SQLCHAR       0       50      \",\"                       4     target             \"\"\r\n"
                    "5       SQLCHAR       0       50       \",\"                       5     location_x         \"\"\r\n"
                    "6       SQLCHAR       0       50       \",\"                       6     location_y         \"\"\r\n"
                    "7       SQLCHAR       0       50       \",\"                       7     location_z         \"\"\r\n"
                    "8      SQLCHAR       0       50      \",\"                       8    say           Korean_Wansung_CI_AS\r\n"
                    "9       SQLCHAR       0       50      \",\"                       9     STR_actor              Korean_Wansung_CI_AS\r\n"
                    "10       SQLCHAR       0       50      \"\\r\\n\"                  10     STR_target             Korean_Wansung_CI_AS\r\n";
            // clang-format on

            DWORD bytesWritten = 0;
            ::WriteFile(newChatDataFile, buffer, strlen(buffer), &bytesWritten, 0);
            ::FlushFileBuffers(newChatDataFile);
            ::CloseHandle(newChatDataFile);
        }
    }
    else
    {
        ::FindClose(chatDataFile);
    }
    ::LeaveCriticalSection(&CBCPLogFile::s_lock);
    unguard();

    return true;
}

// L2LogD 0x00406D50
int CBCPLogFile::BulkInsert(const wchar_t* /*logCategory*/, const wchar_t* filePath, const wchar_t* logTableName)
{
    guard(L"int CBCPLogFile::BulkInsert(WCHAR *szInOut, WCHAR *szFilePath, WCHAR *szDB)");

    DWORD startTime = ::GetTickCount();

    wchar_t sqlQuery[512];
    memset(sqlQuery, 0, sizeof(sqlQuery));

    const wchar_t executeInsert[] = L"EXECUTE lin_BulkInsert '%s', '%s'";
    wsprintfW(sqlQuery, executeInsert, logTableName, filePath);

    g_winlog.Add(LOG_INF, L"SQL(%s)", sqlQuery);

    SQLLEN length = -1;
    DBConn dbConn;
    int executionResult = 0;
    dbConn.BindNullable(&executionResult, &length);
    if (dbConn.Execute(executeInsert, logTableName, filePath))
    {
        dbConn.Fetch();
    }

    DWORD endTime = ::GetTickCount();
    g_winlog.Add(LOG_INF, L"BULK INSERT (%d) seconds, nRet(%d)", (endTime - startTime) / 1000, executionResult);

    unguard();

    return executionResult;
}

// L2LogD 0x00407500
bool CBCPLogFile::GetMaxFileNo(wchar_t* file, wchar_t* clearFileName, int* maxIndex)
{
    ::guard(L"bool CBCPLogFile::GetMaxFileNo(WCHAR* szFile, WCHAR* szFilePre, int& nMax)");

    // FIXME: crazy logic. Might have tons of bugs, to be rewritten

    *maxIndex = 0;

    wchar_t* fileNameTail = wcsstr(file, L".log");  // find .log, and then find back (left) till meet file index
    if (fileNameTail == NULL)
    {
        wcscpy(clearFileName, file);
        unguard();
        return true;
    }

    if (*fileNameTail != '\0')
    {
        while (1)
        {
            wchar_t prevSymbol = *(fileNameTail - 1);
            if (prevSymbol < '0' || prevSymbol > '9')  //  FIXME: doesn't work with numbers bigger then 9
            {
                break;
            }

            --fileNameTail;
            if (*fileNameTail == '\0')
            {
                break;
            }
        }
        *fileNameTail = 0;  // changes "file" variable as well - trims string till found number (exclusivly)
    }

    *fileNameTail = 0;
    wcscpy(clearFileName, file);

    wchar_t fileName[256];
    wcscpy(fileName, clearFileName);
    wcscat(fileName, L"*.log");

    WIN32_FIND_DATAW findFileData;
    HANDLE fileHandle = ::FindFirstFileW(fileName, &findFileData);
    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        int newMax = 0;
        wchar_t foundFileName[256];

        do
        {
            size_t increment = 0;
            wcscpy(foundFileName, findFileData.cFileName);

            wchar_t* foundFileNameChanger = wcsstr(foundFileName, L".log");
            wchar_t fileIndexString[8];
            memset(fileIndexString, 0, sizeof(fileIndexString));

            for (; foundFileNameChanger != NULL; ++increment)  //  FIXME: doesn't work with numbers bigger then 9
            {
                wchar_t fileIndex = *(foundFileNameChanger - 1);
                if (fileIndex < '0')
                {
                    break;
                }
                if (fileIndex > '9')
                {
                    break;
                }
                --foundFileNameChanger;
            }

            wcsncpy(fileIndexString, foundFileNameChanger, increment);
            if (wcslen(fileIndexString) != 0)
            {
                newMax = _wtol(fileIndexString);
            }

            if (newMax > *maxIndex)
            {
                *maxIndex = newMax;
            }

        } while (::FindNextFileW(fileHandle, &findFileData));

        ::FindClose(fileHandle);
    }

    unguard();

    return true;
}

// L2LogD 0x004076B0
bool CBCPLogFile::CheckLogTimeTable(int year, int month, int day, int world)
{
    guard(L"bool CBCPLogFile::CheckLogTimeTable(int nYear, int nMonth, int nDay, int nWorld)");

    if (world < 0)
    {
        g_winlog.Add(LOG_ERROR, L"CBCPLogFile CheckLogTimeTable(%d) world is below 0", world);
        unguard();
        return false;
    }

    wchar_t dateStr[256];
    memset(dateStr, 0, sizeof(dateStr));
    if ((year != 0) && (month != 0) && (day != 0))
    {
        wsprintfW(dateStr, L"L%04d_%02d_%02d_", year, month, day);
    }

    DBConn sql;
    sql.Execute(L"EXECUTE lin_CheckLogTimeTable2 '%s', %d", dateStr, world);

    g_winlog.Add(LOG_INF, L"bcplogfile::checklogtimetable %s, %d", dateStr, world);

    unguard();

    return true;
}

// L2LogD 0x00407890
bool CBCPLogFile::GetMoveFileName(const wchar_t* dirName, const wchar_t* originFileName, wchar_t* newFileName)
{
    ::guard(L"WCHAR* CBCPLogFile::GetMoveFileName(WCHAR* szFolder, WCHAR* szFile, WCHAR* szMoveFile)");

    wchar_t guessedNewFileName[256];
    wcscpy(guessedNewFileName, dirName);
    wcscat(guessedNewFileName, L"insert\\");
    wcscat(guessedNewFileName, originFileName);

    WIN32_FIND_DATAW findFileData;
    HANDLE fileHandle = ::FindFirstFileW(guessedNewFileName, &findFileData);

    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        // File with such a name doesn't exist in "insert" directory
        wcscpy(newFileName, guessedNewFileName);

        unguard();
        return true;
    }

    ::FindClose(fileHandle);

    int maxFoundIndex = 0;
    wchar_t clearFileName[256];
    CBCPLogFile::GetMaxFileNo(guessedNewFileName, clearFileName, &maxFoundIndex);

    wchar_t newIndex[10];
    wsprintfW(newIndex, L"%d", maxFoundIndex + 1);

    wcscpy(newFileName, clearFileName);
    wcscat(newFileName, newIndex);
    wcscat(newFileName, L".log");

    unguard();

    return true;
}

// L2LogD 0x004079C0
void CBCPLogFile::InsertLogFiles(wchar_t* dirPath)
{
    ::guard(L"CBCPLogFile::InsertLogFiles(WCHAR *szDirPath)");

    time_t timeNow = std::time(NULL);
    tm* localTime = std::localtime(&timeNow);

    ::EnterCriticalSection(&CBCPLogFile::s_lock);

    DWORD threadId = ::GetCurrentThreadId();

    g_winlog.Add(LOG_INF, L"[%d]Insert Log File begins at %04d/%02d/%02d %02d:%02d:%02d", threadId, localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

    wchar_t pathName[258];
    wsprintfW(pathName, L"%s\\insert", dirPath);

    ::CreateDirectoryW(pathName, 0);

    wcscpy(m_dirPath, dirPath);

    wchar_t fileName[256];
    wcscpy(fileName, m_dirPath);
    wcscat(fileName, L"*.log");

    WIN32_FIND_DATAW foundFileData;
    HANDLE fileHandle = ::FindFirstFileW(fileName, &foundFileData);

    ::LeaveCriticalSection(&CBCPLogFile::s_lock);

    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        unguard();
        return;
    }

    while (1)
    {
        ::EnterCriticalSection(&CBCPLogFile::s_lock);

        wchar_t logFilePath[256];
        wcscpy(logFilePath, m_dirPath);
        wcscat(logFilePath, foundFileData.cFileName);

        if (wcsstr(foundFileData.cFileName, L".log") == NULL)
        {
            // Not a log file, check next one
            if (::FindNextFileW(fileHandle, &foundFileData) == FALSE)
            {
                ::LeaveCriticalSection(&CBCPLogFile::s_lock);
                unguard();
                return;
            }
            ::LeaveCriticalSection(&CBCPLogFile::s_lock);
            continue;
        }

        HANDLE canBeRead = ::CreateFileW(logFilePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (canBeRead == INVALID_HANDLE_VALUE)
        {
            if (::FindNextFileW(fileHandle, &foundFileData) == FALSE)
            {
                ::LeaveCriticalSection(&CBCPLogFile::s_lock);
                unguard();
                return;
            }

            ::LeaveCriticalSection(&CBCPLogFile::s_lock);
            continue;
        }

        ::CloseHandle(canBeRead);
        ::LeaveCriticalSection(&CBCPLogFile::s_lock);

        wchar_t fileToMove[256];
        wcscpy(fileToMove, foundFileData.cFileName);

        g_winlog.Add(LOG_INF, L"[%d]found log file(%s)", threadId, logFilePath);

        wchar_t componentName[20];
        memset(componentName, 0, sizeof(componentName));

        wchar_t logCategory[20];
        memset(logCategory, 0, sizeof(logCategory));

        wchar_t suffix[256];
        memset(suffix, 0, sizeof(suffix));  // e.g. "logd-chat0.log", "cached-in0.log"

        int year = -1;
        int month = -1;
        int day = -1;
        int hour = -1;
        int world = -1;

        // "2017-06-20-10021-03-logd-chat0.log" - from CLog
        // "2017-06-20-21-03-logd-chat0.log" - from CServerSocket
        swscanf(foundFileData.cFileName, L"%d-%d-%d-%d-%d-%s", &year, &month, &day, &hour, &world, suffix);
        // swscanf(foundFileData.cFileName, L"%d-%d-%d-100%d-%d-%s", &year, &month, &day, &hour, &world, suffix);

        // "-chat0.log"
        wchar_t* categoryStr = wcschr(suffix, '-');

        bool categoryFound = false;
        // if (categoryStr && (*categoryStr = 0, wcscpy(v48, suffix), wcscpy(suffix, categoryStr + 1), (extension = wcschr(suffix, '.')) != 0))
        if (categoryStr != NULL)
        {
            // sufix => "logd"
            categoryStr[0] = '\0';  // "-chat0.log"
            wcscpy(componentName, suffix);
            wcscpy(suffix, categoryStr + 1);  // "chat0.log";
            wchar_t* extension = wcschr(suffix, '.');
            if (extension != NULL)
            {
                *extension = '\0';
                wcscpy(logCategory, suffix);
                categoryFound = true;
            }
        }

        if (!categoryFound)
        {
            ::EnterCriticalSection(&CBCPLogFile::s_lock);
            if (::FindNextFileW(fileHandle, &foundFileData) == FALSE)
            {
                ::LeaveCriticalSection(&CBCPLogFile::s_lock);
                unguard();
                return;
            }

            ::LeaveCriticalSection(&CBCPLogFile::s_lock);
            continue;
        }

        ::EnterCriticalSection(&CBCPLogFile::s_lock);

        int i = 0;

        if (Config::s_BCPThreadCount <= 0)
        {
        LABEL_20:
            CBCPLogFile::s_worldIds[m_slot] = world;
        }
        else
        {
            while (world != CBCPLogFile::s_worldIds[i])
            {
                if (++i >= Config::s_BCPThreadCount)
                {
                    goto LABEL_20;
                }
            }
            categoryFound = false;
        }

        ::LeaveCriticalSection(&CBCPLogFile::s_lock);
        if (categoryFound)
        {
            if (foundFileData.nFileSizeHigh || foundFileData.nFileSizeLow)
            {
                wchar_t logTableName[64];
                memset(logTableName, 0, sizeof(logTableName));

                if (!wcsncmp(logCategory, L"chat", 4u))
                {
                    wsprintfW(logTableName, L"lin2log.dbo.L%04d_%02d_%02d_log_chat_%d", year, month, day, world);
                }
                else if (hour >= 12)
                {
                    wsprintfW(logTableName, L"lin2log.dbo.L%04d_%02d_%02d_log_data2_%d", year, month, day, world);
                }
                else
                {
                    wsprintfW(logTableName, L"lin2log.dbo.L%04d_%02d_%02d_log_data_%d", year, month, day, world);
                }

                CBCPLogFile::CheckLogTimeTable(year, month, day, world);

                DWORD startTime = ::GetTickCount();

                g_winlog.Add(LOG_INF, "[%d]begin bcp", threadId);
                int executionResult = CBCPLogFile::BulkInsert(logCategory, logFilePath, logTableName);

                DWORD timePassed = (::GetTickCount() - startTime) / 1000;

                g_winlog.Add(LOG_INF, "[%d]end bcp. bcp std::time(%d)", threadId, timePassed);

                if (executionResult > -1)
                {
                    wchar_t newFileName[256];
                    CBCPLogFile::GetMoveFileName(m_dirPath, fileToMove, newFileName);
                    ::MoveFileW(logFilePath, newFileName);

                    g_winlog.Add(LOG_INF, L"[%d]move file %s -> %s", threadId, logFilePath, newFileName);

                    ::EnterCriticalSection(&CBCPLogFile::s_lock);
                    CBCPLogFile::s_worldIds[m_slot] = 0;
                    ::LeaveCriticalSection(&CBCPLogFile::s_lock);

                    DWORD endTime = ::GetTickCount();
                    const wchar_t setInserted[] = L"EXECUTE lin_SetInserted  '%s', '%s', %d, %d, %d, %d, %d, '%s', '%s', %d, %d";
                    const int duration = (endTime - startTime) / 1000;
                    g_sqlPollingQueue.PushSQL(setInserted, fileToMove, logTableName, year, month, day, hour, world, componentName, logCategory, executionResult, duration);

                    std::time_t result = std::time(NULL);
                    wchar_t* nowStr = Utils::TimeToWStr(&result);
                    g_winlog.Add(LOG_INF, L"[%d]Now(%s), ThreadId(%d) insert file(%s), processed(%d)", threadId, nowStr, threadId, logFilePath, executionResult);
                }

                ::EnterCriticalSection(&CBCPLogFile::s_lock);
                if (::FindNextFileW(fileHandle, &foundFileData) == FALSE)
                {
                    ::LeaveCriticalSection(&CBCPLogFile::s_lock);
                    unguard();
                    return;
                }
            }
            else
            {
                wchar_t newFileName[256];
                CBCPLogFile::GetMoveFileName(m_dirPath, fileToMove, newFileName);
                ::MoveFileW(logFilePath, newFileName);

                g_winlog.Add(LOG_INF, L"[%d]zero size file... just move file %s -> %s", threadId, logFilePath, newFileName);
                ::EnterCriticalSection(&CBCPLogFile::s_lock);

                CBCPLogFile::s_worldIds[m_slot] = 0;
                if (::FindNextFileW(fileHandle, &foundFileData) == FALSE)
                {
                    ::LeaveCriticalSection(&CBCPLogFile::s_lock);
                    unguard();
                    return;
                }
            }

            ::LeaveCriticalSection(&CBCPLogFile::s_lock);
        }
    }

    unguard();
}

#endif  //  #if defined (L2LOGD)