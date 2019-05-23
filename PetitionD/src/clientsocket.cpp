#include "petitiond/clientsocket.h"

#ifdef SOCKET_DEBUG
void socket_debug(char* fmt, ...)
{
    char text[2048];

    FILE* fp = fopen( "socket_debug.log", "a" );

    if( fp ) {
        if( 0 != fmt ) {
            va_list args;

            va_start( args, fmt );
            vsprintf( text, fmt, args );
            va_end( args );
        }
        fwrite( text, 1, strlen(text), trace_handle );
        fclose( trace_handle );
    }
}
#else
void socket_debug(char* fmt, ...) {}
#endif

ClientSocket::ClientSocket( int timeout )
{
    m_hSocket = INVALID_SOCKET;
    m_nTimeout = timeout;
}

BOOL ClientSocket::Connect( const char* szTarget, USHORT nPort )
{
    // 주소 DNS 룩업
    socket_debug( "DNS look up (%s:%d)...", szTarget, nPort );
    HOSTENT* host = gethostbyname( szTarget );
    if( host == NULL ) {
        socket_debug( "Fail\n" );
        return FALSE;
    }
    socket_debug( "Ok\n" );

    // 주소 설정
    memset( &m_addrTarget, 0, sizeof(SOCKADDR_IN) );
    m_addrTarget.sin_family = AF_INET;
    m_addrTarget.sin_port = htons(nPort);
    m_addrTarget.sin_addr = *(struct in_addr *)host->h_addr;

    // 소켓 생성
    socket_debug( "Create socket..." );
    m_hSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if( m_hSocket == INVALID_SOCKET ) {
        socket_debug( "Fail\n" );
        return FALSE;
    }
    socket_debug( "Ok\n" );

    // 타임아웃 설정
    int ret;
    if( m_nTimeout > 0 ) {
        socket_debug( "Set socket timeout option..." );
        int timeout = m_nTimeout;
        ret = setsockopt( m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout) );
        if( ret != 0 ) socket_debug( "recv fail " );
        ret = setsockopt( m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout) );
        if( ret != 0 ) socket_debug( "send fail " );
        socket_debug( "ok" );
    }

    // 연결
    socket_debug( "Try to connect...\n" );
    ret = connect( m_hSocket, (struct sockaddr *)&m_addrTarget, sizeof(struct sockaddr));
    if( ret == SOCKET_ERROR ) {
        int errno2 = WSAGetLastError();
        socket_debug( "Fail(%d)\n", errno2 );
        Close();
        return FALSE;
    }
    socket_debug( "Ok\n" );

    return TRUE;
}

void ClientSocket::SetSocket( SOCKET s )
{
    m_hSocket = s;
}

void ClientSocket::Close()
{
    socket_debug( "Close socket\n" );
    if( m_hSocket != INVALID_SOCKET ) {
        closesocket( m_hSocket );
        m_hSocket = INVALID_SOCKET;
    }
}

int ClientSocket::Recv( void* buf, int len )
{
    int count = recv( m_hSocket, (char*)buf, len, 0 );
    if( count <= 0 ) throw SocketExceptionRecv();
    return count;
}

int ClientSocket::Send( void* buf, int len )
{
    int count = send( m_hSocket, (char*)buf, len, 0 );
    if( count <= 0 ) throw SocketExceptionSend();
    return count;
}

void ClientSocket::RecvFull( void* buf, int total )
{
    int left = total;

    while( left > 0 )
        left -= Recv( (char*)buf+(total-left), left );
}

void ClientSocket::SendFull( void* buf, int total )
{
    int left = total;

    while( left > 0 )
        left -= Send( (char*)buf+(total-left), left );
}
