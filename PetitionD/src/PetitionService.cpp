// PetitionService.cpp: implementation of the PetitionService class.
//
//////////////////////////////////////////////////////////////////////

#include "petitiond/stdafx.h"
#include "petitiond/WorldEmu.h"
#include "petitiond/WorldEmuDlg.h"
#include "petitiond/PetitionService.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PetitionService::PetitionService( CWorldEmuDlg* pDlg )
{
    m_pDlg = pDlg;
    m_pLog = Log::GetInstance();
}

PetitionService::~PetitionService()
{

}

BOOL PetitionService::Connect( LPCSTR addr, WORD port, BYTE game_code, BYTE world_id, LPCSTR world_name )
{
    m_pLog->WriteLn( "Try to connect petition(%s:%d)...", addr, port );

    if( !m_conn.Connect( addr, port ) ) {
        m_pLog->WriteLn( "Connection fail" );
        return FALSE;
    }

    m_pLog->WriteLn( "Connected" );

    try {
        // Recv : SERVER_VER
        m_pLog->WriteLn( "Recv : SERVER_VER" );
        m_conn.RecvPacked( SERVER_VER );
        UINT build_number;
        m_conn.Unpack_SERVER_VER( &build_number );
        m_pLog->Write( "(%d)", build_number );

        // Send : CONNECT_WORLD
        m_pLog->WriteLn( "Send : CONNECT_WORLD" );
        m_conn.Send_CONNECT_WORLD( WORLD_SERVER_BUILD_NUMBER, game_code, world_id, world_name, 1 ); // support char_int_id

        // Recv : ACCEPT_WORLD
        m_pLog->WriteLn( "Recv : ACCEPT_WORLD" );
        BYTE error;
        m_conn.RecvPacked( ACCEPT_WORLD );
        m_conn.Unpack_ACCEPT_WORLD( &error );
        if( error ) m_pLog->WriteError( error );

        // Send : W_REQUEST_CATEGORY
        m_pLog->WriteLn( "Send : W_REQUEST_CATEGORY" );
        m_conn.Send_W_REQUEST_CATEGORY();

        // other notification packets may arrive faster than W_CATEGORY_LIST ( response of W_REQUEST_CATEGORY )
        // so W_CATEGORY_LIST processing routine must be in Service loop :(

    } catch( SocketException ) {
        m_pLog->WriteLn( "SocketClose or Exception" );
        return FALSE;
    }

    return TRUE;
}

UINT PetitionServiceProc( void* pParam ) {
    ((PetitionService*)pParam)->Service();
    return 0;
}

void PetitionService::StartService( UINT end_msg )
{
    m_end_msg = end_msg;
    m_ServicePetitionServerThread = AfxBeginThread( PetitionServiceProc, (void*)this );
}

void PetitionService::StopService()
{
    try {
        m_conn.Send_NOTIFY_WORLD_DISCONNECTION( 1 );
    } catch( SocketException ) {
        m_pLog->WriteLn( "SocketClose or Exception" );
    }

    // close socket, terminate thread, free memory
    m_conn.Close();
    WaitForSingleObject( m_ServicePetitionServerThread, INFINITE );
    m_ServicePetitionServerThread = NULL;
}


