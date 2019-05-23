#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/adminHandlers.h"

#include "cached/network/packets/adminHandlers/packet00_NoPacket.h"
#include "cached/network/packets/adminHandlers/packet01_CheckCharacterPacket.h"
#include "cached/network/packets/adminHandlers/packet02_SetCharacterLocationPacket.h"
#include "cached/network/packets/adminHandlers/packet03_SetBuilderCharacterPacket.h"
#include "cached/network/packets/adminHandlers/packet04_ChangeCharacterNamePacket.h"
#include "cached/network/packets/adminHandlers/packet05_KickCharacterPacket.h"
#include "cached/network/packets/adminHandlers/packet06_AddSkillPacket.h"
#include "cached/network/packets/adminHandlers/packet07_DelSkillPacket.h"
#include "cached/network/packets/adminHandlers/packet08_ModSkillPacket.h"
#include "cached/network/packets/adminHandlers/packet09_SetOnetimeQuestPacket.h"
#include "cached/network/packets/adminHandlers/packet10_SetQuestPacket.h"
#include "cached/network/packets/adminHandlers/packet11_DelQuestPacket.h"
#include "cached/network/packets/adminHandlers/packet12_AddItemPacket.h"
#include "cached/network/packets/adminHandlers/packet13_DelItemPacket.h"
#include "cached/network/packets/adminHandlers/packet14_ModItemPacket.h"
#include "cached/network/packets/adminHandlers/packet15_ModCharPacket.h"
#include "cached/network/packets/adminHandlers/packet16_ModChar2Packet.h"
#include "cached/network/packets/adminHandlers/packet17_ModCharNickNamePacket.h"
#include "cached/network/packets/adminHandlers/packet18_PunishCharPacket.h"
#include "cached/network/packets/adminHandlers/packet19_SetBuilderAccountPacket.h"
#include "cached/network/packets/adminHandlers/packet20_DisableCharacterPacket.h"
#include "cached/network/packets/adminHandlers/packet21_EnableCharacterPacket.h"
#include "cached/network/packets/adminHandlers/packet22_GetCharactersPacket.h"
#include "cached/network/packets/adminHandlers/packet23_SetBookMarkPacket.h"
#include "cached/network/packets/adminHandlers/packet24_DelBookMarkPacket.h"
#include "cached/network/packets/adminHandlers/packet25_DelPledgeCrestPacket.h"
#include "cached/network/packets/adminHandlers/packet26_ModPledgeNamePacket.h"
#include "cached/network/packets/adminHandlers/packet27_SetProhibitedPacket.h"
#include "cached/network/packets/adminHandlers/packet28_SeizeItemPacket.h"
#include "cached/network/packets/adminHandlers/packet29_ModChar3Packet.h"
#include "cached/network/packets/adminHandlers/packet30_MoveItemPacket.h"
#include "cached/network/packets/adminHandlers/packet31_MoveCharacterPacket.h"
#include "cached/network/packets/adminHandlers/packet32_CommentWritePacket.h"
#include "cached/network/packets/adminHandlers/packet33_CommentDeletePacket.h"
#include "cached/network/packets/adminHandlers/packet34_DeleteCharPacket.h"
#include "cached/network/packets/adminHandlers/packet35_RestoreCharPacket.h"
#include "cached/network/packets/adminHandlers/packet36_PledgeOustPacket.h"
#include "cached/network/packets/adminHandlers/packet37_PledgeChangeOwnerPacket.h"
#include "cached/network/packets/adminHandlers/packet38_PledgeDeletePacket.h"
#include "cached/network/packets/adminHandlers/packet39_BanCharPacket.h"
#include "cached/network/packets/adminHandlers/packet40_MoveItem2Packet.h"
#include "cached/network/packets/adminHandlers/packet41_PrintAllAccountData.h"
#include "cached/network/packets/adminHandlers/packet42_PrintAllItemData.h"
#include "cached/network/packets/adminHandlers/packet43_CopyCharPacket.h"
#include "cached/network/packets/adminHandlers/packet44_CreatePetPacket.h"
#include "cached/network/packets/adminHandlers/packet45_SendHomePacket.h"
#include "cached/network/packets/adminHandlers/packet46_ChangePledgeLevelPacket.h"
#include "cached/network/packets/adminHandlers/packet47_CreatePledgePacket.h"
#include "cached/network/packets/adminHandlers/packet48_SetSkillAllPacket.h"
#include "cached/network/packets/adminHandlers/packet49_RestoreChar2Packet.h"
#include "cached/network/packets/adminHandlers/packet50_ManAnnouncePacket.h"
#include "cached/network/packets/adminHandlers/packet51_ManIntAnnouncePacket.h"
#include "cached/network/packets/adminHandlers/packet52_ModWeekPlayPacket.h"
#include "cached/network/packets/adminHandlers/packet53_SeizeItem2Packet.h"
#include "cached/network/packets/adminHandlers/packet54_DelItem2Packet.h"
#include "cached/network/packets/adminHandlers/packet55_AddItem2Packet.h"

