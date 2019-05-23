#pragma once

#include <string>
#include <l2core/utils/cstdint_support.h>
#include <stdio.h>

namespace FileUtils
{
int GetIntEx(FILE* file);                                                 // L2NPC 0x00464890
std::wstring ReadValue(FILE* file);                                       // L2NPC 0x004736F0
int ReadIndex(FILE* file);                                                // L2NPC 0x004739F0
const char* LoadBinaryAbsolute(const wchar_t* fileName, uint32_t* size);  // L2NPC 0x00473030

}  // namespace FileUtils
