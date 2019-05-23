if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[DB_BACKUP]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[DB_BACKUP]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[LIN_MakeNewBlankItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[LIN_MakeNewBlankItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Lin_EnchantItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[Lin_EnchantItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Lin_GetSummary]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[Lin_GetSummary]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TranLogBackup]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[TranLogBackup]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[dp_GetItemListByAccount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[dp_GetItemListByAccount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[dp_GetItemListByPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[dp_GetItemListByPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[dp_GetItemListByUserID]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[dp_GetItemListByUserID]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[dp_adena_rank]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[dp_adena_rank]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddBlockList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddBlockList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddBookMark]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddBookMark]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddProhibit]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddProhibit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddUserLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddUserLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AdenaChange]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AdenaChange]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AllianceWarChallengeRejected]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AllianceWarChallengeRejected]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AmountChange]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AmountChange]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ApproveBattle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ApproveBattle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_BetaAddItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_BetaAddItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_BreakFriendship]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_BreakFriendship]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CancelAgitAuction]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CancelAgitAuction]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ChallengeRejected]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ChallengeRejected]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ChangeCharacterLocation]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ChangeCharacterLocation]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ChangeCharacterName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ChangeCharacterName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ChangeTimeData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ChangeTimeData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CharLogin]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CharLogin]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CharLogout]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CharLogout]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CheckPetName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CheckPetName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CheckPreviousAllianceWarHistory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CheckPreviousAllianceWarHistory]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CheckPreviousWarHistory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CheckPreviousWarHistory]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CheckReserved]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CheckReserved]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CleanUpGhostData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CleanUpGhostData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CommentDelete]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CommentDelete]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CommentSearch]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CommentSearch]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CommentWrite]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CommentWrite]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateActiveSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateActiveSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateAgitAuction]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateAgitAuction]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateAgitBid]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateAgitBid]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateAgitIfNotExist]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateAgitIfNotExist]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateAlliance]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateAlliance]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateCastle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateCastle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateChar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateChar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateDoorDataIfNotExist]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateDoorDataIfNotExist]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreateItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreateItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreatePet]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreatePet]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CreatePledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CreatePledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelAquireSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelAquireSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelBookMark]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelBookMark]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelIntervalAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelIntervalAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelLoginAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelLoginAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelPledgeCrest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelPledgeCrest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelProhibit]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelProhibit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteAgitBid]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteAgitBid]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteAllResidenceGuard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteAllResidenceGuard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteBBSBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteBBSBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteBlockList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteBlockList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteCastleIncome]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteCastleIncome]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteChar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteChar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteCharClearPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteCharClearPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteFriends]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteFriends]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteMasterRelatedCastleWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteMasterRelatedCastleWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteMercenary]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteMercenary]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteNotOwnedItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteNotOwnedItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeletePet]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeletePet]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeletePledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeletePledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeletePledgeContribution]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeletePledgeContribution]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteResidenceGuard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteResidenceGuard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DeleteSurrenderWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DeleteSurrenderWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DepositBank]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DepositBank]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DisableChar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DisableChar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DismissAlliance]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DismissAlliance]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DropItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DropItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_EnableChar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_EnableChar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_Err]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_Err]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_Err2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_Err2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ErrItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ErrItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_EstablishFriendship]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_EstablishFriendship]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_FinishPledgeWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_FinishPledgeWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_FlushItemName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_FlushItemName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_FlushQuestName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_FlushQuestName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_FlushSkillName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_FlushSkillName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAgitAdena]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAgitAdena]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAgitBid]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAgitBid]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAgitBidOne]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAgitBidOne]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAllCastleSiege]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAllCastleSiege]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAllMemberPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAllMemberPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAquireSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAquireSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBBSBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBBSBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBbsTGSList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBbsTGSList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBbsallList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBbsallList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBookMark]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBookMark]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBuilderAccount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBuilderAccount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetCharByAccountId]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetCharByAccountId]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetContributionRelatedPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetContributionRelatedPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetContributionWinnerPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetContributionWinnerPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetDBIDByCharName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetDBIDByCharName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetDbRelatedCounts]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetDbRelatedCounts]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetDefaultBuilder]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetDefaultBuilder]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetInitBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetInitBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetIntervalAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetIntervalAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetItemAmount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetItemAmount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetItemData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetItemData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetItemType]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetItemType]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetListBookMark]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetListBookMark]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetLoginAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetLoginAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetPetitionMsg]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetPetitionMsg]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetPledgeAdena ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetPledgeAdena ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetPunish]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetPunish]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetRelatedCastleSiege]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetRelatedCastleSiege]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetShortCut]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetShortCut]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetSiegeRelatedAlliancePledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetSiegeRelatedAlliancePledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetSurrenderWarId]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetSurrenderWarId]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetUserDataByCharId]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetUserDataByCharId]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetUserDataByCharName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetUserDataByCharName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetUserLogTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetUserLogTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InitPledgeCrest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InitPledgeCrest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertAgitAdena]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertAgitAdena]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertIntoControlTower]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertIntoControlTower]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertIntoMercenary]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertIntoMercenary]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertIntoResidenceGuard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertIntoResidenceGuard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertItemName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertItemName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertQuestName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertQuestName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertSkillName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertSkillName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertUserHistory]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertUserHistory]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InsertUserLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InsertUserLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InstallBattleCamp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InstallBattleCamp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_JoinAlliance]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_JoinAlliance]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_JoinPledgeMember]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_JoinPledgeMember]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAccount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAccount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAgit]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAgit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllAgit]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllAgit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllAllianceId]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllAllianceId]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllAllianceWarData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllAllianceWarData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllCastle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllCastle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllWarData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllWarData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAlliance]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAlliance]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadAllianceWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadAllianceWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadBlockList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadBlockList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadBuilderAccountByAccountName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadBuilderAccountByAccountName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadCastle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadCastle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadCastleCrop]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadCastleCrop]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadCastleWarRelatedPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadCastleWarRelatedPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadControlTowerByName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadControlTowerByName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadControlTowerByResidenceId]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadControlTowerByResidenceId]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadDayUsedTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadDayUsedTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadDismissReservedPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadDismissReservedPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadDoor]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadDoor]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadFriends]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadFriends]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadItemByItemId]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadItemByItemId]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadItems]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadItems]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadLastLogout]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadLastLogout]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadLastTaxUpdate]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadLastTaxUpdate]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadMercenary]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadMercenary]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadNpcBoss]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadNpcBoss]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPet]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPet]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPetItems]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPetItems]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPledgeById]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPledgeById]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPledgeByName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPledgeByName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPledgeCrest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPledgeCrest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPledgeMember]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPledgeMember]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadPledgeWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadPledgeWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadQuest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadQuest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_LoadResidenceGuard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_LoadResidenceGuard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeBBSBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeBBSBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModChar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModChar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModChar2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModChar2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModChar3]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModChar3]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModItemOwner]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModItemOwner]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModifyPledgeName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModifyPledgeName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharCopyChar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharCopyChar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharCopyPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharCopyPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharPlg]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharPlg]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharSvr]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharSvr]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharSvr2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharSvr2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_OustMemberPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_OustMemberPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_OustPledgeMember]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_OustPledgeMember]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ReadBbsTGS]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ReadBbsTGS]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ReadBbsall]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ReadBbsall]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RefreshCharacterByName]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RefreshCharacterByName]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RestoreChar ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RestoreChar ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RestoreChar2 ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RestoreChar2 ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCastleIncome]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCastleIncome]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCastleSiegeElapsedTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCastleSiegeElapsedTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCastleStatus]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCastleStatus]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCharacter]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCharacter]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCharacterPledge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCharacterPledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCharacter_temp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCharacter_temp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCharacter_temp2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCharacter_temp2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveCropData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveCropData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveDoorStatus]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveDoorStatus]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveDropExp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveDropExp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveNpcBoss]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveNpcBoss]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveObjectHp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveObjectHp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SavePet]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SavePet]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SavePledgeContribution]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SavePledgeContribution]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SaveTimeData]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SaveTimeData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SeizeItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SeizeItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetAgitAuction]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetAgitAuction]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetAgitNextCost]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetAgitNextCost]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetAgitOwner2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetAgitOwner2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetAllianceInfo]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetAllianceInfo]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetAquireSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetAquireSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetBuilderAccount ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetBuilderAccount ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetBuilderCharacter]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetBuilderCharacter]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetCastleOwner2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetCastleOwner2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetCharacterDelete]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetCharacterDelete]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetCharacterDeleteRestore]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetCharacterDeleteRestore]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetIntervalAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetIntervalAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetLastTaxUpdate]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetLastTaxUpdate]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetLoginAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetLoginAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetPetitionMsg]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetPetitionMsg]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetPledgeCrest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetPledgeCrest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetPledgeInfo]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetPledgeInfo]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetPunish]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetPunish]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetQuest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetQuest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetShortCut]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetShortCut]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetSiegeTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetSiegeTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetSkillCoolTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetSkillCoolTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetUserBan]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetUserBan]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetUserDataEx]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetUserDataEx]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetUserNickname]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetUserNickname]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_StartAllianceWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_StartAllianceWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_StartPledgeWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_StartPledgeWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_StopAllianceWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_StopAllianceWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_StopPledgeWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_StopPledgeWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SurrenderAllianceWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SurrenderAllianceWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SurrenderPersonally]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SurrenderPersonally]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SurrenderPledgeWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SurrenderPledgeWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_TrasferWarehouseNewAll]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_TrasferWarehouseNewAll]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_TrasferWarehouseNewPartial]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_TrasferWarehouseNewPartial]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UninstallAllBattleCamp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UninstallAllBattleCamp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UninstallBattleCamp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UninstallBattleCamp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateActiveSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateActiveSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateCastle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateCastle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateCastleWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateCastleWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateControlTower]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateControlTower]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateJournal]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateJournal]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateMercenary]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateMercenary]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateNpcBossVariable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateNpcBossVariable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdatePledgeInfo]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdatePledgeInfo]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateUseTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateUseTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateUserItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateUserItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_UpdateWarehouseItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_UpdateWarehouseItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ViewSiegeList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ViewSiegeList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_WithdrawAlliance]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_WithdrawAlliance]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_WithdrawPledgeMember]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_WithdrawPledgeMember]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_WriteCastleTax]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_WriteCastleTax]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_setAgitOwner]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_setAgitOwner]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_setCastleOwner]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_setCastleOwner]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_writeBbsTGS]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_writeBbsTGS]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_writeBbsall]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_writeBbsall]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[spCopyXYZlocForDummy]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[spCopyXYZlocForDummy]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_dbcc]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_dbcc]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_item_acc]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[stat_item_acc]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[table_info]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[table_info]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Alliance]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Alliance]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ItemData]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[ItemData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[PetitionMsg]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[PetitionMsg]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Pledge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Pledge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Pledge_Crest]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Pledge_Crest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Pledge_War]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Pledge_War]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[Quest]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Quest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[QuestData]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[QuestData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[SkillData]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SkillData]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[agit]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[agit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[agit_adena]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[agit_adena]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[agit_auction]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[agit_auction]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[agit_bid]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[agit_bid]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[alliance_war]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[alliance_war]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[bookmark]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[bookmark]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[builder_account]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[builder_account]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[castle]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[castle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[castle_crop]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[castle_crop]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[castle_tax]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[castle_tax]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[castle_war]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[castle_war]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[char_pet]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[char_pet]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[control_tower]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[control_tower]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[door]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[door]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[dt_adena_rank_temp]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[dt_adena_rank_temp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_item_1]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_item_1]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_pet1_9_28]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_pet1_9_28]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_pet1_9_30]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_pet1_9_30]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_pet2_9_28]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_pet2_9_28]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_pet2_9_30]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_pet2_9_30]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_pet_data]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_pet_data]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[err_skill_1 ]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[err_skill_1 ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[event_items]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[event_items]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[item_amount0_backup]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[item_amount0_backup]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[item_classid_normal]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[item_classid_normal]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[item_list]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[item_list]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[login_announce]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[login_announce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[map]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[map]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[mercenary]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[mercenary]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[npc_boss]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[npc_boss]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[npcname]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[npcname]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[object_data]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[object_data]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[pet_data]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[pet_data]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[pet_data2]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[pet_data2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[pet_data_backup]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[pet_data_backup]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[pledge_contribution]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[pledge_contribution]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[point]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[point]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[req_charmove]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[req_charmove]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[req_charmove_old]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[req_charmove_old]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[residence_guard]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[residence_guard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[shortcut_data]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[shortcut_data]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_acc_class]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_acc_class]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_acc_lev]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_acc_lev]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_acc_mlev]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_acc_mlev]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_acc_race]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_acc_race]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_item_cnt]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_item_cnt]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_item_ent]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_item_ent]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_item_ment]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_item_ment]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[stat_item_mincnt]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[stat_item_mincnt]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[temp_account]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[temp_account]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[temp_inv]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[temp_inv]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[temp_pet_inv]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[temp_pet_inv]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[temp_skill]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[temp_skill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[temp_skill2]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[temp_skill2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[time_data]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[time_data]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_ActiveSkill]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_ActiveSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_ban]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_ban]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_blocklist]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_blocklist]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_comment]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_comment]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_data]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_data]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_data_0908]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_data_0908]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_data_ex]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_data_ex]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_data_moved]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_data_moved]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_deleted]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_deleted]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_friend]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_friend]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_history]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_history]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item_]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item_]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item_9_28]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item_9_28]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item_amouint_9_26]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item_amouint_9_26]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item_amouint_9_28]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item_amouint_9_28]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item_err_9_28]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item_err_9_28]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_item_err_9_30]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_item_err_9_30]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_journal]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_journal]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_log]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_log]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_name_reserved]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_name_reserved]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_prohibit]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_prohibit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_prohibit_word]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_prohibit_word]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_punish]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_punish]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_skill]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_skill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_skill_old]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_skill_old]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_surrender]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_surrender]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_warehouse]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_warehouse]
GO

