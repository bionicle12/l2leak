#include "cached/model/CUser.h"

#include "cached/config/Config.h"
#include "cached/model/CFriendsDb.h"
#include "cached/model/CItem.h"
#include "cached/model/CItemData.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/CQsCheck.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <Sql.h>
#include <Sqlext.h>

// L2CacheD 0x0049D370
long CUser::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x021EEF88
long CUser::s_loggedUsers = 0;                                                 // L2CacheD 0x02684584

// L2CacheD 0x00464160
CUser::CUser(
    const wchar_t* charName,
    const wchar_t* accountName,
    uint32_t charId,
    uint32_t accountId,
    uint32_t pledgeId,
    int builder,
    int gender,
    int race,
    int charClass,
    int worldId,
    int locX,
    int locY,
    int locZ,
    double hp,
    double mp,
    double maxHp,
    double maxMp,
    int spellPoint,
    int expPoint,
    int level,
    uint32_t align,
    int pk,
    int duel,
    int pkPardon,
    int underware,
    int rightEar,
    int leftEar,
    int neck,
    int rightFinger,
    int leftFinger,
    int head,
    int rightHand,
    int leftHand,
    int gloves,
    int chest,
    int legs,
    int feet,
    int back,
    int bothHand,
    AbnormalEffect* abnormalEffects,
    int faceIndex,
    int hairShapeIndex,
    int hairColorIndex,
    bool isInVehicle,
    const wchar_t* nickName,
    const uint8_t* powerFlag,
    int pledgeDismissTime,
    int pledgeOustedTime,
    int pledgeWithdrawTime,
    uint32_t surrenderWarId,
    int useTime,
    int tempDeleteDateYear,
    int tempDeleteDateMonth,
    int tempDeleteDateDay)
    : MemoryObject()
    , m_oneTimeQuests()
    , m_lastUpdateTime(::GetTickCount())
    , m_lastUpdateExp(expPoint)
    , m_rwLock()
    , m_inventory()
    , m_warehouse()
    , m_charId(charId)
    , m_accountId(accountId)
    , m_pledgeId(0)
    , m_builder(0)
    , m_gender(0)
    , m_race(0)
    , m_class(0)
    , m_worldId(0)
    , m_locX(0)
    , m_locY(0)
    , m_locZ(0)
    , m_isInVehicle(false)
    , m_hp(0.0)
    , m_mp(0.0)
    , m_maxHp(0.0)
    , m_maxMp(0.0)
    , m_sp(0)
    , m_exp(0)
    , m_level(0)
    , m_dropExp(0)
    , m_align(0)
    , m_pk(0)
    , m_duel(0)
    , m_pkPardon(0)
    , m_underware(0)
    , m_rightEar(0)
    , m_leftEar(0)
    , m_neck(0)
    , m_rightFinger(0)
    , m_leftFinger(0)
    , m_head(0)
    , m_rightHand(0)
    , m_leftHand(0)
    , m_gloves(0)
    , m_chest(0)
    , m_legs(0)
    , m_feet(0)
    , m_back(0)
    , m_bothHand(0)
    , m_hairColorIndex(0)
    , m_hairShapeIndex(0)
    , m_faceIndex(0)
    , m_deleteYear(tempDeleteDateYear)
    , m_deleteMonth(tempDeleteDateMonth)
    , m_gap(0)
    , m_deleteDay(tempDeleteDateDay)
    , field_432(0)
    , field_436(0)
    , m_lock()
    , m_skillLevels()
    , m_activeSkillsCooldowns()
    , m_pledgeDismissTime(pledgeDismissTime)
    , m_pledgeOustedTime(pledgeOustedTime)
    , m_pledgeWithdrawTime(pledgeWithdrawTime)
    , m_surrenderWarId(surrenderWarId)
    , m_loggedIn(false)
    , m_loginTime(0)
    , m_auditNeeded(false)
    , m_adenaSum(0)
    , m_defaultPriceSum(0)
    , m_itemSum(0)
    , m_usedTime(useTime)
    , m_status(0)
    , m_banEnd(0)
{
    guard(L"CUser::CUser(...)");

    ::memset(m_charNameLow, 0, sizeof(m_charNameLow));
    ::memset(m_charName, 0, sizeof(m_charName));
    ::memset(m_accountName, 0, sizeof(m_accountName));
    ::memset(&m_lastTime, 0, sizeof(SYSTEMTIME));

    Utils::CopyStrInLowerCase(charName, m_charNameLow);
    ::lstrcpyW(m_charName, charName);
    ::lstrcpyW(m_accountName, accountName);

    for (int i = 0; i < QUEST_SIZE; ++i)
    {
        m_quests[i].j1 = 0;
        m_quests[i].questId = 0;
        m_quests[i].state = 0;
    }

    Set(pledgeId,
        builder,
        gender,
        race,
        charClass,
        worldId,
        locX,
        locY,
        locZ,
        hp,
        mp,
        maxHp,
        maxMp,
        spellPoint,
        expPoint,
        level,
        align,
        pk,
        duel,
        pkPardon,
        underware,
        rightEar,
        leftEar,
        neck,
        rightFinger,
        leftFinger,
        head,
        rightHand,
        leftHand,
        gloves,
        chest,
        legs,
        feet,
        back,
        bothHand,
        abnormalEffects,
        faceIndex,
        hairShapeIndex,
        hairColorIndex,
        isInVehicle);

    ::wcscpy(m_nickName, nickName);
    ::memcpy(m_powerFlag, powerFlag, sizeof(m_powerFlag));

    CWareHouse* inventory = new CWareHouse();
    inventory->SetOwnerId(charId);
    inventory->Init(WareHouseType_Inventory, true);
    m_inventory.SetObject(inventory);
    inventory->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    CWareHouse* warehouse = new CWareHouse();
    warehouse->SetOwnerId(charId);
    warehouse->Init(WareHouseType_CharWarehouse, true);
    m_warehouse.SetObject(warehouse);
    warehouse->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
}

// L2CacheD 0x004633D0
CUser::~CUser()
{
}

// L2CacheD 0x0045B390
void* CUser::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CUser");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CUser::s_nAlloc]);

    Allocator::s_classRefNames[CUser::s_nAlloc] = "CUser";
    Allocator::g_allocatedMemory[CUser::s_nAlloc] = sizeof(CUser);

    return memory;
}

// L2CacheD inlined in 0x00463390
void CUser::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CUser at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x0045F210
void CUser::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CUser(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CUser] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CUser::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CUser]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CUser::s_nAlloc]);
        }
        return;
    }

    this->~CUser();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CUser::s_nAlloc]);
}

// L2CacheD 0x0045B700
void CUser::SetChanged(
    uint32_t pledgeId,
    int builder,
    int gender,
    int race,
    int charClass,
    int worldId,
    int locX,
    int locY,
    int locZ,
    double hp,
    double mp,
    double maxHp,
    double maxMp,
    int spellPoint,
    int expPoint,
    int level,
    uint32_t align,
    int pk,
    int duel,
    int pkPardon,
    int underware,
    int rightEar,
    int leftEar,
    int neck,
    int rightFinger,
    int leftFinger,
    int head,
    int rightHand,
    int leftHand,
    int gloves,
    int chest,
    int legs,
    int feet,
    int back,
    int bothHand,
    int faceIndex,
    int hairShapeIndex,
    int hair,
    bool isInVehicle)
{
    guard(L"CUser::SetChanged...");

    m_rwLock.WriteLock();

    m_pledgeId = pledgeId;
    m_builder = builder;
    m_gender = gender;
    m_race = race;
    m_class = charClass;
    m_worldId = worldId;
    m_locX = locX;
    m_locY = locY;
    m_locZ = locZ;
    m_isInVehicle = isInVehicle;
    m_hp = hp;
    m_mp = mp;
    m_maxHp = maxHp;
    m_maxMp = maxMp;
    m_sp = spellPoint;
    m_exp = expPoint;
    m_level = level;
    m_align = align;
    m_pk = pk;
    m_duel = duel;
    m_pkPardon = pkPardon;
    m_underware = underware;
    m_rightEar = rightEar;
    m_leftEar = leftEar;
    m_neck = neck;
    m_rightFinger = rightFinger;
    m_leftFinger = leftFinger;
    m_head = head;
    m_rightHand = rightHand;
    m_leftHand = leftHand;
    m_gloves = gloves;
    m_chest = chest;
    m_legs = legs;
    m_feet = feet;
    m_back = back;
    m_bothHand = bothHand;
    m_hairColorIndex = hair;
    m_hairShapeIndex = hairShapeIndex;
    m_faceIndex = faceIndex;

    m_rwLock.WriteUnlock();

    unguard();
}

bool CUser::IsLoggedIn() const
{
    return m_loggedIn;
}

