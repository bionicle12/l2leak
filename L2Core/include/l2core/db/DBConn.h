#pragma once

#include "l2core/db/Pools.h"
#include "l2core/threads/CIOCriticalSection.h"

#include <windows.h>
#include <Sqltypes.h>

#include <l2core/utils/cstdint_support.h>

struct SqlConnection;

class DBConn
{
public:
    DBConn();               // L2LogD 0x00401000, L2CacheD 0x0040DAE0
    DBConn(Pools bbsPool);  // L2CacheD 0x0040DBE0
    ~DBConn();              // L2LogD 0x004010F0, L2CacheD 0x0040DD50

    static void Init();  // L2LogD 0x00402340, L2CacheD 0x0040F4A0

    bool Fetch();                                                   // L2LogD 0x00401FC0, L2CacheD 0x0040EDF0
    void Bind(wchar_t* value, int length);                          // L2LogD 0x00402250, L2CacheD 0x0040F0C0
    void Bind(char* value, int length);                             // L2CacheD 0x0040F120
    void Bind(unsigned int* value);                                 // L2CacheD 0x0040F180
    void Bind(int* value);                                          // L2CacheD 0x0040F1D0
    void Bind(double* value);                                       // L2CacheD 0x0040F220
    void Bind(uint8_t* pBinary, int size);                          // L2CacheD 0x0040F270
    void BindNullable(uint8_t* pBinary, int size, SQLLEN* length);  // L2CacheD 0x0040F320
    void BindNullable(wchar_t* sValue, int size, SQLLEN* length);   // L2CacheD 0x0040F380
    void BindNullable(unsigned int* value, SQLLEN* length);         // L2CacheD 0x0040F3E0
    void BindNullable(int* value, SQLLEN* indicator);               // L2LogD 0x004022F0, L2CacheD 0x0040F440

    void ResetHtmt();                          // L2LogD 0x004022A0, L2CacheD 0x0040F2D0
    bool Execute(const wchar_t* format, ...);  // L2LogD 0x00402450, L2CacheD 0x0040F5C0
    int GetRowCount() const;                   // L2CacheD 0x0040ED40

    SQLRETURN BindParam(SQLUSMALLINT index, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLINTEGER cbValueMax, SQLLEN* pcbValue);  // L2CacheD inlined
    SQLRETURN ExecuteOptimized(wchar_t* query);

private:
    static void AllocSQLPool();                                                                    // L2LogD 0x00401250, L2CacheD 0x0040DEC0
    static void AllocSQLPool2();                                                                   // L2LogD 0x00401470, L2CacheD 0x0040E110
    static void AllocSQLPool3();                                                                   // L2LogD 0x004016C0, L2CacheD 0x0040E380
    static void Error(SQLSMALLINT handleType, SQLHANDLE handle, const wchar_t* query);             // L2LogD 0x00402120, L2CacheD 0x0040EF70
    static bool Login();                                                                           // L2LogD 0x00401BD0, L2CacheD 0x0040E940
    static bool LoadStrFromReg(wchar_t* str, const wchar_t* keyStr, const wchar_t* regEntry);      // L2LogD 0x004060B0, L2CacheD 0x00465E70
    static void SaveStrToReg(const wchar_t* str, const wchar_t* keyStr, const wchar_t* regEntry);  // L2LogD 0x004061C0, L2CacheD 0x00465FB0

    static INT_PTR CALLBACK loginDlgProc(HWND hDlg, UINT msgType, WPARAM wparam, LPARAM a4);     // L2LogD 0x00401910, L2CacheD 0x0040E600
    static INT_PTR CALLBACK loginBBSDlgProc(HWND hDlg, UINT msgType, WPARAM wparam, LPARAM a4);  // L2LogD 0x00401A70, L2CacheD 0x0040E7A0

private:
    static int s_dbConnectionNum1;             // L2LogD 0x0042D7D4, L2CacheD 0x006529D4
    static int s_dbConnectionNum2;             // L2LogD 0x019D7DF4, L2CacheD 0x006529D0 // FIXME: #2 is for BBS
    static int s_dbConnectionNum3;             // L2LogD 0x019D7E20, L2CacheD 0x006529D8
    static SqlConnection* s_sqlConnections1;   // L2LogD 0x0042E7E8, L2CacheD 0x00652DEC
    static SqlConnection* s_sqlConnections2;   // L2LogD 0x0042E7E4, L2CacheD 0x00652DE8
    static SqlConnection* s_sqlConnections3;   // L2LogD 0x0042E7E0, L2CacheD 0x006529E0
    static wchar_t s_connStrBBS[256];          // L2LogD 0x0042E7F0, L2CacheD 0x006529E8
    static wchar_t s_connStr[256];             // L2LogD 0x0042E9F0, L2CacheD 0x00652BE8
    static SQLHANDLE s_sqlEnvHandle;           // L2LogD 0x0042EBF0, L2CacheD 0x006529E4
    static SqlConnection* s_connectionsHead1;  // L2LogD 0x0042EBF4, L2CacheD 0x00652DF0
    static SqlConnection* s_connectionsHead2;  // L2LogD 0x0042EBF8, L2CacheD 0x00652DF4
    static SqlConnection* s_connectionsHead3;  // L2LogD 0x0042EBFC, L2CacheD 0x00652DF8
    static CIOCriticalSection s_lock1;         // L2LogD 0x0042EC00, L2CacheD 0x00652E18
    static CIOCriticalSection s_lock2;         // L2LogD 0x0042EC1C, L2CacheD 0x00652DFC

private:
    SQLHSTMT m_sqlHandler;
    int m_currentCollumn;
    SqlConnection* m_sqlConnection;
    Pools m_poolIndex;

    static const int QUERY_MAX_LEN = 512;
    wchar_t m_lastQuery[QUERY_MAX_LEN];
};
