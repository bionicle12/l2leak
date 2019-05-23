#include "petitiond/AuthConn.h"

AuthConn::AuthConn( int timeout ) : TlvSocket( timeout ) {
}

void AuthConn::Unpack_SQ_ABOUT_TO_PLAY( int* uid )
{
    UnpackLong( (UINT*)uid );
}

void AuthConn::Unpack_SQ_KICK_ACCOUNT( int* uid, BYTE* reason )
{
    UnpackLong( (UINT*)uid );
    UnpackByte( reason );
}

void AuthConn::Send_AS_PLAY_OK( int uid, int one_time_pwd )
{
    PackBegin( AS_PLAY_OK );
    PackLong( uid );
    PackLong( one_time_pwd );
    SendPacked();
}

void AuthConn::Send_AS_PLAY_GAME( int uid )
{
    PackBegin( AS_PLAY_GAME );
    PackLong( uid );
    SendPacked();
}

void AuthConn::Send_AS_QUIT_GAME( int uid, WORD reason, int usetime )
{
    PackBegin( AS_QUIT_GAME );
    PackLong( uid );
    PackWord( reason );
    PackLong( usetime );
    SendPacked();
}
