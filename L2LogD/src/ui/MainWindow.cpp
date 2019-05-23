#include "l2logd/ui/MainWindow.h"

#include "l2core/AppInstance.h"
#include "l2core/db/CSQLQueue.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/Threads.h"
#include "l2core/utils/CBCPLogFile.h"
#include "l2core/utils/PerfMonitor.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"
#include "l2logd/config/Config.h"
#include "l2logd/data/CReadFile.h"
#include "l2logd/network/CServer.h"
#include "l2logd/threads/Threads.h"
#include "l2logd/ui/resources.h"

#include <process.h>

#include <cstring>

wchar_t MainWindow::s_windowClass[MAX_LOADSTRING];  // L2LogD 0x00455C98
wchar_t MainWindow::s_title[MAX_LOADSTRING];        // L2LogD 0x00455D60

// L2LogD 0x00404460
ATOM MainWindow::RegisterLogDClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {0};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &MainWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = ::LoadIconW(hInstance, (LPCWSTR)ICON_LOGD_32x32);
    wcex.hCursor = ::LoadCursorW(0, (LPCWSTR)IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = (LPCWSTR)STR_L2LOGD;
    wcex.lpszClassName = MainWindow::s_windowClass;
    wcex.hIconSm = ::LoadIconW(wcex.hInstance, (LPCWSTR)ICON_LOGD_16x16);
    return ::RegisterClassExW(&wcex);
}

// L2LogD 0x004044F0
bool MainWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    ::g_instance = hInstance;
    HWND logWnd = ::CreateWindowExW(
        0,
        MainWindow::s_windowClass,
        MainWindow::s_title,
        WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_GROUP | WS_TABSTOP,  //   0x00CF0000u,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (logWnd == 0)
    {
        return false;
    }

    Config::Init();
    g_winlog.Set(logWnd);
    g_winlog.Enable(true);
    ::ShowWindow(logWnd, nCmdShow);
    ::UpdateWindow(logWnd);

    DBConn::Init();

    unsigned int serverThreadId;
    HANDLE serverThread = (HANDLE)_beginthreadex(0, 0, &Threads::LogDServerListeningThread, 0, 0, &serverThreadId);
    g_logServer.setThread(serverThread);
    CThreadManager::SetThread(ThreadIndex_ListenThread, serverThread);

    SYSTEMTIME systemTime;
    ::GetLocalTime(&systemTime);
    wchar_t timeStr[256];
    memset(timeStr, 0, sizeof(timeStr));

    ::wsprintfW(timeStr, L"L%04d_%02d_%02d_", systemTime.wYear, systemTime.wMonth, systemTime.wDay);

    DBConn dbConn;
    dbConn.Execute(L"EXECUTE lin_CheckLogTimeTable2 '%s', %d", timeStr, Config::s_worldId);
    if (Config::s_BCPThreadCount < 10)
    {
        for (int i = 0; i < Config::s_BCPThreadCount; ++i)
        {
            unsigned int threadId;
            Threads::BCPThread_s_threads[i] = (HANDLE)_beginthreadex(0, 0, &Threads::BCPThread, (void*)i, CREATE_SUSPENDED, &threadId);
            CBCPLogFile::s_worldIds[i] = 0;
        }
    }

    if (Config::s_autoBCP)
    {
        g_winlog.Add(LOG_INF, L"Auto BCP mode is on");
        for (int i = 0; i < Config::s_BCPThreadCount; ++i)
        {
            ::ResumeThread(Threads::BCPThread_s_threads[i]);
        }
    }

    if (g_perfMonitor.Init())
    {
        unsigned int perfMonitorThread;
        Threads::PerfMonitor_s_thread = (HANDLE)_beginthreadex(NULL, 0, &Threads::PerfMonitorThread, 0, 0, &perfMonitorThread);
    }

    unsigned int sqlQueueThread;
    _beginthreadex(NULL, 0, &Threads::SqlQueueThread, 0, 0, &sqlQueueThread);

    return true;
}

// L2LogD 0x00403BE0
INT_PTR CALLBACK MainWindow::AboutDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam)
{
    if (msgType == WM_INITDIALOG)
    {
        return TRUE;
    }

    if (msgType != WM_COMMAND || wParam != IDOK && wParam != IDCANCEL)
    {
        return FALSE;
    }

    ::EndDialog(hDlg, wParam);
    return TRUE;
}

