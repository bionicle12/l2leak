#include "cached/data/CAddData.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

CAddData g_addData;  // L2CacheD 0x004F2754

// L2CacheD 0x00404400
CAddData::CAddData()
{
}

// L2CacheD 0x00404410
CAddData::~CAddData()
{
}

// L2CacheD 0x00404420
void CAddData::AddItemData()
{
    guard(L"void CAddData::AddItemData()");

    const wchar_t fileName[] = L"..\\CachedScript\\itemcache.txt";
    FILE* file = ::_wfopen(fileName, L"rb");
    if (file == NULL)
    {
        wchar_t text[512];
        ::wsprintfW(text, L"Add item data fail. Cannot find file[%s]", fileName);
        ::MessageBoxW(0, text, L"Add item data fail", MB_OK);
        g_winlog.Add(LOG_ERROR, L"Cannot find [%s]", fileName);
        unguard();
        return;
    }

    wchar_t name[512];
    ::memset(name, 0, sizeof(name));

    wchar_t description[512];
    ::memset(description, 0, sizeof(description));

    wchar_t consumeType[32];
    ::memset(consumeType, 0, sizeof(consumeType));

    wchar_t isQuestBuffer[32];
    ::memset(isQuestBuffer, 0, sizeof(isQuestBuffer));

    wchar_t idBuffer[32];
    ::memset(idBuffer, 0, sizeof(idBuffer));

    DBConn sql;
    sql.Execute(L"EXEC lin_FlushItemName");

    ::fgetwc(file);

    while (true)
    {
        ::memset(name, 0, sizeof(name));
        ::memset(description, 0, sizeof(description));
        ::memset(consumeType, 0, sizeof(consumeType));
        ::memset(isQuestBuffer, 0, sizeof(isQuestBuffer));
        ::memset(idBuffer, 0, sizeof(idBuffer));

        int size = 0;
        wchar_t* bufferIt = idBuffer;
        wchar_t symbol = WEOF;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n')
            {
                break;
            }

            if (symbol == WEOF)
            {
                ::fclose(file);
                unguard();
                return;
            }

            if (symbol != '[' && symbol != ']')
            {
                *bufferIt = symbol;
                ++bufferIt;
            }
            ++size;
        } while (size < 5);

        if (symbol == WEOF)
        {
            break;
        }

        size = 0;
        int nameIt = 0;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == WEOF)
            {
                break;
            }
            if (symbol != '[' && symbol != ']')
            {
                if (symbol == '\'')
                {
                    name[nameIt++] = '\'';
                    name[nameIt] = '\'';
                }
                else
                {
                    name[nameIt] = symbol;
                }
                ++nameIt;
            }
            ++size;
        } while (size < 512);
        if (nameIt == 0)
        {
            name[0] = '0';
        }

        if (symbol == WEOF)
        {
            break;
        }

        size = 0;
        int descriptionIt = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != '\t' && symbol != '\n' && symbol != WEOF)
            {
                if (symbol != '[' && symbol != ']')
                {
                    if (symbol == '\'')
                    {
                        description[descriptionIt++] = '\'';
                        description[descriptionIt] = '\'';
                    }
                    else
                    {
                        description[descriptionIt] = symbol;
                    }
                    ++descriptionIt;
                }
                if (++size < 512)
                {
                    continue;
                }
            }
            goto LABEL_41;
        }
        ::fgetwc(file);

    LABEL_41:
        if (!descriptionIt)
        {
            description[0] = ' ';
        }

        size = 0;
        int consumeTypeIt = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != '\t' && symbol != '\n' && symbol != WEOF)
            {
                if (symbol != '[' && symbol != ']')
                {
                    if (symbol == '\'')
                    {
                        consumeType[consumeTypeIt++] = '\'';
                        consumeType[consumeTypeIt] = '\'';
                    }
                    else
                    {
                        consumeType[consumeTypeIt] = symbol;
                    }
                    ++consumeTypeIt;
                }
                if (++size < 512)
                {
                    continue;
                }
            }
            goto LABEL_57;
        }
        symbol = ::fgetwc(file);
    LABEL_57:
        if (!consumeTypeIt)
        {
            consumeType[0] = ' ';
        }
        if (symbol == WEOF)
        {
            break;
        }

        size = 0;
        int isQuestBufferIt = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != '\t' && symbol != '\n' && symbol != WEOF)
            {
                if (symbol != '[' && symbol != ']')
                {
                    isQuestBuffer[isQuestBufferIt++] = symbol;
                }
                if (++size < 256)
                {
                    continue;
                }
            }
            goto LABEL_71;
        }
        symbol = ::fgetwc(file);
    LABEL_71:
        if (!isQuestBufferIt)
        {
            isQuestBuffer[0] = '0';
        }
        if (symbol == WEOF)
        {
            break;
        }

        int isQuest = _wtol(isQuestBuffer);
        int id = _wtol(idBuffer);
        sql.Execute(L"EXEC lin_InsertItemName %d, N'%s', N'%s', N'%s', %d", id, name, description, consumeType, isQuest);

        g_winlog.Add(LOG_INF, L"%d, %s, %s, %s, %d", id, name, description, consumeType, isQuest);
    }

    ::fclose(file);
    unguard();
}

