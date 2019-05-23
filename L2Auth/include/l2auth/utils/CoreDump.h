#pragma once

#include <windows.h>

class CoreDump
{
public:
    static void createReport(_EXCEPTION_POINTERS* ex);  // L2AuthD 0x004169E0

private:
    static void IntelStackWalk(HANDLE hFile, CONTEXT* contextRecord);      // L2AuthD 0x004161BE
    static void ImageHelpStackWalk(HANDLE hFile, CONTEXT* contextRecord);  // L2AuthD 0x00415DD8

    static bool GetLogicalAddress(LPCVOID addr, LPSTR moduleName, DWORD nSize, int* section, int* offset);  // L2AuthD 0x00415CD1
    static void writeLine(HANDLE hFile, const char* format, ...);                                           // L2AuthD 0x0041612B
    static void writeModules(HANDLE hFile);                                                                 // L2AuthD 0x0041703B
    static void writeModuleInfo(HANDLE hFile, HMODULE hModule);                                             // L2AuthD 0x00417112
    static void getFileTime(char* out, FILETIME fileTime);                                                  // L2AuthD 0x004172E8
    static void writeExtraInfo(HANDLE hFile);                                                               // L2AuthD 0x004173B0
    static const char* exceptionToString(int exceptionCode);                                                // L2AuthD 0x004174C8
};
