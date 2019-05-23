#pragma once

#include "l2auth/CIOObject.h"

class CIOSocket;
struct sockaddr_in;

class CIOServer : public CIOObject
{
public:
    CIOServer();   // L2AuthD 0x004182BD
    ~CIOServer();  // L2AuthD 0x004182F0

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x004184ED
    void OnEventCallback() override;                                                            // L2AuthD 0x00418633

    void Close();           // L2AuthD 0x0041834E
    bool Create(int port);  // L2AuthD 0x004183AA

protected:
    virtual CIOSocket* CreateSocket(SOCKET socket, sockaddr_in* pAddress) = 0;

private:
    HANDLE m_hAcceptEvent;

protected:
    SOCKET m_socket;
};
