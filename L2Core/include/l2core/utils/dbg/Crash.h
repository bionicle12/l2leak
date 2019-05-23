#pragma once
#include "l2core/utils/dbg/CallStack.h"

#define CRASH_WITH_MSG(MSG)                                                                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                                                                                               \
    do                                                                                                                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                                                                                          \
        CallStack::AddDebugInfo(MSG);                                                                                                                                                                                                                                                                                          \
        int* i = NULL;                                                                                                                                                                                                                                                                                                         \
        *i = 1;                                                                                                                                                                                                                                                                                                                \
                                                                                                                                                                                                                                                                                                                               \
    } while (1)

#define CRASH CRASH_WITH_MSG(L"CRASH!!!")
