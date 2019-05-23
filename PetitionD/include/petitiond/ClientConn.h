#ifndef _SOOMIN_HEADER_CLINET_CONN
#define _SOOMIN_HEADER_CLINET_CONN

#include "petitiond/stdafx.h"
#include "petitiond/PetitionConn.h"

#include "petitiond/tlvsocket.h"

#define CLIENT_LISTEN_PORT      2111
#define CLIENT_LISTEN_BACKLOG     10

enum {
    CW_REQUEST_CHAR_LIST,
    WC_USER_CHAR_LIST,
    CW_JOIN_GAME,
    CW_PETITION_COMMAND,
    CW_QUIT_GAME
};

class ClientConn : public TlvSocket
{
public:
    ClientConn( int timeout = 0 );

    void Send_USER_CHAR_LIST_1( BYTE num_of_chars );
    void Send_USER_CHAR_LIST_2( int char_int_id, LPCSTR char_name );
    void Send_USER_CHAR_LIST_3();

    void Unpack_PETITION_COMMAND( char** petition_cmd );
    void Unpack_REQUEST_CHAR_LIST( int* uid, int* one_time_pwd );
    void Unpack_JOIN_GAME( int* char_int_id );


public: // session infomation
    int uid;
    int begintime;
    int char_int_id;
    CWinThread* thread;
};

#endif
