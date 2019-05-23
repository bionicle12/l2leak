#pragma once

#include "l2core/network/CPacket.h"

class CBBSPacket : public CPacket
{
public:
    static CBBSPacket* Alloc();  // inlined

    BOOL PostObject(DWORD id) override;  // L2CacheD 0x00437850

private:
    CBBSPacket();   // L2CacheD inlined
    ~CBBSPacket();  // L2CacheD 0x0043C690

    static void operator delete(void* ptr);  // L2CacheD inlined inside deleting destructor 0x0043C650
    static void* operator new(size_t size);  // L2CacheD inlined
};
