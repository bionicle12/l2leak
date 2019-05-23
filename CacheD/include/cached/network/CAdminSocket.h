#pragma once

#include "l2core/network/CIOSocket.h"
#include "l2core/network/SocketStatus.h"

class CAdminSocket : public CIOSocket
{
public:
    typedef bool (*PacketHandler)(CAdminSocket*, const char*);

public:
    CAdminSocket(SOCKET socket);  // L2CacheD 0x00414A80
    ~CAdminSocket();              // L2CacheD 0x00414B70

    static CAdminSocket* Allocate(SOCKET socket);  // L2CacheD inlined
    static void* operator new(size_t size);        // L2CacheD inlined
    static void operator delete(void* ptr);        // L2CacheD inlined in 0x00416790

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // FIXED

    void Send(const char* format, ...);                      // L2CacheD 0x00414C00
    void SendBuffer(const char* buffer, signed int length);  // L2CacheD 0x00414CB0

    void SetAddress(in_addr addr);  // L2CacheD 0x00414E20
    const char* IP() const;         // L2CacheD 0x00414E60

protected:
    void TimerExpired(intptr_t id) override;  // L2CacheD 0x00414F50
    void OnCreate() override;                 // L2CacheD 0x00414ED0
    void OnRead() override;                   // L2CacheD 0x00415000
    void OnClose() override;                  // L2CacheD 0x004150D0

private:
    void Process(const char* command);  // L2CacheD 0x00414D80

private:
    static long s_nAlloc;  // L2CacheD FIXED

private:
    SOCKET m_socket;
    // int m_CAdminSocket_unused_4;
    // int m_CAdminSocket_unused_3;
    // int field_32;
    SocketStatus m_socketStatus;
    // int m_CAdminSocket_unused_5;
    const PacketHandler* m_packetHandlers;
    in_addr m_remoteAddr;
    // int m_CAdminSocket_unused_2;
    int m_timeoutRetries;
};
