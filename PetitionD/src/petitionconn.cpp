#include "petitiond/petitionconn.h"

PetitionConn::PetitionConn( int timeout ) : TlvSocket( timeout ) {
}

void PetitionConn::Unpack_SERVER_VER( UINT* build_number )
{
    UnpackLong( build_number );
    UnpackBinary( m_one_time_key, 8 );

    m_pet_build_number = *build_number;
}

void PetitionConn::Send_CONNECT_WORLD( UINT build_number, BYTE game_code, BYTE world_id, LPCSTR world_name, BYTE flag )
{
    PackBegin( CONNECT_WORLD );
    PackLong( build_number );
    PackByte( game_code );
    PackByte( world_id );
    PackStringAsUnicode( world_name, WORLD_NAME_SIZE );
    PackByte( flag );

    char tail[16];
    MD5 md5;
    md5.Update((BYTE*)&m_pSendBuffer[HEADER_SIZE], 27);
    md5.Update((BYTE*)m_one_time_key, 8);
    md5.Update((BYTE*)&m_pet_build_number, 4);
    md5.Update((BYTE*)&build_number, 4);
    md5.Final((BYTE*)tail);

    PackBinary( tail, 16 );
    SendPacked();
}

void PetitionConn::Unpack_ACCEPT_WORLD( BYTE* error )
{
    UnpackByte( error );
}

void PetitionConn::Send_W_REQUEST_CATEGORY()
{
    PackBegin( W_REQUEST_CATEGORY );
    SendPacked();
}

void PetitionConn::Unpack_W_CATEGORY_LIST_1( BYTE* num_of_category )
{
    UnpackByte( num_of_category );
}

void PetitionConn::Unpack_W_CATEGORY_LIST_2( BYTE* category_id, char** category_name )
{
    BYTE len_of_category;
    UnpackByte( category_id );
    UnpackByte( &len_of_category );
    *category_name = new char[len_of_category*2+1];
    UnpackStringFromUnicode( *category_name, len_of_category*2 );
}

void PetitionConn::Unpack_W_CATEGORY_LIST_FAIL( BYTE* error )
{
    UnpackByte( error );
}

void PetitionConn::Unpack_W_NOTIFY_CHECK_OUT( UINT* petition_id, char gm_id[CHAR_NAME_SIZE+1], char char_id[CHAR_NAME_SIZE+1], int* gm_int_id, int* char_int_id )
{
    UnpackLong( petition_id );
    UnpackStringFromUnicode( gm_id, CHAR_NAME_SIZE );
    UnpackStringFromUnicode( char_id, CHAR_NAME_SIZE );
    UnpackLong( (UINT*)gm_int_id );
    UnpackLong( (UINT*)char_int_id );
}

void PetitionConn::Unpack_W_NOTIFY_FINISH( UINT* petition_id )
{
    UnpackLong( petition_id );
}

void PetitionConn::Unpack_LEAVE_MESSAGE( UINT* petition_id, char** message )
{
    WORD len_of_message;
    UnpackLong( petition_id );
    UnpackWord( &len_of_message );
    *message = new char[len_of_message*2+1];
    UnpackStringFromUnicode( *message, len_of_message*2 );
}

void PetitionConn::Send_ACCEPT_MESSAGE( UINT petition_id, BYTE error )
{
    PackBegin( ACCEPT_MESSAGE );
    PackLong( petition_id );
    PackByte( error );
    SendPacked();
}

void PetitionConn::Unpack_SUBMIT_PETITION_OK( UINT* temp_id, UINT* petition_id, char petition_seq[PETITION_SEQ_SIZE+1] )
{
    UnpackLong( temp_id );
    UnpackLong( petition_id );
    UnpackString( petition_seq, PETITION_SEQ_SIZE );
}

void PetitionConn::Unpack_SUBMIT_PETITION_FAIL( UINT* temp_id, BYTE* error )
{
    UnpackLong( temp_id );
    UnpackByte( error );
}

void PetitionConn::Unpack_ACCEPT_CHAT_START( UINT* petition_id, BYTE* error )
{
    UnpackLong( petition_id );
    UnpackByte( error );
}

void PetitionConn::Unpack_ACCEPT_CHAT_END( UINT* petition_id, BYTE* error )
{
    UnpackLong( petition_id );
    UnpackByte( error );
}

