#include "cached/model/CAccount.h"

#include "cached/config/Config.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0049CEF5
long CAccount::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x004F2750

CRWLock CAccount::s_rwLock;  // L2CacheD 0x004F2730
CAccountMap g_accounts;      // L2CacheD 0x004F2700

// L2CacheD 0x00403EE0
CAccount::CAccount()
    : MemoryObject()
    , m_chars()
    , m_id(0)
    , m_weekPlayTime(-1)
    , m_lastSaveTime()
{
    ::memset(m_name, 0, sizeof(m_name));
    ::memset(&m_lastSaveTime, 0, sizeof(m_lastSaveTime));
}

// L2CacheD 0x00403F77
CAccount::~CAccount()
{
}

// L2CacheD 0x00401000
void* CAccount::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CAccount");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CAccount::s_nAlloc]);

    Allocator::s_classRefNames[CAccount::s_nAlloc] = "CAccount";
    Allocator::g_allocatedMemory[CAccount::s_nAlloc] = sizeof(CAccount);

    return memory;
}

// L2CacheD 0x00401050
void CAccount::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CAccount at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x00401E70
void CAccount::Init()
{
    guard(L"void CAccount::Init()");

    if (Config::s_deleteAccount == false)
    {
        unguard();
        return;
    }

    g_winlog.Add(LOG_INF, L"Clearing chars owned by deleted account");

    DBConn sql(Pool_BbsDb);  // FIXME: fix me! Pair DB! or 0
    SQLLEN length = -1;

    int requestDate = 0;
    int deletionDate = 0;
    uint32_t deletionId = 0;
    uint32_t accountId = 0;
    int seq = 0;

    sql.BindNullable(&requestDate, &length);
    sql.BindNullable(&deletionDate, &length);
    sql.BindNullable(&deletionId, &length);
    sql.BindNullable(&accountId, &length);
    sql.BindNullable(&seq, &length);

    if (!sql.Execute(L"EXEC lin2user.dbo.lin_GetDelAccountId %d", Config::s_worldId))
    {
        g_winlog.Add(LOG_ERROR, L"GetDelAccountId failed!");  // FIXED: added

        unguard();
        return;
    }

    requestDate = 0;
    deletionDate = 0;
    deletionId = 0;
    accountId = 0;
    seq = 0;

    if (sql.Fetch())
    {
        int lastDeletionId = 0;
        do
        {
            CAccount::DeleteChars(requestDate, deletionDate, deletionId, accountId, seq);
            lastDeletionId = deletionId;
            requestDate = 0;
            deletionDate = 0;
            deletionId = 0;
            accountId = 0;
            seq = 0;
        } while (sql.Fetch());

        if (lastDeletionId > 0)
        {
            sql.ResetHtmt();
            sql.Execute(L"EXEC lin2user.dbo.lin_SetDelId %d, %d ", Config::s_worldId, lastDeletionId);
        }
    }

    unguard();
}

// L2CacheD 0x00401380
uint32_t CAccount::AccountNameToId(const char* accountName)
{
    guard(L"CAccountSP CAccount::AccountNameToId(char *sAccountName)");

    DBConn sql;
    uint32_t accountId = 0;
    sql.Bind(&accountId);
    if (sql.Execute(L"EXEC lin_LoadBuilderAccountByAccountName N'%S'", accountName))
    {
        sql.Fetch();
    }

    unguard();
    return accountId;
}

// L2CacheD 0x00403FB0
CAccountSP CAccount::Load(uint32_t id)
{
    guard(L"CAccountSP CAccount::Load(uint32_t nAccountID)");

    CAccountSP accPtr = g_accounts.FindObject(id);
    if (accPtr != NULL)
    {
        unguard();
        return accPtr;
    }

    wchar_t accountName[50];
    ::memset(accountName, 0, sizeof(accountName));
    uint32_t charId = 0;

    DBConn sql;
    sql.Bind(&charId);
    sql.Bind(accountName, sizeof(accountName));

    if (sql.Execute(L"EXEC lin_LoadAccount %d", id))
    {
        CAccount* account = new CAccount();

        while (sql.Fetch())
        {
            CUserSP user = g_userDb.GetUser(charId, true);
            if (user != NULL)
            {
                account->m_chars.Insert(charId, user.get(), NULL, -1);
            }
        }

        account->m_id = id;

        ::wcscpy(account->m_name, accountName);

        g_accounts.Insert(id, account, NULL, -1);
        account->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

        unguard();
        return CAccountSP(account, ORT_FUNCTION_CHAIN);
    }

    unguard();
    return CAccountSP();
}

