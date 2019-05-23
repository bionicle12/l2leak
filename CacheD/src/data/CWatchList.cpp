#include "cached/data/CWatchList.h"

#include "cached/data/CWatchObject.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

CWatchList g_watchList;  // 0x02684BAC

// L2CacheD 0x00487220
CWatchList::CWatchList()
    : m_lock()
    , m_npcs()
    , m_items()
{
    ::InitializeCriticalSectionAndSpinCount(&m_lock, 4000u);
}

// L2CacheD 0x0049DA00
CWatchList::~CWatchList()
{
    guard(L"CWatchList::~CWatchList()");

    ::EnterCriticalSection(&m_lock);

    for (WatchObjects::iterator it = m_npcs.begin(); it != m_npcs.end(); ++it)
    {
        WatchObjects::value_type& pair = *it;
        CWatchObject* watchObject = pair.second;
        delete watchObject;
    }

    m_npcs.clear();

    for (WatchObjects::iterator it = m_items.begin(); it != m_items.end(); ++it)
    {
        WatchObjects::value_type& pair = *it;
        CWatchObject* watchObject = pair.second;
        delete watchObject;
    }

    m_items.clear();

    ::LeaveCriticalSection(&m_lock);
    ::DeleteCriticalSection(&m_lock);

    unguard();
}

// L2CacheD 0x00486570
const CWatchObject* CWatchList::CheckWatchList(WatchType type, int itemType) const
{
    guard(L"CWatchObject* CWatchList::CheckWatchList(WatchType type, int itemId)");

    switch (type)
    {
        case WatchType_NPC:
        {
            WatchObjects::const_iterator it = m_npcs.find(itemType);
            if (it == m_npcs.end())
            {
                unguard();
                return NULL;
            }

            CWatchObject* npc = it->second;
            unguard();
            return npc;
        }
        case WatchType_ITEM:
        {
            WatchObjects::const_iterator it = m_items.find(itemType);
            if (it == m_items.end())
            {
                unguard();
                return NULL;
            }

            CWatchObject* item = it->second;
            unguard();
            return item;
        }
    }

    unguard();
    return NULL;
}

// L2CacheD 0x00486C60
bool CWatchList::ParseWatchList()
{
    guard(L"bool CWatchList::ParseWatchList()");

    FILE* file = ::_wfopen(L"..\\CacheDScript\\watch_list.txt", L"rb");
    if (file == NULL)
    {
        int err = ::GetLastError();
        g_winlog.Add(LOG_ERROR, L"CWatchList::ParseWatchList() file open failed. ::GetLastError(%d)", err);
        unguard();
        return false;
    }

    if (::fseek(file, 0, SEEK_SET) != 0)
    {
        ::fclose(file);
        return false;
    }

    ::EnterCriticalSection(&m_lock);

    ::fgetwc(file);
    if (::feof(file))
    {
        ::fclose(file);
        ::LeaveCriticalSection(&m_lock);

        unguard();
        return false;
    }

    bool commentedLine = false;
    WatchType watchType = WatchType_NPC;
    while (true)
    {
        commentedLine = false;

        wchar_t tokenBuffer[256];
        ::memset(tokenBuffer, 0, sizeof(tokenBuffer));

        wchar_t previousSymbol = 0;
        int id = 0;
        int size = 0;
        wchar_t* tokenIterator = tokenBuffer;
        do
        {
            wchar_t symbol = ::fgetwc(file);
            if (symbol == '\n')
            {
                break;
            }

            if (commentedLine)
            {
                ++size;
                continue;
            }

            if (symbol == '\t' || symbol == '\r')  // replace tabs and \r with whitespaces
            {
                *tokenIterator = ' ';
            }
            else
            {
                *tokenIterator = symbol;
            }

            ++tokenIterator;
            if (symbol == '/' && previousSymbol == '/')  // comments
            {
                wchar_t* prev = tokenIterator - 1;
                *prev = 0;
                commentedLine = true;
            }
            previousSymbol = symbol;

            ++size;
        } while (size < sizeof(tokenBuffer) / sizeof(*tokenBuffer));

        int bufLength = ::wcslen(tokenBuffer);
        if (bufLength > 0)
        {
            wchar_t* it = &tokenBuffer[bufLength - 1];
            // removing trailing whitespaces
            for (int i = bufLength; i > 0; --i)
            {
                if (*it == ' ')
                {
                    *it = 0;
                    --it;
                }
                else
                {
                    break;
                }
            }
        }

        wchar_t additionalInfo[256];
        ::memset(additionalInfo, 0, sizeof(additionalInfo));

        if (::_wcsicmp(tokenBuffer, L"npc") == 0)
        {
            watchType = WatchType_NPC;
        }
        else if (::_wcsicmp(tokenBuffer, L"item") == 0)
        {
            watchType = WatchType_ITEM;
        }
        else
        {
            wchar_t* equalSignIterator = ::wcschr(tokenBuffer, ' ');
            if (equalSignIterator != NULL)
            {
                *equalSignIterator = 0;

                wchar_t value[256];
                ::memset(value, 0, sizeof(value));
                ::wcscpy(value, tokenBuffer);

                id = _wtol(value);
                ::wcscpy(additionalInfo, equalSignIterator + 1);
            }

            if (watchType == WatchType_NPC)
            {
                CWatchObject* watchObject = new CWatchObject(id, 0, additionalInfo);
                m_npcs.insert(std::make_pair(id, watchObject));
            }
            else if (watchType == WatchType_ITEM)
            {
                CWatchObject* watchObject = new CWatchObject(0, id, additionalInfo);
                m_items.insert(std::make_pair(id, watchObject));
            }
        }

        if (::feof(file))
        {
            break;
        }
    }

    ::fclose(file);
    ::LeaveCriticalSection(&m_lock);

    unguard();
    return true;
}
