#pragma once

#include <windows.h>

class CBCPLogFile
{
public:
    CBCPLogFile();   // L2LogD 0x00407800
    ~CBCPLogFile();  // L2LogD 0x00406CF0

    static void Job(int bcpSlot);  // L2LogD 0x00403D90

    bool Init(int slot);  // L2LogD 0x00406D20

public:
    static int s_worldIds[10];  // L2LogD 0x00455C20

private:
    void InsertLogFiles(wchar_t* dirPath);  // L2LogD 0x004079C0

    static int BulkInsert(const wchar_t* logCategory, const wchar_t* filePath, const wchar_t* logTableName);   // L2LogD 0x00406D50
    static bool CheckFmtFile();                                                                                // L2LogD 0x00406EB0
    static bool GetMaxFileNo(wchar_t* file, wchar_t* clearFileName, int* maxIndex);                            // L2LogD 0x00407500
    static bool CheckLogTimeTable(int year, int month, int day, int world);                                    // L2LogD 0x004076B0
    static bool GetMoveFileName(const wchar_t* dirName, const wchar_t* originFileName, wchar_t* newFileName);  // L2LogD 0x00407890

private:
    static CRITICAL_SECTION s_lock;  // L2LogD 0x019D6970

    int m_slot;
    int field_1;
    wchar_t m_dirPath[256];
};

extern CBCPLogFile g_bcpFiles[10];  // L2LogD 0x019D6998
