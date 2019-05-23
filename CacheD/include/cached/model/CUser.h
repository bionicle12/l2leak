#pragma once

#include "cached/model/AbnormalEffect.h"
#include "cached/model/CBitStorage.h"
#include "cached/model/CWareHouse.h"
#include "cached/model/Quest.h"
#include "cached/model/WareHouseType.h"
#include "l2core/MemoryObject.h"
#include "l2core/threads/CIOCriticalSection.h"
#include "l2core/threads/CObjectMap.h"
#include "l2core/threads/CSPointer.h"

#include <ctime>
#include <map>

#include <l2core/utils/cstdint_support.h>

class CUser;
typedef CSPointer<CUser> CUserSP;

class CServerSocket;

enum UserLogId
{
    UserLogId_NewLevel = 1,
    UserLogId_NewClass = 2
};

class CUser : public MemoryObject
{
public:
    CUser(
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
        int GetPledgeDismissTime,
        int GetPledgeOustedTime,
        int GetPledgeWithdrawTime,
        uint32_t SurrenderWarId,
        int useTime,
        int tempDeleteDateYear,
        int tempDeleteDateMonth,
        int tempDeleteDateDay);  // L2CacheD 0x00464160

    ~CUser();  // L2CacheD 0x004633D0

    static void* operator new(size_t size);  // L2CacheD 0x0045B390
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x00463390

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x0045F210

    void SetChanged(
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
        bool isInVehicle);  // L2CacheD 0x0045B700

    bool IsLoggedIn() const;                                            // L2CacheD inlined
    void LoadQuestFromDB();                                             // L2CacheD 0x0045BCC0
    void LoadQuest(CServerSocket* gsSocket, uint32_t ownerId, int a4);  // L2CacheD 0x0045FDC0
    bool SetSelectedQuest(uint32_t questId, int questState);            // L2CacheD 0x0045E080
    bool DeleteSelectedQuest(uint32_t questId);                         // L2CacheD 0x0045E140
    void SaveOneTimeQuest();                                            // L2CacheD 0x0045F950
    void SetQuest(const uint8_t* packet, uint32_t userId);              // L2CacheD 0x0045FB30
    void SetOneTimeQuest(uint32_t id, bool swap);                       // L2CacheD 0x004609B0
    void SetQuestFlags(const uint8_t* questFlags);

    void LoadAquireSkill();                                                         // L2CacheD 0x00462C10
    void SendAquireSkill(CServerSocket* gsSocket, int serverId);                    // L2CacheD 0x004611E0
    bool AquireSkill(uint32_t skillId, int skillLevel, bool forced);                // L2CacheD 0x00462730
    bool SetSkillCoolTime(uint32_t skillId, std::time_t toEndTime, bool updateDb);  // L2CacheD 0x00462870
    bool DeleteSkill(uint32_t skillId);                                             // L2CacheD 0x00462DD0

    bool SurrenderPersonally(uint32_t warId);  // L2CacheD 0x0045D000
    uint32_t* GetPersonalSurrenderWarId();
    void LoadSurrenderPersonally();  // L2CacheD 0x0045CEF0

    void WriteLogin(uint32_t charId);                                                                      // L2CacheD 0x0045F580
    void WriteLogout(uint32_t charId, int someFlag);                                                       // L2CacheD 0x0045F740
    void SetLastLogout(int lastYear, int lastMonth, int lastDay, int lastHour, int lastMin, int lastSec);  // L2CacheD 0x0045E7C0
    void LoadLastLogout();                                                                                 // L2CacheD 0x0045E870
    void AddUserLog(UserLogId logId, int logFrom, int logTo, int newUseTime, int usedTimeSec);             // L2CacheD 0x0045DC30
    int GetUserLog(UserLogId logId, int logTo);                                                            // L2CacheD 0x0045DD70
    bool SetDeleted();                                                                                     // L2CacheD 0x0045D690
    void RestoreDeleted();                                                                                 // L2CacheD 0x0045D840
    int GetDeletedElapsedDay() const;                                                                      // L2CacheD 0x0045D9B0
    int GetLoginTime() const;
    int GetUsedTime() const;