// L2CacheD 0x004048A0
void CAddData::AddSkillData()
{
    guard(L"void CAddData::AddSkillData()");

    const wchar_t fileName[] = L"..\\CachedScript\\GMskilldata.txt";
    FILE* file = ::_wfopen(fileName, L"rb");
    if (file == NULL)
    {
        ::MessageBoxW(0, L"Add skill data fail. Cannot find file", L"Add skill data fail", MB_OK);
        g_winlog.Add(LOG_ERROR, L"Cannot find [%s]", fileName);
        unguard();
        return;
    }

    wchar_t isMagicSkillBuffer[16];
    ::memset(isMagicSkillBuffer, 0, sizeof(isMagicSkillBuffer));

    wchar_t activateType[16];
    ::memset(activateType, 0, sizeof(activateType));

    wchar_t levelBuffer[16];
    ::memset(levelBuffer, 0, sizeof(levelBuffer));

    wchar_t idBuffer[16];
    ::memset(idBuffer, 0, sizeof(idBuffer));

    wchar_t skillDescription[512];
    ::memset(skillDescription, 0, sizeof(skillDescription));

    wchar_t name[512];
    ::memset(name, 0, sizeof(name));

    DBConn sql;
    sql.Execute(L"EXEC lin_FlushSkillName");
    ::fgetwc(file);

    while (true)
    {
        ::memset(isMagicSkillBuffer, 0, sizeof(isMagicSkillBuffer));
        ::memset(activateType, 0, sizeof(activateType));
        ::memset(levelBuffer, 0, sizeof(levelBuffer));
        ::memset(idBuffer, 0, sizeof(idBuffer));
        ::memset(skillDescription, 0, sizeof(skillDescription));
        ::memset(name, 0, sizeof(name));

        int idSize = 0;
        wchar_t* idBufferIterator = idBuffer;
        wchar_t symbol = WEOF;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n')
            {
                break;
            }
            if (symbol == WEOF)
            {
                ::fclose(file);
                unguard();
                return;
            }

            if (symbol != '[' && symbol != ']')
            {
                *idBufferIterator = symbol;
                ++idBufferIterator;
            }
            ++idSize;
        } while (idSize < 5);
        if (symbol == WEOF)
        {
            break;
        }

        int levelSize = 0;
        int levelIt = 0;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == WEOF)
            {
                break;
            }
            if (symbol != '[' && symbol != ']')
            {
                levelBuffer[levelIt++] = symbol;
            }
            ++levelSize;
        } while (levelSize < 5);
        if (!levelIt)
        {
            levelBuffer[0] = '0';
        }
        if (symbol == WEOF)
        {
            break;
        }

        int nameSize = 0;
        int nameI = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != WEOF && symbol != '\t')
            {
                if (symbol != '[' && symbol != ']')
                {
                    if (symbol == '\'')
                    {
                        name[nameI++] = '\'';
                        name[nameI] = '\'';
                    }
                    else
                    {
                        name[nameI] = symbol;
                    }
                    ++nameI;
                }
                if (++nameSize < 256)
                {
                    continue;
                }
            }
            goto LABEL_37;
        }
        ::fgetwc(file);
    LABEL_37:
        if (!nameI)
        {
            name[0] = ' ';
        }

        int skillDescriptionSize = 0;
        int skillDescriptionI = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != WEOF && symbol != '\t')
            {
                if (symbol != '[' && symbol != ']')
                {
                    if (symbol == '\'')
                    {
                        skillDescription[skillDescriptionI++] = '\'';
                        skillDescription[skillDescriptionI] = '\'';
                    }
                    else
                    {
                        skillDescription[skillDescriptionI] = symbol;
                    }
                    ++skillDescriptionI;
                }
                if (++skillDescriptionSize < 256)
                {
                    continue;
                }
            }
            goto LABEL_52;
        }
        ::fgetwc(file);
    LABEL_52:
        if (!skillDescriptionI)
        {
            skillDescription[0] = ' ';
        }

        int isMagicSkillSize = 0;
        int isMagicSkillI = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != WEOF && symbol != '\t')
            {
                if (symbol != '[' && symbol != ']')
                {
                    if (symbol == '\'')
                    {
                        isMagicSkillBuffer[isMagicSkillI++] = '\'';
                        isMagicSkillBuffer[isMagicSkillI] = '\'';
                    }
                    else
                    {
                        isMagicSkillBuffer[isMagicSkillI] = symbol;
                    }
                    ++isMagicSkillI;
                }
                if (++isMagicSkillSize < 3)
                {
                    continue;
                }
            }
            goto LABEL_67;
        }
        ::fgetwc(file);
    LABEL_67:
        if (!isMagicSkillI)
        {
            isMagicSkillBuffer[0] = '0';
        }

        int activateTypeSize = 0;
        int activateTypeI = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != WEOF)
            {
                if (symbol != '[' && symbol != ']')
                {
                    if (symbol == '\'')
                    {
                        activateType[activateTypeI++] = '\'';
                        activateType[activateTypeI] = '\'';
                    }
                    else
                    {
                        activateType[activateTypeI] = symbol;
                    }
                    ++activateTypeI;
                }
                if (++activateTypeSize < 5)
                {
                    continue;
                }
            }
            goto LABEL_81;
        }
        symbol = ::fgetwc(file);
    LABEL_81:
        if (!activateTypeI)
        {
            activateType[0] = 'A';
        }
        if (symbol == WEOF)
        {
            break;
        }

        int isMagicSkill = _wtol(isMagicSkillBuffer);
        int level = _wtol(levelBuffer);
        int id = _wtol(idBuffer);
        sql.Execute(L"EXEC lin_InsertSkillName %d, %d, N'%s', N'%s', %d, N'%s'", id, level, name, skillDescription, isMagicSkill, activateType);

        g_winlog.Add(LOG_INF, L"%d, %d, %s, %s, %d, %s", id, level, name, skillDescription, isMagicSkill, activateType);
    }

    ::fclose(file);
    unguard();
}