// L2CacheD 0x0045BCC0
void CUser::LoadQuestFromDB()
{
    guard(L"CUser::LoadQuestFromDB()");

    for (int i = 0; i < QUEST_SIZE; ++i)
    {
        m_quests[i].j1 = 0;
        m_quests[i].questId = 0;
        m_quests[i].state = 0;
    }

    DBConn sql;

    for (int i = 0; i < QUEST_SIZE; ++i)
    {
        sql.Bind(&m_quests[i].questId);
        sql.Bind(&m_quests[i].state);
        sql.Bind(&m_quests[i].j1);
    }

    if (sql.Execute(L"EXEC lin_LoadQuest %d", m_charId))
    {
        if (!sql.Fetch())
        {
            g_winlog.Add(LOG_ERROR, L"Loadquest fetch error. char id[%d]", m_charId);
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"Loadquest exec error. char id[%d]", m_charId);
    }

    unguard();
}

// L2CacheD 0x0045FDC0
void CUser::LoadQuest(CServerSocket* serverSocket, uint32_t ownerId, int a4)
{
    guard(L"CUser::LoadQuest(CSocket* pSocket, int nOwnerId, void *pCUserSocket)");

    if (serverSocket == NULL)
    {
        unguard();
        return;
    }

    m_rwLock.ReadLock();

    uint8_t buff[BUFFER_SIZE];
    int totalSize = 0;
    for (int i = 0; i < QUEST_SIZE; ++i)
    {
        int assembledSize = PacketUtils::Assemble(&buff[totalSize], BUFFER_SIZE - totalSize, "ddd", m_quests[i].questId, m_quests[i].state, m_quests[i].j1);
        if (assembledSize > 0)
        {
            totalSize += assembledSize;
        }
    }

    uint8_t questFlag[CBitStorage::FLAGS_BUFFER_SIZE];
    ::memset(questFlag, 0, sizeof(questFlag));
    m_oneTimeQuests.GetFlagAll(questFlag);
    int questFlagAssembledSize = PacketUtils::Assemble(&buff[totalSize], BUFFER_SIZE - totalSize, "b", sizeof(questFlag), questFlag);
    if (questFlagAssembledSize > 0)
    {
        totalSize += questFlagAssembledSize;
    }

    m_rwLock.ReadUnlock();

    serverSocket->Send("cdb", CacheToServerPacket_LoadQuestPacket, a4, totalSize, buff);

    unguard();
}

// L2CacheD 0x0045E080
bool CUser::SetSelectedQuest(uint32_t questId, int questState)
{
    guard(L"int CUser::SetSelectedQuest(int nQuestId, int nQuestState)");

    WriteLock();

    Quest* quest = m_quests;
    int questIndex = 0;
    while (quest->questId != questId)
    {
        ++questIndex;
        ++quest;
        if (questIndex >= QUEST_SIZE)
        {
            // No quests with this ID found.
            questIndex = 0;
            quest = m_quests;

            // Looking for first empty quest and set it
            while (quest->questId != 0)
            {
                ++questIndex;
                ++quest;
                if (questIndex >= QUEST_SIZE)
                {
                    WriteUnlock();
                    unguard();
                    return false;
                }
            }
            m_quests[questIndex].questId = questId;
            break;
        }
    }

    m_quests[questIndex].state = questState;

    WriteUnlock();

    unguard();
    return true;
}

// L2CacheD 0x0045E140
bool CUser::DeleteSelectedQuest(uint32_t questId)
{
    guard(L"int CUser::DeleteSelectedQuest(int nQuestId)");

    WriteLock();

    int questIndex = 0;
    Quest* quest = m_quests;
    while (quest->questId != questId)
    {
        ++questIndex;
        ++quest;
        if (questIndex >= QUEST_SIZE)
        {
            WriteUnlock();
            unguard();
            return false;
        }
    }

    m_quests[questIndex].questId = 0;
    m_quests[questIndex].state = 0;

    WriteUnlock();
    unguard();
    return true;
}

// L2CacheD 0x0045F950
void CUser::SaveOneTimeQuest()
{
    guard(L"CUser::SaveOneTimeQuest");

    uint8_t questFlag[CBitStorage::FLAGS_BUFFER_SIZE];
    ::memset(questFlag, 0, sizeof(questFlag));
    m_oneTimeQuests.GetFlagAll(questFlag);

    SQLLEN pcbValue = sizeof(questFlag);
    DBConn sql;
    sql.BindParam(1, SQL_CHAR, SQL_BINARY, SQL_BINARY, sizeof(questFlag), 0, (SQLPOINTER)questFlag, sizeof(questFlag), &pcbValue);

    long before = ::GetTickCount();
    wchar_t sqlQuery[1024];
    //::swprintf(sqlQuery, L"UPDATE user_data set quest_flag = ? WHERE char_id=%d", m_charId); FIXED
    const wchar_t UPDATE_QUERY[] = L"UPDATE user_data set quest_flag = ? WHERE char_id=%d";
    ::swprintf(sqlQuery, sizeof sqlQuery / sizeof sqlQuery[0], UPDATE_QUERY, m_charId);

    SQLRETURN sqlResult = sql.ExecuteOptimized(sqlQuery);
    long after = ::GetTickCount();

    uint32_t duration = after - before;
    if (duration > 1000)
    {
        g_qsCheck.AddSlowQs(sqlQuery, duration);
    }

    if (duration > Config::s_sqlExecLimit)
    {
        g_winlog.Add(LOG_ERROR, L"sql execution time [%d]ms, sql[%s]", duration, sqlQuery);
    }

    if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
    {
        g_winlog.Add(LOG_ERROR, sqlQuery);
    }

    unguard();
}

// L2CacheD 0x0045FB30
void CUser::SetQuest(const uint8_t* packet, uint32_t userId)
{
    guard(L"CUser::SetQuest");

    UNUSED(userId);

    bool changed = false;
    m_rwLock.WriteLock();

    const uint8_t* restOfPacket = packet;
    for (int i = 0; i < QUEST_SIZE; ++i)
    {
        Quest& quest = m_quests[i];
        int j1 = quest.j1;
        int questState = quest.state;
        int questId = quest.questId;

        int receivedQuestId = 0;
        int receivedState = 0;
        int receivedJ1 = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "ddd", &receivedQuestId, &receivedState, &receivedJ1);

        if ((questId != receivedQuestId) || (questState != receivedState) || (j1 != receivedJ1))
        {
            quest.state = receivedState;
            quest.questId = receivedQuestId;
            quest.j1 = receivedJ1;
            changed = true;

            const wchar_t* accountName = GetAccountName();
            const wchar_t* charName = GetCharName();
            int newQuestState = quest.state;
            int newQuestId = quest.questId;
            int locZ = GetZ();
            int locY = GetY();
            int locX = GetX();
            uint32_t accountId = GetAccountID();
            uint32_t charId = GetId();
            g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,,,,,,,,%s,%s,,,", LogId_SaveQuest, charId, accountId, locX, locY, locZ, i, newQuestId, newQuestState, charName, accountName);
        }
    }

    uint8_t oldQuestFlags[CBitStorage::FLAGS_BUFFER_SIZE];
    m_oneTimeQuests.GetFlagAll(oldQuestFlags);

    m_oneTimeQuests.SetFlagAll(restOfPacket);

    uint32_t newQuestFlags[CBitStorage::CHUNK_COUNT];
    ::memcpy(newQuestFlags, restOfPacket, sizeof(newQuestFlags));

    m_rwLock.WriteUnlock();

    if (::memcmp(oldQuestFlags, newQuestFlags, CBitStorage::FLAGS_BUFFER_SIZE) != 0)
    {
        const wchar_t* accountName = GetAccountName();
        const wchar_t* charName = GetCharName();
        int quests224_255 = newQuestFlags[7];
        int quests192_223 = newQuestFlags[6];
        int quests160_191 = newQuestFlags[5];
        int quests128_159 = newQuestFlags[4];
        int quests96_127 = newQuestFlags[3];
        int quests64_95 = newQuestFlags[2];
        int quests32_63 = newQuestFlags[1];
        int quests0_31 = newQuestFlags[0];
        int locZ = GetZ();
        int locY = GetY();
        int locX = GetX();
        uint32_t accountId = GetAccountID();
        uint32_t charId = GetId();
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,,,", LogId_SaveOnetimeQuest, charId, accountId, locX, locY, locZ, quests0_31, quests32_63, quests64_95, quests96_127, quests128_159, quests160_191, quests192_223, quests224_255, charName, accountName);

        SaveOneTimeQuest();
    }

    if (changed)
    {
        SaveMemo();
    }

    unguard();
}

// L2CacheD 0x004609B0
void CUser::SetOneTimeQuest(uint32_t id, bool swap)
{
    guard(L"int CUser::SetOneTimeQuest(int nId, bool bSw)");

    WriteLock();
    m_oneTimeQuests.SetFlag(id, swap);
    WriteUnlock();

    unguard();
}

void CUser::SetQuestFlags(const uint8_t* questFlags)
{
    m_oneTimeQuests.SetFlagAll(questFlags);
}

