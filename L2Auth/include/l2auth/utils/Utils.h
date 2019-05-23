#pragma once

#include "l2auth/logger/LogId.h"

#include <windows.h>
#include <Sqltypes.h>

#include <ctime>
#include <l2core/utils/cstdint_support.h>

namespace Utils
{
// Capitalizes acc name
int StdAccount(char* accName);                                                                                                  // L2AuthD 0x0043ADF4
void WriteLogD(LogId logId, char* accName, in_addr connectedIP, int payStat, int age, int a6, int zero, int variant, int uid);  // L2AuthD 0x0043AFA2
int AnsiToUnicode(const char* multiByteStr, int length, wchar_t* wideCharStr);                                                  // L2AuthD 0x0043B6A8
bool CheckAccount(char* accName);                                                                                               // L2AuthD 0x0043B878
bool IsValidNumeric(char* str, int size);                                                                                       // L2AuthD 0x0043B9BA
bool CheckDiskSpace(LPCSTR lpDirectoryName, uint64_t limit);                                                                    // L2AuthD 0x0043BA17
time_t ConvertSQLToTome(const TIMESTAMP_STRUCT& timeStamp, tm* tmStruct);                                                       // L2AuthD 0x0043B7FE
const char* getFileName(const char* str);                                                                                       // L2AuthD 0x0041618B

}  // namespace Utils
