#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/Threads.h"
#include "l2logd/config/Config.h"
#include "l2logd/ui/MainWindow.h"
#include "l2logd/ui/resources.h"

#include <windows.h>
#include <crtdbg.h>

HINSTANCE g_instance;  // L2LogD 0x00455E28

int __stdcall WinMain(HINSTANCE instance, HINSTANCE /*hPrevInstance*/, char* /*lpCmdLine*/, int nShowCmd)
{
    ::CreateMutexW(NULL, TRUE, L"_L2LOGD_EXE_");
    if (::GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ::MessageBoxW(0, L"L2LogD.EXE is already running.", L"Error", MB_OK);
        return -1;
    }

    CThreadManager::SetThisThreadAsMainThread();
    uint32_t maxIOThreadNumber = CThreadManager::GetMaxIOThreadNumber();
    CThreadManager::SetIOThreadNumber(maxIOThreadNumber);

    Config::s_mailServer = "mail.ncsoft.co.kr";  // FIXME: move to config
    if (Config::ExceptionMailing())
    {
        _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
        _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    }

    ::LoadStringW(instance, STR_CAPTION, MainWindow::s_title, MAX_LOADSTRING);
    ::LoadStringW(instance, STR_L2LOGD, MainWindow::s_windowClass, MAX_LOADSTRING);
    MainWindow::RegisterLogDClass(instance);
    const bool success = MainWindow::InitInstance(instance, nShowCmd);
    if (!success)
    {
        return -2;  // FIXED: was 0
    }

    HACCEL accelerators = ::LoadAcceleratorsW(instance, (LPCWSTR)STR_L2LOGD);
    if (Config::ExceptionMailing())
    {
        Threads::MessageLoop_mailing(accelerators);
    }
    else
    {
        Threads::MessageLoop_common(accelerators);
    }

    return 0;  // FIXED: was -1
}
