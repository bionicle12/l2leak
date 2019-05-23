#include "l2core/network/packets/ServerToCachePackets.h"

#include <iostream>

// FIXED: custom
std::ostream& operator<<(std::ostream& out, const ServerToCachePackets packetId)
{
    switch (packetId)
    {
        case ServerToCachePacket_CacheVersionPacket:
            return out << "CacheVersionPacket";
        case ServerToCachePacket_LoadCharacterPacket:
            return out << "LoadCharacterPacket";
        case ServerToCachePacket_CreateCharacterPacket:
            return out << "CreateCharacterPacket";
        case ServerToCachePacket_CreateItemPacket:
            return out << "CreateItemPacket";
        case ServerToCachePacket_LoadItemsPacket:
            return out << "LoadItemsPacket";
        case ServerToCachePacket_CreateInitItems:
            return out << "CreateInitItems";
        case ServerToCachePacket_DropItemPacket:
            return out << "DropItemPacket";
        case ServerToCachePacket_GetItemPacket:
            return out << "GetItemPacket";
        case ServerToCachePacket_SaveCharacterPacket:
            return out << "SaveCharacterPacket";
        case ServerToCachePacket_SaveItemsPacket:
            return out << "SaveItemsPacket";
        case ServerToCachePacket_DeleteCharacterPacket:
            return out << "DeleteCharacterPacket";
        case ServerToCachePacket_RequestListBoardPacket:
            return out << "RequestListBoardPacket";
        case ServerToCachePacket_RequestWriteBoardPacket:
            return out << "RequestWriteBoardPacket";
        case ServerToCachePacket_RequestReadBoardPacket:
            return out << "RequestReadBoardPacket";
        case ServerToCachePacket_RequestUpdateUserPledge:
            return out << "RequestUpdateUserPledge";
        case ServerToCachePacket_RequestDeletePledge:
            return out << "RequestDeletePledge";
        case ServerToCachePacket_LoadWarehouseItemsPacket:
            return out << "LoadWarehouseItemsPacket";
        case ServerToCachePacket_WithdrawWarehouseItemsPacket:
            return out << "WithdrawWarehouseItemsPacket";
        case ServerToCachePacket_RequestShortCutInfoPacket:
            return out << "RequestShortCutInfoPacket";
        case ServerToCachePacket_RequestSetShortCutPacket:
            return out << "RequestSetShortCutPacket";
        case ServerToCachePacket_DepositWarehouseItemsPacket:
            return out << "DepositWarehouseItemsPacket";
        case ServerToCachePacket_SellItemsPacket:
            return out << "SellItemsPacket";
        case ServerToCachePacket_BuyItemsPacket:
            return out << "BuyItemsPacket";
        case ServerToCachePacket_GetNewItemPacket:
            return out << "GetNewItemPacket";
        case ServerToCachePacket_UseItemPacket:
            return out << "UseItemPacket";
        case ServerToCachePacket_RequestLoadPledge:
            return out << "RequestLoadPledge";
        case ServerToCachePacket_RequestOpenPledgeList:
            return out << "RequestOpenPledgeList";
        case ServerToCachePacket_RequestCharacterLogin:
            return out << "RequestCharacterLogin";
        case ServerToCachePacket_RequestCharacterLogout:
            return out << "RequestCharacterLogout";
        case ServerToCachePacket_RequestQuestSet:
            return out << "RequestQuestSet";
        case ServerToCachePacket_RequestSetAgitOwner:
            return out << "RequestSetAgitOwner";
        case ServerToCachePacket_RequestSetCastleOwner:
            return out << "RequestSetCastleOwner";
        case ServerToCachePacket_RequestLoadAllCastleData:
            return out << "RequestLoadAllCastleData";
        case ServerToCachePacket_RequestLoadAgit:
            return out << "RequestLoadAgit";
        case ServerToCachePacket_RequestWriteCastleTax:
            return out << "RequestWriteCastleTax";
        case ServerToCachePacket_RequestSetSiegeTime:
            return out << "RequestSetSiegeTime";
        case ServerToCachePacket_RequestManipulateItem:
            return out << "RequestManipulateItem";
        case ServerToCachePacket_RequestOustPledgeMember:
            return out << "RequestOustPledgeMember";
        case ServerToCachePacket_RequestTrade:
            return out << "RequestTrade";
        case ServerToCachePacket_RequestSetPledgeCrest:
            return out << "RequestSetPledgeCrest";
        case ServerToCachePacket_RequestStartPledgeWar:
            return out << "RequestStartPledgeWar";
        case ServerToCachePacket_RequestStopPledgeWar:
            return out << "RequestStopPledgeWar";
        case ServerToCachePacket_RequestSurrenderPledgeWar:
            return out << "RequestSurrenderPledgeWar";
        case ServerToCachePacket_RequestSetUserNickname:
            return out << "RequestSetUserNickname";
        case ServerToCachePacket_RequestAquireSkill:
            return out << "RequestAquireSkill";
        case ServerToCachePacket_RequestTGSBoardPacket:
            return out << "RequestTGSBoardPacket";
        case ServerToCachePacket_RequestDestroyItem:
            return out << "RequestDestroyItem";
        case ServerToCachePacket_RequestEnchantItem:
            return out << "RequestEnchantItem";
        case ServerToCachePacket_RequestEnchantItemFail:
            return out << "RequestEnchantItemFail";
        case ServerToCachePacket_RequestSetPrivateBankLimit:
            return out << "RequestSetPrivateBankLimit";
        case ServerToCachePacket_RequestInitBoardPacket:
            return out << "RequestInitBoardPacket";
        case ServerToCachePacket_RequestCheckCachedPacket:
            return out << "RequestCheckCachedPacket";
        case ServerToCachePacket_RequestLoadSkill:
            return out << "RequestLoadSkill";
        case ServerToCachePacket_RequestAddBookMarkPacket:
            return out << "RequestAddBookMarkPacket";
        case ServerToCachePacket_RequestDelBookMarkPacket:
            return out << "RequestDelBookMarkPacket";
        case ServerToCachePacket_RequestTelBookMarkPacket:
            return out << "RequestTelBookMarkPacket";
        case ServerToCachePacket_RequestGetBookMarkPacket:
            return out << "RequestGetBookMarkPacket";
        case ServerToCachePacket_RequestLoadFriendList:
            return out << "RequestLoadFriendList";
        case ServerToCachePacket_RequestEstablishFriendship:
            return out << "RequestEstablishFriendship";
        case ServerToCachePacket_RequestBreakFriendship:
            return out << "RequestBreakFriendship";
        case ServerToCachePacket_RequestChangeItemData:
            return out << "RequestChangeItemData";
        case ServerToCachePacket_SetPunishPacket:
            return out << "SetPunishPacket";
        case ServerToCachePacket_GetPunishPacket:
            return out << "GetPunishPacket";
        case ServerToCachePacket_ChangePosPacket:
            return out << "ChangePosPacket";
        case ServerToCachePacket_GetLoginAnnouncePacket:
            return out << "GetLoginAnnouncePacket";
        case ServerToCachePacket_SetLoginAnnouncePacket:
            return out << "SetLoginAnnouncePacket";
        case ServerToCachePacket_DelLoginAnnouncePacket:
            return out << "DelLoginAnnouncePacket";
        case ServerToCachePacket_SetBuilderPacket:
            return out << "SetBuilderPacket";
        case ServerToCachePacket_LoadSelectedCharacter:
            return out << "LoadSelectedCharacter";
        case ServerToCachePacket_RequestDeleteSkill:
            return out << "RequestDeleteSkill";
        case ServerToCachePacket_RequestRestoreCharacter:
            return out << "RequestRestoreCharacter";
        case ServerToCachePacket_RequestSetPledgeInfo:
            return out << "RequestSetPledgeInfo";
        case ServerToCachePacket_RequestPledgeExtendedInfo:
            return out << "RequestPledgeExtendedInfo";
        case ServerToCachePacket_RequestGetPledgeCrest:
            return out << "RequestGetPledgeCrest";
        case ServerToCachePacket_RequestFinishPledgeWar:
            return out << "RequestFinishPledgeWar";
        case ServerToCachePacket_RequestLoadPledgeWar:
            return out << "RequestLoadPledgeWar";
        case ServerToCachePacket_RequestCreatePledge:
            return out << "RequestCreatePledge";
        case ServerToCachePacket_RequestDeletePledgeByTimer:
            return out << "RequestDeletePledgeByTimer";
        case ServerToCachePacket_RequestReserveDismissPenalty:
            return out << "RequestReserveDismissPenalty";
        case ServerToCachePacket_RequestLoadDismissReservedPledge:
            return out << "RequestLoadDismissReservedPledge";
        case ServerToCachePacket_RequestCheckPreviousWarHistory:
            return out << "RequestCheckPreviousWarHistory";
        case ServerToCachePacket_RequestPetiGetCharList:
            return out << "RequestPetiGetCharList";
        case ServerToCachePacket_RequestPetiSaveMsg:
            return out << "RequestPetiSaveMsg";
        case ServerToCachePacket_RequestSetUserPledgeInfo:
            return out << "RequestSetUserPledgeInfo";
        case ServerToCachePacket_RequestLogCharInfo:
            return out << "RequestLogCharInfo";
        case ServerToCachePacket_RequestChallengeRejected:
            return out << "RequestChallengeRejected";
        case ServerToCachePacket_RequestResetUserNickname:
            return out << "RequestResetUserNickname";
        case ServerToCachePacket_RequestManageBattleCamp:
            return out << "RequestManageBattleCamp";
        case ServerToCachePacket_RequestLoadBattleCamp:
            return out << "RequestLoadBattleCamp";
        case ServerToCachePacket_RequestPrepareCastleWar:
            return out << "RequestPrepareCastleWar";
        case ServerToCachePacket_RequestViewSiegeList:
            return out << "RequestViewSiegeList";
        case ServerToCachePacket_RequestApproveBattle:
            return out << "RequestApproveBattle";
        case ServerToCachePacket_RequestConfirmCastleDefence:
            return out << "RequestConfirmCastleDefence";
        case ServerToCachePacket_RequestQueryCastleSiegeForRegister:
            return out << "RequestQueryCastleSiegeForRegister";
        case ServerToCachePacket_RequestQueryCastleSiegeForUnregister:
            return out << "RequestQueryCastleSiegeForUnregister";
        case ServerToCachePacket_RequestQueryCastleSiegeForInfo:
            return out << "RequestQueryCastleSiegeForInfo";
        case ServerToCachePacket_RequestQueryCastleSiegeForDismiss:
            return out << "RequestQueryCastleSiegeForDismiss";
        case ServerToCachePacket_RequestDelPledgeCrest:
            return out << "RequestDelPledgeCrest";
        case ServerToCachePacket_RequestModPledgeName:
            return out << "RequestModPledgeName";
        case ServerToCachePacket_ResetCastleSiegePledge:
            return out << "ResetCastleSiegePledge";
        case ServerToCachePacket_RequestPartyTelBookMarkPacket:
            return out << "RequestPartyTelBookMarkPacket";
        case ServerToCachePacket_RequestBuilderAccountList:
            return out << "RequestBuilderAccountList";
        case ServerToCachePacket_RequestLoadDoor:
            return out << "RequestLoadDoor";
        case ServerToCachePacket_RequestSaveCastleStatus:
            return out << "RequestSaveCastleStatus";
        case ServerToCachePacket_RequestSaveDoorStatus:
            return out << "RequestSaveDoorStatus";
        case ServerToCachePacket_RequestBBSMakeBoard:
            return out << "RequestBBSMakeBoard";
        case ServerToCachePacket_RequestBBSGetBoardList:
            return out << "RequestBBSGetBoardList";
        case ServerToCachePacket_RequestBBSModBoard:
            return out << "RequestBBSModBoard";
        case ServerToCachePacket_RequestBBSDelBoard:
            return out << "RequestBBSDelBoard";
        case ServerToCachePacket_RequestBBSWriteArticle:
            return out << "RequestBBSWriteArticle";
        case ServerToCachePacket_RequestBBSReadArticle:
            return out << "RequestBBSReadArticle";
        case ServerToCachePacket_RequestBBSGetArticleList:
            return out << "RequestBBSGetArticleList";
        case ServerToCachePacket_RequestBBSReadArticleThread:
            return out << "RequestBBSReadArticleThread";
        case ServerToCachePacket_RequestBBSGetComment:
            return out << "RequestBBSGetComment";
        case ServerToCachePacket_RequestBBSReplyForm:
            return out << "RequestBBSReplyForm";
        case ServerToCachePacket_RequestBBSWriteComment:
            return out << "RequestBBSWriteComment";
        case ServerToCachePacket_RequestBBSWriteForm:
            return out << "RequestBBSWriteForm";
        case ServerToCachePacket_RequestBBSSearch:
            return out << "RequestBBSSearch";
        case ServerToCachePacket_RequestBBSModifyForm:
            return out << "RequestBBSModifyForm";
        case ServerToCachePacket_RequestBBSModify:
            return out << "RequestBBSModify";
        case ServerToCachePacket_RequestBBSDelete:
            return out << "RequestBBSDelete";
        case ServerToCachePacket_RequestLoadWarehouseItemList:
            return out << "RequestLoadWarehouseItemList";
        case ServerToCachePacket_RequestCrystallizeItem:
            return out << "RequestCrystallizeItem";
        case ServerToCachePacket_RequestSaveCastleIncome:
            return out << "RequestSaveCastleIncome";
        case ServerToCachePacket_RequestSaveCropData:
            return out << "RequestSaveCropData";
        case ServerToCachePacket_RequestDeleteCropData:
            return out << "RequestDeleteCropData";
        case ServerToCachePacket_RequestInstallAgitDeco:
            return out << "RequestInstallAgitDeco";
        case ServerToCachePacket_RequestSavePledgeContribution:
            return out << "RequestSavePledgeContribution";
        case ServerToCachePacket_RequestGetContributionRelatedPledge:
            return out << "RequestGetContributionRelatedPledge";
        case ServerToCachePacket_RequestSetAgitInfo:
            return out << "RequestSetAgitInfo";
        case ServerToCachePacket_RequestPrivateStoreCommit:
            return out << "RequestPrivateStoreCommit";
        case ServerToCachePacket_RequestSaveDieDropExp:
            return out << "RequestSaveDieDropExp";
        case ServerToCachePacket_RequestBBSGetFavorite:
            return out << "RequestBBSGetFavorite";
        case ServerToCachePacket_RequestBBSAddFavorite:
            return out << "RequestBBSAddFavorite";
        case ServerToCachePacket_RequestBBSDelFavorite:
            return out << "RequestBBSDelFavorite";
        case ServerToCachePacket_RequestResetContribution:
            return out << "RequestResetContribution";
        case ServerToCachePacket_RequestBBSGetAnnounce:
            return out << "RequestBBSGetAnnounce";
        case ServerToCachePacket_RequestSaveObjectHp:
            return out << "RequestSaveObjectHp";
        case ServerToCachePacket_RequestSaveCastleSiegeElapsedTime:
            return out << "RequestSaveCastleSiegeElapsedTime";
        case ServerToCachePacket_RequestSaveSkillUse:
            return out << "RequestSaveSkillUse";
        case ServerToCachePacket_RequestLoadPledge2:
            return out << "RequestLoadPledge2";
        case ServerToCachePacket_RequestPing:
            return out << "RequestPing";
        case ServerToCachePacket_RequestPing_OneAdenaDrop:
            return out << "RequestPing_OneAdenaDrop";
        case ServerToCachePacket_RequestPing_Network:
            return out << "RequestPing_Network";
        case ServerToCachePacket_RequestSaveAbnormalStatus:
            return out << "RequestSaveAbnormalStatus";
        case ServerToCachePacket_RequestLoadAbnormalStatus:
            return out << "RequestLoadAbnormalStatus";
        case ServerToCachePacket_RequestCreateAllianceByNpc:
            return out << "RequestCreateAllianceByNpc";
        case ServerToCachePacket_RequestJoinAlliance:
            return out << "RequestJoinAlliance";
        case ServerToCachePacket_RequestDismissAlliance:
            return out << "RequestDismissAlliance";
        case ServerToCachePacket_RequestOustAllianceMemberPledge:
            return out << "RequestOustAllianceMemberPledge";
        case ServerToCachePacket_RequestWithdrawAlliance:
            return out << "RequestWithdrawAlliance";
        case ServerToCachePacket_RequestCreatePet:
            return out << "RequestCreatePet";
        case ServerToCachePacket_RequestDeletePet:
            return out << "RequestDeletePet";
        case ServerToCachePacket_RequestWithdrawPet:
            return out << "RequestWithdrawPet";
        case ServerToCachePacket_RequestLoadPetItems:
            return out << "RequestLoadPetItems";
        case ServerToCachePacket_RequestDepositPet:
            return out << "RequestDepositPet";
        case ServerToCachePacket_RequestSavePet:
            return out << "RequestSavePet";
        case ServerToCachePacket_RequestChangePetName:
            return out << "RequestChangePetName";
        case ServerToCachePacket_RequestDismissPet:
            return out << "RequestDismissPet";
        case ServerToCachePacket_RequestPetGetItem:
            return out << "RequestPetGetItem";
        case ServerToCachePacket_RequestPetDropItem:
            return out << "RequestPetDropItem";
        case ServerToCachePacket_RequestGiveItemToPet:
            return out << "RequestGiveItemToPet";
        case ServerToCachePacket_RequestGetItemFromPet:
            return out << "RequestGetItemFromPet";
        case ServerToCachePacket_RequestPetUseItem:
            return out << "RequestPetUseItem";
        case ServerToCachePacket_RequestSetAllianceCrest:
            return out << "RequestSetAllianceCrest";
        case ServerToCachePacket_RequestGetAllianceCrest:
            return out << "RequestGetAllianceCrest";
        case ServerToCachePacket_RequestDelAllianceCrest:
            return out << "RequestDelAllianceCrest";
        case ServerToCachePacket_RequestLoadAllAlliance:
            return out << "RequestLoadAllAlliance";
        case ServerToCachePacket_RequestSetAllianceInfo:
            return out << "RequestSetAllianceInfo";
        case ServerToCachePacket_RequestGetDbRelatedCounts:
            return out << "RequestGetDbRelatedCounts";
        case ServerToCachePacket_RequestLoadAllPledgeWar:
            return out << "RequestLoadAllPledgeWar";
        case ServerToCachePacket_RequestIncreaseUserPKCount:
            return out << "RequestIncreaseUserPKCount";
        case ServerToCachePacket_RequestIncreaseUserDuelCount:
            return out << "RequestIncreaseUserDuelCount";
        case ServerToCachePacket_RequestRecipeMakeItem:
            return out << "RequestRecipeMakeItem";
        case ServerToCachePacket_RequestPickItem:
            return out << "RequestPickItem";
        case ServerToCachePacket_RequestCheckPreviousAllianceWarHistory:
            return out << "RequestCheckPreviousAllianceWarHistory";
        case ServerToCachePacket_RequestStartAllianceWar:
            return out << "RequestStartAllianceWar";
        case ServerToCachePacket_RequestStopAllianceWar:
            return out << "RequestStopAllianceWar";
        case ServerToCachePacket_RequestSurrenderAllianceWar:
            return out << "RequestSurrenderAllianceWar";
        case ServerToCachePacket_RequestFinishAllianceWar:
            return out << "RequestFinishAllianceWar";
        case ServerToCachePacket_RequestLoadAllianceWar:
            return out << "RequestLoadAllianceWar";
        case ServerToCachePacket_RequestAllianceWarChallengeRejected:
            return out << "RequestAllianceWarChallengeRejected";
        case ServerToCachePacket_RequestPackageLoadTargetList:
            return out << "RequestPackageLoadTargetList";
        case ServerToCachePacket_RequestPackageSendToTarget:
            return out << "RequestPackageSendToTarget";
        case ServerToCachePacket_RequestAddBlockList:
            return out << "RequestAddBlockList";
        case ServerToCachePacket_RequestDeleteBlockList:
            return out << "RequestDeleteBlockList";
        case ServerToCachePacket_RequestLoadWarehouseItemsEx:
            return out << "RequestLoadWarehouseItemsEx";
        case ServerToCachePacket_RequestWithdrawWarehouseItemsEx:
            return out << "RequestWithdrawWarehouseItemsEx";
        case ServerToCachePacket_RequestDepositWarehouseItemsEx:
            return out << "RequestDepositWarehouseItemsEx";
        case ServerToCachePacket_RequestSetNextCastleSiege:
            return out << "RequestSetNextCastleSiege";
        case ServerToCachePacket_RequestCreateAgitAuction:
            return out << "RequestCreateAgitAuction";
        case ServerToCachePacket_RequestCreateAgitBid:
            return out << "RequestCreateAgitBid";
        case ServerToCachePacket_RequestSetAgitAuction:
            return out << "RequestSetAgitAuction";
        case ServerToCachePacket_RequestLoadCastleGuard:
            return out << "RequestLoadCastleGuard";
        case ServerToCachePacket_RequestLoadAgitBid:
            return out << "RequestLoadAgitBid";
        case ServerToCachePacket_RequestLoadControlTower:
            return out << "RequestLoadControlTower";
        case ServerToCachePacket_RequestSaveControlTower:
            return out << "RequestSaveControlTower";
        case ServerToCachePacket_RequestSaveMercenary:
            return out << "RequestSaveMercenary";
        case ServerToCachePacket_RequestLoadMercenary:
            return out << "RequestLoadMercenary";
        case ServerToCachePacket_RequestDeleteMercenary:
            return out << "RequestDeleteMercenary";
        case ServerToCachePacket_RequestUpdateMercenary:
            return out << "RequestUpdateMercenary";
        case ServerToCachePacket_RequestAgitPledgeAdena:
            return out << "RequestAgitPledgeAdena";
        case ServerToCachePacket_RequestCancelAgitAuction:
            return out << "RequestCancelAgitAuction";
        case ServerToCachePacket_RequestAgitCost:
            return out << "RequestAgitCost";
        case ServerToCachePacket_RequestShowIntervalAnnounce:
            return out << "RequestShowIntervalAnnounce";
        case ServerToCachePacket_RequestSetIntervalAnnounce:
            return out << "RequestSetIntervalAnnounce";
        case ServerToCachePacket_RequestDelIntervalAnnounce:
            return out << "RequestDelIntervalAnnounce";
        case ServerToCachePacket_RequestDeleteCastleGuard:
            return out << "RequestDeleteCastleGuard";
        case ServerToCachePacket_RequestAgitAutoSell:
            return out << "RequestAgitAutoSell";
        case ServerToCachePacket_RequestAgitBidCancel:
            return out << "RequestAgitBidCancel";
        case ServerToCachePacket_RequestLoadIntervalAnnounce:
            return out << "RequestLoadIntervalAnnounce";
        case ServerToCachePacket_RequestSurrenderPersonally:
            return out << "RequestSurrenderPersonally";
        case ServerToCachePacket_RequestEndSiege:
            return out << "RequestEndSiege";
        case ServerToCachePacket_RequestPetiSaveMsgForce:
            return out << "RequestPetiSaveMsgForce";
        case ServerToCachePacket_RequestAdminTool:
            return out << "RequestAdminTool";
        case ServerToCachePacket_RequestLoadLastResidenceTax:
            return out << "RequestLoadLastResidenceTax";
        case ServerToCachePacket_RequestSetLastResidenceTaxUpdate:
            return out << "RequestSetLastResidenceTaxUpdate";
        case ServerToCachePacket_RequestMngComment:
            return out << "RequestMngComment";
        case ServerToCachePacket_RequestLoadPlayTime:
            return out << "RequestLoadPlayTime";
        case ServerToCachePacket_RequestChangeTimeLimit:
            return out << "RequestChangeTimeLimit";
        case ServerToCachePacket_RequestSaveUsedTime:
            return out << "RequestSaveUsedTime";
        case ServerToCachePacket_DummyPacket:
            return out << "DummyPacket";
    }

    return out << "INVALID PACKET ID " << (int)packetId;
}