// L2CacheD 0x00462C10
void CUser::LoadAquireSkill()
{
    m_lock.Enter(0, 0);

    uint32_t skillId = 0;
    int skillLevel = 0;
    std::time_t toEndTime = 0;

    DBConn sql;
    sql.Bind(&skillId);
    sql.Bind(&skillLevel);
    sql.Bind(reinterpret_cast<uint32_t*>(&toEndTime));

    if (!sql.Execute(L"EXEC lin_GetAquireSkill %d", m_charId))
    {
        m_lock.Leave(0, 0);
        return;
    }

    m_skillLevels.clear();

    while (sql.Fetch())
    {
        m_skillLevels[skillId] = skillLevel;
        if (toEndTime > 0)
        {
            if (toEndTime <= std::time(NULL))
            {
                SetSkillCoolTime(skillId, 0, true);
            }
            else
            {
                SetSkillCoolTime(skillId, toEndTime, false);
            }
        }

        skillId = 0;
        skillLevel = 0;
        toEndTime = 0;
    }

    m_lock.Leave(0, 0);
}

// L2CacheD 0x004611E0
void CUser::SendAquireSkill(CServerSocket* serverSocket, int serverId)
{
    guard(L"CUser::SendAquireSkill");

    m_lock.Enter(0, 0);

    int payloadSize = 0;
    uint8_t buff[BUFFER_SIZE];
    int skillCount = 0;
    for (SkillLevelMap::iterator levelIt = m_skillLevels.begin(); levelIt != m_skillLevels.end(); ++levelIt)
    {
        SkillLevelMap::value_type& skillLevelPair = *levelIt;

        int cooldown = 0;
        SkillCooldownMap::iterator skillCdIt = m_activeSkillsCooldowns.find(skillLevelPair.first);
        if (skillCdIt != m_activeSkillsCooldowns.end())
        {
            cooldown = static_cast<int>(skillCdIt->second);
            int skillId = skillCdIt->first;
            if ((cooldown > 0) && (cooldown < std::time(NULL)))
            {
                cooldown = 0;
                skillCdIt->second = 0;
                DBConn sql;
                sql.Execute(L"EXEC lin_SetSkillCoolTime %d, %d, %d", m_charId, skillId, 0);
            }
        }

        int assembledSize = PacketUtils::Assemble(&buff[payloadSize], BUFFER_SIZE - payloadSize, "ddd", skillLevelPair.first, skillLevelPair.second, cooldown);
        if (assembledSize > 0)
        {
            payloadSize += assembledSize;
            ++skillCount;
        }
    }

    m_lock.Leave(0, 0);

    if (skillCount <= 0)
    {
        serverSocket->Send("cddd", CacheToServerPacket_AquiredSkillList, serverId, m_charId, 0);
    }
    else
    {
        serverSocket->Send("cdddb", CacheToServerPacket_AquiredSkillList, serverId, m_charId, skillCount, payloadSize, buff);
    }

    unguard();
}

// L2CacheD 0x00462730
bool CUser::AquireSkill(uint32_t skillId, int skillLevel, bool forced)
{
    if (skillLevel <= 0)
    {
        return false;
    }

    WriteLock();

    m_lock.Enter(0, 0);

    int& currentSkillLevel = m_skillLevels[skillId];
    if (!forced)
    {
        if (currentSkillLevel >= skillLevel)
        {
            m_lock.Leave(0, 0);
            WriteUnlock();
            return false;
        }
    }
    currentSkillLevel = skillLevel;

    DBConn sql;
    sql.Execute(L"EXEC lin_SetAquireSkill %d, %d, %d", m_charId, skillId, skillLevel);
    m_lock.Leave(0, 0);

    WriteUnlock();
    return true;
}

// L2CacheD 0x00462870
bool CUser::SetSkillCoolTime(uint32_t skillId, std::time_t toEndTime, bool updateDb)
{
    if (skillId == 0)
    {
        return false;
    }

    WriteLock();

    m_lock.Enter(0, 0);

    SkillCooldownMap::iterator existed = m_activeSkillsCooldowns.find(skillId);
    if (existed == m_activeSkillsCooldowns.end())
    {
        m_activeSkillsCooldowns[skillId] = toEndTime;
    }
    else
    {
        existed->second = toEndTime;
    }

    if (updateDb)
    {
        DBConn sql;
        sql.Execute(L"EXEC lin_SetSkillCoolTime %d, %d, %d", m_charId, skillId, toEndTime);
    }

    m_lock.Leave(0, 0);

    WriteUnlock();
    return true;
}

// L2CacheD 0x00462DD0
bool CUser::DeleteSkill(uint32_t skillId)
{
    guard(L"bool CUser::DeleteSkill(uint32_t skillId)");  // FIXED: added

    if (skillId == 0)
    {
        unguard();  // FIXED: added
        return false;
    }

    WriteLock();

    m_lock.Enter(0, 0);
    m_skillLevels.erase(skillId);
    m_activeSkillsCooldowns.erase(skillId);
    m_lock.Leave(0, 0);

    DBConn sql;
    sql.Execute(L"EXEC lin_DelAquireSkill %d, %d", m_charId, skillId);

    WriteUnlock();

    unguard();  // FIXED: added
    return true;
}

// L2CacheD 0x0045D000
bool CUser::SurrenderPersonally(uint32_t warId)
{
    guard(L"bool CUser::SurrenderPersonally(uint32_t nWarId)");

    int rowCount = 0;
    DBConn sql;
    sql.Bind(&rowCount);
    if (sql.Execute(L"EXEC lin_SurrenderPersonally %d, %d", m_charId, warId))
    {
        sql.Fetch();
    }
    if (rowCount == 0)
    {
        unguard();
        return false;
    }

    if (!AddSurrenderWar(warId))
    {
        g_winlog.Add(LOG_ERROR, L"Surrender War Overflow User[%d], War[%d]", m_charId, warId);
    }

    unguard();
    return true;
}

uint32_t* CUser::GetPersonalSurrenderWarId()
{
    return m_personalSurrenderWarId;
}

// L2CacheD 0x0045CEF0
void CUser::LoadSurrenderPersonally()
{
    uint32_t surrenderWarId = 0;
    DBConn sql;
    sql.Bind(&surrenderWarId);
    if (sql.Execute(L"lin_GetSurrenderWarId %d", m_charId))
    {
        ::memset(m_personalSurrenderWarId, 0, sizeof(m_personalSurrenderWarId));
        for (int i = 0; sql.Fetch(); ++i)
        {
            m_personalSurrenderWarId[i] = surrenderWarId;
        }
    }
}

// L2CacheD 0x0045F580
void CUser::WriteLogin(uint32_t charId)
{
    guard(L"CUser::WriteLogin");

    if (m_loggedIn)
    {
        g_winlog.Add(LOG_ERROR, L"Invalid WriteLogin %s(%d), %s(%d)", m_charName, charId, m_accountName, m_accountId);
        unguard();
        return;
    }

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_CharLogin %d", charId))
    {
        unguard();
        return;
    }

    m_loginTime = ::GetTickCount();
    m_lastUpdateTime = ::GetTickCount();
    m_loggedIn = true;
    ::InterlockedIncrement(&CUser::s_loggedUsers);

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,", LogId_EnterWorld, charId, m_accountId, m_locX, m_locY, m_locZ, m_race, m_gender, m_class, m_level, s_loggedUsers, m_charName, m_accountName);

    unguard();
}

// L2CacheD 0x0045F740
void CUser::WriteLogout(uint32_t charId, int someFlag)
{
    guard(L"CUser::WriteLogout");

    if (!m_loggedIn)
    {
        g_winlog.Add(LOG_ERROR, L"Invalid WriteLogout %s(%d), %s(%d), (%d)", m_charName, charId, m_accountName, m_accountId, someFlag);
        unguard();
        return;
    }

    long usedTimeSec = (::GetTickCount() - m_loginTime) / 1000;
    m_usedTime += usedTimeSec;

    DBConn sql;
    if (sql.Execute(L"EXEC lin_CharLogout %d, %d", charId, usedTimeSec))
    {
        m_loggedIn = false;
        ::InterlockedDecrement(&CUser::s_loggedUsers);
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%u,,,,,,%s,%s,,,", LogId_LeaveWorld, charId, m_accountId, m_locX, m_locY, m_locZ, m_race, m_gender, m_class, m_level, usedTimeSec, m_charName, m_accountName);
    }

    SYSTEMTIME nowTime;
    ::GetLocalTime(&nowTime);
    SetLastLogout(nowTime.wYear, nowTime.wMonth, nowTime.wDay, nowTime.wHour, nowTime.wMinute, nowTime.wSecond);

    unguard();
}

// L2CacheD 0x0045E7C0
void CUser::SetLastLogout(int lastYear, int lastMonth, int lastDay, int lastHour, int lastMin, int lastSec)
{
    guard(L"void CUser::SetLastLogout(int last_year, int last_month, int last_day, int last_hour, int last_min, int last_sec);");
    if (lastYear >= 0)
    {
        m_lastTime.wYear = lastYear;
        m_lastTime.wMonth = lastMonth;
        m_lastTime.wDay = lastDay;
        m_lastTime.wHour = lastHour;
        m_lastTime.wMinute = lastMin;
        m_lastTime.wSecond = lastSec;
    }

    unguard();
}

