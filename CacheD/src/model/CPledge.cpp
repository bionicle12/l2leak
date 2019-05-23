#include "cached/model/CPledge.h"

#include "cached/model/CUser.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D1F5
long CPledge::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x019E6328

// L2CacheD 0x0042AAD0
CPledge::CPledge(
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
    int allianceDismissTime)
    : MemoryObject()
    , m_id(pledgeId)
    , m_rullerId(rulerId)
    , m_allianceId(allianceId)
    , m_challengeTime(challengeTime)
    , m_nowWarId(nowWarId)
    , m_nameValue(nameValue)
    , m_oustTime(oustTime)
    , m_skillLevel(skillLevel)
    , m_privateFlag(privateFlag)
    , m_status(status)
    , m_rank(rank)
    , m_castleId(castleId)
    , m_agitId(agitId)
    , m_rootNameValue(rootNameValue)
    , m_crestId(crestId)
    , m_isGuilty(isGuilty)
    , m_dismissReservedTime(dismissReservedTime)
    , m_allianceOustedTime(allianceOustedTime)
    , m_allianceWithdrawTime(allianceWithdrawTime)
    , m_allianceDismissTime(allianceDismissTime)
    , field_180(0)
    , field_184(0)
    , field_188(false)
    , m_warehouse()
    , field_385(0)
    , m_pledgdeLock()
    , m_membersLock()
    , m_membersSet()
    , field_308(0)
    , field_312(0)
    , field_316(0)
    , field_320(0)
    , field_324(0)
    , field_328(0)
    , field_332(0)
    , field_336(0)
    , field_340(0)
    , field_344(0)
    , field_348(0)
    , field_352(0)
    , field_356(0)
    , field_360(0)
    , field_364(0)
    , field_368(0)
    , field_372(0)
    , field_376(0)
    , field_380(0)
    , field_384(0)
{
    guard(L"CPledge::CPledge(...)");

    ::wcscpy(m_name, name);
    ::wcscpy(m_rullerName, rulerName);

    CWareHouse* warehouse = new CWareHouse();
    warehouse->SetOwnerId(m_id);
    warehouse->Init(WareHouseType_Pledge, true);
    m_warehouse.SetObject(warehouse);
    warehouse->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
}

// L2CacheD 0x0042AD40
CPledge::CPledge(uint32_t pledgeId, const wchar_t* pledgeName, uint32_t rullerId, const wchar_t* rullerName)
    : MemoryObject()
    , m_id(pledgeId)
    , m_rullerId(rullerId)
    , m_allianceId(0)
    , m_challengeTime(0)
    , m_nowWarId(0)
    , m_nameValue(0)
    , m_oustTime(0)
    , m_skillLevel(0)
    , m_privateFlag(0)
    , m_status(0)
    , m_rank(0)
    , m_castleId(0)
    , m_agitId(0)
    , m_rootNameValue(0)
    , m_crestId(0)
    , m_isGuilty(0)
    , m_dismissReservedTime(0)
    , m_allianceOustedTime(0)
    , m_allianceWithdrawTime(0)
    , m_allianceDismissTime(0)
    , field_180(0)
    , field_184(0)
    , field_188(false)
    , m_warehouse()
    , field_385(0)
    , m_pledgdeLock()
    , m_membersLock()
    , m_membersSet()
    , field_308(0)
    , field_312(0)
    , field_316(0)
    , field_320(0)
    , field_324(0)
    , field_328(0)
    , field_332(0)
    , field_336(0)
    , field_340(0)
    , field_344(0)
    , field_348(0)
    , field_352(0)
    , field_356(0)
    , field_360(0)
    , field_364(0)
    , field_368(0)
    , field_372(0)
    , field_376(0)
    , field_380(0)
    , field_384(0)

{
    guard(L"CPledge::CPledge(uint32_t nId, const wchar_t *sName, uint32_t nRulerId, const wchar_t *sRulerName)");

    ::wcscpy(m_name, pledgeName);
    ::wcscpy(m_rullerName, rullerName);

    CWareHouse* warehouse = new CWareHouse();
    warehouse->SetOwnerId(m_id);
    warehouse->Init(WareHouseType_Pledge, true);
    m_warehouse.SetObject(warehouse);
    warehouse->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
}

// L2CacheD 0x0042A990
CPledge::~CPledge()
{
    guard(L"CPledge::~CPledge()");
    unguard();
}

// L2CacheD 0x0042C540
void* CPledge::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CPledge");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPledge::s_nAlloc]);

    Allocator::s_classRefNames[CPledge::s_nAlloc] = "CPledge";
    Allocator::g_allocatedMemory[CPledge::s_nAlloc] = sizeof(CPledge);

    return memory;
}

