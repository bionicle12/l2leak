#pragma once

#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

namespace StackGuard
{

void Enter(const wchar_t* funcName, const wchar_t* funcNameExit, const wchar_t* fileName, int line);
void Leave();

}  // namespace StackGuard

#define guard(GUARD_NAME) StackGuard::Enter(GUARD_NAME, GUARD_NAME L" (exit)", __WFILE__, __LINE__)
#define unguard StackGuard::Leave