CREATE TABLE [dbo].[Alliance] (
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [master_pledge_id] [int] NOT NULL ,
    [oust_time] [int] NOT NULL ,
    [crest_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[ItemData] (
    [id] [int] NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [desc] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [logdate] [smalldatetime] NOT NULL ,
    [consumetype] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [IsQuest] [tinyint] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[PetitionMsg] (
    [Char_Id] [int] NOT NULL ,
    [msg] [nvarchar] (501) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[Pledge] (
    [pledge_id] [int] IDENTITY (1, 1) NOT NULL ,
    [ruler_id] [int] NOT NULL ,
    [name] [nvarchar] (24) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [alliance_id] [int] NOT NULL ,
    [challenge_time] [int] NOT NULL ,
    [root_name_value] [int] NOT NULL ,
    [now_war_id] [int] NOT NULL ,
    [oust_time] [int] NOT NULL ,
    [skill_level] [smallint] NOT NULL ,
    [castle_id] [int] NOT NULL ,
    [agit_id] [int] NOT NULL ,
    [rank] [int] NOT NULL ,
    [name_value] [int] NOT NULL ,
    [status] [int] NOT NULL ,
    [private_flag] [int] NOT NULL ,
    [crest_id] [int] NOT NULL ,
    [is_guilty] [int] NOT NULL ,
    [dismiss_reserved_time] [int] NOT NULL ,
    [alliance_withdraw_time] [int] NOT NULL ,
    [alliance_dismiss_time] [int] NOT NULL ,
    [alliance_ousted_time] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[Pledge_Crest] (
    [crest_id] [int] IDENTITY (1, 1) NOT NULL ,
    [bitmap_size] [smallint] NOT NULL ,
    [bitmap] [varbinary] (3072) NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[Pledge_War] (
    [begin_time] [int] NOT NULL ,
    [end_time] [int] NULL ,
    [challenger] [int] NOT NULL ,
    [challengee] [int] NOT NULL ,
    [winner] [int] NULL ,
    [status] [tinyint] NOT NULL ,
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [challenger_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [challengee_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [winner_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[Quest] (
    [char_id] [int] NOT NULL ,
    [q1] [int] NOT NULL ,
    [s1] [int] NULL ,
    [q2] [int] NOT NULL ,
    [s2] [int] NOT NULL ,
    [q3] [int] NOT NULL ,
    [s3] [int] NOT NULL ,
    [q4] [int] NOT NULL ,
    [s4] [int] NOT NULL ,
    [q5] [int] NOT NULL ,
    [s5] [int] NOT NULL ,
    [q6] [int] NOT NULL ,
    [s6] [int] NOT NULL ,
    [q7] [int] NOT NULL ,
    [s7] [int] NOT NULL ,
    [q8] [int] NOT NULL ,
    [s8] [int] NOT NULL ,
    [q9] [int] NOT NULL ,
    [s9] [int] NOT NULL ,
    [q10] [int] NOT NULL ,
    [s10] [int] NOT NULL ,
    [q11] [int] NOT NULL ,
    [s11] [int] NOT NULL ,
    [q12] [int] NOT NULL ,
    [s12] [int] NOT NULL ,
    [q13] [int] NOT NULL ,
    [s13] [int] NOT NULL ,
    [q14] [int] NOT NULL ,
    [s14] [int] NOT NULL ,
    [q15] [int] NOT NULL ,
    [s15] [int] NOT NULL ,
    [q16] [int] NOT NULL ,
    [s16] [int] NOT NULL ,
    [j1] [int] NOT NULL ,
    [j2] [int] NOT NULL ,
    [j3] [int] NOT NULL ,
    [j4] [int] NOT NULL ,
    [j5] [int] NOT NULL ,
    [j6] [int] NOT NULL ,
    [j7] [int] NOT NULL ,
    [j8] [int] NOT NULL ,
    [j9] [int] NOT NULL ,
    [j10] [int] NOT NULL ,
    [j11] [int] NOT NULL ,
    [j12] [int] NOT NULL ,
    [j13] [int] NOT NULL ,
    [j14] [int] NOT NULL ,
    [j15] [int] NOT NULL ,
    [j16] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[QuestData] (
    [id] [int] NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [data] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [logdate] [smalldatetime] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[SkillData] (
    [id] [int] NOT NULL ,
    [lev] [smallint] NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [logdate] [smalldatetime] NOT NULL ,
    [skill_desc] [nvarchar] (255) COLLATE Korean_Wansung_CI_AS NULL ,
    [bIsMagic] [tinyint] NULL ,
    [activate_type] [nvarchar] (5) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[agit] (
    [id] [int] NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [pledge_id] [int] NULL ,
    [auction_price] [int] NULL ,
    [auction_date] [int] NULL ,
    [hp_stove] [tinyint] NULL ,
    [mp_flame] [tinyint] NULL ,
    [hatcher] [tinyint] NULL ,
    [hp_stove_expire] [int] NULL ,
    [mp_flame_expire] [int] NULL ,
    [status] [tinyint] NULL ,
    [next_war_time] [int] NULL ,
    [auction_id] [int] NULL ,
    [last_price] [int] NULL ,
    [last_cancel] [int] NULL ,
    [teleport_level] [int] NULL ,
    [teleport_expire] [int] NULL ,
    [next_cost] [int] NULL ,
    [cost_fail] [int] NULL ,
    [tax_rate] [int] NOT NULL ,
    [shop_income] [int] NOT NULL ,
    [tax_rate_to_change] [smallint] NOT NULL ,
    [tax_child_rate] [smallint] NOT NULL ,
    [tax_child_rate_to_change] [smallint] NOT NULL ,
    [shop_income_temp] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[agit_adena] (
    [agit_id] [int] NULL ,
    [pledge_id] [int] NULL ,
    [auction_id] [int] NULL ,
    [reason] [int] NULL ,
    [adena] [int] NULL ,
    [log_id] [int] IDENTITY (1, 1) NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[agit_auction] (
    [agit_id] [int] NULL ,
    [auction_id] [int] IDENTITY (1, 1) NOT NULL ,
    [auction_desc] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL ,
    [min_price] [int] NULL ,
    [accepted_bid] [int] NULL ,
    [auction_time] [int] NULL ,
    [auction_tax] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[agit_bid] (
    [auction_id] [int] NULL ,
    [attend_id] [int] IDENTITY (1, 1) NOT NULL ,
    [attend_price] [int] NULL ,
    [attend_pledge_id] [int] NULL ,
    [attend_date] [datetime] NULL ,
    [attend_time] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[alliance_war] (
    [begin_time] [int] NOT NULL ,
    [end_time] [int] NULL ,
    [challenger] [int] NOT NULL ,
    [challengee] [int] NOT NULL ,
    [winner] [int] NULL ,
    [status] [tinyint] NOT NULL ,
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [challenger_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [challengee_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [winner_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[bookmark] (
    [char_id] [int] NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [world] [int] NULL ,
    [x] [int] NULL ,
    [y] [int] NULL ,
    [z] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[builder_account] (
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [default_builder] [int] NOT NULL ,
    [account_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[castle] (
    [id] [int] NOT NULL ,
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [pledge_id] [int] NOT NULL ,
    [next_war_time] [int] NOT NULL ,
    [tax_rate] [smallint] NOT NULL ,
    [type] [tinyint] NOT NULL ,
    [status] [tinyint] NOT NULL ,
    [crop_income] [int] NOT NULL ,
    [shop_income] [int] NOT NULL ,
    [siege_elapsed_time] [int] NOT NULL ,
    [tax_child_rate] [int] NOT NULL ,
    [shop_income_temp] [int] NOT NULL ,
    [tax_rate_to_change] [smallint] NOT NULL ,
    [tax_child_rate_to_change] [smallint] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[castle_crop] (
    [castle_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [dropRate] [int] NOT NULL ,
    [price] [int] NOT NULL ,
    [level] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[castle_tax] (
    [income_update] [datetime] NOT NULL ,
    [tax_change] [datetime] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[castle_war] (
    [castle_id] [int] NOT NULL ,
    [pledge_id] [int] NOT NULL ,
    [type] [tinyint] NOT NULL ,
    [propose_time] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[char_pet] (
    [char_id] [int] NOT NULL ,
    [pet_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[control_tower] (
    [name] [varchar] (256) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [residence_id] [int] NOT NULL ,
    [control_level] [int] NULL ,
    [hp] [int] NOT NULL ,
    [status] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[door] (
    [name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [hp] [int] NOT NULL ,
    [max_hp] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[dt_adena_rank_temp] (
    [char_id] [int] NOT NULL ,
    [amount] [numeric](18, 0) NOT NULL ,
    [rank] [int] IDENTITY (1, 1) NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_item_1] (
    [etc_num5] [int] NULL ,
    [str_actor] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [actor] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_pet1_9_28] (
    [uiid] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL ,
    [act_time] [datetime] NULL ,
    [log_id] [smallint] NULL ,
    [actor] [int] NULL ,
    [actor_account] [int] NULL ,
    [target] [int] NULL ,
    [target_account] [int] NULL ,
    [location_x] [int] NULL ,
    [location_y] [int] NULL ,
    [location_z] [int] NULL ,
    [etc_str1] [varchar] (200) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str2] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str3] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_num1] [float] NULL ,
    [etc_num2] [float] NULL ,
    [etc_num3] [int] NULL ,
    [etc_num4] [int] NULL ,
    [etc_num5] [int] NULL ,
    [etc_num6] [int] NULL ,
    [etc_num7] [int] NULL ,
    [etc_num8] [int] NULL ,
    [etc_num9] [int] NULL ,
    [etc_num10] [int] NULL ,
    [STR_actor] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_actor_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [item_id] [int] NULL ,
    [iid] [int] NULL ,
    [at] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_pet1_9_30] (
    [uiid] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL ,
    [act_time] [datetime] NULL ,
    [log_id] [smallint] NULL ,
    [actor] [int] NULL ,
    [actor_account] [int] NULL ,
    [target] [int] NULL ,
    [target_account] [int] NULL ,
    [location_x] [int] NULL ,
    [location_y] [int] NULL ,
    [location_z] [int] NULL ,
    [etc_str1] [varchar] (200) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str2] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str3] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_num1] [float] NULL ,
    [etc_num2] [float] NULL ,
    [etc_num3] [int] NULL ,
    [etc_num4] [int] NULL ,
    [etc_num5] [int] NULL ,
    [etc_num6] [int] NULL ,
    [etc_num7] [int] NULL ,
    [etc_num8] [int] NULL ,
    [etc_num9] [int] NULL ,
    [etc_num10] [int] NULL ,
    [STR_actor] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_actor_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [item_id] [int] NULL ,
    [iid] [int] NULL ,
    [at] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_pet2_9_28] (
    [uiid] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL ,
    [act_time] [datetime] NULL ,
    [log_id] [smallint] NULL ,
    [actor] [int] NULL ,
    [actor_account] [int] NULL ,
    [target] [int] NULL ,
    [target_account] [int] NULL ,
    [location_x] [int] NULL ,
    [location_y] [int] NULL ,
    [location_z] [int] NULL ,
    [etc_str1] [varchar] (200) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str2] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str3] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_num1] [float] NULL ,
    [etc_num2] [float] NULL ,
    [etc_num3] [int] NULL ,
    [etc_num4] [int] NULL ,
    [etc_num5] [int] NULL ,
    [etc_num6] [int] NULL ,
    [etc_num7] [int] NULL ,
    [etc_num8] [int] NULL ,
    [etc_num9] [int] NULL ,
    [etc_num10] [int] NULL ,
    [STR_actor] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_actor_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [item_id] [int] NULL ,
    [iid] [int] NULL ,
    [at] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_pet2_9_30] (
    [uiid] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL ,
    [act_time] [datetime] NULL ,
    [log_id] [smallint] NULL ,
    [actor] [int] NULL ,
    [actor_account] [int] NULL ,
    [target] [int] NULL ,
    [target_account] [int] NULL ,
    [location_x] [int] NULL ,
    [location_y] [int] NULL ,
    [location_z] [int] NULL ,
    [etc_str1] [varchar] (200) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str2] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_str3] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [etc_num1] [float] NULL ,
    [etc_num2] [float] NULL ,
    [etc_num3] [int] NULL ,
    [etc_num4] [int] NULL ,
    [etc_num5] [int] NULL ,
    [etc_num6] [int] NULL ,
    [etc_num7] [int] NULL ,
    [etc_num8] [int] NULL ,
    [etc_num9] [int] NULL ,
    [etc_num10] [int] NULL ,
    [STR_actor] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_actor_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target] [varchar] (48) COLLATE Korean_Wansung_CI_AS NULL ,
    [STR_target_account] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [item_id] [int] NULL ,
    [iid] [int] NULL ,
    [at] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_pet_data] (
    [item_id] [int] NULL ,
    [npc_class_id] [int] NULL ,
    [expoint] [int] NULL ,
    [petname] [int] NULL ,
    [hp] [float] NULL ,
    [mp] [float] NULL ,
    [sp] [int] NULL ,
    [meal] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[err_skill_1 ] (
    [class_name] [nvarchar] (255) COLLATE Korean_Wansung_CI_AS NULL ,
    [class] [int] NULL ,
    [lev] [int] NULL ,
    [skill_id] [int] NULL ,
    [skill_name] [nvarchar] (255) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[event_items] (
    [char_id] [int] NULL ,
    [class_id] [int] NULL ,
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [log_date] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[item_amount0_backup] (
    [item_id] [int] NULL ,
    [char_id] [int] NULL ,
    [item_type] [int] NULL ,
    [amount] [int] NULL ,
    [enchant] [int] NULL ,
    [eroded] [int] NULL ,
    [bless] [int] NULL ,
    [ident] [int] NULL ,
    [wished] [int] NULL ,
    [warehouse] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[item_classid_normal] (
    [id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[item_list] (
    [id] [int] NULL ,
    [name] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[login_announce] (
    [announce_id] [int] NOT NULL ,
    [announce_msg] [nvarchar] (256) COLLATE Korean_Wansung_CI_AS NULL ,
    [interval_10] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[map] (
    [map2] [int] NULL ,
    [x2] [int] NULL ,
    [y2] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[mercenary] (
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [residence_id] [int] NOT NULL ,
    [npc_id] [int] NOT NULL ,
    [x] [int] NOT NULL ,
    [y] [int] NOT NULL ,
    [z] [int] NOT NULL ,
    [angle] [int] NOT NULL ,
    [hp] [int] NOT NULL ,
    [mp] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[npc_boss] (
    [npc_db_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [alive] [int] NOT NULL ,
    [hp] [int] NULL ,
    [mp] [int] NULL ,
    [pos_x] [int] NULL ,
    [pos_y] [int] NULL ,
    [pos_z] [int] NULL ,
    [time_low] [int] NULL ,
    [time_high] [int] NULL ,
    [i0] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[npcname] (
    [npc_id] [int] NULL ,
    [npc_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[object_data] (
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [owner_id] [int] NOT NULL ,
    [residence_id] [int] NOT NULL ,
    [max_hp] [int] NOT NULL ,
    [hp] [int] NOT NULL ,
    [x_pos] [int] NOT NULL ,
    [y_pos] [int] NOT NULL ,
    [z_pos] [int] NOT NULL ,
    [type] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[pet_data] (
    [pet_id] [int] NOT NULL ,
    [npc_class_id] [int] NOT NULL ,
    [expoint] [int] NOT NULL ,
    [nick_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [hp] [float] NOT NULL ,
    [mp] [float] NOT NULL ,
    [sp] [int] NOT NULL ,
    [meal] [int] NOT NULL ,
    [slot1] [int] NOT NULL ,
    [slot2] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[pet_data2] (
    [pet_id] [int] NOT NULL ,
    [npc_class_id] [int] NOT NULL ,
    [expoint] [int] NOT NULL ,
    [nick_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [hp] [float] NOT NULL ,
    [mp] [float] NOT NULL ,
    [sp] [int] NOT NULL ,
    [meal] [int] NOT NULL ,
    [slot1] [int] NOT NULL ,
    [slot2] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[pet_data_backup] (
    [pet_id] [int] NOT NULL ,
    [npc_class_id] [int] NOT NULL ,
    [expoint] [int] NOT NULL ,
    [nick_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [hp] [float] NOT NULL ,
    [mp] [float] NOT NULL ,
    [sp] [int] NOT NULL ,
    [meal] [int] NOT NULL ,
    [slot1] [int] NOT NULL ,
    [slot2] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[pledge_contribution] (
    [residence_id] [int] NOT NULL ,
    [pledge_id] [int] NOT NULL ,
    [contribution] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[point] (
    [map] [int] NULL ,
    [align] [int] NULL ,
    [loc] [int] NULL ,
    [x] [int] NULL ,
    [y] [int] NULL ,
    [z] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[req_charmove] (
    [old_char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [old_char_id] [int] NULL ,
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [account_id] [int] NULL ,
    [old_world_id] [int] NULL ,
    [req_date] [datetime] NULL ,
    [req_id] [int] NOT NULL ,
    [new_world_id] [int] NULL ,
    [new_char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [new_char_id] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[req_charmove_old] (
    [old_char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [old_char_id] [int] NULL ,
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [account_id] [int] NULL ,
    [old_world_id] [int] NULL ,
    [req_date] [datetime] NULL ,
    [req_id] [int] IDENTITY (1, 1) NOT NULL ,
    [new_world_id] [int] NULL ,
    [new_char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [new_char_id] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[residence_guard] (
    [residence_id] [int] NOT NULL ,
    [item_id] [int] NOT NULL ,
    [npc_id] [int] NOT NULL ,
    [guard_type] [int] NOT NULL ,
    [can_move] [int] NOT NULL ,
    [x] [int] NOT NULL ,
    [y] [int] NOT NULL ,
    [z] [int] NOT NULL ,
    [angle] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[shortcut_data] (
    [char_id] [int] NOT NULL ,
    [slotnum] [int] NOT NULL ,
    [shortcut_type] [int] NOT NULL ,
    [shortcut_id] [int] NOT NULL ,
    [shortcut_macro] [nvarchar] (256) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_acc_class] (
    [class] [tinyint] NOT NULL ,
    [count] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_acc_lev] (
    [lev] [tinyint] NOT NULL ,
    [count] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_acc_mlev] (
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [lev] [tinyint] NOT NULL ,
    [race] [tinyint] NOT NULL ,
    [class] [tinyint] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_acc_race] (
    [race] [tinyint] NOT NULL ,
    [count] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_item_cnt] (
    [id] [int] NOT NULL ,
    [count] [int] NOT NULL ,
    [sum] [float] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_item_ent] (
    [item_type] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [count] [int] NOT NULL ,
    [sum] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_item_ment] (
    [item_type] [int] NOT NULL ,
    [item_id] [int] NOT NULL ,
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [max_ent] [int] NOT NULL ,
    [builder] [tinyint] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[stat_item_mincnt] (
    [item_type] [int] NOT NULL ,
    [item_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[temp_account] (
    [real_account] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [user_id] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[temp_inv] (
    [item_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [user_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[temp_pet_inv] (
    [pet_item_id] [int] NOT NULL ,
    [pet_item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [pet_collar_id] [int] NOT NULL ,
    [user_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[temp_skill] (
    [char_id] [int] NULL ,
    [skill] [int] NULL ,
    [lev] [int] NULL ,
    [temptime] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[temp_skill2] (
    [char_id] [int] NULL ,
    [skill_id] [int] NULL ,
    [skill_lev] [int] NULL ,
    [temptime] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[time_data] (
    [account_id] [int] NOT NULL ,
    [last_logout] [datetime] NOT NULL ,
    [used_sec] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_ActiveSkill] (
    [char_id] [int] NOT NULL ,
    [s1] [int] NULL ,
    [l1] [tinyint] NULL ,
    [d1] [int] NULL ,
    [s2] [int] NULL ,
    [l2] [tinyint] NULL ,
    [d2] [int] NULL ,
    [s3] [int] NULL ,
    [l3] [tinyint] NULL ,
    [d3] [int] NULL ,
    [s4] [int] NULL ,
    [l4] [tinyint] NULL ,
    [d4] [int] NULL ,
    [s5] [int] NULL ,
    [l5] [tinyint] NULL ,
    [d5] [int] NULL ,
    [s6] [int] NULL ,
    [l6] [tinyint] NULL ,
    [d6] [int] NULL ,
    [s7] [int] NULL ,
    [l7] [tinyint] NULL ,
    [d7] [int] NULL ,
    [s8] [int] NULL ,
    [l8] [tinyint] NULL ,
    [d8] [int] NULL ,
    [s9] [int] NULL ,
    [l9] [tinyint] NULL ,
    [d9] [int] NULL ,
    [s10] [int] NULL ,
    [l10] [tinyint] NULL ,
    [d10] [int] NULL ,
    [s11] [int] NULL ,
    [l11] [tinyint] NULL ,
    [d11] [int] NULL ,
    [s12] [int] NULL ,
    [l12] [tinyint] NULL ,
    [d12] [int] NULL ,
    [s13] [int] NULL ,
    [l13] [tinyint] NULL ,
    [d13] [int] NULL ,
    [s14] [int] NULL ,
    [l14] [tinyint] NULL ,
    [d14] [int] NULL ,
    [s15] [int] NULL ,
    [l15] [tinyint] NULL ,
    [d15] [int] NULL ,
    [s16] [int] NULL ,
    [l16] [tinyint] NULL ,
    [d16] [int] NULL ,
    [s17] [int] NULL ,
    [l17] [tinyint] NULL ,
    [d17] [int] NULL ,
    [s18] [int] NULL ,
    [l18] [tinyint] NULL ,
    [d18] [int] NULL ,
    [s19] [int] NULL ,
    [l19] [tinyint] NULL ,
    [d19] [int] NULL ,
    [s20] [int] NULL ,
    [l20] [tinyint] NULL ,
    [d20] [int] NULL ,
    [c1] [tinyint] NULL ,
    [c2] [tinyint] NULL ,
    [c3] [tinyint] NULL ,
    [c4] [tinyint] NULL ,
    [c5] [tinyint] NULL ,
    [c6] [tinyint] NULL ,
    [c7] [tinyint] NULL ,
    [c8] [tinyint] NULL ,
    [c9] [tinyint] NULL ,
    [c10] [tinyint] NULL ,
    [c11] [tinyint] NULL ,
    [c12] [tinyint] NULL ,
    [c13] [tinyint] NULL ,
    [c14] [tinyint] NULL ,
    [c15] [tinyint] NULL ,
    [c16] [tinyint] NULL ,
    [c17] [tinyint] NULL ,
    [c18] [tinyint] NULL ,
    [c19] [tinyint] NULL ,
    [c20] [tinyint] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_ban] (
    [char_id] [int] NOT NULL ,
    [status] [int] NULL ,
    [ban_date] [datetime] NULL ,
    [ban_hour] [smallint] NULL ,
    [ban_end] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_blocklist] (
    [char_id] [int] NOT NULL ,
    [block_char_id] [int] NOT NULL ,
    [block_char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_comment] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [char_id] [int] NULL ,
    [comment_id] [int] IDENTITY (1, 1) NOT NULL ,
    [comment] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL ,
    [comment_date] [datetime] NULL ,
    [writer] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [deleted] [tinyint] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_data] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [char_id] [int] IDENTITY (1, 1) NOT NULL ,
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [account_id] [int] NOT NULL ,
    [pledge_id] [int] NOT NULL ,
    [builder] [tinyint] NOT NULL ,
    [gender] [tinyint] NOT NULL ,
    [race] [tinyint] NOT NULL ,
    [class] [tinyint] NOT NULL ,
    [world] [smallint] NOT NULL ,
    [xloc] [int] NOT NULL ,
    [yloc] [int] NOT NULL ,
    [zloc] [int] NOT NULL ,
    [IsInVehicle] [smallint] NOT NULL ,
    [HP] [float] NOT NULL ,
    [MP] [float] NOT NULL ,
    [SP] [int] NOT NULL ,
    [Exp] [int] NOT NULL ,
    [Lev] [tinyint] NOT NULL ,
    [align] [int] NOT NULL ,
    [PK] [int] NOT NULL ,
    [PKpardon] [int] NOT NULL ,
    [Duel] [int] NOT NULL ,
    [ST_underware] [int] NOT NULL ,
    [ST_right_ear] [int] NOT NULL ,
    [ST_left_ear] [int] NOT NULL ,
    [ST_neck] [int] NOT NULL ,
    [ST_right_finger] [int] NOT NULL ,
    [ST_left_finger] [int] NOT NULL ,
    [ST_head] [int] NOT NULL ,
    [ST_right_hand] [int] NOT NULL ,
    [ST_left_hand] [int] NOT NULL ,
    [ST_gloves] [int] NOT NULL ,
    [ST_chest] [int] NOT NULL ,
    [ST_legs] [int] NOT NULL ,
    [ST_feet] [int] NOT NULL ,
    [ST_back] [int] NOT NULL ,
    [ST_both_hand] [int] NOT NULL ,
    [create_date] [datetime] NOT NULL ,
    [login] [datetime] NULL ,
    [logout] [datetime] NULL ,
    [quest_flag] [binary] (32) NOT NULL ,
    [nickname] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [power_flag] [binary] (32) NOT NULL ,
    [pledge_dismiss_time] [int] NOT NULL ,
    [pledge_leave_time] [int] NOT NULL ,
    [pledge_leave_status] [tinyint] NOT NULL ,
    [max_hp] [int] NOT NULL ,
    [max_mp] [int] NOT NULL ,
    [quest_memo] [char] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [face_index] [int] NOT NULL ,
    [hair_shape_index] [int] NOT NULL ,
    [hair_color_index] [int] NOT NULL ,
    [use_time] [int] NOT NULL ,
    [temp_delete_date] [smalldatetime] NULL ,
    [pledge_ousted_time] [int] NOT NULL ,
    [pledge_withdraw_time] [int] NOT NULL ,
    [surrender_war_id] [int] NOT NULL ,
    [drop_exp] [int] NOT NULL ,
    [old_x] [int] NULL ,
    [old_y] [int] NULL ,
    [old_z] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_data_0908] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [char_id] [int] IDENTITY (1, 1) NOT NULL ,
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [account_id] [int] NOT NULL ,
    [pledge_id] [int] NOT NULL ,
    [builder] [tinyint] NOT NULL ,
    [gender] [tinyint] NOT NULL ,
    [race] [tinyint] NOT NULL ,
    [class] [tinyint] NOT NULL ,
    [world] [smallint] NOT NULL ,
    [xloc] [int] NOT NULL ,
    [yloc] [int] NOT NULL ,
    [zloc] [int] NOT NULL ,
    [IsInVehicle] [smallint] NOT NULL ,
    [HP] [float] NOT NULL ,
    [MP] [float] NOT NULL ,
    [SP] [int] NOT NULL ,
    [Exp] [int] NOT NULL ,
    [Lev] [tinyint] NOT NULL ,
    [align] [int] NOT NULL ,
    [PK] [int] NOT NULL ,
    [PKpardon] [int] NOT NULL ,
    [Duel] [int] NOT NULL ,
    [ST_underware] [int] NOT NULL ,
    [ST_right_ear] [int] NOT NULL ,
    [ST_left_ear] [int] NOT NULL ,
    [ST_neck] [int] NOT NULL ,
    [ST_right_finger] [int] NOT NULL ,
    [ST_left_finger] [int] NOT NULL ,
    [ST_head] [int] NOT NULL ,
    [ST_right_hand] [int] NOT NULL ,
    [ST_left_hand] [int] NOT NULL ,
    [ST_gloves] [int] NOT NULL ,
    [ST_chest] [int] NOT NULL ,
    [ST_legs] [int] NOT NULL ,
    [ST_feet] [int] NOT NULL ,
    [ST_back] [int] NOT NULL ,
    [ST_both_hand] [int] NOT NULL ,
    [create_date] [datetime] NOT NULL ,
    [login] [datetime] NULL ,
    [logout] [datetime] NULL ,
    [quest_flag] [binary] (32) NOT NULL ,
    [nickname] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [power_flag] [binary] (32) NOT NULL ,
    [pledge_dismiss_time] [int] NOT NULL ,
    [pledge_leave_time] [int] NOT NULL ,
    [pledge_leave_status] [tinyint] NOT NULL ,
    [max_hp] [int] NOT NULL ,
    [max_mp] [int] NOT NULL ,
    [quest_memo] [char] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [face_index] [int] NOT NULL ,
    [hair_shape_index] [int] NOT NULL ,
    [hair_color_index] [int] NOT NULL ,
    [use_time] [int] NOT NULL ,
    [temp_delete_date] [smalldatetime] NULL ,
    [pledge_ousted_time] [int] NOT NULL ,
    [pledge_withdraw_time] [int] NOT NULL ,
    [surrender_war_id] [int] NOT NULL ,
    [drop_exp] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_data_ex] (
    [char_id] [int] NOT NULL ,
    [id] [int] IDENTITY (1, 1) NOT NULL ,
    [dismiss_penalty_reserved] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_data_moved] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [char_id] [int] IDENTITY (1, 1) NOT NULL ,
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [account_id] [int] NOT NULL ,
    [pledge_id] [int] NOT NULL ,
    [builder] [tinyint] NOT NULL ,
    [gender] [tinyint] NOT NULL ,
    [race] [tinyint] NOT NULL ,
    [class] [tinyint] NOT NULL ,
    [world] [smallint] NOT NULL ,
    [xloc] [int] NOT NULL ,
    [yloc] [int] NOT NULL ,
    [zloc] [int] NOT NULL ,
    [IsInVehicle] [smallint] NOT NULL ,
    [HP] [float] NOT NULL ,
    [MP] [float] NOT NULL ,
    [SP] [int] NOT NULL ,
    [Exp] [int] NOT NULL ,
    [Lev] [tinyint] NOT NULL ,
    [align] [int] NOT NULL ,
    [PK] [int] NOT NULL ,
    [PKpardon] [int] NOT NULL ,
    [Duel] [int] NOT NULL ,
    [ST_underware] [int] NOT NULL ,
    [ST_right_ear] [int] NOT NULL ,
    [ST_left_ear] [int] NOT NULL ,
    [ST_neck] [int] NOT NULL ,
    [ST_right_finger] [int] NOT NULL ,
    [ST_left_finger] [int] NOT NULL ,
    [ST_head] [int] NOT NULL ,
    [ST_right_hand] [int] NOT NULL ,
    [ST_left_hand] [int] NOT NULL ,
    [ST_gloves] [int] NOT NULL ,
    [ST_chest] [int] NOT NULL ,
    [ST_legs] [int] NOT NULL ,
    [ST_feet] [int] NOT NULL ,
    [ST_back] [int] NOT NULL ,
    [ST_both_hand] [int] NOT NULL ,
    [create_date] [datetime] NOT NULL ,
    [login] [datetime] NULL ,
    [logout] [datetime] NULL ,
    [quest_flag] [binary] (32) NOT NULL ,
    [nickname] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [power_flag] [binary] (32) NOT NULL ,
    [pledge_dismiss_time] [int] NOT NULL ,
    [pledge_leave_time] [int] NOT NULL ,
    [pledge_leave_status] [tinyint] NOT NULL ,
    [max_hp] [int] NOT NULL ,
    [max_mp] [int] NOT NULL ,
    [quest_memo] [char] (32) COLLATE Korean_Wansung_CI_AS NULL ,
    [face_index] [int] NOT NULL ,
    [hair_shape_index] [int] NOT NULL ,
    [hair_color_index] [int] NOT NULL ,
    [use_time] [int] NOT NULL ,
    [temp_delete_date] [smalldatetime] NULL ,
    [pledge_ousted_time] [int] NOT NULL ,
    [pledge_withdraw_time] [int] NOT NULL ,
    [surrender_war_id] [int] NOT NULL ,
    [drop_exp] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_deleted] (
    [char_id] [int] NOT NULL ,
    [delete_date] [datetime] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_friend] (
    [char_id] [int] NOT NULL ,
    [friend_char_id] [int] NOT NULL ,
    [friend_char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_history] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [char_id] [int] NOT NULL ,
    [log_date] [datetime] NOT NULL ,
    [log_action] [tinyint] NOT NULL ,
    [account_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
    [create_date] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item] (
    [item_id] [int] IDENTITY (1, 1) NOT FOR REPLICATION  NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [int] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL ,
    [old_world_id] [int] NULL ,
    [old_item_id] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item_] (
    [item_id] [int] NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item_9_28] (
    [item_id] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item_amouint_9_26] (
    [item_type] [int] NOT NULL ,
    [item_amount] [money] NOT NULL ,
    [item_count] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item_amouint_9_28] (
    [item_type] [int] NOT NULL ,
    [item_amount] [money] NOT NULL ,
    [item_count] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item_err_9_28] (
    [item_id] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_item_err_9_30] (
    [item_id] [int] IDENTITY (1, 1) NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NOT NULL ,
    [warehouse] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_journal] (
    [char_id] [int] NOT NULL ,
    [type] [smallint] NOT NULL ,
    [int_data_1] [int] NULL ,
    [int_data_2] [int] NULL ,
    [log_data] [smalldatetime] NOT NULL ,
    [play_time] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_log] (
    [char_id] [int] NULL ,
    [log_id] [tinyint] NULL ,
    [log_date] [datetime] NULL ,
    [log_from] [int] NULL ,
    [log_to] [int] NULL ,
    [use_time] [int] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_name_reserved] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL ,
    [account_id] [int] NOT NULL ,
    [used] [tinyint] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_prohibit] (
    [char_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_prohibit_word] (
    [words] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_punish] (
    [char_id] [int] NOT NULL ,
    [punish_id] [int] NOT NULL ,
    [punish_on] [tinyint] NOT NULL ,
    [remain_game] [int] NULL ,
    [remain_real] [int] NULL ,
    [punish_seconds] [int] NULL ,
    [punish_date] [datetime] NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_skill] (
    [char_id] [int] NOT NULL ,
    [skill_id] [int] NOT NULL ,
    [skill_lev] [tinyint] NOT NULL ,
    [to_end_time] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_skill_old] (
    [char_id] [int] NOT NULL ,
    [skill_id] [int] NOT NULL ,
    [skill_lev] [tinyint] NOT NULL ,
    [to_end_time] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_surrender] (
    [char_id] [int] NOT NULL ,
    [surrender_war_id] [int] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_warehouse] (
    [item_id] [int] NOT NULL ,
    [char_id] [int] NOT NULL ,
    [item_type] [int] NOT NULL ,
    [amount] [int] NOT NULL ,
    [enchant] [int] NOT NULL ,
    [eroded] [int] NOT NULL ,
    [bless] [tinyint] NOT NULL ,
    [ident] [tinyint] NOT NULL ,
    [wished] [tinyint] NULL ,
    [warehouse] [int] NOT NULL
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[Alliance] WITH NOCHECK ADD
    CONSTRAINT [PK_Alliance] PRIMARY KEY  CLUSTERED
    (
        [name]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[ItemData] WITH NOCHECK ADD
    CONSTRAINT [PK_ItemData] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[Pledge] WITH NOCHECK ADD
    CONSTRAINT [PK_Pledge] PRIMARY KEY  CLUSTERED
    (
        [pledge_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[Pledge_Crest] WITH NOCHECK ADD
    CONSTRAINT [PK_Pledge_Crest] PRIMARY KEY  CLUSTERED
    (
        [crest_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[Pledge_War] WITH NOCHECK ADD
    CONSTRAINT [PK_Pledge_War] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[SkillData] WITH NOCHECK ADD
    CONSTRAINT [PK_SkillData] PRIMARY KEY  CLUSTERED
    (
        [id],
        [lev]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[agit] WITH NOCHECK ADD
    CONSTRAINT [PK_agit] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[alliance_war] WITH NOCHECK ADD
     PRIMARY KEY  CLUSTERED
    (
        [id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[builder_account] WITH NOCHECK ADD
    CONSTRAINT [PK_account_builder] PRIMARY KEY  CLUSTERED
    (
        [account_name]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[castle] WITH NOCHECK ADD
    CONSTRAINT [PK_castle] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[castle_crop] WITH NOCHECK ADD
    CONSTRAINT [PK_castle_crop] PRIMARY KEY  CLUSTERED
    (
        [castle_id],
        [item_type]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[control_tower] WITH NOCHECK ADD
     PRIMARY KEY  CLUSTERED
    (
        [name]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[door] WITH NOCHECK ADD
    CONSTRAINT [PK_door] PRIMARY KEY  CLUSTERED
    (
        [name]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[item_classid_normal] WITH NOCHECK ADD
    CONSTRAINT [PK_item_classid_normal] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[object_data] WITH NOCHECK ADD
    CONSTRAINT [PK_object_data] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[pet_data] WITH NOCHECK ADD
    CONSTRAINT [PK_pet_data] PRIMARY KEY  CLUSTERED
    (
        [pet_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[pledge_contribution] WITH NOCHECK ADD
    CONSTRAINT [PK_pledge_contribution] PRIMARY KEY  CLUSTERED
    (
        [residence_id],
        [pledge_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[residence_guard] WITH NOCHECK ADD
    CONSTRAINT [pk_residence_guard] PRIMARY KEY  CLUSTERED
    (
        [x],
        [y],
        [z]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[shortcut_data] WITH NOCHECK ADD
    CONSTRAINT [PK_shortcut_data] PRIMARY KEY  CLUSTERED
    (
        [char_id],
        [slotnum]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[time_data] WITH NOCHECK ADD
    CONSTRAINT [PK_char_data2] PRIMARY KEY  CLUSTERED
    (
        [account_id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_ban] WITH NOCHECK ADD
    CONSTRAINT [PK_user_ban] PRIMARY KEY  CLUSTERED
    (
        [char_id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_blocklist] WITH NOCHECK ADD
    CONSTRAINT [PK_user_blocklist] PRIMARY KEY  CLUSTERED
    (
        [char_id],
        [block_char_id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_data] WITH NOCHECK ADD
    CONSTRAINT [PK_user_data] PRIMARY KEY  CLUSTERED
    (
        [char_id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_data_ex] WITH NOCHECK ADD
    CONSTRAINT [PK_user_data_ex] PRIMARY KEY  CLUSTERED
    (
        [id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_friend] WITH NOCHECK ADD
    CONSTRAINT [PK_user_friend] PRIMARY KEY  CLUSTERED
    (
        [char_id],
        [friend_char_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_name_reserved] WITH NOCHECK ADD
    CONSTRAINT [PK_user_name_reserved] PRIMARY KEY  CLUSTERED
    (
        [char_name]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_prohibit] WITH NOCHECK ADD
    CONSTRAINT [PK_user_prohibit] PRIMARY KEY  CLUSTERED
    (
        [char_name]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_prohibit_word] WITH NOCHECK ADD
    CONSTRAINT [PK_user_prohibit_word] PRIMARY KEY  CLUSTERED
    (
        [words]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

 CREATE  CLUSTERED  INDEX [IX_user_comment] ON [dbo].[user_comment]([char_id], [deleted], [comment_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  CLUSTERED  INDEX [idx_user_item_charid] ON [dbo].[user_item]([char_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  CLUSTERED  INDEX [IX_user_log] ON [dbo].[user_log]([char_id], [log_id], [log_to]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

ALTER TABLE [dbo].[Alliance] WITH NOCHECK ADD
    CONSTRAINT [DF__alliance__master__2B6A5820] DEFAULT (0) FOR [master_pledge_id],
    CONSTRAINT [DF__alliance__oust_t__2C5E7C59] DEFAULT (0) FOR [oust_time],
    CONSTRAINT [DF__alliance__crest___443605EA] DEFAULT (0) FOR [crest_id]
GO

ALTER TABLE [dbo].[ItemData] WITH NOCHECK ADD
    CONSTRAINT [DF_ItemData_date] DEFAULT (getdate()) FOR [logdate],
    CONSTRAINT [DF_ItemData_IsQuest] DEFAULT (0) FOR [IsQuest]
GO

ALTER TABLE [dbo].[Pledge] WITH NOCHECK ADD
    CONSTRAINT [DF_Pledge_alliance_id] DEFAULT (0) FOR [alliance_id],
    CONSTRAINT [DF_Pledge_challenge_time] DEFAULT (0) FOR [challenge_time],
    CONSTRAINT [DF_Pledge_name_value] DEFAULT (0) FOR [root_name_value],
    CONSTRAINT [DF_Pledge_now_war_id] DEFAULT (0) FOR [now_war_id],
    CONSTRAINT [DF_Pledge_oust_time] DEFAULT (0) FOR [oust_time],
    CONSTRAINT [DF_Pledge_skill_level] DEFAULT (0) FOR [skill_level],
    CONSTRAINT [DF_Pledge_castle_id] DEFAULT (0) FOR [castle_id],
    CONSTRAINT [DF_Pledge_agit_id] DEFAULT (0) FOR [agit_id],
    CONSTRAINT [DF_Pledge_rank] DEFAULT (0) FOR [rank],
    CONSTRAINT [DF_Pledge_name_value_1] DEFAULT (0) FOR [name_value],
    CONSTRAINT [DF_Pledge_status] DEFAULT (0) FOR [status],
    CONSTRAINT [DF_Pledge_private_flag] DEFAULT (0) FOR [private_flag],
    CONSTRAINT [DF_Pledge_crest_id] DEFAULT (0) FOR [crest_id],
    CONSTRAINT [DF_Pledge_is_guilty] DEFAULT (0) FOR [is_guilty],
    CONSTRAINT [DF_Pledge_dismiss_reserved_time] DEFAULT (0) FOR [dismiss_reserved_time],
    CONSTRAINT [DF__pledge__alliance__29820FAE] DEFAULT (0) FOR [alliance_withdraw_time],
    CONSTRAINT [DF__pledge__alliance__2A7633E7] DEFAULT (0) FOR [alliance_dismiss_time],
    CONSTRAINT [DF__pledge__alliance__288DEB75] DEFAULT (0) FOR [alliance_ousted_time],
    CONSTRAINT [IX_Pledge] UNIQUE  NONCLUSTERED
    (
        [name]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[Pledge_Crest] WITH NOCHECK ADD
    CONSTRAINT [DF_Pledge_Crest_bitmap_size] DEFAULT (0) FOR [bitmap_size]
GO

ALTER TABLE [dbo].[Pledge_War] WITH NOCHECK ADD
    CONSTRAINT [DF_Pledge_War_status] DEFAULT (0) FOR [status]
GO

ALTER TABLE [dbo].[Quest] WITH NOCHECK ADD
    CONSTRAINT [DF_Quest_q1] DEFAULT (0) FOR [q1],
    CONSTRAINT [DF_Quest_s1] DEFAULT (0) FOR [s1],
    CONSTRAINT [DF_Quest_q2] DEFAULT (0) FOR [q2],
    CONSTRAINT [DF_Quest_s2] DEFAULT (0) FOR [s2],
    CONSTRAINT [DF_Quest_q3] DEFAULT (0) FOR [q3],
    CONSTRAINT [DF_Quest_s3] DEFAULT (0) FOR [s3],
    CONSTRAINT [DF_Quest_q4] DEFAULT (0) FOR [q4],
    CONSTRAINT [DF_Quest_s4] DEFAULT (0) FOR [s4],
    CONSTRAINT [DF_Quest_q5] DEFAULT (0) FOR [q5],
    CONSTRAINT [DF_Quest_s5] DEFAULT (0) FOR [s5],
    CONSTRAINT [DF_Quest_q6] DEFAULT (0) FOR [q6],
    CONSTRAINT [DF_Quest_s6] DEFAULT (0) FOR [s6],
    CONSTRAINT [DF_Quest_q7] DEFAULT (0) FOR [q7],
    CONSTRAINT [DF_Quest_s7] DEFAULT (0) FOR [s7],
    CONSTRAINT [DF_Quest_q8] DEFAULT (0) FOR [q8],
    CONSTRAINT [DF_Quest_s8] DEFAULT (0) FOR [s8],
    CONSTRAINT [DF_Quest_q9] DEFAULT (0) FOR [q9],
    CONSTRAINT [DF_Quest_s9] DEFAULT (0) FOR [s9],
    CONSTRAINT [DF_Quest_q10] DEFAULT (0) FOR [q10],
    CONSTRAINT [DF_Quest_s10] DEFAULT (0) FOR [s10],
    CONSTRAINT [DF_Quest_q11] DEFAULT (0) FOR [q11],
    CONSTRAINT [DF_Quest_s11] DEFAULT (0) FOR [s11],
    CONSTRAINT [DF_Quest_q12] DEFAULT (0) FOR [q12],
    CONSTRAINT [DF_Quest_s12] DEFAULT (0) FOR [s12],
    CONSTRAINT [DF_Quest_q13] DEFAULT (0) FOR [q13],
    CONSTRAINT [DF_Quest_s13] DEFAULT (0) FOR [s13],
    CONSTRAINT [DF_Quest_q14] DEFAULT (0) FOR [q14],
    CONSTRAINT [DF_Quest_s14] DEFAULT (0) FOR [s14],
    CONSTRAINT [DF_Quest_q15] DEFAULT (0) FOR [q15],
    CONSTRAINT [DF_Quest_s15] DEFAULT (0) FOR [s15],
    CONSTRAINT [DF_Quest_q16] DEFAULT (0) FOR [q16],
    CONSTRAINT [DF_Quest_s16] DEFAULT (0) FOR [s16],
    CONSTRAINT [DF_Quest_j1] DEFAULT (0) FOR [j1],
    CONSTRAINT [DF_Quest_j2] DEFAULT (0) FOR [j2],
    CONSTRAINT [DF_Quest_j3] DEFAULT (0) FOR [j3],
    CONSTRAINT [DF_Quest_j4] DEFAULT (0) FOR [j4],
    CONSTRAINT [DF_Quest_j5] DEFAULT (0) FOR [j5],
    CONSTRAINT [DF_Quest_j6] DEFAULT (0) FOR [j6],
    CONSTRAINT [DF_Quest_j7] DEFAULT (0) FOR [j7],
    CONSTRAINT [DF_Quest_j8] DEFAULT (0) FOR [j8],
    CONSTRAINT [DF_Quest_j9] DEFAULT (0) FOR [j9],
    CONSTRAINT [DF_Quest_j10] DEFAULT (0) FOR [j10],
    CONSTRAINT [DF_Quest_j11] DEFAULT (0) FOR [j11],
    CONSTRAINT [DF_Quest_j12] DEFAULT (0) FOR [j12],
    CONSTRAINT [DF_Quest_j13] DEFAULT (0) FOR [j13],
    CONSTRAINT [DF_Quest_j14] DEFAULT (0) FOR [j14],
    CONSTRAINT [DF_Quest_j15] DEFAULT (0) FOR [j15],
    CONSTRAINT [DF_Quest_j16] DEFAULT (0) FOR [j16],
    CONSTRAINT [IX_Quest] UNIQUE  NONCLUSTERED
    (
        [char_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[QuestData] WITH NOCHECK ADD
    CONSTRAINT [DF_QuestData_logdate] DEFAULT (getdate()) FOR [logdate]
GO

ALTER TABLE [dbo].[SkillData] WITH NOCHECK ADD
    CONSTRAINT [DF_SkillData_logdate] DEFAULT (getdate()) FOR [logdate]
GO

ALTER TABLE [dbo].[agit] WITH NOCHECK ADD
    CONSTRAINT [DF__agit__pledge_id__17236851] DEFAULT (0) FOR [pledge_id],
    CONSTRAINT [DF__agit__auction_pr__18178C8A] DEFAULT (0) FOR [auction_price],
    CONSTRAINT [DF__agit__auction_da__190BB0C3] DEFAULT (0) FOR [auction_date],
    CONSTRAINT [DF__agit__hp_stove__1F6E958F] DEFAULT (0) FOR [hp_stove],
    CONSTRAINT [DF__agit__mp_flame__2062B9C8] DEFAULT (0) FOR [mp_flame],
    CONSTRAINT [DF__agit__hatcher__2156DE01] DEFAULT (0) FOR [hatcher],
    CONSTRAINT [DF__agit__hp_stove_e__224B023A] DEFAULT (0) FOR [hp_stove_expire],
    CONSTRAINT [DF__agit__mp_flame_e__233F2673] DEFAULT (0) FOR [mp_flame_expire],
    CONSTRAINT [DF__agit__status__270FB757] DEFAULT (2) FOR [status],
    CONSTRAINT [DF__agit__next_war_t__2803DB90] DEFAULT (0) FOR [next_war_time],
    CONSTRAINT [DF__agit__teleport_l__442BE449] DEFAULT (0) FOR [teleport_level],
    CONSTRAINT [DF__agit__teleport_e__45200882] DEFAULT (0) FOR [teleport_expire],
    CONSTRAINT [DF_agit_tax_rate] DEFAULT (0) FOR [tax_rate],
    CONSTRAINT [DF_agit_shop_income] DEFAULT (0) FOR [shop_income],
    CONSTRAINT [DF__agit__tax_rate_t__2759D01A] DEFAULT ((-1)) FOR [tax_rate_to_change],
    CONSTRAINT [DF__agit__tax_child___284DF453] DEFAULT (0) FOR [tax_child_rate],
    CONSTRAINT [DF__agit__tax_child___2942188C] DEFAULT ((-1)) FOR [tax_child_rate_to_change],
    CONSTRAINT [DF__agit__shop_incom__2A363CC5] DEFAULT (0) FOR [shop_income_temp]
GO

ALTER TABLE [dbo].[agit_bid] WITH NOCHECK ADD
    CONSTRAINT [DF_agit_bid_attend_date] DEFAULT (getdate()) FOR [attend_date],
    CONSTRAINT [IX_agit_bid] UNIQUE  NONCLUSTERED
    (
        [auction_id],
        [attend_pledge_id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[builder_account] WITH NOCHECK ADD
    CONSTRAINT [DF_account_builder_default_builder] DEFAULT (0) FOR [default_builder],
    CONSTRAINT [DF_builder_account_account_id] DEFAULT (0) FOR [account_id]
GO

ALTER TABLE [dbo].[castle] WITH NOCHECK ADD
    CONSTRAINT [DF__castle__pledge_i__1352D76D] DEFAULT (0) FOR [pledge_id],
    CONSTRAINT [DF__castle__next_war__1446FBA6] DEFAULT (0) FOR [next_war_time],
    CONSTRAINT [DF__castle__tax_rate__153B1FDF] DEFAULT (0) FOR [tax_rate],
    CONSTRAINT [DF_castle_type] DEFAULT (1) FOR [type],
    CONSTRAINT [DF_castle_status] DEFAULT (0) FOR [status],
    CONSTRAINT [DF_castle_crop_income] DEFAULT (0) FOR [crop_income],
    CONSTRAINT [DF_castle_shop_income] DEFAULT (0) FOR [shop_income],
    CONSTRAINT [DF__castle__siege_el__3FA65AF7] DEFAULT (0) FOR [siege_elapsed_time],
    CONSTRAINT [DF_castle_tax_child_rate] DEFAULT (0) FOR [tax_child_rate],
    CONSTRAINT [DF__castle__shop_inc__2B2A60FE] DEFAULT (0) FOR [shop_income_temp],
    CONSTRAINT [DF__castle__tax_rate__2C1E8537] DEFAULT ((-1)) FOR [tax_rate_to_change],
    CONSTRAINT [DF__castle__tax_chil__2D12A970] DEFAULT ((-1)) FOR [tax_child_rate_to_change]
GO

ALTER TABLE [dbo].[castle_war] WITH NOCHECK ADD
    CONSTRAINT [DF__castle_wa__propo__1A35AA7D] DEFAULT (0) FOR [propose_time]
GO

ALTER TABLE [dbo].[control_tower] WITH NOCHECK ADD
    CONSTRAINT [DF__control_t__contr__33F57C80] DEFAULT (0) FOR [control_level]
GO

ALTER TABLE [dbo].[event_items] WITH NOCHECK ADD
    CONSTRAINT [DF_event_items_log_date] DEFAULT (getdate()) FOR [log_date]
GO

ALTER TABLE [dbo].[login_announce] WITH NOCHECK ADD
    CONSTRAINT [DF_login_announce_interval_10] DEFAULT (0) FOR [interval_10]
GO

ALTER TABLE [dbo].[npc_boss] WITH NOCHECK ADD
    CONSTRAINT [DF_npc_boss_i0] DEFAULT (0) FOR [i0]
GO

ALTER TABLE [dbo].[object_data] WITH NOCHECK ADD
    CONSTRAINT [DF_object_data_pledge_id] DEFAULT (0) FOR [owner_id],
    CONSTRAINT [DF_object_data_castle_id] DEFAULT (0) FOR [residence_id],
    CONSTRAINT [DF_object_data_max_hp] DEFAULT (0) FOR [max_hp],
    CONSTRAINT [DF_object_data_hp] DEFAULT (0) FOR [hp],
    CONSTRAINT [DF_object_data_x_pos] DEFAULT (0) FOR [x_pos],
    CONSTRAINT [DF_object_data_y_pos] DEFAULT (0) FOR [y_pos],
    CONSTRAINT [DF_object_data_z_pos] DEFAULT (0) FOR [z_pos]
GO

ALTER TABLE [dbo].[pet_data] WITH NOCHECK ADD
    CONSTRAINT [DF_pet_data_hp] DEFAULT (1) FOR [hp],
    CONSTRAINT [DF_pet_data_mp] DEFAULT (0) FOR [mp],
    CONSTRAINT [DF_pet_data_sp] DEFAULT (0) FOR [sp],
    CONSTRAINT [DF_pet_data_meal] DEFAULT (1) FOR [meal],
    CONSTRAINT [DF_pet_data_slot1] DEFAULT (0) FOR [slot1],
    CONSTRAINT [DF_pet_data_slot2] DEFAULT (0) FOR [slot2]
GO

ALTER TABLE [dbo].[pet_data2] WITH NOCHECK ADD
    CONSTRAINT [DF_pet_data2_slot1] DEFAULT (0) FOR [slot1],
    CONSTRAINT [DF_pet_data2_slot2] DEFAULT (0) FOR [slot2]
GO

ALTER TABLE [dbo].[pledge_contribution] WITH NOCHECK ADD
    CONSTRAINT [DF_pledge_contribution_contribution] DEFAULT (0) FOR [contribution]
GO

ALTER TABLE [dbo].[req_charmove_old] WITH NOCHECK ADD
    CONSTRAINT [DF_req_charmove_reg_date] DEFAULT (getdate()) FOR [req_date],
    CONSTRAINT [IX_req_charmove] UNIQUE  NONCLUSTERED
    (
        [new_char_name]
    )  ON [PRIMARY] ,
    CONSTRAINT [IX_req_charmove_1] UNIQUE  NONCLUSTERED
    (
        [old_char_id],
        [old_world_id]
    )  ON [PRIMARY] ,
    CONSTRAINT [IX_req_charmove_2] UNIQUE  NONCLUSTERED
    (
        [account_id]
    )  ON [PRIMARY] ,
    CONSTRAINT [IX_req_charmove_3] UNIQUE  NONCLUSTERED
    (
        [new_char_name],
        [new_world_id]
    )  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_ban] WITH NOCHECK ADD
    CONSTRAINT [DF_user_ban_status] DEFAULT (0) FOR [status],
    CONSTRAINT [DF_user_ban_ban_date] DEFAULT (getdate()) FOR [ban_date],
    CONSTRAINT [DF_user_ban_ban_hour] DEFAULT (0) FOR [ban_hour],
    CONSTRAINT [DF_user_ban_ban_end] DEFAULT (0) FOR [ban_end]
GO

ALTER TABLE [dbo].[user_comment] WITH NOCHECK ADD
    CONSTRAINT [DF_user_comment_comment_date] DEFAULT (getdate()) FOR [comment_date],
    CONSTRAINT [DF_user_comment_deleted] DEFAULT (0) FOR [deleted]
GO

ALTER TABLE [dbo].[user_data] WITH NOCHECK ADD
    CONSTRAINT [DF_user_data_pledge_id] DEFAULT (0) FOR [pledge_id],
    CONSTRAINT [DF_user_data_builder] DEFAULT (0) FOR [builder],
    CONSTRAINT [DF_user_data_IsInVehicle] DEFAULT (0) FOR [IsInVehicle],
    CONSTRAINT [DF_user_data_SP] DEFAULT (0) FOR [SP],
    CONSTRAINT [DF_user_data_PK] DEFAULT (0) FOR [PK],
    CONSTRAINT [DF_user_data_PKpardon] DEFAULT (0) FOR [PKpardon],
    CONSTRAINT [DF_user_data_Dual] DEFAULT (0) FOR [Duel],
    CONSTRAINT [DF_user_data_ST_underware] DEFAULT (0) FOR [ST_underware],
    CONSTRAINT [DF_user_data_ST_right_ear] DEFAULT (0) FOR [ST_right_ear],
    CONSTRAINT [DF_user_data_ST_left_ear] DEFAULT (0) FOR [ST_left_ear],
    CONSTRAINT [DF_user_data_ST_neck] DEFAULT (0) FOR [ST_neck],
    CONSTRAINT [DF_user_data_ST_right_finger] DEFAULT (0) FOR [ST_right_finger],
    CONSTRAINT [DF_user_data_ST_left_finger] DEFAULT (0) FOR [ST_left_finger],
    CONSTRAINT [DF_user_data_ST_head] DEFAULT (0) FOR [ST_head],
    CONSTRAINT [DF_user_data_ST_right_hand] DEFAULT (0) FOR [ST_right_hand],
    CONSTRAINT [DF_user_data_ST_left_hand] DEFAULT (0) FOR [ST_left_hand],
    CONSTRAINT [DF_user_data_ST_gloves] DEFAULT (0) FOR [ST_gloves],
    CONSTRAINT [DF_user_data_ST_chest] DEFAULT (0) FOR [ST_chest],
    CONSTRAINT [DF_user_data_ST_legs] DEFAULT (0) FOR [ST_legs],
    CONSTRAINT [DF_user_data_ST_feet] DEFAULT (0) FOR [ST_feet],
    CONSTRAINT [DF_user_data_ST_back] DEFAULT (0) FOR [ST_back],
    CONSTRAINT [DF_user_data_ST_both_hand] DEFAULT (0) FOR [ST_both_hand],
    CONSTRAINT [DF_user_data_create_date] DEFAULT (getdate()) FOR [create_date],
    CONSTRAINT [DF_user_data_quest_flag] DEFAULT (0x00) FOR [quest_flag],
    CONSTRAINT [DF_user_data_power_flag] DEFAULT (0x0000000000000000000000000000000000000000000000000000000000000000) FOR [power_flag],
    CONSTRAINT [DF_user_data_pledge_manage_time] DEFAULT (0) FOR [pledge_dismiss_time],
    CONSTRAINT [DF_user_data_pledge_leave_time] DEFAULT (0) FOR [pledge_leave_time],
    CONSTRAINT [DF_user_data_pledge_leave_status] DEFAULT (0) FOR [pledge_leave_status],
    CONSTRAINT [DF_user_data_max_hp] DEFAULT (0) FOR [max_hp],
    CONSTRAINT [DF_user_data_max_mp] DEFAULT (0) FOR [max_mp],
    CONSTRAINT [DF_user_data_face_index] DEFAULT (0) FOR [face_index],
    CONSTRAINT [DF_user_data_hair_shape_index] DEFAULT (0) FOR [hair_shape_index],
    CONSTRAINT [DF_user_data_hair_color_index] DEFAULT (0) FOR [hair_color_index],
    CONSTRAINT [DF_user_data_use_time] DEFAULT (0) FOR [use_time],
    CONSTRAINT [DF_user_data_pledge_ousted_time] DEFAULT (0) FOR [pledge_ousted_time],
    CONSTRAINT [DF_user_data_plwdge_withdraw_time] DEFAULT (0) FOR [pledge_withdraw_time],
    CONSTRAINT [DF_user_data_surrender_war_id] DEFAULT (0) FOR [surrender_war_id],
    CONSTRAINT [DF_user_data_drop_exp] DEFAULT (0) FOR [drop_exp]
GO

ALTER TABLE [dbo].[user_history] WITH NOCHECK ADD
    CONSTRAINT [DF_user_history_log_date] DEFAULT (getdate()) FOR [log_date]
GO

ALTER TABLE [dbo].[user_item] WITH NOCHECK ADD
    CONSTRAINT [DF_user_item_wished] DEFAULT (0) FOR [wished],
    CONSTRAINT [pk_user_item] PRIMARY KEY  NONCLUSTERED
    (
        [item_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

ALTER TABLE [dbo].[user_item_9_28] WITH NOCHECK ADD
    CONSTRAINT [DF__user_item__wishe__0A7378A9] DEFAULT (0) FOR [wished]
GO

ALTER TABLE [dbo].[user_item_err_9_28] WITH NOCHECK ADD
    CONSTRAINT [DF__user_item__wishe__0E44098D] DEFAULT (0) FOR [wished]
GO

ALTER TABLE [dbo].[user_journal] WITH NOCHECK ADD
    CONSTRAINT [DF_user_journal_log_data] DEFAULT (getdate()) FOR [log_data]
GO

ALTER TABLE [dbo].[user_log] WITH NOCHECK ADD
    CONSTRAINT [DF_user_log_log_date] DEFAULT (getdate()) FOR [log_date]
GO

ALTER TABLE [dbo].[user_name_reserved] WITH NOCHECK ADD
    CONSTRAINT [DF_user_name_reserved_account_id] DEFAULT (0) FOR [account_id],
    CONSTRAINT [DF_user_name_reserved_used] DEFAULT (0) FOR [used]
GO

ALTER TABLE [dbo].[user_punish] WITH NOCHECK ADD
    CONSTRAINT [DF_user_punish_punish_on] DEFAULT (0) FOR [punish_on],
    CONSTRAINT [DF_user_punish_punish_date] DEFAULT (getdate()) FOR [punish_date]
GO

ALTER TABLE [dbo].[user_skill] WITH NOCHECK ADD
    CONSTRAINT [DF_user_skill_skill_lev] DEFAULT (0) FOR [skill_lev],
    CONSTRAINT [DF_user_skill_last_use] DEFAULT (0) FOR [to_end_time],
    CONSTRAINT [PK_user_skill] PRIMARY KEY  NONCLUSTERED
    (
        [char_id],
        [skill_id]
    ) WITH  FILLFACTOR = 90  ON [PRIMARY]
GO

 CREATE  INDEX [IX_ItemData] ON [dbo].[ItemData]([id], [consumetype]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_itemdata_name] ON [dbo].[ItemData]([name]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_petmsg_charid] ON [dbo].[PetitionMsg]([Char_Id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [IX_name] ON [dbo].[SkillData]([name]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_agit_adena] ON [dbo].[agit_adena]([pledge_id], [auction_id], [reason]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_agit_auction_1] ON [dbo].[agit_auction]([agit_id], [auction_time] DESC ) ON [PRIMARY]
GO

 CREATE  INDEX [IX_agit_auction_2] ON [dbo].[agit_auction]([auction_id]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_agit_auction] ON [dbo].[agit_bid]([auction_id]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_agit_price] ON [dbo].[agit_bid]([attend_price] DESC , [attend_date]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_err_table2] ON [dbo].[err_skill_1 ]([class], [lev]) ON [PRIMARY]
GO

 CREATE  UNIQUE  INDEX [idx_npc_boss_unique_name] ON [dbo].[npc_boss]([npc_db_name]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_user_ActiveSkill] ON [dbo].[user_ActiveSkill]([char_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [IX_user_comment_1] ON [dbo].[user_comment]([comment_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  UNIQUE  INDEX [idx_user_data1] ON [dbo].[user_data]([char_name]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_user_data_pledge] ON [dbo].[user_data]([pledge_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_user_data_1] ON [dbo].[user_data]([account_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_user_data_account_name] ON [dbo].[user_data]([account_name]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [IX_user_history] ON [dbo].[user_history]([char_name]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_item_type] ON [dbo].[user_item]([item_type]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_warehouse] ON [dbo].[user_item]([warehouse]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [IX_user_punish] ON [dbo].[user_punish]([char_id], [punish_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_skill_lev] ON [dbo].[user_skill]([skill_lev]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_skill_toend] ON [dbo].[user_skill]([to_end_time]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  UNIQUE  INDEX [idx_user_warehouse_itemid] ON [dbo].[user_warehouse]([item_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_user_warehouse_charid] ON [dbo].[user_warehouse]([char_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_user_warehouse_itemtype] ON [dbo].[user_warehouse]([item_type]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO



CREATE PROC DB_BACKUP
    @DBNAME  varCHAR(16),
    @path  varchar(32) = 'd:\MSSQL\BACKUP\',
    @gen  int = 7
   AS
    begin
        SET QUOTED_IDENTIFIER OFF

        declare @dev_name varchar(64)
        declare @dev_name_del varchar(64)
        declare @physical_name  varchar(64)
        declare @description varchar(64)

        if ( select count(*) from master.dbo.sysdatabases where name = @dbname ) = 0
        begin
            select 'Database "' + @DBNAME + '" does not exist.'
            return
        end

        select @description = @DBNAME  + ' , ' + CONVERT(CHAR(20),GETDATE())

        if datepart(hour,getdate()) < 12
          begin
            select @dev_name = @@SERVERNAME + '.' + @DBNAME + ' ' + convert(char(10),getdate() , 120 )
            select @dev_name_del = @@SERVERNAME + '.' + @DBNAME + ' ' + convert(char(10),getdate() - @gen , 120 )
            select @physical_name = rtrim(upper(@PATH)) + rtrim(upper(@dev_name)) + '.BAK'
            select @description = 'Daily Backup , ' + @DBNAME  + '   ' + CONVERT(CHAR(20),GETDATE())
          end
            else
          begin
            select @dev_name = @@SERVERNAME + '.' + @DBNAME + '.' + convert(char(10),getdate() , 120 )
            select @dev_name_del = @@SERVERNAME + '.' + @DBNAME + '.' + convert(char(10),getdate() - 1 , 120 )
            select @physical_name = rtrim(upper(@PATH)) + rtrim(upper(@dev_name)) + '.PMBAK'
            select @description = 'Daily 2nd Backup , ' + @DBNAME  + '   ' + CONVERT(CHAR(20),GETDATE())
          end

        if ( select count(*) from master.dbo.sysdevices where name = rtrim(@dev_name_del) ) > 0
            EXEC sp_dropdevice @dev_name_del,'delfile'

        if ( select count(*) from master.dbo.sysdevices where name = rtrim(@dev_name) ) = 0
            EXEC sp_addumpdevice 'disk' , @dev_name , @physical_name

        BACKUP DATABASE @DBNAME TO @dev_name WITH INIT , NAME = @description , NOSKIP , NOFORMAT

    end

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.LIN_MakeNewBlankItem    Script Date: 2003-09-20 오전 11:51:56 ******/
CREATE PROCEDURE [DBO].[LIN_MakeNewBlankItem]
AS

SET NOCOUNT ON

declare @newItemId int

insert into user_item (char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
values(0,0,0,0,0,0,0,0,0)

SET @newItemId = @@IDENTITY
select @newItemId






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO







/****** Object:  Stored Procedure dbo.Lin_EnchantItem    Script Date: 2003-09-20 오전 11:51:56 ******/
/********************************************
Lin_EnchantItem
    enchant item
INPUT
    @char_id	INT,
    @item_id 	INT,
    @target_item_id 	INT,
    @nEnchantNum 	INT
    @bZeorDelete 	INT = 0
OUTPUT
    @nResultAmount	INT
return
made by
    carrot
date
    2002-10-14
********************************************/
CREATE PROCEDURE [DBO].[Lin_EnchantItem]
(
    @char_id	INT,
    @item_id 	INT,
    @target_item_id 	INT,
    @nEnchantNum 	INT,
    @bZeorDelete 	INT = 0
)
AS
SET NOCOUNT ON

DECLARE @nResultAmount 	INT
SET @nResultAmount = -1

UPDATE user_item SET amount = amount -1 WHERE char_id = @char_id AND item_id = @item_id
UPDATE user_item SET enchant = enchant + @nEnchantNum WHERE char_id = @char_id AND item_id = @target_item_id

IF NOT @@ROWCOUNT = 1
    SELECT -1
ELSE
BEGIN

    SELECT @nResultAmount = ISNULL(amount, -1) FROM user_item WHERE char_id = @char_id AND item_id = @item_id
    IF ( @nResultAmount = 0 AND @bZeorDelete = 1)
    BEGIN
        DELETE user_item WHERE char_id = @char_id AND item_id = @item_id
--		UPDATE user_item SET char_id = 0, item_type = 0 WHERE char_id = @char_id AND item_id = @item_id
    END

    SELECT @nResultAmount
END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.Lin_GetSummary    Script Date: 2003-09-20 오전 11:51:56 ******/
CREATE PROCEDURE [DBO].[Lin_GetSummary]
AS

SET NOCOUNT ON

Select count(id) as Total from BBS_All




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




CREATE PROC TranLogBackup
    @DBNAME varchar(20)
AS

--==================================================================================
--공통 변수 선언
    DECLARE
        @query varchar(1000),
        @cur_hour tinyint,
        @del_hour tinyint,
        @cur_device varchar(50),
        @del_device varchar(50),
        @description varchar(48),
        @physical_name  varchar(64)


--==================================================================================
--공통 변수 설정
    SET @cur_hour = datepart(hour,getdate())
    SET @del_hour = datepart( hour,dateadd(hour,-24,getdate()))

--==================================================================================
--사전체크
    IF @cur_hour in (6,18) --full backup 받는 시간
        RETURN


    SET @cur_device = @@servername + '_' + @DBNAME + '_tlog_' + CONVERT(char(8),getdate(),112) + '_'
    SET @del_device = @@servername + '_' + @DBNAME + '_tlog_' + CONVERT(char(8),dateadd(hour,-24,getdate()),112) + '_'
    SET @description = 'Log Hourly Backup , ' + @DBNAME  + '  ' + CONVERT(CHAR(16),GETDATE(),20)


    IF @cur_hour < 10
        SET @cur_device = @cur_device + '0' + convert(char(1),@cur_hour)
    ELSE
        SET @cur_device = @cur_device + convert(char(2),@cur_hour)


    IF @del_hour < 10
        SET @del_device = @del_device + '0' + convert(char(1),@del_hour)
    ELSE
        SET @del_device = @del_device + convert(char(2),@del_hour)

    SET @physical_name = 'd:\MSSQL\BACKUP\' + @cur_device + '.tbak'

    PRINT 'cur_device : ' + @cur_device
    PRINT 'del_device : ' + @del_device
    PRINT 'physical_name : ' + @physical_name


--==================================================================================
--12 시간 이전의 device를 삭제한다.
    IF ( select count(*) from master.dbo.sysdevices where name = rtrim(@del_device) ) = 1
        EXEC sp_dropdevice @del_device,'delfile'


--==================================================================================
--dump device를 설정한다.
    IF ( select count(*) from master.dbo.sysdevices where name = rtrim(@cur_device) ) = 0
        EXEC sp_addumpdevice 'disk' , @cur_device , @physical_name


--==================================================================================
--transaction log 를 백업받는다.
    SET @query = 'BACKUP LOG ' + @DBNAME + ' TO ' + @cur_device
    PRINT @query
    EXECUTE(@query)


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.dp_GetItemListByAccount    Script Date: 2003-09-20 오전 11:51:57 ******/

CREATE PROCEDURE [dbo].[dp_GetItemListByAccount] @user_id varchar(12)
AS
SELECT b.item_id, c.name, a.char_name, b.warehouse, b.amount, b.enchant, b.eroded, b.bless, b.wished
FROM user_data a, user_item b, itemdata  c
WHERE a.account_name = @user_id
AND a.char_id = b.char_id AND b.item_type = c.id
ORDER BY a.char_name, b.warehouse, b.item_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.dp_GetItemListByPledge    Script Date: 2003-09-20 오전 11:51:57 ******/

CREATE PROCEDURE [dbo].[dp_GetItemListByPledge] @user_id varchar(30)
AS
SELECT b.item_id, c.name, a.char_name, b.warehouse, b.amount, b.enchant, b.eroded, b.bless, b.wished
FROM user_data a INNER JOIN user_item b ON a.char_id = b.char_id, itemdata c
WHERE a.char_id in (SELECT char_id FROM user_data a INNER JOIN pledge b ON a.pledge_id = b.pledge_id WHERE b.name = @user_id)
AND b.item_type = c.id
ORDER BY a.char_name, b.warehouse, b.item_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.dp_GetItemListByUserID    Script Date: 2003-09-20 오전 11:51:58 ******/

CREATE PROCEDURE [dbo].[dp_GetItemListByUserID] @user_id varchar(12)
AS
SELECT user_item.item_id, itemdata.name, user_data.char_name, user_item.warehouse, user_item.amount, user_item.enchant, user_item.eroded, user_item.bless, user_item.wished
FROM user_data, user_item, itemdata
WHERE char_name = @user_id
AND user_data.char_id = user_item.char_id AND user_item.item_type = itemdata.id
ORDER BY  user_item.warehouse, user_item.item_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.dp_adena_rank    Script Date: 2003-09-20 오전 11:51:56 ******/
CREATE PROCEDURE dbo.dp_adena_rank
(
@limit int
)
  AS

declare @crdate datetime

select @crdate = crdate   from dbo.sysobjects where id = object_id(N'[dbo].[dt_adena_rank_temp]') and OBJECTPROPERTY(id, N'IsUserTable') = 1

if @crdate is not null
    if  datediff(hh,@crdate, getdate()) > 1
        drop table [dbo].[dt_adena_rank_temp]
    else
        goto SelectData


CREATE TABLE [dbo].[dt_adena_rank_temp] (
        [char_id] [int] NOT NULL ,
        [amount] [numeric](18, 0) NOT NULL ,
        [rank] [int] IDENTITY (1, 1) NOT NULL
    ) ON [PRIMARY]

insert dbo.dt_adena_rank_temp (char_id, amount)
select  top 1000  char_id, sum(cast(amount as numeric )) as amount from user_item with (readpast) where item_type = 57 group by char_id
order by 2 desc


SelectData:

select  b.char_name, b.account_name, a.amount, a.rank from [dbo].[dt_adena_rank_temp] as a, user_data as b
where a.rank <= @limit and a.char_id = b.char_id
order by rank




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO


/********************************************
lin_AddBlockList
 add character's blocked list.
INPUT
 char_id,
 target char_name
OUTPUT
return
made by
 carrot
date
 2003-12-01
change
********************************************/
CREATE PROCEDURE [DBO].[lin_AddBlockList]
(
 @char_id INT,
 @target_char_name NVARCHAR(50)
)
AS

SET NOCOUNT ON

DECLARE @target_char_id INT
DECLARE @target_builder_lev INT
SET @target_char_id = 0
SET @target_builder_lev  = 0

SELECT @target_char_id = char_id, @target_builder_lev = builder FROM user_data WHERE char_name = @target_char_name

IF (@target_builder_lev  > 0 AND @target_builder_lev  <= 5)
BEGIN
  RAISERROR ('Try block builder : char id = [%d], target naem[%s]', 16, 1, @char_id, @target_char_name)
  RETURN -1;
END

IF @target_char_id > 0
BEGIN
 INSERT INTO user_blocklist VALUES (@char_id, @target_char_id, @target_char_name)
 IF NOT @@ROWCOUNT = 1
 BEGIN
  RAISERROR ('Cannot find add blocklist: char id = [%d], target naem[%s]', 16, 1, @char_id, @target_char_name)
 END
 ELSE
 BEGIN
  SELECT @target_char_id
 END
END
ELSE
BEGIN
 RAISERROR ('Cannot find add blocklist: char id = [%d], target naem[%s]', 16, 1, @char_id, @target_char_name)
END


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_AddBookMark    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_AddBookMark
    add bookmark item
INPUT
    @char_id	int,
    @bookmark_name	nvarchar(50),
    @world		int,
    @x		int,
    @y		int,
    @z		int
OUTPUT

return
made by
    young
date
    2002-11-13
********************************************/
CREATE PROCEDURE [DBO].[lin_AddBookMark]
(
    @char_id	int,
    @bookmark_name	nvarchar(50),
    @world		int,
    @x		int,
    @y		int,
    @z		int
)
AS
SET NOCOUNT ON

if exists(select name from bookmark where char_id = @char_id and name = @bookmark_name)
begin
    update bookmark set world=@world, x=@x, y=@y, z=@z where char_id = @char_id and name = @bookmark_name
end
else
begin
    insert into bookmark(char_id, name, world, x, y, z)
    values( @char_id, @bookmark_name, @world, @x,@y,@z)
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_AddProhibit    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_AddProhibit

INPUT
    @char_name	nvarchar(50)
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
CREATE PROCEDURE [DBO].[lin_AddProhibit]
(
    @char_name	nvarchar(50),
    @noption	int
)
AS
SET NOCOUNT ON

if ( @noption = 1)
    insert into user_prohibit values (@char_name)
else if ( @noption = 3)
    insert into user_prohibit_word values (@char_name)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_AddUserLog    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_AddUserLog

INPUT
    @char_id	int,
    @log_id		int,
    @log_from	int,
    @log_to		int,
    @use_time	int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_AddUserLog]
(
    @char_id	int,
    @log_id		int,
    @log_from	int,
    @log_to		int,
    @use_time	int
)
AS
SET NOCOUNT ON

insert into user_log(char_id, log_id, log_from, log_to, use_time) values(@char_id, @log_id, @log_from, @log_to, @use_time)






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_AdenaChange    Script Date: 2003-09-20 오전 11:51:56 ******/
/********************************************
lin_AdenaChange
    change adena and return result amount
INPUT
    @char_id	INT,
    @price	 	INT
OUTPUT
    adena id		INT,
    amount		INT
return
made by
    carrot
date
    2002-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_AdenaChange]
(
    @char_id	INT,
    @price	 	INT
)
AS
SET NOCOUNT ON

DECLARE @nAmount	INT

SET @nAmount = NULL

SELECT @nAmount = amount FROM user_item WHERE char_id = @char_id AND item_type = 57
IF @nAmount IS NULL
    BEGIN
        SELECT -1, -1
    END
ELSE IF @nAmount + @price < 0
    BEGIN
        SELECT -1, -1
    END
ELSE
    BEGIN
        UPDATE user_item SET amount = amount + @price WHERE char_id = @char_id AND item_type = 57 AND warehouse = 0
        SELECT item_id, amount FROM user_item WHERE char_id = @char_id AND item_type = 57 AND warehouse = 0
    END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_AllianceWarChallengeRejected

INPUT
    @challenger int,
    @challenger_name nvarchar(50),
    @challengee int,
    @challengee_name nvarchar(50),
    @begin_time int,
    @status int
OUTPUT
return
made by
    bert
date
    2003-11-04
********************************************/
create PROCEDURE [DBO].[lin_AllianceWarChallengeRejected]
(
    @challenger int,
    @challenger_name nvarchar(50),
    @challengee int,
    @challengee_name nvarchar(50),
    @begin_time int,
    @status int
)
AS
SET NOCOUNT ON

INSERT INTO alliance_war (challenger, challenger_name,  challengee, challengee_name, begin_time, status)
VALUES (@challenger, @challenger_name,  @challengee, @challengee_name, @begin_time, @status)



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_AmountChange    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_AmountChange
    change item's amount and return result amount
INPUT
    @char_id	INT,
    @item_id 	INT,
    @change 	INT,
    @bZeorDelete 	INT = 0
OUTPUT
    amount		INT
return
made by
    carrot
date
    2002-04-22
change
    2002-10-15
        아이템 갯수가 0이 되었을 때 지울지 말지 변수 받도록 수정
change
    2003-05-12
        줄일 아이템 갯수를 받도록 수정
********************************************/
CREATE PROCEDURE [DBO].[lin_AmountChange]
(
    @char_id	INT,
    @item_id 	INT,
    @change 	INT,
    @bZeorDelete 	INT = 0
)
AS
SET NOCOUNT ON

DECLARE @nResultAmount 	INT
SET @nResultAmount = -1

IF(select top 1 amount from user_item where char_id = @char_id AND item_id = @item_id ) + @change >= 0
begin
    UPDATE user_item SET amount = amount + @change WHERE char_id = @char_id AND item_id = @item_id

    IF NOT @@ROWCOUNT = 1
        SELECT -1
    ELSE
        SELECT @nResultAmount = ISNULL(amount, -1) FROM user_item WHERE char_id = @char_id AND item_id = @item_id
        IF ( @nResultAmount = 0 AND @bZeorDelete = 1)
        BEGIN
            DELETE user_item WHERE char_id = @char_id AND item_id = @item_id
    --		UPDATE user_item SET char_id = 0, item_type = 0 WHERE char_id = @char_id AND item_id = @item_id
        END

        SELECT @nResultAmount
end
else
select -1




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ApproveBattle    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_ApproveBattle

INPUT
    @castle_id	int,
    @type	int
OUTPUT
    pledge_id,
    name
    type
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_ApproveBattle]
(
    @castle_id	int,
    @type	int
)
AS
SET NOCOUNT ON

SELECT
    p.pledge_id,
    p.name,
    type
FROM
    pledge p (nolock),
    castle_war cw (nolock)
WHERE
    p.pledge_id = cw.pledge_id
    AND cw.castle_id = @castle_id
    AND cw.type <> @type






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_BetaAddItem    Script Date: 2003-09-20 오전 11:51:56 ******/
CREATE PROCEDURE [DBO].[lin_BetaAddItem]
(
    @char_id int,
    @Item_type int,
    @amount int
)
AS

SET NOCOUNT ON

DECLARE @tempRowCount INT
DECLARE @bIsStackable TINYINT
SELECT @bIsStackable = IsStackable FROM ITEMNAME WHERE id = @Item_type

If @bIsStackable Is NULL
Begin
    RAISERROR ('Not exist Item Type', 16, 1)
End
Else
Begin
    If @bIsStackable = 1
    Begin
        Update user_item set amount = amount + @amount  where item_type = @Item_type and char_id = @char_id
        Set @tempRowCount = @@ROWCOUNT
        If @tempRowCount = 0
            INSERT INTO user_item (char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse) VALUES (@char_id, @Item_type, @amount, 0,0,0,0,0,0)
    End
    Else If @amount = 1
    Begin
        INSERT INTO user_item (char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse) VALUES (@char_id, @Item_type, @amount, 0,0,0,0,0,0)
        Set @tempRowCount = @@ROWCOUNT
    End
    Else
    Begin
        RAISERROR ('Amount is invalid', 16, 1)
    End
End

If @tempRowCount Is NOT NULL
    Select @tempRowCount





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_BreakFriendship    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_BreakFriendship
-- by bert

CREATE PROCEDURE dbo.lin_BreakFriendship (@char_id INT, @friend_char_id INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

DELETE FROM user_friend
WHERE
(char_id = @char_id AND friend_char_id = @friend_char_id)
OR
(char_id = @friend_char_id AND friend_char_id = @char_id)

IF @@ERROR = 0 AND @@ROWCOUNT = 2
BEGIN
    COMMIT TRAN
    SELECT @ret = 1
END
ELSE
BEGIN
    ROLLBACK TRAN
    SELECT @ret = 0
END

SELECT @ret




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_CancelAgitAuction
    cancel agit auction
INPUT
    @agit_id	int,


OUTPUT
return
made by
    young
date
    2003-12-11
********************************************/
CREATE PROCEDURE [DBO].[lin_CancelAgitAuction]
(
@agit_id		INT,
@last_cancel		INT
)
AS
SET NOCOUNT ON

declare @auction_id int
set @auction_id = 0

select @auction_id = isnull(auction_id , 0) from agit (nolock) where id = @agit_id

update agit set auction_id = 0 , last_cancel = @last_cancel where id = @agit_id

select @auction_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ChallengeRejected    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_ChallengeRejected

INPUT
    @challenger int,
    @challenger_name nvarchar(50),
    @challengee int,
    @challengee_name nvarchar(50),
    @begin_time int,
    @status int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_ChallengeRejected]
(
    @challenger int,
    @challenger_name nvarchar(50),
    @challengee int,
    @challengee_name nvarchar(50),
    @begin_time int,
    @status int
)
AS
SET NOCOUNT ON

INSERT INTO pledge_war (challenger, challenger_name,  challengee, challengee_name, begin_time, status)
VALUES (@challenger, @challenger_name,  @challengee, @challengee_name, @begin_time, @status)






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ChangeCharacterLocation    Script Date: 2003-09-20 오전 11:51:56 ******/
/********************************************
lin_ChangeCharacterLocation
    Set Character location
INPUT
    @char_name	nvarchar,
    @nWorld		SMALLINT,
    @nX		INT,
    @nY		INT,
    @nZ		INT
OUTPUT
    char_id
return
made by
    carrot
date
    2002-07-02
********************************************/
CREATE PROCEDURE [DBO].[lin_ChangeCharacterLocation]
(
    @char_name	NVARCHAR(24),
    @nWorld		INT,
    @nX		INT,
    @nY		INT,
    @nZ		INT
)
AS

SET NOCOUNT ON

DECLARE @Char_id INT
SET @Char_id = 0

UPDATE user_data SET world = @nWorld, xLoc = @nX , yLoc = @nY , zLoc = @nZ WHERE char_name = @char_name
IF @@ROWCOUNT > 0
BEGIN
    SELECT @Char_id = char_id FROM user_data WHERE char_name = @char_name
END

SELECT @Char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_ChangeCharacterName    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_ChangeCharacterName
    change character name
INPUT
    @old_char_name	nvarchar,
    @new_char_name	nvarchar
OUTPUT
    char_id
return
made by
    young
date
    2002-010-08
********************************************/
CREATE PROCEDURE [DBO].[lin_ChangeCharacterName]
(
    @old_char_name	NVARCHAR(24),
    @new_char_name	NVARCHAR(24)
)
AS

SET NOCOUNT ON

DECLARE @Char_id INT
DECLARE @nTmpCount INT
DECLARE @account_name NVARCHAR(50)
DECLARE @create_date datetime

SET @Char_id = 0

IF not exists(SELECT char_name FROM user_data WHERE char_name = @new_char_name)
BEGIN
    UPDATE user_data set char_name = @new_char_name where char_name = @old_char_name
    IF @@ROWCOUNT > 0
    BEGIN
        SELECT @char_id = char_id , @account_name = account_name, @create_date = create_date  FROM user_data WHERE char_name = @new_char_name
    END
END

SELECT @Char_id

if @char_id > 0
begin
    -- make user_history
    exec lin_InsertUserHistory @new_char_name, @char_id, 3, @account_name, @create_date
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO

/********************************************
lin_ChangeTimeData
 chagne time data table
INPUT
 @char_name NVARCHAR(30),
 @nType INT,
 @nChangeMin INT
OUTPUT
 changed acount id
 result used sec
return

made by
 carrot
date
 2004-04-29
change
********************************************/
CREATE PROCEDURE [DBO].[lin_ChangeTimeData]
(
 @char_name NVARCHAR(30),
 @nType INT,
 @nChangeMin INT
)
AS

SET NOCOUNT ON


SET @nChangeMin = @nChangeMin * 60      -- change min to sec
IF (@nType < 1 OR @nType > 2 OR @nChangeMin <= 0) -- 1 : add, 2 : del
BEGIN
    RAISERROR ('Not valid parameter : charnname[%s] type[%d], min[%d] ',16, 1,  @char_name,  @nType , @nChangeMin )
    RETURN -1
END

DECLARE @account_id INT
SET @account_id = 0
SELECT @account_id = account_id FROM user_data (nolock) WHERE char_name = @char_name

IF (@account_id <= 0)
BEGIN
    RAISERROR ('Not valid account id : charnname[%s] type[%d], min[%d] ',16, 1,  @char_name,  @nType , @nChangeMin )
    RETURN -1
END

DECLARE @used_sec INT
SET @used_sec = -1
SELECT TOP 1 @used_sec = used_sec FROM time_data WHERE account_id = @account_id
IF (@used_sec < 0 )
BEGIN
    RAISERROR ('Not exist time data : account_id[%d], charnname[%s] type[%d], min[%d] ',16, 1,  @account_id, @char_name,  @nType , @nChangeMin )
    RETURN -1
END

IF (@nType = 1) -- add
BEGIN
 UPDATE time_data SET used_sec = @used_sec + @nChangeMin WHERE account_id = @account_id
END
ELSE IF (@nType = 2) -- del
BEGIN
 IF (@used_sec < @nChangeMin)
 BEGIN
  SET @nChangeMin = @used_sec
 END
 UPDATE time_data SET used_sec = @used_sec - @nChangeMin WHERE account_id = @account_id
END
ELSE
BEGIN
    RAISERROR ('Not valid parameter : charnname[%s] type[%d], min[%d] ',16, 1,  @char_name,  @nType , @nChangeMin )
    RETURN -1
END

SELECT TOP 1 account_id, used_sec FROM time_data WHERE account_id = @account_id

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_CharLogin    Script Date: 2003-09-20 오전 11:51:56 ******/
/********************************************
lin_CharLogin
    log character login
INPUT
    char_id
OUTPUT
return
made by
    carrot
date
    2002-06-11
change
********************************************/
CREATE PROCEDURE [DBO].[lin_CharLogin]
(
    @char_id	INT
)
AS

SET NOCOUNT ON

UPDATE user_data SET login = GETDATE() WHERE char_id = @char_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO

/********************************************
lin_CharLogout
 log character Logout
INPUT
 char_id
OUTPUT
return
 week play time by sec
made by
 carrot
date
 2002-06-11
change
 2002.-12-20
  add usetime set
 2004-03-29
  add function to write today's used sec
********************************************/
CREATE PROCEDURE [DBO].[lin_CharLogout]
(
 @char_id INT,
 @usedTimeSec INT
)
AS

SET NOCOUNT ON

DECLARE @logoutDate DATETIME
SET @logoutDate = GETDATE()

UPDATE user_data SET Logout = @logoutDate, use_time = use_time + @usedTimeSec WHERE char_id = @char_id

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




CREATE PROCEDURE [DBO].[lin_CheckPetName]
(
@pet_name NVARCHAR(24)
)
AS

SET NOCOUNT ON

declare @result  int
set @result = 1

SET @pet_name = RTRIM(@pet_name)
IF @pet_name  LIKE N' '
BEGIN
    RAISERROR ('pet name has space : name = [%s]', 16, 1, @pet_name)
    set @result = -1
END

-- check user_prohibit
if exists(select char_name from user_prohibit (nolock) where char_name = @pet_name)
begin
    RAISERROR ('Pet  name is prohibited: name = [%s]', 16, 1, @pet_name)
    set @result = -2
end

-- prohibit word
declare @user_prohibit_word nvarchar(20)
select top 1 @user_prohibit_word = words from user_prohibit_word (nolock) where PATINDEX('%' + words + '%', @pet_name) > 0
if @user_prohibit_word is not null
begin
    RAISERROR ('pet  name has prohibited word: name = [%s], word[%s]', 16, 1, @pet_name, @user_prohibit_word)
    set @result = -3
end

-- check reserved name
--declare @reserved_name nvarchar(50)
--select top 1 @reserved_name = char_name from user_name_reserved (nolock) where used = 0 and char_name = @pet_name
--if not @reserved_name is null
--begin
--	RAISERROR ('pet name is reserved by other player: name = [%s]', 16, 1, @pet_name)
--	set @result = -4
--end

-- check duplicated pet name
declare @dup_pet_name nvarchar(50)
select top 1 @dup_pet_name = nick_name from pet_data (nolock) where nick_name = @pet_name
if not @dup_pet_name is null
begin
    RAISERROR ('duplicated pet name[%s]', 16, 1, @pet_name)
    set @result = -4
end

select @result



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_CheckPreviousAllianceWarHistory

INPUT
    @challenger_alliance_id		int
    @challengee_alliance_id		int

OUTPUT

made by
    bert
date
    2003-11-04
********************************************/

create PROCEDURE [DBO].[lin_CheckPreviousAllianceWarHistory]
(
    @challenger		int,
    @challengee		int
)
AS
SET NOCOUNT ON

SELECT
    id, challenger, challengee, status, begin_time
FROM
    alliance_war (nolock)
WHERE
    (challenger = @challenger AND challengee = @challengee)
    OR (challengee = @challengee AND challenger = @challenger)
ORDER BY
    begin_time DESC



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_CheckPreviousWarHistory    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_CheckPreviousWarHistory

INPUT
    @residence_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_CheckPreviousWarHistory]
(
    @challenger1		int,
    @challengee1		int,
    @challengee2		int,
    @challenger2		int
)
AS
SET NOCOUNT ON

SELECT
    id, challenger, challengee, status, begin_time
FROM
    pledge_war (nolock)
WHERE
    (challenger = @challenger1 AND challengee = @challengee1)
    OR (challengee = @challengee2 AND challenger = @challenger2)
ORDER BY
    begin_time DESC






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_CheckReserved    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_CheckReserved

INPUT
    @char_name	NCHAR(12),
    @account_name	NCHAR(13),
    @account_id	INT
OUTPUT

return
made by
    carrot
date
    2003-07-09
change
********************************************/
CREATE PROCEDURE [DBO].[lin_CheckReserved]
(
@char_name	NVARCHAR(24),
@account_name	NVARCHAR(24),
@account_id	INT
)
AS

SET NOCOUNT ON

SET @char_name = RTRIM(@char_name)

-- check reserved name
declare @reserved_name nvarchar(50)
declare @reserved_account_id int
select top 1 @reserved_name = char_name, @reserved_account_id = account_id from user_name_reserved (nolock) where used = 0 and char_name = @char_name
if not @reserved_name is null
begin
    if not @reserved_account_id = @account_id
    begin
        RAISERROR ('Character name is reserved by other player: name = [%s]', 16, 1, @char_name)
        RETURN -1
    end
end






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



CREATE PROCEDURE dbo.lin_CleanUpGhostData
AS
SET NOCOUNT ON

-- 유령 정리
UPDATE user_data
SET pledge_id = 0, nickname = ''
WHERE account_id = -1

-- 유령 친구 정리
DELETE FROM user_friend
WHERE
char_id IN (SELECT char_id FROM user_data WHERE account_id = -1)
OR
friend_char_id IN (SELECT char_id FROM user_data WHERE account_id = -1)

-- 유령 혈맹 정리 (혈맹주가 없는 혈)
DELETE FROM pledge WHERE ruler_id IN (SELECT char_id FROM user_data WHERE account_id = -1)

-- 유령혈맹 해산처리
UPDATE user_data
SET pledge_id = 0
WHERE pledge_id <> 0 AND pledge_id NOT IN (SELECT pledge_id FROM pledge)

UPDATE user_data
SET nickname = ''
WHERE pledge_id = 0

-- 유령 아지트 소유혈 정리
UPDATE agit
SET pledge_id = 0
WHERE pledge_id <> 0 AND pledge_id NOT IN (SELECT pledge_id FROM pledge)

-- 유령 성 소유혈 정리
UPDATE castle
SET pledge_id = 0
WHERE pledge_id <> 0 AND pledge_id NOT IN (SELECT pledge_id FROM pledge)

-- 유령 혈전 정리
DELETE FROM pledge_war
WHERE
status = 0
AND
(
(challengee <> 0 AND challengee NOT IN (SELECT pledge_id FROM pledge))
OR
(challenger <> 0 AND challenger NOT IN (SELECT pledge_id FROM pledge))
)

-- 유령 동맹 처리(동맹주가 없는 동맹)
DELETE FROM alliance WHERE master_pledge_id NOT IN (SELECT pledge_id FROM pledge)

-- 유령 동맹해산 처리
UPDATE pledge
SET alliance_id = 0
WHERE alliance_id <> 0 AND alliance_id NOT IN (SELECT id FROM alliance)

-- 유령 동맹전 정리
DELETE FROM alliance_war
WHERE
status = 0
AND
(
(challengee <> 0 AND challengee NOT IN (SELECT id FROM alliance))
OR
(challenger <> 0 AND challenger NOT IN (SELECT id FROM alliance))
)


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_CommentDelete

INPUT
    @delete		int,
    @comment_id		int
OUTPUT
return
made by
    young
date
    2003-09-02
********************************************/
CREATE PROCEDURE [DBO].[lin_CommentDelete]
(
    @delete		int,
    @comment_id		int
)
AS
SET NOCOUNT ON

if @delete = 1
    update user_comment set deleted = 1 where comment_id = @comment_id
else if @delete = 2
    update user_comment set deleted = 0 where comment_id = @comment_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_CommentSearch    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_CommentSearch

INPUT
    @char_id		int,
    @page			int
OUTPUT
return
made by
    young
date
    2003-09-02
********************************************/
CREATE PROCEDURE [DBO].[lin_CommentSearch]
(
    @char_id		int,
    @page			int
)
AS
SET NOCOUNT ON


select comment_id, char_name, char_id, comment, writer from user_comment (nolock)
where char_id = @char_id and deleted = 0
order by comment_id desc




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_CommentWrite    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_CommentWrite

INPUT
    @char_name		nvarchar(50),
    @char_id		int,
    @comment		nvarchar(200),
    @writer			nvarchar(50)
OUTPUT
return
made by
    young
date
    2003-09-02
********************************************/
create PROCEDURE [DBO].[lin_CommentWrite]
(
    @char_name		nvarchar(50),
    @char_id		int,
    @comment		nvarchar(200),
    @writer			nvarchar(50)
)
AS
SET NOCOUNT ON

insert into user_comment ( char_name, char_id, comment, writer )
values ( @char_name, @char_id, @comment, @writer )




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_CreateActiveSkill    Script Date: 2003-09-20 오전 11:51:58 ******/
--by bert for clee

CREATE PROCEDURE [DBO].[lin_CreateActiveSkill]
(
    @char_id INT,
    @s1 INT, @l1 TINYINT, @d1 INT, @c1 TINYINT,
    @s2 INT, @l2 TINYINT, @d2 INT, @c2 TINYINT,
    @s3 INT, @l3 TINYINT, @d3 INT, @c3 TINYINT,
    @s4 INT, @l4 TINYINT, @d4 INT, @c4 TINYINT,
    @s5 INT, @l5 TINYINT, @d5 INT, @c5 TINYINT,
    @s6 INT, @l6 TINYINT, @d6 INT, @c6 TINYINT,
    @s7 INT, @l7 TINYINT, @d7 INT, @c7 TINYINT,
    @s8 INT, @l8 TINYINT, @d8 INT, @c8 TINYINT,
    @s9 INT, @l9 TINYINT, @d9 INT, @c9 TINYINT,
    @s10 INT, @l10 TINYINT, @d10 INT, @c10 TINYINT,
    @s11 INT, @l11 TINYINT, @d11 INT, @c11 TINYINT,
    @s12 INT, @l12 TINYINT, @d12 INT, @c12 TINYINT,
    @s13 INT, @l13 TINYINT, @d13 INT, @c13 TINYINT,
    @s14 INT, @l14 TINYINT, @d14 INT, @c14 TINYINT,
    @s15 INT, @l15 TINYINT, @d15 INT, @c15 TINYINT,
    @s16 INT, @l16 TINYINT, @d16 INT, @c16 TINYINT,
    @s17 INT, @l17 TINYINT, @d17 INT, @c17 TINYINT,
    @s18 INT, @l18 TINYINT, @d18 INT, @c18 TINYINT,
    @s19 INT, @l19 TINYINT, @d19 INT, @c19 TINYINT,
    @s20 INT, @l20 TINYINT, @d20 INT, @c20 TINYINT
)
AS
SET NOCOUNT ON

INSERT INTO user_activeskill
(char_id,
s1, l1, d1, c1,
s2, l2, d2, c2,
s3, l3, d3, c3,
s4, l4, d4, c4,
s5, l5, d5, c5,
s6, l6, d6, c6,
s7, l7, d7, c7,
s8, l8, d8, c8,
s9, l9, d9, c9,
s10, l10, d10, c10,
s11, l11, d11, c11,
s12, l12, d12, c12,
s13, l13, d13, c13,
s14, l14, d14, c14,
s15, l15, d15, c15,
s16, l16, d16, c16,
s17, l17, d17, c17,
s18, l18, d18, c18,
s19, l19, d19, c19,
s20, l20, d20, c20)
VALUES
(@char_id,
@s1, @l1, @d1, @c1,
@s2, @l2, @d2, @c2,
@s3, @l3, @d3, @c3,
@s4, @l4, @d4, @c4,
@s5, @l5, @d5, @c5,
@s6, @l6, @d6, @c6,
@s7, @l7, @d7, @c7,
@s8, @l8, @d8, @c8,
@s9, @l9, @d9, @c9,
@s10, @l10, @d10, @c10,
@s11, @l11, @d11, @c11,
@s12, @l12, @d12, @c12,
@s13, @l13, @d13, @c13,
@s14, @l14, @d14, @c14,
@s15, @l15, @d15, @c15,
@s16, @l16, @d16, @c16,
@s17, @l17, @d17, @c17,
@s18, @l18, @d18, @c18,
@s19, @l19, @d19, @c19,
@s20, @l20, @d20, @c20)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_CreateAgitAuction
    create agit auction
INPUT
    @agit_id	int,
    @auction_desc	nvarchar(200),
    @min_price	int

OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_CreateAgitAuction]
(
@agit_id		INT,
@auction_desc		nvarchar(200),
@min_price		INT,
@auction_time		INT,
@auction_tax		INT
)
AS
SET NOCOUNT ON

declare @auction_id int

insert into agit_auction ( agit_id, auction_desc, min_price, auction_time , auction_tax)
values ( @agit_id, @auction_desc, @min_price, @auction_time  , @auction_tax )

select @auction_id = @@IDENTITY

update agit set auction_id = @auction_id where id = @agit_id

select @auction_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_CreateAgitBid
    create agit bid
INPUT
    @auction_id	int,
    @price		int,
    @pledge_id	int

OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_CreateAgitBid]
(
@agit_id		INT,
@auction_id		INT,
@price			INT,
@pledge_id		INT,
@attend_time		INT
)
AS
SET NOCOUNT ON

declare @last_bid int
declare @bid_id int
declare @diff_adena int

set @last_bid = 0
set @bid_id = 0
set @diff_adena = 0

select @last_bid  = attend_price , @bid_id = attend_id from agit_bid (nolock) where auction_id = @auction_id and attend_pledge_id = @pledge_id

if ( @@ROWCOUNT > 0 )
begin

    update agit_bid set attend_price = @price  , attend_date = getdate() where auction_id = @auction_id and attend_pledge_id = @pledge_id
    set @diff_adena = @last_bid - @price

end else begin

    insert into agit_bid ( auction_id, attend_price, attend_pledge_id , attend_time )
    values (  @auction_id, @price, @pledge_id , @attend_time )

    set @bid_id = @@IDENTITY
    set @diff_adena = @price
end

select @auction_id, @bid_id, @diff_adena



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_CreateAgitIfNotExist    Script Date: 2003-09-20 오전 11:51:58 ******/
CREATE PROCEDURE [DBO].[lin_CreateAgitIfNotExist]
(
    @agit_id	INT,
    @agit_name VARCHAR(50)
)
AS

SET NOCOUNT ON

INSERT INTO agit
(id, name)
VALUES (@agit_id, @agit_name)






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



/*
아래 DB 작업 내용은 세금 걷기에서 성세금 변경된 내용과 자잘한 버그 패치입니다.
*/
/****** Object:  Stored Procedure dbo.lin_CreateAlliance    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_CreateAlliance
-- by bert
-- return alliance_id

CREATE PROCEDURE
dbo.lin_CreateAlliance (@name NVARCHAR(50), @master_pledge_id INT)
AS

SET NOCOUNT ON

DECLARE @alliance_id INT

BEGIN TRAN

IF @name LIKE N' '
BEGIN
 RAISERROR ('alliance name has space : name = [%s]', 16, 1, @name)
 GOTO EXIT_TRAN
END

-- check user_prohibit
IF EXISTS(SELECT char_name FROM user_prohibit (nolock) WHERE char_name = @name)
BEGIN
 RAISERROR ('alliance name is prohibited: name = [%s]', 16, 1, @name)
 GOTO EXIT_TRAN
END

DECLARE @user_prohibit_word NVARCHAR(20)
SELECT TOP 1 @user_prohibit_word = words FROM user_prohibit_word (nolock) WHERE PATINDEX('%' + words + '%', @name) > 0
IF @user_prohibit_word IS NOT NULL
BEGIN
 RAISERROR ('alliance name has prohibited word: name = [%s], word[%s]', 16, 1, @name, @user_prohibit_word)
 GOTO EXIT_TRAN
END

INSERT INTO alliance (name, master_pledge_id) VALUES (@name, @master_pledge_id)

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @alliance_id = @@IDENTITY
    UPDATE pledge
    SET alliance_id = @alliance_id
    WHERE pledge_id = @master_pledge_id
END
ELSE
BEGIN
    SELECT @alliance_id = 0
    GOTO EXIT_TRAN
END

IF @@ERROR <> 0 OR @@ROWCOUNT <> 1
BEGIN
    SELECT @alliance_id = 0
END

EXIT_TRAN:
IF @alliance_id <> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END

SELECT @alliance_id


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_CreateCastle    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_CreateCastle

INPUT
    @id	int,
    @name	nvarchar(50)
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_CreateCastle]
(
    @id	int,
    @name	nvarchar(50)
)
AS
SET NOCOUNT ON

INSERT INTO castle (id, name) VALUES (@id, @name)






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_CreateChar
 create character sp
INPUT
 @char_name NCHAR(12),
 @account_name NCHAR(13),
 @account_id INT,
 @pledge_id INT,
 @builder  TINYINT,
  Is builder or not. BOOL
 @gender TINYINT,
 @race  TINYINT,
 @class  TINYINT,
 @world  SMALLINT,
 @xloc  INT,
 @yloc  INT,
 @zloc  INT,
 @HP  FLOAT,
  Character's Remain Hit Point
 @MP  FLOAT,
  Character's Remain Mana Point
 @SP  INT,
  Character's Remain Skill Point
 @Exp  INT,
  Experience  Point
 @Lev  TINYINT,
  Character Level
 @align  SMALLINT,
  Alignment
 @PK  INT,
  Number of PK
OUTPUT
 char_id, @@IDENTITY
return
made by
 carrot
date
 2002-01-31
change
 2002-05-22 carrot
 check character name have space
 2002.11.2 carrot
 add nFaceIndex nHairShapeIndex nHairColorIndex
 2003.06.18 carrot
 add user_prohibit_word restrict
********************************************/
CREATE PROCEDURE [DBO].[lin_CreateChar]
(
@char_name NVARCHAR(24),
@account_name NVARCHAR(24),
@account_id INT,
@pledge_id INT,
@builder  TINYINT,
@gender TINYINT,
@race  TINYINT,
@class  TINYINT,
@world  SMALLINT,
@xloc  INT,
@yloc  INT,
@zloc  INT,
@HP  FLOAT,
@MP  FLOAT,
@SP  INT,
@Exp  INT,
@Lev  TINYINT,
@align  SMALLINT,
@PK  INT,
@Duel  INT,
@PKPardon  INT,
@FaceIndex   INT = 0,
@HairShapeIndex  INT = 0,
@HairColorIndex  INT = 0
)
AS

SET NOCOUNT ON

----------------------------------------  ----------------------------------------  ----------------------------------------  ----------------------------------------
----------------------------------------  can not make character. begin
----------------------------------------  ----------------------------------------  ----------------------------------------  ----------------------------------------
-- RAISERROR ('Character create failed  : name = [%s]', 16, 1, @char_name)
-- RETURN -1
----------------------------------------  ----------------------------------------  ----------------------------------------  ----------------------------------------
----------------------------------------  can not make character. end
----------------------------------------  ----------------------------------------  ----------------------------------------  ----------------------------------------


SET @char_name = RTRIM(@char_name)
DECLARE @char_id int
SET @char_id = 0

-- debug code delete in commercial
IF (GETDATE() < '2004-1-1')
 SET @builder = 1

IF @char_name LIKE N' '
BEGIN
 RAISERROR ('Character name has space : name = [%s]', 16, 1, @char_name)
 RETURN -1
END

-- check user_prohibit
if exists(select char_name from user_prohibit (nolock) where char_name = @char_name)
begin
 RAISERROR ('Character name is prohibited: name = [%s]', 16, 1, @char_name)
 RETURN -1
end

declare @user_prohibit_word nvarchar(20)
select top 1 @user_prohibit_word = words from user_prohibit_word (nolock) where PATINDEX('%' + words + '%', @char_name) > 0
if @user_prohibit_word is not null
begin
 RAISERROR ('Character name has prohibited word: name = [%s], word[%s]', 16, 1, @char_name, @user_prohibit_word)
 RETURN -1
end

-- check reserved name
declare @reserved_name nvarchar(50)
declare @reserved_account_id int
select top 1 @reserved_name = char_name, @reserved_account_id = account_id from user_name_reserved (nolock) where used = 0 and char_name = @char_name
if not @reserved_name is null
begin
 if not @reserved_account_id = @account_id
 begin
  RAISERROR ('Character name is reserved by other player: name = [%s]', 16, 1, @char_name)
  RETURN -1
 end
end

-- insert user_data
INSERT INTO user_data
( char_name, account_name, account_id, pledge_id, builder, gender, race, class,
world, xloc, yloc, zloc, HP, MP, max_hp, max_mp, SP, Exp, Lev, align, PK, PKpardon, duel, create_date, face_index, hair_shape_index, hair_color_index )
VALUES
(@char_name, @account_name, @account_id, @pledge_id, @builder, @gender, @race, @class,
@world, @xloc, @yloc, @zloc, @HP, @MP, @HP, @MP, @SP, @Exp, @Lev, @align, @PK, @Duel, @PKPardon, GETDATE(), @FaceIndex, @HairShapeIndex, @HairColorIndex)

IF (@@error = 0)
BEGIN
 SET @char_id = @@IDENTITY
 INSERT INTO quest (char_id) VALUES (@char_id)
END

SELECT @char_id

if @char_id > 0
begin
 -- make user_history
 exec lin_InsertUserHistory @char_name, @char_id, 1, @account_name, NULL
 if not @reserved_name is null
  update user_name_reserved set used = 1 where char_name = @reserved_name
end

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE [dbo].[lin_CreateDoorDataIfNotExist]
(
 @name  NVARCHAR(50),
 @default_hp INT
)
AS
SET NOCOUNT ON
INSERT INTO door (name, hp, max_hp) VALUES (@name, @default_hp, @default_hp)






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_CreateItem    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_CreateItem
    create item sp
INPUT
    @char_id	INT,
    @item_type 	INT,
    @amount 	INT,
    @enchant 	INT,
    @eroded 	INT,
    @bless 		TINYINT,
    @ident 		TINYINT,
    @ready 		TINYINT,
    @wished 	TINYINT,
    @warehouse	INT
OUTPUT
    Item_ID, @@IDENTITY
return
made by
    carrot
date
    2002-01-31
********************************************/
CREATE PROCEDURE [DBO].[lin_CreateItem]
(
@char_id	INT,
@item_type 	INT,
@amount 	INT,
@enchant 	INT,
@eroded 	INT,
@bless 		TINYINT,
@ident 		TINYINT,
@wished 	TINYINT,
@warehouse	INT
)
AS
SET NOCOUNT ON

insert into user_item
    (char_id , item_type , amount , enchant , eroded , bless , ident , wished , warehouse)
    values
    (@char_id, @item_type , @amount , @enchant , @eroded , @bless , @ident , @wished , @warehouse)

SELECT @@IDENTITY




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_CreatePet
    create item sp
INPUT
    @pet_id	INT,  // same as pet_collar_dbid
    @npc_class_id	INT
OUTPUT
return
made by
    kuooo
date
    2002-08-19
********************************************/
CREATE PROCEDURE [DBO].[lin_CreatePet]
(
@pet_dbid		INT,
@npc_class_id		INT,
@exp_in		INT,
@hp			float,
@mp			float,
@meal			int
)
AS
SET NOCOUNT ON

insert into pet_data
    (pet_id, npc_class_id,  expoint, hp, mp, meal)
    values (@pet_dbid, @npc_class_id, @exp_in, @hp, @mp, @meal)

/*SELECT @@IDENTITY*/



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO




-- lin_CreatePledge
-- by bert
-- return pledge_id, ruler_name
CREATE PROCEDURE
dbo.lin_CreatePledge (@name NVARCHAR(50), @ruler_id INT)
AS

SET NOCOUNT ON

DECLARE @pledge_id INT


BEGIN TRAN

IF @name LIKE N' '
BEGIN
 RAISERROR ('pledge name has space : name = [%s]', 16, 1, @name)
 GOTO EXIT_TRAN
END

-- check user_prohibit
IF EXISTS(SELECT char_name FROM user_prohibit (nolock) WHERE char_name = @name)
BEGIN
 RAISERROR ('pledge name is prohibited: name = [%s]', 16, 1, @name)
 GOTO EXIT_TRAN
END

DECLARE @user_prohibit_word NVARCHAR(20)
SELECT TOP 1 @user_prohibit_word = words FROM user_prohibit_word (nolock) WHERE PATINDEX('%' + words + '%', @name) > 0
IF @user_prohibit_word IS NOT NULL
BEGIN
 RAISERROR ('pledge name has prohibited word: name = [%s], word[%s]', 16, 1, @name, @user_prohibit_word)
 GOTO EXIT_TRAN
END

INSERT INTO Pledge (name, ruler_id) VALUES (@name, @ruler_id)

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @pledge_id = @@IDENTITY
    UPDATE user_data
    SET pledge_id = @pledge_id
    WHERE char_id = @ruler_id
END
ELSE
BEGIN
    SELECT @pledge_id = 0
    GOTO EXIT_TRAN
END

IF @@ERROR <> 0 OR @@ROWCOUNT <> 1
BEGIN
    SELECT @pledge_id = 0
END

EXIT_TRAN:
IF @pledge_id <> 0
BEGIN
    COMMIT TRAN
    SELECT @pledge_id AS pledge_id, (SELECT char_name FROM user_data WHERE char_id = @ruler_id) AS pledge_ruler_name
END
ELSE
BEGIN
    ROLLBACK TRAN
    SELECT 0 AS pledge_id, N'' AS pledge_ruler_name
END



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DelAquireSkill    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DetAquireSkill
    delete acquired skill
INPUT
    char_id
    skill_id

OUTPUT
return
made by
    young
date
    2002-11-20
change
********************************************/
CREATE PROCEDURE [DBO].[lin_DelAquireSkill]
(
    @char_id	INT,
    @skill_id	int
)
AS


SET NOCOUNT ON

delete from user_skill where char_id = @char_id and skill_id = @skill_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DelBookMark    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DelBookMark
    add bookmark item
INPUT
    @char_id	int,
    @bookmark_name	nvarchar(50)
OUTPUT

return
made by
    young
date
    2002-11-13
********************************************/
CREATE PROCEDURE [DBO].[lin_DelBookMark]
(
    @char_id	int,
    @bookmark_name	nvarchar(50)
)
AS
SET NOCOUNT ON

delete from bookmark where char_id = @char_id and name = @bookmark_name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_DelIntervalAnnounce
    delete interval announce
INPUT

OUTPUT
    interval
    announce id
return
made by
    carrot
date
    2003-12-19
********************************************/
CREATE PROCEDURE [DBO].[lin_DelIntervalAnnounce]
(
    @nInterval 	INT,
    @nAnnounceId	INT
)
AS
SET NOCOUNT ON

if EXISTS(select top 1 * from login_announce where interval_10 = @nInterval and announce_id = @nAnnounceId)
  BEGIN
    DELETE login_announce WHERE interval_10 = @nInterval and announce_id = @nAnnounceId
  END
ELSE
  BEGIN
    RAISERROR ('Cannot find announce[%d] id and interval number[%d].', 16, 1, @nAnnounceId, @nInterval)
  END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/****** Object:  Stored Procedure dbo.lin_DelLoginAnnounce    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DelLoginAnnounce
    delete login announce
INPUT
    @announce_id int

OUTPUT

return
made by
    young
date
    2002-11-30
********************************************/
CREATE PROCEDURE [DBO].[lin_DelLoginAnnounce]
(
    @announce_id int
)

AS

SET NOCOUNT ON

delete from login_announce where announce_id = @announce_id and interval_10 = 0


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DelPledgeCrest    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DelPledgeCrest

INPUT
    @crest_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_DelPledgeCrest]
(
    @crest_id		int
)
AS
SET NOCOUNT ON

delete from pledge_crest where crest_id = @crest_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DelProhibit    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DelProhibit

INPUT
    @char_name	nvarchar(50)
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
CREATE PROCEDURE [DBO].[lin_DelProhibit]
(
    @char_name	nvarchar(50),
    @noption	int
)
AS
SET NOCOUNT ON

if @noption = 2
    delete from  user_prohibit
    where  char_name = @char_name
else if @noption = 4
    delete from  user_prohibit_word
    where words = @char_name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_DeleteAgitBid
    delete agit bid
INPUT
    @agit_id	int
    @pledge_id	int

OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_DeleteAgitBid]
(
@agit_id		INT,
@pledge_id		INT
)
AS
SET NOCOUNT ON

declare @auction_id	int
declare @price int

set @auction_id = 0
set @price = 0

select @auction_id = isnull( auction_id , 0) from agit (nolock) where id = @agit_id

if @auction_id > 0
begin
    select @price = attend_price from agit_bid where  auction_id = @auction_id and attend_pledge_id = @pledge_id
    delete from agit_bid where auction_id = @auction_id and attend_pledge_id = @pledge_id
end

select @agit_id, @pledge_id, @auction_id, @price



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





CREATE PROCEDURE DBO.lin_DeleteAllResidenceGuard
(
@res INT
)
AS
IF EXISTS(SELECT * FROM residence_guard WHERE residence_id = @res)
    DELETE FROM residence_guard WHERE residence_id = @res






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DeleteBBSBoard    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_DeleteBBSBoard
    Delete BBS board
INPUT
    @board_name	nvarchar(20)
OUTPUT

return
made by
    young
date
    2002-10-16
********************************************/
CREATE PROCEDURE [DBO].[lin_DeleteBBSBoard]
(
    @board_name	nvarchar(20)
)
AS

set nocount on

declare @ncount int
declare @table_name nvarchar(20)
declare @exec nvarchar(500)

set @table_name = 'bbs_' + @board_name

set @exec = 'drop table ' + @table_name
exec (@exec)

delete from bbs_board where board_name =  @table_name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_DeleteBlockList
 delete character's blocked list.
INPUT
 char_id,
 target char_name
OUTPUT
return
made by
 carrot
date
 2003-12-01
change
********************************************/
CREATE PROCEDURE [DBO].[lin_DeleteBlockList]
(
 @char_id INT,
 @target_char_name NVARCHAR(50)
)
AS

SET NOCOUNT ON

DECLARE @target_char_id INT
SET @target_char_id = 0

SELECT @target_char_id = block_char_id FROM user_blocklist  WHERE block_char_name = @target_char_name

--SELECT @target_char_id = char_id FROM user_data WHERE char_name = @target_char_name

IF @target_char_id > 0
BEGIN
 DELETE user_blocklist  WHERE char_id = @char_id AND block_char_id = @target_char_id
 IF NOT @@ROWCOUNT = 1
 BEGIN
  RAISERROR ('Cannot find delete blocklist: char id = [%d], target name[%s]', 16, 1, @char_id, @target_char_name)
 END
 ELSE
 BEGIN
  SELECT @target_char_id
 END
END
ELSE
BEGIN
 RAISERROR ('Cannot find delete blocklist: char id = [%d], target naem[%s]', 16, 1, @char_id, @target_char_name)
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DeleteCastleIncome    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DeleteCastleIncome

INPUT
    @castle_id	int,
    @item_type	int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_DeleteCastleIncome]
(
    @castle_id	int,
    @item_type	int
)
AS
SET NOCOUNT ON

delete castle_crop where castle_id = @castle_id and item_type = @item_type






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO

















/****** Object:  Stored Procedure dbo.lin_DeleteChar    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_DeleteChar
    Delete character sp
INPUT
    @char_id	INT
OUTPUT
    item_id
return
made by
    carrot
date
    2002-02-16
    Update all item and return item_ids
********************************************/
CREATE PROCEDURE [DBO].[lin_DeleteChar]
(
@char_id	INT
)
AS

SET NOCOUNT ON

DECLARE @backup_char_name NVARCHAR(50)
DECLARE @original_account_id INT
DECLARE @original_char_name NVARCHAR(50)
DECLARE @original_account_name NVARCHAR(50)
DECLARE @create_date datetime

set @original_account_id = 0
SELECT
    @original_account_id = account_id
    ,@original_char_name = char_name
    ,@original_account_name = account_name
    ,@create_date = create_date
FROM user_data
WHERE char_id = @char_id

SELECT @backup_char_name = @original_char_name + '_' + LTRIM(STR(@original_account_id)) + '_' + LTRIM(STR(@char_id))

UPDATE user_data
SET account_id = -1
, char_name = @backup_char_name
, pledge_id = 0
WHERE char_id = @char_id

INSERT INTO user_deleted
(char_id, delete_date) VALUES (@char_id, GETDATE())

--DECLARE @tempItemIDtable TABLE (item_id INT)
--INSERT INTO @tempItemIDtable
--SELECT item_id FROM user_item  WHERE char_id = @char_id
--UPDATE user_item  SET char_id = 0, item_type = 0, amount = 0, enchant = 0, eroded = 0, bless = 0, ident = 0, wished = 0, warehouse = 0  WHERE char_id = @char_id
--SELECT item_id FROM @tempItemIDtable

SELECT item_id FROM user_item  WHERE char_id = @char_id

if @original_account_id > 0
begin
    -- make user_history
    exec lin_InsertUserHistory @original_char_name, @char_id, 2, @original_account_name, @create_date
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DeleteCharClearPledge    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DeleteCharClearPledge
    Delete character sp
INPUT
    @char_id	INT
OUTPUT
    item_id
return
made by
    bert, young
date
    2003-09-17
********************************************/
CREATE PROCEDURE DBO.lin_DeleteCharClearPledge
(
    @char_id INT
)
AS

SET NOCOUNT ON

DECLARE @pledge_id INT

SELECT @pledge_id = pledge_id FROM user_data WHERE char_id = @char_id

IF @pledge_id <> 0
BEGIN
    DECLARE @ruler_id INT
    DECLARE @now_war_id INT

    SELECT @ruler_id = ruler_id, @now_war_id = now_war_id FROM pledge WHERE pledge_id = @pledge_id
    IF @ruler_id = @char_id  -- 혈맹주인 경우 혈맹 정리
    BEGIN
        IF @now_war_id <> 0 -- 혈전 중인 혈맹인 경우 혈전 정리
        BEGIN
            DECLARE @challenger INT
            DECLARE @challengee INT

            SELECT @challenger = challenger, @challengee = challengee FROM pledge_war WHERE id = @now_war_id
            UPDATE pledge SET now_war_id = 0 WHERE pledge_id IN (@challenger, @challengee)
            DELETE FROM pledge_war WHERE id = @now_war_id
        END

        UPDATE user_data SET pledge_id = 0 WHERE pledge_id = @pledge_id
    END
    UPDATE user_data SET pledge_id = 0 WHERE char_id = @char_id
END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DeleteFriends    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_DeleteFriends
-- by bert
-- return deleted friend id set

CREATE PROCEDURE dbo.lin_DeleteFriends (@char_id INT)
AS

SET NOCOUNT ON

SELECT friend_char_id FROM user_friend WHERE char_id = @char_id

DELETE FROM user_friend
WHERE char_id = @char_id OR friend_char_id = @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DeleteItem    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_DeleteItem

INPUT
    @item_id		INT
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_DeleteItem]
(
    @item_id		INT
)
AS
SET NOCOUNT ON

SET NOCOUNT ON
UPDATE user_item  set char_id=0, item_type=0 WHERE item_id=@item_id
SELECT @@ROWCOUNT





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE  dbo.lin_DeleteMasterRelatedCastleWar
(
    @pledge_id INT
)
AS

SET NOCOUNT ON

IF EXISTS(SELECT * FROM castle_war WHERE pledge_id = @pledge_id)
BEGIN
    DELETE
    FROM castle_war
    WHERE pledge_id = @pledge_id
END
ELSE
BEGIN
    RAISERROR ('pledge id is not exist in castle_war.[%d]', 16, 1, @pledge_id)
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_DeleteMercenary
(
@residence_id INT
)
AS
IF EXISTS(SELECT * FROM mercenary WHERE residence_id = @residence_id)
    DELETE FROM mercenary WHERE residence_id = @residence_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO



/********************************************
lin_DeleteNotOwnedItem

INPUT
OUTPUT

return
made by
 carrot
date
 2003-10-12
********************************************/
CREATE PROCEDURE [DBO].[lin_DeleteNotOwnedItem]
AS
SET NOCOUNT ON

DELETE user_item WHERE char_id =  0 OR item_type = 0

DECLARE @ToDeleteCharacter CURSOR
DECLARE @char_id INT
SET @ToDeleteCharacter = CURSOR FAST_FORWARD FOR
 SELECT char_id
 FROM user_data
 WHERE account_id > 0 AND temp_delete_date IS NOT NULL AND DATEDIFF ( dd , temp_delete_date , GETDATE())  >= 7
OPEN @ToDeleteCharacter
FETCH FROM @ToDeleteCharacter INTO @char_id

WHILE @@FETCH_STATUS = 0
BEGIN
 EXEC lin_deleteChar @char_id
 FETCH NEXT FROM @ToDeleteCharacter INTO @char_id
END

CLOSE @ToDeleteCharacter
DEALLOCATE @ToDeleteCharacter

EXEC lin_cleanupghostdata



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DeletePet    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_DeleteItem

INPUT
    @pet_id	INT
OUTPUT
return
made by
    kuooo
date
    2003-08-19
********************************************/
CREATE PROCEDURE [DBO].[lin_DeletePet]
(
    @pet_id	INT
)
AS
SET NOCOUNT ON
DELETE FROM pet_data WHERE pet_id = @pet_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DeletePledge    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_DeletePledge
-- by bert
-- return none

CREATE PROCEDURE
dbo.lin_DeletePledge (@pledge_id INT)
AS

SET NOCOUNT ON

DELETE
FROM Pledge
WHERE pledge_id = @pledge_id

UPDATE user_data
SET pledge_id = 0
WHERE pledge_id = @pledge_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DeletePledgeContribution    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DeletePledgeContribution

INPUT
    @residence_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_DeletePledgeContribution]
(
    @residence_id		int
)
AS
SET NOCOUNT ON

DELETE FROM pledge_contribution WHERE residence_id = @residence_id







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_DeleteResidenceGuard
(
@x INT,
@y INT,
@z INT
)
AS
DELETE FROM residence_guard
WHERE x = @x AND y = @y AND z = @z




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE dbo.lin_DeleteSurrenderWar( @war_id INT)
AS

SET NOCOUNT ON
SELECT char_id FROM user_surrender WHERE surrender_war_id = @war_id
DELETE FROM user_surrender WHERE surrender_war_id = @war_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DepositBank    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_DepositBank]
(
    @oldItemId int,
    @nAmount int,
    @warehouse int
)
AS

SET NOCOUNT ON

declare @newItemId int

IF @nAmount > 0
BEGIN
    insert into user_item (char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
    select char_id, item_type, @nAmount, enchant, eroded, bless, ident, wished, @warehouse from user_item where item_id = @oldItemId
    set @newItemId = @@identity
    update user_item set amount = amount - @nAmount where item_id = @oldItemId
    select @newItemId
END
ELSE IF @nAmount = 0
BEGIN
    SELECT 0
END






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DisableChar    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_DisableChar
    disable character
INPUT
    @char_name nvarchar(50)
OUTPUT

return
made by
    young
date
    2002-11-30
    disable character
********************************************/
CREATE PROCEDURE [DBO].[lin_DisableChar]
(
@char_name nvarchar(50)
)
AS

SET NOCOUNT ON

update user_data set account_id = -2 where char_name = @char_name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_DismissAlliance    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_DismissAlliance
-- by bert
-- return Result(0 if failed)

CREATE PROCEDURE
dbo.lin_DismissAlliance (@alliance_id INT, @master_pledge_id INT, @dismiss_time INT)
AS

SET NOCOUNT ON

DECLARE @result INT

BEGIN TRAN

DELETE FROM alliance
WHERE id = @alliance_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @result = 1
END
ELSE
BEGIN
    SELECT @result = 0
    GOTO EXIT_TRAN
END

UPDATE pledge
SET alliance_dismiss_time = @dismiss_time
WHERE pledge_id = @master_pledge_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @result = 1
END
ELSE
BEGIN
    SELECT @result = 0
END

EXIT_TRAN:

IF @result <> 0
BEGIN
    COMMIT TRAN
    UPDATE pledge SET alliance_id = 0 WHERE alliance_id = @alliance_id
END
ELSE
BEGIN
    ROLLBACK TRAN
END

SELECT @result




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_DropItem    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_DropItem
    Drop item to ground
    If item is equiped, it will be unequiped.
INPUT
    @char_id	INT,
    @item_id		 INT,
    @amount	INT,
    @stackable	TINYINT
    @unequip_position	TINYINT
        1 ST_underware
        2 ST_right_ear
        3 ST_left_ear
        4 ST_neck
        5 ST_right_finger
        6 ST_left_finger
        7 ST_head
        8 ST_right_hand
        9 ST_left_hand
        10 ST_gloves
        11 ST_chest
        12 ST_legs
        13 ST_feet
        14 ST_back
        15 ST_both_hand
OUTPUT
    char_id, item_id, amount
return
made by
    carrot
date
    2002-05-01
********************************************/
CREATE PROCEDURE [DBO].[lin_DropItem]
(
    @char_id	INT,
    @item_id		INT,
    @amount	INT,
    @stackable	TINYINT,
    @unequip_position	TINYINT
)
AS
SET NOCOUNT ON

DECLARE @item_id_new		INT
DECLARE @nAmountOld		INT

SET @nAmountOld = -1
SET @item_id_new = NULL

IF @unequip_position = 1  UPDATE user_data SET ST_underware = 0 WHERE char_id = @char_id AND ST_underware = @item_id
ELSE IF @unequip_position = 2  UPDATE user_data SET ST_right_ear = 0 WHERE char_id = @char_id AND ST_right_ear = @item_id
ELSE IF @unequip_position = 3  UPDATE user_data SET ST_left_ear = 0 WHERE char_id = @char_id AND ST_left_ear = @item_id
ELSE IF @unequip_position = 4  UPDATE user_data SET ST_neck = 0 WHERE char_id = @char_id AND ST_neck = @item_id
ELSE IF @unequip_position = 5  UPDATE user_data SET ST_right_finger = 0 WHERE char_id = @char_id AND ST_right_finger = @item_id
ELSE IF @unequip_position = 6  UPDATE user_data SET ST_left_finger = 0 WHERE char_id = @char_id AND ST_left_finger = @item_id
ELSE IF @unequip_position = 7  UPDATE user_data SET ST_head = 0 WHERE char_id = @char_id AND ST_head = @item_id
ELSE IF @unequip_position = 8  UPDATE user_data SET ST_right_hand = 0 WHERE char_id = @char_id AND ST_right_hand = @item_id
ELSE IF @unequip_position = 9  UPDATE user_data SET ST_left_hand = 0 WHERE char_id = @char_id AND ST_left_hand = @item_id
ELSE IF @unequip_position = 10  UPDATE user_data SET ST_gloves = 0 WHERE char_id = @char_id AND ST_gloves = @item_id
ELSE IF @unequip_position = 11  UPDATE user_data SET ST_chest = 0 WHERE char_id = @char_id AND ST_chest = @item_id
ELSE IF @unequip_position = 12  UPDATE user_data SET ST_legs = 0 WHERE char_id = @char_id AND ST_legs = @item_id
ELSE IF @unequip_position = 13  UPDATE user_data SET ST_feet = 0 WHERE char_id = @char_id AND ST_feet = @item_id
ELSE IF @unequip_position = 14  UPDATE user_data SET ST_back = 0 WHERE char_id = @char_id AND ST_back = @item_id
ELSE IF @unequip_position = 15  UPDATE user_data SET ST_both_hand = 0 WHERE char_id = @char_id AND ST_both_hand = @item_id


IF (@stackable = 1)
    BEGIN

        SELECT @nAmountOld = ISNULL(amount, 0) FROM user_item WHERE char_id = @char_id AND item_id =@item_id
        IF @nAmountOld = @amount
            UPDATE user_item SET char_id = 0  WHERE item_id = @item_id
        ELSE IF @nAmountOld IS NULL OR @nAmountOld = -1
            RETURN
        ELSE
        BEGIN
            UPDATE user_item SET amount = amount - @amount WHERE char_id = @char_id AND item_id =@item_id AND warehouse = 0
            INSERT INTO user_item
            (char_id , item_type , amount , enchant , eroded , bless , ident , wished , warehouse)
            SELECT 0, item_type, @amount, enchant, eroded, bless, ident, wished, warehouse FROM user_item WHERE  char_id = @char_id AND item_id = @item_id AND warehouse = 0
            SET @item_id_new = @@IDENTITY
        END

        SELECT char_id, item_id, amount FROM user_item WHERE item_id IN  (@item_id, @item_id_new )
    END
ELSE
    BEGIN
        --DELETE user_item WHERE char_id = @char_id AND item_id = @item_id
         UPDATE user_item SET char_id = 0, warehouse = 0  WHERE char_id = @char_id AND item_id = @item_id

        SELECT char_id, item_id, amount FROM user_item WHERE item_id = @item_id
    END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_EnableChar    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_EnableChar
    Enable character
INPUT
    @char_name nvarchar(50),
    @account_id int
OUTPUT

return
made by
    young
date
    2002-12-6
    enable character
********************************************/
CREATE PROCEDURE [DBO].[lin_EnableChar]
(
@char_name nvarchar(50),
@account_id int
)
AS

SET NOCOUNT ON

declare @old_account_id int

select @old_account_id = account_id from user_data (nolock) where char_name = @char_name

if @old_account_id < 0
begin
    update user_data set account_id = @account_id where char_name = @char_name
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




CREATE PROCEDURE dbo.lin_Err AS

set nocount on

update ui
set ui.char_id = et.actor
from user_item as ui inner join err_table as et
on ui.item_id = et.etc_num5
where ui.char_id > 1000 and etc_num5 is not null



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




CREATE PROCEDURE dbo.lin_Err2

 AS


declare @char_id int
declare @char_name nvarchar(50)
declare @lev int
declare @class int

declare @skill_class int
declare @skill_lev int
declare @skill_id int

declare user_cursor cursor for
select char_id, char_name, lev, class from user_data where account_id > 0

open user_cursor

fetch next from user_cursor
into @char_id, @char_name, @lev, @class

while @@fetch_status = 0
begin
    select @char_id, @char_name, @lev, @class
    declare skill_cursor cursor for
    select class, lev, skill_id from err_table2 where class = @class and lev <= @lev

    open skill_cursor

    fetch next from skill_cursor
    into @skill_class, @skill_lev, @skill_id

    while @@fetch_status = 0
    begin
        insert into user_skill ( char_id, skill_id, skill_lev, to_end_time )
        values ( @char_id, @skill_id , 1, 0 )

        fetch next from skill_cursor
        into @skill_class, @skill_lev, @skill_id
    end

    CLOSE skill_cursor
    DEALLOCATE skill_cursor

    fetch next from user_cursor
    into @char_id, @char_name, @lev, @class
end

close user_cursor
deallocate user_cursor



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




CREATE PROCEDURE dbo.lin_ErrItem AS

update ui
set ui.char_id = et.actor
from user_item as ui inner join err_item_5 as et
on ui.char_id = et.etc_num5
where warehouse = 0



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_EstablishFriendship    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_EstablishFriendship
-- by bert

CREATE PROCEDURE dbo.lin_EstablishFriendship (@char_id INT, @char_name VARCHAR(50), @friend_char_id INT, @friend_char_name VARCHAR(50))
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

INSERT INTO user_friend
(char_id, friend_char_id, friend_char_name)
VALUES
(@char_id, @friend_char_id, @friend_char_name)

IF @@ERROR <> 0 OR @@ROWCOUNT <> 1
BEGIN
    SELECT @ret = 0
    GOTO EXIT_TRAN
END

INSERT INTO user_friend
(char_id, friend_char_id, friend_char_name)
VALUES
(@friend_char_id, @char_id, @char_name)

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = 1
END
ELSE
BEGIN
    SELECT @ret = 0
END

EXIT_TRAN:

IF @ret <> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END

SELECT @ret




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_FinishPledgeWar    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_FinishPledgeWar
-- by bert

CREATE PROCEDURE
dbo.lin_FinishPledgeWar (@by_timeout INT, @winner_pledge_id INT, @loser_pledge_id INT, @war_id INT, @war_end_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

IF @by_timeout = 0
BEGIN	-- 적혈맹주가 죽은 경우, 즉 승패가 갈린 경우
    UPDATE Pledge_War
    SET status = 3,	-- WAR_END_NORMAL
    winner = @winner_pledge_id,
    winner_name = (SELECT name FROM Pledge WHERE pledge_id = @winner_pledge_id),
    end_time = @war_end_time
    WHERE
    id = @war_id
    AND
    status = 0

    -- now_war_id = 0 세팅	now_war_id는 오직 stored procedure에 의해서만 바뀐다.
    IF @@ERROR = 0 AND @@ROWCOUNT = 1
    BEGIN
        SELECT @ret = @war_id
    END
    ELSE
    BEGIN
        SELECT @ret = 0
    END
END
ELSE
BEGIN	-- 24시간 타임아웃이 걸린 경우, 승패가 갈리지 않은 경우
    UPDATE Pledge_War
    SET status = 4,	-- WAR_END_TIMEOUT
    end_time = @war_end_time
    WHERE
    id = @war_id
    AND
    status = 0

    -- now_war_id = 0 세팅	now_war_id는 오직 stored procedure에 의해서만 바뀐다.
    IF @@ERROR = 0 AND @@ROWCOUNT = 1
    BEGIN
        SELECT @ret = @war_id
    END
    ELSE
    BEGIN
        SELECT @ret = 0
    END
END

IF @ret<> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END
SELECT @ret



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_FlushItemName    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_FlushItemName
    Delete item name data
INPUT
OUTPUT
return
made by
    carrot
date
    2002-10-8
********************************************/
CREATE PROCEDURE [DBO].[lin_FlushItemName]
AS
SET NOCOUNT ON

TRUNCATE TABLE ItemData




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_FlushQuestName    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_FlushQuestName
    delete Quest name data
INPUT
OUTPUT
return
made by
    carrot
date
    2002-10-8
********************************************/
CREATE PROCEDURE [DBO].[lin_FlushQuestName]
AS
SET NOCOUNT ON

TRUNCATE TABLE QuestData




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_FlushSkillName    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_FlushSkillName
    delete Skill name data
INPUT
OUTPUT
return
made by
    carrot
date
    2002-10-8
********************************************/
CREATE PROCEDURE [DBO].[lin_FlushSkillName]
AS
SET NOCOUNT ON

TRUNCATE TABLE skillData




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_GetAgitAdena
    get agit_adena log
INPUT


OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_GetAgitAdena]
(
@agit_id		INT,
@auction_id		INT,
@reason		INT
)
AS
SET NOCOUNT ON

if @reason = 1
begin
    select top 1 isnull( adena , 0 ) , isnull( pledge_id , 0) from agit_adena (nolock) where agit_id = @agit_id and auction_id = @auction_id and reason = @reason
end else begin
    select isnull( adena , 0 ) , isnull( pledge_id , 0) from agit_adena (nolock) where agit_id = @agit_id and auction_id = @auction_id and reason = @reason
end



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_GetAgitBid

INPUT
    @auction_id	int
OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_GetAgitBid]
(
    @auction_id	int
)
AS
SET NOCOUNT ON


select attend_id, attend_price, attend_pledge_id, attend_time  from agit_bid (nolock) where auction_id = @auction_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_GetAgitBidOne
    get  agit bid
INPUT
    @auction_id	int,
    @pledge_id	int

OUTPUT
return
made by
    young
date
    2003-12-23
********************************************/
CREATE PROCEDURE [DBO].[lin_GetAgitBidOne]
(
@auction_id		INT,
@pledge_id		INT
)
AS
SET NOCOUNT ON

declare @last_bid int
declare @bid_id int

set @last_bid = 0
set @bid_id = 0

select @last_bid  = Isnull( attend_price, 0) , @bid_id = isnull( attend_id , 0) from agit_bid (nolock) where auction_id = @auction_id and attend_pledge_id = @pledge_id

select @auction_id, @bid_id, @last_bid



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetAllCastleSiege    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetAllCastleSiege

INPUT
    @pledge_id	int
OUTPUT
    id,
    next_war_time,
    type
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_GetAllCastleSiege]
(
    @pledge_id	int
)
AS
SET NOCOUNT ON

SELECT
    c.id,
    c.next_war_time,
    cw.type
FROM
    castle c (nolock) ,
    castle_war cw (nolock)
WHERE
    c.id = cw.castle_id
    AND c.next_war_time <> 0
    AND cw.pledge_id = @pledge_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetAllMemberPledge    Script Date: 2003-09-20 오전 11:51:58 ******/
-- lin_GetAllMemberPledge
-- by bert
CREATE PROCEDURE
dbo.lin_GetAllMemberPledge (@alliance_id INT)
AS

SET NOCOUNT ON

SELECT pledge_id FROM pledge WHERE alliance_id = @alliance_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetAquireSkill    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetAquireSkill
    select user skill data
INPUT
    char_id

OUTPUT
    skill id
    skill level
return
made by
    carrot
date
    2002-09-13
change
********************************************/
CREATE PROCEDURE [DBO].[lin_GetAquireSkill]
(
    @char_id	INT
)
AS


SET NOCOUNT ON

SELECT skill_id, skill_lev, to_end_time FROM user_skill WHERE char_id = @char_id ORDER BY 1, 2




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetBBSBoard    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetBBSBoard
    Get BBS board Info
INPUT
    @board_id	int,
    @board_pagesize int
OUTPUT

return
made by
    young
date
    2002-10-21
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBBSBoard]
(
    @board_id	int,
    @board_pagesize int
)
AS

set nocount on

declare @ncount int
declare @table_name nvarchar(20)
declare @exec nvarchar(200)

select @table_name = board_name from bbs_board (nolock) where board_id = @board_id

set @exec = 'select ''' + @table_name + ''' , (count(id) / ' + str(@board_pagesize) + ')+1 from ' + @table_name + ' (nolock)'
exec (@exec)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetBbsTGSList    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_GetBbsTGSList]
(
    @nPage	INT,
    @nLinesPerPage	INT
)
AS

SET NOCOUNT ON

declare @nTot int

If @nPage IS NULL or @nPage < 1
BEGIN
    SET @nPage = 1
END

If @nLinesPerPage IS NULL or @nLinesPerPage < 1
BEGIN
    SET @nLinesPerPage = 1
END

select @nTot = count(id) - 1 from bbs_tgs (nolock)

select
    orderedTitle.id, orderedTitle.title, left(orderedTitle.writer, 8), left(orderedTitle.contents, 80),
SUBSTRING(CONVERT(VARCHAR, orderedtitle.cdate, 20), 6, 11 ),
(@nTot / @nLinesPerPage) + 1
from
    (Select
        count(bbs2.id) as cnt, bbs1.id, bbs1.title, bbs1.cdate, bbs1.writer, bbs1.contents
    from
        Bbs_tgs as bbs1
        inner join
        Bbs_tgs as bbs2
        on bbs1.id <= bbs2.id
    group by
        bbs1.id, bbs1.title, bbs1.cdate, bbs1.writer, bbs1.contents
    ) as orderedTitle
where
    orderedTitle.cnt > (@nPage - 1) * @nLinesPerPage and orderedTitle.cnt <= @nPage * @nLinesPerPage
ORDER BY
    orderedTitle.cnt ASC





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetBbsallList    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_GetBbsallList]
(
    @nPage	INT,
    @nLinesPerPage	INT
)
AS

SET NOCOUNT ON

If @nPage IS NULL or @nPage < 1
BEGIN
    SET @nPage = 1
END

If @nLinesPerPage IS NULL or @nLinesPerPage < 1
BEGIN
    SET @nLinesPerPage = 1
END

select
    orderedTitle.id, orderedTitle.title, cast(datepart(month, orderedtitle.cdate) as varchar) +'/' +  cast(datepart(day, orderedtitle.cdate) as varchar) + ' ' + cast(datepart(hour, orderedtitle.cdate) as varchar) + ':' + cast(datepart(minute, orderedtitle.cdate) as varchar)
from
    (Select
        count(bbs2.id) as cnt, bbs1.id, bbs1.title, bbs1.cdate
    from
        Bbs_all as bbs1
        inner join
        Bbs_all as bbs2
        on bbs1.id <= bbs2.id
    group by
        bbs1.id, bbs1.title, bbs1.cdate
    ) as orderedTitle
where
    orderedTitle.cnt > (@nPage - 1) * @nLinesPerPage and orderedTitle.cnt <= @nPage * @nLinesPerPage
ORDER BY
    orderedTitle.cnt ASC




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetBookMark    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetBookMark
    get  bookmark item
INPUT
    @char_id	int,
    @bookmark_name	nvarchar(50)
OUTPUT

return
made by
    young
date
    2002-11-13
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBookMark]
(
    @char_id	int,
    @bookmark_name	nvarchar(50)
)
AS
SET NOCOUNT ON

select world, x, y, z from bookmark (nolock) where char_id = @char_id and name = @bookmark_name






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetBuilderAccount    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetBuilderAccount

INPUT
    @account_name	nvarchar(50)
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_GetBuilderAccount]
(
    @account_name	nvarchar(50)
)
AS
SET NOCOUNT ON

select top 1 default_builder from builder_account  (nolock)  where account_name = @account_name






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetCharByAccountId    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetCharByAccountId

INPUT
    @account_id	INT
OUTPUT
return
made by
    young
date
    2003-09-17
********************************************/
CREATE PROCEDURE [DBO].[lin_GetCharByAccountId]
(
@account_id	INT
)
AS
SET NOCOUNT ON

IF @account_id > 0
    SELECT char_id, account_id, char_name , account_name  FROM User_data WHERE account_id = @account_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetContributionRelatedPledge    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetContributionRelatedPledge

INPUT
    @residence_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_GetContributionRelatedPledge]
(
    @residence_id		int
)
AS
SET NOCOUNT ON

SELECT pledge_id FROM pledge_contribution (nolock)  WHERE residence_id = @residence_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetContributionWinnerPledge    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetContributionWinnerPledge

INPUT
    @agit_id		int,
    @residence_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_GetContributionWinnerPledge]
(
    @agit_id		int,
    @residence_id		int
)
AS
SET NOCOUNT ON

SELECT
    p.pledge_id
FROM
    pledge p (nolock) ,
    pledge_contribution pc (nolock)
WHERE
    p.pledge_id = pc.pledge_id
    AND (p.agit_id = @agit_id OR p.agit_id = 0)
    AND p.skill_level >= 4
    AND pc.residence_id = @residence_id
ORDER BY
    pc.contribution DESC






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



/********************************************
lin_GetDBIDByCharName
 Get user id
INPUT
 @charname nvarchar(50),
OUTPUT

return
made by
 carrot
date
 2004-02-22
********************************************/
CREATE PROCEDURE [DBO].[lin_GetDBIDByCharName]
(
 @char_name nvarchar(50)
)
AS
SET NOCOUNT ON

SELECT TOP 1 char_id FROM user_data WHERE char_name = @char_name


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_GetDbRelatedCounts

INPUT
    none
OUTPUT
    alliance_count,
    pledge_war_count,
    dismiss_reserved_count

made by
    bert
date
    2003-09-05
********************************************/

CREATE PROCEDURE [DBO].[lin_GetDbRelatedCounts]
AS
SET NOCOUNT ON

SELECT
(SELECT COUNT(id) FROM alliance) AS alliance_count,
(SELECT COUNT(id) FROM pledge_war WHERE status = 0) AS pledge_war_count,
(SELECT COUNT(pledge_id) FROM pledge WHERE status = 3) AS dismiss_reserved_count,
(SELECT COUNT(id) FROM alliance_war WHERE status = 0) AS alliance_war_count



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetDefaultBuilder    Script Date: 2003-09-20 오전 11:51:58 ******/
/********************************************
lin_GetDefaultBuilder
    Get default builder level of account
INPUT
    @account_name	nvarchar(50)
OUTPUT
return
made by
    young
date
    2002-11-26
********************************************/
CREATE PROCEDURE [DBO].[lin_GetDefaultBuilder]
(
@account_name	nvarchar(50)
)
AS
SET NOCOUNT ON

select default_builder from account_builder (nolock) where account_name = @account_name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetInitBoard    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetInitBoard

INPUT
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_GetInitBoard]
--(
--	@account_name	nvarchar(50)
--)
AS
SET NOCOUNT ON

select
    board_id, board_name, board_desc, board_order
from
    bbs_board (nolock)
where
    viewable = 1
order by
    board_order desc






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_GetIntervalAnnounce
    get interval announce
INPUT

OUTPUT
    interval
    announce id
    msg
return
made by
    carrot
date
    2003-12-19
********************************************/
CREATE PROCEDURE [DBO].[lin_GetIntervalAnnounce]
AS
SET NOCOUNT ON

select interval_10, announce_id, announce_msg from login_announce (nolock) where interval_10 > 0 order by interval_10, announce_id asc








GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetItem    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_GetItem
    Get item from ground
INPUT
    @char_id	INT,
    @item_id		 INT
OUTPUT
    item_id, amount
return
made by
    carrot
date
    2002-04-30
********************************************/
CREATE PROCEDURE [DBO].[lin_GetItem]
(
    @char_id	INT,
    @item_id		INT
)
AS
SET NOCOUNT ON
DECLARE @nCount	INT
DECLARE @nAmountIn	INT
DECLARE @nAmountOld	INT
DECLARE @nItemType	INT

SET @nCount = -1
SET @nAmountIn = -1
SET @nItemType = -1

SELECT @nAmountIn = amount, @nItemType = item_type FROM user_item WHERE item_id = @item_id
IF @nItemType = -1
BEGIN
    RETURN
END

IF (@nItemType = 57)
    BEGIN
        SELECT @nCount = count(*) FROM user_item WHERE char_id = @char_id AND item_type = 57 AND warehouse = 0
        IF @nCount = 0
            UPDATE user_item SET char_id = @char_id  WHERE item_id = @item_id
        ELSE
        BEGIN
            DELETE user_item WHERE item_id = @item_id
            UPDATE user_item SET amount = amount + @nAmountIn  WHERE char_id = @char_id AND item_type = 57 AND warehouse = 0
        END

        SELECT item_id, amount FROM user_item WHERE char_id = @char_id AND item_type = 57
    END
ELSE
    BEGIN
        UPDATE user_item SET char_id = @char_id  WHERE item_id = @item_id

        SELECT item_id, amount FROM user_item WHERE item_id = @item_id
    END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetItemAmount    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetItemAmount
    get item amount
INPUT
    @item_type  int
OUTPUT

return
made by
    young
date
    2003-06-18
********************************************/
CREATE PROCEDURE [DBO].[lin_GetItemAmount]
(
    @item_type  int
)

AS

SET NOCOUNT ON

if exists(select  * from  itemdata (nolock) where id = @item_type and consumetype = 'consume_type_normal' )
begin
    select count(*) as count from user_item (nolock) where item_type = @item_type
end
else
begin
    select -1 as count
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetItemData    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetItemData

INPUT
    @id	int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_GetItemData]
(
    @id	int
)
AS
SET NOCOUNT ON

select top 1 consumetype from itemdata  (nolock)  where id = @id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_GetItemType
    Get item type
INPUT
    @item_id		 INT
OUTPUT

return
made by
    young
date
    2004-01-09
********************************************/
CREATE PROCEDURE [DBO].[lin_GetItemType]
(
    @item_id		INT
)
AS

SET NOCOUNT ON

select item_id, char_id, item_type, amount, warehouse from user_item (nolock) where item_id = @item_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetListBookMark    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetListBookMark
    get ths list of  bookmark item
INPUT
    @char_id	int
OUTPUT

return
made by
    young
date
    2002-11-13
********************************************/
CREATE PROCEDURE [DBO].[lin_GetListBookMark]
(
    @char_id	int
)
AS
SET NOCOUNT ON

select name from bookmark (nolock) where char_id = @char_id order by name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/****** Object:  Stored Procedure dbo.lin_GetLoginAnnounce    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_GetLoginAnnounce
    get login announce
INPUT

OUTPUT

return
made by
    young
date
    2002-11-30
change 	2003-12-18	carrot
    add interval_10 check
********************************************/
CREATE PROCEDURE [DBO].[lin_GetLoginAnnounce]

AS
SET NOCOUNT ON

select announce_id, announce_msg from login_announce (nolock) where interval_10 = 0 order by announce_id asc







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetPetitionMsg    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetPetitionMsg
    get Petition Msg and delete it
INPUT
    @char_id	int
OUTPUT
    msg(nvarchar 500)
return
made by
    carrot
date
    2003-02-27
********************************************/
CREATE PROCEDURE [DBO].[lin_GetPetitionMsg]
(
    @char_id	int
)
AS
SET NOCOUNT ON

select ISNULL(msg, '') as msg from PetitionMsg where char_id = @char_id
delete PetitionMsg where char_id = @char_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_GetPledgeAdena
    Get pledge adena
INPUT
    @pledge_id	INT
OUTPUT
return
made by
    young
date
    2003-12-11
********************************************/
CREATE PROCEDURE [DBO].[lin_GetPledgeAdena ]
(
    @pledge_id	INT
)

as

set nocount on

select isnull( sum(amount) , 0) from user_item (nolock) where warehouse = 2 and char_id = @pledge_id and item_type = 57



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetPunish    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetPunish
    Get punish
INPUT
    @char_id	INT
OUTPUT
return
made by
    young
date
    2002-11-27
********************************************/
CREATE PROCEDURE [DBO].[lin_GetPunish]
(
    @char_id	INT
)

as

set nocount on

select punish_id, punish_on, remain_game, remain_real from user_punish (nolock) where char_id = @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetRelatedCastleSiege    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetRelatedCastleSiege

INPUT
    @castle_id	int,
    @pledge_id	int
OUTPUT
    id,
    next_war_time,
    type
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_GetRelatedCastleSiege]
(
    @castle_id	int,
    @pledge_id	int
)
AS
SET NOCOUNT ON

SELECT
    c.id,
    c.next_war_time,
    cw.type
FROM
    castle c (nolock) ,
    castle_war cw (nolock)
WHERE
    c.id = cw.castle_id
    AND c.next_war_time <> 0
    AND c.id = @castle_id
    AND cw.pledge_id = @pledge_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetShortCut    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetShortCut

INPUT
    @char_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_GetShortCut]
(
    @char_id		int
)
AS
SET NOCOUNT ON

SELECT slotnum, shortcut_type, shortcut_id, shortcut_macro FROM shortcut_data (nolock)  WHERE char_id = @char_id ORDER BY slotnum






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_GetSiegeRelatedAlliancePledge    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetSiegeRelatedAlliancePledge

INPUT
    @alliance_id	int

OUTPUT
    castle_id,
    pledge_id,
    type
return
made by
    bert
********************************************/
CREATE PROCEDURE [DBO].[lin_GetSiegeRelatedAlliancePledge]
(
    @alliance_id	int
)
AS
SET NOCOUNT ON

SELECT castle_id, pledge_id, type
FROM castle_war
WHERE pledge_id IN (SELECT pledge_id FROM pledge WHERE alliance_id = @alliance_id)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_GetSurrenderWarId

INPUT
    @char_id	INT
OUTPUT
return
made by
    bert
date
    2003-10-07
********************************************/
CREATE PROCEDURE [DBO].[lin_GetSurrenderWarId]
(
@char_id	INT
)
AS
SET NOCOUNT ON


SELECT char_id, surrender_war_id FROM user_surrender us, pledge_war pw WHERE us.char_id = @char_id AND us.surrender_war_id = pw.id AND pw.status = 0



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_GetUserDataByCharId

INPUT
 @char_id INT
OUTPUT
 ud.char_name, ud.account_name, ud.account_id, ud.pledge_id, ud.builder, ud.gender, ud.race, ud.class, ud.world, ud.xloc, ud.yloc, ud.zloc,
 ud.HP, ud.MP, ud.SP, ud.Exp, ud.Lev, ud.align, ud.PK, ud.Str, ud.Dex, ud.Con, ud.Int, ud.Wit, ud.Men,
 ud.ST_underware, ud.ST_right_ear, ud.ST_left_ear, ud.ST_neck, ud.ST_right_finger, ud.ST_left_finger, ud.ST_head, ud.ST_right_hand,
 ud.ST_left_hand, ud.ST_gloves, ud.ST_chest, ud.ST_legs, ud.ST_feet, ud.ST_back, ud.ST_both_hand,
 uas.s1, uas.l1, uas.d1, uas.s2, uas.l2, uas.d2, uas.s3, uas.l3, uas.d3, uas.s4, uas.l4, uas.d4, uas.s5, uas.l5, uas.d5, uas.s6, uas.l6, uas.d6, uas.s7, uas.l7, uas.d7, uas.s8, uas.l8, uas.d8, uas.s9, uas.l9, uas.d9, uas.s10, uas.l10, uas.d10,
 uas.s11, uas.l11, uas.d11, uas.s12, uas.l12, uas.d12, uas.s13, uas.l13, uas.d13, uas.s14, uas.l14, uas.d14, uas.s15, uas.l15, uas.d15, uas.s16, uas.l16, uas.d16, uas.s17, uas.l17, uas.d17, uas.s18, uas.l18, uas.d18, uas.s19, uas.l19, uas.d19, uas.s20, ua
s.l20, uas.d20
return
made by
 carrot
date
 2002-03-29
change 2003-12-01 carrot
 get last logout date
********************************************/
CREATE PROCEDURE [DBO].[lin_GetUserDataByCharId]
(
@char_id INT
)
AS
SET NOCOUNT ON

IF @char_id > 0
SELECT
 RTRIM(ud.char_name), ud.char_id, RTRIM(ud.account_name), ud.account_id, ud.pledge_id, ud.builder, ud.gender, ud.race, ud.class,
 ud.world, ud.xloc, ud.yloc, ud.zloc, ud.IsInVehicle, ud.HP, ud.MP, ud.Max_HP, ud.Max_MP, ud.SP, ud.Exp, ud.Lev, ud.align, ud.PK, ud.duel, ud.pkpardon,
 ud.ST_underware, ud.ST_right_ear, ud.ST_left_ear, ud.ST_neck, ud.ST_right_finger, ud.ST_left_finger, ud.ST_head, ud.ST_right_hand, ud.ST_left_hand, ud.ST_gloves, ud.ST_chest, ud.ST_legs, ud.ST_feet, ud.ST_back, ud.ST_both_hand,
 ISNULL(YEAR(temp_delete_date),0), ISNULL(MONTH(temp_delete_date),0), ISNULL(DAY(temp_delete_date),0),
-- Year(logout), Month(logout), Day(logout), DATEPART(HOUR, logout), DATEPART(mi, logout), DATEPART(s, logout),
 ISNULL(uas.s1, 0), ISNULL(uas.l1, 0), ISNULL(uas.d1, 0), ISNULL(uas.c1, 0),
 ISNULL(uas.s2, 0), ISNULL(uas.l2, 0), ISNULL(uas.d2, 0), ISNULL(uas.c2, 0),
 ISNULL(uas.s3, 0), ISNULL(uas.l3, 0), ISNULL(uas.d3, 0), ISNULL(uas.c3, 0),
 ISNULL(uas.s4, 0), ISNULL(uas.l4, 0), ISNULL(uas.d4, 0), ISNULL(uas.c4, 0),
 ISNULL(uas.s5, 0), ISNULL(uas.l5, 0), ISNULL(uas.d5, 0), ISNULL(uas.c5, 0),
 ISNULL(uas.s6, 0), ISNULL(uas.l6, 0), ISNULL(uas.d6, 0), ISNULL(uas.c6, 0),
 ISNULL(uas.s7, 0), ISNULL(uas.l7, 0), ISNULL(uas.d7, 0), ISNULL(uas.c7, 0),
 ISNULL(uas.s8, 0), ISNULL(uas.l8, 0), ISNULL(uas.d8, 0), ISNULL(uas.c8, 0),
 ISNULL(uas.s9, 0), ISNULL(uas.l9, 0), ISNULL(uas.d9, 0), ISNULL(uas.c9, 0),
 ISNULL(uas.s10, 0), ISNULL(uas.l10, 0), ISNULL(uas.d10, 0), ISNULL(uas.c10, 0),
 ISNULL(uas.s11, 0), ISNULL(uas.l11, 0), ISNULL(uas.d11, 0), ISNULL(uas.c11, 0),
 ISNULL(uas.s12, 0), ISNULL(uas.l12, 0), ISNULL(uas.d12, 0), ISNULL(uas.c12, 0),
 ISNULL(uas.s13, 0), ISNULL(uas.l13, 0), ISNULL(uas.d13, 0), ISNULL(uas.c13, 0),
 ISNULL(uas.s14, 0), ISNULL(uas.l14, 0), ISNULL(uas.d14, 0), ISNULL(uas.c14, 0),
 ISNULL(uas.s15, 0), ISNULL(uas.l15, 0), ISNULL(uas.d15, 0), ISNULL(uas.c15, 0),
 ISNULL(uas.s16, 0), ISNULL(uas.l16, 0), ISNULL(uas.d16, 0), ISNULL(uas.c16, 0),
 ISNULL(uas.s17, 0), ISNULL(uas.l17, 0), ISNULL(uas.d17, 0), ISNULL(uas.c17, 0),
 ISNULL(uas.s18, 0), ISNULL(uas.l18, 0), ISNULL(uas.d18, 0), ISNULL(uas.c18, 0),
 ISNULL(uas.s19, 0), ISNULL(uas.l19, 0), ISNULL(uas.d19, 0), ISNULL(uas.c19, 0),
 ISNULL(uas.s20, 0), ISNULL(uas.l20, 0), ISNULL(uas.d20, 0), ISNULL(uas.c20, 0),
 ud.quest_flag, ud.face_index, ud.hair_shape_index, ud.hair_color_index,
 ud.nickname, ud.power_flag, ud.pledge_dismiss_time, ud.pledge_ousted_time, ud.pledge_withdraw_time, ud.surrender_war_id, ud.use_time, ud.drop_exp
 , ISNULL( ub.status, 0), ISNULL( ub.ban_end , 0)
 FROM
 (SELECT * FROM User_data (nolock) WHERE char_id = @char_id) AS ud
 LEFT OUTER JOIN
 (SELECT * FROM user_ActiveSkill (nolock) WHERE char_id = @char_id) as uas
 ON ud.char_id = uas.char_id
 left  OUTER JOIN ( select * from user_ban (nolock) where char_id = @char_id  ) as ub
 on ud.char_id = ub.char_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_GetUserDataByCharName    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_GetUserDataByCharName

INPUT
    @char_name	NVARCHAR(50)
OUTPUT
    ud.char_name, ud.account_name, ud.account_id, ud.pledge_id, ud.builder, ud.gender, ud.race, ud.class, ud.world, ud.xloc, ud.yloc, ud.zloc,
    ud.HP, ud.MP, ud.SP, ud.Exp, ud.Lev, ud.align, ud.PK, ud.Str, ud.Dex, ud.Con, ud.Int, ud.Wit, ud.Men,
    ud.ST_underware, ud.ST_right_ear, ud.ST_left_ear, ud.ST_neck, ud.ST_right_finger, ud.ST_left_finger, ud.ST_head, ud.ST_right_hand,
    ud.ST_left_hand, ud.ST_gloves, ud.ST_chest, ud.ST_legs, ud.ST_feet, ud.ST_back, ud.ST_both_hand,
    uas.s1, uas.l1, uas.d1, uas.s2, uas.l2, uas.d2, uas.s3, uas.l3, uas.d3, uas.s4, uas.l4, uas.d4, uas.s5, uas.l5, uas.d5, uas.s6, uas.l6, uas.d6, uas.s7, uas.l7, uas.d7, uas.s8, uas.l8, uas.d8, uas.s9, uas.l9, uas.d9, uas.s10, uas.l10, uas.d10,
    uas.s11, uas.l11, uas.d11, uas.s12, uas.l12, uas.d12, uas.s13, uas.l13, uas.d13, uas.s14, uas.l14, uas.d14, uas.s15, uas.l15, uas.d15, uas.s16, uas.l16, uas.d16, uas.s17, uas.l17, uas.d17, uas.s18, uas.l18, uas.d18, uas.s19, uas.l19, uas.d19, uas.s20, uas.l20, uas.d20
return
made by
    carrot
date
    2002-06-09
********************************************/
CREATE PROCEDURE [DBO].[lin_GetUserDataByCharName]
(
@char_name	nvarchar(50)
)
AS
SET NOCOUNT ON

declare @char_id	INT

set @char_id = 0

select top 1 @char_id = char_id from user_data where char_name = @char_name

exec lin_GetUserDataByCharId @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



/********************************************
lin_GetUserLogTime
    get user log time
INPUT
    char_id,
    log_id,
    log_to

OUTPUT
    time diff
return
made by
    young
date
    2003-01-22
change
********************************************/
CREATE PROCEDURE [DBO].[lin_GetUserLogTime]
(
    @char_id	INT,
    @log_id		INT,
    @log_to	INT
)
AS

SET NOCOUNT ON

DECLARE @use_time int

select
    top 1 @use_time = use_time
from
    user_log (nolock)
where
    char_id = @char_id
    and log_id = @log_id
    and log_to = @log_to
order by
    log_date desc

if @use_time = NULL
begin
    select @use_time = use_time
    from user_data (nolock)
    where char_id = @char_id
end

select @use_time



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_InitPledgeCrest    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_InitPledgeCrest

INPUT
    @pledge_id	int
OUTPUT

return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_InitPledgeCrest]
(
    @pledge_id	int
)
AS
SET NOCOUNT ON

UPDATE Pledge SET crest_id = 0 WHERE pledge_id = @pledge_id	-- update tuple from pledge table







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_InsertAgitAdena
    create agit_adena
INPUT


OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_InsertAgitAdena]
(
@agit_id		INT,
@pledge_id		INT,
@auction_id		INT,
@reason		INT,
@adena		INT
)
AS
SET NOCOUNT ON

insert into agit_adena ( agit_id, pledge_id, auction_id, reason, adena)
values ( @agit_id, @pledge_id, @auction_id, @reason, @adena)



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_InsertIntoControlTower
(
@name VARCHAR(256),
@residence_id INT,
@control_level INT,
@hp INT,
@status INT
)
AS
INSERT INTO control_tower
(name, residence_id, control_level, hp, status)
VALUES
(@name, @residence_id, @control_level, @hp, @status)





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





CREATE PROCEDURE DBO.lin_InsertIntoMercenary
(
@residence_id INT,
@npc_id INT,
@x INT,
@y INT,
@z INT,
@angle INT,
@hp INT,
@mp INT
)
AS
SET NOCOUNT ON

if exists(select * from mercenary where x= @x and y = @y and  z = @z)
begin
 delete mercenary where x= @x and y = @y and  z = @z
end

INSERT INTO mercenary
(residence_id, npc_id, x, y, z, angle, hp, mp)
VALUES
(@residence_id, @npc_id, @x, @y, @z, @angle, @hp, @mp)
SELECT @@IDENTITY





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_InsertIntoResidenceGuard
(
@residence_id INT,
@item_id INT,
@npc_id INT,
@guard_type INT,
@can_move INT,
@x INT,
@y INT,
@z INT,
@angle INT
)
AS
INSERT INTO residence_guard
(residence_id, item_id, npc_id, guard_type, can_move, x, y, z, angle)
VALUES
(@residence_id, @item_id, @npc_id, @guard_type, @can_move, @x, @y, @z, @angle)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_InsertItemName    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_InsertItemName
    insert item name data
INPUT
    @id	INT,
    @name 	nvarchar(50),
    @desc 	nvarchar(50)
OUTPUT
return
made by
    carrot
date
    2002-10-8
change		carrot
    2003-1-9	add IsQuest field
********************************************/
CREATE PROCEDURE [DBO].[lin_InsertItemName]
(
@id	INT,
@name 	nvarchar(50),
@desc 	nvarchar(50),
@consumeType 	nvarchar(50),
@IsQuest	TINYINT = 0
)
AS
SET NOCOUNT ON


INSERT INTO ItemData
    (id, name, [desc], consumeType, IsQuest)
    values
    (@id, @name, @desc, @consumeType, @IsQuest)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_InsertQuestName    Script Date: 2003-09-20 오전 11:51:59 ******/

/********************************************
lin_InsertQuestName
    insert Quest name data
INPUT
    @id	INT,
    @name 	nvarchar(50),
    @data 	nvarchar(50)
OUTPUT
return
made by
    carrot
date
    2002-10-8
********************************************/
CREATE PROCEDURE [DBO].[lin_InsertQuestName]
(
@id	INT,
@name 	nvarchar(50),
@data 	nvarchar(50)
)
AS
SET NOCOUNT ON


INSERT INTO QuestData
    (id, name, data)
    values
    (@id, @name, @data)





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_InsertSkillName    Script Date: 2003-09-20 오전 11:51:59 ******/

/********************************************
lin_InsertSkillName
    insert Skill name data
INPUT
    @id	INT,
    @lev 	INT,
    @name 	nvarchar(50)
    @skill_desc 	nvarchar(50),
    @magic_skill	INT,
    @activateType	nvarchar(5)
OUTPUT
return
made by
    carrot
date
    2002-10-8
********************************************/
CREATE PROCEDURE [DBO].[lin_InsertSkillName]
(
@id	INT,
@lev 	INT,
@name 	nvarchar(50),
@skill_desc 	nvarchar(50),
@magic_skill	INT,
@activateType	nvarchar(5)
)
AS
SET NOCOUNT ON


INSERT INTO skillData
    (id, lev, name, skill_desc, bIsMagic, activate_type)
    values
    (@id, @lev, @name, @skill_desc, @magic_skill, @activateType)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO









/****** Object:  Stored Procedure dbo.lin_InsertUserHistory    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_InsertUserHistory
    make user history log
INPUT
    @char_name	nvarchar(50),
    @char_id	int,
    @log_action	tinyint,
    @account_name	nvarchar(50),
    @create_date		datetime
OUTPUT
return
made by
    young
date
    2003-1-14
********************************************/
CREATE PROCEDURE [DBO].[lin_InsertUserHistory]
(
    @char_name	nvarchar(50),
    @char_id	int,
    @log_action	tinyint,
    @account_name	nvarchar(50),
    @create_date		datetime
)
AS
SET NOCOUNT ON

declare @create_date2 datetime

if @create_date is NULL
begin
    set @create_date2 = getdate()
end
else
begin
    set @create_date2 = @create_date
end
insert into user_history( char_name, char_id, log_action, account_name, create_date) values
( @char_name, @char_id, @log_action, @account_name, @create_date2)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_InsertUserLog    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_InsertUserLog
    add user log data
INPUT
    char_id
    log_id
OUTPUT
return
made by
    young
date
    2003-1-15
change
********************************************/
CREATE PROCEDURE [DBO].[lin_InsertUserLog]
(
    @char_id	INT,
    @log_id	TINYINT
)
AS

SET NOCOUNT ON

insert into user_log( char_id, log_id)
values (@char_id, @log_id)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_InstallBattleCamp    Script Date: 2003-09-20 오전 11:51:59 ******/
-- lin_InstallBattleCamp
-- by bert
-- return new battle camp id

CREATE PROCEDURE dbo.lin_InstallBattleCamp (@pledge_id INT, @castle_id INT, @max_hp INT, @hp INT, @x INT, @y INT, @z INT, @type INT)
AS

SET NOCOUNT ON

INSERT INTO object_data
(owner_id, residence_id, max_hp, hp, x_pos, y_pos, z_pos, type)
VALUES
(@pledge_id, @castle_id, @max_hp, @hp, @x, @y, @z, @type)

SELECT @@IDENTITY




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_JoinAlliance    Script Date: 2003-09-20 오전 11:51:59 ******/
-- lin_JoinAlliance
-- by bert
-- return Result(0 if failed)

CREATE PROCEDURE
dbo.lin_JoinAlliance (@alliance_id INT, @member_pledge_id INT)
AS

SET NOCOUNT ON

DECLARE @result INT

UPDATE pledge
SET alliance_id = @alliance_id
WHERE pledge_id = @member_pledge_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @result = 1
END
ELSE
BEGIN
    SELECT @result = 0
END

SELECT @result




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_JoinPledgeMember    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_JoinPledgeMember
-- by bert

CREATE PROCEDURE
dbo.lin_JoinPledgeMember (@pledge_id INT, @member_id INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

UPDATE user_data
SET pledge_id = @pledge_id
WHERE char_id = @member_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    -- 추가되는 코드는 여기에
    SELECT @ret = 1
END
ELSE
BEGIN
    SELECT @ret = 0
    GOTO EXIT_TRAN
END

EXIT_TRAN:
IF @ret<> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END
SELECT @ret




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadAccount    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadAccount

INPUT
    @account_id	int
OUTPUT
return
made by
    carrot
date
    2002-06-09
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadAccount]
(
@account_id	int
)
AS
SET NOCOUNT ON

if @account_id < 1
begin
    RAISERROR ('lin_LoadAccount : invalid account_id [%d]', 16, 1, @account_id)
    RETURN -1
end

SELECT top 10 char_id, account_name FROM user_data (nolock) WHERE account_id= @account_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO


/********************************************
lin_LoadAgit

INPUT
 @agit_id  int
OUTPUT
 pledge_id,
 hp_stove,
 hp_stove_expire,
 mp_flame,
 mp_flame_expire,
 hatcher,
 status,
 next_war_time
return
made by
 carrot
date
 2002-06-16
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadAgit]
(
 @agit_id  int
)
AS

SET NOCOUNT ON

select pledge_id, hp_stove, hp_stove_expire, mp_flame, mp_flame_expire, hatcher, status, next_war_time ,
  isnull(R1.auction_id, 0) , isnull( auction_time, 0)   , isnull ( last_price , 0) , isnull(last_cancel, 0) , isnull (min_price, 0), isnull(teleport_level, 0),
 isnull(teleport_expire, 0),  isnull ( auction_desc, '') , isnull( next_cost, 0) , isnull ( cost_fail, 0 )  , isnull ( tax_rate, 0 ),
 isnull (tax_rate_to_change, 0), isnull (tax_child_rate, 0), isnull (tax_child_rate_to_change, 0), isnull(shop_income, 0), isnull(shop_income_temp, 0)
from (
 select id, pledge_id, hp_stove, hp_stove_expire, mp_flame, mp_flame_expire, hatcher, status, next_war_time , auction_id, last_price, last_cancel,
 teleport_level, teleport_expire, next_cost, cost_fail  , tax_rate, tax_rate_to_change, tax_child_rate, tax_child_rate_to_change, shop_income_temp, shop_income
 from agit (nolock)
 where id = @agit_id
 ) as R1
 left join
 (
 select agit_id, auction_id, auction_time , min_price, auction_desc
 from agit_auction (nolock)
 where agit_id = @agit_id
 ) as R2
 on R1.id = R2.agit_id and R1.auction_id = R2.auction_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadAllAgit    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadAllAgit

INPUT
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_LoadAllAgit]
AS
SET NOCOUNT ON

SELECT id, pledge_id FROM castle  (nolock) WHERE type = 2 ORDER BY id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_LoadAllAllianceId    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_LoadAllAllianceId
-- by bert
CREATE PROCEDURE
dbo.lin_LoadAllAllianceId
AS

SET NOCOUNT ON

SELECT id FROM alliance




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_LoadAllAllianceWarData

INPUT
    @status	int
OUTPUT
    id,
    begin_time,
    challenger,
    challengee
return
made by
    bert
date
    2003-11-07
********************************************/
create PROCEDURE [DBO].[lin_LoadAllAllianceWarData]
(
    @status	int
)
AS
SET NOCOUNT ON

SELECT
    id, begin_time, challenger, challengee
FROM
    alliance_war (nolock)
WHERE
    status = @status



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadAllCastle    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadAllCastle

INPUT
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_LoadAllCastle]
--(
--	@tax_rate		int,
--	@castle_id		int
--)
AS
SET NOCOUNT ON

SELECT castle_d.id, castle_d.pledge_id, castle_d.next_war_time, castle_d.tax_rate, (select char_name from user_data where char_id = p.ruler_id)
FROM
    (select * from castle (nolock) where type= 1) as castle_d
    inner join
    (select * from pledge (nolock) where pledge_id in (select pledge_id from castle)) as p
    on
    castle_d.pledge_id = p.pledge_id
ORDER BY castle_d.id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadAllPledge    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadAllPledge

INPUT
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_LoadAllPledge]
--(
--	@account_name	nvarchar(50)
--)
AS
SET NOCOUNT ON

SELECT
    p.pledge_id, p.name, p.ruler_id, ud.char_name,
    p.alliance_id, p.challenge_time, p.now_war_id, p.name_value, p.oust_time, p.skill_level,
    p.private_flag, p.status, p.rank, p.castle_id, p.agit_id, p.root_name_value,
    p.crest_id, p.is_guilty, p.dismiss_reserved_time
FROM
    pledge p (nolock),
    (select * from user_data (nolock) where pledge_id > 0 ) ud
WHERE
    p.ruler_id = ud.char_id







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadAllWarData    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadAllWarData

INPUT
    @status	int
OUTPUT
    id,
    begin_time,
    challenger,
    challengee
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_LoadAllWarData]
(
    @status	int
)
AS
SET NOCOUNT ON

SELECT
    id, begin_time, challenger, challengee
FROM
    pledge_war (nolock)
WHERE
    status = @status








GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_LoadAlliance    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_LoadAlliance
-- by bert
CREATE PROCEDURE
dbo.lin_LoadAlliance (@alliance_id INT)
AS

SET NOCOUNT ON

SELECT id, name, master_pledge_id, oust_time, crest_id FROM alliance WHERE id = @alliance_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_LoadAllianceWar

INPUT
    @war_id		int
OUTPUT
return
made by
    bert
date
    2003-11-07
********************************************/
create PROCEDURE [DBO].[lin_LoadAllianceWar]
(
    @war_id		int
)
AS
SET NOCOUNT ON

SELECT challenger, challengee, begin_time, status FROM alliance_war (nolock)  WHERE id = @war_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/********************************************
lin_LoadBlockList
    when character log in, load he's blocked list.
INPUT
    char_id
OUTPUT
return
made by
    carrot
date
    2003-12-01
change
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadBlockList]
(
    @char_id	INT
)
AS

SET NOCOUNT ON

SELECT block_char_id, block_char_name FROM user_blocklist WHERE char_id = @char_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadBuilderAccountByAccountName    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadBuilderAccountByAccountName

INPUT
    @account_name	NVARCHAR(50)
OUTPUT
return
made by
    carrot
date
    2002-06-09
change 	2003-07-03	carrot
    restrict only builer account
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadBuilderAccountByAccountName]
(
@account_name	NVARCHAR(50)
)
AS
SET NOCOUNT ON

SELECT top 1 account_id FROM builder_account (nolock) WHERE account_name= @account_name and account_id > 0






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_LoadCastle

INPUT
 @id int,
 @type int
OUTPUT
 pledge_id,
 next_war_time,
 tax_rate,
 status,
 name,
 crop_income,
 shop_income,
 siege_elapsed_time
 shop_Income_Temp,
 Tax_rate_to_change,
 tax_child_rate_to_change
return
made by
 carrot
date
 2002-06-16
change 2004-02-29 carrot
 add CastleIncomeTemp and TaxRateTochange, tax_child_rate_to_change
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadCastle]
(
 @id int,
 @type int
)
AS
SET NOCOUNT ON

SELECT
 pledge_id, next_war_time, tax_rate, tax_child_rate, status, name, crop_income, shop_income, siege_elapsed_time, shop_Income_Temp, Tax_rate_to_change,
 tax_child_rate_to_change
FROM
 castle (nolock)
WHERE
 id = @id AND type = @type



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadCastleCrop    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadCastleCrop

INPUT
    @castle_id	int,
OUTPUT
    item_type,
    droprate,
    price,
    level
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_LoadCastleCrop]
(
    @castle_id	int
)
AS
SET NOCOUNT ON

SELECT
    item_type, droprate, price, level
from
    castle_crop (nolock)
WHERE
    castle_id = @castle_id







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_LoadCastleWarRelatedPledge    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadCastleWarRelatedPledge

INPUT
    @castle_id	int
OUTPUT
return
made by
    bert
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadCastleWarRelatedPledge]
(
    @castle_id	int
)
AS
SET NOCOUNT ON

SELECT
    pledge_id, type, propose_time
FROM
    castle_war (nolock)
WHERE
    castle_id = @castle_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_LoadControlTowerByName
(
@name VARCHAR(256)
)
AS
SELECT residence_id, control_level, hp, status
FROM control_tower
WHERE name = @name




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_LoadControlTowerByResidenceId
(
@residence_id INT
)
AS
SELECT name, control_level, hp, status
FROM control_tower
WHERE residence_id = @residence_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO

/********************************************
lin_LoadDayUsedTime
 load account's today used time
INPUT
 account_id
OUTPUT
return
 used sec INT
made by
 carrot
date
 2004-03-29
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadDayUsedTime]
(
 @account_id INT
)
AS

SET NOCOUNT ON

SELECT TOP 1 used_sec, convert(varchar(19), last_logout, 121) FROM time_data (nolock) WHERE account_id = @account_id

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadDismissReservedPledge    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadDismissReservedPledge

INPUT
    @status	int
OUTPUT
    pledge_id,
    dismiss_reserved_time
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_LoadDismissReservedPledge]
(
    @status	int
)
AS
SET NOCOUNT ON

SELECT pledge_id, dismiss_reserved_time FROM pledge  (nolock) WHERE status = @status






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE [dbo].[lin_LoadDoor]
(
 @name NVARCHAR(50)
)
AS
SET NOCOUNT ON
SELECT hp, ISNULL(max_hp, hp) FROM door  (nolock) WHERE name = @name





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




CREATE PROCEDURE dbo.lin_LoadFriends (@char_id INT)
AS

SET NOCOUNT ON

SELECT friend_char_id, ud.char_name AS friend_char_name
FROM user_friend AS uf, user_data AS ud
WHERE uf.char_id = @char_id AND uf.friend_char_id = ud.char_id AND ud.account_id <> -1



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadItemByItemId    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_LoadItemByItemId

INPUT
    @item_id		INT
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadItemByItemId]
(
    @item_id		INT
)
AS
SET NOCOUNT ON

SELECT char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse FROM user_item (nolock) WHERE item_id = @item_id AND (NOT item_type = 0)





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



/********************************************
lin_LoadItems
 Load item data and check adena data
INPUT
 @char_id INT,
 @warehouse  INT
OUTPUT
 item_id, item_type, amount, enchant, eroded, bless, ident, wished
return
made by
 carrot
date
 2002-04-23
//const WCHAR* qsLoadItems = L"SELECT item_id, item_type, amount, enchant, eroded, bless, ident, wished FROM user_item WHERE char_id = %d AND warehouse = %d AND (NOT item_type = 0) AND NOT ITEM_TYPE = 57";
********************************************/
CREATE  PROCEDURE [DBO].[lin_LoadItems]
(
 @char_id INT,
 @warehouse INT
)
AS
SET NOCOUNT ON

DECLARE @nSum  INT
DECLARE @nCount INT

SET @nSum = 0
SET @nCount = 0


--SELECT @nCount = count(amount), @nSum = sum(amount) FROM user_item WHERE char_id = @char_id AND item_type = 57 AND warehouse = @warehouse
--IF @nCount > 1
--BEGIN
-- DECLARE @nMaxItemId INT
-- SELECT @nMaxItemId = Max(item_id) FROM user_item WHERE char_id = @char_id AND item_type = 57 AND warehouse = @warehouse
-- IF @nMaxItemId > 0
-- BEGIN
--  UPDATE user_item Set amount = @nSum WHERE char_id = @char_id AND item_type = 57 AND warehouse = @warehouse And item_id = @nMaxItemId
--  DELETE user_item WHERE char_id = @char_id AND item_type = 57 AND warehouse = @warehouse And NOT item_id = @nMaxItemId
-- END
--END


    SELECT item_id, item_type, amount, enchant, eroded, bless, ident, wished
    FROM user_item (nolock)
    WHERE char_id = @char_id AND warehouse = @warehouse  AND item_type > 0


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_LoadLastLogout
    load char last logout
INPUT
    char_id	int

OUTPUT
return
made by
    carrot
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadLastLogout]
(
@char_id		INT

)
AS
SET NOCOUNT ON


select Year(logout), Month(logout), Day(logout), DATEPART(HOUR, logout), DATEPART(mi, logout), DATEPART(s, logout)
from user_data (nolock) where char_id = @char_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO


/********************************************
lin_LoadLastTaxUpdate

INPUT
OUTPUT
made by
 carrot
date
 2004-02-29
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadLastTaxUpdate]
AS

SET NOCOUNT ON

SELECT TOP 1
 YEAR(income_update), MONTH(income_update), DAY(income_update),
 DATEPART ( hh , income_update ), DATEPART ( mi , income_update ), DATEPART ( ss , income_update ),
 YEAR(tax_change), MONTH(tax_change), DAY(tax_change),
 DATEPART ( hh , tax_change ), DATEPART ( mi , tax_change), DATEPART ( ss , tax_change)
FROM
 castle_tax



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_LoadMercenary
(
@residence_id INT
)
AS
SELECT id, npc_id, x, y, z, angle, hp, mp
FROM mercenary
WHERE residence_id = @residence_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadNpcBoss    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadNpcBoss

INPUT
    @NPC_name	nvarchar(50)
OUTPUT
    alive,
    hp,
    mp,
    pos_x,
    pos_y,
    pos_z,
    time_low,
    time_high
    i0
return
made by
    carrot
date
    2002-06-16
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadNpcBoss]
(
    @NPC_name	nvarchar(50)
)
AS
SET NOCOUNT ON

select
    alive,  hp,  mp, pos_x, pos_y, pos_z, time_low, time_high , i0
from
    npc_boss  (nolock)
where
    npc_db_name = @NPC_name



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_LoadPet

INPUT
    @pet_id int
OUTPUT
return
made by
    kuooo
date
    2003-08-22
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadPet]
(
    @pet_id int
)
AS
SET NOCOUNT ON

SELECT npc_class_id  , expoint , hp, mp, sp, meal, nick_name , slot1, slot2 FROM pet_data (nolock) WHERE pet_id = @pet_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_LoadPetItems    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadPetItems
    Load item data from pet inventory
INPUT
    @pet_id 	INT
OUTPUT
    item_id, item_type, amount, enchant, eroded, bless, ident, wished
return
made by
    kuooo
date
    2003-08-25

********************************************/
CREATE PROCEDURE [DBO].[lin_LoadPetItems]
(
    @pet_id 	INT
)
AS
SET NOCOUNT ON

SELECT item_id, item_type, amount, enchant, eroded, bless, ident, wished FROM user_item WHERE char_id = @pet_id  AND warehouse = 5




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




CREATE PROCEDURE [DBO].[lin_LoadPledgeById]
(
    @PledgeId		int
)
AS
SET NOCOUNT ON

SELECT
    p.pledge_id, p.name, p.ruler_id, ud.char_name,
    p.alliance_id, p.challenge_time, p.now_war_id, p.name_value, p.oust_time, p.skill_level,
    p.private_flag, p.status, p.rank, p.castle_id, p.agit_id, p.root_name_value,
    p.crest_id, p.is_guilty, p.dismiss_reserved_time, p.alliance_ousted_time, p.alliance_withdraw_time, p.alliance_dismiss_time
FROM
    (select * from pledge (nolock)where pledge_id = @PledgeId) as  p
    JOIN
    (select * from user_data (nolock)) as  ud
    ON p.ruler_id = ud.char_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



CREATE PROCEDURE [DBO].[lin_LoadPledgeByName]
(
    @PledgeName		NVARCHAR(50)
)
AS
SET NOCOUNT ON


DECLARE @PledgeId INT
set @PledgeId = -1
SELECT @PledgeId = pledge_id from pledge where  name = @PledgeName

IF @PledgeId  > -1
begin
    SELECT
        p.pledge_id, p.name, p.ruler_id, ud.char_name,
        p.alliance_id, p.challenge_time, p.now_war_id, p.name_value, p.oust_time, p.skill_level,
        p.private_flag, p.status, p.rank, p.castle_id, p.agit_id, p.root_name_value,
        p.crest_id, p.is_guilty, p.dismiss_reserved_time, p.alliance_ousted_time, p.alliance_withdraw_time, p.alliance_dismiss_time
    FROM
        (select * from pledge (nolock)  where pledge_id = @PledgeId) as  p
        JOIN
        (select * from user_data (nolock)) as  ud
        ON
        p.ruler_id = ud.char_id
end





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadPledgeCrest    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadPledgeCrest

INPUT
    @crest_id	int
OUTPUT
    bitmap_size,
    bitmap
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_LoadPledgeCrest]
(
    @crest_id	int
)
AS
SET NOCOUNT ON

SELECT
    bitmap_size, bitmap
FROM
    pledge_crest  (nolock)
WHERE
    crest_id = @crest_id







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadPledgeMember    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadPledgeMember

INPUT
    pledge_id = @pledge_id
OUTPUT
return
made by
    carrot
date
    2002-06-10
change 2003-07-22 carrot
    check character is deleted.
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadPledgeMember]
(
    @pledge_id		int
)
AS
SET NOCOUNT ON

SELECT char_id FROM user_data (nolock) WHERE pledge_id = @pledge_id and account_id > 0




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadPledgeWar    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_LoadPledgeWar

INPUT
    @war_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_LoadPledgeWar]
(
    @war_id		int
)
AS
SET NOCOUNT ON

SELECT challenger, challengee, begin_time, status FROM pledge_war (nolock)  WHERE id = @war_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_LoadQuest    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_LoadQuest

INPUT
    @char_id	int
OUTPUT
return
made by
    carrot
date
    2002-06-09
********************************************/
CREATE PROCEDURE [DBO].[lin_LoadQuest]
(
@char_id	int
)
AS
SET NOCOUNT ON

SELECT TOP 1  q1, s1, j1, q2, s2, j2, q3, s3, j3, q4, s4, j4,
        q5, s5, j5, q6, s6, j6, q7, s7, j7, q8, s8, j8,
        q9, s9, j9, q10, s10, j10, q11, s11,  j11, q12, s12, j12,
        q13, s13, j13, q14, s14, j14, q15, s15, j15, q16, s16, j16
FROM quest (nolock)
WHERE char_id = @char_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_LoadResidenceGuard
(
@residence_id INT
)
AS
SELECT item_id, npc_id, guard_type, can_move, x, y, z, angle
FROM residence_guard
WHERE residence_id = @residence_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_MakeBBSBoard    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_MakeBBSBoard
    Make BBS board
INPUT
    @board_name	nvarchar(20),
    @board_desc	nvarchar(50)
OUTPUT

return
made by
    young
date
    2002-10-16
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeBBSBoard]
(
    @board_name	nvarchar(20),
    @board_desc	nvarchar(50)
)
AS

set nocount on

declare @ncount int
declare @table_name nvarchar(20)
declare @exec nvarchar(500)

set @table_name = 'bbs_' + @board_name

select @ncount = count(*) from sysobjects (nolock) where name = @table_name
select @ncount
if @ncount = 0
begin

    set @exec = 'CREATE TABLE dbo.' + @table_name + '(' + char(13)
    set @exec = @exec + ' id int IDENTITY (1,1) NOT NULL, ' + char(13)
    set @exec = @exec + ' title nvarchar(100) NULL, ' + char(13)
    set @exec = @exec + ' contents nvarchar(3000) NULL, ' + char(13)
    set @exec = @exec + ' writer nvarchar(50) NULL, ' + char(13)
    set @exec = @exec + ' cdate datetime NOT NULL, ' + char(13)
    set @exec = @exec + ' nread int NOT NULL)  ' + char(13)
    exec (@exec)
    set @exec = 'ALTER TABLE dbo.' + @table_name + ' WITH NOCHECK ADD' + char(13)
    set @exec = @exec + 'CONSTRAINT PK_' + @table_name + ' PRIMARY KEY CLUSTERED' + char(13)
    set @exec = @exec + '( ' + char(13)
    set @exec = @exec + 'id ' + char(13)
    set @exec = @exec + ')' + char(13)
    exec (@exec)
    set @exec = 'ALTER TABLE dbo.' + @table_name + ' WITH NOCHECK ADD' + char(13)
    set @exec = @exec + 'CONSTRAINT DF_' + @table_name + '_cdate DEFAULT getdate() FOR cdate, ' + char(13)
    set @exec = @exec + 'CONSTRAINT DF_' + @table_name + '_nread DEFAULT 0 FOR nread ' + char(13)
    exec (@exec)

    insert into bbs_board(board_name, board_desc) values(@table_name, @board_desc)
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ModChar    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_ModChar

INPUT
    @sp		int,
    @exp		int,
    @align		int,
    @pk		int,
    @pkpardon	int,
    @duel		int,
    @char_id	int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_ModChar]
(
    @sp		int,
    @exp		int,
    @align		int,
    @pk		int,
    @pkpardon	int,
    @duel		int,
    @char_id	int
)
AS
SET NOCOUNT ON

update user_data set sp=@sp, exp=@exp, align=@align, pk=@pk, pkpardon=@pkpardon, duel=@duel where char_id = @char_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ModChar2    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_ModChar2

INPUT
    @sp		int,
    @exp		int,
    @align		int,
    @pk		int,
    @pkpardon	int,
    @duel		int,
    @char_id	int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_ModChar2]
(
    @gender		int,
    @race		int,
    @class		int,
    @face_index		int,
    @hair_shape_index	int,
    @hair_color_index		int,
    @char_id	int
)
AS
SET NOCOUNT ON

update user_data set gender=@gender, race=@race, class=@class, face_index=@face_index, hair_shape_index=@hair_shape_index, hair_color_index=@hair_color_index where char_id = @char_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_ModChar3    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_ModChar3

INPUT
    @mod field	int,
    @delta		int,
    @char_id	int
OUTPUT
return
made by
    young
date
    2003-08-26
********************************************/
CREATE PROCEDURE [DBO].[lin_ModChar3]
(
    @sp		int,
    @exp		int,
    @align		int,
    @pk		int,
    @pkpardon	int,
    @duel		int,
    @char_id	int
)
AS
SET NOCOUNT ON

update user_data set
    sp = sp + @sp,
    exp = exp + @exp,
    align = align + @align,
    pk = pk + @pk,
    pkpardon = pkpardon + @pkpardon,
    duel = duel + @duel
where char_id = @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_ModItemOwner

INPUT
    @item_id	INT,
    @new_char_id	INT,
    @new_warehouse	INT
OUTPUT
return
made by
    young
date
    2003-11-07
********************************************/
CREATE PROCEDURE [DBO].[lin_ModItemOwner]
(
@item_id	INT,
@new_char_id 	INT,
@new_warehouse	INT

)
AS
SET NOCOUNT ON

UPDATE user_item  set char_id=@new_char_id,  warehouse=@new_warehouse WHERE item_id=@item_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ModifyPledgeName    Script Date: 2003-09-20 오전 11:51:59 ******/
/********************************************
lin_ModifyPledgeName

INPUT
    @crest_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_ModifyPledgeName]
(
    @pledge_name		NVARCHAR(50),
    @pledge_id		int
)
AS
SET NOCOUNT ON

update pledge set name = @pledge_name where pledge_id = @pledge_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO






CREATE PROCEDURE dbo.lin_MoveCharCopyChar
(
    @world_id	varchar(5)
)
AS


declare @sql varchar(1024)
declare @conn_str varchar(256)

set @conn_str = '10.10.12.' + @world_id + ''';''gamma'';''lineage2pwd'


set @sql = ' insert into req_charmove ( old_char_name, old_char_id, account_name, account_id,  old_world_id, new_world_id, new_char_name ) select R1.char_name, char_id, account_name, account_id, ' + @world_id + ' , 100, R1.char_name + ''-' + @world_id + '''   from ( select * from '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '' select char_id, char_name, account_id, account_name from lin2world.dbo.user_data (nolock)  '' ) )  as R1 '
    + ' left join ( select * from req_char (nolock) where server_id = ' + @world_id + ' ) as R2 '
    + ' on R1.char_name = R2.char_name '
    + ' where server_id is not null '
exec ( @sql )




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





CREATE PROCEDURE dbo.lin_MoveCharCopyPledge
(
    @world_id	varchar(5)
)
AS


declare @sql varchar(1024)
declare @conn_str varchar(256)

set @conn_str = '10.10.12.' + @world_id + ''';''gamma'';''lineage2pwd'

set @sql = ' insert into req_charmove ( old_char_name, old_char_id, account_name, account_id,  old_world_id, new_world_id, new_char_name ) select R1.char_name, char_id, account_name, account_id, ' + @world_id + ' , 100, R1.char_name + ''-' + @world_id + '''   from ( select * from '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '' select pledge_id, char_id, char_name, account_id, account_name from lin2world.dbo.user_data (nolock) where account_id > 0  '' ) )  as R1 '
    + ' left join ( select * from req_pledge (nolock) where server_id = ' + @world_id + ' ) as R2 '
    + ' on R1.pledge_id = R2.pledge_id '
    + ' where server_id is not null '

exec ( @sql )




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





CREATE PROCEDURE dbo.lin_MoveCharPlg
(
    @world_id	varchar(5)
)
AS


declare @sql varchar(1024)
declare @conn_str varchar(256)

set @conn_str = '10.10.12.' + @world_id + ''';''gamma'';''lineage2pwd'

set @sql = ' insert into pledge ( old_world_id, old_pledge_id,  old_ruler_id, ruler_id, name, alliance_id, challenge_time, root_name_value, now_war_id, oust_time, skill_level, castle_id, agit_id, rank, name_value, status, private_flag, crest_id, is_guilty, dismiss_reserved_time, alliance_ousted_time, alliance_withdraw_time, alliance_dismiss_time )  '
    + ' select ' + @world_id + '  , R1.pledge_id, ruler_id, 0, name + ''-' + @world_id + ''' , 0, 0, 0, 0 ,0 ,0 , 0, 0, 0, name_value, 0, 0, 0, 0, 0, 0, 0, 0  from ( select * from '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '' select * from lin2world.dbo.pledge (nolock)  '' ) )  as R1 '
    + ' left join ( select * from req_pledge (nolock) where server_id = ' + @world_id + ' ) as R2 '
    + ' on R1.pledge_id = R2.pledge_id '
    + ' where server_id is not null '

exec ( @sql )




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO


/********************************************
lin_MoveCharSvr
    move char
INPUT
    @world_id	int
OUTPUT

return
made by
    young
date
    2003-7-30
    2003-10-06
    2004-1-6
    2004-2-24
    2004-3-3
********************************************/
CREATE PROCEDURE [DBO].[lin_MoveCharSvr]
(
    @old_world_id		int,
    @new_world_id		int,
    @conn_str		varchar(100)
)
AS

SET NOCOUNT ON

declare @sql varchar(4000)

--	& ' OPENROWSET ( 'SQLOLEDB', 'l2world01';'gamma';'lineage2pwd', '


-- make user_data

set @sql = ' insert into user_data ( '
    + ' char_name, pledge_id, account_name, account_id, builder, gender, race, class, world, xloc, yloc, zloc,  '
    + ' IsInVehicle, HP, MP, SP, Exp, Lev, align, PK, PKpardon, Duel, ST_underware, ST_right_ear, ST_left_ear, '
    + ' ST_neck, ST_right_finger, ST_left_finger, ST_head, ST_right_hand, ST_left_hand, ST_gloves, ST_chest,  '
    + ' ST_feet, ST_back, ST_both_hand, ST_legs, create_date, login, logout, quest_flag, power_flag, max_hp, max_mp, '
    + ' quest_memo, face_index, hair_color_index,  hair_shape_index, use_time, drop_exp,  '
    + ' surrender_war_id, pledge_withdraw_time, pledge_ousted_time, pledge_leave_status, pledge_leave_time, '
    + ' pledge_dismiss_time , old_pledge_id, old_char_id '
    + ' ) '
    + ' select R2.new_char_name, 0, account_name, R1.account_id, builder, gender, race, class, world, xloc, yloc, zloc,  '
    + ' IsInVehicle, HP, MP, SP, Exp, Lev, align, PK, PKpardon, Duel, 0, 0, 0, '
    + ' 0, 0, 0, 0, 0, 0, 0, 0,  '
    + ' 0, 0, 0, 0,  create_date, login, logout, quest_flag, power_flag, max_hp, max_mp, '
    + ' quest_memo, face_index, hair_color_index, hair_shape_index, use_time, drop_exp,  '
    + ' 0, 0, 0, 0, 0, '
    + '  0 , pledge_id, char_id '
    + ' from '
    + ' ( '
    + ' select pledge_id, char_id, account_name, account_id, builder, gender, race, class, world, xloc, yloc, zloc,  '
    + ' IsInVehicle, HP, MP, SP, Exp, Lev, align, PK, PKpardon, Duel, ST_underware, ST_right_ear, ST_left_ear, '
    + ' ST_neck, ST_right_finger, ST_left_finger, ST_head, ST_right_hand, ST_left_hand, ST_gloves, ST_chest,  '
    + ' ST_feet, ST_back, ST_both_hand, ST_legs,  create_date, login, logout, quest_flag, power_flag, max_hp, max_mp, '
    + ' quest_memo, face_index, hair_color_index, hair_shape_index, use_time, drop_exp,  '
    + ' surrender_war_id, pledge_withdraw_time, pledge_ousted_time, pledge_leave_status, pledge_leave_time, '
    + ' pledge_dismiss_time '
    + ' from '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.user_data (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' + CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_name, account_id, old_char_id from req_charmove (nolock) where old_world_id = ' + CAST ( @old_world_id as varchar) + ' and new_world_id = ' + cast ( @new_world_id  as varchar ) + ' )  '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '

select @sql

exec (@sql)

-- update char_id
set @sql = ' update r '
    + ' set r.new_char_id = u.char_id '
    + ' from req_charmove as r  inner join user_data as u '
    + ' on r.new_char_name = u.char_name '
    + ' where r.old_world_id = ' +  CAST ( @old_world_id as VARCHAR)  + ' and r.new_world_id = ' + CAST ( @new_world_id as varchar)   + '  and u.account_id > 0  '

exec (@sql)

-- copy user_item
set @sql = ' insert into user_item (char_id, item_type, amount, enchant, eroded, bless,  ident, wished, warehouse, old_world_id, old_item_id ) '
    + ' select R2.new_char_id, R1.item_type, R1.amount, R1.enchant, R1.eroded, R1.bless, R1. ident, R1.wished, R1.warehouse, ' + CAST ( @old_world_id as varchar ) + ' , R1.item_id '
    + ' from '
    + ' ( '
    + ' select * from '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.user_item (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +  CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + '  ) '
    + ' ) as R1 '
    + ' left join ( select new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '

exec (@sql)


-- copy user_skill
set @sql = ' insert into user_skill ( char_id, skill_id, skill_lev, to_end_time) '
    + ' select R2.new_char_id, R1.skill_id, R1.skill_lev, R1.to_end_time '
    + ' from '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.user_skill (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +  CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '
exec (@sql)


-- copy quest
set @sql = ' insert into quest ( char_id, q1, s1, q2, s2, q3, s3, q4, s4, q5, s5, q6, s6, q7, s7, q8, s8, q9, s9, q10, s10, q11, s11, q12, s12, q13, s13, q14, s14, q15, s15, q16, s16) '
    + ' select R2.new_char_id, q1, s1, q2, s2, q3, s3, q4, s4, q5, s5, q6, s6, q7, s7, q8, s8, q9, s9, q10, s10, q11, s11, q12, s12, q13, s13, q14, s14, q15, s15, q16, s16 '
    + ' from '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.quest (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +  CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +  CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '

exec (@sql)


-- copy user_history
set @sql = ' insert into user_history( char_name, char_id, log_date, log_action, account_name, create_date) '
    + ' select R2.new_char_name, R2.new_char_id, R1.log_date, R1.log_action, R1.account_name, R1.create_date '
    + ' from '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.user_history (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_name, new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '

exec (@sql)


-- copy user_log
set @sql = ' insert into user_log  ( char_id, log_id, log_date, log_from, log_to, use_time ) '
    + ' select R2.new_char_id, log_id, log_date, log_from, log_to, use_time  '
    + ' from '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.user_log  (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar)  + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR) + '  and new_world_id = ' + CAST ( @new_world_id as varchar)  + '  ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '
exec (@sql)


-- shortcut_data
set @sql = ' insert into shortcut_data ( char_id, slotnum, shortcut_type, shortcut_id, shortcut_macro ) '
    + ' select R2.new_char_id, slotnum, shortcut_type, shortcut_id, shortcut_macro '
    + ' from '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.shortcut_data (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR)  + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +  CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar)  + ' ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '
exec (@sql)


-- user_comment
set @sql = ' insert into user_comment ( char_name, char_id, comment, comment_date, writer, deleted ) '
    + ' select R2.new_char_name, R2.new_char_id, comment, comment_date, writer, deleted  '
    + ' from '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select * from lin2world.dbo.user_comment  (nolock) '' ) '
    + ' where char_id in ( select old_char_id from req_charmove (nolock) where old_world_id = ' +   CAST ( @old_world_id as VARCHAR)  + ' and new_world_id = ' + CAST ( @new_world_id as varchar) + ' ) '
    + ' ) as R1 '
    + ' left join ( select new_char_name, new_char_id , old_char_id from req_charmove (nolock) where old_world_id = ' +  CAST ( @old_world_id as VARCHAR) + ' and new_world_id = ' + CAST ( @new_world_id as varchar)  + ' ) '
    + ' as R2 '
    + ' on R1.char_id = R2.old_char_id '
    + ' where new_char_id is not null '
exec (@sql)


-- pet_data
set @sql = ' insert into pet_data ( pet_id, npc_class_id, expoint, nick_name, hp, mp, sp, meal  ) '
    + ' select item_id, npc_class_id, expoint, null, hp, mp, sp, meal   '
    + ' from '
    + ' ( select * from user_item (nolock) where item_type in ( 2375 , 3500, 3501, 3502 ) and old_world_id = ' + CAST ( @old_world_id as varchar ) + ' ) as R1 '
    + ' left join '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select pet_id, npc_class_id, expoint, hp, mp, sp, meal  from lin2world.dbo.pet_data (nolock) '' ) '
    + ' ) as R2 '
    + ' on R1.old_item_id = R2.pet_id '
    + ' where R2.npc_class_id is not null '
exec (@sql)

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_MoveCharSvr2
    move char
INPUT
    @world_id	int
OUTPUT

return
made by
    young
date
    2003-7-30
    2003-10-06
    2004-1-6
    2004-2-24
    2004-3-3
    2004-3-4
********************************************/
CREATE PROCEDURE [DBO].[lin_MoveCharSvr2]
(
    @old_world_id		int,
    @new_world_id		int,
    @conn_str		varchar(100)
)
AS

SET NOCOUNT ON

declare @sql varchar(4000)

--	& ' OPENROWSET ( 'SQLOLEDB', 'l2world01';'gamma';'lineage2pwd', '


-- pet_data
/*
set @sql = ' insert into pet_data ( pet_id, npc_class_id, expoint, nick_name, hp, mp, sp, meal  ) '
    + ' select item_id, npc_class_id, expoint, null, hp, mp, sp, meal   '
    + ' from '
    + ' ( select * from user_item (nolock) where item_type in ( 2375 , 3500, 3501, 3502 ) and old_world_id = ' + CAST ( @old_world_id as varchar ) + ' ) as R1 '
    + ' left join '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select pet_id, npc_class_id, expoint, hp, mp, sp, meal  from lin2world.dbo.pet_data (nolock) '' ) '
    + ' ) as R2 '
    + ' on R1.old_item_id = R2.pet_id '
    + ' where R2.npc_class_id is not null '
*/

set @sql =   ' insert into pet_data2 ( pet_id, npc_class_id, expoint, nick_name, hp, mp, sp, meal  ) '
    + ' select  item_id, npc_class_id, expoint, ''petname''=null, hp, mp, sp, meal  '
    + ' from '
    + ' ( select * from user_item (nolock) where item_type in (  3500, 3501, 3502 ) and old_world_id = ' + CAST ( @old_world_id as varchar ) + ' ) as R1 '
    + ' left join '
    + ' ( '
    + ' select * from  '
    + ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', '
    + ' '' select pet_id, npc_class_id, expoint, hp, mp, sp, meal  from lin2world.dbo.pet_data (nolock) '' ) '
    + ' ) as R2 '
    + ' on R1.old_item_id = R2.pet_id '
    + ' where R2.npc_class_id is not null  order by item_id asc'


exec (@sql)

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_OustMemberPledge    Script Date: 2003-09-20 오전 11:51:59 ******/
-- lin_OustMemberPledge
-- by bert
-- return Result(0 if failed)

CREATE PROCEDURE
dbo.lin_OustMemberPledge (@alliance_id INT, @member_pledge_id INT, @oust_time INT)
AS

SET NOCOUNT ON

DECLARE @result INT

BEGIN TRAN

UPDATE alliance
SET oust_time = @oust_time
WHERE id = @alliance_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @result = 1
END
ELSE
BEGIN
    SELECT @result = 0
    GOTO EXIT_TRAN
END

UPDATE pledge
SET alliance_id = 0, alliance_ousted_time = @oust_time
WHERE pledge_id = @member_pledge_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @result = 1
END
ELSE
BEGIN
    SELECT @result = 0
END

EXIT_TRAN:
IF @result <> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END

SELECT @result




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_OustPledgeMember    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_OustPledgeMember
-- by bert
-- return ousted member id
CREATE PROCEDURE [DBO].[lin_OustPledgeMember]
(
    @pledge_id	INT,
    @char_name	NVARCHAR(50)
)
AS

DECLARE @ret INT
DECLARE @char_id INT

SELECT @char_id = char_id
FROM user_data
WHERE char_name = @char_name

IF @@ERROR <> 0 OR @@ROWCOUNT <> 1
BEGIN
    SELECT @ret = 0
    GOTO EXIT_PROC
END

SET NOCOUNT ON

BEGIN TRAN

UPDATE user_data
SET pledge_id = 0
WHERE char_id = @char_id AND pledge_id = @pledge_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = @char_id
    -- 추가되는 코드는 여기에 들어간다.
END
ELSE
BEGIN
    SELECT @ret = 0
    GOTO EXIT_TRAN
END

EXIT_TRAN:
IF @ret<> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END

EXIT_PROC:
SELECT @ret




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_ReadBbsTGS    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_ReadBbsTGS]
(
    @nId	INT
)
AS

SET NOCOUNT ON

select id, title, contents, writer, cast( cdate as smalldatetime)
from bbs_tgs (nolock)
where id = @nId

update bbs_tgs set nRead = nRead + 1 where id = @nId




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ReadBbsall    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_ReadBbsall]
(
    @nId	INT
)
AS

SET NOCOUNT ON

select
    cnt, orderedTitle.title, orderedTitle.contents, orderedTitle.writer, cast( orderedTitle.cdate as smalldatetime)
from
    (Select
        count(bbs2.id) as cnt, bbs1.id, bbs1.title, bbs1.contents, bbs1.writer, bbs1.cdate
    from
        Bbs_all as bbs1
        inner join
        Bbs_all as bbs2
        on bbs1.id <= bbs2.id
    group by
        bbs1.id, bbs1.title, bbs1.contents, bbs1.writer, bbs1.cdate
    ) as orderedTitle
where
    orderedTitle.id = @nId

IF @@rowcount = 1
    UPDATE Bbs_all SET nRead = nRead + 1 WHERE id = @nId
Else
    RAISERROR ('Unavailable id.', 16, 1)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_RefreshCharacterByName    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_RefreshCharacterByName

INPUT
    @CharName		NVARCHAR(50)
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_RefreshCharacterByName]
(
    @CharName		NVARCHAR(50)
)
AS
SET NOCOUNT ON

SELECT
    char_id, account_name, account_id, pledge_id, builder, gender, race, class, world, xloc, yloc, zloc,
    HP, MP, SP, Exp, Lev, align, PK, duel, pkpardon,
    ST_underware, ST_right_ear, ST_left_ear, ST_neck, ST_right_finger, ST_left_finger, ST_head, ST_right_hand, ST_left_hand, ST_gloves, ST_chest, ST_legs, ST_feet, ST_back, ST_both_hand
FROM user_data (nolock)
WHERE char_name = @CharName





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_SetCharAccountId
    update account_id character
INPUT
    @account_id	int,
    @char_id	int
OUTPUT

return
made by
    young
date
    2003-09-02
    update account_id from character
********************************************/
CREATE PROCEDURE [DBO].[lin_RestoreChar ]
(
    @account_id	int,
    @char_id	int,
    @account_name	nvarchar(50) = ''
)
AS

SET NOCOUNT ON

declare @char_inx int
declare @old_char_name nvarchar(50)
declare @new_char_name nvarchar(50)

select @old_char_name = char_name from user_data (nolock) where char_id = @char_id
select @char_inx = CHARINDEX ( '_', @old_char_name )

if @char_inx > 0
begin
    select @new_char_name = SUBSTRING( @old_char_name, 1, @char_inx - 1)
end
else
begin
    select @new_char_name = @old_char_name
end

if ( len ( @account_name ) > 0 )
begin
    update user_data set account_id = @account_id , char_name = @new_char_name, account_name = @account_name , temp_delete_date = null  where char_id = @char_id
end else begin
    update user_data set account_id = @account_id , char_name = @new_char_name , temp_delete_date = null  where char_id = @char_id
end



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO


/********************************************
lin_RestoreChar2
    restore deleted char
INPUT
    @account_id	int,
    @char_id	int
OUTPUT

return
made by
    young
date
    2004-03-11
    update account_id from character
********************************************/
CREATE PROCEDURE [DBO].[lin_RestoreChar2 ]
(
    @account_id	int,
    @char_id	int,
    @new_char_name	nvarchar(50),
    @account_name	nvarchar(50) = ''
)
AS

SET NOCOUNT ON

if ( len ( @account_name ) > 0 )
begin
    update user_data set account_id = @account_id , char_name = @new_char_name, account_name = @account_name , temp_delete_date = null  where char_id = @char_id
end else begin
    update user_data set account_id = @account_id , char_name = @new_char_name , temp_delete_date = null  where char_id = @char_id
end


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO


/********************************************
lin_SaveCastleIncome

INPUT
 @crop_income int,
 @shop_income int,
 @castle_id int
OUTPUT
return
made by
 carrot
date
 2002-06-16
change 2003-12-22 carrot
 add about agit income
change 2004-03-02 carrot
 add taxincomeTemp
 ********************************************/
create PROCEDURE [DBO].[lin_SaveCastleIncome]
(
 @crop_income int,
 @shop_income int,
 @castle_id int  ,
 @crop_income_temp int,
 @is_castle int
)
AS
SET NOCOUNT ON

if (@is_castle = 1) -- castle
 UPDATE castle SET crop_income = @crop_income, shop_income = @shop_income, shop_income_temp = @crop_income_temp WHERE id = @castle_id
else -- agit
 UPDATE agit SET shop_income = @shop_income, shop_income_temp = @crop_income_temp WHERE id = @castle_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveCastleSiegeElapsedTime    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCastleSiegeElapsedTime

INPUT
    @siege_elapsed_time	int,
    @castle_id	int
OUTPUT

return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SaveCastleSiegeElapsedTime]
(
    @siege_elapsed_time	int,
    @castle_id	int
)
AS
SET NOCOUNT ON

UPDATE castle SET siege_elapsed_time = @siege_elapsed_time WHERE id = @castle_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveCastleStatus    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCastleStatus

INPUT
    @status		int,
    @castle_id	int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SaveCastleStatus]
(
    @status		int,
    @castle_id	int
)
AS
SET NOCOUNT ON

UPDATE castle SET status = @status WHERE id = @castle_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveCharacter    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCharacter

INPUT
OUTPUT
return
made by
    carrot
date
    2003-06-13
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveCharacter]
(
    @pledge_id INT,
    @class INT,
    @world INT,
    @xloc INT,
    @yloc INT,
    @zloc INT,
    @IsInVehicle INT,
    @HP FLOAT,
    @MP FLOAT,
    @max_HP FLOAT,
    @max_MP FLOAT,
    @SP INT,
    @Exp INT,
    @Lev INT,
    @align INT,
    @PK INT,
    @duel INT,
    @pkpardon INT,
    @ST_underware INT,
    @ST_right_ear INT,
    @ST_left_ear INT,
    @ST_neck INT,
    @ST_right_finger INT,
    @ST_left_finger INT,
    @ST_head INT,
    @ST_right_hand INT,
    @ST_left_hand INT,
    @ST_gloves INT,
    @ST_chest INT,
    @ST_legs INT,
    @ST_feet INT,
    @ST_back INT,
    @ST_both_hand INT,
    @Face_Index INT,
    @Hair_Shape_Index INT,
    @Hair_Color_Index INT,
    @char_id  INT
)
AS

SET NOCOUNT ON

UPDATE
    user_data
set
    class= @class,
    world= @world,
    xloc= @xloc,
    yloc= @yloc,
    zloc= @zloc,
    IsInVehicle= @IsInVehicle,
    HP= @HP,
    MP= @MP,
    max_HP= @max_HP,
    max_MP= @max_MP,
    SP= @SP,
    Exp= @Exp,
    Lev= @Lev,
    align= @align,
    PK= @PK,
    duel= @duel,
    pkpardon= @pkpardon,
    ST_underware= @ST_underware,
    ST_right_ear= @ST_right_ear,
    ST_left_ear= @ST_left_ear,
    ST_neck= @ST_neck,
    ST_right_finger= @ST_right_finger,
    ST_left_finger= @ST_left_finger,
    ST_head= @ST_head,
    ST_right_hand= @ST_right_hand,
    ST_left_hand= @ST_left_hand,
    ST_gloves= @ST_gloves,
    ST_chest= @ST_chest,
    ST_legs= @ST_legs,
    ST_feet= @ST_feet,
    ST_back= @ST_back,
    ST_both_hand= @ST_both_hand,
    Face_Index= @Face_Index,
    Hair_Shape_Index= @Hair_Shape_Index,
    Hair_Color_Index= @Hair_Color_Index
WHERE
    char_id= @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveCharacterPledge    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCharacterPledge

INPUT
OUTPUT
return
made by
    carrot
date
    2003-06-30
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveCharacterPledge]
(
    @pledge_id INT,
    @char_id  INT
)
AS

SET NOCOUNT ON

UPDATE
    user_data
set
    pledge_id= @pledge_id
WHERE
    char_id= @char_id







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveCharacter_temp    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCharacter_temp

INPUT
OUTPUT
return
made by
    carrot
date
    2003-06-13
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveCharacter_temp]
(
    @pledge_id INT,
    @class INT,
    @world INT,
    @xloc INT,
    @yloc INT,
    @zloc INT,
    @IsInVehicle INT,
    @HP FLOAT,
    @MP FLOAT,
    @max_HP FLOAT,
    @max_MP FLOAT,
    @SP INT,
    @Exp INT,
    @Lev INT,
    @align INT,
    @PK INT,
    @duel INT,
    @pkpardon INT,
    @char_id  INT
)
AS

SET NOCOUNT ON

UPDATE
    user_data
set
    class= @class,
    world= @world,
    xloc= @xloc,
    yloc= @yloc,
    zloc= @zloc,
    IsInVehicle= @IsInVehicle,
    HP= @HP,
    MP= @MP,
    max_HP= @max_HP,
    max_MP= @max_MP,
    SP= @SP,
    Exp= @Exp,
    Lev= @Lev,
    align= @align,
    PK= @PK,
    duel= @duel,
    pkpardon= @pkpardon
WHERE
    char_id= @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveCharacter_temp2    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCharacter_temp

INPUT
OUTPUT
return
made by
    carrot
date
    2003-06-13
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveCharacter_temp2]
(
    @ST_underware INT,
    @ST_right_ear INT,
    @ST_left_ear INT,
    @ST_neck INT,
    @ST_right_finger INT,
    @ST_left_finger INT,
    @ST_head INT,
    @ST_right_hand INT,
    @ST_left_hand INT,
    @ST_gloves INT,
    @ST_chest INT,
    @ST_legs INT,
    @ST_feet INT,
    @ST_back INT,
    @ST_both_hand INT,
    @char_id  INT
)
AS

SET NOCOUNT ON

UPDATE
    user_data
set
    ST_underware= @ST_underware,
    ST_right_ear= @ST_right_ear,
    ST_left_ear= @ST_left_ear,
    ST_neck= @ST_neck,
    ST_right_finger= @ST_right_finger,
    ST_left_finger= @ST_left_finger,
    ST_head= @ST_head,
    ST_right_hand= @ST_right_hand,
    ST_left_hand= @ST_left_hand,
    ST_gloves= @ST_gloves,
    ST_chest= @ST_chest,
    ST_legs= @ST_legs,
    ST_feet= @ST_feet,
    ST_back= @ST_back,
    ST_both_hand= @ST_both_hand
WHERE
    char_id= @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_SaveCropData    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveCropData
    create  or update castle crop data
INPUT
    @castle_id	INT,
    @item_type 	INT,
    @droprate 	INT,
    @price 	INT
OUTPUT
return
made by
    carrot
date
    2003-05-06
change 2003-06-11
    add level
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveCropData]
(
    @castle_id	INT,
    @item_type 	INT,
    @droprate 	INT,
    @price 		INT,
    @level 		INT
)
AS
SET NOCOUNT ON

if exists(select item_type from castle_crop where castle_id = @castle_id and item_type = @item_type)
begin
    update castle_crop set droprate =@droprate, price = @price , level = @level where castle_id = @castle_id and item_type = @item_type
end
else
begin
    insert into  castle_crop (castle_id, item_type, droprate, price, level) values (@castle_id,@item_type,@droprate ,@price,@level )
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE [dbo].[lin_SaveDoorStatus]
(
 @hp INT,
 @max_hp INT,
 @name NVARCHAR(50)
)
AS
SET NOCOUNT ON
UPDATE door SET hp = @hp, max_hp = @max_hp WHERE name = @name





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveDropExp    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveDropExp

INPUT
    @drop_exe	int,
    @char_id	int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SaveDropExp]
(
    @drop_exe	int,
    @char_id	int
)
AS
SET NOCOUNT ON

update user_data set drop_exp = @drop_exe where char_id = @char_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveNpcBoss    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveNpcBoss

INPUT
OUTPUT
return
made by
date
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveNpcBoss]
(
@npc_db_name	nvarchar(50),
@alive		INT,
@hp 		INT,
@mp 		INT,
@pos_x 		INT,
@pos_y 		INT,
@pos_z 		INT,
@time_low 	INT,
@time_high	INT
)
AS
SET NOCOUNT ON

if exists(select alive from npc_boss where npc_db_name = @npc_db_name)
begin
    update npc_boss
    set
        alive=@alive, hp=@hp, mp=@mp, pos_x=@pos_x, pos_y=@pos_y, pos_z=@pos_z, time_low=@time_low, time_high=@time_high
    where npc_db_name = @npc_db_name
end
else
begin
    insert into npc_boss values
    (@npc_db_name, @alive, @hp,@mp, @pos_x, @pos_y,@pos_z, @time_low, @time_high, 0)
end



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SaveObjectHp    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SaveObjectHp

INPUT
    @hp	int,
    @id	int
OUTPUT

return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SaveObjectHp]
(
    @hp	int,
    @id	int
)
AS
SET NOCOUNT ON

UPDATE object_data SET hp = @hp WHERE id = @id







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_SavePet

INPUT
OUTPUT
return
made by
    kuooo
date
    2003-08-19
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SavePet]
(
    @pet_id 	INT,
    @expoint	INT,
    @hp		float,
    @mp		float,
    @sp		INT,
    @meal		INT,
    @nick_name	NVARCHAR(50),
    @slot1		int,
    @slot2		int
)
AS

SET NOCOUNT ON

UPDATE
    pet_data
set
    expoint = @expoint,
    hp = @hp,
    mp = @mp,
    sp = @sp,
    meal = @meal,
    nick_name = @nick_name,
    slot1 = @slot1,
    slot2 = @slot2
WHERE
    pet_id = @pet_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_SavePledgeContribution

INPUT
    @contribution INT
    @pledge_id INT
    @residence_id INT

OUTPUT
return

********************************************/
CREATE PROCEDURE [DBO].[lin_SavePledgeContribution]
(
    @contribution INT,
    @pledge_id INT,
    @residence_id INT
)
AS
SET NOCOUNT ON

UPDATE pledge_contribution SET contribution = contribution + @contribution WHERE pledge_id = @pledge_id AND residence_id = @residence_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO

/********************************************
lin_SaveTimeData
 Save time data table
INPUT
 @char_name NVARCHAR(30),
 @nUsedSec INT
OUTPUT
return

made by
 carrot
date
 2004-05-10
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SaveTimeData]
(
 @account_id INT,
 @nUsedSec INT,
 @dtLastSaveDate NVARCHAR(20)
)
AS

SET NOCOUNT ON

IF (@nUsedSec < 0)
BEGIN
    RAISERROR ('Not valid parameter : account id[%d] sec[%d], dt[%s] ',16, 1,  @account_id,  @nUsedSec, @dtLastSaveDate)
    RETURN -1
END

UPDATE  time_data SET last_logout = @dtLastSaveDate, used_sec = @nUsedSec WHERE account_id = @account_id

IF (@@ROWCOUNT = 0)
BEGIN
    INSERT INTO time_data (account_id, last_logout, used_sec) VALUES (@account_id, @dtLastSaveDate, @nUsedSec)
END

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_SeizeItem    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SeizeItem

INPUT
    @option	INT,
    @warehouse	INT,
    @item_id	INT
OUTPUT
return
made by
    young
date
    2003-06-25
********************************************/
create PROCEDURE [DBO].[lin_SeizeItem]
(
@option	INT,
@warehouse	INT,
@item_id	INT
)
AS
SET NOCOUNT ON

if @option = 1
    update user_item set warehouse = 1001 where item_id = @item_id
else if @option = 2
    update user_item set warehouse = @warehouse where item_id = @item_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



/********************************************
lin_SetAgitAuction
    create agit bid
INPUT
    @auction_id	int

OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_SetAgitAuction]
(
@agit_id		INT,
@auction_id		INT,
@next_cost		INT

)
AS
SET NOCOUNT ON

declare @max_price  int
declare @attend_id int
declare @pledge_id int
declare @tax int

set @attend_id = 0
set @max_price = 0
set @pledge_id = 0
set @tax = 0

select top 1 @max_price = attend_price, @attend_id = attend_id, @pledge_id = attend_pledge_id from agit_bid (nolock)
    where auction_id = @auction_id
    order by attend_price desc, attend_id asc

if ( @max_price > 0 )
begin
    -- 낙찰
    update agit_auction set accepted_bid = @attend_id where auction_id = @auction_id
    update agit set auction_id = null , last_price = @max_price, next_cost = @next_cost  , cost_fail = NULL  where id = @agit_id
    update pledge set agit_id = @agit_id where pledge_id = @pledge_id
    select @tax = isnull ( auction_tax , 0) from agit_auction (nolock) where auction_id = @auction_id
end  else begin
    -- 유찰
    update agit_auction set accepted_bid = 0 where auction_id = @auction_id
    update agit set auction_id = null , next_cost = 0 , cost_fail = NULL where id = @agit_id
end

select @attend_id, @max_price, @pledge_id, @tax




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/********************************************
lin_SetAgitNextCost

INPUT


OUTPUT
return
made by
    young
date
    2003-12-1
********************************************/
CREATE PROCEDURE [DBO].[lin_SetAgitNextCost]
(
@agit_id		INT,
@next_cost		INT,
@cost_fail		int=0

)
AS
SET NOCOUNT ON

update agit set next_cost = @next_cost  , cost_fail = @cost_fail where id = @agit_id


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetAgitOwner2    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetAgitOwner2

INPUT
    @pledge_id	int,
    @agit_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SetAgitOwner2]
(
    @pledge_id	int,
    @agit_id		int
)
AS
SET NOCOUNT ON

UPDATE agit SET pledge_id = @pledge_id WHERE id = @agit_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_SetAllianceInfo    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_SetAllianceInfo

INPUT
    @fieldName	nvarchar(50),
    @field_data	INT,
    @pledge_id	INT
OUTPUT

return
made by
    bert ^^
********************************************/

CREATE PROCEDURE [DBO].[lin_SetAllianceInfo]
(
@fieldName	nvarchar(50),
@field_data	INT,
@alliance_id	INT
)
AS
SET NOCOUNT ON

IF @fieldName = N'oust_time' begin update alliance set oust_time = @field_data where id =  @alliance_id end
ELSE IF @fieldName = N'crest_id' begin update alliance set crest_id = @field_data where id =  @alliance_id end
ELSE
BEGIN
    RAISERROR ('lin_SetAllianceInfo : invalid field [%s]', 16, 1, @fieldName)
    RETURN -1
END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetAquireSkill    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetAquireSkill
    add or update user skill data
INPUT
    char_id
    skill id
    skill level

OUTPUT
return
made by
    carrot
date
    2002-09-13
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SetAquireSkill]
(
    @char_id	INT,
    @skill_id		INT,
    @skill_level		TINYINT
)
AS


SET NOCOUNT ON

IF exists(SELECT skill_lev FROM user_skill WHERE char_id = @char_id AND skill_id = @skill_id)
    UPDATE user_skill SET skill_lev = @skill_level WHERE char_id = @char_id AND skill_id = @skill_id
ELSE
    INSERT INTO user_skill (char_id, skill_id, skill_lev) VALUES (@char_id, @skill_id, @skill_level)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_SetBuilderAccount     Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetBuilderAccount
    set builder account
INPUT
    @account_name	nvarchar(50),
    @default_level		int

OUTPUT
return
made by
    young
date
    2002-11-28
change

Application date 2004-05-12
********************************************/
CREATE PROCEDURE [DBO].[lin_SetBuilderAccount ]
(
    @account_name	nvarchar(50),
    @default_level		int
)
AS

SET NOCOUNT ON

if ( @default_level = 0)
begin
    delete from builder_account where account_name = @account_name
end else begin
    if exists(select * from builder_account where account_name = @account_name)
    begin
        update builder_account set default_builder = @default_level where account_name = @account_name
    end else begin
        declare @account_id int
        set @account_id = 0
        select top 1 @account_id = account_id from user_data where account_name = @account_name and account_id > 0
        insert into builder_account(account_name, default_builder, account_id) values(@account_name, @default_level, @account_id)
    end
end

GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetBuilderCharacter    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_SetBuilderCharacter
    Set Builder Character flag
INPUT
    @char_name	nvarchar,
    @nBuilderLev	int
OUTPUT
    char_id
return
made by
    carrot
date
    2002-06-28
********************************************/
CREATE PROCEDURE [DBO].[lin_SetBuilderCharacter]
(
    @char_name	NVARCHAR(24),
    @nBuilderLev	INT
)
AS

SET NOCOUNT ON

DECLARE @Char_id INT
SET @Char_id = 0

UPDATE user_data SET builder =  @nBuilderLev WHERE char_name = @char_name
IF @@ROWCOUNT > 0
BEGIN
    SELECT @Char_id = char_id FROM user_data WHERE char_name = @char_name
END

SELECT @Char_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetCastleOwner2    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetCastleOwner2

INPUT
    @pledge_id	int,
    @agit_id		int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SetCastleOwner2]
(
    @pledge_id	int,
    @castle_id		int
)
AS
SET NOCOUNT ON

UPDATE castle SET pledge_id = @pledge_id WHERE id = @castle_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetCharacterDelete    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_SetCharacterDelete
    Set character is deleted
INPUT
    @char_id	INT
OUTPUT
    year
    month
    day
return
made by
    carrot
date
    2003-01-7
********************************************/
CREATE PROCEDURE [DBO].[lin_SetCharacterDelete]
(
    @char_id	INT
)
AS

SET NOCOUNT ON

DECLARE @deletedDate	SMALLDATETIME

SET @deletedDate = GetDate()

UPDATE user_data SET temp_delete_date = @deletedDate WHERE char_id = @char_id

IF @@ROWCOUNT > 0
BEGIN
    SELECT YEAR(@deletedDate), MONTH(@deletedDate), DAY(@deletedDate)
END
ELSE
BEGIN
    SELECT 0,0,0
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetCharacterDeleteRestore    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_SetCharacterDeleteRestore
    Restore character which is set deleted
INPUT
    @char_id	INT
OUTPUT
return
made by
    carrot
date
    2003-01-7
********************************************/
CREATE PROCEDURE [DBO].[lin_SetCharacterDeleteRestore]
(
    @char_id	INT
)
AS

SET NOCOUNT ON

UPDATE user_data SET temp_delete_date = NULL WHERE char_id = @char_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




/********************************************
lin_SetIntervalAnnounce
    set interval announce
INPUT

OUTPUT
    interval
    announce id
    msg
return
made by
    carrot
date
    2003-12-19
********************************************/
CREATE PROCEDURE [DBO].[lin_SetIntervalAnnounce]
(
    @nInterval 	INT,
    @nAnnounceId	INT,
    @wsMsg	NVARCHAR(100)
)
AS
SET NOCOUNT ON

if EXISTS(select top 1 * from login_announce where interval_10 = @nInterval and announce_id = @nAnnounceId)
  BEGIN
    UPDATE login_announce SET announce_msg = @wsMsg WHERE interval_10 = @nInterval and announce_id = @nAnnounceId
  END
ELSE
  BEGIN
    INSERT INTO login_announce (interval_10, announce_id, announce_msg) VALUES (@nInterval, @nAnnounceId, @wsMsg)
  END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



/********************************************
lin_SetLastTaxUpdate

INPUT
@income  datetime,
@tax datetime
OUTPUT
made by
 carrot
date
 2004-02-29
********************************************/
create PROCEDURE [DBO].[lin_SetLastTaxUpdate]
(
@income  datetime,
@tax datetime
)
AS

-- date fix addon, smeli

declare @income_ datetime
declare @tax_ datetime

set @income_ = CONVERT(Datetime, @income, 120)
set @tax_ = CONVERT(Datetime, @tax, 120)

-- end date fix addon, smeli

SET NOCOUNT ON

IF EXISTS(SELECT * FROM castle_tax)
BEGIN
 UPDATE castle_tax SET   income_update =  @income_, tax_change =   @tax_
END
ELSE
BEGIN
 INSERT INTO castle_tax VALUES
 (  @income_, @tax_)

END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO






/****** Object:  Stored Procedure dbo.lin_SetLoginAnnounce    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetLoginAnnounce
    set login announce
INPUT
    @announce_id int,
    @announce_msg nvarchar(64)
OUTPUT

return
made by
    young
date
    2002-11-30
********************************************/
CREATE PROCEDURE [DBO].[lin_SetLoginAnnounce]
(
    @announce_id int ,
    @announce_msg nvarchar(64)
)

AS

SET NOCOUNT ON


if exists(select announce_id from login_announce (nolock) where announce_id = @announce_id  and interval_10 = 0 )
begin

    update login_announce set announce_msg = @announce_msg where announce_id = @announce_id and interval_10 = 0

end else begin

    insert into login_announce(announce_id, announce_msg , interval_10 ) values(@announce_id, @announce_msg, 0 )

end


GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetPetitionMsg    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetPetitionMsg
    store Petition Msg
INPUT
    @char_id	int,
    @msg	nvarchar(500)
OUTPUT

return
made by
    carrot
date
    2003-02-27
********************************************/
CREATE PROCEDURE [DBO].[lin_SetPetitionMsg]
(
    @char_id	int,
    @msg	nvarchar(500)
)
AS
SET NOCOUNT ON

if exists(select * from PetitionMsg where char_id =@char_id)
begin
    update PetitionMsg set msg = @msg where char_id = @char_id
end
else
begin
    insert into PetitionMsg  (char_id, msg)
    values( @char_id, @msg)
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetPledgeCrest    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_SetPledgeCrest
-- by bert
-- return crest id

CREATE PROCEDURE [DBO].[lin_SetPledgeCrest]
(
    @bitmap_size	INT,
    @bitmap	VARBINARY(1270)
)
AS

SET NOCOUNT ON

INSERT INTO Pledge_Crest
(bitmap_size, bitmap) VALUES (@bitmap_size, @bitmap)

SELECT @@IDENTITY




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetPledgeInfo    Script Date: 2003-09-20 오전 11:52:00 ******/

/********************************************
lin_SetPledgeInfo

INPUT
    @fieldName	nvarchar(50),
    @field_data	INT,
    @pledge_id	INT
OUTPUT

return
made by
    carrot
date
    2002-06-16
********************************************/
CREATE PROCEDURE [DBO].[lin_SetPledgeInfo]
(
@fieldName	nvarchar(50),
@field_data	INT,
@pledge_id	INT
)
AS
SET NOCOUNT ON

IF @fieldName = N'alliance_id' begin update pledge set alliance_id = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'challenge_time' begin update pledge set challenge_time = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'root_name_value' begin update pledge set root_name_value = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'now_war_id' begin update pledge set now_war_id = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'oust_time' begin update pledge set oust_time = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'skill_level' begin update pledge set skill_level = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'castle_id' begin update pledge set castle_id = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'agit_id' begin update pledge set agit_id = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'rank' begin update pledge set rank = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'name_value' begin update pledge set name_value = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'status' begin update pledge set status = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'private_flag' begin update pledge set private_flag = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'crest_id' begin update pledge set crest_id = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'is_guilty' begin update pledge set is_guilty = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'dismiss_reserved_time' begin update pledge set dismiss_reserved_time = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'alliance_ousted_time' begin update pledge set alliance_ousted_time = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'alliance_withdraw_time' begin update pledge set alliance_withdraw_time = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'alliance_dismiss_time' begin update pledge set alliance_dismiss_time = @field_data where pledge_id =  @pledge_id end
ELSE IF @fieldName = N'ruler_id' begin update pledge set ruler_id = @field_data where pledge_id =  @pledge_id end
ELSE
BEGIN
    RAISERROR ('lin_SetPledgeInfo : invalid field [%s]', 16, 1, @fieldName)
    RETURN -1
END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_SetPunish    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetPunish
    Set punish
INPUT
    @char_id	INT,
    @punish_id 	INT,
    @punish_on	INT,
    @remain	INT
OUTPUT
return
made by
    young
date
    2002-11-27
********************************************/
CREATE PROCEDURE [DBO].[lin_SetPunish]
(
    @char_id	INT,
    @punish_id	INT,
    @punish_on	INT,
    @remain	INT

)
AS
SET NOCOUNT ON

declare @nCount int

select @nCount = count(*) from user_punish (nolock) where char_id = @char_id and punish_id = @punish_id

if ( @nCount > 0 and @remain = 0)
begin
    delete from user_punish where char_id = @char_id and punish_id = @punish_id
end

if ( @nCount > 0 and @remain > 0)
begin
    if @punish_on = 1
        update user_punish set  remain_game = @remain where char_id = @char_id and punish_id = @punish_id

    if @punish_on = 0
        update user_punish set  remain_real = @remain  where char_id = @char_id and punish_id = @punish_id

end

if ( @nCount = 0 and @remain > 0)
begin
    if @punish_on = 1
        insert into user_punish(char_id, punish_id, punish_on, remain_game) values (@char_id, @punish_id, 1, @remain)

    if @punish_on = 0
        insert into user_punish(char_id, punish_id, punish_on, remain_real) values (@char_id, @punish_id, 0, @remain)
end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetQuest    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_SetQuest

INPUT
@q1	INT,
@s1	INT,
@j1	INT,

@q2	INT,
@s2	INT,
@j2	INT,

@q3	INT,
@s3	INT,
@j3	INT,

@q4	INT,
@s4	INT,
@j4	INT,

@q5	INT,
@s5	INT,
@j5	INT,

@q6	INT,
@s6	INT,
@j6	INT,


@q7	INT,
@s7	INT,
@j7	INT,

@q8	INT,
@s8	INT,
@j8	INT,

@q9	INT,
@s9	INT,
@j9	INT,

@q10	INT,
@s10	INT,
@j10	INT,

@q11	INT,
@s11	INT,
@j11	INT,

@q12	INT,
@s12	INT,
@j12	INT,

@q13	INT,
@s13	INT,
@j13	INT,

@q14	INT,
@s14	INT,
@j14	INT,

@q15	INT,
@s15	INT,
@j15	INT,

@q16	INT,
@s16	INT,
@j16	INT,

@char_id		INT
OUTPUT
return
made by
    carrot
date
    2002-06-09
********************************************/
CREATE PROCEDURE [DBO].[lin_SetQuest]
(
@q1	INT,
@s1	INT,
@j1	INT,

@q2	INT,
@s2	INT,
@j2	INT,

@q3	INT,
@s3	INT,
@j3	INT,

@q4	INT,
@s4	INT,
@j4	INT,

@q5	INT,
@s5	INT,
@j5	INT,

@q6	INT,
@s6	INT,
@j6	INT,


@q7	INT,
@s7	INT,
@j7	INT,

@q8	INT,
@s8	INT,
@j8	INT,

@q9	INT,
@s9	INT,
@j9	INT,

@q10	INT,
@s10	INT,
@j10	INT,

@q11	INT,
@s11	INT,
@j11	INT,

@q12	INT,
@s12	INT,
@j12	INT,

@q13	INT,
@s13	INT,
@j13	INT,

@q14	INT,
@s14	INT,
@j14	INT,

@q15	INT,
@s15	INT,
@j15	INT,

@q16	INT,
@s16	INT,
@j16	INT,

@char_id		INT

)
AS
SET NOCOUNT ON

UPDATE quest
SET
    q1=@q1, s1=@s1,   j1=@j1,
    q2=@q2, s2=@s2,   j2=@j2,
    q3=@q3, s3=@s3,   j3=@j3,
    q4=@q4, s4=@s4,   j4=@j4,
    q5=@q5, s5=@s5,   j5=@j5,
    q6=@q6, s6=@s6,   j6=@j6,
    q7=@q7, s7=@s7,   j7=@j7,
    q8=@q8, s8=@s8,   j8=@j8,
    q9=@q9, s9=@s9,   j9=@j9,
    q10=@q10, s10=@s10,   j10=@j10,
    q11=@q11, s11=@s11,   j11=@j11,
    q12=@q12, s12=@s12,   j12=@j12,
    q13=@q13, s13=@s13,   j13=@j13,
    q14=@q14, s14=@s14,   j14=@j14,
    q15=@q15, s15=@s15,   j15=@j15,
    q16=@q16, s16=@s16 ,	 j16=@j16
WHERE char_id = @char_id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetShortCut    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetShortCut
    Set short cut macro
INPUT
    @char_id	INT,
    @slotnum 	INT,
    @type 		INT,
    @id 		INT,
    @macro 		NVARCHAR(256)
OUTPUT
return
made by
    carrot
date
    2002-11-02
********************************************/
CREATE PROCEDURE [DBO].[lin_SetShortCut]
(
    @char_id	INT,
    @slotnum 	INT,
    @type 		INT,
    @id 		INT,
    @macro 		NVARCHAR(256)
)
AS
SET NOCOUNT ON

IF (@type = 0)
BEGIN
    DELETE shortcut_data WHERE  char_id = @char_id AND slotnum = @slotnum
END
ELSE
BEGIN
    UPDATE shortcut_data SET shortcut_type=@type , shortcut_id= @id, shortcut_macro = @macro WHERE char_id = @char_id AND slotnum = @slotnum
    IF (@@ROWCOUNT = 0)
    BEGIN
        INSERT INTO shortcut_data values (@char_id, @slotnum, @type, @id, @macro)
    END
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetSiegeTime    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetSiegeTime

INPUT
    @next_war_time	int,
    @castle_id	int,
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SetSiegeTime]
(
    @next_war_time	int,
    @castle_id	int
)
AS
SET NOCOUNT ON

UPDATE
    castle
SET
    next_war_time = @next_war_time
WHERE
    id = @castle_id






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetSkillCoolTime    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetSkillCoolTime

INPUT
    char_id
    skill id
    skill level

OUTPUT
return
made by
    carrot
date
    2003-06-27
change
********************************************/
CREATE PROCEDURE [DBO].[lin_SetSkillCoolTime]
(
    @char_id	INT,
    @skill_id		INT,
    @nToEndTime	INT
)
AS


SET NOCOUNT ON

UPDATE user_skill SET to_end_time = @nToEndTime WHERE char_id = @char_id AND skill_id = @skill_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/********************************************
lin_SetUserBan

INPUT
    @char_id	INT
    @ban_hour	smallint
OUTPUT
return
made by
    young
date
    2003-09-22
********************************************/
CREATE PROCEDURE [DBO].[lin_SetUserBan]
(
    @char_id	INT,
    @status		INT,
    @ban_hour	smallint,
    @ban_end	INT
)
AS
SET NOCOUNT ON

if @ban_hour = 0
begin
    delete from user_ban where char_id = @char_id
end else begin

    if ( exists ( select * from user_ban (nolock) where char_id = @char_id ) )
    begin
        -- update
        update user_ban set status = @status, ban_date = getdate(), ban_hour = @ban_hour, ban_end = @ban_end where char_id = @char_id
    end else begin
        -- insert
        insert into user_ban ( char_id, status, ban_hour , ban_end ) values ( @char_id, @status, @ban_hour, @ban_end  )
    end
end



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetUserDataEx    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_SetUserDataEx

INPUT
    @char_id	int,
    @dismiss_penalty_reserved	int
OUTPUT
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_SetUserDataEx]
(
    @char_id	int,
    @dismiss_penalty_reserved	int
)
AS
SET NOCOUNT ON

INSERT INTO user_data_ex (char_id, dismiss_penalty_reserved) VALUES (@char_id, @dismiss_penalty_reserved)






GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SetUserNickname    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE
dbo.lin_SetUserNickname (@user_id INT, @nickname NVARCHAR(50))
AS

SET NOCOUNT ON

DECLARE @ret INT

UPDATE user_data
SET nickname = @nickname
WHERE char_id = @user_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = @user_id
END
ELSE
BEGIN
    SELECT @ret = 0
END

SELECT @ret




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




-- lin_StartAllianceWar
-- by bert

CREATE PROCEDURE
dbo.lin_StartAllianceWar (@challenger_alliance_id INT, @challengee_alliance_id INT, @war_begin_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

DECLARE @challenger_name VARCHAR(50)
DECLARE @challengee_name VARCHAR(50)

SELECT @challenger_name = name FROM alliance WHERE id = @challenger_alliance_id
SELECT @challengee_name = name FROM alliance WHERE id = @challengee_alliance_id

INSERT INTO Alliance_War
(challenger, challengee, begin_time, challenger_name, challengee_name)
VALUES
(@challenger_alliance_id, @challengee_alliance_id, @war_begin_time, @challenger_name, @challengee_name)

SELECT @@IDENTITY



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_StartPledgeWar    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_StartPledgeWar
-- by bert

CREATE PROCEDURE
dbo.lin_StartPledgeWar (@challenger_pledge_id INT, @challengee_pledge_id INT, @war_begin_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

DECLARE @challenger_name VARCHAR(50)
DECLARE @challengee_name VARCHAR(50)

SELECT @challenger_name = name FROM Pledge WHERE pledge_id = @challenger_pledge_id
SELECT @challengee_name = name FROM Pledge WHERE pledge_id = @challengee_pledge_id

INSERT INTO Pledge_War
(challenger, challengee, begin_time, challenger_name, challengee_name)
VALUES
(@challenger_pledge_id, @challengee_pledge_id, @war_begin_time, @challenger_name, @challengee_name)

SELECT @@IDENTITY



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



CREATE PROCEDURE
dbo.lin_StopAllianceWar (@proposer_alliance_id INT, @proposee_alliance_id INT, @war_id INT,  @war_end_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

UPDATE Alliance_War
SET status = 1,	-- WAR_END_STOP
winner = 0,
end_time = @war_end_time
WHERE
id = @war_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = @war_id
END
ELSE
BEGIN
    SELECT @ret = 0
END

SELECT @ret



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_StopPledgeWar    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_StopPledgeWar
-- by bert

CREATE PROCEDURE
dbo.lin_StopPledgeWar (@proposer_pledge_id INT, @proposee_pledge_id INT, @war_id INT,  @war_end_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

UPDATE Pledge_War
SET status = 1,	-- WAR_END_STOP
winner = 0,
end_time = @war_end_time
WHERE
id = @war_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = @war_id
END
ELSE
BEGIN
    SELECT @ret = 0
END

EXIT_TRAN:
IF @ret<> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END
SELECT @ret



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




-- lin_SurrenderAllianceWar
-- by bert

CREATE PROCEDURE
dbo.lin_SurrenderAllianceWar (@proposer_alliance_id INT, @proposee_alliance_id INT, @war_id INT, @war_end_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

UPDATE alliance_war
SET status = 2,	-- WAR_END_SURRENDER
winner = @proposee_alliance_id,
winner_name = (SELECT name FROM alliance WHERE id = @proposee_alliance_id),
end_time = @war_end_time
WHERE
id = @war_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = @war_id
END
ELSE
BEGIN
    SELECT @ret = 0
END

SELECT @ret



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE dbo.lin_SurrenderPersonally(@char_id INT, @war_id INT)
AS

SET NOCOUNT ON

INSERT INTO user_surrender
(char_id, surrender_war_id)
VALUES
(@char_id, @war_id)

SELECT @@ROWCOUNT





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_SurrenderPledgeWar    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_SurrenderPledgeWar
-- by bert

CREATE PROCEDURE
dbo.lin_SurrenderPledgeWar (@proposer_pledge_id INT, @proposee_pledge_id INT, @war_id INT, @war_end_time INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

UPDATE Pledge_War
SET status = 2,	-- WAR_END_SURRENDER
winner = @proposee_pledge_id,
winner_name = (SELECT name FROM Pledge WHERE pledge_id = @proposee_pledge_id),
end_time = @war_end_time
WHERE
id = @war_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @ret = @war_id
END
ELSE
BEGIN
    SELECT @ret = 0
END

IF @ret<> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END
SELECT @ret



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_TrasferWarehouseNewAll    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_TrasferWarehouseNewPartial
    movet inventory to warehouse || move warehouse to inventory total item
INPUT
    @char_id		INT,
    @item_id			INT,
    @ToWarehouseID	INT,
    @bIsToInven		TINYINT
OUTPUT

return
made by
    carrot
date
    2002-10-17
********************************************/
CREATE PROCEDURE [DBO].[lin_TrasferWarehouseNewAll]
(
    @char_id		INT,
    @item_id			INT,
    @ToWarehouseID	INT,
    @bIsToInven		TINYINT
)
AS
SET NOCOUNT ON

IF (@bIsToInven > 0)
BEGIN
    SET IDENTITY_INSERT user_item ON

    IF (SELECT COUNT(*) FROm user_warehouse WHERE item_id = @item_id) = 1
    BEGIN
        INSERT INTO user_item (item_id, char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
            SELECT item_id, char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse FROM user_warehouse WHERE item_id = @item_id
        IF @@ROWCOUNT = 0
        BEGIN
            SELECT 0
        END
        ELSE
        BEGIN
            DELETE user_warehouse WHERE item_id = @item_id
            SELECT 1
        END
    END
    ELSE
    BEGIN
        SELECT 0
    END

    SET IDENTITY_INSERT user_item OFF
END
ELSE
BEGIN
    IF (SELECT COUNT(*) FROm user_item WHERE item_id = @item_id) = 1
    BEGIN
        INSERT INTO user_warehouse (item_id, char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
            SELECT item_id, char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse FROM user_item WHERE item_id = @item_id
        IF @@ROWCOUNT = 0
        BEGIN
            SELECT 0
        END
        ELSE
        BEGIN
            DELETE user_item WHERE item_id = @item_id
            SELECT 1
        END
    END
    ELSE
    BEGIN
        SELECT 0
    END
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_TrasferWarehouseNewPartial    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_TrasferWarehouseNewPartial
    move inventory to warehouse || move warehouse to inventory total partial item
INPUT
    @char_id		INT,
    @item_id			INT,
    @ToWarehouseID	INT,
    @bIsToInven		TINYINT
    @nCount			INT
OUTPUT
    bIsSuccess		1/0
return
made by
    carrot
date
    2002-10-17
********************************************/
CREATE PROCEDURE [DBO].[lin_TrasferWarehouseNewPartial]
(
    @char_id		INT,
    @item_id			INT,
    @ToWarehouseID	INT,
    @bIsToInven		TINYINT,
    @nCount			INT
)
AS
SET NOCOUNT ON

IF (@bIsToInven > 0)
BEGIN
    IF (SELECT amount FROm user_warehouse WHERE item_id = @item_id) > @nCount
    BEGIN
        INSERT INTO user_item (char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
            SELECT char_id, item_type, @nCount, enchant, eroded, bless, ident, wished, warehouse FROM user_warehouse WHERE item_id = @item_id
        IF @@ROWCOUNT = 0
        BEGIN
            SELECT 0
        END
        ELSE
        BEGIN
            SELECT item_id FROM user_item WHERE item_id = @@IDENTITY
            UPDATE user_warehouse SET amount = amount - @nCount WHERE item_id = @item_id
        END
    END
    ELSE
    BEGIN
        SELECT 0
    END
END
ELSE
BEGIN
    IF (SELECT amount FROm user_item WHERE item_id = @item_id) > @nCount
    BEGIN
        INSERT INTO user_item (char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
            SELECT char_id, item_type, @nCount, enchant, eroded, bless, ident, wished, warehouse FROM user_item WHERE item_id = @item_id
        INSERT INTO user_warehouse (item_id, char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse)
            SELECT item_id, char_id, item_type, @nCount, enchant, eroded, bless, ident, wished, warehouse FROM user_item WHERE item_id = @@IDENTITY
        IF @@ROWCOUNT = 0
        BEGIN
            SELECT 0
        END
        ELSE
        BEGIN
            SELECT item_id FROM user_warehouse WHERE item_id = @@IDENTITY
            DELETE user_item WHERE item_id = @@IDENTITY
            UPDATE user_item SET amount = amount - @nCount WHERE item_id = @item_id
        END
    END
    ELSE
    BEGIN
        SELECT 0
    END
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_UninstallAllBattleCamp    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_UninstallAllBattleCamp
-- by bert
-- return deleted battle camp ids

CREATE PROCEDURE dbo.lin_UninstallAllBattleCamp (@castle_id INT, @type INT)
AS

SET NOCOUNT ON

SELECT id FROM object_data WHERE residence_id = @castle_id AND type = @type

DELETE FROM object_data WHERE residence_id = @castle_id AND type = @type




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_UninstallBattleCamp    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_UninstalllBattleCamp
-- by bert
-- return deleted battle camp id

CREATE PROCEDURE dbo.lin_UninstallBattleCamp (@pledge_id INT, @type INT)
AS

SET NOCOUNT ON

SELECT id FROM object_data WHERE owner_id = @pledge_id AND type = @type

DELETE FROM object_data WHERE owner_id = @pledge_id AND type = @type





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO




/****** Object:  Stored Procedure dbo.lin_UpdateActiveSkill    Script Date: 2003-09-20 오전 11:52:00 ******/
CREATE PROCEDURE [DBO].[lin_UpdateActiveSkill]
(
 @char_id INT,
 @s1 INT, @l1 TINYINT, @d1 INT, @c1 TINYINT,
 @s2 INT, @l2 TINYINT, @d2 INT, @c2 TINYINT,
 @s3 INT, @l3 TINYINT, @d3 INT, @c3 TINYINT,
 @s4 INT, @l4 TINYINT, @d4 INT, @c4 TINYINT,
 @s5 INT, @l5 TINYINT, @d5 INT, @c5 TINYINT,
 @s6 INT, @l6 TINYINT, @d6 INT, @c6 TINYINT,
 @s7 INT, @l7 TINYINT, @d7 INT, @c7 TINYINT,
 @s8 INT, @l8 TINYINT, @d8 INT, @c8 TINYINT,
 @s9 INT, @l9 TINYINT, @d9 INT, @c9 TINYINT,
 @s10 INT, @l10 TINYINT, @d10 INT, @c10 TINYINT,
 @s11 INT, @l11 TINYINT, @d11 INT, @c11 TINYINT,
 @s12 INT, @l12 TINYINT, @d12 INT, @c12 TINYINT,
 @s13 INT, @l13 TINYINT, @d13 INT, @c13 TINYINT,
 @s14 INT, @l14 TINYINT, @d14 INT, @c14 TINYINT,
 @s15 INT, @l15 TINYINT, @d15 INT, @c15 TINYINT,
 @s16 INT, @l16 TINYINT, @d16 INT, @c16 TINYINT,
 @s17 INT, @l17 TINYINT, @d17 INT, @c17 TINYINT,
 @s18 INT, @l18 TINYINT, @d18 INT, @c18 TINYINT,
 @s19 INT, @l19 TINYINT, @d19 INT, @c19 TINYINT,
 @s20 INT, @l20 TINYINT, @d20 INT, @c20 TINYINT
)
AS
SET NOCOUNT ON

IF EXISTS(SELECT * FROM user_activeskill WHERE char_id = @char_id)
BEGIN
 UPDATE user_activeskill
 SET
 s1 = @s1, l1 = @l1, d1 = @d1, c1 = @c1,
 s2 = @s2, l2 = @l2, d2 = @d2, c2 = @c2,
 s3 = @s3, l3 = @l3, d3 = @d3, c3 = @c3,
 s4 = @s4, l4 = @l4, d4 = @d4, c4 = @c4,
 s5 = @s5, l5 = @l5, d5 = @d5, c5 = @c5,
 s6 = @s6, l6 = @l6, d6 = @d6, c6 = @c6,
 s7 = @s7, l7 = @l7, d7 = @d7, c7 = @c7,
 s8 = @s8, l8 = @l8, d8 = @d8, c8 = @c8,
 s9 = @s9, l9 = @l9, d9 = @d9, c9 = @c9,
 s10 = @s10, l10 = @l10, d10 = @d10, c10 = @c10,
 s11 = @s11, l11 = @l11, d11 = @d11, c11 = @c11,
 s12 = @s12, l12 = @l12, d12 = @d12, c12 = @c12,
 s13 = @s13, l13 = @l13, d13 = @d13, c13 = @c13,
 s14 = @s14, l14 = @l14, d14 = @d14, c14 = @c14,
 s15 = @s15, l15 = @l15, d15 = @d15, c15 = @c15,
 s16 = @s16, l16 = @l16, d16 = @d16, c16 = @c16,
 s17 = @s17, l17 = @l17, d17 = @d17, c17 = @c17,
 s18 = @s18, l18 = @l18, d18 = @d18, c18 = @c18,
 s19 = @s19, l19 = @l19, d19 = @d19, c19 = @c19,
 s20 = @s20, l20 = @l20, d20 = @d20, c20 = @c20
 WHERE char_id = @char_id
END
ELSE
BEGIN
 INSERT INTO user_activeskill
 (char_id,
 s1, l1, d1, c1,
 s2, l2, d2, c2,
 s3, l3, d3, c3,
 s4, l4, d4, c4,
 s5, l5, d5, c5,
 s6, l6, d6, c6,
 s7, l7, d7, c7,
 s8, l8, d8, c8,
 s9, l9, d9, c9,
 s10, l10, d10, c10,
 s11, l11, d11, c11,
 s12, l12, d12, c12,
 s13, l13, d13, c13,
 s14, l14, d14, c14,
 s15, l15, d15, c15,
 s16, l16, d16, c16,
 s17, l17, d17, c17,
 s18, l18, d18, c18,
 s19, l19, d19, c19,
 s20, l20, d20, c20)
 VALUES
 (@char_id,
 @s1, @l1, @d1, @c1,
 @s2, @l2, @d2, @c2,
 @s3, @l3, @d3, @c3,
 @s4, @l4, @d4, @c4,
 @s5, @l5, @d5, @c5,
 @s6, @l6, @d6, @c6,
 @s7, @l7, @d7, @c7,
 @s8, @l8, @d8, @c8,
 @s9, @l9, @d9, @c9,
 @s10, @l10, @d10, @c10,
 @s11, @l11, @d11, @c11,
 @s12, @l12, @d12, @c12,
 @s13, @l13, @d13, @c13,
 @s14, @l14, @d14, @c14,
 @s15, @l15, @d15, @c15,
 @s16, @l16, @d16, @c16,
 @s17, @l17, @d17, @c17,
 @s18, @l18, @d18, @c18,
 @s19, @l19, @d19, @c19,
 @s20, @l20, @d20, @c20)
END



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_UpdateCastle    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE
dbo.lin_UpdateCastle (@id INT, @pledge_id INT, @next_war_time INT, @tax_rate SMALLINT)
AS
UPDATE castle
SET pledge_id = @pledge_id, next_war_time = @next_war_time, tax_rate = @tax_rate
WHERE id = @id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_UpdateCastleWar    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_UpdateCastleWar
-- by bert ( -_-)/

CREATE PROCEDURE
dbo.lin_UpdateCastleWar (@castle_id INT, @pledge_id INT, @status INT)
AS
SET NOCOUNT ON

UPDATE castle_war
SET type = @status
WHERE castle_id = @castle_id AND pledge_id = @pledge_id

SELECT @@ROWCOUNT




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_UpdateControlTower
(
@control_level INT,
@hp INT,
@status INT,
@name VARCHAR(256)
)
AS
UPDATE control_tower
SET
control_level = @control_level,
hp = @hp,
status = @status
WHERE name = @name
IF @@ROWCOUNT <> 1
BEGIN
RAISERROR ('Failed to Update Control Tower name = %s.', 16, 1, @name)
END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





--	kuooo
CREATE PROCEDURE
dbo.lin_UpdateJournal ( @id INT,
@j1 int, @j2 int, @j3 int, @j4 int, @j5 int, @j6 int, @j7 int, @j8 int,
@j9 int, @j10 int, @j11 int, @j12 int, @j13 int, @j14 int, @j15 int, @j16 int)
AS
UPDATE Quest
set
j1 = @j1,
j2 = @j2,
j3 = @j3,
j4 = @j4,
j5 = @j5,
j6 = @j6,
j7 = @j7,
j8 = @j8,
j9 = @j9,
j10 = @j10,
j11 = @j11,
j12 = @j12,
j13 = @j13,
j14 = @j14,
j15 = @j15,
j16 = @j16
where char_id = @id



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO




CREATE PROCEDURE DBO.lin_UpdateMercenary
(
@id INT,
@x INT,
@y INT,
@z INT,
@angle INT,
@hp INT,
@mp INT
)
AS
UPDATE mercenary
SET
x = @x,
y = @y,
z = @z,
angle = @angle,
hp = @hp,
mp = @mp
WHERE id = @id
IF @@ROWCOUNT <> 1
BEGIN
RAISERROR ('Failed to Update Mercenary id = %d.', 16, 1, @id)
END




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO




-- kuooo
CREATE PROCEDURE [DBO].[lin_UpdateNpcBossVariable]
(
    @npc_name 	nvarchar(50),
    @i0		int
)
AS
SET NOCOUNT ON
UPDATE npc_boss
SET
i0 = @i0
where npc_db_name = @npc_name



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_UpdatePledgeInfo    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_UpdatePledgeInfo

INPUT
    @fieldName	nvarchar(50),
    @field_data	INT,
    @char_id	INT
OUTPUT
return
made by
    carrot
date
    2003-06-13
********************************************/
CREATE PROCEDURE [DBO].[lin_UpdatePledgeInfo]
(
@fieldName	nvarchar(50),
@field_data	INT,
@char_id	INT
)
AS
SET NOCOUNT ON

IF @fieldName = N'pledge_dismiss_time' begin update user_data set pledge_dismiss_time = @field_data where char_id =  @char_id end
ELSE IF @fieldName = N'pledge_ousted_time' begin update user_data set pledge_ousted_time = @field_data where char_id =  @char_id end
ELSE IF @fieldName = N'pledge_withdraw_time' begin update user_data set pledge_withdraw_time = @field_data where char_id =  @char_id end
ELSE IF @fieldName = N'surrender_war_id' begin update user_data set surrender_war_id = @field_data where char_id =  @char_id end
ELSE
BEGIN
    RAISERROR ('lin_UpdatePledgeInfo : invalid field [%s]', 16, 1, @fieldName)
    RETURN -1
END



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_UpdateUseTime    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_UpdateUseTime
    update character use time
INPUT
    char_id		int,
    usedtimesec	int
OUTPUT
return
made by
    young
date
    2003-03-26

        add usetime set
********************************************/
CREATE PROCEDURE [DBO].[lin_UpdateUseTime]
(
    @char_id	INT,
    @usedTimeSec	INT
)
AS

SET NOCOUNT ON

UPDATE user_data SET use_time = use_time + @usedTimeSec WHERE char_id = @char_id




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_UpdateUserItem    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_UpdateUserItem

INPUT
    @char_id	INT,
    @item_type	INT,
    @amount	INT,
    @enchant	INT,
    @eroded	INT,
    @bless		INT,
    @ident		INT,
    @wished	INT,
    @warehouse	INT,
    @item_id		INT
OUTPUT
return
made by
    carrot
date
    2002-06-09
********************************************/
create PROCEDURE [DBO].[lin_UpdateUserItem]
(
@char_id	INT,
@item_type	INT,
@amount	INT,
@enchant	INT,
@eroded	INT,
@bless		INT,
@ident		INT,
@wished	INT,
@warehouse	INT,
@item_id		INT
)
AS
SET NOCOUNT ON

UPDATE user_item  set char_id=@char_id, item_type=@item_type, amount=@amount, enchant=@enchant, eroded=@eroded, bless=@bless, ident=@ident, wished=@wished, warehouse=@warehouse WHERE item_id=@item_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_UpdateWarehouseItem    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_UpdateWarehouseItem

INPUT
    @warehouse	INT,
    @amount	INT,
    @item_id		INT
OUTPUT
return
made by
    carrot
date
    2002-06-10
********************************************/
create PROCEDURE [DBO].[lin_UpdateWarehouseItem]
(
    @warehouse	INT,
    @amount	INT,
    @item_id		INT
)
AS
SET NOCOUNT ON

UPDATE user_item SET warehouse=@warehouse,amount=@amount WHERE item_id=@item_id





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_ViewSiegeList    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_ViewSiegeList

INPUT
    @castle_id	int,
    @type	int
OUTPUT
    pledge_id,
    name
return
made by
    carrot
date
    2002-06-16
********************************************/
create PROCEDURE [DBO].[lin_ViewSiegeList]
(
    @castle_id	int,
    @type	int
)
AS
SET NOCOUNT ON

SELECT
    p.pledge_id, p.name
FROM
    pledge p (nolock) ,
    castle_war cw (nolock)
WHERE
    p.pledge_id = cw.pledge_id
    AND cw.castle_id = @castle_id
    AND cw.type = @type







GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_WithdrawAlliance    Script Date: 2003-09-20 오전 11:52:00 ******/
-- lin_WithdrawAlliance
-- by bert
-- return Result(0 if failed)

CREATE PROCEDURE
dbo.lin_WithdrawAlliance (@alliance_id INT, @member_pledge_id INT, @alliance_withdraw_time INT)
AS

SET NOCOUNT ON

DECLARE @result INT

UPDATE pledge
SET alliance_id = 0, alliance_withdraw_time = @alliance_withdraw_time
WHERE pledge_id = @member_pledge_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    SELECT @result = 1
END
ELSE
BEGIN
    SELECT @result = 0
END

SELECT @result




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_WithdrawPledgeMember    Script Date: 2003-09-20 오전 11:51:57 ******/
-- lin_WithdrawPledgeMember
-- by bert

CREATE PROCEDURE
dbo.lin_WithdrawPledgeMember (@pledge_id INT, @member_id INT)
AS

SET NOCOUNT ON

DECLARE @ret INT

BEGIN TRAN

UPDATE user_data
SET pledge_id = 0
WHERE char_id = @member_id
AND pledge_id = @pledge_id

IF @@ERROR = 0 AND @@ROWCOUNT = 1
BEGIN
    -- 추가되는 코드는 여기에
    SELECT @ret = 1
END
ELSE
BEGIN
    SELECT @ret = 0
    GOTO EXIT_TRAN
END

EXIT_TRAN:
IF @ret<> 0
BEGIN
    COMMIT TRAN
END
ELSE
BEGIN
    ROLLBACK TRAN
END
SELECT @ret




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO


/********************************************
lin_WriteCastleTax

INPUT
OUTPUT
return
made by
 carrot
date
 2002-06-10
change carrot 2003-12-22
 add tax_type, residence type to differentiate agit from castle
change carrot 2004-02-29
 add TaxRateToChange
********************************************/
CREATE PROCEDURE [DBO].[lin_WriteCastleTax]
(
 @nIsCastle int,
 @tax_type int,
 @tax_rate  int,
 @to_change  int,
 @residence_id  int
)
AS
SET NOCOUNT ON

IF(@nIsCastle = 1)
BEGIN
 IF (@tax_type = 2)
  UPDATE castle SET tax_child_rate = @tax_rate, tax_child_rate_to_change = @to_change  WHERE id = @residence_id
 ELSE IF (@tax_type = 1)
  UPDATE castle SET tax_rate = @tax_rate, tax_rate_to_change = @to_change  WHERE id = @residence_id
 ELSE
  RAISERROR ('tax type is invalid. castle cannot save type[%d] id and castle id[%d].', 16, 1, @tax_type, @residence_id )
END
ELSE IF(@nIsCastle = 0)
BEGIN
 IF (@tax_type = 2)
BEGIN
  UPDATE agit SET tax_child_rate = @tax_rate, tax_child_rate_to_change = @to_change  WHERE id = @residence_id
END
 ELSE IF (@tax_type = 1)
  UPDATE agit SET tax_rate = @tax_rate, tax_rate_to_change = @to_change WHERE id = @residence_id
 ELSE
  RAISERROR ('tax type is invalid. agit cannot save type[%d] id and agit id[%d].', 16, 1, @tax_type, @residence_id )
END



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_setAgitOwner    Script Date: 2003-09-20 오전 11:52:00 ******/
/********************************************
lin_setAgitOwner
    set Agit Owner
INPUT
    nAgit_id,
    nPledge_id

OUTPUT
return
made by
    carrot
date
    2002-06-12
change
********************************************/
CREATE PROCEDURE [DBO].[lin_setAgitOwner]
(
    @Agit_id		INT,
    @Pledge_id	INT
)
AS

SET NOCOUNT ON

IF NOT exists(SELECT id FROM castle WHERE id = @Agit_id )
    INSERT INTO castle (id, name, pledge_id, type) VALUES (@Agit_id, 'test', @Pledge_id,  2)
ELSE
    UPDATE castle  SET pledge_id = @Pledge_id WHERE id = @Agit_id AND type = 2

IF @@ROWCOUNT > 0
    SELECT 1
ELSE
    SELECT 0




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_setCastleOwner    Script Date: 2003-09-20 오전 11:51:57 ******/
/********************************************
lin_setCastleOwner
    set castle Owner
INPUT
    nCastle_id,
    nPledge_id

OUTPUT
return
made by
    carrot
date
    2002-06-12
change
********************************************/
CREATE PROCEDURE [DBO].[lin_setCastleOwner]
(
    @Castle_id	INT,
    @Pledge_id	INT
)
AS

SET NOCOUNT ON

DECLARE @Castle_idOld INT
DECLARE @nPledgeIdOld INT

SET @Castle_idOld = 0
SET @nPledgeIdOld = 0

SELECT @Castle_idOld = id, @nPledgeIdOld = pledge_id FROM castle WHERE id = @Castle_id

IF @Castle_idOld = 0
    INSERT INTO castle (id, name, pledge_id, type) VALUES (@Castle_id , 'test', @Pledge_id,  1)
ELSE
    UPDATE castle  SET pledge_id = @Pledge_id WHERE id = @Castle_id  AND type = 1

IF @@ROWCOUNT > 0
    SELECT 1
ELSE
    SELECT 0




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





/****** Object:  Stored Procedure dbo.lin_writeBbsTGS    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_writeBbsTGS]
(
    @title NVARCHAR(50),
    @contents NVARCHAR(4000),
    @writer NVARCHAR(50)
)
AS


insert into bbs_tgs (title, contents, writer) values (@title, @contents, @writer)




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.lin_writeBbsall    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE [DBO].[lin_writeBbsall]
(
    @title NVARCHAR(50),
    @contents NVARCHAR(4000),
    @writer NVARCHAR(50)
)
AS
insert into bbs_all (title, contents, writer) values (@title, @contents, @writer)








GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO





/****** Object:  Stored Procedure dbo.spCopyXYZlocForDummy    Script Date: 2003-09-20 오전 11:51:57 ******/
CREATE PROCEDURE DBO.spCopyXYZlocForDummy (@nSrc INT, @nDest INT, @nCount INT)
AS

DECLARE @i INT
DECLARE @xloc INT
DECLARE @yloc INT
DECLARE @zloc INT

SELECT @i = 0

WHILE @i < @nCount
BEGIN

SELECT @xloc = xloc, @yloc = yloc, @zloc = zloc
FROM user_data
WHERE char_name = 'dummy0' + STR(@nSrc + @i, 4)

UPDATE user_data
SET xloc = @xloc, yloc = @yloc, zloc = @zloc
WHERE char_name = 'dummy0' + STR(@nDest + @i, 4)

SELECT @i = @i + 1

END





GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO





create proc sp_dbcc
    @fillfactor int = 90
as

declare @query 	varchar(100)

--1.
exec lin_DeleteNotOwnedItem

--2.
set @query = 'dbcc dbreindex (''user_item'','''',' + cast(@fillfactor as char(2)) + ')'
--print @query
exec (@query)

--3.
dbcc checkdb('lin2world')



GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS OFF
GO



CREATE procedure stat_item_acc
as
begin

truncate table stat_item_cnt
truncate table stat_item_ent
truncate table stat_item_ment
truncate table stat_item_mincnt



--1. 현재 CB 서버에 존재하는 아이템과 그것의 총량
insert into stat_item_cnt
select il.id , count(ui.item_id)  as '아이템 총갯수', sum(isnull(cast (amount as float),0))  as '아이템 총량'
from ItemData as il  left outer join  user_item as ui
on ui.item_type=il.id
group by il.id
order by il.id


---------------------------------------------------------------
--2. 현재 CB 서버에 존재하는 +1 이상의 인챈트된 아이템과 그 총량

insert into stat_item_ent
select item_type , enchant , count(item_type)  as '아이템 총갯수', sum(amount) as '아이템 총량'
from user_item
where enchant >0
group by item_type, enchant
order by item_type, enchant asc


----------------------------------------------------------------
--3. 해당 아이템중 인챈트가 가장 높은 아이템의 unique_id
insert into stat_item_ment
select T2.item_type, T2.item_id, ud.char_name, T2.me,  ud.builder
from
(
select ui.char_id as char_id ,ui.item_type as item_type, ui.item_id as item_id, t.max_enchant as me
from user_item as ui inner join
(
select item_type, max(enchant) as max_enchant
from user_item
where enchant >0
group by item_type

) as T
on ui.item_type = T.item_type and ui.enchant = T.max_enchant
--order by ui.item_type
) as T2 inner join user_data as ud
on T2.char_id = ud.char_id
where ud.account_id<>-1
order by T2.item_type




------------------------------------------------------------------

--4. 1번으로 검색된 것들 중에서 그 총량이 10이하인 아이템의 unique_id

insert into stat_item_mincnt
select  item_type , item_id
from user_item
where item_type in (select item_type
        from user_item
        group by item_type
        having count(item_type)<11)
order by item_type


--====================================================================

truncate table stat_acc_race
truncate table stat_acc_class
truncate table stat_acc_lev
truncate table stat_acc_mlev


--1. 종족별 클래스별 count
insert into stat_acc_race
select race,count(race) from user_data where builder=0 and account_id<>-1 group by race order by race

insert into stat_acc_class
select class,count(class) from user_data where builder=0 and account_id<>-1 group by class order by class

--2. 레벨별 count
insert into stat_acc_lev
select lev,count(lev) from user_data where builder=0 and account_id<>-1 group by lev order by lev

--3. 40레벨이상의 캐릭터명단
insert into stat_acc_mlev
select account_name, char_name, lev, race, class  from user_data where lev>=40 and builder=0 and account_id<>-1 order by lev desc

end




GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO



--Text
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--exec table_info
CREATE proc table_info
as


declare @id	int
declare @type	character(2)
declare	@pages	int
declare @dbname sysname
declare @dbsize dec(15,0)
declare @bytesperpage	dec(15,0)
declare @pagesperMB		dec(15,0)

create table #spt_space
(
    objid		int null,
    rows		int null,
    reserved	dec(15) null,
    data		dec(15) null,
    indexp		dec(15) null,
    unused		dec(15) null
)

set nocount on

-- Create a cursor to loop through the user tables
declare c_tables cursor for
select	id
from	sysobjects
where	xtype = 'U'

open c_tables

fetch next from c_tables
into @id

while @@fetch_status = 0
begin

    /* Code from sp_spaceused */
    insert into #spt_space (objid, reserved)
        select objid = @id, sum(reserved)
            from sysindexes
                where indid in (0, 1, 255)
                    and id = @id

    select @pages = sum(dpages)
            from sysindexes
                where indid < 2
                    and id = @id
    select @pages = @pages + isnull(sum(used), 0)
        from sysindexes
            where indid = 255
                and id = @id
    update #spt_space
        set data = @pages
    where objid = @id


    /* index: sum(used) where indid in (0, 1, 255) - data */
    update #spt_space
        set indexp = (select sum(used)
                from sysindexes
                where indid in (0, 1, 255)
                and id = @id)
                - data
        where objid = @id

    /* unused: sum(reserved) - sum(used) where indid in (0, 1, 255) */
    update #spt_space
        set unused = reserved
                - (select sum(used)
                    from sysindexes
                        where indid in (0, 1, 255)
                        and id = @id)
        where objid = @id

    update #spt_space
        set rows = i.rows
            from sysindexes i
                where i.indid < 2
                and i.id = @id
                and objid = @id

    fetch next from c_tables
    into @id
end

select 	TableName = (select left(name,60) from sysobjects where id = objid),
    Rows = convert(char(11), rows),
    ReservedKB = ltrim(str(reserved * d.low / 1024.,15,0)),
    DataKB = ltrim(str(data * d.low / 1024.,15,0) + ' ' + 'KB'),
    IndexSizeKB = ltrim(str(indexp * d.low / 1024.,15,0) + ' ' + 'KB'),
    UnusedKB = ltrim(str(unused * d.low / 1024.,15,0) + ' ' + 'KB')

from 	#spt_space, master.dbo.spt_values d
where 	d.number = 1
and 	d.type = 'E'
order by reserved desc
drop table #spt_space
close c_tables
deallocate c_tables









GO
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON
GO

