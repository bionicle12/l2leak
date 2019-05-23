#include "cached/model/CCastleDb.h"

#include "cached/config/Config.h"
#include "cached/model/CCastle.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CCastleDb g_castleDb;  // L2CacheD 0x004F2988

// L2CacheD 0x0040D040
CCastleDb::CCastleDb()
    : m_lock()
    , m_castles()
{
}

// L2CacheD 0x0049D7A0
CCastleDb::~CCastleDb()
{
}

// L2CacheD 0x0040D420
CCastleSP CCastleDb::GetCastle(uint32_t castleId)
{
    guard(L"CCastleSP CCastleDb::GetCastle(int nCastleId)");

    m_lock.WriteLock();  // FIXED: added

    CCastleSP result = m_castles.FindObject(castleId);
    if (result != NULL)
    {
        m_lock.WriteUnlock();  // FIXED: added

        unguard();
        return result;
    }

    result = LoadFromDb(castleId);
    if (result == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] undefined (or unregistered) castle Id[%d]", TEXT(__FILE__), __LINE__, castleId);
        CallStack::ReportCallStack();
    }

    m_lock.WriteUnlock();  // FIXED: added

    unguard();
    return result;
}

// L2CacheD 0x0040B340
void CCastleDb::GetRelatedCastleSiege(int* castleSiegeCount, int* packetSize, uint8_t* responsePacket, uint32_t castleId, uint32_t pledgeId)
{
    guard(L"void CCastleDb::GetRelatedCastleSiege(int *nCastleSiegeCount , int *nBufSize , char *buf, uint32_t nCastleId, uint32_t nPledgeId)");

    int originPacketSize = *packetSize;
    *castleSiegeCount = 0;
    *packetSize = 0;

    uint32_t castleIdOut = 0;
    int nextWarTime = 0;
    int siegeType = 0;

    DBConn sql;
    sql.Bind(&castleIdOut);
    sql.Bind(&nextWarTime);
    sql.Bind(&siegeType);
    if (castleId == 0)
    {
        if (!sql.Execute(L"EXEC lin_GetAllCastleSiege %d", pledgeId))
        {
            *castleSiegeCount = -1;
            unguard();
            return;
        }
    }
    else
    {
        if (!sql.Execute(L"EXEC lin_GetRelatedCastleSiege %d, %d, %d", castleId, pledgeId))
        {
            *castleSiegeCount = -1;
            unguard();
            return;
        }
    }

    for (; sql.Fetch(); ++*castleSiegeCount)
    {
        *packetSize += PacketUtils::Assemble(&responsePacket[*packetSize], originPacketSize - *packetSize, "ddd", castleIdOut, nextWarTime, siegeType);
    }

    unguard();
}

// L2CacheD 0x0040B4F0
void CCastleDb::GetSiegeRelatedAlliancePledge(int* pledgeCount, int* packetSize, uint8_t* responsePacket, uint32_t castleId, uint32_t allianceId, uint32_t pledgeId)
{
    guard(L"void CCastleDb::GetSiegeRelatedAlliancePledge(int *nPledgeCount , int *nBufSize , char *buf, uint32_t nCastleId, uint32_t nAllianceId, uint32_t nPledgeId)");

    int packetSizeOrigin = *packetSize;
    *pledgeCount = 0;
    *packetSize = 0;

    uint32_t dbCastleId = 0;
    uint32_t dbPledgeId = 0;
    int siegeType = 0;

    DBConn sql;
    sql.Bind(&dbCastleId);
    sql.Bind(&dbPledgeId);
    sql.Bind(&siegeType);
    bool success = sql.Execute(L"EXEC lin_GetSiegeRelatedAlliancePledge %d", allianceId);
    if (!success)
    {
        *pledgeCount = -1;
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        if (dbCastleId == castleId && dbPledgeId != pledgeId)
        {
            *packetSize += PacketUtils::Assemble(&responsePacket[*packetSize], packetSizeOrigin - *packetSize, "dd", dbPledgeId, siegeType);
            ++*pledgeCount;
        }
    }

    unguard();
}

