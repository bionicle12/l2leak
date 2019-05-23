#include "cached/model/CAnnounce.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/dbg/StackGuard.h"

CAnnounce g_announce;  // L2CacheD 0x0234EFB8

// L2CacheD 0x0047DB20
CAnnounce::CAnnounce()
    : m_lock()
    , m_loaded(false)
    , m_loginAnnoncesSize(0)
    , m_loginAnnoncesNumber(0)
{
    guard(L"CAnnounce::CAnnounce()");

    ::InitializeCriticalSection(&m_lock);
    ::memset(m_loginAnnoncesPacket, 0, sizeof(m_loginAnnoncesPacket));

    unguard();
}

// L2CacheD 0x0049D900
CAnnounce::~CAnnounce()
{
    guard(L"CAnnounce::~CAnnounce()");

    ::DeleteCriticalSection(&m_lock);

    unguard();
}

// L2CacheD 0x0047DBC0
void CAnnounce::ReadAnnounce(bool reload)
{
    guard(L"void CAnnounce::ReadAnnounce(bool bReload)");

    if (!m_loaded || reload)
    {
        wchar_t announceMsg[255];
        ::memset(announceMsg, 0, sizeof(announceMsg));
        ::memset(m_loginAnnoncesPacket, 0, sizeof(m_loginAnnoncesPacket));

        int announceId = 0;
        m_loginAnnoncesSize = 0;

        DBConn sql;
        sql.Bind(&announceId);
        sql.Bind(announceMsg, 510);

        m_loginAnnoncesNumber = 0;

        if (sql.Execute(L"EXEC lin_GetLoginAnnounce") && sql.Fetch())
        {
            do
            {
                if (m_loginAnnoncesNumber >= 10)
                {
                    break;
                }
                int assembledSize = PacketUtils::Assemble(&m_loginAnnoncesPacket[m_loginAnnoncesSize], 0x1000 - m_loginAnnoncesSize, "dS", m_loginAnnoncesNumber, announceMsg);
                if (assembledSize > 0)
                {
                    m_loginAnnoncesSize += assembledSize;
                }
                ++m_loginAnnoncesNumber;
            } while (sql.Fetch());
        }

        m_loaded = true;
    }

    unguard();
}

int CAnnounce::GetLoginAnnoncesNumber() const
{
    return m_loginAnnoncesNumber;
}

// L2CacheD 0x0047DD50
int CAnnounce::GetPacketSize() const
{
    return m_loginAnnoncesSize;
}

const uint8_t* CAnnounce::GetLoginAnnoncesPacket() const
{
    return m_loginAnnoncesPacket;
}

// L2CacheD 0x0047DD60
bool CAnnounce::ShowIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"bool CAnnounce::ShowIntervalAnnounce(CSocket* pSocket, const unsigned char* packet)");

    int creatureId = 0;
    int repetitive = 0;
    PacketUtils::Disassemble(packet, "dd", &creatureId, &repetitive);

    int interval = 0;
    int announceId = 0;

    wchar_t announceMsg[100];
    ::memset(announceMsg, 0, sizeof(announceMsg));

    DBConn sql;
    sql.Bind(&interval);
    sql.Bind(&announceId);
    sql.Bind(announceMsg, 200);

    int payloadSize = 0;
    if (!sql.Execute(L"EXEC lin_GetIntervalAnnounce"))
    {
        serverSocket->Send("cdddb", CacheToServerPacket_ReplyShowIntervalAnnounce, creatureId, repetitive, 0);
        unguard();
        return false;
    }

    int messagesNumber = 0;

    uint8_t buff[BUFFER_SIZE];
    ::memset(buff, 0, sizeof(buff));

    while (sql.Fetch())
    {
        int assembledSize = PacketUtils::Assemble(&buff[payloadSize], BUFFER_SIZE - payloadSize, "ddS", interval, announceId, announceMsg);
        if (assembledSize > 0)
        {
            ++messagesNumber;
            payloadSize += assembledSize;
        }
        ::memset(announceMsg, 0, sizeof(announceMsg));
    }

    serverSocket->Send("cdddb", CacheToServerPacket_ReplyShowIntervalAnnounce, creatureId, repetitive, messagesNumber, payloadSize, buff);

    unguard();

    return true;
}

// L2CacheD 0x0047DFA0
bool CAnnounce::SetIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"bool CAnnounce::SetIntervalAnnounce(CSocket* pSocket, const unsigned char* packet)");

    wchar_t announceMsg[100];
    ::memset(announceMsg, 0, sizeof(announceMsg));

    int creatureId = 0;
    int interval = 0;
    int announceId = 0;

    PacketUtils::Disassemble(packet, "dddS", &creatureId, &interval, &announceId, 200, announceMsg);

    DBConn sql;
    if (sql.Execute(L"EXEC lin_SetIntervalAnnounce %d, %d, N'%s'", interval, announceId, announceMsg))
    {
        serverSocket->Send("cdddS", CacheToServerPacket_ReplySetIntervalAnnounce, creatureId, interval, announceId, announceMsg);

        unguard();

        return true;
    }

    serverSocket->Send("cdddS", CacheToServerPacket_ReplySetIntervalAnnounce, creatureId, interval, 0, announceMsg);

    unguard();

    return false;
}

// L2CacheD 0x0047E120
bool CAnnounce::DelIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"bool CAnnounce::DelIntervalAnnounce(CSocket* pSocket, const unsigned char* packet)");

    int creatureId = 0;
    int interval = 0;
    int announceId = 0;
    PacketUtils::Disassemble(packet, "ddd", &creatureId, &interval, &announceId);

    DBConn sql;
    if (sql.Execute(L"EXEC lin_DelIntervalAnnounce %d, %d", interval, announceId))
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplyDelIntervalAnnounce, creatureId, interval, announceId);

        unguard();
        return true;
    }

    serverSocket->Send("cddd", CacheToServerPacket_ReplyDelIntervalAnnounce, creatureId, interval, 0);

    unguard();
    return false;
}

// L2CacheD 0x0047E260
bool CAnnounce::LoadIntervalAnnounce(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"bool CAnnounce::LoadIntervalAnnounce(CSocket* pSocket, const unsigned char* packet)");

    int interval = 0;
    int announceId = 0;
    int announcesNumber = 0;

    wchar_t announceMsg[100];
    ::memset(announceMsg, 0, sizeof(announceMsg));

    DBConn sql;
    sql.Bind(&interval);
    sql.Bind(&announceId);
    sql.Bind(announceMsg, 200);

    uint8_t buff[BUFFER_SIZE];
    ::memset(buff, 0, BUFFER_SIZE);

    if (sql.Execute(L"EXEC lin_GetIntervalAnnounce") && sql.Fetch())
    {
        int payloadSize = 0;
        do
        {
            int assembledSize = PacketUtils::Assemble(&buff[payloadSize], BUFFER_SIZE - payloadSize, "ddS", interval, announceId, announceMsg);
            if (assembledSize > 0)
            {
                ++announcesNumber;
                payloadSize += assembledSize;
            }
            ::memset(announceMsg, 0, sizeof(announceMsg));
        } while (sql.Fetch());

        if (announcesNumber > 0)
        {
            serverSocket->Send("cdb", CacheToServerPacket_ReplyLoadIntervalAnnounce, announcesNumber, payloadSize, buff);
        }

        unguard();
        return true;
    }

    unguard();
    return false;
}

void CAnnounce::Lock()
{
    ::EnterCriticalSection(&m_lock);
}

void CAnnounce::Unlock()
{
    ::LeaveCriticalSection(&m_lock);
}
