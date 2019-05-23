#pragma once

#include "l2auth/CIOObject.h"

#include <l2core/utils/cstdint_support.h>

class CLogSocket;
class CIOBuffer;

class CLogPacket : public CIOObject
{
public:
    CLogPacket();   // L2AuthD 0x0042F440
    ~CLogPacket();  // L2AuthD 0x0042F490

    static CLogPacket* Alloc();  // L2AuthD 0x0042E87C
    static void FreeAll();       // L2AuthD 0x0042E93E

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x0042EA1B

    void Free();  // L2AuthD 0x0042E9CD

public:
    static LONG g_nPendingPacket;

    CLogSocket* m_pSocket;
    CIOBuffer* m_pBuf;

    typedef bool (*PacketFunc)(CLogSocket*, uint8_t* packet);
    PacketFunc m_pFunc;
};
