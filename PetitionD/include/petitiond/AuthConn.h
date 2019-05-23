#ifndef _SOOMIN_HEADER_AUTH_CONN
#define _SOOMIN_HEADER_AUTH_CONN

#include "petitiond/TlvSocket.h"

#define AUTH_SERVER_PORT      2104

enum {
    SQ_ABOUT_TO_PLAY,
    SQ_KICK_ACCOUNT,
    SQ_MAX
};

enum {
    AS_PLAY_OK,
    AS_PLAY_FAIL,
    AS_PLAY_GAME,
    AS_QUIT_GAME,
    AS_MAX
};

class AuthConn : public TlvSocket
{
public:
    AuthConn( int timeout = 0 );

    void Unpack_SQ_ABOUT_TO_PLAY( int* uid );
    void Unpack_SQ_KICK_ACCOUNT( int* uid, BYTE* reason );

    void Send_AS_PLAY_OK( int uid, int one_time_pwd );
    void Send_AS_PLAY_GAME( int uid );
    void Send_AS_QUIT_GAME( int uid, WORD reason, int usetime );
        //reason 0: S_NORMAL_LOGOUT : Á¤»ó Á¾·á
        //       1: S_LINK_DEAD     : ¿¬°á ²÷±è
};

#endif
