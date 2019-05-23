#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet081_RequestReserveDismissPenalty.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

int baseValueForPenalty[] = {68,        363,       1168,      2884,      6038,      11287,     19423,     31378,     48229,     71202,     101677,    141193,    191454,    254330,    331867,    426288,     540000,     675596,     835862,     1023784,
                             1242546,   1495543,   1786379,   2118876,   2497077,   2925250,   3407897,   3949754,   4555796,   5231246,   5981576,   6812513,   7730044,   8740422,   9850166,   11066072,   12395215,   13844951,   15422929,   17137087,
                             18995665,  21007203,  23180550,  25524868,  28049635,  30764654,  33680052,  36806289,  40154162,  45525133,  51262490,  57383988,  63907911,  70853089,  80700831,  91162654,   102265881,  114038596,  126509653,  146308200,
                             167244337, 189364894, 212717908, 237352644, 271975263, 308443198, 346827154, 387199547, 429634523, 474207979, 532694979, 606322775, 696381369, 804225364, 931275828, 1108571463, 1309482881, 1535687304, 1788937098, 2071061777};

double CalculatePenaltyForCharacterLevel(int level)
{
    double levelModifier = 10.0 - (level - 1) * 0.125;
    if (levelModifier <= 4.0)
    {
        levelModifier = 4.0;
    }
    return -((baseValueForPenalty[level + 1] - baseValueForPenalty[level]) * (levelModifier * 0.01));
}

// L2CacheD 0x004409F0
bool packet081_RequestReserveDismissPenalty(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet081_RequestReserveDismissPenalty(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"error, cannot find user. dbid [%d]", characterId);

        unguard();
        return false;
    }

    int penalty = static_cast<int>(CalculatePenaltyForCharacterLevel(character->GetLevel()));
    DBConn sql;
    sql.Execute(L"EXEC lin_SetUserDataEx %d, %d", characterId, penalty);

    unguard();
    return false;
}
}  // namespace serverHandlers
