#pragma once

#include "l2auth/CIOObject.h"

#include <l2core/utils/cstdint_support.h>

class CWantedSocket;
class CIOBuffer;

class CWantedPacket : public CIOObject
{
public:
    CWantedPacket();   // L2AuthD 0x0043C5F0
    ~CWantedPacket();  // L2AuthD 0x0043C640

    static CWantedPacket* Alloc();  // L2AuthD 0x0043BCEC
    static void FreeAll();          // L2AuthD 0x0043BDAE

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x0043BE8B

    void Free();  // L2AuthD 0x0043BE3C

public:
    static LONG g_nPendingPacket;

    CWantedSocket* m_pSocket;
    CIOBuffer* m_pBuf;

    typedef bool (*PacketFunc)(CWantedSocket*, uint8_t* packet);
    PacketFunc m_pFunc;
};
