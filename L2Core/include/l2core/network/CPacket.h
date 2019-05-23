#pragma once

#include "l2core/CIOObject.h"

#include <l2core/utils/cstdint_support.h>

class CIOSocket;
class CIOBuffer;

class CPacket : public CIOObject
{
public:
    static CPacket* Alloc();  // L2LogD inlined, L2CacheD inlined
    static void FreeAll();    // L2LogD 0x00409B50, L2CacheD 0x00480840

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;               // L2LogD 0x00409A20
    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2LogD 0x0040A460

protected:
    CPacket();   // L2LogD inlined, L2CacheD 0x00427F30
    ~CPacket();  // L2LogD inlined, L2CacheD 0x00427FA0

private:
    static void operator delete(void* ptr);  // L2LogD 0x004092C0, L2CacheD inlined inside deleting destructor 0x00427F60
    static void* operator new(size_t size);  // L2LogD inlined, L2CacheD 0x00427EB0

public:
    static long g_nPendingPacket;  // L2LogD 0x01BD3BB0, L2CacheD 0x02684624

#ifdef L2CACHED
    int m_createTime;
    int m_handleTime;
    int m_deleteTime;
    int m_packetType;
#endif  // #ifdef L2CACHED
    CIOSocket* m_pSocket;
    CIOBuffer* m_pBuf;
    typedef bool (*PacketFunc)(CIOSocket*, const uint8_t* packet);
    PacketFunc m_pFunc;

protected:
    static long s_nAlloc;  // L2LogD 0x01BD3E0C, L2CacheD 0x026846D0, L2NPC 0x0217C64C
};
