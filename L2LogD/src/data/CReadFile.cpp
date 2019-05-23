#include "l2logd/data/CReadFile.h"

#include "l2core/db/DBConn.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

CReadFile g_readFile;  // L2LogD 0x01BD5020

// L2LogD 0x0040E2F0
CReadFile::CReadFile()
{
    guard(L"CReadFile::CReadFile()");
    unguard();
}

// L2LogD 0x0040E330
bool CReadFile::ParseItemName()
{
    guard(L"bool CReadFile::ParseItemName()");

    FILE* file = ::_wfopen(L".\\Itemname-k.txt", L"rb");
    if (file == NULL)
    {
        return false;
    }

    if (::fseek(file, 0, SEEK_SET) != 0)
    {
        ::fclose(file);
        return false;
    }

    ::fgetwc(file);

    DBConn sql;
    sql.Execute(L"delete from lin2report.dbo.ItemName");
    bool itemBegin = false;
    int id = -1;
    wchar_t name[256];
    wchar_t description[512];

    while (true)
    {
        wchar_t tokenBuffer[256];
        ::memset(tokenBuffer, 0, sizeof(tokenBuffer));

        wchar_t token[256];
        ::memset(token, 0, sizeof(token));

        int size = 0;
        wchar_t symbol = 0;
        wchar_t* tokenIterator = tokenBuffer;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == '\r')
            {
                break;
            }

            if (symbol == WEOF)
            {
                ::fclose(file);
                return true;
            }

            if (symbol != '[' && symbol != ']' && symbol != '\'')
            {
                *tokenIterator = symbol;
                ++tokenIterator;
            }
            ++size;
            //} while (size < 512); FIXED
        } while (size < sizeof(tokenBuffer) / sizeof(*tokenBuffer));

        if (symbol == WEOF)
        {
            ::fclose(file);
            return false;
        }

        Utils::CopyStrInLowerCase(tokenBuffer, token);
        if (!::wcscmp(token, L"item_name_begin"))
        {
            ::memset(name, 0, sizeof(name));
            itemBegin = true;
            id = 0;
            ::memset(description, 0, sizeof(description));
        }
        else if (!::wcscmp(token, L"item_name_end"))
        {
            itemBegin = false;
            sql.Execute(L"insert into lin2report.dbo.ItemName(item_id, item_name, item_desc) values(%d, '%s', '%s') ", id, name, description);
        }
        else if (itemBegin == true)
        {
            wchar_t* equalSignIterator = ::wcschr(tokenBuffer, '=');
            if (equalSignIterator != NULL)
            {
                *equalSignIterator = 0;

                wchar_t attributeName[256];
                ::wcscpy(attributeName, tokenBuffer);

                wchar_t value[256];
                ::wcscpy(value, equalSignIterator + 1);

                wchar_t attributeNameLowerCase[256];
                Utils::CopyStrInLowerCase(attributeName, attributeNameLowerCase);
                if (!::wcsncmp(attributeNameLowerCase, L"id", 2u))
                {
                    id = _wtol(value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"name", 4u))
                {
                    ::wcscpy(name, value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"description", 11u))
                {
                    ::wcscpy(description, value);
                }
            }
        }
    }

    ::fclose(file);
    return true;
}

