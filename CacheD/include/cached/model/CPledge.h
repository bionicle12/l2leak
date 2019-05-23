#pragma once

#include "cached/model/CWareHouse.h"
#include "l2core/MemoryObject.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <set>
#include <l2core/utils/cstdint_support.h>

class CPledge;
typedef CSPointer<CPledge> CPledgeSP;

typedef std::set<uint32_t> PledgeIdList;  // original typedef from L2 binary

class CPledge : public MemoryObject
{
public:
    CPledge(
        uint32_t pledgeId,
        const wchar_t* name,
        uint32_t rulerId,
        const wchar_t* rulerName,
        uint32_t allianceId,
        int challengeTime,
        uint32_t nowWarId,
        int nameValue,
        int oustTime,
        int skillLevel,
        int privateFlag,
        int status,
        int rank,
        uint32_t castleId,
        uint32_t agitId,
        int rootNameValue,
        int a18,
        uint32_t crestId,
        int isGuilty,
        int dismissReservedTime,
        int allianceOustedTime,
        int allianceWithdrawTime,
        int allianceDismissTime);                                                                         // L2CacheD 0x0042AAD0
    CPledge(uint32_t pledgeId, const wchar_t* pledgeName, uint32_t rullerId, const wchar_t* rullerName);  // L2CacheD 0x0042AD40
    ~CPledge();                                                                                           // L2CacheD 0x0042A990

    static void* operator new(size_t size);  // L2CacheD 0x0042C540
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x0042AA90

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x0042A6A0

    bool DeleteCrest();                     // L2CacheD 0x0042A5C0
    uint32_t AddMember(uint32_t memberId);  // L2CacheD 0x0042A860
    void RemoveMember(uint32_t memberId);   // L2CacheD 0x0042A900

    CWareHouseSP GetWareHouse() const;  // L2CacheD 0x0042A7D0

    void SendReplyToLoadPledge(CServerSocket* pSocket);  // L2CacheD 0x00457540

    // those methos were abset in L2CacheD
    uint32_t id() const;
    void setId(const uint32_t id);

    const wchar_t* name() const;
    void setName(const wchar_t* name);

    uint32_t rullerId() const;
    void setRullerId(const uint32_t rullerId);

    const wchar_t* rullerName() const;
    void setRullerName(const wchar_t* rullerName);

    uint32_t allianceId() const;
    void setAllianceId(const uint32_t allianceId);

    int challengeTime() const;
    void setChallengeTime(int challengeTime);

    uint32_t nowWarId() const;
    void setNowWarId(const uint32_t nowWarId);

    int nameValue() const;
    void setNameValue(int nameValue);

    int oustTime() const;
    void setOustTime(int oustTime);

    int skillLevel() const;
    void setSkillLevel(int skillLevel);

    int privateFlag() const;
    void setPrivateFlag(int privateFlag);

    int status() const;
    void setStatus(int status);

    int rank() const;
    void setRank(int rank);

    uint32_t castleId() const;
    void setCastleId(const uint32_t castleId);

    uint32_t agitId() const;
    void setAgitId(const uint32_t agitId);

    int rootNameValue() const;
    void setRootNameValue(int rootNameValue);

    uint32_t crestId() const;
    void setCrestId(const uint32_t crestId);

    int isGuilty() const;
    void setIsGuilty(int isGuilty);

    int dismissReservedTime() const;
    void setDismissReservedTime(int dismissReservedTime);

    int allianceOustedTime() const;
    void setAllianceOustedTime(int allianceOustedTime);

    int allianceWithdrawTime() const;
    void setAllianceWithdrawTime(int allianceWithdrawTime);

    int allianceDismissTime() const;
    void setAllianceDismissTime(int allianceDismissTime);

    PledgeIdList::const_iterator membersBegin() const;
    PledgeIdList::const_iterator membersEnd() const;

    void ReadLock();    // L2CacheD inlined
    void ReadUnlock();  // L2CacheD inlined

private:
    static long s_nAlloc;  // L2CacheD 0x019E6328

    uint32_t m_id;
    wchar_t m_name[26];  // FIXED: extra bytes added to have null-terminated string
    uint32_t m_rullerId;
    wchar_t m_rullerName[26];  // FIXED: extra bytes added to have null-terminated string
    uint32_t m_allianceId;
    int m_challengeTime;
    uint32_t m_nowWarId;
    int m_nameValue;
    int m_oustTime;
    int m_skillLevel;
    int m_privateFlag;
    int m_status;
    int m_rank;
    uint32_t m_castleId;
    uint32_t m_agitId;
    int m_rootNameValue;
    uint32_t m_crestId;
    int m_isGuilty;
    int m_dismissReservedTime;
    int m_allianceOustedTime;
    int m_allianceWithdrawTime;
    int m_allianceDismissTime;
    int field_180;
    int field_184;
    bool field_188;
    CWareHouseStorage m_warehouse;
    int field_385;
    CRWLock m_pledgdeLock;
    CRWLock m_membersLock;
    PledgeIdList m_membersSet;
    int field_308;
    int field_312;
    int field_316;
    int field_320;
    int field_324;
    int field_328;
    int field_332;
    int field_336;
    int field_340;
    int field_344;
    int field_348;
    int field_352;
    int field_356;
    int field_360;
    int field_364;
    int field_368;
    int field_372;
    int field_376;
    int field_380;
    int field_384;
};