    bool DelItem(uint32_t itemId);                                                        // L2CacheD 0x00460B10
    bool SetSeizedItemOwner(uint32_t itemId, uint32_t newCharId, CWareHouse* warehouse);  // L2CacheD 0x00460BF0
    WareHouseType GetItemWare(uint32_t itemId);                                           // L2CacheD 0x00460A40
    CWareHouseSP GetWareHouse(WareHouseType warehouseType);                               // L2CacheD 0x00460FA0

    bool Delete();    // L2CacheD 0x004606D0
    void Save();      // L2CacheD 0x0045F340
    void SaveMemo();  // L2CacheD 0x0045BA90

    uint32_t GetId() const;                                    // L2CacheD 0x0045B440
    const wchar_t* GetCharName() const;                        // L2CacheD 0x0045C990
    const wchar_t* GetCharNameLow() const;                     // L2CacheD 0x0045C960
    const wchar_t* GetAccountName() const;                     // L2CacheD 0x0045C9D0
    uint32_t GetAccountID() const;                             // L2CacheD 0x0045CA10
    void SetAccountId(uint32_t accountId);                     // L2CacheD inlined
    const wchar_t* ChangeAccount(const wchar_t* accountName);  // L2CacheD 0x00414A60

    const wchar_t* GetNickName() const;
    void SetNickName(const wchar_t* nickName);

    /*!
     * 0 - normal
     * 1 - ban
     */
    int GetStatus() const;
    void SetStatus(int status);

    std::time_t GetBanEnd() const;
    void SetBanEnd(std::time_t banEnd);

    const uint8_t* GetPowerFlag() const;

    int GetPledgeDismissTime() const;
    void SetPledgeDismissTime(int GetPledgeDismissTime);

    int GetPledgeOustedTime() const;
    void SetPledgeOustedTime(int GetPledgeOustedTime);

    int GetPledgeWithdrawTime() const;
    void SetPledgeWithdrawTime(int GetPledgeWithdrawTime);

    int SurrenderWarId() const;
    void SetSurrenderWarId(int SurrenderWarId);

    uint32_t GetPledgeID() const;       // L2CacheD 0x0045CA50
    void SetPledge(uint32_t pledgeId);  // L2CacheD 0x0045B960

    int GetBuilder() const;        // L2CacheD 0x0045CA90
    int GetGender() const;         // L2CacheD 0x0045CAD0
    int GetRace() const;           // L2CacheD 0x0045CB10
    int GetClass() const;          // L2CacheD 0x0045CB50
    int GetWorld() const;          // L2CacheD 0x0045CB90
    int GetX() const;              // L2CacheD 0x0045CBD0
    int GetY() const;              // L2CacheD 0x0045CC10
    int GetZ() const;              // L2CacheD 0x0045CC50
    double GetHP() const;          // L2CacheD 0x0045CC90
    double GetMaxHP();             // L2CacheD 0x00434F60
    double GetMP() const;          // L2CacheD 0x0045CCE0
    double GetMaxMP();             // L2CacheD 0x00434FA0
    int GetSP() const;             // L2CacheD 0x0045CD30
    int GetExp() const;            // L2CacheD 0x0045CD70
    int GetLevel() const;          // L2CacheD 0x0045CDB0
    uint32_t GetAlign() const;     // L2CacheD 0x0045CDF0
    int GetPK() const;             // L2CacheD 0x0045CE30
    int GetDuel() const;           // L2CacheD 0x0045CE70
    int GetPKPardon() const;       // L2CacheD 0x0045CEB0
    int GetDropExp() const;        // L2CacheD inlined
    void SetDropExp(int dropExp);  // L2CacheD 0x0045E320
    int GetPlayDiff();             // L2CacheD 0x0045E4B0
    int GetExpDiff();              // L2CacheD 0x0045E500

