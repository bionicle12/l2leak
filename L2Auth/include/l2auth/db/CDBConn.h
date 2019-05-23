#pragma once

#include <windows.h>
#include <Sqltypes.h>

#include <l2core/utils/cstdint_support.h>

class DBEnv;
struct SqlConnection;

class CDBConn
{
public:
    explicit CDBConn(DBEnv* dbEnv);         // L2AuthD 0x00413E9E
    ~CDBConn();                             // L2AuthD 0x00413F5F
    bool Execute(const char* format, ...);  // L2AuthD 0x00414123
    SQLRETURN execRaw(const char* sqlQuery, int textLength);
    bool Fetch(bool* notFound);                                                    // L2AuthD 0x004143F1
    void Error(SQLSMALLINT handlerType, SQLHANDLE handler, const char* sqlQuery);  // L2AuthD 0x00414532
    SQLRETURN bindByte(char* value);                                               // L2AuthD 0x004146F6
    SQLRETURN bindBool(bool* value);                                               // L2AuthD 0x00414739
    SQLRETURN bindStr(SQLPOINTER value, SQLINTEGER length);                        // L2AuthD 0x0041477C
    SQLRETURN bindInt(int32_t* value);                                             // L2AuthD 0x00414804
    SQLRETURN bindUInt(uint32_t* value);                                           // L2AuthD 0x004147C1
    SQLRETURN bindParam(SQLUSMALLINT index, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, size_t cbValueMax, SQLLEN* pcbValue);

    void ResetHtmt();  // L2AuthD 0x00414A7B

    SQLHSTMT getHandler() const
    {
        return m_sqlHandler;
    }

private:
    /*
    static void ErrorExceptInsert(SQLSMALLINT handlerType, SQLHANDLE handler, const char *sqlQuery);
    // L2AuthD 0x00414647
    */

private:
    SQLHSTMT m_sqlHandler;
    int m_currentCollumn;
    int m_currentRow;
    SqlConnection* m_sqlConnection;
    DBEnv* m_dbEnv;
};
