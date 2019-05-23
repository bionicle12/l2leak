#pragma once

#include "l2core/CIOObject.h"

#if defined(NEW_SOCKET_SYSTEM)
#include "l2core/threads/CExecutionSerializerFast.h"
#include "l2core/threads/IODummyLock.h"
#endif

class CIOBuffer;

class CIOSocket : public CIOObject
{
public:
    ~CIOSocket();  // L2LogD 0x00409D10, L2CacheD 0x00480B60, L2PNC 0x00478FD0

    long AddRef(const char* file, int line, ORTs workType) override;  // L2PNC 0x00478D60

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2LogD 0x0040A7C0, L2CacheD 0x00481540, L2PNC 0x004792A0
    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;               // L2LogD 0x00409540, L2CacheD 0x004801E0, L2PNC 0x00478D80

    void Read(size_t dwLeft);       // L2LogD 0x00409DD0, L2CacheD 0x00480C30, L2PNC 0x004794D0
    void Write(CIOBuffer* buffer);  // L2LogD 0x0040A180, L2CacheD 0x00481000, L2PNC 0x00479940

    void Initialize();     // L2LogD 0x00408BF0, L2CacheD 0x0047F920, L2PNC 0x0047A3F0
    void Close();          // L2LogD 0x004089C0, L2CacheD 0x0047F6A0, L2PNC 0x00479120
    void GracefulClose();  // L2PNC 0x004791F0

    int pendingWrite() const;

protected:
    CIOSocket(SOCKET socket);  // L2LogD 0x00409670, L2CacheD 0x00480310, L2PNC 0x00478EB0

    virtual void OnCreate();  // L2LogD 0x00408A70, L2CacheD 0x0047F760, L2PNC 0x00479390
    virtual void OnClose();   // L2LogD 0x004089A0, L2CacheD 0x0047F670, L2PNC 0x004790D0
    virtual void OnRead() = 0;

    void ReadCallback(DWORD dwTransferred);   // L2LogD 0x00408AD0, L2CacheD 0x0047F7D0, L2PNC 0x00479410
    void WriteCallback(DWORD dwTransferred);  // L2LogD 0x00409FC0, L2CacheD 0x00480E40, L2PNC 0x00479760

private:
    static void operator delete(void* ptr);  // L2LogD inlined inside deleting destructor 0x0040A780, inlined inside deleting destructor L2CacheD 0x00481500

protected:
    SOCKET m_hSocket;
    int m_nPendingWrite;

#if defined(NEW_SOCKET_SYSTEM)
    CExecutionSerializerFast m_ioSocketSerializer;
    IODummyLock m_lock;
#else
    CIOCriticalSection m_lock;
#endif
    OVERLAPPED m_overlappedRead;
    OVERLAPPED m_overlappedWrite;
    CIOBuffer* m_pReadBuf;
    CIOBuffer* m_pFirstBuf;
    CIOBuffer* m_pLastBuf;

protected:
    static volatile LONG s_pendingWriteBytes;  // L2LogD 0x01BD3BCC, L2CacheD 0x02684634, L2PNC 0x013FC178

private:
    static long s_nAlloc;  // L2LogD 0x01BD3D7C, L2CacheD 0x02684924, L2PNC 0x0217C5BC
};