// L2CacheD 0x00404320
CAccountSP CAccount::Reload(uint32_t id)
{
    CAccountSP account = g_accounts.FindObject(id);
    if (account != NULL)
    {
        g_accounts.DeleteObject(id, NULL, -1);
    }

    account = CAccount::Load(id);
    return account;
}

// L2CacheD 0x00401D40
void CAccount::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CAccount(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAccount] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAccount::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAccount]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAccount::s_nAlloc]);
        }
        return;
    }

    this->~CAccount();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAccount::s_nAlloc]);
}

// L2CacheD 0x00401480
const CObjectMap<CUser>& CAccount::GetChars() const
{
    return m_chars;
}

// L2CacheD 0x00401490
uint32_t CAccount::GetId() const
{
    return m_id;
}

// L2CacheD inlined
const wchar_t* CAccount::GetName() const
{
    return m_name;
}

// L2CacheD 0x004038A0
void CAccount::SetCharacter(CUser* user)
{
    guard(L"void CAccount::SetCharacter(CUser* pUser)");

    if (user != NULL)
    {
        m_chars.Insert(user->GetId(), user, NULL, -1);
    }

    unguard();
}

// L2CacheD 0x00403920
bool CAccount::DeleteCharacter(uint32_t charId, bool deleteDb)
{
    guard(L"bool CAccount::DeleteCharacter(uint32_t nCharID, bool bDeleteDB)");

    CUserSP user = m_chars.FindObject(charId);
    if (user == NULL)
    {
        unguard();
        return false;
    }

    m_chars.DeleteObject(charId, NULL, -1);
    bool deleted = g_userDb.DeleteChar(user.get(), deleteDb);

    unguard();

    return deleted;
}

// L2CacheD 0x00402280
int CAccount::GetCharCount() const
{
    return m_chars.GetSize();
}

// L2CacheD 0x00401080
void CAccount::DeleteChars(int requestDate, int deletionDate, uint32_t deletionId, uint32_t accountId, int seq)
{
    guard(L"void CAccount::DeleteChars ( int request_date, int del_date, int del_id, int account_id, int seq)");

    int charId = 0;
    int accountIdOut = 0;

    wchar_t charName[50];
    ::memset(charName, 0, sizeof(charName));

    wchar_t accountName[50];
    ::memset(accountName, 0, sizeof(accountName));

    DBConn sql;
    sql.Bind(&charId);
    sql.Bind(&accountIdOut);
    sql.Bind(charName, 100);
    sql.Bind(accountName, 100);
    if (!sql.Execute(L"EXEC lin_GetCharByAccountId %d ", accountId))
    {
        unguard();
        return;
    }

    charId = 0;
    accountIdOut = 0;
    ::memset(charName, 0, sizeof(charName));
    ::memset(accountName, 0, sizeof(accountName));

    while (sql.Fetch())
    {
        if (Config::s_dbPair)
        {
            DBConn pairSql(Pool_PairDb);
            if (!pairSql.Execute(L"EXEC lin2user.dbo.lin_MakeCharacterCheckDelete %d, N'%s'", Config::s_worldId, charName))

            {
                g_winlog.Add(LOG_ERROR, L"Cannot delete character name from pair db. [%s]", charName);
            }
            pairSql.ResetHtmt();
        }

        DBConn sqlDeleteChars;
        if (sqlDeleteChars.Execute(L"EXEC lin_DeleteChar %d", charId))
        {
            sqlDeleteChars.ResetHtmt();
            if (sqlDeleteChars.Execute(L"EXEC lin_DeleteCharClearPledge %d ", charId))
            {
                g_winlog.Add(LOG_IN, L"%d,%d,%d,,,,,,,,,%d,%d,%d,%d,,,,,,,%s,%s,,,", LogId_DelCharByDelAccount, charId, accountIdOut, requestDate, deletionDate, deletionId, seq, charName, accountName);
            }
            else
            {
                g_winlog.Add(LOG_ERROR, L"Cannot delete character name from lin2world db. failed to clear pledge. [%d],[%s]", charId, charName);
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"Cannot delete character name from lin2world db. [%d],[%s]", charId, charName);
        }
        sqlDeleteChars.ResetHtmt();
    }

    unguard();
}

// L2CacheD 0x00402060
int CAccount::GetWeekPlayTime()
{
    guard(L"CAccount::GetWeekPlayTime()");

    if (m_weekPlayTime == -1)
    {
        GetWeekPlayTimeFromDB();
    }

    if (m_weekPlayTime == -1)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Error. Cannot load Week play time, account id [%d]", TEXT(__FILE__), __LINE__, GetId());
        unguard();
        return 0;
    }

    unguard();

    return m_weekPlayTime;
}

