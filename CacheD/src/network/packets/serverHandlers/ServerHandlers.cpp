#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/ServerHandlers.h"

#include "cached/network/packets/serverHandlers/packet000_CacheVersionPacket.h"
#include "cached/network/packets/serverHandlers/packet001_LoadCharacterPacket.h"
#include "cached/network/packets/serverHandlers/packet002_CreateCharacterPacket.h"
#include "cached/network/packets/serverHandlers/packet003_CreateItemPacket.h"
#include "cached/network/packets/serverHandlers/packet005_LoadItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet006_CreateInitItems.h"
#include "cached/network/packets/serverHandlers/packet007_DropItemPacket.h"
#include "cached/network/packets/serverHandlers/packet008_GetItemPacket.h"
#include "cached/network/packets/serverHandlers/packet009_SaveCharacterPacket.h"
#include "cached/network/packets/serverHandlers/packet010_SaveItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet011_DeleteCharacterPacket.h"
#include "cached/network/packets/serverHandlers/packet012_RequestListBoardPacket.h"
#include "cached/network/packets/serverHandlers/packet013_RequestWriteBoardPacket.h"
#include "cached/network/packets/serverHandlers/packet014_RequestReadBoardPacket.h"
#include "cached/network/packets/serverHandlers/packet016_RequestUpdateUserPledge.h"
#include "cached/network/packets/serverHandlers/packet017_RequestDeletePledge.h"
#include "cached/network/packets/serverHandlers/packet018_LoadWarehouseItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet019_WithdrawWarehouseItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet020_RequestShortCutInfoPacket.h"
#include "cached/network/packets/serverHandlers/packet021_RequestSetShortCutPacket.h"
#include "cached/network/packets/serverHandlers/packet022_DepositWarehouseItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet023_SellItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet024_BuyItemsPacket.h"
#include "cached/network/packets/serverHandlers/packet025_GetNewItemPacket.h"
#include "cached/network/packets/serverHandlers/packet026_UseItemPacket.h"
#include "cached/network/packets/serverHandlers/packet027_RequestLoadPledge.h"
#include "cached/network/packets/serverHandlers/packet028_RequestOpenPledgeList.h"
#include "cached/network/packets/serverHandlers/packet029_RequestCharacterLogin.h"
#include "cached/network/packets/serverHandlers/packet030_RequestCharacterLogout.h"
#include "cached/network/packets/serverHandlers/packet031_RequestQuestSet.h"
#include "cached/network/packets/serverHandlers/packet032_RequestSetAgitOwner.h"
#include "cached/network/packets/serverHandlers/packet033_RequestSetCastleOwner.h"
#include "cached/network/packets/serverHandlers/packet034_RequestLoadAllCastleData.h"
#include "cached/network/packets/serverHandlers/packet035_RequestLoadAgit.h"
#include "cached/network/packets/serverHandlers/packet036_RequestWriteCastleTax.h"
#include "cached/network/packets/serverHandlers/packet037_RequestSetSiegeTime.h"
#include "cached/network/packets/serverHandlers/packet038_RequestManipulateItem.h"
#include "cached/network/packets/serverHandlers/packet039_RequestOustPledgeMember.h"
#include "cached/network/packets/serverHandlers/packet041_RequestTrade.h"
#include "cached/network/packets/serverHandlers/packet042_RequestSetPledgeCrest.h"
#include "cached/network/packets/serverHandlers/packet043_RequestStartPledgeWar.h"
#include "cached/network/packets/serverHandlers/packet044_RequestStopPledgeWar.h"
#include "cached/network/packets/serverHandlers/packet045_RequestSurrenderPledgeWar.h"
#include "cached/network/packets/serverHandlers/packet046_RequestSetUserNickname.h"
#include "cached/network/packets/serverHandlers/packet047_RequestAquireSkill.h"
#include "cached/network/packets/serverHandlers/packet048_RequestTGSBoardPacket.h"
#include "cached/network/packets/serverHandlers/packet049_RequestDestroyItem.h"
#include "cached/network/packets/serverHandlers/packet050_RequestEnchantItem.h"
#include "cached/network/packets/serverHandlers/packet051_RequestEnchantItemFail.h"
#include "cached/network/packets/serverHandlers/packet052_RequestSetPrivateBankLimit.h"
#include "cached/network/packets/serverHandlers/packet053_RequestInitBoardPacket.h"
#include "cached/network/packets/serverHandlers/packet054_RequestCheckCachedPacket.h"
#include "cached/network/packets/serverHandlers/packet055_RequestLoadSkill.h"
#include "cached/network/packets/serverHandlers/packet056_RequestAddBookMarkPacket.h"
#include "cached/network/packets/serverHandlers/packet057_RequestDelBookMarkPacket.h"
#include "cached/network/packets/serverHandlers/packet058_RequestTelBookMarkPacket.h"
#include "cached/network/packets/serverHandlers/packet059_RequestGetBookMarkPacket.h"
#include "cached/network/packets/serverHandlers/packet060_RequestLoadFriendList.h"
#include "cached/network/packets/serverHandlers/packet061_RequestEstablishFriendship.h"
#include "cached/network/packets/serverHandlers/packet062_RequestBreakFriendship.h"
#include "cached/network/packets/serverHandlers/packet063_RequestChangeItemData.h"
#include "cached/network/packets/serverHandlers/packet064_SetPunishPacket.h"
#include "cached/network/packets/serverHandlers/packet065_GetPunishPacket.h"
#include "cached/network/packets/serverHandlers/packet066_ChangePosPacket.h"
#include "cached/network/packets/serverHandlers/packet067_GetLoginAnnouncePacket.h"
#include "cached/network/packets/serverHandlers/packet068_SetLoginAnnouncePacket.h"
#include "cached/network/packets/serverHandlers/packet069_DelLoginAnnouncePacket.h"
#include "cached/network/packets/serverHandlers/packet070_SetBuilderPacket.h"
#include "cached/network/packets/serverHandlers/packet071_LoadSelectedCharacter.h"
#include "cached/network/packets/serverHandlers/packet072_RequestDeleteSkill.h"
#include "cached/network/packets/serverHandlers/packet073_RequestRestoreCharacter.h"
#include "cached/network/packets/serverHandlers/packet074_RequestSetPledgeInfo.h"
#include "cached/network/packets/serverHandlers/packet075_RequestPledgeExtendedInfo.h"
#include "cached/network/packets/serverHandlers/packet076_RequestGetPledgeCrest.h"
#include "cached/network/packets/serverHandlers/packet077_RequestFinishPledgeWar.h"
#include "cached/network/packets/serverHandlers/packet078_RequestLoadPledgeWar.h"
#include "cached/network/packets/serverHandlers/packet079_RequestCreatePledge.h"
#include "cached/network/packets/serverHandlers/packet080_RequestDeletePledgeByTimer.h"
#include "cached/network/packets/serverHandlers/packet081_RequestReserveDismissPenalty.h"
#include "cached/network/packets/serverHandlers/packet082_RequestLoadDismissReservedPledge.h"
#include "cached/network/packets/serverHandlers/packet083_RequestCheckPreviousWarHistory.h"
#include "cached/network/packets/serverHandlers/packet084_RequestPetiGetCharList.h"
#include "cached/network/packets/serverHandlers/packet085_RequestPetiSaveMsg.h"
#include "cached/network/packets/serverHandlers/packet086_RequestSetUserPledgeInfo.h"
#include "cached/network/packets/serverHandlers/packet087_RequestLogCharInfo.h"
#include "cached/network/packets/serverHandlers/packet088_RequestChallengeRejected.h"
#include "cached/network/packets/serverHandlers/packet089_RequestResetUserNickname.h"
#include "cached/network/packets/serverHandlers/packet090_RequestManageBattleCamp.h"
#include "cached/network/packets/serverHandlers/packet091_RequestLoadBattleCamp.h"
#include "cached/network/packets/serverHandlers/packet092_RequestPrepareCastleWar.h"
#include "cached/network/packets/serverHandlers/packet093_RequestViewSiegeList.h"
#include "cached/network/packets/serverHandlers/packet094_RequestApproveBattle.h"
#include "cached/network/packets/serverHandlers/packet095_RequestConfirmCastleDefence.h"
#include "cached/network/packets/serverHandlers/packet096_RequestQueryCastleSiegeForRegister.h"
#include "cached/network/packets/serverHandlers/packet097_RequestQueryCastleSiegeForUnregister.h"
#include "cached/network/packets/serverHandlers/packet098_RequestQueryCastleSiegeForInfo.h"
#include "cached/network/packets/serverHandlers/packet099_RequestQueryCastleSiegeForDismiss.h"
#include "cached/network/packets/serverHandlers/packet100_RequestDelPledgeCrest.h"
#include "cached/network/packets/serverHandlers/packet101_RequestModPledgeName.h"
#include "cached/network/packets/serverHandlers/packet102_ResetCastleSiegePledge.h"
#include "cached/network/packets/serverHandlers/packet103_RequestPartyTelBookMarkPacket.h"
#include "cached/network/packets/serverHandlers/packet104_RequestBuilderAccountList.h"
#include "cached/network/packets/serverHandlers/packet105_RequestLoadDoor.h"
#include "cached/network/packets/serverHandlers/packet106_RequestSaveCastleStatus.h"
#include "cached/network/packets/serverHandlers/packet107_RequestSaveDoorStatus.h"
#include "cached/network/packets/serverHandlers/packet108_RequestBBSMakeBoard.h"
#include "cached/network/packets/serverHandlers/packet109_RequestBBSGetBoardList.h"
#include "cached/network/packets/serverHandlers/packet110_RequestBBSModBoard.h"
#include "cached/network/packets/serverHandlers/packet111_RequestBBSDelBoard.h"
#include "cached/network/packets/serverHandlers/packet112_RequestBBSWriteArticle.h"
#include "cached/network/packets/serverHandlers/packet113_RequestBBSReadArticle.h"
#include "cached/network/packets/serverHandlers/packet114_RequestBBSGetArticleList.h"
#include "cached/network/packets/serverHandlers/packet115_RequestBBSReadArticleThread.h"
#include "cached/network/packets/serverHandlers/packet116_RequestBBSGetComment.h"
#include "cached/network/packets/serverHandlers/packet117_RequestBBSReplyForm.h"
#include "cached/network/packets/serverHandlers/packet118_RequestBBSWriteComment.h"
#include "cached/network/packets/serverHandlers/packet119_RequestBBSWriteForm.h"
#include "cached/network/packets/serverHandlers/packet120_RequestBBSSearch.h"
#include "cached/network/packets/serverHandlers/packet121_RequestBBSModifyForm.h"
#include "cached/network/packets/serverHandlers/packet122_RequestBBSModify.h"
#include "cached/network/packets/serverHandlers/packet123_RequestBBSDelete.h"
#include "cached/network/packets/serverHandlers/packet124_RequestLoadWarehouseItemList.h"
#include "cached/network/packets/serverHandlers/packet125_RequestCrystallizeItem.h"
#include "cached/network/packets/serverHandlers/packet126_RequestSaveCastleIncome.h"
#include "cached/network/packets/serverHandlers/packet127_RequestSaveCropData.h"
#include "cached/network/packets/serverHandlers/packet128_RequestDeleteCropData.h"
#include "cached/network/packets/serverHandlers/packet129_RequestInstallAgitDeco.h"
#include "cached/network/packets/serverHandlers/packet130_RequestSavePledgeContribution.h"
#include "cached/network/packets/serverHandlers/packet131_RequestGetContributionRelatedPledge.h"
#include "cached/network/packets/serverHandlers/packet132_RequestSetAgitInfo.h"
#include "cached/network/packets/serverHandlers/packet133_RequestPrivateStoreCommit.h"
#include "cached/network/packets/serverHandlers/packet134_RequestSaveDieDropExp.h"
#include "cached/network/packets/serverHandlers/packet135_RequestBBSGetFavorite.h"
#include "cached/network/packets/serverHandlers/packet136_RequestBBSAddFavorite.h"
#include "cached/network/packets/serverHandlers/packet137_RequestBBSDelFavorite.h"
#include "cached/network/packets/serverHandlers/packet138_RequestResetContribution.h"
#include "cached/network/packets/serverHandlers/packet139_RequestBBSGetAnnounce.h"
#include "cached/network/packets/serverHandlers/packet140_RequestSaveObjectHp.h"
#include "cached/network/packets/serverHandlers/packet141_RequestSaveCastleSiegeElapsedTime.h"
#include "cached/network/packets/serverHandlers/packet142_RequestSaveSkillUse.h"
#include "cached/network/packets/serverHandlers/packet143_RequestLoadPledge.h"
#include "cached/network/packets/serverHandlers/packet144_RequestPing.h"
#include "cached/network/packets/serverHandlers/packet145_RequestPing_OneAdenaDrop.h"
#include "cached/network/packets/serverHandlers/packet146_RequestPing_Network.h"
#include "cached/network/packets/serverHandlers/packet147_RequestSaveAbnormalStatus.h"
#include "cached/network/packets/serverHandlers/packet148_RequestLoadAbnormalStatus.h"
#include "cached/network/packets/serverHandlers/packet149_RequestCreateAllianceByNpc.h"
#include "cached/network/packets/serverHandlers/packet150_RequestJoinAlliance.h"
#include "cached/network/packets/serverHandlers/packet151_RequestDismissAlliance.h"
#include "cached/network/packets/serverHandlers/packet152_RequestOustAllianceMemberPledge.h"
#include "cached/network/packets/serverHandlers/packet153_RequestWithdrawAlliance.h"
#include "cached/network/packets/serverHandlers/packet154_RequestCreatePet.h"
#include "cached/network/packets/serverHandlers/packet155_RequestDeletePet.h"
#include "cached/network/packets/serverHandlers/packet156_RequestWithdrawPet.h"
#include "cached/network/packets/serverHandlers/packet157_RequestLoadPetItems.h"
#include "cached/network/packets/serverHandlers/packet158_RequestDepositPet.h"
#include "cached/network/packets/serverHandlers/packet159_RequestSavePet.h"
#include "cached/network/packets/serverHandlers/packet160_RequestChangePetName.h"
#include "cached/network/packets/serverHandlers/packet161_RequestDismissPet.h"
#include "cached/network/packets/serverHandlers/packet162_RequestPetGetItem.h"
#include "cached/network/packets/serverHandlers/packet163_RequestPetDropItem.h"
#include "cached/network/packets/serverHandlers/packet164_RequestGiveItemToPet.h"
#include "cached/network/packets/serverHandlers/packet165_RequestGetItemFromPet.h"
#include "cached/network/packets/serverHandlers/packet166_RequestPetUseItem.h"
#include "cached/network/packets/serverHandlers/packet167_RequestSetAllianceCrest.h"
#include "cached/network/packets/serverHandlers/packet168_RequestGetAllianceCrest.h"
#include "cached/network/packets/serverHandlers/packet169_RequestDelAllianceCrest.h"
#include "cached/network/packets/serverHandlers/packet170_RequestLoadAllAlliance.h"
#include "cached/network/packets/serverHandlers/packet171_RequestSetAllianceInfo.h"
#include "cached/network/packets/serverHandlers/packet172_RequestGetDbRelatedCounts.h"
#include "cached/network/packets/serverHandlers/packet173_RequestLoadAllPledgeWar.h"
#include "cached/network/packets/serverHandlers/packet174_RequestIncreaseUserPKCount.h"
#include "cached/network/packets/serverHandlers/packet175_RequestIncreaseUserDuelCount.h"
#include "cached/network/packets/serverHandlers/packet176_RequestRecipeMakeItem.h"
#include "cached/network/packets/serverHandlers/packet177_RequestPickItem.h"
#include "cached/network/packets/serverHandlers/packet178_RequestCheckPreviousAllianceWarHistory.h"
#include "cached/network/packets/serverHandlers/packet179_RequestStartAllianceWar.h"
#include "cached/network/packets/serverHandlers/packet180_RequestStopAllianceWar.h"
#include "cached/network/packets/serverHandlers/packet181_RequestSurrenderAllianceWar.h"
#include "cached/network/packets/serverHandlers/packet182_RequestFinishAllianceWar.h"
#include "cached/network/packets/serverHandlers/packet183_RequestLoadAllianceWar.h"
#include "cached/network/packets/serverHandlers/packet184_RequestAllianceWarChallengeRejected.h"
#include "cached/network/packets/serverHandlers/packet185_RequestPackageLoadTargetList.h"
#include "cached/network/packets/serverHandlers/packet186_RequestPackageSendToTarget.h"
#include "cached/network/packets/serverHandlers/packet187_RequestAddBlockList.h"
#include "cached/network/packets/serverHandlers/packet188_RequestDeleteBlockList.h"
#include "cached/network/packets/serverHandlers/packet189_RequestLoadWarehouseItemsEx.h"
#include "cached/network/packets/serverHandlers/packet190_RequestWithdrawWarehouseItemsEx.h"
#include "cached/network/packets/serverHandlers/packet191_RequestDepositWarehouseItemsEx.h"
#include "cached/network/packets/serverHandlers/packet192_RequestSetNextCastleSiege.h"
#include "cached/network/packets/serverHandlers/packet193_RequestCreateAgitAuction.h"
#include "cached/network/packets/serverHandlers/packet194_RequestCreateAgitBid.h"
#include "cached/network/packets/serverHandlers/packet195_RequestSetAgitAuction.h"
#include "cached/network/packets/serverHandlers/packet196_RequestLoadCastleGuard.h"
#include "cached/network/packets/serverHandlers/packet197_RequestLoadAgitBid.h"
#include "cached/network/packets/serverHandlers/packet198_RequestLoadControlTower.h"
#include "cached/network/packets/serverHandlers/packet199_RequestSaveControlTower.h"
#include "cached/network/packets/serverHandlers/packet200_RequestSaveMercenary.h"
#include "cached/network/packets/serverHandlers/packet201_RequestLoadMercenary.h"
#include "cached/network/packets/serverHandlers/packet202_RequestDeleteMercenary.h"
#include "cached/network/packets/serverHandlers/packet203_RequestUpdateMercenary.h"
#include "cached/network/packets/serverHandlers/packet204_RequestAgitPledgeAdena.h"
#include "cached/network/packets/serverHandlers/packet205_RequestCancelAgitAuction.h"
#include "cached/network/packets/serverHandlers/packet206_RequestAgitCost.h"
#include "cached/network/packets/serverHandlers/packet207_RequestShowIntervalAnnounce.h"
#include "cached/network/packets/serverHandlers/packet208_RequestSetIntervalAnnounce.h"
#include "cached/network/packets/serverHandlers/packet209_RequestDelIntervalAnnounce.h"
#include "cached/network/packets/serverHandlers/packet210_RequestDeleteCastleGuard.h"
#include "cached/network/packets/serverHandlers/packet211_RequestAgitAutoSell.h"
#include "cached/network/packets/serverHandlers/packet212_RequestAgitBidCancel.h"
#include "cached/network/packets/serverHandlers/packet213_RequestLoadIntervalAnnounce.h"
#include "cached/network/packets/serverHandlers/packet214_RequestSurrenderPersonally.h"
#include "cached/network/packets/serverHandlers/packet215_RequestEndSiege.h"
#include "cached/network/packets/serverHandlers/packet216_RequestPetiSaveMsgForce.h"
#include "cached/network/packets/serverHandlers/packet217_RequestAdminTool.h"
#include "cached/network/packets/serverHandlers/packet218_RequestLoadLastResidenceTax.h"
#include "cached/network/packets/serverHandlers/packet219_RequestSetLastResidenceTaxUpdate.h"
#include "cached/network/packets/serverHandlers/packet220_RequestMngComment.h"
#include "cached/network/packets/serverHandlers/packet221_RequestLoadPlayTime.h"
#include "cached/network/packets/serverHandlers/packet222_RequestChangeTimeLimit.h"
#include "cached/network/packets/serverHandlers/packet223_RequestSaveUsedTime.h"
#include "cached/network/packets/serverHandlers/packet224_DummyPacket.h"

