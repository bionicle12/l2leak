// UserDB.h: interface for the UserDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERDB_H__F00E4CA0_E47E_483D_A4D9_6D2FC3321505__INCLUDED_)
#define AFX_USERDB_H__F00E4CA0_E47E_483D_A4D9_6D2FC3321505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "petitiond/PetitionConn.h"
#include <map>
#include <algorithm>

class UserDB
{
private:
    typedef struct {
        int uid;
        char account[ACCOUNT_SIZE+1];
        int cid;
        char char_name[CHAR_NAME_SIZE+1];
        BYTE gm_grade;
    } USER_INFO;

    typedef std::map<int,USER_INFO> UserMap;

    UserMap m_UserMap;

public:
    UserDB();
    virtual ~UserDB();

    int Load( LPCSTR filename );
    int GetCharCountOf( int uid );
    int GetNthCharIdOf( int uid, int index );
    LPCSTR GetNthCharNameOf( int uid, int index );
    int GetCharIntIdByName( LPCSTR name );
    LPCSTR GetCharNameByIntId( int cid );
};

#endif // !defined(AFX_USERDB_H__F00E4CA0_E47E_483D_A4D9_6D2FC3321505__INCLUDED_)