    void IncreasePKCount();    // L2CacheD 0x0045E3D0
    void IncreaseDuelCount();  // L2CacheD 0x0045E470

    int GetUnderware() const;      // L2CacheD 0x0045BE20
    void RemoveUnderware(int id);  // L2CacheD 0x0045C1E0

    int GetRightEar() const;      // L2CacheD 0x0045BE60
    void RemoveRightEar(int id);  // L2CacheD 0x0045C260

    int GetLeftEar() const;      // L2CacheD 0x0045BEA0
    void RemoveLeftEar(int id);  // L2CacheD 0x0045C2E0

    int GetNeck() const;      // L2CacheD 0x0045BEE0
    void RemoveNeck(int id);  // L2CacheD 0x0045C360

    int GetRightFinger() const;      // L2CacheD 0x0045BF20
    void RemoveRightFinger(int id);  // L2CacheD 0x0045C3E0

    int GetLeftFinger() const;      // L2CacheD 0x0045BF60
    void RemoveLeftFinger(int id);  // L2CacheD 0x0045C460

    int GetHead() const;      // L2CacheD 0x0045BFA0
    void RemoveHead(int id);  // L2CacheD 0x0045C4E0

    int GetRightHand() const;      // L2CacheD 0x0045BFE0
    void RemoveRightHand(int id);  // L2CacheD 0x0045C560

    int GetLeftHand() const;      // L2CacheD 0x0045C020
    void RemoveLeftHand(int id);  // L2CacheD 0x0045C5E0

    int GetGloves() const;      // L2CacheD 0x0045C060
    void RemoveGloves(int id);  // L2CacheD 0x0045C660

    int GetChest() const;      // L2CacheD 0x0045C0A0
    void RemoveChest(int id);  // L2CacheD 0x0045C6E0

    int GetLegs() const;      // L2CacheD 0x0045C0E0
    void RemoveLegs(int id);  // L2CacheD 0x0045C760

    int GetFeet() const;      // L2CacheD 0x0045C120
    void RemoveFeet(int id);  // L2CacheD 0x0045C7E0

    int GetBack() const;      // L2CacheD 0x0045C160
    void RemoveBack(int id);  // L2CacheD 0x0045C860

    int GetBothHand() const;      // L2CacheD 0x0045C1A0
    void RemoveBothHand(int id);  // L2CacheD 0x0045C8E0

    bool IsInVehicle() const;  // L2CacheD inlined

    const SYSTEMTIME& GetLastTime() const;

    int GetHairColorIndex() const;
    int GetHairShapeIndex() const;
    int GetFaceIndex() const;

    void ShowPetiMsg(CServerSocket* serverSocket);              // L2CacheD 0x0045E1F0
    void SendBlockList(CServerSocket* gsSocket, int serverId);  // L2CacheD 0x0045D140

    bool ChangeLocationExtern(const wchar_t* charName, int worldId, int x, int y, int z, bool save);        // L2CacheD 0x0045D310
    bool SetBuilderLevExtern(const wchar_t* charName, int builderLev);                                      // L2CacheD 0x0045D480
    bool ModCharExtern(uint32_t nSP, uint32_t exp, int align, int pk, uint32_t pkPardon, uint32_t duel);    // L2CacheD 0x0045FF50
    bool ModChar2Extern(int gender, int race, int charClass, int faceIndex, int hairShape, int hairColor);  // L2CacheD 0x004600C0
    bool ModChar3Extern(int nSP, int expDiff, int alignDiff, int pkDiff, int plPardonDiff, int duelDiff);   // L2CacheD 0x00460220
    bool ModCharNicknameExtern(const wchar_t* nickName);                                                    // L2CacheD 0x004603C0
    bool ChangeCharacterNameExtern(const wchar_t* oldName, const wchar_t* newName);                         // L2CacheD 0x00463D50
    bool CharAudit(int adenaSum, int defaultPriceSum, int itemSum);                                         // L2CacheD 0x0045DE90

