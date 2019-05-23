#include "petitiond/ClientConn.h"

ClientConn::ClientConn( int timeout ) : TlvSocket( timeout ) {
    uid = 0;
    begintime = 0;
}

void ClientConn::Send_USER_CHAR_LIST_1( BYTE num_of_chars )
{
    PackBegin( WC_USER_CHAR_LIST );
    PackByte( num_of_chars );
}

void ClientConn::Send_USER_CHAR_LIST_2( int char_int_id, LPCSTR char_name )
{
    PackLong( char_int_id );
    PackString( char_name, CHAR_NAME_SIZE );
}

void ClientConn::Send_USER_CHAR_LIST_3()
{
    SendPacked();
}

void ClientConn::Unpack_REQUEST_CHAR_LIST( int* uid, int* one_time_pwd )
{
    UnpackLong( (UINT*)uid );
    UnpackLong( (UINT*)one_time_pwd );
}

void ClientConn::Unpack_JOIN_GAME( int* char_int_id )
{
    UnpackLong( (UINT*)char_int_id );
}

void ClientConn::Unpack_PETITION_COMMAND( char** petition_cmd )
{
    WORD len_of_message;
    UnpackWord( &len_of_message );
    *petition_cmd = new char[len_of_message+1];
    UnpackString( *petition_cmd, len_of_message );
}
