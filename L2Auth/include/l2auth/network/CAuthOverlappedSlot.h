#pragma once

#include "l2auth/threads/CLock.h"

class CAuthOverlapped;

class CAuthOverlappedSlot
{
public:
    CAuthOverlappedSlot();
    ~CAuthOverlappedSlot();

    union
    {
        CAuthOverlapped* overlapped;
        CAuthOverlappedSlot* slot;
    } m_data;

    CLock m_lock;
};
