#include "l2core/utils/dbg/StackGuard.h"

#include "l2core/utils/dbg/CallStack.h"

namespace StackGuard
{

void StackGuard::Enter(const wchar_t* funcName, const wchar_t* funcNameExit, const wchar_t* fileName, int line)
{
    CallStack::Push(funcName, funcNameExit, fileName, line);
}

void StackGuard::Leave()
{
    CallStack::Pop();
}

}  // namespace StackGuard