void PetitionConn::Send_SUBMIT_PETITION( UINT temp_id, BYTE category, LPCSTR account, LPCSTR char_id, int char_int_id, LPCSTR contents )
{
    PackBegin( SUBMIT_PETITION );
    PackLong( temp_id );
    PackByte( category );
    PackString( account, ACCOUNT_SIZE );
    PackStringAsUnicode( char_id, CHAR_NAME_SIZE );
    PackLong( char_int_id );
    PackStringAsUnicodeWithByteLength( contents );
    SendPacked();
}

void PetitionConn::Send_REQUEST_CHAT_START( UINT petition_id )
{
    PackBegin( REQUEST_CHAT_START );
    PackLong( petition_id );
    SendPacked();
}

void PetitionConn::Send_REQUEST_CHAT_END( UINT petition_id )
{
    PackBegin( REQUEST_CHAT_END );
    PackLong( petition_id );
    SendPacked();
}

void PetitionConn::Send_NOTIFY_USER_CHAT( UINT petition_id, LPCSTR contents )
{
    PackBegin( NOTIFY_USER_CHAT );
    PackLong( petition_id );
    PackStringAsUnicodeWithByteLength( contents );
    SendPacked();
}

void PetitionConn::Send_NOTIFY_GM_CHAT( UINT petition_id, LPCSTR contents )
{
    PackBegin( NOTIFY_GM_CHAT );
    PackLong( petition_id );
    PackStringAsUnicodeWithByteLength( contents );
    SendPacked();
}

void PetitionConn::Unpack_REQUEST_CHAR_LIST( char account[ACCOUNT_SIZE+1] )
{
    UnpackString( account, ACCOUNT_SIZE );
}

void PetitionConn::Send_CHAR_LIST1( LPCSTR account, BYTE num_of_char )
{
    PackBegin( CHAR_LIST );
    PackString( account, ACCOUNT_SIZE );
    PackByte( num_of_char );
}

void PetitionConn::Send_CHAR_LIST2( LPCSTR char_id, int char_int_id, BYTE gm_grade )
{
    PackStringAsUnicode( char_id, CHAR_NAME_SIZE );
    PackLong( char_int_id );
    PackByte( gm_grade );
}

void PetitionConn::Send_CHAR_LIST3()
{
    SendPacked();
}

void PetitionConn::Send_CHAR_LIST_FAIL( LPCSTR account, BYTE error )
{
    PackBegin( CHAR_LIST_FAIL );
    PackString( account, ACCOUNT_SIZE );
    PackByte( error );
    SendPacked();
}

void PetitionConn::Send_NOTIFY_WORLD_DISCONNECTION( BYTE error )
{
    PackBegin( NOTIFY_WORLD_DISCONNECTION );
    PackByte( error );
    SendPacked();
}

void PetitionConn::Send_CONNECTED_CHARS( BYTE num_of_chars, int char_int_id[] )
{
    PackBegin( CONNECTED_CHARS );
    PackByte( num_of_chars );
    for( int i = 0; i < num_of_chars; i++ )
        PackLong( char_int_id[i] );
    SendPacked();
}

void PetitionConn::Unpack_REQUEST_CONNECTED_CHARS_1( BYTE* num_of_chars )
{
    UnpackByte( num_of_chars );
}

void PetitionConn::Unpack_REQUEST_CONNECTED_CHARS_2( int* char_int_id )
{
    UnpackLong( (UINT*)char_int_id );
}

void PetitionConn::Send_CANCEL_PETITION( LPCSTR char_id, int char_int_id )
{
    PackBegin( CANCEL_PETITION );
    PackStringAsUnicode( char_id, CHAR_NAME_SIZE );
    PackLong( char_int_id );
    SendPacked();
}

void PetitionConn::Unpack_CANCEL_PETITION_OK( char char_id[CHAR_NAME_SIZE+1], int* char_int_id, UINT* petition_id, char petition_seq[PETITION_SEQ_SIZE+1] )
{
    UnpackStringFromUnicode( char_id, CHAR_NAME_SIZE );
    UnpackLong( (UINT*)char_int_id );
    UnpackLong( (UINT*)petition_id );
    UnpackString( petition_seq, PETITION_SEQ_SIZE );
}

void PetitionConn::Unpack_CANCEL_PETITION_FAIL( char char_id[CHAR_NAME_SIZE+1], int* char_int_id, BYTE* error )
{
    UnpackStringFromUnicode( char_id, CHAR_NAME_SIZE );
    UnpackLong( (UINT*)char_int_id );
    UnpackByte( error );
}
