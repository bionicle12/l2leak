#pragma once

#include "l2auth/CIOObject.h"

#include <l2core/utils/cstdint_support.h>

class WorldSrvSocket;
class CIOBuffer;

class WorldSrvPacket : public CIOObject
{
public:
    WorldSrvPacket();   // L2AuthD 0x0041E100
    ~WorldSrvPacket();  // L2AuthD 0x0041E150

    static WorldSrvPacket* Alloc();  // L2AuthD 0x0041DE1D
    static void FreeAll();           // L2AuthD 0x0041DF2E

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x0041DFBC
    void Free();                                                                                // L2AuthD 0x0041DEDF

public:
    static LONG g_nPendingPacket;

    WorldSrvSocket* m_pSocket;
    CIOBuffer* m_pBuf;

    typedef bool (*PacketFunc)(WorldSrvSocket*, uint8_t* packet);
    PacketFunc m_pFunc;
};