// L2LogD 0x00403EA0
LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT mstType, WPARAM wParam, LPARAM lParam)
{
    wchar_t buffer[100];
    ::LoadStringW(g_instance, STR_HELLO_WORLD, buffer, sizeof(buffer));
    if (mstType == WM_DESTROY)
    {
        ::PostQuitMessage(0);
        return FALSE;
    }

    if (mstType == WM_PAINT)
    {
        g_winlog.Redraw();
        return FALSE;
    }

    if (mstType != WM_COMMAND)
    {
        return ::DefWindowProcW(hWnd, mstType, wParam, lParam);
    }

    int cmd = wParam;
    if (cmd <= MENU_ITEM_RELOAD_CONF)
    {
        if (cmd == MENU_ITEM_RELOAD_CONF)
        {
            ::SuspendThread(Threads::PerfMonitor_s_thread);
            g_perfMonitor.Reload();
            ::ResumeThread(Threads::PerfMonitor_s_thread);
            return FALSE;
        }

        switch (cmd)
        {
            case MENU_ITEM_START_MONITOR:
                ::ResumeThread(Threads::PerfMonitor_s_thread);
                return FALSE;
            case MENU_ITEM_INSERT_ITEM_NAME:
                CReadFile::ParseItemName();
                return FALSE;
            case MENU_ITEM_INSERT_NPC_NAME:
                CReadFile::ParseNPCName();
                return FALSE;
            case MENU_ITEM_INSERT_QUEST_NAME:
                CReadFile::ParseQuestName();
                return FALSE;
            case MENU_ITEM_INSERT_SKILL_NAME:
                CReadFile::ParseSkillName();
                return FALSE;
            case MENU_ITEM_ABOUT:
                ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_ABOUT), hWnd, &MainWindow::AboutDlgProc, 0);
                return FALSE;
            case MENU_ITEM_EXIT:
                ::DestroyWindow(hWnd);
                return FALSE;
            default:
                return ::DefWindowProcW(hWnd, WM_COMMAND, wParam, lParam);
        }
    }

    if (cmd > MENU_ITEM_STOP_INSERT_DATA)
    {
        if (cmd == MENU_ITEM_CONFIGURE)
        {
            ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_CONFIGURATION), hWnd, &MainWindow::ConfigDlgProc, 0);
            return FALSE;
        }
        if (cmd == MENU_ITEM_START_SERVER_MONITOR || cmd == MENU_ITEM_STOP_SERVER_MONITOR)
        {
            return FALSE;
        }
        return ::DefWindowProcW(hWnd, WM_COMMAND, wParam, lParam);
    }

    if (cmd != MENU_ITEM_STOP_INSERT_DATA)
    {
        if (cmd == MENU_ITEM_STOP_MONITOR)
        {
            ::SuspendThread(Threads::PerfMonitor_s_thread);
            return FALSE;
        }
        if (cmd == MENU_ITEM_SPACEUSED)
        {
            g_sqlPollingQueue.SpaceUsed(true);
            return FALSE;
        }
        if (cmd != MENU_ITEM_START_INSERT_DATA)
        {
            return ::DefWindowProcW(hWnd, WM_COMMAND, wParam, lParam);
        }
        if (Config::s_BCPThreadCount <= 0)
        {
            return FALSE;
        }

        for (int i = 0; i < Config::s_BCPThreadCount; ++i)
        {
            ::ResumeThread(Threads::BCPThread_s_threads[i]);
        }
        return FALSE;
    }

    for (int i = 0; i < Config::s_BCPThreadCount; ++i)
    {
        ::SuspendThread(Threads::BCPThread_s_threads[i]);
    }

    return FALSE;
}

// L2LogD 0x004084B0
INT_PTR CALLBACK MainWindow::ConfigDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM /*lParam*/)
{
    guard(L"configDlgProc");

    if (msgType == WM_INITDIALOG)
    {
        wchar_t strBuffer[68];
        Utils::ToWString(Config::s_BCPLogFileInterval / 60000, strBuffer, 10);
        ::SendDlgItemMessageW(hDlg, CONTROL_CONFIGURATION_EDIT_BOX_BCP_LOG_INTERVAL, WM_SETTEXT, 0, (LPARAM)strBuffer);

        Utils::ToWString(Config::s_serverReportInterval / 1000, strBuffer, 10);
        ::SendDlgItemMessageW(hDlg, CONTROL_CONFIGURATION_EDIT_BOX_SERVER_REPORT_INTERVAL, WM_SETTEXT, 0, (LPARAM)strBuffer);

        ::SendDlgItemMessageW(hDlg, CONTROL_CONFIGURATION_CHECK_BOX_BCP_ON, BM_SETCHECK, Config::s_autoBCP, 0);

        unguard();
        return TRUE;
    }

    if (msgType != WM_COMMAND)
    {
        unguard();
        return FALSE;
    }

    if (wParam == IDOK)
    {
        wchar_t buffer[64];
        ::SendDlgItemMessageW(hDlg, CONTROL_CONFIGURATION_EDIT_BOX_BCP_LOG_INTERVAL, WM_GETTEXT, 64u, (LPARAM)buffer);
        Config::s_BCPLogFileInterval = 60000 * _wtol(buffer);

        ::SendDlgItemMessageW(hDlg, CONTROL_CONFIGURATION_EDIT_BOX_SERVER_REPORT_INTERVAL, WM_GETTEXT, 64u, (LPARAM)buffer);
        Config::s_serverReportInterval = 1000 * _wtol(buffer);

        Config::s_autoBCP = ::SendDlgItemMessageW(hDlg, CONTROL_CONFIGURATION_CHECK_BOX_BCP_ON, BM_GETSTATE, 0, 0) == BST_CHECKED;
        Utils::ToWString(Config::s_autoBCP, buffer, 10);

        Config::Save();

        ::EndDialog(hDlg, TRUE);
        unguard();

        return FALSE;
    }

    if (wParam != IDCANCEL)
    {
        unguard();
        return FALSE;
    }

    ::EndDialog(hDlg, IDCANCEL);

    unguard();
    return TRUE;
}
