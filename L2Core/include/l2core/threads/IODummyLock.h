#pragma once

#include <crtdefs.h>

class IODummyLock
{
public:
    void Enter(const wchar_t*, intptr_t)
    {
    }

    void Leave(const wchar_t*, intptr_t)
    {
    }
};
