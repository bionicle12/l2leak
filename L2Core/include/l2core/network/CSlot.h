#pragma once

#include "l2core/threads/SpinLock.h"

class CPacket;
class CIOSocket;

class CSlot
{
public:
    CSlot();
    ~CSlot();

    union
    {
        CPacket* packet;
        CIOSocket* socket;
    } m_data;

    SpinLock m_lock;
};