    void PrintCharWarehouseData();  // L2CacheD 0x004610F0
    void PrintCharData();           // L2CacheD 0x0045E580

    void WriteLock();    // L2CacheD 0x0045D5B0
    void WriteUnlock();  // L2CacheD 0x0045D620

    const AbnormalEffect* GetAbnormalEffects() const;
    void SetAbnormalEffects(const AbnormalEffect* abnormalEffects);

public:
    static long s_loggedUsers;  // L2CacheD 0x02684584

    static const uint32_t ABNORMAL_EFFECT_SIZE = 20;
    static const uint32_t POWER_FLAG_SIZE = 32;
    static const uint32_t SURRENDER_WAR_SIZE = 10;
    static const uint32_t QUEST_SIZE = 16;

private:
    static int CalcKarma(int newPkCount, int pkPardon);  // L2CacheD 0x0045E360

    void Set(
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
        bool isInVehicle);  // L2CacheD 0x0045B480

    bool AddSurrenderWar(uint32_t warId);  // L2CacheD 0x0045B400

private:
    static long s_nAlloc;  // L2CacheD 0x021EEF88

    typedef std::map<uint32_t, int> SkillLevelMap;
    typedef std::map<uint32_t, std::time_t> SkillCooldownMap;

    CBitStorage m_oneTimeQuests;
    int m_lastUpdateTime;
    int m_lastUpdateExp;
    CRWLock m_rwLock;
    CWareHouseStorage m_inventory;
    CWareHouseStorage m_warehouse;
    wchar_t m_charNameLow[26];  // FIXED: extra bytes added to have null-terminated string
    wchar_t m_charName[26];     // FIXED: extra bytes added to have null-terminated string
    uint32_t m_charId;
    wchar_t m_accountName[26];  // FIXED: extra bytes added to have null-terminated string
    uint32_t m_accountId;
    uint32_t m_pledgeId;
    int m_builder;
    int m_gender;
    int m_race;
    int m_class;
    int m_worldId;
    int m_locX;
    int m_locY;
    int m_locZ;
    bool m_isInVehicle;
    double m_hp;
    double m_mp;
    double m_maxHp;
    double m_maxMp;
    int m_sp;
    int m_exp;
    int m_level;
    int m_dropExp;
    uint32_t m_align;
    int m_pk;
    int m_duel;
    int m_pkPardon;
    int m_underware;
    int m_rightEar;
    int m_leftEar;
    int m_neck;
    int m_rightFinger;
    int m_leftFinger;
    int m_head;
    int m_rightHand;
    int m_leftHand;
    int m_gloves;
    int m_chest;
    int m_legs;
    int m_feet;
    int m_back;
    int m_bothHand;
    int m_hairColorIndex;
    int m_hairShapeIndex;
    int m_faceIndex;
    int16_t m_deleteYear;
    int16_t m_deleteMonth;
    int16_t m_gap;
    int16_t m_deleteDay;
    int field_432;
    int field_436;
    CIOCriticalSection m_lock;
    SkillLevelMap m_skillLevels;
    SkillCooldownMap m_activeSkillsCooldowns;
    SYSTEMTIME m_lastTime;
    AbnormalEffect m_abnormalEffects[ABNORMAL_EFFECT_SIZE];
    wchar_t m_nickName[24];
    uint8_t m_powerFlag[POWER_FLAG_SIZE];
    int m_pledgeDismissTime;
    int m_pledgeOustedTime;
    int m_pledgeWithdrawTime;
    int m_surrenderWarId;
    Quest m_quests[QUEST_SIZE];
    uint32_t m_personalSurrenderWarId[SURRENDER_WAR_SIZE];
    bool m_loggedIn;
    int m_loginTime;
    bool m_auditNeeded;
    int m_adenaSum;
    int m_defaultPriceSum;
    int m_itemSum;
    int m_usedTime;
    int m_status;
    std::time_t m_banEnd;
};
