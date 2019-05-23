#pragma once

#include "l2core/logger/FileBuffers.h"
#include "l2core/logger/LogType.h"
#include "l2core/logger/ServerTypes.h"
#include "l2core/network/CIOBuffer.h"
#include "l2core/network/CIOSocket.h"
#include "l2core/network/SocketStatus.h"

class CServerSocket : public CIOSocket
{
public:
    typedef bool (*PacketHandler)(CIOSocket*, const uint8_t*);

public:
    CServerSocket(SOCKET socket, size_t buffSize = BUFFER_SIZE);  // L2LogD 0x0040F6B0
    ~CServerSocket();                                             // L2LogD 0x0040F890

    static CServerSocket* Allocate(SOCKET socket);  // L2LogD 0x0040F9A0
    static void* operator new(size_t size);         // L2LogD inlined
    static void operator delete(void* ptr);         // L2LogD 0x0040F470

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2LogD 0x004100E0

    void SetAddress(in_addr addr);  // L2LogD 0x00410080
    in_addr GetAddress() const;     // L2LogD 0x004100B0

protected:
    void TimerExpired(intptr_t timerId) override;  // L2LogD 0x004111F0
    void OnCreate() override;                 // L2LogD 0x0040FA60
    void OnRead() override;                   // L2LogD 0x00411280
    void OnClose() override;                  // L2LogD 0x0040FAD0

private:
    static const wchar_t* ParseLogData(const wchar_t* logMessage, const char* format, ...);  // L2LogD 0x0040F520

    static bool packet00_SendLog(CIOSocket* socket, const uint8_t* packet);         // L2LogD 0x00410620
    static bool packet01_SetCheckStatus(CIOSocket* socket, const uint8_t* packet);  // L2LogD 0x0040F610
    static bool packet02_CheckLogD(CIOSocket* socket, const uint8_t* packet);       // L2LogD 0x00410F70
    static bool packet03_ServerStarted(CIOSocket* socket, const uint8_t* packet);   // L2LogD 0x00411020
    static bool packet04_DummyPacket(CIOSocket* socket, const uint8_t* packet);     // L2LogD 0x0040F690

    bool CanAppend(int year, int month, int day, int hour, bool half) const;   // L2LogD 0x0040F490
    void LockBuffer(int bufferIndex);                                          // L2LogD 0x0040F4E0
    void UnlockBuffer(int bufferIndex);                                        // L2LogD 0x0040F500
    void WriteLogFile(LogType logType, const wchar_t* msg);                    // L2LogD 0x0040FD00
    bool CheckLogTimeTable(int worldId);                                       // L2LogD 0x0040FFC0
    void CreateNewLogFile(int year, int month, int day, int hour, bool half);  // L2LogD 0x00410250
    void Send(const char* format, ...);                                        // L2LogD 0x004104F0

private:
    struct FilePath
    {
        wchar_t path[MAX_PATH];
    };

private:
    static long s_nAlloc;  // L2LogD 0x01BD5438

    static const int HANDLERS_NUMBER = 4;
    static const PacketHandler s_packetHandlers[HANDLERS_NUMBER + 1];  // L2LogD 0x0042D8A8

    static const wchar_t* s_serverTypes[7];    // L2LogD 0x0042D8DC
    static const wchar_t* s_logCategories[8];  // L2LogD 0x0042D8BC

    SOCKET m_socket;
    int m_buffSize;
    in_addr m_remoteAddr;
    SocketStatus m_status;
    // int field_149; UNUSED
    // int field_150; UNUSED
    // int field_151; UNUSED
    // int field_152; UNUSED
    uint8_t* m_readBuffer;
    // int field_154;  UNUSED
    // int field_155;  UNUSED
    // int field_156;  UNUSED
    // int field_157;  UNUSED
    // int field_158;  UNUSED
    uint8_t* m_writeBuffer;
    HANDLE m_event;
    const PacketHandler* m_packetHandlers;
    CIOCriticalSection m_lock1;
    CIOCriticalSection m_socketWriteLock;
    // int m_socketStatus; FIXED: removed
    int m_packetSize;
    // int field_178;   UNUSED
    // int field_179;   UNUSED
    // int field_180;   UNUSED
    // int field_181;   UNUSED
    // int field_182;   UNUSED
    // int field_183;   UNUSED
    // int field_184;   UNUSED
    bool m_checkStatus;
    int m_createdTime;
    wchar_t m_yearMonthDay[16];
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    bool m_half;
    int m_worldId;
    ServerTypes m_logComponent;
    HANDLE m_fileBuffers[FileBuffers_BuffersCount];
    CRITICAL_SECTION m_bufferLocks[FileBuffers_BuffersCount];
    FilePath m_fileNames[FileBuffers_BuffersCount];
    CRITICAL_SECTION m_fileLock;
    // int field_1236; UNUSED
};
