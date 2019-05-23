#pragma once

#include "cached/model/CCastle.h"
#include "l2core/threads/CObjectMap.h"

#include <l2core/utils/cstdint_support.h>

class CServerSocket;
typedef CObjectMap<CCastle> CCastleMap;

class CCastleDb
{
public:
    CCastleDb();   // L2CacheD 0x0040D040
    ~CCastleDb();  // L2CacheD 0x0049D7A0

    CCastleSP GetCastle(uint32_t castleId);                                                                                                                     // L2CacheD 0x0040D420
    void GetRelatedCastleSiege(int* castleSiegeCount, int* packetSize, uint8_t* responsePacket, uint32_t castleId, uint32_t pledgeId);                          // L2CacheD 0x0040B340
    void GetSiegeRelatedAlliancePledge(int* pledgeCount, int* packetSize, uint8_t* responsePacket, uint32_t castleId, uint32_t allianceId, uint32_t pledgeId);  // L2CacheD 0x0040B4F0

    void SendReplyToLoadCastle(CServerSocket* serverSocket, uint32_t castleId, const wchar_t* castleName);                       // L2CacheD 0x0040BAC0
    void SendReplyToViewSiegeList(CServerSocket* serverSocket, void* userSocket, uint32_t castleId, const wchar_t* returnHtml);  // L2CacheD 0x0040AF50
    void SendReplyToApproveBattle(CServerSocket* serverSocket, void* userSocket, uint32_t castleId, const wchar_t* returnHtml);  // L2CacheD 0x0040B140

private:
    void Add(CCastle* castle);                                                // L2CacheD 0x0040CB40
    CCastleSP LoadFromDb(uint32_t castleId);                                  // L2CacheD 0x0040D2B0
    void LoadCastleCropData(CServerSocket* serverSocket, uint32_t castleId);  // L2CacheD 0x0040ADA0

private:
    CRWLock m_lock;
    CCastleMap m_castles;
};

extern CCastleDb g_castleDb;  // L2CacheD 0x004F2988
