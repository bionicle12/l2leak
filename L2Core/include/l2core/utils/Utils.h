#pragma once

#include <ctime>

namespace Utils
{

bool IsNumber(wchar_t chr);  // L2LogD 0x004063A0

bool CheckCharacterName(const wchar_t* charName, int code);  // L2CacheD 0x00466190

wchar_t* ToWString(int number, wchar_t* outStr, int maxSize);                            // L2LogD 0x00413C15, L2CacheD 0x00489966
char* UnicodeToMultibyte2(const wchar_t* wideMsg);                                       // L2LogD 0x0040FC90
char* UnicodeToMultibyte(const wchar_t* wideMsg);                                        // L2LogD 0x0040BE10, L2CacheD 0x00483050
char* UnicodeToMultibyte_WithoutAllocation(const wchar_t* wideMsg);                      // L2LogD 0x00402690, L2CacheD 0x0040F860
int AnsiToUnicode(const char* ansistr, int maxansilen, wchar_t* unistr, int maxunilen);  // L2LogD 0x004062E0, L2CacheD 0x00466120
int GetIntFromString(const wchar_t* strWithNum);                                         // L2LogD 0x00406B40
int UnicodeToAnsi(const wchar_t* unistr, int maxunilen, char* ansistr, int maxansilen);  // L2LogD 0x00406280, L2CacheD 0x004660B0, L2NPC 0x00472F10
void CopyStrInLowerCase(const wchar_t* in, wchar_t* out);                                // L2LogD 0x00406340, L2CacheD 0x004662A0
wchar_t* GetFileName(wchar_t* str);                                                      // L2LogD 0x00402920, L2CacheD 0x0040FAF0

char* TimeToStr(const std::time_t* time);      // L2LogD 0x004126D0, L2NPC 0x004AACB1
wchar_t* TimeToWStr(const std::time_t* time);  // L2LogD 0x00413D9D, L2CacheD 0x00488A55

int Random(int min, int max);                    // L2NPC 0x004480D0
double GetRandomNumber(double min, double max);  // L2NPC 0x004473A0

}  // namespace Utils
