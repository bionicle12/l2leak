#include "cached/ui/MainWindow.h"

#include "cached/config/Config.h"
#include "cached/data/CAddData.h"
#include "cached/data/CReadFile.h"
#include "cached/data/CWatchList.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CCacheDServer.h"
#include "cached/threads/Threads.h"
#include "cached/ui/resources.h"
#include "l2core/AppInstance.h"
#include "l2core/logger/CLog.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/utils/CQsCheck.h"
#include "l2core/utils/dbg/Crash.h"
#include "l2core/utils/dbg/Debug.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <process.h>

wchar_t MainWindow::s_windowClass[MAX_LOADSTRING];  // L2CacheD 0x004F28C0
wchar_t MainWindow::s_title[MAX_LOADSTRING];        // L2CacheD 0x004F27E8

// L2CacheD 0x0040A710
ATOM MainWindow::RegisterCacheDClass(HINSTANCE hInstance)
{
    guard(L"MainWindow::RegisterCacheDClass");

    WNDCLASSEXW wcex = {0};  // FIXED: zeroing
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &MainWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = ::LoadIconW(hInstance, (LPCWSTR)ICON_CACHED_32x32);
    wcex.hCursor = ::LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = (LPCWSTR)STR_L2CACHED;
    wcex.lpszClassName = MainWindow::s_windowClass;
    wcex.hIconSm = ::LoadIconW(wcex.hInstance, (LPCWSTR)ICON_CACHED_16x16);

    ATOM result = ::RegisterClassExW(&wcex);

    unguard();

    return result;
}

// L2CacheD 0x0040AA10
bool MainWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    guard(L"bool MainWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)");

    ::g_instance = hInstance;

    HWND logWnd = ::CreateWindowExW(
        0,
        MainWindow::s_windowClass,
        MainWindow::s_title,
#ifdef L2CACHED
        WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_GROUP | WS_TABSTOP,  //   0x00CF0000u,
#elif L2SERVER
        WS_OVERLAPPEDWINDOW,
#endif  // #ifdef L2CACHED
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

    g_readFile.ParseItemData();
    if (g_watchList.ParseWatchList())
    {
        g_winlog.Add(LOG_INF, L"watch list loaded");
    }

    unsigned int threadId;
    HANDLE gameServerDbThread = (HANDLE)_beginthreadex(NULL, 0, &Threads::CacheDListeningThread, 0, 0, &threadId);
    g_gameDbServer.setThread(gameServerDbThread);
    CThreadManager::SetThread(ThreadIndex_ListenThread, g_gameDbServer.thread());

    unguard();
    return true;
}

// L2CacheD 0x00409E70
INT_PTR CALLBACK MainWindow::AboutDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam)
{
    guard(L"BOOL CALLBACK MainWindow::AboutDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam)");

    switch (msgType)
    {
        case WM_INITDIALOG:
            unguard();
            return TRUE;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                ::EndDialog(hDlg, wParam);

                unguard();
                return TRUE;
            }
    }

    unguard();
    return FALSE;
}

// L2CacheD 0x0040A260
LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT msgType, WPARAM wParam, LPARAM lParam)
{
    guard(L"MainWindow::WndProc");

    wchar_t buffer[MAX_LOADSTRING];
    ::LoadStringW(g_instance, STR_HELLO_WORLD, buffer, 100);
    if (msgType == WM_DESTROY)
    {
        ::PostQuitMessage(0);
        unguard();
        return FALSE;
    }

    if (msgType == WM_PAINT)
    {
        g_winlog.Redraw();
        unguard();
        return FALSE;
    }

    if (msgType != WM_COMMAND)
    {
        LRESULT result = ::DefWindowProcW(hWnd, msgType, wParam, lParam);
        unguard();
        return result;
    }

    int cmd = wParam;
    if (cmd <= DEBUG_REPORT_PACKET)
    {
        if (cmd == DEBUG_REPORT_PACKET)
        {
            g_qsCheck.ShowPacketReport();
            unguard();
            return FALSE;
        }
        switch (cmd)
        {
            case DEBUG_RELOAD_CONFIG:
                Config::Init();
                break;
            case FILE_CRASH_REPORT:
            {
                guard(L"Crash report!");
                CRASH;
                unguard();
                break;
            }
            case HELP_ABOUT:
                ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_ABOUT), hWnd, &MainWindow::AboutDlgProc, 0);
                break;
            case FILE_EXIT:
                ::DestroyWindow(hWnd);
                break;
            case DEBUG_QSREPORT:
                g_qsCheck.Report();
                break;
            case DEBUG_QSSLOWREPORT:
                g_qsCheck.SlowReport();
                break;
            case DEBUG_TOGGLEUSEBBSCONN:
                if (Config::s_useBbs)
                {
                    Config::s_useBbs = 0;
                    g_winlog.Add(LOG_ERROR, L"BBS use is disabled.");
                }
                else
                {
                    Config::s_useBbs = 1;
                    g_winlog.Add(LOG_ERROR, L"BBS use is enabled.");
                }
                Config::Save();
                break;
            case DEBUG_SAVE_CONFIG:
                Config::Save();
                break;
            case DEBUG_RESET_PROFILE:
            case DEBUG_REPORT_PROFILE:
                break;
            default:
                unguard();
                return ::DefWindowProcW(hWnd, msgType, wParam, lParam);
        }
        unguard();
        return FALSE;
    }

    if (cmd > LOG_CONNECT_TO_LOGD)
    {
        switch (cmd)
        {
            case DEBUG_CLASS_REFCOUNT:
                Debug::ReportClassWorkRefCount();
                unguard();
                return FALSE;
            case SCRIPT_ADD_ITEM_DATA:
                g_addData.AddItemData();
                unguard();
                return FALSE;
            case SCRIPT_ADD_SKILL_DATA:
                g_addData.AddSkillData();
                unguard();
                return FALSE;
            case SCRIPT_ADD_QUEST_DATA:
                g_addData.AddQuestData();
                unguard();
                return FALSE;
            default:
                break;
        }
        unguard();
        return ::DefWindowProcW(hWnd, msgType, wParam, lParam);
    }

    if (cmd != LOG_CONNECT_TO_LOGD)
    {
        switch (cmd)
        {
            case DEBUG_CLEAR_PACKET:
                g_qsCheck.ClearPacketReport();
                unguard();
                return FALSE;
            case DEBUG_TOGGLE_PACKET:
                if (CQsCheck::s_packetReport)
                {
                    CQsCheck::s_packetReport = false;
                    g_winlog.Add(LOG_ERROR, L"packet report is disabled.");
                }
                else
                {
                    CQsCheck::s_packetReport = true;
                    g_winlog.Add(LOG_ERROR, L"packet report is enabled.");
                }
                unguard();
                return FALSE;
            case DEBUG_PRINTCHARDATA:
                g_userDb.PrintAllAccountData();
                unguard();
                return FALSE;
            case DEBUG_PRINTWAREHOUSEDATA:
                g_userDb.PrintAllAccountWarehouseData();
                unguard();
                return FALSE;
            default:
                break;
        }
        unguard();
        return ::DefWindowProcW(hWnd, msgType, wParam, lParam);
    }

    g_winlog.ConnectToLogD();

    unguard();
    return FALSE;
}
