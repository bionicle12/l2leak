#include "cached/config/Config.h"
#include "cached/threads/Threads.h"
#include "cached/ui/MainWindow.h"
#include "cached/ui/resources.h"
#include "l2core/network/CIOBufferPool.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/threads/Threads.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"

#include <windows.h>
#include <crtdbg.h>

HINSTANCE g_instance;  // L2CacheD 0x004F28B4

// L2CacheD 0x0040AB60
int __stdcall WinMain(HINSTANCE instance, HINSTANCE /*hPrevInstance*/, char* /*lpCmdLine*/, int nShowCmd)
{
    ::CreateMutexW(NULL, TRUE, L"_L2CACHE_EXE_");
    if (::GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ::MessageBoxW(0, L"L2cached.EXE is already running.", L"Error", MB_OK);
        return -1;
    }

    CThreadManager::SetThisThreadAsMainThread();
    uint32_t maxIOThreadNumber = CThreadManager::GetMaxIOThreadNumber();
    CThreadManager::SetIOThreadNumber(maxIOThreadNumber);

    g_IOBufferPools[tls::GetCurrentThreadIndex()] = new CIOBufferPool(100);  // FIXME: static mem leak

    CallStack::InitializeGuardStack();

    Config::s_mailServer = new char[1000u];

    wchar_t mailServer[1000];
    ::GetPrivateProfileStringW(L"Setting", L"MailServer", L"mail.ncsoft.co.kr", mailServer, sizeof(mailServer), L".\\l2cache.ini");
    Utils::UnicodeToAnsi(mailServer, 1000, Config::s_mailServer, 1000);

    if (Config::ExceptionMailing())
    {
        _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
        _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    }

    ::LoadStringW(instance, STR_CAPTION, MainWindow::s_title, MAX_LOADSTRING);
    ::LoadStringW(instance, STR_L2CACHED, MainWindow::s_windowClass, MAX_LOADSTRING);

    MainWindow::RegisterCacheDClass(instance);
    const bool success = MainWindow::InitInstance(instance, nShowCmd);
    if (!success)
    {
        return -2;  // FIXED: was 0
    }

    HACCEL accelerators = ::LoadAcceleratorsW(instance, (LPCWSTR)ACCELERATOR_L2CACHED);
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