// L2CacheD 0x0045E870
void CUser::LoadLastLogout()
{
    guard(L"void CUser::LoadLastLogout()");

    int lastYear = 0;
    int lastMonth = 0;
    int lastDay = 0;
    int lastHour = 0;
    int lastMin = 0;
    int lastSec = 0;
    DBConn sql;
    SQLLEN len = -1;
    sql.BindNullable(&lastYear, &len);
    sql.BindNullable(&lastMonth, &len);
    sql.BindNullable(&lastDay, &len);
    sql.BindNullable(&lastHour, &len);
    sql.BindNullable(&lastMin, &len);
    sql.BindNullable(&lastSec, &len);
    if (sql.Execute(L"EXEC lin_LoadLastLogout %d", m_charId) && sql.Fetch() && lastYear >= 0)
    {
        SetLastLogout(lastYear, lastMonth, lastDay, lastHour, lastMin, lastSec);
    }

    unguard();
}

// L2CacheD 0x0045DC30
void CUser::AddUserLog(UserLogId logId, int logFrom, int logTo, int newUseTime, int usedTimeSec)
{
    guard(L"int CUser::AddUserLog(int nLogId, int nLogFrom, int nLogTo, uint32_t nNewUseTime, int nUseTime)");

    m_loginTime = ::GetTickCount();
    m_usedTime += usedTimeSec;
    DBConn sql;
    sql.Execute(L"EXEC lin_UpdateUseTime %d, %d", m_charId, usedTimeSec);
    sql.Execute(L"EXEC lin_AddUserLog %d,%d,%d,%d,%d", m_charId, logId, logFrom, logTo, newUseTime);

    unguard();
}

// L2CacheD 0x0045DD70
int CUser::GetUserLog(UserLogId logId, int logTo)
{
    guard(L"int CUser::GetUserLog(int nLogId, int nLogTo)");

    SQLLEN len = -1;
    int useTime = 0;
    DBConn sql;
    sql.BindNullable(&useTime, &len);
    if (sql.Execute(L"EXEC lin_GetUserLogTime %d, %d, %d", m_charId, logId, logTo))
    {
        sql.Fetch();
    }

    unguard();

    return useTime;
}

