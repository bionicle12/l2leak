#pragma once

#include <windows.h>

#include <l2core/utils/cstdint_support.h>

class CServerSocket;

class CAnnounce
{
public:
    CAnnounce();   // L2CacheD 0x0047DB20
    ~CAnnounce();  // L2CacheD 0x0049D900

    void ReadAnnounce(bool reload);                                                 // L2CacheD 0x0047DBC0
    bool ShowIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet);  // L2CacheD 0x0047DD60
    bool SetIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet);   // L2CacheD 0x0047DFA0
    bool DelIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet);   // L2CacheD 0x0047E120
    bool LoadIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet);  // L2CacheD 0x0047E260

    int GetLoginAnnoncesNumber() const;
    int GetPacketSize() const;  // L2CacheD 0x0047DD50
    const uint8_t* GetLoginAnnoncesPacket() const;

    void Lock();    // L2CacheD inlined 0x00445C2A
    void Unlock();  // L2CacheD inlined 0x00445C6D

private:
    CRITICAL_SECTION m_lock;
    bool m_loaded;
    uint8_t m_loginAnnoncesPacket[0x1000];
    int m_loginAnnoncesSize;
    int m_loginAnnoncesNumber;
};

extern CAnnounce g_announce;  // L2CacheD 0x0234EFB8
