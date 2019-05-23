#pragma once

#include <windows.h>
#include <Sqltypes.h>

struct SqlConnection;

struct SqlConnection
{
    bool free;
    SQLHANDLE dbcSqlHandler;
    SQLHANDLE stmtSqlHandler;
    SqlConnection* prevConnection;
};
