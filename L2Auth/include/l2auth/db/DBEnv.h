#pragma once

#include "l2auth/CIOObject.h"
#include "l2auth/threads/CLock.h"

#include <Sqltypes.h>

struct SqlConnection;

class DBEnv : public CIOObject
{
public:
    DBEnv();   // L2AuthD 0x004133DF
    ~DBEnv();  // L2AuthD 0x0041346F

    void Init(int dbConnectionNumber);  // L2AuthD 0x004134F8

    void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped) override;  // L2AuthD 0x00414AF0
    void OnTimerCallback() override;                                                            // L2AuthD 0x00413D60
    void OnEventCallback() override;                                                            // L2AuthD 0x00414AE0

private:
    static INT_PTR CALLBACK LoginDlgProc(HWND hDlg, UINT msgType, WPARAM wparam, LPARAM lparam);  // L2AuthD 0x00413FD9

    void AllocSQLPool();         // L2AuthD 0x00413759
    void Destroy();              // L2AuthD 0x00413AC8
    bool Login(bool reconnect);  // L2AuthD 0x004135F2
    bool LoadConnStrFromReg();   // L2AuthD 0x00413B7E
    void SaveConnStrToReg();     // L2AuthD 0x00413C76

public:
    CLock spinLock;
    SQLHENV sqlEnvHandle;
    SqlConnection* sqlConnections;
    SqlConnection* connectionsHead;

    char connectionStr[256];
    int connectionNumber;
    int recoveryTriggered;
};

extern DBEnv g_linDB;
