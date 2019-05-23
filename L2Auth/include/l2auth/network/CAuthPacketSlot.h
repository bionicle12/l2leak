#pragma once

#include "l2auth/threads/CLock.h"

class CAuthPacket;
class CAuthSocket;

class CAuthPacketSlot
{
public:
    CAuthPacketSlot();  // L2AuthD 0x00431D90
    ~CAuthPacketSlot();

    union
    {
        CAuthPacket* packet;
        CAuthSocket* socket;
    } m_data;
    CLock m_lock;
};
