#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CObjectMap.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <windows.h>

class CUser;

class CAccount;
typedef CSPointer<CAccount> CAccountSP;

class CAccount : public MemoryObject
{
public:
    CAccount();   // L2CacheD 0x00403EE0
    ~CAccount();  // L2CacheD 0x00403F77

    static void* operator new(size_t size);  // L2CacheD 0x00401000
    static void operator delete(void* ptr);  // L2CacheD 0x00401050

    static void Init();                                        // L2CacheD 0x00401E70
    static uint32_t AccountNameToId(const char* accountName);  // L2CacheD 0x00401380
    static CAccountSP Load(uint32_t id);                       // L2CacheD 0x00403FB0
    static CAccountSP Reload(uint32_t id);                     // L2CacheD 0x00404320

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x00401D40

    const CObjectMap<CUser>& GetChars() const;  // L2CacheD 0x00401480

    uint32_t GetId() const;          // L2CacheD 0x00401490
    const wchar_t* GetName() const;  // L2CacheD inlined

    void SetCharacter(CUser* user);                        // L2CacheD 0x004038A0
    bool DeleteCharacter(uint32_t charId, bool deleteDb);  // L2CacheD 0x00403920
    int GetCharCount() const;                              // L2CacheD 0x00402280

    int GetWeekPlayTime();                                              // L2CacheD 0x00402060
    void CAccount::SetWeekPlayTime(int newWeekPlayTime);                // L2CacheD inlined
    void SaveWeekPlayTime(int weekPlayTime, SYSTEMTIME* lastSaveTime);  // L2CacheD 0x00401840
    bool SetLastSaveTime(SYSTEMTIME* lastSaveTime);                     // L2CacheD 0x00401990
    SYSTEMTIME GetWeekPlayTimeLastChanged();                            // L2CacheD 0x00402130

    void ReadLock();     // L2CacheD 0x004014A0
    void ReadUnlock();   // L2CacheD 0x00401510
    void WriteLock();    // L2CacheD 0x00401580
    void WriteUnlock();  // L2CacheD 0x004015F0

private:
    static void DeleteChars(int requestDate, int deletionDate, uint32_t deletionId, uint32_t accountId, int seq);  // L2CacheD 0x00401080

    void GetWeekPlayTimeFromDB();  // L2CacheD 0x00401660

private:
    static long s_nAlloc;     // L2CacheD 0x004F2750
    static CRWLock s_rwLock;  // L2CacheD 0x004F2730

private:
    CObjectMap<CUser> m_chars;
    uint32_t m_id;
    wchar_t m_name[32];
    int m_weekPlayTime;
    SYSTEMTIME m_lastSaveTime;
};

typedef CObjectMap<CAccount> CAccountMap;
extern CAccountMap g_accounts;  // L2CacheD 0x004F2700
