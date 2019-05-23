/*
 * 클라이언트 측 소켓 라이브러리
 * -----------------------------
 * clientsocket.h/.cpp
 * -----------------------------
 * Kim Soo Min / 2002-11-25
 * -----------------------------
 * - DNS 룩업을 통한 서버 연결
 * - 버클리 소켓 기반 블럭킹 모드 사용
 * - 소켓 타임 아웃 설정 가능
 * - 지정한 바이트 만큼 받을 때까지 기다리는 기능
 * - 예외 처리를 통한 소켓 에러 처리
 * - SOCKET_DEBUG 심볼 선언으로 디버그 메시지 파일에 남김
 */

#ifndef _SM_CLIENT_SOCKET
#define _SM_CLIENT_SOCKET

#include <winsock.h>

class SocketException {};
class SocketExceptionSend : public SocketException {};
class SocketExceptionRecv : public SocketException {};

class ClientSocket
{
protected:
    SOCKET      m_hSocket;
    SOCKADDR_IN m_addrTarget;
    int         m_nTimeout;

public:
    ClientSocket( int timeout = 5000 );
    BOOL Connect( const char* szTarget, USHORT nPort );
    void SetSocket( SOCKET s );
    void Close();

    int Recv( void* buf, int len );
    int Send( void* buf, int len );

    void RecvFull( void* buf, int total );
    void SendFull( void* buf, int total );
};

void socket_debug(char* fmt, ...);

#endif