// L2LogD 0x0040E680
bool CReadFile::ParseNPCName()
{
    guard(L"bool CReadFile::ParseNPCName()");

    FILE* file = ::_wfopen(L".\\npcname-k.txt", L"rb");
    if (file == NULL)
    {
        return false;
    }

    if (::fseek(file, 0, SEEK_SET) != 0)
    {
        ::fclose(file);
        return false;
    }

    ::fgetwc(file);

    DBConn sql;
    sql.Execute(L"delete from lin2report.dbo.NPCName");
    bool npcBegin = 0;

    int id = -1;
    wchar_t name[256];

    while (true)
    {
        wchar_t tokenBuffer[256];
        ::memset(tokenBuffer, 0, sizeof(tokenBuffer));

        wchar_t token[256];
        ::memset(token, 0, sizeof(token));

        int size = 0;
        wchar_t symbol = 0;
        wchar_t* tokenIterator = tokenBuffer;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == '\r')
            {
                break;
            }

            if (symbol == WEOF)
            {
                ::fclose(file);
                return true;
            }

            if (symbol != '[' && symbol != ']' && symbol != '\'')
            {
                *tokenIterator = symbol;
                ++tokenIterator;
            }
            ++size;
            //} while (size < 512); FIXED
        } while (size < sizeof(tokenBuffer) / sizeof(*tokenBuffer));

        if (symbol == WEOF)
        {
            ::fclose(file);
            return false;
        }

        Utils::CopyStrInLowerCase(tokenBuffer, token);
        if (!::wcscmp(token, L"npc_begin"))
        {
            npcBegin = true;
            id = 0;
            ::memset(name, 0, sizeof(name));
        }
        else if (!::wcscmp(token, L"npc_end"))
        {
            npcBegin = false;
            sql.Execute(L"insert into lin2report.dbo.NPCName(NPC_id, NPC_name) values(%d, '%s') ", id, name);
        }
        else if (npcBegin == true)
        {
            wchar_t* equalSignIterator = ::wcschr(tokenBuffer, '=');
            if (equalSignIterator != NULL)
            {
                *equalSignIterator = 0;
                wchar_t attributeName[256];
                ::wcscpy(attributeName, tokenBuffer);

                wchar_t value[256];
                ::wcscpy(value, equalSignIterator + 1);

                wchar_t attributeNameLowerCase[256];
                Utils::CopyStrInLowerCase(attributeName, attributeNameLowerCase);

                if (!::wcsncmp(attributeNameLowerCase, L"id", 2u))
                {
                    id = _wtol(value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"name", 4u))
                {
                    ::wcscpy(name, value);
                }
            }
        }
    }

    ::fclose(file);
    return true;
}

// L2LogD 0x0040E980
bool CReadFile::ParseQuestName()
{
    guard(L"bool CReadFile::ParseQuestName()");

    FILE* file = ::_wfopen(L".\\questname-k.txt", L"rb");
    if (file == NULL)
    {
        return false;
    }

    if (::fseek(file, 0, SEEK_SET) != 0)
    {
        ::fclose(file);
        return false;
    }

    ::fgetwc(file);

    DBConn sql;
    sql.Execute(L"delete from lin2report.dbo.QuestName");
    bool questBegin = false;
    int id = -1;
    wchar_t name[256];
    wchar_t description[1024];

    while (true)
    {
        wchar_t tokenBuffer[1024];
        ::memset(tokenBuffer, 0, sizeof(tokenBuffer));

        wchar_t token[1024];
        ::memset(token, 0, sizeof(token));

        int size = 0;
        wchar_t symbol = 0;
        wchar_t* tokenIterator = tokenBuffer;

        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == '\r')
            {
                break;
            }

            if (symbol == WEOF)
            {
                ::fclose(file);
                return true;
            }

            if (symbol != '[' && symbol != ']' && symbol != '\'')
            {
                *tokenIterator = symbol;
                ++tokenIterator;
            }

            ++size;
            //} while (size < 1024); FIXED
        } while (size < sizeof(tokenBuffer) / sizeof(*tokenBuffer));

        if (symbol == WEOF)
        {
            break;
        }

        Utils::CopyStrInLowerCase(tokenBuffer, token);
        if (!::wcscmp(token, L"quest_begin"))
        {
            ::memset(name, 0, sizeof(name));
            questBegin = true;
            id = 0;
            ::memset(description, 0, sizeof(description));
        }
        else if (!::wcsncmp(token, L"quest_end", 9u))
        {
            questBegin = false;
            sql.Execute(L"insert into lin2report.dbo.QuestName(quest_id, quest_name, quest_desc) values(%d, '%s', '%s') ", id, name, description);
        }
        else if (questBegin == true)
        {
            wchar_t* equalSignIterator = ::wcschr(tokenBuffer, '=');
            if (equalSignIterator != NULL)
            {
                *equalSignIterator = 0;

                wchar_t attributeName[256];
                ::memset(attributeName, 0, sizeof(attributeName));
                ::wcscpy(attributeName, tokenBuffer);

                wchar_t value[1024];
                ::memset(value, 0, sizeof(value));
                ::wcscpy(value, equalSignIterator + 1);

                wchar_t attributeNameLowerCase[256];
                ::memset(attributeNameLowerCase, 0, sizeof(attributeNameLowerCase));
                Utils::CopyStrInLowerCase(attributeName, attributeNameLowerCase);
                if (!::wcsncmp(attributeNameLowerCase, L"id", 2u))
                {
                    id = _wtol(value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"name", 4u))
                {
                    ::wcscpy(name, value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"desc", 4u))
                {
                    ::wcscpy(description, value);
                }
            }
        }
    }

    ::fclose(file);
    return true;
}