// L2CacheD inlined in 0x0042AA90
void CPledge::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPledge at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x0042A6A0
void CPledge::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CPledge(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPledge] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledge::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPledge]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledge::s_nAlloc]);
        }
        return;
    }

    this->~CPledge();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledge::s_nAlloc]);
}

// L2CacheD 0x0042A5C0
bool CPledge::DeleteCrest()
{
    guard(L"bool CPledge::DeleteCrest()");

    DBConn sql;
    bool sqlResult = sql.Execute(L"EXEC lin_InitPledgeCrest %d", m_id);

    unguard();

    return sqlResult;
}

// L2CacheD 0x0042A860
uint32_t CPledge::AddMember(uint32_t memberId)
{
    guard(L"uint32_t CPledge::AddMember(uint32_t nMemberId)");

    m_membersLock.WriteLock();

    m_membersSet.insert(memberId);
    uint32_t size = m_membersSet.size();

    m_membersLock.WriteUnlock();

    unguard();

    return size;
}

// L2CacheD 0x0042A900
void CPledge::RemoveMember(uint32_t memberId)
{
    guard(L"void CPledge::RemoveMember(uint32_t nMemberId)");

    m_membersLock.WriteLock();
    m_membersSet.erase(memberId);
    m_membersLock.WriteUnlock();

    unguard();
}

// L2CacheD 0x0042A7D0
CWareHouseSP CPledge::GetWareHouse() const
{
    guard(L"CWareHouseSP CPledge::GetWareHouse()");

    CWareHouseSP warehouse = m_warehouse.GetObjct();

    unguard();
    return warehouse;
}

// L2CacheD 0x00457540
void CPledge::SendReplyToLoadPledge(CServerSocket* pSocket)
{
    guard(L"static void SendReplyToLoadPledge(CSocket *pSocket, CPledge *pPledge)");

    m_pledgdeLock.ReadLock();

    wchar_t pledgeName[24];
    ::memset(pledgeName, 0, sizeof(pledgeName));
    ::wcscpy(pledgeName, m_name);

    wchar_t rullerName[24];
    ::memset(rullerName, 0, sizeof(rullerName));
    ::wcscpy(rullerName, m_rullerName);

    uint8_t buff[BUFFER_SIZE];
    int assembledPayloadSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "SddS", pledgeName, m_id, m_rullerId, rullerName);
    const int headerPayloadSize = assembledPayloadSize;

    int payloadSize = headerPayloadSize + 4;  // 4 bytes are reserved for memberCount
    int memberCount = 0;
    for (PledgeIdList::const_iterator it = m_membersSet.begin(); it != m_membersSet.end(); ++it)
    {
        uint32_t memberId = *it;

        CUserSP member = g_userDb.GetUser(memberId, false);
        if (member != NULL)
        {
            int memberRace = member->GetRace();
            int memberGender = member->GetGender();
            int memberClass = member->GetClass();
            int memberLevel = member->GetLevel();
            const wchar_t* memberName = member->GetCharName();
            payloadSize += PacketUtils::Assemble(&buff[payloadSize], BUFFER_SIZE - payloadSize, "dSdddd", memberId, memberName, memberLevel, memberClass, memberGender, memberRace);
            ++memberCount;
            continue;
        }

        wchar_t memberName[50];
        ::memset(memberName, 0, sizeof(memberName));
        int memberRace = 0;
        int memberGender = 0;
        int memberClass = 0;
        int memberLevel = 0;
        if (g_userDb.SimpleLoad(memberId, memberName, sizeof(memberName), &memberLevel, &memberClass, &memberGender, &memberRace))
        {
            payloadSize += PacketUtils::Assemble(&buff[payloadSize], BUFFER_SIZE - payloadSize, "dSdddd", memberId, memberName, memberLevel, memberClass, memberGender, memberRace);
            ++memberCount;
            continue;
        }

        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", __FILE__, __LINE__, memberId);
    }

    PacketUtils::Assemble(&buff[headerPayloadSize], 4, "d", memberCount);

    payloadSize += PacketUtils::Assemble(
        &buff[payloadSize],
        BUFFER_SIZE - payloadSize,
        "dddddddddddddddddd",
        m_nowWarId,
        m_rootNameValue,
        m_challengeTime,
        m_oustTime,
        m_allianceId,
        field_180,
        m_castleId,
        m_agitId,
        m_rank,
        m_status,
        m_privateFlag,
        m_crestId,
        m_isGuilty,
        m_dismissReservedTime,
        m_skillLevel,
        m_allianceOustedTime,
        m_allianceWithdrawTime,
        m_allianceDismissTime);

    m_pledgdeLock.ReadUnlock();

    pSocket->Send("cb", CacheToServerPacket_ReplyLoadPledge, payloadSize, buff);

    unguard();
}

