#include "cached/data/CReadFile.h"

#include "cached/data/CReadItemData.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

CReadFile g_readFile;  // L2CacheD 02684B88

// L2CacheD 0x00486490
CReadFile::CReadFile()
    : m_lock()
    , m_items()
{
    guard(L"CReadFile::CReadFile()");
    ::InitializeCriticalSectionAndSpinCount(&m_lock, 4000u);
    unguard();
}

// L2CacheD 0x0049D9F0
CReadFile::~CReadFile()
{
    guard(L"CReadFile::~CReadFile()");

    ::EnterCriticalSection(&m_lock);

    for (Items::iterator it = m_items.begin(); it != m_items.end(); ++it)
    {
        Items::value_type& pair = *it;
        CReadItemData* item = pair.second;
        delete item;
    }

    m_items.clear();

    ::LeaveCriticalSection(&m_lock);
    ::DeleteCriticalSection(&m_lock);

    unguard();
}

// L2CacheD 0x00485970
const CReadItemData* CReadFile::FindItem(int itemType) const
{
    guard(L"CReadItemData* CReadFile::FindItem(int itemId)");

    Items::const_iterator it = m_items.find(itemType);
    if (it == m_items.end())
    {
        return NULL;
    }

    const CReadItemData* item = it->second;

    unguard();

    return item;
}

// L2CacheD 0x00486010
void CReadFile::ParseItemData()
{
    guard(L"void CReadFile::ParseItemData()");

    FILE* file = ::_wfopen(L"..\\CacheDScript\\itemdata.txt", L"rb");
    if (file == NULL)
    {
        return;
    }

    if (::fseek(file, 0, SEEK_SET) != 0)
    {
        ::fclose(file);
        return;
    }
    ::EnterCriticalSection(&m_lock);

    ::fgetwc(file);

    int tokenIndex = 0;
    int itemType = 0;
    int defaultPrice = 0;
    wchar_t itemName[256];

    while (true)
    {
        wchar_t tokenBuffer[256];
        ::memset(tokenBuffer, 0, sizeof(tokenBuffer));

        wchar_t token[256];
        ::memset(token, 0, sizeof(token));

        if (::fwscanf(file, L"%s", tokenBuffer) < 1)
        {
            break;
        }

        Utils::CopyStrInLowerCase(tokenBuffer, token);
        if (::wcscmp(token, L"item_begin") == 0)
        {
            tokenIndex = 0;
            itemType = 0;
            ::memset(itemName, 0, sizeof(itemName));
            defaultPrice = 0;
            while (true)
            {
                ::memset(tokenBuffer, 0, sizeof(tokenBuffer));
                ::memset(token, 0, sizeof(token));

                if (::fwscanf(file, L"%s", tokenBuffer) < 1)
                {
                    break;
                }

                Utils::CopyStrInLowerCase(tokenBuffer, token);
                if (::wcscmp(token, L"item_end") == 0)
                {
                    break;
                }

                if (++tokenIndex == 2)
                {
                    itemType = _wtol(tokenBuffer);
                }
                else if (tokenIndex == 3)
                {
                    ::wcscpy(itemName, tokenBuffer);
                }
                else
                {
                    wchar_t* equalSignIterator = ::wcschr(tokenBuffer, '=');
                    if (equalSignIterator != NULL)
                    {
                        *equalSignIterator = 0;

                        wchar_t attributeName[256];
                        ::memset(attributeName, 0, sizeof(attributeName));
                        ::wcscpy(attributeName, tokenBuffer);

                        wchar_t value[256];
                        ::memset(value, 0, sizeof(value));
                        ::wcscpy(value, equalSignIterator + 1);

                        wchar_t attributeNameLowerCase[256];
                        ::memset(attributeNameLowerCase, 0, sizeof(attributeNameLowerCase));
                        Utils::CopyStrInLowerCase(attributeName, attributeNameLowerCase);

                        if (::wcscmp(attributeNameLowerCase, L"default_price") == 0)
                        {
                            defaultPrice = _wtol(value);
                        }
                    }
                }
            }

            CReadItemData* itemData = new CReadItemData(itemType, itemName, defaultPrice);
            m_items.insert(std::make_pair(itemType, itemData));
        }
    }

    ::fclose(file);
    ::LeaveCriticalSection(&m_lock);

    unguard();
}

// L2CacheD 0x004859A0
int CReadFile::GetDefaultPrice(int itemType) const
{
    guard(L"int CReadFile::GetDefaultPrice(int itemType)");  // FIXED: added

    Items::const_iterator it = m_items.find(itemType);
    if (it == m_items.end())
    {
        return 0;
    }

    const CReadItemData* item = it->second;

    unguard();  // FIXED: added

    return item->m_defaultPrice;
}