const PacketHandler serverHandlers::s_packetHandlers[serverHandlers::HANDLERS_NUMBER + 1] = {&serverHandlers::packet000_CacheVersionPacket,
                                                                                             &serverHandlers::packet001_LoadCharacterPacket,
                                                                                             &serverHandlers::packet002_CreateCharacterPacket,
                                                                                             &serverHandlers::packet003_CreateItemPacket,
                                                                                             &serverHandlers::packet224_DummyPacket,
                                                                                             &serverHandlers::packet005_LoadItemsPacket,
                                                                                             &serverHandlers::packet006_CreateInitItems,
                                                                                             &serverHandlers::packet007_DropItemPacket,
                                                                                             &serverHandlers::packet008_GetItemPacket,
                                                                                             &serverHandlers::packet009_SaveCharacterPacket,
                                                                                             &serverHandlers::packet010_SaveItemsPacket,
                                                                                             &serverHandlers::packet011_DeleteCharacterPacket,
                                                                                             &serverHandlers::packet012_RequestListBoardPacket,
                                                                                             &serverHandlers::packet013_RequestWriteBoardPacket,
                                                                                             &serverHandlers::packet014_RequestReadBoardPacket,
                                                                                             &serverHandlers::packet224_DummyPacket,
                                                                                             &serverHandlers::packet016_RequestUpdateUserPledge,
                                                                                             &serverHandlers::packet017_RequestDeletePledge,
                                                                                             &serverHandlers::packet018_LoadWarehouseItemsPacket,
                                                                                             &serverHandlers::packet019_WithdrawWarehouseItemsPacket,
                                                                                             &serverHandlers::packet020_RequestShortCutInfoPacket,
                                                                                             &serverHandlers::packet021_RequestSetShortCutPacket,
                                                                                             &serverHandlers::packet022_DepositWarehouseItemsPacket,
                                                                                             &serverHandlers::packet023_SellItemsPacket,
                                                                                             &serverHandlers::packet024_BuyItemsPacket,
                                                                                             &serverHandlers::packet025_GetNewItemPacket,
                                                                                             &serverHandlers::packet026_UseItemPacket,
                                                                                             &serverHandlers::packet027_RequestLoadPledge,
                                                                                             &serverHandlers::packet028_RequestOpenPledgeList,
                                                                                             &serverHandlers::packet029_RequestCharacterLogin,
                                                                                             &serverHandlers::packet030_RequestCharacterLogout,
                                                                                             &serverHandlers::packet031_RequestQuestSet,
                                                                                             &serverHandlers::packet032_RequestSetAgitOwner,
                                                                                             &serverHandlers::packet033_RequestSetCastleOwner,
                                                                                             &serverHandlers::packet034_RequestLoadAllCastleData,
                                                                                             &serverHandlers::packet035_RequestLoadAgit,
                                                                                             &serverHandlers::packet036_RequestWriteCastleTax,
                                                                                             &serverHandlers::packet037_RequestSetSiegeTime,
                                                                                             &serverHandlers::packet038_RequestManipulateItem,
                                                                                             &serverHandlers::packet039_RequestOustPledgeMember,
                                                                                             &serverHandlers::packet224_DummyPacket,
                                                                                             &serverHandlers::packet041_RequestTrade,
                                                                                             &serverHandlers::packet042_RequestSetPledgeCrest,
                                                                                             &serverHandlers::packet043_RequestStartPledgeWar,
                                                                                             &serverHandlers::packet044_RequestStopPledgeWar,
                                                                                             &serverHandlers::packet045_RequestSurrenderPledgeWar,
                                                                                             &serverHandlers::packet046_RequestSetUserNickname,
                                                                                             &serverHandlers::packet047_RequestAquireSkill,
                                                                                             &serverHandlers::packet048_RequestTGSBoardPacket,
                                                                                             &serverHandlers::packet049_RequestDestroyItem,
                                                                                             &serverHandlers::packet050_RequestEnchantItem,
                                                                                             &serverHandlers::packet051_RequestEnchantItemFail,
                                                                                             &serverHandlers::packet052_RequestSetPrivateBankLimit,
                                                                                             &serverHandlers::packet053_RequestInitBoardPacket,
                                                                                             &serverHandlers::packet054_RequestCheckCachedPacket,
                                                                                             &serverHandlers::packet055_RequestLoadSkill,
                                                                                             &serverHandlers::packet056_RequestAddBookMarkPacket,
                                                                                             &serverHandlers::packet057_RequestDelBookMarkPacket,
                                                                                             &serverHandlers::packet058_RequestTelBookMarkPacket,
                                                                                             &serverHandlers::packet059_RequestGetBookMarkPacket,
                                                                                             &serverHandlers::packet060_RequestLoadFriendList,
                                                                                             &serverHandlers::packet061_RequestEstablishFriendship,
                                                                                             &serverHandlers::packet062_RequestBreakFriendship,
                                                                                             &serverHandlers::packet063_RequestChangeItemData,
                                                                                             &serverHandlers::packet064_SetPunishPacket,
                                                                                             &serverHandlers::packet065_GetPunishPacket,
                                                                                             &serverHandlers::packet066_ChangePosPacket,
                                                                                             &serverHandlers::packet067_GetLoginAnnouncePacket,
                                                                                             &serverHandlers::packet068_SetLoginAnnouncePacket,
                                                                                             &serverHandlers::packet069_DelLoginAnnouncePacket,
                                                                                             &serverHandlers::packet070_SetBuilderPacket,
                                                                                             &serverHandlers::packet071_LoadSelectedCharacter,
                                                                                             &serverHandlers::packet072_RequestDeleteSkill,
                                                                                             &serverHandlers::packet073_RequestRestoreCharacter,
                                                                                             &serverHandlers::packet074_RequestSetPledgeInfo,
                                                                                             &serverHandlers::packet075_RequestPledgeExtendedInfo,
                                                                                             &serverHandlers::packet076_RequestGetPledgeCrest,
                                                                                             &serverHandlers::packet077_RequestFinishPledgeWar,
                                                                                             &serverHandlers::packet078_RequestLoadPledgeWar,
                                                                                             &serverHandlers::packet079_RequestCreatePledge,
                                                                                             &serverHandlers::packet080_RequestDeletePledgeByTimer,
                                                                                             &serverHandlers::packet081_RequestReserveDismissPenalty,
                                                                                             &serverHandlers::packet082_RequestLoadDismissReservedPledge,
                                                                                             &serverHandlers::packet083_RequestCheckPreviousWarHistory,
                                                                                             &serverHandlers::packet084_RequestPetiGetCharList,
                                                                                             &serverHandlers::packet085_RequestPetiSaveMsg,
                                                                                             &serverHandlers::packet086_RequestSetUserPledgeInfo,
                                                                                             &serverHandlers::packet087_RequestLogCharInfo,
                                                                                             &serverHandlers::packet088_RequestChallengeRejected,
                                                                                             &serverHandlers::packet089_RequestResetUserNickname,
                                                                                             &serverHandlers::packet090_RequestManageBattleCamp,
                                                                                             &serverHandlers::packet091_RequestLoadBattleCamp,
                                                                                             &serverHandlers::packet092_RequestPrepareCastleWar,
                                                                                             &serverHandlers::packet093_RequestViewSiegeList,
                                                                                             &serverHandlers::packet094_RequestApproveBattle,
                                                                                             &serverHandlers::packet095_RequestConfirmCastleDefence,
                                                                                             &serverHandlers::packet096_RequestQueryCastleSiegeForRegister,
                                                                                             &serverHandlers::packet097_RequestQueryCastleSiegeForUnregister,
                                                                                             &serverHandlers::packet098_RequestQueryCastleSiegeForInfo,
                                                                                             &serverHandlers::packet099_RequestQueryCastleSiegeForDismiss,
                                                                                             &serverHandlers::packet100_RequestDelPledgeCrest,
                                                                                             &serverHandlers::packet101_RequestModPledgeName,
                                                                                             &serverHandlers::packet102_ResetCastleSiegePledge,
                                                                                             &serverHandlers::packet103_RequestPartyTelBookMarkPacket,
                                                                                             &serverHandlers::packet104_RequestBuilderAccountList,
                                                                                             &serverHandlers::packet105_RequestLoadDoor,
                                                                                             &serverHandlers::packet106_RequestSaveCastleStatus,
                                                                                             &serverHandlers::packet107_RequestSaveDoorStatus,
                                                                                             &serverHandlers::packet108_RequestBBSMakeBoard,
                                                                                             &serverHandlers::packet109_RequestBBSGetBoardList,
                                                                                             &serverHandlers::packet110_RequestBBSModBoard,
                                                                                             &serverHandlers::packet111_RequestBBSDelBoard,
                                                                                             &serverHandlers::packet112_RequestBBSWriteArticle,
                                                                                             &serverHandlers::packet113_RequestBBSReadArticle,
                                                                                             &serverHandlers::packet114_RequestBBSGetArticleList,
                                                                                             &serverHandlers::packet115_RequestBBSReadArticleThread,
                                                                                             &serverHandlers::packet116_RequestBBSGetComment,
                                                                                             &serverHandlers::packet117_RequestBBSReplyForm,
                                                                                             &serverHandlers::packet118_RequestBBSWriteComment,
                                                                                             &serverHandlers::packet119_RequestBBSWriteForm,
                                                                                             &serverHandlers::packet120_RequestBBSSearch,
                                                                                             &serverHandlers::packet121_RequestBBSModifyForm,
                                                                                             &serverHandlers::packet122_RequestBBSModify,
                                                                                             &serverHandlers::packet123_RequestBBSDelete,
                                                                                             &serverHandlers::packet124_RequestLoadWarehouseItemList,
                                                                                             &serverHandlers::packet125_RequestCrystallizeItem,
                                                                                             &serverHandlers::packet126_RequestSaveCastleIncome,
                                                                                             &serverHandlers::packet127_RequestSaveCropData,
                                                                                             &serverHandlers::packet128_RequestDeleteCropData,
                                                                                             &serverHandlers::packet129_RequestInstallAgitDeco,
                                                                                             &serverHandlers::packet130_RequestSavePledgeContribution,
                                                                                             &serverHandlers::packet131_RequestGetContributionRelatedPledge,
                                                                                             &serverHandlers::packet132_RequestSetAgitInfo,
                                                                                             &serverHandlers::packet133_RequestPrivateStoreCommit,
                                                                                             &serverHandlers::packet134_RequestSaveDieDropExp,
                                                                                             &serverHandlers::packet135_RequestBBSGetFavorite,
                                                                                             &serverHandlers::packet136_RequestBBSAddFavorite,
                                                                                             &serverHandlers::packet137_RequestBBSDelFavorite,
                                                                                             &serverHandlers::packet138_RequestResetContribution,
                                                                                             &serverHandlers::packet139_RequestBBSGetAnnounce,
                                                                                             &serverHandlers::packet140_RequestSaveObjectHp,
                                                                                             &serverHandlers::packet141_RequestSaveCastleSiegeElapsedTime,
                                                                                             &serverHandlers::packet142_RequestSaveSkillUse,
                                                                                             &serverHandlers::packet143_RequestLoadPledge,
                                                                                             &serverHandlers::packet144_RequestPing,
                                                                                             &serverHandlers::packet145_RequestPing_OneAdenaDrop,
                                                                                             &serverHandlers::packet146_RequestPing_Network,
                                                                                             &serverHandlers::packet147_RequestSaveAbnormalStatus,
                                                                                             &serverHandlers::packet148_RequestLoadAbnormalStatus,
                                                                                             &serverHandlers::packet149_RequestCreateAllianceByNpc,
                                                                                             &serverHandlers::packet150_RequestJoinAlliance,
                                                                                             &serverHandlers::packet151_RequestDismissAlliance,
                                                                                             &serverHandlers::packet152_RequestOustAllianceMemberPledge,
                                                                                             &serverHandlers::packet153_RequestWithdrawAlliance,
                                                                                             &serverHandlers::packet154_RequestCreatePet,
                                                                                             &serverHandlers::packet155_RequestDeletePet,
                                                                                             &serverHandlers::packet156_RequestWithdrawPet,
                                                                                             &serverHandlers::packet157_RequestLoadPetItems,
                                                                                             &serverHandlers::packet158_RequestDepositPet,
                                                                                             &serverHandlers::packet159_RequestSavePet,
                                                                                             &serverHandlers::packet160_RequestChangePetName,
                                                                                             &serverHandlers::packet161_RequestDismissPet,
                                                                                             &serverHandlers::packet162_RequestPetGetItem,
                                                                                             &serverHandlers::packet163_RequestPetDropItem,
                                                                                             &serverHandlers::packet164_RequestGiveItemToPet,
                                                                                             &serverHandlers::packet165_RequestGetItemFromPet,
                                                                                             &serverHandlers::packet166_RequestPetUseItem,
                                                                                             &serverHandlers::packet167_RequestSetAllianceCrest,
                                                                                             &serverHandlers::packet168_RequestGetAllianceCrest,
                                                                                             &serverHandlers::packet169_RequestDelAllianceCrest,
                                                                                             &serverHandlers::packet170_RequestLoadAllAlliance,
                                                                                             &serverHandlers::packet171_RequestSetAllianceInfo,
                                                                                             &serverHandlers::packet172_RequestGetDbRelatedCounts,
                                                                                             &serverHandlers::packet173_RequestLoadAllPledgeWar,
                                                                                             &serverHandlers::packet174_RequestIncreaseUserPKCount,
                                                                                             &serverHandlers::packet175_RequestIncreaseUserDuelCount,
                                                                                             &serverHandlers::packet176_RequestRecipeMakeItem,
                                                                                             &serverHandlers::packet177_RequestPickItem,
                                                                                             &serverHandlers::packet178_RequestCheckPreviousAllianceWarHistory,
                                                                                             &serverHandlers::packet179_RequestStartAllianceWar,
                                                                                             &serverHandlers::packet180_RequestStopAllianceWar,
                                                                                             &serverHandlers::packet181_RequestSurrenderAllianceWar,
                                                                                             &serverHandlers::packet182_RequestFinishAllianceWar,
                                                                                             &serverHandlers::packet183_RequestLoadAllianceWar,
                                                                                             &serverHandlers::packet184_RequestAllianceWarChallengeRejected,
                                                                                             &serverHandlers::packet185_RequestPackageLoadTargetList,
                                                                                             &serverHandlers::packet186_RequestPackageSendToTarget,
                                                                                             &serverHandlers::packet187_RequestAddBlockList,
                                                                                             &serverHandlers::packet188_RequestDeleteBlockList,
                                                                                             &serverHandlers::packet189_RequestLoadWarehouseItemsEx,
                                                                                             &serverHandlers::packet190_RequestWithdrawWarehouseItemsEx,
                                                                                             &serverHandlers::packet191_RequestDepositWarehouseItemsEx,
                                                                                             &serverHandlers::packet192_RequestSetNextCastleSiege,
                                                                                             &serverHandlers::packet193_RequestCreateAgitAuction,
                                                                                             &serverHandlers::packet194_RequestCreateAgitBid,
                                                                                             &serverHandlers::packet195_RequestSetAgitAuction,
                                                                                             &serverHandlers::packet196_RequestLoadCastleGuard,
                                                                                             &serverHandlers::packet197_RequestLoadAgitBid,
                                                                                             &serverHandlers::packet198_RequestLoadControlTower,
                                                                                             &serverHandlers::packet199_RequestSaveControlTower,
                                                                                             &serverHandlers::packet200_RequestSaveMercenary,
                                                                                             &serverHandlers::packet201_RequestLoadMercenary,
                                                                                             &serverHandlers::packet202_RequestDeleteMercenary,
                                                                                             &serverHandlers::packet203_RequestUpdateMercenary,
                                                                                             &serverHandlers::packet204_RequestAgitPledgeAdena,
                                                                                             &serverHandlers::packet205_RequestCancelAgitAuction,
                                                                                             &serverHandlers::packet206_RequestAgitCost,
                                                                                             &serverHandlers::packet207_RequestShowIntervalAnnounce,
                                                                                             &serverHandlers::packet208_RequestSetIntervalAnnounce,
                                                                                             &serverHandlers::packet209_RequestDelIntervalAnnounce,
                                                                                             &serverHandlers::packet210_RequestDeleteCastleGuard,
                                                                                             &serverHandlers::packet211_RequestAgitAutoSell,
                                                                                             &serverHandlers::packet212_RequestAgitBidCancel,
                                                                                             &serverHandlers::packet213_RequestLoadIntervalAnnounce,
                                                                                             &serverHandlers::packet214_RequestSurrenderPersonally,
                                                                                             &serverHandlers::packet215_RequestEndSiege,
                                                                                             &serverHandlers::packet216_RequestPetiSaveMsgForce,
                                                                                             &serverHandlers::packet217_RequestAdminTool,
                                                                                             &serverHandlers::packet218_RequestLoadLastResidenceTax,
                                                                                             &serverHandlers::packet219_RequestSetLastResidenceTaxUpdate,
                                                                                             &serverHandlers::packet220_RequestMngComment,
                                                                                             &serverHandlers::packet221_RequestLoadPlayTime,
                                                                                             &serverHandlers::packet222_RequestChangeTimeLimit,
                                                                                             &serverHandlers::packet223_RequestSaveUsedTime,
                                                                                             &serverHandlers::packet224_DummyPacket};
