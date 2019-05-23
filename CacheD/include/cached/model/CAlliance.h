#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <set>
#include <l2core/utils/cstdint_support.h>

class CAlliance;

typedef CSPointer<CAlliance> CAllianceSP;

typedef std::set<uint32_t> PledgeIdList;  // original typedef from L2 binary

class CAlliance : public MemoryObject
{
public:
    CAlliance(uint32_t id, const wchar_t* name, uint32_t masterPledgeId, int oustTime, uint32_t crestId);  // L2CacheD 0x00406AC0
    ~CAlliance();                                                                                          // L2CacheD 0x00406BB0

    static void* operator new(size_t size);  // L2CacheD 0x00405210
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x00406B70

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x004050E0

    void AddMemberPledge(uint32_t memberPledgeId);     // L2CacheD 0x004065A0
    void RemoveMemberPledge(uint32_t memberPledgeId);  // L2CacheD 0x004066F0

    void GetAllMemberPledgeId(PledgeIdList& pledgeList) const;  // L2CacheD 0x00406920

    uint32_t id() const;
    void setId(uint32_t id);

    const wchar_t* name() const;
    void setName(const wchar_t* name);

    uint32_t masterPledgeId() const;
    void setMasterPledgeId(uint32_t masterPledgeId);

    int oustTime() const;
    void setOustTime(int oustTime);

    uint32_t crestId() const;
    void setCrestId(uint32_t crestId);

private:
    static long s_nAlloc;  // L2CacheD 0x004F2758

    uint32_t m_id;
    wchar_t m_name[25];
    uint32_t m_masterPledgeId;
    int m_oustTime;
    uint32_t m_crestId;
    mutable CRWLock m_lock;
    PledgeIdList m_members;
    char m_gap[80];
};
