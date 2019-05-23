#pragma once

#include <windows.h>
#include <Sqltypes.h>

struct SqlConnection;

struct SqlConnection
{
    SQLHANDLE dbcSqlHandler;
    SQLHANDLE stmtSqlHandler;
    SqlConnection* nextConnection;
};