// L2CacheD 0x0045D690
bool CUser::SetDeleted()
{
    guard(L"CUser::SetDeleted()");

    int year = 0;
    int month = 0;
    int day = 0;
    DBConn sql;
    sql.Bind(&year);
    sql.Bind(&month);
    sql.Bind(&day);
    if (!sql.Execute(L"EXEC lin_SetCharacterDelete %d", m_charId))
    {
        unguard();
        return false;
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,,,%d,%d,%d,%d,,,,,,,%s,%s,,,", LogId_DeleteChar, m_charId, m_accountId, m_charName, m_race, m_gender, m_class, m_level, m_charName, m_accountName);
    if (!sql.Fetch())
    {
        unguard();
        return false;
    }

    m_deleteYear = year;
    m_deleteMonth = month;
    m_deleteDay = day;

    unguard();
    return true;
}

// L2CacheD 0x0045D840
void CUser::RestoreDeleted()
{
    guard(L"CUser::RestoreDeleted()");
    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SetCharacterDeleteRestore %d", m_charId))
    {
        unguard();
        return;
    }

    m_deleteYear = 0;
    m_deleteMonth = 0;
    m_deleteDay = 0;

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,,,,,%s,%s,,,", LogId_RestoreDeletedChar, m_charId, m_accountId, m_locX, m_locY, m_locZ, m_race, m_gender, m_class, m_level, m_charName, m_accountName);

    unguard();
}

// It is a little-known fact that not every fourth year is a leap year.
// In short, a year is a leap year if it is divisible by four, UNLESS it is also divisible by 100.
// A year is NOT a leap year if it is divisible by 100 UNLESS it is also divisible by 400.
static bool isLeapYear(int year)
{
    const bool leapYearNow = ((year % 4) == 0) && ((year % 100) != 0);
    return leapYearNow;
}

// L2CacheD 0x0045D9B0
int CUser::GetDeletedElapsedDay() const
{
    guard(L"CUser::GetDeletedElapsedDay()");

    if (m_deleteYear == 0)
    {
        unguard();
        return 0;
    }

    SYSTEMTIME now;
    ::GetLocalTime(&now);

    const int daysInYear[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    const int daysInLeapYear[13] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

    const int nowDayFromTheBeginningOfYear = ::isLeapYear(now.wYear) ? (daysInLeapYear[now.wMonth - 1] + now.wDay) : (daysInYear[now.wMonth - 1] + now.wDay);
    const int deletedDayFromTheBeginningOfYear = ::isLeapYear(m_deleteYear) ? (daysInLeapYear[m_deleteMonth - 1] + m_deleteDay) : (daysInYear[m_deleteMonth - 1] + m_deleteDay);

    int elapsedYearDaysFromDeletion = 1;
    for (int deleteYear = m_deleteYear; deleteYear < now.wYear; ++deleteYear)
    {
        if (::isLeapYear(deleteYear))
        {
            elapsedYearDaysFromDeletion += 366;
        }
        else
        {
            elapsedYearDaysFromDeletion += 365;
        }
    }

    int totalElapsedDaysFromDeletion = elapsedYearDaysFromDeletion + nowDayFromTheBeginningOfYear - deletedDayFromTheBeginningOfYear;

    unguard();
    return totalElapsedDaysFromDeletion;
}

int CUser::GetLoginTime() const
{
    return m_loginTime;
}

int CUser::GetUsedTime() const
{
    return m_usedTime;
}

// L2CacheD 0x00460B10
bool CUser::DelItem(uint32_t itemId)
{
    guard(L"int CUser::DelItem(int nItemId)");

    CItemSP item = CItem::Load(itemId);
    if (item == NULL)
    {
        unguard();
        return false;
    }

    item->setOwnerID(0);
    item->Save();
    item->Delete(false);

    unguard();
    return true;
}

// L2CacheD 0x00460BF0
bool CUser::SetSeizedItemOwner(uint32_t itemId, uint32_t newCharId, CWareHouse* warehouse)
{
    guard(L"bool CUser::SetSeizedItemOwner(int nItemId, int nNewCharId, CWareHouse * pWarehouse)");

    UNUSED(newCharId);

    if (GetItemWare(itemId) != WareHouseType_Seized_CharWarehouse)
    {
        unguard();
        return false;
    }

    CItemSP itemToMove = CItem::Load(itemId);
    if (itemToMove == NULL)
    {
        unguard();
        return false;
    }

    if (itemToMove->OwnerID() != m_charId)
    {
        unguard();
        return false;
    }

    uint32_t warehouseOwnerId = warehouse->GetOwnerId();
    if (itemToMove->OwnerID() != warehouseOwnerId)
    {
        unguard();
        return false;
    }

    warehouse->WriteLock();

    ItemConsumeType consumeType = g_itemData.GetConsumeType(itemToMove->ItemType());
    switch (consumeType)
    {
        case ConsumeType_Asset:
        case ConsumeType_Stackable:
        {
            CItemSP warehouseItem = warehouse->GetItemByType(itemToMove->ItemType(), 0);
            if (warehouseItem != NULL)
            {
                int warehouseItemAmount = warehouseItem->Amount();
                int newAmount = itemToMove->Amount() + warehouseItemAmount;
                warehouseItem->SetAmount(newAmount);
                warehouseItem->Save();
                itemToMove->Delete(true);
            }
            else
            {
                itemToMove->setOwnerID(warehouse->GetOwnerId());
                WareHouseType warehouseType = warehouse->GetWarehouseNum();
                itemToMove->SetWarehouse(warehouseType);
                itemToMove->Save();
                warehouse->PushItem(itemToMove.get());
            }
        }
        break;
        case ConsumeType_Normal:
        case ConsumeType_Charge:
        {
            itemToMove->setOwnerID(warehouse->GetOwnerId());
            WareHouseType warehouseType = warehouse->GetWarehouseNum();
            itemToMove->SetWarehouse(warehouseType);
            itemToMove->Save();
            warehouse->PushItem(itemToMove.get());
        }
        break;
        case ConsumeType_Invalid:
            break;
    }

    warehouse->WriteUnlock();

    unguard();
    return true;
}

// L2CacheD 0x00460A40
WareHouseType CUser::GetItemWare(uint32_t itemId)
{
    guard(L"int CUser::GetItemWare(int nItemId)");

    CItemSP item = CItem::Load(itemId);
    if (item == NULL)
    {
        unguard();
        return WareHouseType_Inventory;
    }

    WareHouseType warehouse = item->Warehouse();
    item->Delete(false);

    unguard();
    return warehouse;
}

// L2CacheD 0x00460FA0
CWareHouseSP CUser::GetWareHouse(WareHouseType warehouseType)
{
    guard(L"int CUser::GetItemWare(int nItemId)");

    CWareHouseSP warehouse = (warehouseType == WareHouseType_CharWarehouse) ? m_warehouse.GetObjct() : m_inventory.GetObjct();
    if (warehouse == NULL)
    {
        unguard();
        return CWareHouseSP();
    }

    if (!warehouse->ItemsLoaded())
    {
        warehouse->LoadItems(WareHouseType_Inventory);
    }

    unguard();
    return warehouse;
}

// L2CacheD 0x004606D0
bool CUser::Delete()
{
    guard(L"CUser::Delete()");

    if (Config::s_dbPair)
    {
        DBConn pairDbSql(Pool_PairDb);
        if (!pairDbSql.Execute(L"EXEC lin2user.dbo.lin_MakeCharacterCheckDelete %d, N'%s'", Config::s_worldId, m_charName))
        {
            g_winlog.Add(LOG_ERROR, L"Cannot delete character name from pair db. [%s]", m_charName);
        }
    }

    uint32_t itemId = 0;
    DBConn sql;
    sql.Bind(&itemId);
    if (!sql.Execute(L"EXEC lin_DeleteChar %d", m_charId))
    {
        unguard();
        return false;
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,,,,,%s,%s,,,", LogId_ConfirmDeleteChar, m_charId, m_accountId, m_locX, m_locY, m_locZ, m_race, m_gender, m_class, m_level, m_charName, m_accountName);

    while (sql.Fetch())
    {
        CItemSP loaded = CItem::Load(itemId);
        if (loaded != NULL)
        {
            loaded->Delete(false);
        }
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(m_pledgeId);
    if (pledge != NULL)
    {
        pledge->RemoveMember(m_charId);
    }

    m_pledgeId = 0;

    unguard();
    return true;
}

// L2CacheD 0x0045F340
void CUser::Save()
{
    guard(L"CUser::Save()");

    DBConn sql;
    bool success = sql.Execute(
        L"EXEC lin_SaveCharacter %d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d,%d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
        m_pledgeId,
        m_class,
        m_worldId,
        m_locX,
        m_locY,
        m_locZ,
        m_isInVehicle,
        m_hp,
        m_mp,
        m_maxHp,
        m_maxMp,
        m_sp,
        m_exp,
        m_level,
        m_align,
        m_pk,
        m_duel,
        m_pkPardon,
        m_underware,
        m_rightEar,
        m_leftEar,
        m_neck,
        m_rightFinger,
        m_leftFinger,
        m_head,
        m_rightHand,
        m_leftHand,
        m_gloves,
        m_chest,
        m_legs,
        m_feet,
        m_back,
        m_bothHand,
        m_faceIndex,
        m_hairShapeIndex,
        m_hairColorIndex,
        m_charId);

    if (!success)
    {
        g_winlog.Add(LOG_ERROR, L"Character save error");
    }

    unguard();
}

// L2CacheD 0x0045BA90
void CUser::SaveMemo()
{
    guard(L"CUser::SaveMemo");

    DBConn sql;
    bool success = sql.Execute(
        L"EXEC lin_SetQuest   %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,                  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d,  %d, %d, %d, %d",
        m_quests[0].questId,
        m_quests[0].state,
        m_quests[0].j1,
        m_quests[1].questId,
        m_quests[1].state,
        m_quests[1].j1,
        m_quests[2].questId,
        m_quests[2].state,
        m_quests[2].j1,
        m_quests[3].questId,
        m_quests[3].state,
        m_quests[3].j1,
        m_quests[4].questId,
        m_quests[4].state,
        m_quests[4].j1,
        m_quests[5].questId,
        m_quests[5].state,
        m_quests[5].j1,
        m_quests[6].questId,
        m_quests[6].state,
        m_quests[6].j1,
        m_quests[7].questId,
        m_quests[7].state,
        m_quests[7].j1,
        m_quests[8].questId,
        m_quests[8].state,
        m_quests[8].j1,
        m_quests[9].questId,
        m_quests[9].state,
        m_quests[9].j1,
        m_quests[10].questId,
        m_quests[10].state,
        m_quests[10].j1,
        m_quests[11].questId,
        m_quests[11].state,
        m_quests[11].j1,
        m_quests[12].questId,
        m_quests[12].state,
        m_quests[12].j1,
        m_quests[13].questId,
        m_quests[13].state,
        m_quests[13].j1,
        m_quests[14].questId,
        m_quests[14].state,
        m_quests[14].j1,
        m_quests[15].questId,
        m_quests[15].state,
        m_quests[15].j1,
        m_charId);

    // FIXED: log added
    if (!success)
    {
        g_winlog.Add(LOG_ERROR, L"Character quest save error");
    }

    unguard();
}

// L2CacheD 0x0045B440
uint32_t CUser::GetId() const
{
    guard(L"CUser::GetId()");
    uint32_t charId = m_charId;
    unguard();
    return charId;
}

// L2CacheD 0x0045C960
const wchar_t* CUser::GetCharNameLow() const
{
    guard(L"CUser::GetCharNameLow");
    unguard();
    return m_charNameLow;
}

// L2CacheD 0x0045C990
const wchar_t* CUser::GetCharName() const
{
    guard(L"CUser::GetCharName");
    unguard();
    return m_charName;
}

// L2CacheD 0x0045C9D0
const wchar_t* CUser::GetAccountName() const
{
    guard(L"CUser::GetAccountName");
    unguard();
    return m_accountName;
}

// L2CacheD 0x0045CA10
uint32_t CUser::GetAccountID() const
{
    guard(L"CUser::GetAccountID");
    uint32_t accountId = m_accountId;
    unguard();
    return accountId;
}

// L2CacheD inlined
void CUser::SetAccountId(uint32_t accountId)
{
    m_accountId = accountId;
}

// L2CacheD 0x00414A60
const wchar_t* CUser::ChangeAccount(const wchar_t* accountName)
{
    return ::wcscpy(m_accountName, accountName);
}

const wchar_t* CUser::GetNickName() const
{
    return m_nickName;
}

void CUser::SetNickName(const wchar_t* nickName)
{
    ::wcscpy(m_nickName, nickName);
}

int CUser::GetStatus() const
{
    return m_status;
}

void CUser::SetStatus(int status)
{
    m_status = status;
}

std::time_t CUser::GetBanEnd() const
{
    return m_banEnd;
}

void CUser::SetBanEnd(std::time_t banEnd)
{
    m_banEnd = banEnd;
}

int CUser::SurrenderWarId() const
{
    return m_surrenderWarId;
}

void CUser::SetSurrenderWarId(int surrenderWarId)
{
    m_surrenderWarId = surrenderWarId;
}

int CUser::GetPledgeWithdrawTime() const
{
    return m_pledgeWithdrawTime;
}

void CUser::SetPledgeWithdrawTime(int pledgeWithdrawTime)
{
    m_pledgeWithdrawTime = pledgeWithdrawTime;
}

int CUser::GetPledgeOustedTime() const
{
    return m_pledgeOustedTime;
}

void CUser::SetPledgeOustedTime(int pledgeOustedTime)
{
    m_pledgeOustedTime = pledgeOustedTime;
}

const uint8_t* CUser::GetPowerFlag() const
{
    return m_powerFlag;
}

int CUser::GetPledgeDismissTime() const
{
    return m_pledgeDismissTime;
}

void CUser::SetPledgeDismissTime(int pledgeDismissTime)
{
    m_pledgeDismissTime = pledgeDismissTime;
}

// L2CacheD 0x0045CA50
uint32_t CUser::GetPledgeID() const
{
    guard(L"CUser::GetPledgeID");
    uint32_t pledgeId = m_pledgeId;
    unguard();
    return pledgeId;
}

// L2CacheD 0x0045B960
void CUser::SetPledge(uint32_t pledgeId)
{
    guard(L"CUser::SetPledge");

    m_rwLock.WriteLock();
    m_pledgeId = pledgeId;
    m_rwLock.WriteUnlock();

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SaveCharacterPledge %d,%d", m_pledgeId, m_charId))
    {
        g_winlog.Add(LOG_ERROR, L"Error, Cannot save user pledge id.[%d]user [%d]pledge", m_pledgeId, m_charId);
    }

    unguard();
}

// L2CacheD 0x0045CA90
int CUser::GetBuilder() const
{
    guard(L"CUser::GetBuilder");
    int builder = m_builder;
    unguard();
    return builder;
}

// L2CacheD 0x0045CAD0
int CUser::GetGender() const
{
    guard(L"CUser::GetGender");
    int gender = m_gender;
    unguard();
    return gender;
}

// L2CacheD 0x0045CB10
int CUser::GetRace() const
{
    guard(L"CUser::GetRace");
    int race = m_race;
    unguard();
    return race;
}

// L2CacheD 0x0045CB50
int CUser::GetClass() const
{
    guard(L"CUser::GetClass");
    int charClass = m_class;
    unguard();
    return charClass;
}

// L2CacheD 0x0045CB90
int CUser::GetWorld() const
{
    guard(L"CUser::GetWorld");
    int worldId = m_worldId;
    unguard();
    return worldId;
}

// L2CacheD 0x0045CBD0
int CUser::GetX() const
{
    guard(L"CUser::GetX");
    int locX = m_locX;
    unguard();
    return locX;
}

// L2CacheD 0x0045CC10
int CUser::GetY() const
{
    guard(L"CUser::GetY");
    int locY = m_locY;
    unguard();
    return locY;
}

// L2CacheD 0x0045CC50
int CUser::GetZ() const
{
    guard(L"CUser::GetZ");
    int locZ = m_locZ;
    unguard();
    return locZ;
}

// L2CacheD 0x0045CC90
double CUser::GetHP() const
{
    guard(L"CUser::GetHP");
    double hp = m_hp;
    unguard();
    return hp;
}

double CUser::GetMaxHP()
{
    if (m_maxHp <= 0.0)
    {
        if (m_hp <= 0.0)
        {
            m_maxHp = 1.0;
        }
        else
        {
            m_maxHp = m_hp;
        }
    }

    return m_maxHp;
}

// L2CacheD 0x0045CCE0
double CUser::GetMP() const
{
    guard(L"CUser::GetMP");
    double mp = m_mp;
    unguard();
    return mp;
}

double CUser::GetMaxMP()
{
    if (m_maxMp <= 0.0)
    {
        if (m_mp <= 0.0)
        {
            m_maxMp = 1.0;
        }
        else
        {
            m_maxMp = m_mp;
        }
    }

    return m_maxMp;
}

// L2CacheD 0x0045CD30
int CUser::GetSP() const
{
    guard(L"CUser::GetSP");
    int spellPoint = m_sp;
    unguard();
    return spellPoint;
}

// L2CacheD 0x0045CD70
int CUser::GetExp() const
{
    guard(L"CUser::GetExp");
    int exp = m_exp;
    unguard();
    return exp;
}

// L2CacheD 0x0045CDB0
int CUser::GetLevel() const
{
    guard(L"CUser::GetLevel");
    int level = m_level;
    unguard();
    return level;
}

// L2CacheD 0x0045CDF0
uint32_t CUser::GetAlign() const
{
    guard(L"CUser::GetAlign");
    int align = m_align;
    unguard();
    return align;
}

// L2CacheD 0x0045CE30
int CUser::GetPK() const
{
    guard(L"CUser::GetPK");
    int pk = m_pk;
    unguard();
    return pk;
}

// L2CacheD 0x0045CE70
int CUser::GetDuel() const
{
    guard(L"CUser::GetDuel");
    int duel = m_duel;
    unguard();
    return duel;
}

// L2CacheD 0x0045CEB0
int CUser::GetPKPardon() const
{
    guard(L"CUser::GetPKPardon");
    int pkPardon = m_pkPardon;
    unguard();
    return pkPardon;
}

int CUser::GetDropExp() const
{
    return m_dropExp;
}

// L2CacheD 0x0045E320
void CUser::SetDropExp(int dropExp)
{
    guard(L"void CUser::SetDropExp(int nDropExp);");
    m_dropExp = dropExp;
    return unguard();
}

// L2CacheD 0x0045E4B0
int CUser::GetPlayDiff()
{
    guard(L"int CUser::GetPlayDiff()");

    DWORD now = ::GetTickCount();
    int diffMs = now - m_lastUpdateTime;
    m_lastUpdateTime = now;
    unguard();
    return diffMs / 1000;
}

// L2CacheD 0x0045E500
int CUser::GetExpDiff()
{
    guard(L"int CUser::GetExpDiff()");

    int expDiff = m_exp - m_lastUpdateExp;
    m_lastUpdateExp = m_exp;

    unguard();
    return expDiff;
}

// L2CacheD 0x0045E3D0
void CUser::IncreasePKCount()
{
    guard(L"void CUser::IncreasePKCount()");

    // FIXED! Max karma value for 1 PK is 1200240
    // const int ALIGN_LIMIT = INT_MAX - 20000;
    const int ALIGN_LIMIT = INT_MAX - 1200250;

    ++m_pk;
    if (m_align < ALIGN_LIMIT)
    {
        m_align += CalcKarma(m_pk, m_pkPardon);
        m_align = min(INT_MAX, m_align);  // FIXED to avoid overflow!
    }

    unguard();
}

// L2CacheD 0x0045E470
void CUser::IncreaseDuelCount()
{
    guard(L"void CUser::IncreaseDuelCount()");
    ++m_duel;
    unguard();
}

// L2CacheD 0x0045BE20
int CUser::GetUnderware() const
{
    guard(L"CUser::GetUnderware");
    int underware = m_underware;
    unguard();
    return underware;
}

// L2CacheD 0x0045C1E0
void CUser::RemoveUnderware(int id)
{
    guard(L"void CUser::RemoveUnderware(int nId)");
    if (id == GetUnderware())
    {
        m_underware = 0;
    }
    unguard();
}

// L2CacheD 0x0045BE60
int CUser::GetRightEar() const
{
    guard(L"CUser::GetRight_ear");
    int rightEar = m_rightEar;
    unguard();
    return rightEar;
}

// L2CacheD 0x0045C260
void CUser::RemoveRightEar(int id)
{
    guard(L"void CUser::RemoveRight_ear(int nId)");
    if (id == GetRightEar())
    {
        m_rightEar = 0;
    }
    unguard();
}

// L2CacheD 0x0045BEA0
int CUser::GetLeftEar() const
{
    guard(L"CUser::GetLeft_ear");
    int leftEar = m_leftEar;
    unguard();
    return leftEar;
}

// L2CacheD 0x0045C2E0
void CUser::RemoveLeftEar(int id)
{
    guard(L"void CUser::RemoveLeft_ear(int nId)");
    if (id == GetLeftEar())
    {
        m_leftEar = 0;
    }
    unguard();
}

// L2CacheD 0x0045BEE0
int CUser::GetNeck() const
{
    guard(L"CUser::GetNeck");
    int neck = m_neck;
    unguard();
    return neck;
}

// L2CacheD 0x0045C360
void CUser::RemoveNeck(int id)
{
    guard(L"void CUser::RemoveNeck(int nId)");
    if (id == GetNeck())
    {
        m_neck = 0;
    }
    unguard();
}

// L2CacheD 0x0045BF20
int CUser::GetRightFinger() const
{
    guard(L"CUser::GetRight_finger");
    int rightFinger = m_rightFinger;
    unguard();
    return rightFinger;
}

// L2CacheD 0x0045C3E0
void CUser::RemoveRightFinger(int id)
{
    guard(L"void CUser::RemoveRight_finger(int nId)");
    if (id == GetRightFinger())
    {
        m_rightFinger = 0;
    }
    unguard();
}

// L2CacheD 0x0045BF60
int CUser::GetLeftFinger() const
{
    guard(L"CUser::GetLeft_finger");
    int leftFinger = m_leftFinger;
    unguard();
    return leftFinger;
}

// L2CacheD 0x0045C460
void CUser::RemoveLeftFinger(int id)
{
    guard(L"void CUser::RemoveLeft_finger(int nId)");
    if (id == GetLeftFinger())
    {
        m_leftFinger = 0;
    }
    unguard();
}

// L2CacheD 0x0045BFA0
int CUser::GetHead() const
{
    guard(L"CUser::GetHead");
    int head = m_head;
    unguard();
    return head;
}

// L2CacheD 0x0045C4E0
void CUser::RemoveHead(int id)
{
    guard(L"void CUser::RemoveHead(int nId)");
    if (id == GetHead())
    {
        m_head = 0;
    }
    unguard();
}

// L2CacheD 0x0045BFE0
int CUser::GetRightHand() const
{
    guard(L"CUser::GetRight_hand");
    int rightHand = m_rightHand;
    unguard();
    return rightHand;
}

// L2CacheD 0x0045C560
void CUser::RemoveRightHand(int id)
{
    guard(L"void CUser::RemoveRight_hand(int nId)");
    if (id == GetRightHand())
    {
        m_rightHand = 0;
    }
    unguard();
}

// L2CacheD 0x0045C020
int CUser::GetLeftHand() const
{
    guard(L"CUser::GetLeft_hand");
    int leftHand = m_leftHand;
    unguard();
    return leftHand;
}

// L2CacheD 0x0045C5E0
void CUser::RemoveLeftHand(int id)
{
    guard(L"void CUser::RemoveLeft_hand(int nId)");
    if (id == GetLeftHand())
    {
        m_leftHand = 0;
    }
    unguard();
}

// L2CacheD 0x0045C060
int CUser::GetGloves() const
{
    guard(L"CUser::GetGloves");
    int gloves = m_gloves;
    unguard();
    return gloves;
}

// L2CacheD 0x0045C660
void CUser::RemoveGloves(int id)
{
    guard(L"void CUser::RemoveGloves(int nId)");
    if (id == GetGloves())
    {
        m_gloves = 0;
    }
    unguard();
}

// L2CacheD 0x0045C0A0
int CUser::GetChest() const
{
    guard(L"CUser::GetChest");
    int chest = m_chest;
    unguard();
    return chest;
}

// L2CacheD 0x0045C6E0
void CUser::RemoveChest(int id)
{
    guard(L"void CUser::RemoveChest(int nId)");
    if (id == GetChest())
    {
        m_chest = 0;
    }
    unguard();
}

// L2CacheD 0x0045C0E0
int CUser::GetLegs() const
{
    guard(L"CUser::GetLegs");
    int legs = m_legs;
    unguard();
    return legs;
}

// L2CacheD 0x0045C760
void CUser::RemoveLegs(int id)
{
    guard(L"void CUser::RemoveLegs(int nId)");
    if (id == GetLegs())
    {
        m_legs = 0;
    }
    unguard();
}

// L2CacheD 0x0045C120
int CUser::GetFeet() const
{
    guard(L"CUser::GetFeet");
    int feet = m_feet;
    unguard();
    return feet;
}

// L2CacheD 0x0045C7E0
void CUser::RemoveFeet(int id)
{
    guard(L"void CUser::RemoveFeet(int nId)");
    if (id == GetFeet())
    {
        m_feet = 0;
    }
    unguard();
}

// L2CacheD 0x0045C160
int CUser::GetBack() const
{
    guard(L"CUser::GetBack");
    int back = m_back;
    unguard();
    return back;
}

// L2CacheD 0x0045C860
void CUser::RemoveBack(int id)
{
    guard(L"void CUser::RemoveBack(int nId)");
    if (id == GetBack())
    {
        m_back = 0;
    }
    unguard();
}

// L2CacheD 0x0045C1A0
int CUser::GetBothHand() const
{
    guard(L"CUser::GetBoth_hand");
    int bothHand = m_bothHand;
    unguard();
    return bothHand;
}

// L2CacheD 0x0045C8E0
void CUser::RemoveBothHand(int id)
{
    guard(L"void CUser::RemoveBoth_hand(int nId)");
    if (id == GetBothHand())
    {
        m_bothHand = 0;
    }
    unguard();
}

int CUser::GetHairColorIndex() const
{
    return m_hairColorIndex;
}
int CUser::GetHairShapeIndex() const
{
    return m_hairShapeIndex;
}
int CUser::GetFaceIndex() const
{
    return m_faceIndex;
}

// L2CacheD 0x0045E1F0
void CUser::ShowPetiMsg(CServerSocket* serverSocket)
{
    guard(L"CUser::ShowPetiMsg(CSocket* pSocket)");

    wchar_t msg[502];
    DBConn sql;
    sql.Bind(msg, sizeof(msg));
    if (sql.Execute(L"EXEC lin_GetPetitionMsg %d", m_charId) && sql.Fetch())
    {
        serverSocket->Send("cdS", CacheToServerPacket_ShowPetitionMsg, m_charId, msg);
    }

    unguard();
}

// L2CacheD 0x0045D140
void CUser::SendBlockList(CServerSocket* serverSocket, int serverId)
{
    guard(L"SendBlockList(CSocket* pSocket, uint32_t nUserServerId)");

    int blockCharId = 0;
    wchar_t blockCharName[24];
    ::memset(blockCharName, 0, sizeof(blockCharName));

    DBConn sql;
    sql.Bind(&blockCharId);
    sql.Bind(blockCharName, sizeof(blockCharName));
    if (!sql.Execute(L"EXEC lin_LoadBlockList %d", m_charId))
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyBlockList, serverId, 0);
        unguard();
        return;
    }

    uint8_t buffer[BUFFER_SIZE];
    int blockedPayloadSize = 0;
    int blockedCharacters = 0;
    while (sql.Fetch())
    {
        int assembledSize = PacketUtils::Assemble(&buffer[blockedPayloadSize], BUFFER_SIZE - blockedPayloadSize, "dS", blockCharId, blockCharName);
        if (assembledSize > 0)
        {
            blockedPayloadSize += assembledSize;
            ++blockedCharacters;
        }
        ::memset(blockCharName, 0, sizeof(blockCharName));
    }

    if (blockedCharacters > 0)
    {
        serverSocket->Send("cddb", CacheToServerPacket_ReplyBlockList, serverId, blockedCharacters, blockedPayloadSize, buffer);
    }
    else
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyBlockList, serverId, blockedCharacters);
    }

    unguard();
}