uint32_t CPledge::id() const
{
    return m_id;
}

const wchar_t* CPledge::name() const
{
    return m_name;
}

void CPledge::setName(const wchar_t* name)
{
    ::wcscpy(m_name, name);
}

uint32_t CPledge::rullerId() const
{
    return m_rullerId;
}

const wchar_t* CPledge::rullerName() const
{
    return m_rullerName;
}

void CPledge::setRullerName(const wchar_t* rullerName)
{
    ::wcscpy(m_rullerName, rullerName);
}

uint32_t CPledge::allianceId() const
{
    return m_allianceId;
}

int CPledge::challengeTime() const
{
    return m_challengeTime;
}

uint32_t CPledge::nowWarId() const
{
    return m_nowWarId;
}

int CPledge::nameValue() const
{
    return m_nameValue;
}

int CPledge::oustTime() const
{
    return m_oustTime;
}

int CPledge::skillLevel() const
{
    return m_skillLevel;
}

int CPledge::privateFlag() const
{
    return m_privateFlag;
}

int CPledge::status() const
{
    return m_status;
}

int CPledge::rank() const
{
    return m_rank;
}

uint32_t CPledge::castleId() const
{
    return m_castleId;
}

uint32_t CPledge::agitId() const
{
    return m_agitId;
}

int CPledge::rootNameValue() const
{
    return m_rootNameValue;
}

uint32_t CPledge::crestId() const
{
    return m_crestId;
}

int CPledge::isGuilty() const
{
    return m_isGuilty;
}

int CPledge::dismissReservedTime() const
{
    return m_dismissReservedTime;
}

int CPledge::allianceOustedTime() const
{
    return m_allianceOustedTime;
}

int CPledge::allianceWithdrawTime() const
{
    return m_allianceWithdrawTime;
}

int CPledge::allianceDismissTime() const
{
    return m_allianceDismissTime;
}
void CPledge::setId(const uint32_t id)
{
    m_id = id;
}
void CPledge::setRullerId(const uint32_t rullerId)
{
    m_rullerId = rullerId;
}
void CPledge::setAllianceId(const uint32_t allianceId)
{
    m_allianceId = allianceId;
}
void CPledge::setChallengeTime(int challengeTime)
{
    m_challengeTime = challengeTime;
}
void CPledge::setNowWarId(const uint32_t nowWarId)
{
    m_nowWarId = nowWarId;
}
void CPledge::setNameValue(int nameValue)
{
    m_nameValue = nameValue;
}
void CPledge::setOustTime(int oustTime)
{
    m_oustTime = oustTime;
}
void CPledge::setSkillLevel(int skillLevel)
{
    m_skillLevel = skillLevel;
}
void CPledge::setPrivateFlag(int privateFlag)
{
    m_privateFlag = privateFlag;
}
void CPledge::setStatus(int status)
{
    m_status = status;
}
void CPledge::setRank(int rank)
{
    m_rank = rank;
}
void CPledge::setCastleId(const uint32_t castleId)
{
    m_castleId = castleId;
}
void CPledge::setAgitId(const uint32_t agitId)
{
    m_agitId = agitId;
}
void CPledge::setRootNameValue(int rootNameValue)
{
    m_rootNameValue = rootNameValue;
}
void CPledge::setCrestId(const uint32_t crestId)
{
    m_crestId = crestId;
}
void CPledge::setIsGuilty(int isGuilty)
{
    m_isGuilty = isGuilty;
}
void CPledge::setDismissReservedTime(int dismissReservedTime)
{
    m_dismissReservedTime = dismissReservedTime;
}
void CPledge::setAllianceOustedTime(int allianceOustedTime)
{
    m_allianceOustedTime = allianceOustedTime;
}
void CPledge::setAllianceWithdrawTime(int allianceWithdrawTime)
{
    m_allianceWithdrawTime = allianceWithdrawTime;
}
void CPledge::setAllianceDismissTime(int allianceDismissTime)
{
    m_allianceDismissTime = allianceDismissTime;
}

void CPledge::ReadLock()
{
    m_pledgdeLock.ReadLock();
}

void CPledge::ReadUnlock()
{
    m_pledgdeLock.ReadUnlock();
}

PledgeIdList::const_iterator CPledge::membersBegin() const
{
    return m_membersSet.begin();
}

PledgeIdList::const_iterator CPledge::membersEnd() const
{
    return m_membersSet.end();
}
