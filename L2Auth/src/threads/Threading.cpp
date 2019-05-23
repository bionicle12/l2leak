#include "l2auth/threads/Threading.h"

#include "l2auth/threads/CJob.h"
#include "l2auth/threads/IOCP.h"

#include "l2auth/network/CAuthServer.h"
#include "l2auth/network/CAuthSocket.h"
#include "l2auth/network/CIOServerInt.h"
#include "l2auth/network/CLogSocket.h"
#include "l2auth/network/CSocketInt.h"
#include "l2auth/network/IPSocket.h"
#include "l2auth/network/WorldSrvServer.h"
#include "l2auth/network/WorldSrvSocket.h"

#include "l2auth/config/Config.h"

#include "l2auth/ui/CLog.h"
#include "l2auth/ui/CReporter.h"
#include "l2auth/utils/CExceptionInit.h"

#include "l2auth/CIOObject.h"

#include "l2auth/AppInstance.h"

#include <cmath>
#include <ctime>
#include <process.h>  // _beginthreadex

static HANDLE* g_hThread;
static unsigned int* g_nThreadId;

static HANDLE* g_hThreadExtra;
static unsigned int* g_nThreadIdExtra;

bool Threading::g_teminateEvent = false;
bool Threading::g_bTerminating = false;

// L2AuthD 0x0043A4A3
void Threading::CreateIOThread()
{
    auth_guard;

    unsigned int timerThreadId;
    _beginthreadex(NULL, 0, &Threading::TimerThread, 0, 0, &timerThreadId);

    IOCP::g_hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    IOCP::g_hCompletionPortExtra = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

    g_hThread = new HANDLE[sizeof(HANDLE) * g_Config.numServerThread];
    g_nThreadId = new unsigned int[sizeof(unsigned int) * g_Config.numServerThread];

    g_hThreadExtra = new HANDLE[sizeof(HANDLE) * g_Config.numServerIntThread];
    g_nThreadIdExtra = new unsigned int[sizeof(unsigned int) * g_Config.numServerIntThread];

    for (int i = 0; i < g_Config.numServerThread; ++i)
    {
        g_hThread[i] = (HANDLE)_beginthreadex(NULL, 0, &Threading::IOThreadServer, (void*)i, 0, &g_nThreadId[i]);
    }

    for (int i = 0; i < g_Config.numServerIntThread; ++i)
    {
        g_hThreadExtra[i] = (HANDLE)_beginthreadex(NULL, 0, &Threading::IOThreadInt, (void*)i, 0, &g_nThreadIdExtra[i]);
    }

    auth_vunguard;
}

// L2AuthD 0x0043A2F1
unsigned int __stdcall Threading::ListenThread(void*)
{
    auth_guard;

    g_worldServServer.Run(g_Config.serverPort, &WorldSrvSocket::Allocate);
    g_authServer.Run(g_Config.serverExPort, &CAuthSocket::Allocate);
    g_CIOServerInt.Run(g_Config.serverIntPort, &CSocketInt::Allocate);

    g_job.RunEvent();

    g_worldServServer.Close();
    g_authServer.Stop();
    g_CIOServerInt.Close();

    if (g_IPSocket != NULL)
    {
        IPSocket::s_lock.WriteLock();

        if (!IPSocket::isReconnecting)
        {
            g_IPSocket->CloseSocket();
        }
        g_IPSocket->ReleaseRef();

        IPSocket::s_lock.WriteUnlock();
    }

    if (g_LogDSocket != NULL)
    {
        CLogSocket::s_lock.WriteLock();

        if (!CLogSocket::isReconnecting)
        {
            g_LogDSocket->CloseSocket();
        }
        g_LogDSocket->ReleaseRef();

        CLogSocket::s_lock.WriteUnlock();
    }

    delete[] g_hThread;
    delete[] g_nThreadId;
    delete[] g_hThreadExtra;
    delete[] g_nThreadIdExtra;

    Threading::g_teminateEvent = true;

    auth_vunguard;
    return 0;
}

// L2AuthD 0x0043A0C0
unsigned int __stdcall Threading::TimerThread(void*)
{
    auth_guard;

    g_job.RunTimer();

    g_winlog.AddLog(LOG_WRN, "Timer thread terminated");

    auth_vunguard;
    return 0;
}

// L2AuthD 0x0043A0E7
unsigned int __stdcall Threading::IOThreadServer(void*)
{
    auth_guard;

    time_t now = std::time(NULL);
    ::srand(static_cast<int>(now));

    while (!Threading::g_bTerminating)
    {
        DWORD dwTransferred = 0;
        OVERLAPPED* overlapped = NULL;
        CIOObject* pObject = NULL;
        BOOL success = ::GetQueuedCompletionStatus(IOCP::g_hCompletionPort, &dwTransferred, (PULONG_PTR)&pObject, &overlapped, INFINITE);

        ::InterlockedIncrement(&CReporter::g_nRunningThread);

        pObject->OnIOCallback(success, dwTransferred, overlapped);

        ::InterlockedDecrement(&CReporter::g_nRunningThread);
    }

    g_winlog.AddLog(LOG_WRN, "terminate IOThreadServer");
    g_winlog.AddLog(LOG_WRN, "IOThreadServer Server Exit");

    auth_vunguard;
    return 0;
}

// L2AuthD 0x0043A201
unsigned int __stdcall Threading::IOThreadInt(void*)
{
    auth_guard;

    time_t now = std::time(NULL);
    ::srand(static_cast<int>(now));
    while (!Threading::g_bTerminating)
    {
        DWORD dwTransferred = 0;
        OVERLAPPED* overlapped = NULL;
        CIOObject* pObject = NULL;
        BOOL success = ::GetQueuedCompletionStatus(IOCP::g_hCompletionPortExtra, &dwTransferred, (PULONG_PTR)&pObject, &overlapped, INFINITE);
        if (pObject != NULL)  // FIXED: crash in debug, at exit
        {
            pObject->OnIOCallback(success, dwTransferred, overlapped);
        }
    }

    g_winlog.AddLog(LOG_WRN, "terminate IOThreadInt");

    auth_vunguard;
    return 0;
}
