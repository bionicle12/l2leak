#pragma once

#include "l2core/CIOObject.h"

class CIOCPMessage : public CIOObject
{
public:
    CIOCPMessage();   // L2NPC 0x0043A720
    ~CIOCPMessage();  // L2NPC 0x004300B0

    static void* operator new(size_t size);  // FIXED: Added
    static void operator delete(void* ptr);  // L2NPC 0x004300C0

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;            // FIXED: Added
    void OnIOCallback(BOOL success, DWORD transferred, LPOVERLAPPED lpOverlapped) override;  // L2NPC 0x00427EC0

    virtual void OnReceive(int id) = 0;

    void Post(int id);  // L2NPC 0x00427E00

private:
    static long s_nAlloc;  // FIXED: Added
};