void CAccount::SetWeekPlayTime(int newWeekPlayTime)
{
    m_weekPlayTime = newWeekPlayTime;
}

// L2CacheD 0x00402130
SYSTEMTIME CAccount::GetWeekPlayTimeLastChanged()
{
    guard(L"SYSTEMTIME CAccount::GetWeekPlayTimeLastChanged()");

    if (m_weekPlayTime == -1)
    {
        GetWeekPlayTimeFromDB();
        if (m_weekPlayTime == -1)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Error. Cannot load Week play time, account id [%d]", TEXT(__FILE__), __LINE__, GetId());
        }
    }

    SYSTEMTIME result;
    ::memcpy(&result, &m_lastSaveTime, sizeof(m_lastSaveTime));

    unguard();

    return result;
}

// L2CacheD 0x00401660
void CAccount::GetWeekPlayTimeFromDB()
{
    guard(L"CAccount::GetWeekPlayTimeFromDB()");

    int usedSec = 0;
    wchar_t lastLogoutStr[20] = {0};
    ::memcpy(lastLogoutStr, L"2004-01-01 0:0:0", sizeof(L"2004-01-01 0:0:0"));

    DBConn sql;
    sql.Bind(&usedSec);
    sql.Bind(lastLogoutStr, sizeof(lastLogoutStr));
    if (sql.Execute(L"EXEC lin_LoadDayUsedTime %d", m_id) && sql.Fetch())
    {
        m_weekPlayTime = usedSec;

        SYSTEMTIME lastLogout = {0};
        // FIXME: to be fixed in devel! %d scans for ints, but passing them to short
        ::swscanf(lastLogoutStr, L"%d-%d-%d %d:%d:%d", &lastLogout.wYear, &lastLogout.wMonth, &lastLogout.wDay, &lastLogout.wHour, &lastLogout.wMinute, &lastLogout.wSecond);

        // setting DayOfWeek, since this attribute is not read from SQL
        FILETIME fileTime = {0};
        ::SystemTimeToFileTime(&lastLogout, &fileTime);
        ::FileTimeToSystemTime(&fileTime, &lastLogout);

        ::memcpy(&m_lastSaveTime, &lastLogout, sizeof(lastLogout));
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] Cannot load day uesed time for account [%d]", TEXT(__FILE__), __LINE__, GetId());
    }

    unguard();
}

// L2CacheD 0x00401840
void CAccount::SaveWeekPlayTime(int weekPlayTime, SYSTEMTIME* lastSaveTime)
{
    guard(L"bool CAccount::SaveWeekPlayTime(int nWeekPlayTime, SYSTEMTIME *ptmLastSaveTime)");

    int second = lastSaveTime->wSecond;
    int minute = lastSaveTime->wMinute;
    int hour = lastSaveTime->wHour;
    int day = lastSaveTime->wDay;
    int month = lastSaveTime->wMonth;
    int year = lastSaveTime->wYear;

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SaveTimeData %d, %d, '%d-%d-%d %d:%d:%d'", GetId(), weekPlayTime, year, month, day, hour, minute, second))
    {
        g_winlog.Add(LOG_ERROR, L"Save Play Time Limit Error. [%s][%d]", m_name, weekPlayTime);
    }

    m_weekPlayTime = weekPlayTime;
    m_lastSaveTime = *lastSaveTime;

    unguard();
}

// L2CacheD 0x00401990
bool CAccount::SetLastSaveTime(SYSTEMTIME* lastSaveTime)
{
    guard(L"bool CAccount::SetLastSaveTIme(SYSTEMTIME *ptmLastSaveTime)");

    m_lastSaveTime = *lastSaveTime;

    unguard();
    return true;
}

// L2CacheD 0x004014A0
void CAccount::ReadLock()
{
    guard(L"CAccount::ReadLock()");

    CAccount::s_rwLock.ReadLock();

    unguard();
}

// L2CacheD 0x00401510
void CAccount::ReadUnlock()
{
    guard(L"CAccount::ReadUnlock()");

    CAccount::s_rwLock.ReadUnlock();

    unguard();
}

// L2CacheD 0x00401580
void CAccount::WriteLock()
{
    guard(L"CAccount::WriteLock()");

    CAccount::s_rwLock.WriteLock();

    unguard();
}

// L2CacheD 0x004015F0
void CAccount::WriteUnlock()
{
    guard(L"CAccount::WriteUnlock()");

    CAccount::s_rwLock.WriteUnlock();

    unguard();
}