// L2CacheD 0x0045D310
bool CUser::ChangeLocationExtern(const wchar_t* charName, int worldId, int x, int y, int z, bool save)
{
    guard(L"bool CUser::ChangeLocationExtern(wchar_t * wcharName, int world, int x, int y, int z, bool bSave)");

    UNUSED(save);

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);
    if (sql.Execute(L"EXEC lin_ChangeCharacterLocation N'%s', %d, %d, %d, %d", charName, worldId, x, y, z) && sql.Fetch() && charId > 0)
    {
        m_rwLock.WriteLock();
        m_worldId = worldId;
        m_locX = x;
        m_locY = y;
        m_locZ = z;
        m_rwLock.WriteUnlock();

        unguard();
        return true;
    }

    unguard();
    return false;
}

// L2CacheD 0x0045D480
bool CUser::SetBuilderLevExtern(const wchar_t* charName, int builderLev)
{
    guard(L"bool CUser::SetBuilderLevExtern(wchar_t * wcharName, int nBuilderLev)");

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);
    if (sql.Execute(L"EXEC lin_SetBuilderCharacter N'%s', %d", charName, builderLev) && sql.Fetch() && charId > 0)
    {
        m_rwLock.WriteLock();
        m_builder = builderLev;
        m_rwLock.WriteUnlock();
        unguard();
        return true;
    }

    unguard();
    return false;
}

