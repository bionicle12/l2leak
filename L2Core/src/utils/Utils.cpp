#include "l2core/utils/Utils.h"

#include "l2core/utils/dbg/StackGuard.h"

#include <windows.h>

#include <cstdlib>
#include <cstring>
#include <string>

namespace Utils
{

// L2CacheD 0x00466190
bool CheckCharacterName(const wchar_t* charName, int code)
{
    guard(L"bool CheckCharacterName(const WCHAR * name, int code)");

    const size_t nameLen = ::wcslen(charName);
    for (size_t i = 0; i < nameLen; ++i)
    {
        const wchar_t symbol = charName[i];
        if (('0' <= symbol && symbol <= '9') || ('a' <= symbol && symbol <= 'z') || ('A' <= symbol && symbol <= 'Z'))
        {
            continue;
        }

        // Unicode symbol handling

        if (code == 0)  // Korean, AC00 - D7AF     Hangul Syllables
        {
            if ((symbol < 0xAC00u) || (symbol > 0xD7A3u))
            {
                return false;
            }
        }

        // Japan and Taiwan
        if ((code == 2) || code == 3)
        {
            // 4E00 - 9FFF CJK Unified Ideographs
            if ((symbol < 0x3041u || symbol > 0x3096u) && (symbol < 0x30A1u || symbol > 0x30FCu))
            {
                if ((symbol < 0x4E00u) || (symbol > 0x9FA5u))
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }

    unguard();

    return true;
}

// L2LogD 0x00402920, L2CacheD 0x004660B0
wchar_t* GetFileName(wchar_t* str)
{
    wchar_t* backSlash = ::wcsrchr(str, '\\');
    if (backSlash)
    {
        return backSlash + 1;
    }

    return str;
}

// L2LogD 0x004062E0, L2CacheD 0x00466120
int AnsiToUnicode(const char* ansistr, int /*maxansilen*/, wchar_t* unistr, int /*maxunilen*/)
{
    guard(L"int AnsiToUnicode(char* ansistr, int maxansilen, wchar_t* unistr, int maxunilen)");

    int length = ::MultiByteToWideChar(CP_ACP, 0, ansistr, -1, 0, 0);
    ::MultiByteToWideChar(CP_ACP, 0, ansistr, -1, unistr, length);
    unistr[length - 1] = 0;

    unguard();

    return length;
}

// L2LogD 0x004063A0
bool IsNumber(wchar_t chr)
{
    return chr >= '0' && chr <= '9' || chr == '-';
}

// L2LogD 0x00406B40
int GetIntFromString(const wchar_t* strWithNum)
{
    guard(L"int GetIntFromString(wchar_t * sNum)");

    std::wstring str;
    int strWithNumLen = ::wcslen(strWithNum);
    if (strWithNumLen < 1)
    {
        unguard();
        return 0;
    }

    if (IsNumber(*strWithNum))
    {
        int i = 0;
        do
        {
            i++;
            if (i > strWithNumLen)
            {
                break;
            }
            if (i >= 10)
            {
                break;
            }
            str.assign(1, *strWithNum);
        } while (IsNumber(strWithNum[i]));
    }

    int number = ::_wtol(str.c_str());

    unguard();

    return number;
}

// L2LogD 0x0040BE10, L2CacheD 0x00483050
char* UnicodeToMultibyte(const wchar_t* wideMsg)
{
    guard(L"UnicodeToMultibyte");

    int newLength = ::WideCharToMultiByte(CP_ACP, 0, wideMsg, -1, 0, 0, 0, 0);
    char* multiByte = new char[newLength + 1];
    ::WideCharToMultiByte(CP_ACP, 0, wideMsg, -1, multiByte, newLength, 0, 0);
    multiByte[newLength - 1] = 0;

    unguard();

    return multiByte;
}

// L2LogD 0x0040FC90
char* UnicodeToMultibyte2(const wchar_t* wideMsg)
{
    guard(L"UnicodeToMultibyte");

    int newLength = ::WideCharToMultiByte(CP_ACP, 0, wideMsg, -1, 0, 0, 0, 0);
    char* multiByte = new char[newLength + 1];

    BOOL usedDefaultChar;
    ::WideCharToMultiByte(CP_ACP, 0, wideMsg, -1, multiByte, newLength, 0, &usedDefaultChar);
    multiByte[newLength - 1] = 0;

    unguard();

    return multiByte;
}

// L2LogD 0x00402690, L2CacheD 0x0040F860
char* UnicodeToMultibyte_WithoutAllocation(const wchar_t* wideMsg)
{
    static char localBuffer[40001];
    int newLength = ::WideCharToMultiByte(CP_THREAD_ACP, 0, wideMsg, -1, 0, 0, 0, 0);

    BOOL usedDefaultChar;
    ::WideCharToMultiByte(CP_THREAD_ACP, 0, wideMsg, -1, localBuffer, newLength, 0, &usedDefaultChar);
    localBuffer[newLength - 1] = 0;
    return localBuffer;
}

// L2LogD 0x00413C15
wchar_t* ToWString(int number, wchar_t* outStr, int maxSize)
{
    char buffer[20];
    ::_itoa(number, buffer, maxSize);
    ::mbstowcs(outStr, buffer, sizeof(buffer));
    return outStr;
}

// L2LogD 0x00406280, L2CacheD 0x004660B0, L2NPC 0x00472F10
int UnicodeToAnsi(const wchar_t* unistr, int /*maxunilen*/, char* ansistr, int /*maxansilen*/)
{
    guard(L"int UnicodeToAnsi(WCHAR* unistr, int maxunilen, char* ansistr, int maxansilen)");

    int length = ::WideCharToMultiByte(CP_ACP, 0, unistr, -1, 0, 0, 0, 0);

    ::WideCharToMultiByte(CP_ACP, 0, unistr, -1, ansistr, length, 0, 0);
    ansistr[length - 1] = 0;

    unguard();

    return length;
}

// L2LogD 0x00413D9D, L2CacheD 0x00488A55
wchar_t* TimeToWStr(const std::time_t* time)
{
    tm* localTime = std::localtime(time);
    if (localTime != NULL)
    {
        return ::_wasctime(localTime);
    }

    return NULL;
}

// L2LogD 0x004126D0, L2NPC 0x004AACB1
char* TimeToStr(const std::time_t* time)
{
    tm* localTime = std::localtime(time);
    if (localTime != NULL)
    {
        return ::asctime(localTime);
    }

    return NULL;
}

// L2LogD 0x00406340, L2CacheD 0x004662A0
void Utils::CopyStrInLowerCase(const wchar_t* in, wchar_t* out)
{
    int inputSize = ::wcslen(in);
    if (inputSize <= 0)
    {
        // out[inputSize] = 0; FIXED
        out[0] = 0;
        return;
    }

    for (int i = 0; i < inputSize; ++i)
    {
        wchar_t symbol = in[i];
        if (symbol > 64u && symbol < 91u)  // CAPITAL letter
        {
            symbol += 32;
        }
        *out = symbol;
        ++out;
    }
}

// L2NPC 0x004473A0
double GetRandomNumber(double min, double max)
{
    guard(L"double GetRandomNumber(double min, double max)");

    int seed = std::rand();
    const double RAND_MAX_DIV_BY_1 = 0.00003051850947599719;
    double result = double(seed * RAND_MAX_DIV_BY_1 * (max - min) + min);

    unguard();
    return result;
}

// L2NPC 0x004480D0
int Random(int min, int max)
{
    guard(L"int Random(int min, int max)");

    if (min > max)
    {
        int oldMin = min;
        min = max;
        max = oldMin;
    }

    int seed = std::rand();
    int result = min + seed % (max - min + 1);
    unguard();
    return result;
}

}  // namespace Utils
