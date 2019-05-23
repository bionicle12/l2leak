#ifndef _SM_PETITION_CONN
#define _SM_PETITION_CONN

#include "petitiond/tlvsocket.h"
#include "petitiond/md5.h"

#define PETITION_SEQ_SIZE     14
#define WORLD_NAME_SIZE       20
#define CHAR_NAME_SIZE        28
#define TIME_STR_SIZE         14
#define ACCOUNT_SIZE          14

enum {
    SERVER_VER = 101,
    CONNECT_WORLD,
    ACCEPT_WORLD,
    NOTIFY_WORLD_DISCONNECTION,
    W_REQUEST_CATEGORY,
    W_CATEGORY_LIST,
    W_CATEGORY_LIST_FAIL,
    SUBMIT_PETITION,
    SUBMIT_PETITION_OK,
    SUBMIT_PETITION_FAIL,
    W_NOTIFY_CHECK_OUT,
    W_NOTIFY_FINISH,
    REQUEST_CHAT_START,
    ACCEPT_CHAT_START,
    REQUEST_CHAT_END,
    ACCEPT_CHAT_END,
    NOTIFY_USER_CHAT,
    NOTIFY_GM_CHAT,
    LEAVE_MESSAGE,
    ACCEPT_MESSAGE,
    REQUEST_CHAR_LIST,
    CHAR_LIST,
    CHAR_LIST_FAIL,
    REQUEST_CONNECTED_CHARS,
    CONNECTED_CHARS,
    CANCEL_PETITION,
    CANCEL_PETITION_OK,
    CANCEL_PETITION_FAIL
};

class PetitionConn : public TlvSocket
{
public:
    char m_one_time_key[8];
    UINT m_pet_build_number;

    PetitionConn( int timeout = 0 );

    void Send_CONNECT_WORLD( UINT build_number, BYTE game_code, BYTE world_id, LPCSTR world_name, BYTE flag );
    void Send_W_REQUEST_CATEGORY();
    void Send_ACCEPT_MESSAGE( UINT petition_id, BYTE error );
    void Send_SUBMIT_PETITION( UINT temp_id, BYTE category, LPCSTR account, LPCSTR char_id, int char_int_id, LPCSTR contents );
    void Send_REQUEST_CHAT_START( UINT petition_id );
    void Send_REQUEST_CHAT_END( UINT petition_id );
    void Send_NOTIFY_USER_CHAT( UINT petition_id, LPCSTR contents );
    void Send_NOTIFY_GM_CHAT( UINT petition_id, LPCSTR contents );
    void Send_CHAR_LIST1( LPCSTR account, BYTE num_of_char );
    void Send_CHAR_LIST2( LPCSTR char_id, int char_int_id, BYTE gm_grade );
    void Send_CHAR_LIST3();
    void Send_CHAR_LIST_FAIL( LPCSTR account, BYTE error );
    void Send_NOTIFY_WORLD_DISCONNECTION( BYTE error );
    void Send_CONNECTED_CHARS( BYTE num_of_chars, int char_int_id[] );
    void Send_CANCEL_PETITION( LPCSTR char_id, int char_int_id );

    void Unpack_SERVER_VER( UINT* build_number );
    void Unpack_ACCEPT_WORLD( BYTE* error );
    void Unpack_W_CATEGORY_LIST_1( BYTE* num_of_category );
    void Unpack_W_CATEGORY_LIST_2( BYTE* category_id, char** category_name );
    void Unpack_W_CATEGORY_LIST_FAIL( BYTE* error );
    void Unpack_W_NOTIFY_CHECK_OUT( UINT* petition_id, char gm_id[CHAR_NAME_SIZE+1], char char_id[CHAR_NAME_SIZE+1], int* gm_int_id, int* char_int_id );
    void Unpack_W_NOTIFY_FINISH( UINT* petition_id );
    void Unpack_LEAVE_MESSAGE( UINT* petition_id, char** message );
    void Unpack_SUBMIT_PETITION_OK( UINT* temp_id, UINT* petition_id, char petition_seq[PETITION_SEQ_SIZE+1] );
    void Unpack_SUBMIT_PETITION_FAIL( UINT* temp_id, BYTE* error );
    void Unpack_ACCEPT_CHAT_START( UINT* petition_id, BYTE* error );
    void Unpack_ACCEPT_CHAT_END( UINT* petition_id, BYTE* error );
    void Unpack_REQUEST_CHAR_LIST( char account[ACCOUNT_SIZE+1] );
    void Unpack_REQUEST_CONNECTED_CHARS_1( BYTE* num_of_chars );
    void Unpack_REQUEST_CONNECTED_CHARS_2( int* char_int_id );
    void Unpack_CANCEL_PETITION_OK( char char_id[CHAR_NAME_SIZE+1], int* char_int_id, UINT* petition_id, char petition_seq[PETITION_SEQ_SIZE+1] );
    void Unpack_CANCEL_PETITION_FAIL( char char_id[CHAR_NAME_SIZE+1], int* char_int_id, BYTE* error );
};

#endif
