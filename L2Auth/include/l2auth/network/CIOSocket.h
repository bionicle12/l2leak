#pragma once

#include "l2auth/CIOObject.h"

class CIOBuffer;

class CIOSocket : public CIOObject
{
public:
    CIOSocket(SOCKET socket);  // L2AuthD 0x0041D4D0
    ~CIOSocket();              // L2AuthD 0x0041D583

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x0041D738

    void Read(size_t dwLeft);     // L2AuthD 0x0041D995
    void Write(CIOBuffer* buff);  // L2AuthD 0x0041DB1A

    void CloseSocket();                              // L2AuthD 0x0041D61F
    void Initialize(HANDLE existingCompletionPort);  // L2AuthD 0x0041D687

    SOCKET getSocket() const
    {
        return m_hSocket;
    }

protected:
    virtual void OnClose();   // L2AuthD 0x0041D614
    virtual void OnCreate();  // L2AuthD 0x0041D722
    virtual void OnRead() = 0;
    virtual void OnReadCallback(int dwTransferred);   // L2AuthD 0x0041D7A9
    virtual void OnWriteCallback(int dwTransferred);  // L2AuthD 0x0041D80B

protected:
    CRITICAL_SECTION m_lock;
    OVERLAPPED m_overlappedRead;
    OVERLAPPED m_overlappedWrite;
    CIOBuffer* m_pReadBuf;
    CIOBuffer* m_pFirstBuf;
    CIOBuffer* m_pLastBuf;
    int m_nPendingWrite;
    SOCKET m_hSocket;
};
