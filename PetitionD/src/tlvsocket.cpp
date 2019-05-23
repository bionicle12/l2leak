#include "petitiond/tlvsocket.h"

TlvSocket::TlvSocket( int timeout ) : ClientSocket( timeout ) {
    m_nSendBufferPos = 0;
    m_nRecvBufferPos = 0;
    InitializeCriticalSection( &m_csSendLock );
}

TlvSocket::~TlvSocket() {
    DeleteCriticalSection( &m_csSendLock );
}

void TlvSocket::SendPacked() {
    socket_debug( "NetSendPacked %d bytes\n", HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer) );

    SendFull( m_pSendBuffer, HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer) );
    m_nSendBufferPos = 0;

    LeaveCriticalSection( &m_csSendLock );

    socket_debug( "NetSendPacked complete\n" );
}

int TlvSocket::RecvPacked() {
    if( m_hSocket == INVALID_SOCKET ) return -1;

    m_nRecvBufferPos = 0;
    RecvFull( m_pRecvBuffer, HEADER_SIZE );

    if( HEADER_SIZE + PAYLOAD_SIZE( m_pRecvBuffer ) > RECV_BUFFER_SIZE )
        throw SocketExceptionRecvTooBigPacket();

    RecvFull( m_pRecvBuffer+HEADER_SIZE, PAYLOAD_SIZE( m_pRecvBuffer ) );

    // 데이터를 읽을 위치에 포지션을 지정
    m_nRecvBufferPos = HEADER_SIZE;

    return PACKET_TYPE(m_pRecvBuffer);
}

void TlvSocket::RecvPacked( BYTE nPacketType )
{
    BYTE type = RecvPacked();
    if( type != nPacketType ) throw SocketExceptionIllegalTypePacket();
}

int TlvSocket::RecvPacked( BYTE nPacketTypes[], int size )
{
    BYTE type = RecvPacked();

    for( int i = 0; i < size; i++ )
        if( nPacketTypes[i] == type )
            return type;

    throw SocketExceptionIllegalTypePacket();
}

void TlvSocket::RecvPackedSkipOthers( BYTE nPacketType )
{
    while( RecvPacked() != nPacketType ) ;
}

int TlvSocket::RecvPackedSkipOthers( BYTE nPacketTypes[], int size )
{
    while( TRUE ) {
        BYTE type = RecvPacked();

        for( int i = 0; i < size; i++ )
            if( nPacketTypes[i] == type )
                return type;
    }
}

void TlvSocket::PackBegin( BYTE nPacketType )
{
    EnterCriticalSection( &m_csSendLock );

    PACKET_TYPE(m_pSendBuffer) = nPacketType;
    PAYLOAD_SIZE(m_pSendBuffer) = 0;
}

void TlvSocket::PackByte( BYTE aByte )
{
    m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)] = aByte;
    PAYLOAD_SIZE(m_pSendBuffer) += 1;
}

void TlvSocket::PackWord( WORD aWord )
{
    *(WORD*)&m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)] = aWord;
    PAYLOAD_SIZE(m_pSendBuffer) += sizeof(WORD);
}

void TlvSocket::PackLong( UINT aLong )
{
    *(UINT*)&m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)] = aLong;
    PAYLOAD_SIZE(m_pSendBuffer) += sizeof(UINT);
}

void TlvSocket::PackBinary( void* pMem, WORD bytes )
{
    memcpy( &m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)], pMem, bytes );
    PAYLOAD_SIZE(m_pSendBuffer) += bytes;
}

void TlvSocket::PackString( const char* str, int bytes )
{
    strcpy( &m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)], str );
    PAYLOAD_SIZE(m_pSendBuffer) += bytes;
}

void TlvSocket::PackStringAsUnicode( const char* str, int bytes )
{
    MultiByteToWideChar( CP_ACP, 0, str, -1, (WCHAR*)&m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)], bytes );
    PAYLOAD_SIZE(m_pSendBuffer) += bytes;
}

void TlvSocket::PackStringAsUnicodeWithByteLength( const char* str )
{
    BYTE size = MultiByteToWideChar( CP_ACP, 0, str, -1, NULL, 0 );
    size--; // null character
    PackByte( size );

    int size2 = MultiByteToWideChar( CP_ACP, 0, str, -1, (WCHAR*)&m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)], size+1 );
    PAYLOAD_SIZE(m_pSendBuffer) += size*2;
}

void TlvSocket::PackStringAsUnicodeWithWordLength( const char* str )
{
    BYTE size = MultiByteToWideChar( CP_ACP, 0, str, -1, NULL, 0 );
    size--; // null character
    PackWord( size );

    int size2 = MultiByteToWideChar( CP_ACP, 0, str, -1, (WCHAR*)&m_pSendBuffer[HEADER_SIZE+PAYLOAD_SIZE(m_pSendBuffer)], size+1 );
    PAYLOAD_SIZE(m_pSendBuffer) += size*2;
}

void TlvSocket::UnpackByte( BYTE* aByte )
{
    *aByte = m_pRecvBuffer[m_nRecvBufferPos];
    m_nRecvBufferPos += sizeof(BYTE);
}

void TlvSocket::UnpackWord( WORD* aWord )
{
    *aWord = *(WORD*)&m_pRecvBuffer[m_nRecvBufferPos];
    m_nRecvBufferPos += sizeof(WORD);
}

void TlvSocket::UnpackLong( UINT* aLong )
{
    *aLong = *(UINT*)&m_pRecvBuffer[m_nRecvBufferPos];
    m_nRecvBufferPos += sizeof(UINT);
}

void TlvSocket::UnpackBinary( void* pMem, WORD size )
{
    memcpy( pMem, &m_pRecvBuffer[m_nRecvBufferPos], size );
    m_nRecvBufferPos += size;
}

void TlvSocket::UnpackString( char* pMem, WORD size )
{
    UnpackBinary( pMem, size );
    pMem[size] = '\0';
}

void TlvSocket::UnpackStringFromUnicode( char* str, int bytes )
{
    int size = WideCharToMultiByte( CP_ACP, 0, (WCHAR*)&m_pRecvBuffer[m_nRecvBufferPos], bytes/2, str, bytes+1, NULL, NULL );
    str[size] = '\0';
    m_nRecvBufferPos += bytes;
}