const PacketHandler adminHandlers::s_packetHandlers[adminHandlers::HANDLERS_NUMBER] = {&adminHandlers::packet00_NoPacket,
                                                                                       &adminHandlers::packet01_CheckCharacterPacket,
                                                                                       &adminHandlers::packet02_SetCharacterLocationPacket,
                                                                                       &adminHandlers::packet03_SetBuilderCharacterPacket,
                                                                                       &adminHandlers::packet04_ChangeCharacterNamePacket,
                                                                                       &adminHandlers::packet05_KickCharacterPacket,
                                                                                       &adminHandlers::packet06_AddSkillPacket,
                                                                                       &adminHandlers::packet07_DelSkillPacket,
                                                                                       &adminHandlers::packet08_ModSkillPacket,
                                                                                       &adminHandlers::packet09_SetOnetimeQuestPacket,
                                                                                       &adminHandlers::packet10_SetQuestPacket,
                                                                                       &adminHandlers::packet11_DelQuestPacket,
                                                                                       &adminHandlers::packet12_AddItemPacket,
                                                                                       &adminHandlers::packet13_DelItemPacket,
                                                                                       &adminHandlers::packet14_ModItemPacket,
                                                                                       &adminHandlers::packet15_ModCharPacket,
                                                                                       &adminHandlers::packet16_ModChar2Packet,
                                                                                       &adminHandlers::packet17_ModCharNickNamePacket,
                                                                                       &adminHandlers::packet18_PunishCharPacket,
                                                                                       &adminHandlers::packet19_SetBuilderAccountPacket,
                                                                                       &adminHandlers::packet20_DisableCharacterPacket,
                                                                                       &adminHandlers::packet21_EnableCharacterPacket,
                                                                                       &adminHandlers::packet22_GetCharactersPacket,
                                                                                       &adminHandlers::packet23_SetBookMarkPacket,
                                                                                       &adminHandlers::packet24_DelBookMarkPacket,
                                                                                       &adminHandlers::packet25_DelPledgeCrestPacket,
                                                                                       &adminHandlers::packet26_ModPledgeNamePacket,
                                                                                       &adminHandlers::packet27_SetProhibitedPacket,
                                                                                       &adminHandlers::packet28_SeizeItemPacket,
                                                                                       &adminHandlers::packet29_ModChar3Packet,
                                                                                       &adminHandlers::packet30_MoveItemPacket,
                                                                                       &adminHandlers::packet31_MoveCharacterPacket,
                                                                                       &adminHandlers::packet32_CommentWritePacket,
                                                                                       &adminHandlers::packet33_CommentDeletePacket,
                                                                                       &adminHandlers::packet34_DeleteCharPacket,
                                                                                       &adminHandlers::packet35_RestoreCharPacket,
                                                                                       &adminHandlers::packet36_PledgeOustPacket,
                                                                                       &adminHandlers::packet37_PledgeChangeOwnerPacket,
                                                                                       &adminHandlers::packet38_PledgeDeletePacket,
                                                                                       &adminHandlers::packet39_BanCharPacket,
                                                                                       &adminHandlers::packet40_MoveItem2Packet,
                                                                                       &adminHandlers::packet41_PrintAllAccountData,
                                                                                       &adminHandlers::packet42_PrintAllItemData,
                                                                                       &adminHandlers::packet43_CopyCharPacket,
                                                                                       &adminHandlers::packet44_CreatePetPacket,
                                                                                       &adminHandlers::packet45_SendHomePacket,
                                                                                       &adminHandlers::packet46_ChangePledgeLevelPacket,
                                                                                       &adminHandlers::packet47_CreatePledgePacket,
                                                                                       &adminHandlers::packet48_SetSkillAllPacket,
                                                                                       &adminHandlers::packet49_RestoreChar2Packet,
                                                                                       &adminHandlers::packet50_ManAnnouncePacket,
                                                                                       &adminHandlers::packet51_ManIntAnnouncePacket,
                                                                                       &adminHandlers::packet52_ModWeekPlayPacket,
                                                                                       &adminHandlers::packet53_SeizeItem2Packet,
                                                                                       &adminHandlers::packet54_DelItem2Packet,
                                                                                       &adminHandlers::packet55_AddItem2Packet};
