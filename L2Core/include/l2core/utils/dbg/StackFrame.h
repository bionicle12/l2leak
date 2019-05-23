#pragma once

struct StackFrame
{
    int stackSize;
    const wchar_t* guardedFuncName;
    wchar_t data[100];
    const wchar_t* file;
    int line;
    int lockCount;
    const wchar_t* lockName;
};