// L2CacheD 0x0045FF50
bool CUser::ModCharExtern(uint32_t nSP, uint32_t exp, int align, int pk, uint32_t pkPardon, uint32_t duel)
{
    guard(L"bool CUser::ModCharExtern(uint32_t nSP, uint32_t nExp, int nAlign, int nPK, uint32_t nPKPardon, uint32_t nDuel)");

    WriteLock();
    m_pkPardon = pkPardon;
    m_sp = nSP;
    m_exp = exp;
    m_lastUpdateExp = exp;
    m_align = align;
    m_pk = pk;
    m_duel = duel;

    DBConn sql;
    bool result = sql.Execute(L" EXEC lin_ModChar %d, %d, %d, %d, %d, %d, %d", m_sp, m_exp, m_align, m_pk, m_pkPardon, m_duel, m_charId);

    WriteUnlock();
    unguard();

    return result;
}

// L2CacheD 0x004600C0
bool CUser::ModChar2Extern(int gender, int race, int charClass, int faceIndex, int hairShape, int hairColor)
{
    guard(L"bool CUser::ModChar2Extern(int nGender, int nRace, int nClass, int nFace, int nHairShape, int nHairColor )");

    WriteLock();

    m_hairShapeIndex = hairShape;
    m_gender = gender;
    m_race = race;
    m_class = charClass;
    m_faceIndex = faceIndex;
    m_hairColorIndex = hairColor;

    DBConn sql;
    bool result = sql.Execute(L"EXEC lin_ModChar2 %d, %d, %d, %d, %d, %d, %d", m_gender, m_race, m_class, m_faceIndex, m_hairShapeIndex, m_hairColorIndex, m_charId);

    WriteUnlock();
    unguard();

    return result;
}

// L2CacheD 0x00460220
bool CUser::ModChar3Extern(int nSP, int expDiff, int alignDiff, int pkDiff, int plPardonDiff, int duelDiff)
{
    guard(L"bool CUser::ModChar3Extern(int nSP, int nExp, int nAlign, int nPK, int nPKPardon, int nDuel)");

    WriteLock();

    m_exp += expDiff;
    m_sp += nSP;
    m_lastUpdateExp += expDiff;
    m_align += alignDiff;
    m_pk += pkDiff;
    m_pkPardon += plPardonDiff;
    m_duel += duelDiff;

    DBConn sql;
    bool result = sql.Execute(L"EXEC lin_ModChar3 %d, %d, %d, %d, %d, %d, %d", nSP, expDiff, alignDiff, pkDiff, plPardonDiff, duelDiff, m_charId);

    WriteUnlock();
    unguard();

    return result;
}

// L2CacheD 0x004603C0
bool CUser::ModCharNicknameExtern(const wchar_t* nickName)
{
    guard(L"bool CUser::ModCharPledgeExtern(wchar_t* wNickName)");

    WriteLock();
    if (nickName != NULL)
    {
        ::wcscpy(m_nickName, nickName);
    }
    else
    {
        ::memset(m_nickName, 0, sizeof(m_nickName));
    }

    int resultCode = 0;
    DBConn sql;
    sql.Bind(&resultCode);
    bool result = sql.Execute(L"EXEC lin_SetUserNickname %d, N'%s'", m_charId, nickName);

    WriteUnlock();
    unguard();

    return result;
}

// L2CacheD 0x00463D50
bool CUser::ChangeCharacterNameExtern(const wchar_t* oldName, const wchar_t* newName)
{
    guard(L"bool CUser::ChangeCharacternameExtern(wchar_t * woldCharNameLow, wchar_t * wnewCharName)");

    wchar_t sqlQuery[512];
    ::wsprintfW(sqlQuery, L"EXEC lin_ChangeCharacterName N'%s', N'%s'", oldName, newName);
    g_winlog.Add(LOG_REQUEST, L"ChangeCharacternameExtern. sql(%s)", sqlQuery);

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);
    if (sql.Execute(L"EXEC lin_ChangeCharacterName N'%s', N'%s'", oldName, newName) && sql.Fetch() && charId > 0)
    {
        m_rwLock.WriteLock();
        ::memset(m_charNameLow, 0, sizeof(m_charNameLow));  // FIXED: added
        Utils::CopyStrInLowerCase(newName, m_charNameLow);
        ::wcscpy(m_charName, newName);
        m_rwLock.WriteUnlock();

        g_userDb.RefreshMaps(oldName, m_charNameLow);
        g_friendsDb.ChangeFriendName(m_charId, m_charName);
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,,,,,,,%s,%s,,,", LogId_ChangeName, m_charId, m_accountId, m_locX, m_locY, m_locZ, newName, m_race, m_gender, m_class, m_level, oldName, m_accountName);

        unguard();
        return true;
    }

    unguard();
    return false;
}

