#include "l2auth/ui/MainWindow.h"

#include "l2auth/ui/CLog.h"
#include "l2auth/ui/CReporter.h"
#include "l2auth/ui/resources.h"

#include "l2auth/AppInstance.h"

#include "l2auth/config/Config.h"

#include "l2auth/model/AccountDB.h"
#include "l2auth/model/CServerList.h"
#include "l2auth/model/ServerKind.h"
#include "l2auth/model/ServersProvider.h"

#include "l2auth/threads/CJob.h"
#include "l2auth/threads/Threading.h"

#include "l2auth/network/WorldSrvServer.h"
#include "l2core/network/packets/AuthToServerPackets.h"

#include "l2auth/utils/CExceptionInit.h"
#include "l2auth/utils/Utils.h"

HWND MainWindow::mainWnd;
HWND MainWindow::reporterWnd;
HWND MainWindow::logWnd;
HWND MainWindow::resetBtn;
HWND MainWindow::reloadBtn;

INT_PTR CALLBACK MainWindow::closeAuthFunc(HWND hDlg, UINT command, WPARAM param, LPARAM)
{
    if (command == WM_COMMAND)
    {
        if (param == IDOK)
        {
            ::DestroyWindow(mainWnd);
            ::EndDialog(hDlg, 0);
        }
        else if (param == IDCANCEL)
        {
            ::EndDialog(hDlg, 0);
        }
    }
    return 0;
}

LRESULT CALLBACK MainWindow::wndProc(HWND hWndParent, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    auth_guard;

    if (Msg > 0x10)
    {
        if (Msg == WM_COMMAND)
        {
            short cmd = (short)wParam;
            if (!(wParam >> 16) && cmd == 2)
            {
                g_serverList.ReloadServer();
                g_serverKind.ReloadServerList();
            }
        }
        else if (Msg == WM_TIMER)
        {
            switch (wParam)
            {
                case WinParam_UpdateUserNumber:
                    g_reporter.users = g_accountDb.GetUserNum();
                    ::InvalidateRect(reporterWnd, 0, 0);
                    break;
                case WinParam_UpdateServerStatus:
                    for (int serverId = 1;; ++serverId)
                    {
                        int serverNumber = g_serverList.GetMaxServerNum();
                        if (serverId > serverNumber)
                        {
                            break;
                        }
                        if (ServersProvider::GetServerStatus(serverId))
                        {
                            // WorldServer worldServer = g_serverList.getServerInfo(serverId); //
                            // FIXED
                            WorldServer worldServer = ServersProvider::GetWorldServer(serverId);
                            WorldSrvServer::SendSocket(worldServer.ipAddress, "c", AuthToServerPacket_OnlineUsersRequest);
                        }
                    }
                    break;
                case WinParam_UpdateDisckFreeSpace:
                    Utils::CheckDiskSpace(g_Config.logDirectory, 400000000);
                    break;
            }
        }
    }
    else
    {
        switch (Msg)
        {
            case WM_CLOSE:
                if (hWndParent == MainWindow::mainWnd)
                {
                    HWND closeAuth = ::CreateDialogParamA(hInstance, MAKEINTRESOURCE(DLG_CLOSE_L2_AUTH), hWndParent, &closeAuthFunc, 0);
                    ::ShowWindow(closeAuth, SW_SHOW);
                    return 0;
                }
                break;
            case WM_DESTROY:
                if (hWndParent == MainWindow::mainWnd)
                {
                    Threading::g_bTerminating = true;
                    g_winlog.Enable(0);
                    g_job.SetTerminate();
                    ::Sleep(2000u);
                    ::PostQuitMessage(0);
                }
                break;
            case WM_SIZE:
            {
                short width = (short)lParam;
                short height = (unsigned int)(lParam >> 16);

                if (hWndParent == MainWindow::mainWnd)
                {
                    ::MoveWindow(reporterWnd, 160, 0, width - 160, 20, 1);
                    ::MoveWindow(logWnd, 0, 20, width, height - 20, 1);
                    ::MoveWindow(resetBtn, 0, 0, 80, 20, 1);
                    ::MoveWindow(reloadBtn, 80, 0, 80, 20, 1);
                }
                else if (hWndParent == logWnd)
                {
                    g_winlog.Resize(width, height);
                }
                else
                {
                    hWndParent = reporterWnd;
                    if (reporterWnd)
                    {
                        g_reporter.Resize(width, height);
                    }
                }
                break;
            }
            case WM_PAINT:
                if (hWndParent == logWnd)
                {
                    g_winlog.Redraw();
                }
                else if (hWndParent == reporterWnd)
                {
                    g_reporter.Redraw();
                }
                break;
        }
    }

    auth_vunguard;

    return ::DefWindowProcA(hWndParent, Msg, wParam, lParam);
}