// L2CacheD 0x00404D80
void CAddData::AddQuestData()
{
    guard(L"void CAddData::AddQuestData()");

    const wchar_t fileName[] = L"..\\CachedScript\\questcomp.txt";
    FILE* file = ::_wfopen(fileName, L"rb");
    if (file == NULL)
    {
        ::MessageBoxW(NULL, L"Add quest data fail. Cannot find file", L"Add quest data fail", MB_OK);
        g_winlog.Add(LOG_ERROR, L"Cannot find [%s]", fileName);
        unguard();
        return;
    }

    wchar_t idBuffer[16];
    ::memset(idBuffer, 0, sizeof(idBuffer));

    wchar_t data[512];
    ::memset(data, 0, sizeof(data));

    wchar_t name[512];
    ::memset(name, 0, sizeof(name));

    DBConn sql;
    sql.Execute(L"EXEC lin_FlushQuestName");

    ::fgetwc(file);

    while (true)
    {
        ::memset(idBuffer, 0, sizeof(idBuffer));
        ::memset(data, 0, sizeof(data));
        ::memset(name, 0, sizeof(name));

        int size = 0;
        wchar_t* tokenIterator = idBuffer;
        wchar_t symbol = WEOF;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n')
            {
                break;
            }
            if (symbol == WEOF)
            {
                ::fclose(file);
                unguard();
                return;
            }

            if (symbol != '[' && symbol != ']')
            {
                *tokenIterator = symbol;
                ++tokenIterator;
            }
            ++size;
        } while (size < 7);

        if (symbol == WEOF)
        {
            break;
        }

        size = 0;
        int i = 0;
        do
        {
            symbol = ::fgetwc(file);
            if (symbol == '\t' || symbol == '\n' || symbol == WEOF)
            {
                break;
            }
            if (symbol != '[' && symbol != ']')
            {
                if (symbol == '\'')
                {
                    name[i++] = '\'';
                    name[i] = '\'';
                }
                else
                {
                    name[i] = symbol;
                }
                ++i;
            }
            ++size;
        } while (size < 256);
        if (!i)
        {
            name[0] = ' ';
        }
        if (symbol == WEOF)
        {
            break;
        }

        size = 0;
        int dataIt = 0;
        while (true)
        {
            symbol = ::fgetwc(file);
            if (symbol == '\r')
            {
                break;
            }
            if (symbol != WEOF)
            {
                // additional check for multiple ;;; - they should be treaten as single ;
                // if (symbol != '[' && symbol != ']' && symbol != '{' && symbol != '}' && (dataIt <= 0 || *(&v15 + dataIt) != ';' || symbol != ';'))
                if (symbol != '[' && symbol != ']' && symbol != '{' && symbol != '}' && (dataIt <= 0 || data[dataIt - 1] != ';' || symbol != ';'))
                {
                    if (symbol == '\'')
                    {
                        data[dataIt++] = '\'';
                        data[dataIt] = '\'';
                    }
                    else
                    {
                        data[dataIt] = symbol;
                    }
                    ++dataIt;
                }
                if (++size < 511)
                {
                    continue;
                }
            }
            goto LABEL_44;
        }
        symbol = ::fgetwc(file);
    LABEL_44:

        if (!dataIt)
        {
            data[0] = ' ';
        }
        if (symbol == WEOF)
        {
            break;
        }

        int id = _wtol(idBuffer);
        sql.Execute(L"EXEC lin_InsertQuestName %d, N'%s', N'%s'", id, name, data);

        g_winlog.Add(LOG_INF, L"%d, %s, %s", id, name, data);
    }

    ::fclose(file);
    unguard();
}