// L2LogD 0x0040ECE0
bool CReadFile::ParseSkillName()
{
    guard(L"bool CReadFile::ParseSkillName()");

    FILE* file = ::_wfopen(L".\\skillname-k.txt", L"rb");
    if (file == NULL)
    {
        return false;
    }

    if (::fseek(file, 0, SEEK_SET) != 0)
    {
        ::fclose(file);
        return false;
    }

    ::fgetwc(file);

    DBConn sql;
    sql.Execute(L"delete from lin2report.dbo.SkillName");
    bool skillBegin = 0;
    int id = -1;
    int level = -1;
    wchar_t name[256];
    wchar_t description[512];

    while (true)
    {
        wchar_t tokenBuffer[256];
        ::memset(tokenBuffer, 0, sizeof(tokenBuffer));

        wchar_t token[256];
        ::memset(token, 0, sizeof(token));

        int size = 0;
        wchar_t symbol = 0;
        wchar_t* tokenIterator = tokenBuffer;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == '\r')
            {
                break;
            }

            if (symbol == WEOF)
            {
                ::fclose(file);
                return true;
            }

            if (symbol != '[' && symbol != ']' && symbol != '\'')
            {
                *tokenIterator = symbol;
                ++tokenIterator;
            }

            ++size;
            //} while (size < 512); FIXED
        } while (size < sizeof(tokenBuffer) / sizeof(*tokenBuffer));

        if (symbol == WEOF)
        {
            ::fclose(file);
            return false;
        }

        Utils::CopyStrInLowerCase(tokenBuffer, token);
        if (!::wcscmp(token, L"skill_begin"))
        {
            ::memset(name, 0, sizeof(name));
            id = 0;
            skillBegin = true;
            level = 0;
            ::memset(description, 0, sizeof(description));
        }
        else if (!::wcscmp(token, L"skill_end"))
        {
            skillBegin = 0;
            sql.Execute(L"insert into lin2report.dbo.SkillName(skill_id, skill_name, skill_lev, skill_desc) values(%d, '%s', %d,  '%s') ", id, name, level, description);
        }
        else if (skillBegin == true)
        {
            wchar_t* equalSignIterator = ::wcschr(tokenBuffer, '=');
            if (equalSignIterator != NULL)
            {
                *equalSignIterator = 0;
                wchar_t attributeName[256];
                ::wcscpy(attributeName, tokenBuffer);

                wchar_t value[256];
                ::wcscpy(value, equalSignIterator + 1);

                wchar_t attributeNameLowerCase[256];
                Utils::CopyStrInLowerCase(attributeName, attributeNameLowerCase);
                if (!::wcsncmp(attributeNameLowerCase, L"skill_id", 8u))
                {
                    id = _wtol(value);
                }
                if (!::wcsncmp(attributeNameLowerCase, L"skill_level", 11u))
                {
                    level = _wtol(value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"name", 4u))
                {
                    ::wcscpy(name, value);
                }
                else if (!::wcsncmp(attributeNameLowerCase, L"desc", 4u))
                {
                    ::wcscpy(description, value);
                }
            }
        }
    }
    ::fclose(file);
    return true;
}