void PetitionService::Service()
{
    int type;
    try {
        while( TRUE ) {
            type = m_conn.RecvPacked();
            switch( type ) {

            case W_CATEGORY_LIST:
                {
                    m_pLog->WriteLn( "Recv : W_CATEGORY_LIST" );
                    BYTE num_of_category, category_id;
                    m_conn.Unpack_W_CATEGORY_LIST_1( &num_of_category );
                    for( int i = 0; i < num_of_category; i++ ) {
                        char* category_name;
                        m_conn.Unpack_W_CATEGORY_LIST_2( &category_id, &category_name );
                        m_pLog->WriteLn( "%d : %s", category_id, category_name );
                        delete [] category_name;
                    }
                }
                break;

            case W_NOTIFY_CHECK_OUT:
                {
                    m_pLog->WriteLn( "Recv : W_NOTIFY_CHECK_OUT" );
                    UINT petition_id;
                    int gm_int_id, char_int_id;
                    char gm_id[CHAR_NAME_SIZE+1], char_id[CHAR_NAME_SIZE+1];
                    m_conn.Unpack_W_NOTIFY_CHECK_OUT( &petition_id, gm_id, char_id, &gm_int_id, &char_int_id );
                    m_pLog->Write( "(%d, %s, %s, %d, %d)", petition_id, gm_id, char_id, gm_int_id, char_int_id );

                    m_pDlg->UpdatePetitionToCheckOut( petition_id, gm_id, char_id );
                }
                break;

            case W_NOTIFY_FINISH:
                {
                    m_pLog->WriteLn( "Recv : W_NOTIFY_FINISH" );
                    UINT petition_id;
                    m_conn.Unpack_W_NOTIFY_FINISH( &petition_id );
                    m_pLog->Write( "(%d)", petition_id );

                    m_pDlg->UpdatePetitionState( petition_id, "FINISH" );
                }
                break;

            case LEAVE_MESSAGE:
                {
                    m_pLog->WriteLn( "Recv : LEAVE_MESSAGE" );
                    UINT petition_id;
                    char* message;
                    m_conn.Unpack_LEAVE_MESSAGE( &petition_id, &message );
                    m_pLog->Write( "(%d, %s)", petition_id, message );
                    delete [] message;

                    m_pLog->WriteLn( "Send : ACCEPT_MESSAGE" );
                    BYTE error = 0;
                    m_conn.Send_ACCEPT_MESSAGE( petition_id, error );
                }
                break;

            case SUBMIT_PETITION_OK:
                {
                    m_pLog->WriteLn( "Recv : SUBMIT_PETITION_OK" );
                    UINT temp_id, petition_id;
                    char petition_seq[PETITION_SEQ_SIZE];
                    m_conn.Unpack_SUBMIT_PETITION_OK( &temp_id, &petition_id, petition_seq );
                    m_pLog->Write( "(%d, %d, %s)", temp_id, petition_id, petition_seq );

                    m_pDlg->UpdateTempPetition( temp_id, petition_id );
                }
                break;

            case SUBMIT_PETITION_FAIL:
                {
                    m_pLog->WriteLn( "Recv : SUBMIT_PETITION_FAIL" );
                    UINT temp_id;
                    BYTE error;
                    m_conn.Unpack_SUBMIT_PETITION_FAIL( &temp_id, &error );
                    m_pLog->Write( "(%d, %d)", temp_id, error );

                    if( error ) m_pLog->WriteError( error );

                    m_pDlg->UpdateTempPetition( temp_id, 0 );
                }
                break;

            case ACCEPT_CHAT_START:
                {
                    m_pLog->WriteLn( "Recv : ACCEPT_CHAT_START" );
                    UINT petition_id;
                    BYTE error;
                    m_conn.Unpack_ACCEPT_CHAT_START( &petition_id, &error );
                    m_pLog->Write( "(%d, %d)", petition_id, error );

                    // 대화 시작 후 월드 서버가 죽었다 살아나고
                    // GM이 다시 대화 시작을 요청한 경우 eAlreadyChatStarted
                    if( error && error != eAlreadyChatStarted ) {
                        m_pLog->WriteError( error );
                        break;
                    }

                    m_pDlg->UpdatePetitionState( petition_id, "CHAT_START_OK" );
                }
                break;

            case ACCEPT_CHAT_END:
                {
                    m_pLog->WriteLn( "Recv : ACCEPT_CHAT_END" );
                    UINT petition_id;
                    BYTE error;
                    m_conn.Unpack_ACCEPT_CHAT_END( &petition_id, &error );
                    m_pLog->Write( "(%d, %d)", petition_id, error );

                    if( error ) {
                        m_pLog->WriteError( error );
                        break;
                    }

                    m_pDlg->UpdatePetitionState( petition_id, "CHAT_END_OK" );
                }
                break;

            case REQUEST_CHAR_LIST:
                {
                    m_pLog->WriteLn( "Recv : REQUEST_CHAR_LIST" );
                    char account[ACCOUNT_SIZE+1];
                    m_conn.Unpack_REQUEST_CHAR_LIST( account );
                    m_pLog->Write( "(%s)", account );

                    CString str = account;

                    m_conn.Send_CHAR_LIST1( account, 4 );
                    m_conn.Send_CHAR_LIST2( str + "_char1", 0, 3 );
                    m_conn.Send_CHAR_LIST2( str + "_char2", 0, 2 );
                    m_conn.Send_CHAR_LIST2( str + "_char3", 0, 1 );
                    m_conn.Send_CHAR_LIST2( str + "_char4", 0, 0 );
                    m_conn.Send_CHAR_LIST3();
                }
                break;

            case REQUEST_CONNECTED_CHARS:
                {
                    m_pLog->WriteLn( "Recv : REQUEST_CONNECTED_CHARS" );
                    BYTE num_of_chars;
                    m_conn.Unpack_REQUEST_CONNECTED_CHARS_1( &num_of_chars );
                    m_pLog->Write( "(%d)", num_of_chars );

                    int char_int_id;
                    std::vector<int> connected_user;
                    for( int i = 0; i < num_of_chars; i++ ) {
                        m_conn.Unpack_REQUEST_CONNECTED_CHARS_2( &char_int_id );
                        m_pLog->WriteLn( "(%d)", char_int_id );

                        if( m_pDlg->IsCharOnline( char_int_id ) ) {
                            connected_user.push_back( char_int_id );
                            m_pLog->Write( "->Online" );
                        }
                    }

                    m_pLog->WriteLn( "Send : CONNECTED_CHARS(%d)", connected_user.size() );
                    m_conn.Send_CONNECTED_CHARS( connected_user.size(), &connected_user[0] );
                }
                break;

            case CANCEL_PETITION_OK:
                {
                    m_pLog->WriteLn( "Recv : CANCEL_PETITION_OK" );
                    int char_int_id;
                    UINT petition_id;
                    char char_id[CHAR_NAME_SIZE+1];
                    char petition_seq[PETITION_SEQ_SIZE];
                    m_conn.Unpack_CANCEL_PETITION_OK( char_id, &char_int_id, &petition_id, petition_seq );
                    m_pLog->Write( "(%s, %d, %d, %s)", char_id, char_int_id, petition_id, petition_seq );

                    m_pDlg->UpdatePetitionState( petition_id, "CANCEL_OK" );
                }
                break;

            case CANCEL_PETITION_FAIL:
                {
                    m_pLog->WriteLn( "Recv : CANCEL_PETITION_FAIL" );
                    int char_int_id;
                    char char_id[CHAR_NAME_SIZE+1];
                    BYTE error;
                    m_conn.Unpack_CANCEL_PETITION_FAIL( char_id, &char_int_id, &error );
                    m_pLog->Write( "(%s, %d, %d)", char_id, char_int_id, error );

                    m_pLog->WriteError( error );
                }
                break;

            default:
                throw SocketExceptionIllegalTypePacket();
            }
        }
    } catch( SocketException ) {
        m_pLog->WriteLn( "SocketClose or Exception" );
    }

    m_conn.Close();

    m_pDlg->PostMessage( m_end_msg );
}
