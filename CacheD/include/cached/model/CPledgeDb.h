#pragma once

#include "cached/model/CPledge.h"
#include "cached/model/PledgeFields.h"
#include "cached/model/PledgeMemberFields.h"
#include "l2core/threads/CObjectMap.h"
#include "l2core/threads/CStringObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CObjectMap<CPledge> CPledgeMap;
typedef CStringObjectMap<CPledge> CStringPledgeMap;

class CPledgeDb
{
public:
    CPledgeDb();           // L2CacheD 0x004306D0
    virtual ~CPledgeDb();  // L2CacheD 0x00430760

    void Init();  // L2CacheD 0x004307F0

    CPledgeSP GetPledge(const wchar_t* pledgeName);                 // L2CacheD 0x0042EF00
    CPledgeSP GetPledge(uint32_t pledgeId);                         // L2CacheD 0x0042F080
    int CreatePledge(const wchar_t* pledgeName, uint32_t rulerId);  // L2CacheD 0x0042FB90
    bool DeletePledge(uint32_t pledgeId);                           // L2CacheD 0x0042FDF0

    bool SetUserPledgeInfo(uint32_t userId, PledgeMemberFields updateField, uint32_t updateValue);  // L2CacheD 0x0042C8D0
    bool SetPledgeInfo(uint32_t pledgeId, PledgeFields updateField, uint32_t updateValue);          // L2CacheD 0x0042F1A0
    bool ModifyPledgeName(uint32_t pledgeId, const wchar_t* newName);                               // L2CacheD 0x0042F840

    void LoadPledgeMember(CPledge* pledge);                                 // L2CacheD 0x0042C5B0
    bool JoinPledgeMember(uint32_t pledgeId, uint32_t userId);              // L2CacheD 0x00430170
    bool WithdrawPledgeMember(uint32_t pledgeId, uint32_t userId);          // L2CacheD 0x00430350
    uint32_t OustPledgeMember(uint32_t pledgeId, const wchar_t* charName);  // L2CacheD 0x00430040

private:
    CPledgeSP LoadPledge(const wchar_t* name);  // L2CacheD 0x0042E630
    CPledgeSP LoadPledge(uint32_t pledgeId);    // L2CacheD 0x0042EAA0

    void InsertIntoMap(uint32_t pledgeId, const wchar_t* name, CPledge* pledge);  // L2CacheD 0x0042E3C0
    void DeleteFromMap(CPledge* pledge);                                          // L2CacheD 0x0042E4C0

private:
    CRWLock m_lock;
    CPledgeMap m_pledgesById;
    CStringPledgeMap m_pledgesByName;
};

extern CPledgeDb g_pledgeDb;  // L2CacheD 0x019E6368
