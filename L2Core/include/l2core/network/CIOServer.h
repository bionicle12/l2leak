#pragma once

#include "l2core/CIOObject.h"

class CIOSocket;

class CIOServer : public CIOObject
{
public:
    ~CIOServer();  // L2LogD 0x004098D0, L2CacheD 0x00480590

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;               // L2LogD 0x00409730, L2CacheD 0x004803E0
    void OnWaitCallback() override;                                                             // L2LogD 0x00408BB0, L2CacheD 0x0047F8D0
    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2LogD 0x00409940, L2CacheD 0x00480610

protected:
    CIOServer();  // L2LogD 0x00409860, L2CacheD 0x00480510
    virtual CIOSocket* CreateSocket(SOCKET socket, sockaddr_in* address) = 0;
    bool Create(int port);  // L2LogD 0x0040B900, L2CacheD 0x00482740
    SOCKET getSocket() const;

private:
    static void operator delete(void* ptr);  // L2LogD inlined inside 0x0040A3D0, L2CacheD inlined inside 0x00481260
    void Close();                            // L2LogD 0x00408B60, L2CacheD 0x0047F870

private:
    static long s_nAlloc;  // L2LogD 0x01BD3D80, L2CacheD 0x026846A4
    SOCKET m_hSocket;
    HANDLE m_hAcceptEvent;
};
