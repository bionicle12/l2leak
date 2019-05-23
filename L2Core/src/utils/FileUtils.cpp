#include "l2core/utils/FileUtils.h"

#include "l2core/utils/dbg/StackGuard.h"

#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

// L2NPC inlined
static bool GetWideSymbol(FILE* file, wchar_t* out)
{
    int symbolLowPart = fgetc(file);
    if (feof(file))
    {
        return false;
    }

    int symbolHiPart = fgetc(file);
    if (feof(file))
    {
        return false;
    }

    wchar_t finalWideSymbol = symbolLowPart;
    finalWideSymbol |= symbolHiPart << 8;

    *out = finalWideSymbol;

    return true;
}

// L2NPC 0x004736F0
std::wstring FileUtils::ReadValue(FILE* file)
{
    guard(L"std::wstring FileUtils::ReadValue(FILE *f)");  // FIXED: added

    while (true)
    {
        wchar_t symbol = 0;
        if (!GetWideSymbol(file, &symbol))
        {
            return std::wstring();
        }

        if (symbol == '[')
        {
            break;
        }
    }

    std::wstring value;
    while (true)
    {
        wchar_t symbol = 0;
        if (!GetWideSymbol(file, &symbol))
        {
            return std::wstring();
        }

        if (symbol == ']')
        {
            break;
        }

        value.append(1, symbol);
    }

    unguard();

    return value;
}

// L2NPC 0x004739F0
int FileUtils::ReadIndex(FILE* file)
{
    guard(L"int FileUtils::GetIntEx(FILE *f)");  // FIXED: added

    std::wstring indexString;
    wchar_t symbol = 0;
    // skipping end of line symbols and comments
    while (true)
    {
        if (!GetWideSymbol(file, &symbol))
        {
            return 0;
        }

        if (('0' <= symbol && symbol <= '9') || symbol == '-')
        {
            break;
        }
    }

    // Accumulating numbers and sign symbol
    indexString.append(1, symbol);
    while (true)
    {
        if (!GetWideSymbol(file, &symbol))
        {
            return 0;
        }

        if ((symbol < '0' || symbol > '9') && symbol != '-')
        {
            break;
        }

        indexString.append(1, symbol);
    }

    int stringId = _wtol(indexString.c_str());

    unguard();

    return stringId;
}

// L2NPC 0x00464890
int FileUtils::GetIntEx(FILE* file)
{
    guard(L"int FileUtils::GetIntEx(FILE *f)");

    std::wstring intString;
    while (true)
    {
        wchar_t symbol = 0;
        if (!GetWideSymbol(file, &symbol))
        {
            return 0;
        }

        if (('0' <= symbol && symbol <= '9') || symbol == '-')
        {
            intString.append(1, symbol);
            break;
        }
    }

    while (!feof(file))
    {
        wchar_t symbol = 0;
        if (!GetWideSymbol(file, &symbol))
        {
            break;
        }

        if ((symbol < '0' || symbol > '9') && symbol != '-' && symbol != 'x' && (symbol < 'a' || symbol > 'f'))
        {
            break;
        }

        intString.append(1, symbol);
    }

    int result = 0;
    if (intString.length() > 2 && intString[0] == '0' && (intString[1] == 'x' || intString[1] == 'X'))
    {
        result = wcstol(intString.c_str() + 2, NULL, 16);
    }
    else
    {
        result = _wtol(intString.c_str());
    }

    unguard();

    return result;
}

// L2NPC 0x00473030
const char* FileUtils::LoadBinaryAbsolute(const wchar_t* fileName, uint32_t* size)
{
    guard(L"char *FileUtils::LoadBinaryAbsolute(const wchar_t *fileName, uint32_t *size)");

    int file = _wopen(fileName, _O_BINARY, _O_RDONLY);
    if (file < 0)
    {
        unguard();
        return NULL;
    }

    struct _stat stat = {0};
    _wstat(fileName, &stat);
    char* fileInMemory = (char*)malloc(stat.st_size + 0x50);
    if (fileInMemory == NULL)
    {
        _close(file);
        unguard();
        return NULL;
    }

    _read(file, fileInMemory, stat.st_size);
    _close(file);
    *size = stat.st_size;

    unguard();
    return fileInMemory;
}
