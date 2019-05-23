#include "l2core/utils/dbg/Assert.h"

#include "l2core/utils/dbg/CExceptionInit.h"

void EASSERT()
{
    static bool asserting = false;

    if (asserting)
    {
        return;
    }

    asserting = true;

    CExceptionInit::LogException(L"Intentional Exception\n");
}