// L2CacheD 0x0045DE90
bool CUser::CharAudit(int adenaSum, int defaultPriceSum, int itemSum)
{
    guard(L"bool CUser::CharAudit(int nAdenaSum, int nDefaultPriceSum, int nItemSum)");

    if (!m_auditNeeded)
    {
        m_adenaSum = adenaSum;
        m_defaultPriceSum = defaultPriceSum;
        m_itemSum = itemSum;
        m_auditNeeded = true;

        unguard();
        return true;
    }

    int priceSumDiff = 0;
    if (defaultPriceSum <= m_defaultPriceSum)
    {
        priceSumDiff = m_defaultPriceSum - defaultPriceSum;
    }
    else
    {
        priceSumDiff = defaultPriceSum - m_defaultPriceSum;
    }

    int adenaSumDiff = 0;
    int prevAdenaSum = m_adenaSum;
    if (adenaSum <= prevAdenaSum)
    {
        adenaSumDiff = prevAdenaSum - adenaSum;
    }
    else
    {
        adenaSumDiff = adenaSum - prevAdenaSum;
    }

    int priceSum = defaultPriceSum;
    if (defaultPriceSum >= m_defaultPriceSum)
    {
        priceSum = m_defaultPriceSum;
    }

    int devider = defaultPriceSum;
    int changeRatio = 0;
    if (priceSum >= 1)
    {
        if (defaultPriceSum >= m_defaultPriceSum)
        {
            devider = m_defaultPriceSum;
        }
        changeRatio = 100 * (priceSumDiff / devider);
    }
    else
    {
        changeRatio = 100;
    }

    int adenaRatioDiff = adenaSum;
    if (adenaSum >= prevAdenaSum)
    {
        adenaRatioDiff = prevAdenaSum;
    }

    int adenaChangeRatio = 0;
    if (adenaRatioDiff >= 1)
    {
        if (adenaSum < prevAdenaSum)
        {
            prevAdenaSum = adenaSum;
        }
        adenaChangeRatio = 100 * (adenaSumDiff / prevAdenaSum);
    }
    else
    {
        adenaChangeRatio = 100;
    }

    if ((priceSumDiff >= Config::s_defaultPriceLimit) || ((defaultPriceSum >= Config::s_defaultPriceCheck) && (changeRatio >= Config::s_chgRatioLimit)) || (adenaSumDiff >= Config::s_adenaLimit) || ((adenaSum >= Config::s_adenaCheck) && (adenaChangeRatio >= Config::s_adenaChgRatioLimit)))
    {
        g_winlog.Add(LOG_AUDIT, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,", LogId_CacheDAuditItemInfo, m_charId, m_accountId, m_locX, m_locY, m_locZ, adenaSum, defaultPriceSum, itemSum, prevAdenaSum, m_defaultPriceSum, m_itemSum, m_charName, m_accountName);
    }

    m_itemSum = itemSum;
    m_adenaSum = adenaSum;
    m_defaultPriceSum = defaultPriceSum;

    unguard();
    return true;
}

// L2CacheD 0x004610F0
void CUser::PrintCharWarehouseData()
{
    guard(L"void CUser::PrintCharWarehouseData()");

    // Looks like C1 doesn't have implementation... it all what was in binary
    // CWareHouseSP inventory = GetWareHouse(WareHouseType_Inventory);
    // inventory->OnWaitCallback();
    //
    // CWareHouseSP warehouse = GetWareHouse(WareHouseType_CharWarehouse);
    // warehouse->OnWaitCallback();

    unguard();
}

// L2CacheD 0x0045E580
void CUser::PrintCharData()
{
    guard(L"void CUser::PrintCharData()");

    double maxMp = 0.0;
    if (m_maxMp <= 0.0)
    {
        if (m_mp <= 0.0)
        {
            maxMp = 1.0;
        }
        else
        {
            maxMp = m_mp;
        }
    }
    else
    {
        maxMp = m_maxMp;
    }

    double maxHp = 0.0;
    if (m_maxHp <= 0.0)
    {
        if (m_hp <= 0.0)
        {
            maxHp = 1.0;
        }
        else
        {
            maxHp = m_hp;
        }
    }
    else
    {
        maxHp = m_maxHp;
    }

    g_winlog.Add(
        LOG_INF,
        L"%s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
        m_accountName,
        m_charName,
        m_accountId,
        m_charId,
        m_pledgeId,
        m_builder,
        m_gender,
        m_race,
        m_class,
        m_worldId,
        m_locX,
        m_locY,
        m_locZ,
        m_isInVehicle,
        m_hp,
        m_mp,
        maxHp,
        maxMp,
        m_sp,
        m_exp,
        m_level,
        m_align,
        m_pk,
        m_duel,
        m_pkPardon,
        m_faceIndex,
        m_hairShapeIndex,
        m_hairColorIndex);

    unguard();
}

// L2CacheD 0x0045D5B0
void CUser::WriteLock()
{
    guard(L"CUser::WriteLock()");
    m_rwLock.WriteLock();
    unguard();
}

// L2CacheD 0x0045D620
void CUser::WriteUnlock()
{
    guard(L"CUser::WriteUnlock()");
    m_rwLock.WriteUnlock();
    unguard();
}

// L2CacheD 0x0045E360
int CUser::CalcKarma(int newPkCount, int pkPardon)
{
    guard(L"User::CalcKarma()");

    int karmaLimit = newPkCount - pkPardon - 1;
    if (karmaLimit < 0)
    {
        karmaLimit = 0;
    }
    else
    {
        if (karmaLimit >= 10000)
        {
            karmaLimit = 10000;
        }
    }
    unguard();

    return 240 * static_cast<int>(double(karmaLimit) * 0.5 + 1.0);
}

// L2CacheD 0x0045B480
void CUser::Set(
    uint32_t pledgeId,
    int builder,
    int gender,
    int race,
    int charClass,
    int worldId,
    int locX,
    int locY,
    int locZ,
    double hp,
    double mp,
    double maxHp,
    double maxMp,
    int spellPoint,
    int expPoint,
    int level,
    uint32_t align,
    int pk,
    int duel,
    int pkPardon,
    int underware,
    int rightEar,
    int leftEar,
    int neck,
    int rightFinger,
    int leftFinger,
    int head,
    int rightHand,
    int leftHand,
    int gloves,
    int chest,
    int legs,
    int feet,
    int back,
    int bothHand,
    const AbnormalEffect* abnormalEffects,
    int faceIndex,
    int hairShapeIndex,
    int hairColorIndex,
    bool isInVehicle)
{
    guard(L"CUser::Set...");

    m_rwLock.WriteLock();
    m_pledgeId = pledgeId;
    m_builder = builder;
    m_gender = gender;
    m_race = race;
    m_class = charClass;
    m_worldId = worldId;
    m_locX = locX;
    m_locY = locY;
    m_locZ = locZ;
    m_isInVehicle = isInVehicle;
    m_hp = hp;
    m_mp = mp;
    m_maxHp = maxHp;
    m_maxMp = maxMp;
    m_sp = spellPoint;
    m_exp = expPoint;
    m_level = level;
    m_align = align;
    m_pk = pk;
    m_duel = duel;
    m_pkPardon = pkPardon;
    m_underware = underware;
    m_rightEar = rightEar;
    m_leftEar = leftEar;
    m_neck = neck;
    m_rightFinger = rightFinger;
    m_leftFinger = leftFinger;
    m_head = head;
    m_rightHand = rightHand;
    m_leftHand = leftHand;
    m_gloves = gloves;
    m_chest = chest;
    m_legs = legs;
    m_feet = feet;
    m_back = back;
    m_bothHand = bothHand;
    m_hairColorIndex = hairColorIndex;
    m_hairShapeIndex = hairShapeIndex;
    m_faceIndex = faceIndex;

    if (abnormalEffects != NULL)
    {
        ::memcpy(m_abnormalEffects, abnormalEffects, sizeof(m_abnormalEffects));
    }

    m_rwLock.WriteUnlock();

    unguard();
}

// L2CacheD 0x0045B400
bool CUser::AddSurrenderWar(uint32_t warId)
{
    int counter = 0;
    uint32_t* personalSurrenderWarId = m_personalSurrenderWarId;
    while (*personalSurrenderWarId != 0)
    {
        ++counter;
        ++personalSurrenderWarId;
        if (counter >= SURRENDER_WAR_SIZE)
        {
            return false;
        }
    }

    m_personalSurrenderWarId[counter] = warId;
    return true;
}

bool CUser::IsInVehicle() const
{
    return m_isInVehicle;
}

const AbnormalEffect* CUser::GetAbnormalEffects() const
{
    return m_abnormalEffects;
}

void CUser::SetAbnormalEffects(const AbnormalEffect* abnormalEffects)
{
    memcpy(m_abnormalEffects, abnormalEffects, ABNORMAL_EFFECT_SIZE * sizeof(AbnormalEffect));
}

const SYSTEMTIME& CUser::GetLastTime() const
{
    return m_lastTime;
}
