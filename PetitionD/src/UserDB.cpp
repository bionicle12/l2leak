// UserDB.cpp: implementation of the UserDB class.
//
//////////////////////////////////////////////////////////////////////

#include "petitiond/stdafx.h"
#include "petitiond/WorldEmu.h"
#include "petitiond/UserDB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UserDB::UserDB()
{

}

UserDB::~UserDB()
{

}

int UserDB::Load( LPCSTR filename )
{
    FILE* fp = fopen( filename, "r" );
    if( fp == NULL ) return 0;

    char linebuf[1024];
    USER_INFO user;
    while( fgets( linebuf, 1024, fp ) ) {
        int count = sscanf( linebuf, "%d %s %d %s %d", &user.uid, &user.account, &user.cid, &user.char_name, &user.gm_grade );
        if( count == 5 ) {
            m_UserMap[user.cid] = user;
        }
    }

    return m_UserMap.size();
}

int UserDB::GetCharCountOf( int uid )
{
    // std::count_if(
    int count = 0;
    UserMap::iterator pos;
    ITERATE_CONTAINER( m_UserMap, pos ) {
        if( pos->second.uid == uid ) count++;
    }

    return count;
}

int UserDB::GetNthCharIdOf( int uid, int index )
{
    int count = 0;
    UserMap::iterator pos;
    ITERATE_CONTAINER( m_UserMap, pos ) {
        if( pos->second.uid == uid ) {
            if( count == index ) {
                return pos->second.cid;
            }
            count++;
        }
    }

    return 0;
}

LPCSTR UserDB::GetNthCharNameOf( int uid, int index )
{
    int count = 0;
    UserMap::iterator pos;
    ITERATE_CONTAINER( m_UserMap, pos ) {
        if( pos->second.uid == uid ) {
            if( count == index ) {
                return pos->second.char_name;
            }
            count++;
        }
    }

    return NULL;
}

int UserDB::GetCharIntIdByName( LPCSTR name )
{
    UserMap::iterator pos;
    ITERATE_CONTAINER(m_UserMap,pos) {
        if( !strcmp( pos->second.char_name, name ) ) {
            return pos->second.cid;
        }
    }
    return 0;
}

LPCSTR UserDB::GetCharNameByIntId( int cid )
{
    return m_UserMap[cid].char_name;
}
