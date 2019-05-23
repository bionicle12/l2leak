#include "petitiond/stdafx.h"
#include "petitiond/Log.h"

#define NUM_OF_ERROR_CODE    44
const char* g_error_string[NUM_OF_ERROR_CODE] = {
    "success",
    "non-existing account",
    "incorrect password",
    "should change password",
    "should change password & quiz",
    "duplicate login(GM account)",
    "blocked account",
    "not GM account",
    "unexpected(non or out of range) game_code",
    "unmatched tail",
    "world server down",
    "non-existing character",
    "banned or blocked character",
    "unexpected world_id",
    "GM already leaved the world",
    "unexpected petition_grade",
    "unexpected petition_id",
    "already checked out this petition",
    "check in first",
    "no right to access",
    "check out, first",
    "SMTP(mail server) unavailable",
    "unexpected gm_grade",
    "not marked for deletion",
    "world already connected(duplication)",
    "obsolete build_number",
    "character already submitted petition",
    "the action is forbidden in this state of petition",
    "database fail",
    "network fail",
    "internal server fail(cases except database and network)",
    "no world server up in this game",
    "login first",
    "enter the world first",
    "GM already entered the world",
    "session id unmatched",
    "unexpected petition category",
    "unexpected messaging operation code",
    "GM already started chatting",
    "GM already ended chatting",
    "should change SSN",
    "expired account",
    "too many petitions in this world",
    "the character has no ongoing petition"
};

Log* Log::m_instance = NULL;
CString Log::m_filename;

Log* Log::GetInstance()
{
    if( m_instance == NULL ) {
        m_instance = new Log();
    }

    return m_instance;
}

Log::Log()
{
    m_pEdit = NULL;
    InitializeCriticalSection( &m_csLock );
}

Log::~Log()
{
    DeleteCriticalSection( &m_csLock );
}

void Log::Close()
{
    EnterCriticalSection( &m_csLock );

    DetachEditCtrl();

    /*
    if( m_instance != NULL ) {
        delete m_instance;
        m_instance = NULL;
    }*/

    LeaveCriticalSection( &m_csLock );
}

void Log::AttachEditCtrl( CEdit* pControl )
{
    m_pEdit = pControl;
}

void Log::DetachEditCtrl()
{
    m_pEdit = NULL;
}

void Log::Add( LPCSTR str )
{
    EnterCriticalSection( &m_csLock );

    if( m_pEdit ) {
        CString line = str;
        line.Replace( "\n", "\r\n" );

        CString log;
        m_pEdit->GetWindowText( log );
        log += line;
        m_pEdit->SetWindowText( log );
        m_pEdit->LineScroll( m_pEdit->GetLineCount() );
    }

    LeaveCriticalSection( &m_csLock );
}

void Log::Write(char* fmt, ...)
{
    char text[2048];
    va_list args;

    va_start( args, fmt );
    vsprintf( text, fmt, args );
    va_end( args );

    Add( text );
}

void Log::WriteLn(char* fmt, ...)
{
    Add( "\n" );

    char text[2048];
    va_list args;

    va_start( args, fmt );
    vsprintf( text, fmt, args );
    va_end( args );

    Add( text );
}

void Log::WriteError( BYTE error_code )
{
    char text[2048];

    if( error_code < NUM_OF_ERROR_CODE )
        sprintf( text, "ERROR %d : %s", error_code, g_error_string[error_code] );
    else
        sprintf( text, "ERROR %d : unknown error", error_code );

    WriteLn( text );
}
