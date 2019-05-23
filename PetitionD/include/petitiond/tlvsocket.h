/*
 * 클라이언트 측 소켓 라이브러리
 * -----------------------------
 * tlvsocket.h/.cpp
 * -----------------------------
 * Kim Soo Min / 2002-11-25
 * -----------------------------
 * - 헤더 + 페이로드 방식의 패킷 형태 사용시 유용
 * - 헤더는 타입/페이로드 크기로 구성되야 하며 크기 및 순서는 #define으로 수정가능
 * - 단위 패킷 단위로 수신 가능
 * - 각 데이터 타입에 따른 패킷 수신/구성 가능
 * - 일반 아스키 문자를 유니코드 형식으로 송/수신 가능
 * - 수신 함수를 부르는 스레드는 하나여야 함
 * - 송신 함수를 부르는 스레드가 여럿일 경우 크리티컬 섹션으로 보호됨
 * - 패킷의 크기가 큰 경우와 원하지 않은 패킷이 올 경우 예외 발생
 * - 데이터 풀기/적재 시 버퍼 바운더리 체크 안함
 * - 이 클래스를 상속 하여 특정 프로토콜에 맞춘 클래스 생성 가능
 */

#ifndef _SM_TLV_SOCKET
#define _SM_TLV_SOCKET

#include "petitiond/clientsocket.h"

#define SEND_BUFFER_SIZE   1021
#define RECV_BUFFER_SIZE   1021
#define HEADER_SIZE        ((USHORT)3)
#define PAYLOAD_SIZE(x)    (*(USHORT*)&x[0])
#define PACKET_TYPE(x)     (*(BYTE*)&x[2])

class SocketExceptionRecvTooBigPacket : public SocketExceptionRecv {};
class SocketExceptionIllegalTypePacket : public SocketExceptionRecv {};

class TlvSocket : public ClientSocket
{
protected:
    char m_pSendBuffer[SEND_BUFFER_SIZE];
    int  m_nSendBufferPos;
    char m_pRecvBuffer[RECV_BUFFER_SIZE];
    int  m_nRecvBufferPos;
    CRITICAL_SECTION m_csSendLock;

public:
    TlvSocket( int timeout );
    ~TlvSocket();

    void PackBegin( BYTE nPacketType );
    void PackByte( BYTE aByte );
    void PackWord( WORD aWord );
    void PackLong( UINT aLong );
    void PackBinary( void* pMem, WORD bytes );
    void PackString( const char* str, int bytes ); // string size must be less than bytes+1
    void PackStringAsUnicode( const char* str, int bytes );
    void PackStringAsUnicodeWithByteLength( const char* str );
    void PackStringAsUnicodeWithWordLength( const char* str );
    void SendPacked();

    int  RecvPacked();
    void RecvPacked( BYTE nPacketType );
    int  RecvPacked( BYTE nPacketTypes[], int size );
    void RecvPackedSkipOthers( BYTE nPacketType );
    int  RecvPackedSkipOthers( BYTE nPacketTypes[], int size );
    void UnpackByte( BYTE* aByte );
    void UnpackWord( WORD* aWord );
    void UnpackLong( UINT* aLong );
    void UnpackBinary( void* pMem, WORD bytes );
    void UnpackString( char* pMem, WORD bytes ); // just add null character, pMem size must be bytes+1
    void UnpackStringFromUnicode( char* str, int bytes );
};

#endif
