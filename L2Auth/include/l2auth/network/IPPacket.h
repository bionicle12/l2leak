#pragma once

#include "l2auth/CIOObject.h"

#include <l2core/utils/cstdint_support.h>

class IPSocket;
class CIOBuffer;

class IPPacket : public CIOObject
{
public:
    IPPacket();   // L2AuthD 0x00426960
    ~IPPacket();  // L2AuthD 0x004269B0

    static IPPacket* Alloc();  // L2AuthD 0x004245CF
    static void FreeAll();     // L2AuthD 0x00424691

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x0042476E

    void Free();  // L2AuthD 0x0042471F

public:
    static LONG g_nPendingPacket;

    IPSocket* m_pSocket;
    CIOBuffer* m_pBuf;

    typedef bool (*PacketFunc)(IPSocket*, uint8_t* packet);
    PacketFunc m_pFunc;
};