// L2CacheD 0x0040BAC0
void CCastleDb::SendReplyToLoadCastle(CServerSocket* serverSocket, uint32_t castleId, const wchar_t* castleName)
{
    guard(L"void CCastleDb::SendReplyToLoadCastle(CSocket *pSocket, uint32_t nCastleId, const wchar_t *sCastleName)");

    uint32_t pledgeId = 0;
    int nextWarTime = 0;
    int taxRate = 0;
    int status = 0;
    int cropIncome = 0;
    int shopIncome = 0;
    int siegeElapsedTime = 0;
    int shopIncomeTemp = 0;
    int taxRateToChange = 0;
    int taxChildRateToChange = 0;
    int taxChildRate = 0;

    wchar_t castleNameOut[256];
    ::memset(castleNameOut, 0, sizeof(castleNameOut));

    DBConn sql;
    sql.Bind(&pledgeId);
    sql.Bind(&nextWarTime);
    sql.Bind(&taxRate);
    sql.Bind(&taxChildRate);
    sql.Bind(&status);
    sql.Bind(castleNameOut, sizeof(castleNameOut));
    sql.Bind(&cropIncome);
    sql.Bind(&shopIncome);
    sql.Bind(&siegeElapsedTime);
    sql.Bind(&shopIncomeTemp);
    sql.Bind(&taxRateToChange);
    sql.Bind(&taxChildRateToChange);
    if (sql.Execute(L"EXEC lin_LoadCastle %d, %d", castleId, 1) && sql.Fetch() || (sql.ResetHtmt(), sql.Execute(L"EXEC lin_CreateCastle %d, N'%s'", castleId, castleName), sql.ResetHtmt(), sql.Execute(L"EXEC lin_LoadCastle %d, %d", castleId, 1)) && sql.Fetch())
    {
        sql.ResetHtmt();

        uint32_t warPledgeId = 0;
        int warType = 0;
        int proposeTime = 0;

        SQLLEN length = -1;
        sql.Bind(&warPledgeId);
        sql.Bind(&warType);
        sql.BindNullable(&proposeTime, &length);
        if (!sql.Execute(L"EXEC lin_LoadCastleWarRelatedPledge %d", castleId) || !sql.Fetch())
        {
            serverSocket->Send("cddddddSddddddd", CacheToServerPacket_LoadCastlePacket, castleId, pledgeId, nextWarTime, taxRate, taxChildRate, status, castleNameOut, cropIncome, shopIncome, siegeElapsedTime, shopIncomeTemp, taxRateToChange, taxChildRateToChange, 0);
            LoadCastleCropData(serverSocket, castleId);

            unguard();
            return;
        }

        int payloadSize = 0;
        int warCount = 0;
        uint8_t buff[8204];
        do
        {
            payloadSize += PacketUtils::Assemble(&buff[payloadSize], 8196 - payloadSize, "ddd", warPledgeId, warType, proposeTime);
            ++warCount;
        } while (sql.Fetch());

        if (warCount)
        {
            serverSocket->Send("cddddddSdddddddb", CacheToServerPacket_LoadCastlePacket, castleId, pledgeId, nextWarTime, taxRate, taxChildRate, status, castleNameOut, cropIncome, shopIncome, siegeElapsedTime, shopIncomeTemp, taxRateToChange, taxChildRateToChange, warCount, payloadSize, buff);
            CCastleDb::LoadCastleCropData(serverSocket, castleId);
        }
        else
        {
            serverSocket->Send("cddddddSddddddd", CacheToServerPacket_LoadCastlePacket, castleId, pledgeId, nextWarTime, taxRate, taxChildRate, status, castleNameOut, cropIncome, shopIncome, siegeElapsedTime, shopIncomeTemp, taxRateToChange, taxChildRateToChange, 0);
            LoadCastleCropData(serverSocket, castleId);
        }
    }
    else
    {
        serverSocket->Send("cddddddSdddd", CacheToServerPacket_LoadCastlePacket, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    unguard();
}

// L2CacheD 0x0040AF50
void CCastleDb::SendReplyToViewSiegeList(CServerSocket* serverSocket, void* userSocket, uint32_t castleId, const wchar_t* returnHtml)
{
    guard(L"void CCastleDb::SendReplyToViewSiegeList(CSocket *pSocket, void *pUserSocket, uint32_t nCastleId, const wchar_t *sReturnHtml)");

    wchar_t pledgeName[24];
    ::memset(pledgeName, 0, sizeof(pledgeName));
    uint32_t pledgeId = 0;

    DBConn sql;
    sql.Bind(&pledgeId);
    sql.Bind(pledgeName, sizeof(pledgeName));
    if (!sql.Execute(L"EXEC lin_ViewSiegeList %d, %d", castleId, 1))
    {
        serverSocket->Send("cddSd", CacheToServerPacket_ReplyViewSiegeList, userSocket, castleId, returnHtml, 0);
        unguard();
        return;
    }

    int payloadSize = 0;
    uint8_t buff[8196];
    int count = 0;
    while (sql.Fetch())
    {
        payloadSize += PacketUtils::Assemble(&buff[payloadSize], 8196 - payloadSize, "dS", pledgeId, pledgeName);
        ++count;
    }
    serverSocket->Send("cddSdb", CacheToServerPacket_ReplyViewSiegeList, userSocket, castleId, returnHtml, count, payloadSize, buff);
    unguard();
}

// L2CacheD 0x0040B140
void CCastleDb::SendReplyToApproveBattle(CServerSocket* serverSocket, void* userSocket, uint32_t castleId, const wchar_t* returnHtml)
{
    guard(L"void CCastleDb::SendReplyToApproveBattle(CSocket *pSocket, void *pUserSocket, uint32_t nCastleId, const wchar_t *sReturnHtml)");

    wchar_t pledgeName[24];
    ::memset(pledgeName, 0, sizeof(pledgeName));
    uint32_t pledgeId = 0;
    int type = 0;

    DBConn sql;
    sql.Bind(&pledgeId);
    sql.Bind(pledgeName, 48);
    sql.Bind(&type);
    if (!sql.Execute(L"EXEC lin_ApproveBattle %d, %d", castleId, 1))
    {
        serverSocket->Send("cddSd", CacheToServerPacket_ReplyApproveBattle, userSocket, castleId, returnHtml, 0);
        unguard();
        return;
    }

    int payloadSize = 0;
    uint8_t buff[8196];
    int count = 0;
    while (sql.Fetch())
    {
        payloadSize += PacketUtils::Assemble(&buff[payloadSize], 8196 - payloadSize, "dSd", pledgeId, pledgeName, type);
        ++count;
    }
    serverSocket->Send("cddSdb", CacheToServerPacket_ReplyApproveBattle, userSocket, castleId, returnHtml, count, payloadSize, buff);
    unguard();
}

// L2CacheD 0x0040CB40
void CCastleDb::Add(CCastle* castle)
{
    guard(L"CCastleDb::Add(CCastle * pCastle)");

    if (castle != NULL)
    {
        m_castles.Insert(castle->id(), castle, NULL, -1);
    }

    unguard();
}

// L2CacheD 0x0040D2B0
CCastleSP CCastleDb::LoadFromDb(uint32_t castleId)
{
    guard(L"CCastleSP CCastleDb::LoadFromDb(int nCastleId)");

    CCastle* castle = new CCastle(castleId);
    Add(castle);

    CCastleSP result(castle, ORT_FUNCTION_CHAIN);
    castle->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
    return result;
}

// L2CacheD 0x0040ADA0
void CCastleDb::LoadCastleCropData(CServerSocket* serverSocket, uint32_t castleId)
{
    guard(L"void CCastleDb::LoadCastleCropData(CSocket *pSocketunsigned, int nCastleId)");

    int itemType = 0;
    int dropRate = 0;
    int price = 0;
    int level = 0;

    DBConn sql;
    sql.Bind(&itemType);
    sql.Bind(&dropRate);
    sql.Bind(&price);
    sql.Bind(&level);
    if (!sql.Execute(L"EXEC lin_LoadCastleCrop %d", castleId))
    {
        unguard();
        return;
    }

    int payloadSize = 0;
    int count = 0;
    uint8_t buff[8196];
    while (sql.Fetch())
    {
        payloadSize += PacketUtils::Assemble(&buff[payloadSize], 8196 - payloadSize, "dddd", itemType, dropRate, price, level);
        ++count;
    }

    if (count != 0)
    {
        serverSocket->Send("cddb", CacheToServerPacket_LoadCropData, castleId, count, payloadSize, buff);
    }

    unguard();
}
