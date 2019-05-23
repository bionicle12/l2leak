if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CheckReportTable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CheckReportTable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetClassAmount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetClassAmount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetItemAmount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetItemAmount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetLevAmount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetLevAmount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeReport]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeReport]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeReportTable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeReportTable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ProcessLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ProcessLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ProcessLog2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ProcessLog2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ProcessLog3]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ProcessLog3]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ProcessLogNew]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ProcessLogNew]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAccountPlayTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAccountPlayTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAsset]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAsset]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAuthStat]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAuthStat]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAuthStatAge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAuthStatAge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAuthStatSex]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAuthStatSex]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAuthed]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAuthed]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPAuthed2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPAuthed2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPBeginQuest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPBeginQuest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCastSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCastSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCastSpoil]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCastSpoil]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCastleTax]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCastleTax]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCastleTaxIncome]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCastleTaxIncome]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCastleTaxTribute]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCastleTaxTribute]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCastleWar]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCastleWar]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPChangeClass]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPChangeClass]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCharPlay]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCharPlay]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCharPlayTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCharPlayTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPClass ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPClass ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPClassDec ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPClassDec ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPClassInc ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPClassInc ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPConcurrent]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPConcurrent]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPCrystalize]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPCrystalize]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPDieDrop]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPDieDrop]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPDieDuration]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPDieDuration]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEarnAdena]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEarnAdena]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEarnSP]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEarnSP]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEnchant ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEnchant ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEnchantFail ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEnchantFail ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEndQuest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEndQuest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEquipItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEquipItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPEquipped ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPEquipped ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPExp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPExp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPGetItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPGetItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPHuntCount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPHuntCount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPItemBuy]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPItemBuy]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPItemDec ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPItemDec ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPItemInc ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPItemInc ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPItemSell]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPItemSell]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPKillPCCount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPKillPCCount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPLearnSkillLev]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPLearnSkillLev]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPLevDec ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPLevDec ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPLevInc ]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPLevInc ]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPLevUp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPLevUp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPLevUp2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPLevUp2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPLoginCount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPLoginCount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCDieLoc]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCDieLoc]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCDieLoc2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCDieLoc2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCDrop]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCDrop]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCDrop2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCDrop2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCDropItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCDropItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCDropLoc]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCDropLoc]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPNPCHunted]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPNPCHunted]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPCDie]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPCDie]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPCDieLoc]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPCDieLoc]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPCDieLoc2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPCDieLoc2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPCKillNPC]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPCKillNPC]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPCKillPC]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPCKillPC]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPlayAge]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPlayAge]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPlaySex]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPlaySex]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPlayStat]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPlayStat]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPlayTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPlayTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPledgeUp]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPledgeUp]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPPrivateStore]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPPrivateStore]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPRecipe]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPRecipe]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPSayCount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPSayCount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPSellPrivate]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPSellPrivate]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPStand]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPStand]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPStopQuest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPStopQuest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPSvrStart]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPSvrStart]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPTradeGet]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPTradeGet]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPTradeGive]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPTradeGive]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPTradeItem]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPTradeItem]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPUseSkill]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPUseSkill]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPWareDeposit]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPWareDeposit]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPWareRetrieve]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPWareRetrieve]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RPWorldSnap]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RPWorldSnap]
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO



/********************************************
lin_CheckReportTable
	do check whether report table is exist or not
INPUT
	@table_type	int,
	@table_name varchar(60)
OUTPUT
	
return
made by
	young
date
	2003-1-24
********************************************/
CREATE PROCEDURE [DBO].[lin_CheckReportTable]
(
	@table_type	int,
	@table_name varchar(60)

)
AS
SET NOCOUNT ON

declare @sql varchar(255)

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_name + ''''

exec (@sql)

if (@@ROWCOUNT = 0)
begin

	exec lin_MakeReportTable @table_type , @table_name	

end

/*
if @table_type = 1 
begin
	-- HUNT_LOG table
	set @sql = 'select * from sysobjects (nolock) where name = ''' + @table_name + ''''

	exec (@sql)
	if (@@ROWCOUNT = 0)
	begin
		set @sql = 'exec lin_MakeReportTable 1, ''' + @table_name + ''''
		exec (@sql)
	end
end
*/


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
lin_GetClassAmount
	get class amount
INPUT
	@class		int,
	@world		int

OUTPUT

return
made by
	young
date
	2003-11-10
********************************************/
CREATE PROCEDURE [DBO].[lin_GetClassAmount]
	@class		int,
	@world		int

AS

SET NOCOUNT ON

declare @dt 	nvarchar(30)
declare @dt2 	nvarchar(30)
declare @ym	nvarchar(10)
declare @ym2 	nvarchar(10)
declare @sql nvarchar(3000)

set @dt = cast ( getdate() as nvarchar)
set @dt2 = cast ( dateadd ( mm, -1, getdate() ) as nvarchar )

set @ym = substring( @dt , 7, 4) + '_' + substring( @dt , 1, 2)
set @ym2 = substring( @dt2 , 7, 4) + '_' + substring( @dt2 , 1, 2)

set @sql = ' declare @nbase int  '
	+ ' declare @ndec int  '
	+ ' declare @ninc int  '
	+ ' declare @ndec2 int  '
	+ ' declare @ninc2 int  '
	+ ' declare @ndate int '
	+ ' set @nbase = 0 '
	+ ' set @ndec = 0 '
	+ ' set @ninc = 0 '
	+ ' set @ndec2 = 0 '
	+ ' set @ninc2 = 0 '
	+ ' set @ndate = 0 '
	+ ' select @ndate = log_date, @nbase = namount from  '
	+ ' ( '
	+ ' select top 1 log_date,  namount=sum(class_count) from lin2report.dbo.R' +  @ym + '_SNAPCLASS_' + cast ( @world as nvarchar) + ' (nolock) '
	+ ' where class  =  ' + cast ( @class as nvarchar)
	+ ' group by log_date  '
	+ ' order by log_date desc '
	+ ' ) as R1 '
	+ ' if @ndate > 0 '
	+ ' begin '
		+ ' select  @ndec = isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_CLASSDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where class = ' + cast ( @class as nvarchar) + ' and log_date >= @ndate '
		+ ' select @ninc =  isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_CLASSINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where class = ' + cast ( @class as nvarchar) + ' and log_date >= @ndate '
		+ ' select @nbase, @ninc + @ndec, @nbase + @ninc + @ndec '
	+ ' end else begin '
		+ ' select @ndate = log_date, @nbase = namount from  '
		+ ' ( '
		+ ' select top 1 log_date,  namount= isnull ( sum(class_count) , 0) from lin2report.dbo.R' +  @ym2 + '_SNAPCLASS_' + cast ( @world as nvarchar) + ' (nolock) '
		+ ' where class =  ' + cast ( @class as nvarchar)
		+ ' group by log_date  '
		+ ' order by log_date desc '
		+ ' ) as R1 '
		+ ' select  @ndec = isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym2 + '_CLASSDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where class = ' + cast ( @class as nvarchar) + ' and log_date >= @ndate '
		+ ' select @ninc = isnull ( sum(amount) , 0) from lin2report.dbo.R' + @ym2 + '_CLASSINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where class = ' + cast ( @class as nvarchar) + ' and log_date >= @ndate '
		+ ' select  @ndec2 = isnull ( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_CLASSDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where class = ' + cast ( @class as nvarchar)  
		+ ' select @ninc2 = isnull (  sum(amount) , 0) from lin2report.dbo.R' + @ym + '_CLASSINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where class = ' + cast ( @class as nvarchar)  
		+ ' select @nbase, @ninc + @ndec, @nbase + @ninc + @ndec  + @ninc2 + @ndec2 '
	+ ' end '

exec (@sql)

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
lin_GetItemAmount
	get stackable item amount
INPUT
	@item_type	int,
	@world		int

OUTPUT

return
made by
	young
date
	2003-6-24
********************************************/
CREATE PROCEDURE [DBO].[lin_GetItemAmount]
	@item_type	int,
	@world		int

AS

SET NOCOUNT ON

declare @dt 	nvarchar(30)
declare @dt2 	nvarchar(30)
declare @ym	nvarchar(10)
declare @ym2 	nvarchar(10)
declare @sql nvarchar(3000)

set @dt = cast ( getdate() as nvarchar)
set @dt2 = cast ( dateadd ( mm, -1, getdate() ) as nvarchar )

set @ym = substring( @dt , 7, 4) + '_' + substring( @dt , 1, 2)
set @ym2 = substring( @dt2 , 7, 4) + '_' + substring( @dt2 , 1, 2)

set @sql = ' declare @nbase money '
	+ ' declare @ndec money '
	+ ' declare @ninc money '
	+ ' declare @ndec2 money '
	+ ' declare @ninc2 money '
	+ ' declare @ndate int '
	+ ' set @nbase = 0 '
	+ ' set @ndec = 0 '
	+ ' set @ninc = 0 '
	+ ' set @ndec2 = 0 '
	+ ' set @ninc2 = 0 '
	+ ' set @ndate = 0 '
	+ ' select @ndate = log_date, @nbase = namount from  '
	+ ' ( '
	+ ' select top 1 log_date,  namount=sum(amount) from lin2report.dbo.R' +  @ym + '_SNAPITEM_' + cast ( @world as nvarchar) + ' (nolock) '
	+ ' where item_type =  ' + cast ( @item_type as nvarchar)
	+ ' group by log_date  '
	+ ' order by log_date desc '
	+ ' ) as R1 '
	+ ' if @ndate > 0 '
	+ ' begin '
		+ ' select  @ndec = isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_ITEMDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where item_id = ' + cast ( @item_type as nvarchar) + ' and log_date >= @ndate '
		+ ' select @ninc =  isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_ITEMINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where item_id = ' + cast ( @item_type as nvarchar) + ' and log_date >= @ndate '
		+ ' select @nbase, @ninc + @ndec, @nbase + @ninc + @ndec '
	+ ' end else begin '
		+ ' select @ndate = log_date, @nbase = namount from  '
		+ ' ( '
		+ ' select top 1 log_date,  namount= isnull ( sum(amount) , 0) from lin2report.dbo.R' +  @ym2 + '_SNAPITEM_' + cast ( @world as nvarchar) + ' (nolock) '
		+ ' where item_type =  ' + cast ( @item_type as nvarchar)
		+ ' group by log_date  '
		+ ' order by log_date desc '
		+ ' ) as R1 '
		+ ' select  @ndec = isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym2 + '_ITEMDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where item_id = ' + cast ( @item_type as nvarchar) + ' and log_date >= @ndate '
		+ ' select @ninc = isnull ( sum(amount) , 0) from lin2report.dbo.R' + @ym2 + '_ITEMINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where item_id = ' + cast ( @item_type as nvarchar) + ' and log_date >= @ndate '
		+ ' select  @ndec2 = isnull ( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_ITEMDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where item_id = ' + cast ( @item_type as nvarchar)  
		+ ' select @ninc2 = isnull (  sum(amount) , 0) from lin2report.dbo.R' + @ym + '_ITEMINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where item_id = ' + cast ( @item_type as nvarchar)  
		+ ' select @nbase, @ninc + @ndec, @nbase + @ninc + @ndec  + @ninc2 + @ndec2 '
	+ ' end '

exec (@sql)

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
lin_GetLevAmount
	get level amount
INPUT
	@lev		int,
	@world		int

OUTPUT

return
made by
	young
date
	2003-11-10
********************************************/
CREATE PROCEDURE [DBO].[lin_GetLevAmount]
	@lev		int,
	@world		int

AS

SET NOCOUNT ON

declare @dt 	nvarchar(30)
declare @dt2 	nvarchar(30)
declare @ym	nvarchar(10)
declare @ym2 	nvarchar(10)
declare @sql nvarchar(3000)

set @dt = cast ( getdate() as nvarchar)
set @dt2 = cast ( dateadd ( mm, -1, getdate() ) as nvarchar )

set @ym = substring( @dt , 7, 4) + '_' + substring( @dt , 1, 2)
set @ym2 = substring( @dt2 , 7, 4) + '_' + substring( @dt2 , 1, 2)

set @sql = ' declare @nbase int  '
	+ ' declare @ndec int  '
	+ ' declare @ninc int  '
	+ ' declare @ndec2 int  '
	+ ' declare @ninc2 int  '
	+ ' declare @ndate int '
	+ ' set @nbase = 0 '
	+ ' set @ndec = 0 '
	+ ' set @ninc = 0 '
	+ ' set @ndec2 = 0 '
	+ ' set @ninc2 = 0 '
	+ ' set @ndate = 0 '
	+ ' select @ndate = log_date, @nbase = namount from  '
	+ ' ( '
	+ ' select top 1 log_date,  namount=sum(lev_count) from lin2report.dbo.R' +  @ym + '_SNAPLEV_' + cast ( @world as nvarchar) + ' (nolock) '
	+ ' where lev  =  ' + cast ( @lev as nvarchar)
	+ ' group by log_date  '
	+ ' order by log_date desc '
	+ ' ) as R1 '
	+ ' if @ndate > 0 '
	+ ' begin '
		+ ' select  @ndec = isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_LEVDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where lev = ' + cast ( @lev as nvarchar) + ' and log_date >= @ndate '
		+ ' select @ninc =  isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_LEVINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where lev = ' + cast ( @lev as nvarchar) + ' and log_date >= @ndate '
		+ ' select @nbase, @ninc + @ndec, @nbase + @ninc + @ndec '
	+ ' end else begin '
		+ ' select @ndate = log_date, @nbase = namount from  '
		+ ' ( '
		+ ' select top 1 log_date,  namount= isnull ( sum(lev_count) , 0) from lin2report.dbo.R' +  @ym2 + '_SNAPLEV_' + cast ( @world as nvarchar) + ' (nolock) '
		+ ' where lev =  ' + cast ( @lev as nvarchar)
		+ ' group by log_date  '
		+ ' order by log_date desc '
		+ ' ) as R1 '
		+ ' select  @ndec = isnull( sum(amount) , 0) from lin2report.dbo.R' + @ym2 + '_LEVDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where lev = ' + cast ( @lev as nvarchar) + ' and log_date >= @ndate '
		+ ' select @ninc = isnull ( sum(amount) , 0) from lin2report.dbo.R' + @ym2 + '_LEVINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where lev = ' + cast ( @lev as nvarchar) + ' and log_date >= @ndate '
		+ ' select  @ndec2 = isnull ( sum(amount) , 0) from lin2report.dbo.R' + @ym + '_LEVDEC_' + cast ( @world as nvarchar)  + ' (nolock) '
		+ ' where lev = ' + cast ( @lev as nvarchar)  
		+ ' select @ninc2 = isnull (  sum(amount) , 0) from lin2report.dbo.R' + @ym + '_LEVINC_' + cast ( @world as nvarchar) + '  (nolock) '
		+ ' where lev = ' + cast ( @lev as nvarchar)  
		+ ' select @nbase, @ninc + @ndec, @nbase + @ninc + @ndec  + @ninc2 + @ndec2 '
	+ ' end '

exec (@sql)

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
lin_MakeReport
	do make report
INPUT
	@report_date	datetime,
	@report_world	int
OUTPUT
	
return
made by
	young
date
	2003-1-24
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeReport]
/*
	@report_date datetime ,
	@report_world int = 1
*/
AS
SET NOCOUNT ON

	declare @report_date datetime
	declare @report_world tinyint

	SET @report_date = dateadd(d, -1, getdate())
	SET @report_world = 1


	exec lin_ProcessLog @report_date, @report_world	
/*
if @report_date is null
begin
	set @report_date = getdate()
	set @report_date = dateadd(d, -1, getdate())
end


DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)

set @nyear = datepart(yyyy, @report_date)
set @nmonth = datepart(mm, @report_date)
set @nday = datepart(dd, @report_date)

set @stryear = cast(@nyear as varchar)
if @nmonth < 10
	set @strmonth = '0' + cast(@nmonth as varchar)
else
	set @strmonth = cast (@nmonth as varchar)

if @nday < 10
	set @strday = '0' + cast(@nday as varchar)
else
	set @strday = cast (@nday as varchar)	

set @str_report = @stryear + '/' + @strmonth + '/' + @strday

------------- now.. we have year, month, day string
DECLARE @table_from varchar(60)
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data_1 '

DECLARE @table_name varchar(60)
set @table_name = 'R' + @stryear + '_' + @strmonth + '_' + @strday + '_HUNT_LOG_' + cast(@report_world as varchar)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
select 'check HUNT_LOG table'
exec lin_CheckReportTable 1, @table_name
-- insert statistics
DECLARE @strsql		varchar(512)

-- 레벨별 사냥하는 위치 (map별)
set @strsql = 'insert into ' + RTRIM(@table_name) + ' (log_id,   log_date, level, xloc, yloc, zloc, hunt_count) ( ' 
	+ ' select 1,   ''' + RTRIM(@str_report) + ''', etc_num3 , FLOOR( location_x  / 32768.0 ), FLOOR(location_y / 32768.0 ) , 0, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1104 group by etc_num3 , FLOOR( location_x  / 32768.0 ), FLOOR(location_y / 32768.0 )   ) '

exec (@strsql )

-- 레벨별 사냥하는 위치 (sector 별)
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_id,  log_date, level, xloc, yloc, zloc, hunt_count) ( ' 
	+ ' select  2,  ''' + RTRIM(@str_report) + ''', etc_num3 , FLOOR( location_x  / 256.0 ), FLOOR(location_y / 256.0 ) , 0, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1104 group by etc_num3 , FLOOR( location_x  / 256.0 ), FLOOR(location_y / 256.0 )   ) '

exec (@strsql )

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-- 레벨별 사냥하는 NPC 숫자
select 'check HUNT_LOG2 table'
set @table_name = 'R' + @stryear + '_' + @strmonth + '_' + @strday + '_HUNT2_LOG_' + cast(@report_world as varchar)
exec lin_CheckReportTable 2, @table_name
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_id,  log_date, level, npc_type, hunt_count) ( ' 
	+ ' select  1,  ''' + RTRIM(@str_report) + ''', etc_num3 , target_account, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1104 group by etc_num3 , target_account   ) '
exec (@strsql )

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
select 'check PCDIE_LOG  table'
-- race 별 죽은 PC숫자
set @table_name = 'R' + @stryear + '_' + @strmonth + '_' + @strday + '_PCDIE_LOG_' + cast(@report_world as varchar)
exec lin_CheckReportTable 3, @table_name
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_id, log_date,  stats_type, die_count) ( ' 
	+ ' select  1,  ''' + RTRIM(@str_report) + ''', etc_num1, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1101 group by etc_num1 ) '
exec (@strsql )

-- class 별 죽은 PC 숫자
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_id, log_date,  stats_type, die_count) ( ' 
	+ ' select  2,  ''' + RTRIM(@str_report) + ''', etc_num3, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1101 group by etc_num3 ) '
exec (@strsql )

-- 죽기전 level 별 죽은 PC 숫자
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_id,  log_date, stats_type, die_count) ( ' 
	+ ' select  3,  ''' + RTRIM(@str_report) + ''', etc_num4, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1101 group by etc_num4 ) '
exec (@strsql )

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
select 'check COUNT_LOG  table'
set @table_name = 'R' + @stryear + '_' + @strmonth + '_' + @strday + '_COUNT_LOG_' + cast(@report_world as varchar)
exec lin_CheckReportTable 4, @table_name

-- race 별 로그인한 캐릭 숫자
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_count ) ( ' 
	+ ' select  ''' + RTRIM(@str_report) + ''', 1, etc_num1, count(distinct actor) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 803 group by etc_num1 ) '
exec (@strsql )
-- sex 별 로그인한 캐릭 숫자
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_count ) ( ' 
	+ ' select  ''' + RTRIM(@str_report) + ''', 2, etc_num2, count(distinct actor) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 803 group by etc_num2 ) '
exec (@strsql )
-- class 별 로그인한 캐릭 숫자
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_count ) ( ' 
	+ ' select  ''' + RTRIM(@str_report) + ''', 3, etc_num3, count(distinct actor) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 803 group by etc_num3 ) '
exec (@strsql )
-- level 별 로그인한 캐릭 숫자
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_count ) ( ' 
	+ ' select  ''' + RTRIM(@str_report) + ''', 4, etc_num4, count(distinct actor) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 803 group by etc_num4 ) '
exec (@strsql )

-- race 별 사냥한 총 NPC수
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_subval,  log_count ) ( ' 
	+ ' select ''' + RTRIM(@str_report) + ''', 5, etc_num1, target_account, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1112 group by etc_num1, target_account  ) '
exec (@strsql )
-- sex 별 사냥한 총 NPC수
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_subval,  log_count ) ( ' 
	+ ' select ''' + RTRIM(@str_report) + ''', 6, etc_num2, target_account, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1112 group by etc_num2, target_account  ) '
exec (@strsql )
-- class 별 사냥한 총 NPC수
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_subval,  log_count ) ( ' 
	+ ' select ''' + RTRIM(@str_report) + ''', 7, etc_num3, target_account, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1112 group by etc_num3, target_account ) '
exec (@strsql )
-- level 별 사냥한 총 NPC수
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_subval, log_count ) ( ' 
	+ ' select  ''' + RTRIM(@str_report) + ''', 8, etc_num4, target_account, count(*) '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 1112 group by etc_num4, target_account  ) '
exec (@strsql )


-- race 별 스킬을 익힌 평균 레벨
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_subval, log_count ) ( ' 
	+ ' select ''' + RTRIM(@str_report) + ''', 9, etc_num5, etc_num1, sum(etc_num4) / count(*)  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 401 group by etc_num5, etc_num1 ) '
exec (@strsql )
-- class 별 스킬을 익힌 평균 레벨
set @strsql = 'insert into ' + RTRIM(@table_name) + ' ( log_date,  count_id, log_val, log_subval, log_count ) ( ' 
	+ ' select ''' + RTRIM(@str_report) + ''', 10, etc_num5, etc_num3, sum(etc_num4) / count(*)  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 401 group by etc_num5, etc_num3 ) '
exec (@strsql )

*/


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
lin_MakeReportTable
	do make report table
INPUT
	@table_type int
	@table_name varchar(60)
OUTPUT
	
return
made by
	young
date
	2003-1-24
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeReportTable]
(
	@table_type int,
	@table_name varchar(60)
)
AS
SET NOCOUNT ON

declare @sql varchar(1024)

if @table_type = 1 
begin
	set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
		+ ' log_id	int, '
		+ ' log_date	datetime, '
		+ ' level	int, '
		+ ' xloc	int, '
		+ ' yloc	int, '
		+ ' zloc	int, '
		+ ' hunt_count	int '
		+ ' ) '

	exec (@sql)
end

if @table_type = 2
begin
	set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
		+ ' log_id	int, '
		+ ' log_date	datetime, '
		+ ' level	int, '
		+ ' npc_type int, '
		+ ' hunt_count	int '
		+ ' ) '

	exec (@sql)
end 

if @table_type = 3
begin
	set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
		+ ' log_id	int, '
		+ ' log_date	datetime, '
		+ ' stats_type int, '
		+ ' die_count	int '
		+ ' ) '

	exec (@sql)
end

if @table_type = 4
begin
	set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
		+ ' log_date	datetime, '
		+ 'count_id	int, '
		+ 'log_val	int, '
		+ 'log_subval	int,'
		+ 'log_count 	int'
		+ ' ) '

	exec (@sql)
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
lin_ProcessLog
	do make report table
INPUT
	@report_date	datetime,
	@report_world	int
OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_ProcessLog]

	@report_date datetime ,
	@report_world int = 1
AS
SET NOCOUNT ON

if @report_date is null
begin
	set @report_date = getdate()
	set @report_date = dateadd(d, -1, getdate())
end

DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)
DECLARE @logdate int

set @nyear = datepart(yyyy, @report_date)
set @nmonth = datepart(mm, @report_date)
set @nday = datepart(dd, @report_date)

set @stryear = cast(@nyear as varchar)
if @nmonth < 10
	set @strmonth = '0' + cast(@nmonth as varchar)
else
	set @strmonth = cast (@nmonth as varchar)

if @nday < 10
	set @strday = '0' + cast(@nday as varchar)
else
	set @strday = cast (@nday as varchar)	

set @str_report = @stryear + '/' + @strmonth + '/' + @strday
set @logdate = cast(@stryear + @strmonth + @strday as int)

------------- now.. we have year, month, day string
DECLARE @table_from varchar(60)
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data_' + cast ( @report_world as varchar)

DECLARE @table_to varchar(60)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
-- make LOGINCOUNT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LOGINCOUNT_' + cast(@report_world as varchar)
exec lin_RPLoginCount @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make HUNTCOUNT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_HUNTCOUNT_' + cast(@report_world as varchar)
exec lin_RPHuntCount @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make LEARNSKILLLEV report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEARNSKILLLEV_' + cast(@report_world as varchar)
exec lin_RPLearnSkillLev @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make CHANGECLASS report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CHANGECLASS_' + cast(@report_world as varchar)
exec lin_RPChangeClass @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make PLAYTIME report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLAYTIME_' + cast(@report_world as varchar)
exec lin_RPPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make NPCHUNTED report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCHUNTED_' + cast(@report_world as varchar)
exec lin_RPNPCHunted @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ITEMBUY report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMBUY_' + cast(@report_world as varchar)
exec lin_RPItemBuy @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ITEMSELL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMSELL_' + cast(@report_world as varchar)
exec lin_RPItemSell @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make EARNADENA report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EARNADENA_' + cast(@report_world as varchar)
exec lin_RPEarnAdena @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make EARNSP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EARNSP_' + cast(@report_world as varchar)
exec lin_RPEarnSP @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make NPCDROP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROP_' + cast(@report_world as varchar)
exec lin_RPNPCDrop @table_from, @table_to, @logdatewaitfor delay '0:0:10'

-- make NPCDROP2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROP2_' + cast(@report_world as varchar)
exec lin_RPNPCDrop2 @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make LEVUP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEVUP_' + cast(@report_world as varchar)
exec lin_RPLevUp @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make PCDIE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIE_' + cast(@report_world as varchar)
exec lin_RPPCDie @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make PCDIELOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIELOC_' + cast(@report_world as varchar)
exec lin_RPPCDieLoc @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make NPCDIELOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDIELOC_' + cast(@report_world as varchar)
exec lin_RPNPCDieLoc @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make PCDIELOC2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIELOC2_' + cast(@report_world as varchar)
exec lin_RPPCDieLoc2 @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make NPCDIELOC2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDIELOC2_' + cast(@report_world as varchar)
exec lin_RPNPCDieLoc2 @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make WAREDEPOSIT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_WAREDEPOSIT_' + cast(@report_world as varchar)
exec lin_RPWareDeposit @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make WARERETRIEVE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_WARERETRIEVE_' + cast(@report_world as varchar)
exec lin_RPWareRetrieve @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make TRADEGIVE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEGIVE_' + cast(@report_world as varchar)
exec lin_RPTradeGive @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make TRADEGET  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEGET_' + cast(@report_world as varchar)
exec lin_RPTradeGet  @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make USESKILL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_USESKILL_' + cast(@report_world as varchar)
exec lin_RPUseSkill @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ACCOUNTPLAYTIME  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ACCOUNTPLAYTIME_' + cast(@report_world as varchar)
exec lin_RPAccountPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make CASTSKILL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CASTSKILL_' + cast(@report_world as varchar)
exec lin_RPCastSkill @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make PCKILLNPC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCKILLNPC_' + cast(@report_world as varchar)
exec lin_RPPCKillNPC @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make NPCDROPLOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROPLOC_' + cast(@report_world as varchar)
exec lin_RPNPCDropLoc @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make EQUIPITEM report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EQUIPITEM_' + cast(@report_world as varchar)
exec lin_RPEquipItem @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make STAND report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_STAND_' + cast(@report_world as varchar)
exec lin_RPStand @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make DIEDURATION report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_DIEDURATION_' + cast(@report_world as varchar)
exec lin_RPDieDuration @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make CONCURRENT  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CONCURRENT_' + cast(@report_world as varchar)
exec lin_RPConcurrent @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make CLASS report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CLASS_' + cast(@report_world as varchar)
exec lin_RPClass @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ENCHANT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENCHANT_' + cast(@report_world as varchar)
exec lin_RPEnchant @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ENCHANTFAIL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENCHANTFAIL_' + cast(@report_world as varchar)
exec lin_RPEnchantFail @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make CRYSTALIZE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CRYSTALIZE_' + cast(@report_world as varchar)
exec lin_RPCrystalize @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make SELLPRIVATE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_SELLPRIVATE_' + cast(@report_world as varchar)
exec lin_RPSellPrivate @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ITEMINC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMINC_' + cast(@report_world as varchar)
exec lin_RPItemInc @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ITEMDEC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMDEC_' + cast(@report_world as varchar)
exec lin_RPItemDec @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make BEGINQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_BEGINQUEST_' + cast(@report_world as varchar)
exec lin_RPBeginQuest @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make ENDQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENDQUEST_' + cast(@report_world as varchar)
exec lin_RPEndQuest @table_from, @table_to, @logdate
waitfor delay '0:0:10'

-- make STOPQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_STOPQUEST_' + cast(@report_world as varchar)
exec lin_RPStopQuest @table_from, @table_to, @logdate

*/

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
lin_ProcessLog2
	do make report table
INPUT
	@report_date	datetime,
	@report_world	int
OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_ProcessLog2]

	@report_date datetime ,
	@report_world int = 1
AS


SET NOCOUNT ON

if @report_date is null
begin
	set @report_date = getdate()
	set @report_date = dateadd(d, -1, getdate())
end

DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)
DECLARE @logdate int

set @nyear = datepart(yyyy, @report_date)
set @nmonth = datepart(mm, @report_date)
set @nday = datepart(dd, @report_date)

set @stryear = cast(@nyear as varchar)
if @nmonth < 10
	set @strmonth = '0' + cast(@nmonth as varchar)
else
	set @strmonth = cast (@nmonth as varchar)

if @nday < 10
	set @strday = '0' + cast(@nday as varchar)
else
	set @strday = cast (@nday as varchar)	

set @str_report = @stryear + '/' + @strmonth + '/' + @strday
set @logdate = cast(@stryear + @strmonth + @strday as int)

------------- now.. we have year, month, day string
DECLARE @table_from varchar(60)
DECLARE @table_to varchar(60)
declare @sql varchar(512)


--------------------------- using view
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

-- make LOGINCOUNT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LOGINCOUNT_' + cast(@report_world as varchar)
exec lin_RPLoginCount @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make HUNTCOUNT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_HUNTCOUNT_' + cast(@report_world as varchar)
exec lin_RPHuntCount @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make LEARNSKILLLEV report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEARNSKILLLEV_' + cast(@report_world as varchar)
exec lin_RPLearnSkillLev @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CHANGECLASS report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CHANGECLASS_' + cast(@report_world as varchar)
exec lin_RPChangeClass @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PLAYTIME report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLAYTIME_' + cast(@report_world as varchar)
exec lin_RPPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCHUNTED report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCHUNTED_' + cast(@report_world as varchar)
exec lin_RPNPCHunted @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make EARNSP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EARNSP_' + cast(@report_world as varchar)
exec lin_RPEarnSP @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make LEVUP report
-- set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEVUP_' + cast(@report_world as varchar)
-- exec lin_RPLevUp @table_from, @table_to, @logdate
-- waitfor delay '0:0:6'

-- make PCDIE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIE_' + cast(@report_world as varchar)
exec lin_RPPCDie @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCDIELOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIELOC_' + cast(@report_world as varchar)
exec lin_RPPCDieLoc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDIELOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDIELOC_' + cast(@report_world as varchar)
exec lin_RPNPCDieLoc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCDIELOC2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIELOC2_' + cast(@report_world as varchar)
exec lin_RPPCDieLoc2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDIELOC2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDIELOC2_' + cast(@report_world as varchar)
exec lin_RPNPCDieLoc2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make USESKILL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_USESKILL_' + cast(@report_world as varchar)
exec lin_RPUseSkill @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ACCOUNTPLAYTIME  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ACCOUNTPLAYTIME_' + cast(@report_world as varchar)
exec lin_RPAccountPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CASTSKILL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CASTSKILL_' + cast(@report_world as varchar)
exec lin_RPCastSkill @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCKILLNPC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCKILLNPC_' + cast(@report_world as varchar)
exec lin_RPPCKillNPC @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make STAND report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_STAND_' + cast(@report_world as varchar)
exec lin_RPStand @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make DIEDURATION report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_DIEDURATION_' + cast(@report_world as varchar)
exec lin_RPDieDuration @table_from, @table_to, @logdatewaitfor delay '0:0:6'

-- make CONCURRENT  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CONCURRENT_' + cast(@report_world as varchar)
exec lin_RPConcurrent @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CLASS report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CLASS_' + cast(@report_world as varchar)
exec lin_RPClass @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make BEGINQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_BEGINQUEST_' + cast(@report_world as varchar)
exec lin_RPBeginQuest @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ENDQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENDQUEST_' + cast(@report_world as varchar)
exec lin_RPEndQuest @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make STOPQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_STOPQUEST_' + cast(@report_world as varchar)
exec lin_RPStopQuest @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make SAYCOUNT  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_SAYCOUNT_' + cast(@report_world as varchar)
exec lin_RPSayCount @table_from, @table_to, @logdate
waitfor delay '0:0:6'


---------------------------------- item report part

-- make ITEMBUY report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMBUY_' + cast(@report_world as varchar)
exec lin_RPItemBuy @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ITEMSELL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMSELL_' + cast(@report_world as varchar)
exec lin_RPItemSell @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make EARNADENA report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EARNADENA_' + cast(@report_world as varchar)
exec lin_RPEarnAdena @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDROP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROP_' + cast(@report_world as varchar)
exec lin_RPNPCDrop @table_from, @table_to, @logdatewaitfor delay '0:0:6'

-- make NPCDROP2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROP2_' + cast(@report_world as varchar)
exec lin_RPNPCDrop2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make WAREDEPOSIT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_WAREDEPOSIT_' + cast(@report_world as varchar)
exec lin_RPWareDeposit @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make WARERETRIEVE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_WARERETRIEVE_' + cast(@report_world as varchar)
exec lin_RPWareRetrieve @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TRADEGIVE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEGIVE_' + cast(@report_world as varchar)
exec lin_RPTradeGive @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TRADEGET  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEGET_' + cast(@report_world as varchar)
exec lin_RPTradeGet  @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make NPCDROPLOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROPLOC_' + cast(@report_world as varchar)
exec lin_RPNPCDropLoc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make EQUIPITEM report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EQUIPITEM_' + cast(@report_world as varchar)
exec lin_RPEquipItem @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ENCHANT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENCHANT_' + cast(@report_world as varchar)
exec lin_RPEnchant @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ENCHANTFAIL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENCHANTFAIL_' + cast(@report_world as varchar)
exec lin_RPEnchantFail @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CRYSTALIZE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CRYSTALIZE_' + cast(@report_world as varchar)
exec lin_RPCrystalize @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make SELLPRIVATE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_SELLPRIVATE_' + cast(@report_world as varchar)
exec lin_RPSellPrivate @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make ITEMINC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMINC_' + cast(@report_world as varchar)
exec lin_RPItemInc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ITEMDEC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMDEC_' + cast(@report_world as varchar)
exec lin_RPItemDec @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make DIEDROP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_DIEDROP_' + cast(@report_world as varchar)
exec lin_RPDieDrop @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDROPITEM report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROPITEM_' + cast(@report_world as varchar)
exec lin_RPNPCDropItem @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make RECIPE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_RECIPE_' + cast(@report_world as varchar)
exec lin_RPRecipe @table_from, @table_to, @logdate
waitfor delay '0:0:6'

----------------------------------------- new reports
-- make CHARPLAYTIME report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CHARPLAYTIME_' + cast(@report_world as varchar)
exec lin_RPCharPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make EXP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EXP_' + cast(@report_world as varchar)
exec lin_RPExp @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make GETITEM  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_GETITEM_' + cast(@report_world as varchar)
exec lin_RPGetItem @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ASSET  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ASSET_' + cast(@report_world as varchar)
exec lin_RPAsset @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make EQUIPPED  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EQUIPPED_' + cast(@report_world as varchar)
exec lin_RPEquipped @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TRADEITEM  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEITEM_' + cast(@report_world as varchar)
exec lin_RPTradeItem @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make LEVINC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEVINC_' + cast(@report_world as varchar)
exec lin_RPLevInc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make LEVDEC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEVDEC_' + cast(@report_world as varchar)
exec lin_RPLevDec @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CLASSINC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CLASSINC_' + cast(@report_world as varchar)
exec lin_RPClassInc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CLASSDEC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CLASSDEC_' + cast(@report_world as varchar)
exec lin_RPClassDec @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PRIVATESTORE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PRIVATESTORE_' + cast(@report_world as varchar)
exec lin_RPPrivateStore @table_from, @table_to, @logdate

-- make SVRSTART  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_realtime_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_SVRSTART_' + cast(@report_world as varchar)
exec lin_RPSvrStart @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CASTSPOIL  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CASTSPOIL_' + cast(@report_world as varchar)
exec lin_RPCastSpoil @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CASTLEWAR report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CASTLEWAR_' + cast(@report_world as varchar)
exec lin_RPCastleWar @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TAXINCOME  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TAXINCOME_' + cast(@report_world as varchar)
exec lin_RPCastleTaxIncome @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TAXTRIBUTE report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TAXTRIBUTE_' + cast(@report_world as varchar)
exec lin_RPCastleTaxTribute @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make LEVUP2  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEVUP2_' + cast(@report_world as varchar)
exec lin_RPLevUp2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PLEDGEUP  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLEDGEUP_' + cast(@report_world as varchar)
exec lin_RPPledgeUp @table_from, @table_to, @logdate

waitfor delay '0:0:6'

-- make PLAYSTAT  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLAYSTAT_' + cast(@report_world as varchar)
exec lin_RPPlayStat @table_from, @table_to, @logdate

waitfor delay '0:0:6'

-- make PCKILLPC  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCKILLPC_' + cast(@report_world as varchar)
exec lin_RPPCKillPC @table_from, @table_to, @logdate

waitfor delay '0:0:6'

-- make TAX  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TAX_' + cast(@report_world as varchar)
exec lin_RPCastleTax @table_from, @table_to, @logdate

waitfor delay '0:0:6'

-- make CHARPLAY report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CHARPLAY_' + cast(@report_world as varchar)
exec lin_RPCharPlay @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make KILLPCCOUNT  report
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_KILLPCCOUNT_' + cast(@report_world as varchar)
exec lin_RPKillPCCount  @table_from, @table_to, @logdate
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
lin_ProcessLog3
	do make report table
INPUT
	@report_date	datetime,
	@report_world	int
OUTPUT
	
return
made by
	young
date
	2003-8-5
********************************************/
CREATE PROCEDURE [DBO].[lin_ProcessLog3]

	@report_date datetime ,
	@report_world int = 1
AS
SET NOCOUNT ON

if @report_date is null
begin
	set @report_date = getdate()
	set @report_date = dateadd(d, -1, getdate())
end

DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)
DECLARE @logdate int

set @nyear = datepart(yyyy, @report_date)
set @nmonth = datepart(mm, @report_date)
set @nday = datepart(dd, @report_date)

set @stryear = cast(@nyear as varchar)
if @nmonth < 10
	set @strmonth = '0' + cast(@nmonth as varchar)
else
	set @strmonth = cast (@nmonth as varchar)

if @nday < 10
	set @strday = '0' + cast(@nday as varchar)
else
	set @strday = cast (@nday as varchar)	

set @str_report = @stryear + '/' + @strmonth + '/' + @strday
set @logdate = cast(@stryear + @strmonth + @strday as int)

------------- now.. we have year, month, day string
DECLARE @table_from varchar(60)
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data_' + cast ( @report_world as varchar)

DECLARE @table_to varchar(60)



declare @sql varchar(512)



--------------------------- using view
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------


-- make AUTHED report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_AUTHED_' + cast(@report_world as varchar)
exec lin_RPAuthed @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make AUTHED2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_AUTHED2_' + cast(@report_world as varchar)
exec lin_RPAuthed2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PLAYAGE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLAYAGE_' + cast(@report_world as varchar)
exec lin_RPPlayAge @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PLAYSEX report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLAYSEX_' + cast(@report_world as varchar)
exec lin_RPPlaySex @table_from, @table_to, @logdate

-- make AUTHSTAT  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_AUTHSTAT_' + cast(@report_world as varchar)
exec lin_RPAuthStat @table_from, @table_to, @logdate

-- make AUTHSTATAGE  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_AUTHSTATAGE_' + cast(@report_world as varchar)
exec lin_RPAuthStatAge @table_from, @table_to, @logdate

-- make AUTHSTATSEX  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_AUTHSTATSEX_' + cast(@report_world as varchar)
exec lin_RPAuthStatSex @table_from, @table_to, @logdate
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
lin_ProcessLogNew
	do make report table
INPUT
	@report_date	datetime,
	@report_world	int
OUTPUT
	
return
made by
	young
date
	2003-09-23
********************************************/
CREATE PROCEDURE [DBO].[lin_ProcessLogNew]

	@report_date datetime ,
	@report_world int = 1
AS
SET NOCOUNT ON

if @report_date is null
begin
	set @report_date = getdate()
	set @report_date = dateadd(d, -1, getdate())
end

DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)
DECLARE @logdate int

set @nyear = datepart(yyyy, @report_date)
set @nmonth = datepart(mm, @report_date)
set @nday = datepart(dd, @report_date)

set @stryear = cast(@nyear as varchar)
if @nmonth < 10
	set @strmonth = '0' + cast(@nmonth as varchar)
else
	set @strmonth = cast (@nmonth as varchar)

if @nday < 10
	set @strday = '0' + cast(@nday as varchar)
else
	set @strday = cast (@nday as varchar)	

set @str_report = @stryear + '/' + @strmonth + '/' + @strday
set @logdate = cast(@stryear + @strmonth + @strday as int)

------------- now.. we have year, month, day string
DECLARE @table_from varchar(60)
DECLARE @table_to varchar(60)
declare @sql varchar(512)


set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data_' + cast ( @report_world as varchar)

-- check index
set @sql = 'select * from  lin2log.dbo.sysindexes (nolock) where name = ''IX_' + @table_from + '_3'''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE CLUSTERED INDEX IX_' + @table_from + '_3 on lin2log.dbo.' + @table_from + ' (log_id) '
	exec (@sql)
end 

set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data2_' + cast ( @report_world as varchar)

-- check index
set @sql = 'select * from  lin2log.dbo.sysindexes (nolock) where name = ''IX_' + @table_from + '_3'''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE CLUSTERED INDEX IX_' + @table_from + '_3 on lin2log.dbo.' + @table_from + ' (log_id) '
	exec (@sql)
end 


--------------------------- using view
set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @report_world as varchar)


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

-- make LOGINCOUNT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LOGINCOUNT_' + cast(@report_world as varchar)
exec lin_RPLoginCount @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make HUNTCOUNT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_HUNTCOUNT_' + cast(@report_world as varchar)
exec lin_RPHuntCount @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make LEARNSKILLLEV report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEARNSKILLLEV_' + cast(@report_world as varchar)
exec lin_RPLearnSkillLev @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CHANGECLASS report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CHANGECLASS_' + cast(@report_world as varchar)
exec lin_RPChangeClass @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PLAYTIME report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PLAYTIME_' + cast(@report_world as varchar)
exec lin_RPPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCHUNTED report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCHUNTED_' + cast(@report_world as varchar)
exec lin_RPNPCHunted @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ITEMBUY report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMBUY_' + cast(@report_world as varchar)
exec lin_RPItemBuy @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ITEMSELL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMSELL_' + cast(@report_world as varchar)
exec lin_RPItemSell @table_from, @table_to, @logdate
waitfor delay '0:0:6'


-- make EARNADENA report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EARNADENA_' + cast(@report_world as varchar)
exec lin_RPEarnAdena @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make EARNSP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EARNSP_' + cast(@report_world as varchar)
exec lin_RPEarnSP @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDROP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROP_' + cast(@report_world as varchar)
exec lin_RPNPCDrop @table_from, @table_to, @logdatewaitfor delay '0:0:6'

-- make NPCDROP2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROP2_' + cast(@report_world as varchar)
exec lin_RPNPCDrop2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make LEVUP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_LEVUP_' + cast(@report_world as varchar)
exec lin_RPLevUp @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCDIE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIE_' + cast(@report_world as varchar)
exec lin_RPPCDie @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCDIELOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIELOC_' + cast(@report_world as varchar)
exec lin_RPPCDieLoc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDIELOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDIELOC_' + cast(@report_world as varchar)
exec lin_RPNPCDieLoc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCDIELOC2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCDIELOC2_' + cast(@report_world as varchar)
exec lin_RPPCDieLoc2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDIELOC2 report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDIELOC2_' + cast(@report_world as varchar)
exec lin_RPNPCDieLoc2 @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make WAREDEPOSIT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_WAREDEPOSIT_' + cast(@report_world as varchar)
exec lin_RPWareDeposit @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make WARERETRIEVE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_WARERETRIEVE_' + cast(@report_world as varchar)
exec lin_RPWareRetrieve @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TRADEGIVE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEGIVE_' + cast(@report_world as varchar)
exec lin_RPTradeGive @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make TRADEGET  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_TRADEGET_' + cast(@report_world as varchar)
exec lin_RPTradeGet  @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make USESKILL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_USESKILL_' + cast(@report_world as varchar)
exec lin_RPUseSkill @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ACCOUNTPLAYTIME  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ACCOUNTPLAYTIME_' + cast(@report_world as varchar)
exec lin_RPAccountPlayTime @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CASTSKILL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CASTSKILL_' + cast(@report_world as varchar)
exec lin_RPCastSkill @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make PCKILLNPC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_PCKILLNPC_' + cast(@report_world as varchar)
exec lin_RPPCKillNPC @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDROPLOC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROPLOC_' + cast(@report_world as varchar)
exec lin_RPNPCDropLoc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make EQUIPITEM report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_EQUIPITEM_' + cast(@report_world as varchar)
exec lin_RPEquipItem @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make STAND report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_STAND_' + cast(@report_world as varchar)
exec lin_RPStand @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make DIEDURATION report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_DIEDURATION_' + cast(@report_world as varchar)
exec lin_RPDieDuration @table_from, @table_to, @logdatewaitfor delay '0:0:6'

-- make CONCURRENT  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CONCURRENT_' + cast(@report_world as varchar)
exec lin_RPConcurrent @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CLASS report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CLASS_' + cast(@report_world as varchar)
exec lin_RPClass @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ENCHANT report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENCHANT_' + cast(@report_world as varchar)
exec lin_RPEnchant @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ENCHANTFAIL report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENCHANTFAIL_' + cast(@report_world as varchar)
exec lin_RPEnchantFail @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make CRYSTALIZE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_CRYSTALIZE_' + cast(@report_world as varchar)
exec lin_RPCrystalize @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make SELLPRIVATE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_SELLPRIVATE_' + cast(@report_world as varchar)
exec lin_RPSellPrivate @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ITEMINC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMINC_' + cast(@report_world as varchar)
exec lin_RPItemInc @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ITEMDEC report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ITEMDEC_' + cast(@report_world as varchar)
exec lin_RPItemDec @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make BEGINQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_BEGINQUEST_' + cast(@report_world as varchar)
exec lin_RPBeginQuest @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make ENDQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_ENDQUEST_' + cast(@report_world as varchar)
exec lin_RPEndQuest @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make STOPQUEST report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_STOPQUEST_' + cast(@report_world as varchar)
exec lin_RPStopQuest @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make DIEDROP report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_DIEDROP_' + cast(@report_world as varchar)
exec lin_RPDieDrop @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make NPCDROPITEM report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_NPCDROPITEM_' + cast(@report_world as varchar)
exec lin_RPNPCDropItem @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make SAYCOUNT  report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_SAYCOUNT_' + cast(@report_world as varchar)
exec lin_RPSayCount @table_from, @table_to, @logdate
waitfor delay '0:0:6'

-- make RECIPE report
set @table_to =  'R' + @stryear + '_' + @strmonth  +  '_RECIPE_' + cast(@report_world as varchar)
exec lin_RPRecipe @table_from, @table_to, @logdate
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
lin_RPAccountPlayTime
	do make account play time report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAccountPlayTime]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' account_id	int, '
		+ ' play_time	int, '
		+ ' logoff_count	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)

end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor_account, etc_num5  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 805   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num5  ) ( select log_id, actor_account, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 805  ) '
exec (@sql)



-- insert into report table

-- 계정별 playtime
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  account_id, play_time, logoff_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', actor_account, sum(etc_num5 ), count(log_id) from  '
	+ @tmp_table  + ' ( nolock )  group by actor_account  )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPAsset
	do make item asset report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-10-31
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAsset]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' level		int,' 
		+ ' class		int, '
		+ ' adena_sum	int, '
		+ ' price_sum	int, '
		+ ' item_sum	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor,  etc_num1,  etc_num2, etc_num3, etc_num4, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 813 and etc_num6 < 600  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor,  etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 ) ( select log_id, actor, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 813 and etc_num6 < 600  ) '
exec (@sql)

-- insert into report table
-- item
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, level, class, adena_sum, price_sum, item_sum ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', etc_num4, etc_num5, avg ( cast ( ad as money) ),  avg ( cast ( dp as money) ),  avg ( cast ( ts as money) )  '
	+ '  from ( select actor, etc_num4, etc_num5, ad=avg ( cast ( etc_num1 as money) ),  dp=avg ( cast ( etc_num2 as money) ),  ts=avg ( cast ( etc_num3 as money) ) from '
	+ @tmp_table  + ' ( nolock )  group by actor, etc_num4, etc_num5 ) as R1  group by etc_num4, etc_num5 )  option (MAXDOP 1 )'
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

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
lin_RPAuthStat
	do make authed report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-18
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAuthStat]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(2048)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' stat		int, '
		+ ' play_account int, '
		+ ' logout_count		int, '
		+ ' avg_playtime		int ,  '
		+ ' stdev_playtime	int ,  '
		+ ' sum_playtime		money  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  stat, play_account, logout_count, avg_playtime, stdev_playtime, sum_playtime  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', stat, count ( distinct ( actor_account)), count ( stat ), avg ( cast ( etc_num4 as money ) ) , stdev ( cast ( etc_num4 as money ) ) ,  sum ( cast ( etc_num4 as money ) )    from   '
	+ ' ( select stat = case when etc_num1 < 1001 then 1 else 1001 end  ,  etc_num4 , actor_account  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 804 ) as R1 group by stat  )  option (MAXDOP 1 ) '
exec (@sql )
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
lin_RPAuthStatAge
	do make authed report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-23
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAuthStatAge]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(2048)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' stat		int, '
		+ ' age		smallint, '
		+ ' play_account int, '
		+ ' logout_count		int, '
		+ ' avg_playtime		int ,  '
		+ ' stdev_playtime	int ,  '
		+ ' sum_playtime		money  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  stat, age, play_account, logout_count, avg_playtime, stdev_playtime, sum_playtime  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', stat, etc_num2, count ( distinct ( actor_account)), count ( stat ), avg ( cast ( etc_num4 as money ) ) , stdev ( cast ( etc_num4 as money ) ) ,  sum ( cast ( etc_num4 as money ) )    from   '
	+ ' ( select stat = case when etc_num1 < 1001 then 1 else 1001 end  ,  etc_num2, etc_num4 , actor_account  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 804 ) as R1 group by stat  , etc_num2 )  option (MAXDOP 1 ) '
exec (@sql )
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
lin_RPAuthStatSex
	do make authed report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-23
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAuthStatSex]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(2048)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' stat		int, '
		+ ' sex		smallint, '
		+ ' play_account int, '
		+ ' logout_count		int, '
		+ ' avg_playtime		int ,  '
		+ ' stdev_playtime	int ,  '
		+ ' sum_playtime		money  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  stat, sex, play_account, logout_count, avg_playtime, stdev_playtime, sum_playtime  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', stat, etc_num3, count ( distinct ( actor_account)), count ( stat ), avg ( cast ( etc_num4 as money ) ) , stdev ( cast ( etc_num4 as money ) ) ,  sum ( cast ( etc_num4 as money ) )    from   '
	+ ' ( select stat = case when etc_num1 < 1001 then 1 else 1001 end  ,  etc_num3, etc_num4 , actor_account  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 804 ) as R1 group by stat  , etc_num3 )  option (MAXDOP 1 ) '
exec (@sql )
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
lin_RPAuthed
	do make authed report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-8-5
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAuthed]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_hour	smallint, '
		+ ' log_min	smallint, '
		+ ' min_logon	int, '
		+ ' max_logon	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_hour, log_min, min_logon, max_logon ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', datepart(hour, act_time), datepart(minute, act_time), min(etc_num4),  max(etc_num4)  from  '
	+ ' ( select log_id, act_time, etc_num4  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 801 ) as R1 group by datepart(hour, act_time), datepart(minute, act_time)  )  option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPAuthed2
	do make authed report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-8-5
********************************************/
CREATE PROCEDURE [DBO].[lin_RPAuthed2]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_hour	smallint, '
		+ ' log_min	smallint, '
		+ ' min_logon	int, '
		+ ' max_logon	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_hour, log_min, min_logon, max_logon ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', datepart(hour, act_time), datepart(minute, act_time), min(etc_num4),  max(etc_num4)  from  '
	+ ' ( select log_id, act_time, etc_num4  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 802 ) as R1 group by datepart(hour, act_time), datepart(minute, act_time)  )  option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPBeginQuest
	do make die item crystalize stats
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-06-02
********************************************/
CREATE PROCEDURE [DBO].[lin_RPBeginQuest]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' race		smallint, '
		+ ' class		smallint, '
		+ ' level		smallint, '
		+ ' quest_id	int, '
		+ ' quest_count	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num3, etc_num4, etc_num5  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 303   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num3, etc_num4, etc_num5  ) ( select log_id, etc_num1, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 303  ) '
exec (@sql)


-- insert into report table
-- begin quest report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  race, class, level, quest_id, quest_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num3, etc_num4, etc_num5, count(log_id) from '
	+ @tmp_table  + ' ( nolock )  group by  etc_num1, etc_num3, etc_num4, etc_num5 )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPCastSkill
	do make cast skill report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCastSkill]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' skill_id 	int , '
		+ ' skill_level 	smallint , '
		+ ' cast_count 	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 403 and ( etc_num7 is null or etc_num7 = 0 )  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7 ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 403 and ( etc_num7 is null or etc_num7 = 0 )  ) '
exec (@sql)

-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, cast_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, etc_num5, etc_num6, count(log_id )  from   '
	+ @tmp_table + ' ( nolock )  group by etc_num5, etc_num6, etc_num1   )  option (MAXDOP 1 ) '
exec (@sql )
-- sex  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, cast_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, etc_num5, etc_num6, count(log_id)  from  '
	+ @tmp_table  + ' ( nolock ) group by etc_num5, etc_num6, etc_num2    )  option (MAXDOP 1 ) '
exec (@sql )
-- class  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, cast_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,  etc_num5, etc_num6, count(log_id) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num5, etc_num6, etc_num3  ) option (MAXDOP 1 )  '
exec (@sql )
-- level  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, cast_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4,  etc_num5, etc_num6, count(log_id) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num5, etc_num6, etc_num4   )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table  ' + @tmp_table
exec ( @sql )

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
lin_RPCastSpoil
	do make cast spoin skill stats
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-12-16
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCastSpoil]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_type	smallint, '
		+ ' x_loc		int, '
		+ ' y_loc 	int, '
		+ ' npc_classid 	int, '
		+ ' cast_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_3 on dbo.' + @table_to + ' (npc_classid) '
	exec (@sql)

end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, target, etc_num5,  location_x, location_y  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 403 and etc_num5 = 254  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, target, etc_num5,  location_x, location_y  ) ( select log_id, target, etc_num5,  location_x, location_y  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 403 and etc_num5 = 254 ) '
exec (@sql)


-- insert into report table

-- 
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, x_loc, y_loc, npc_classid, cast_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1,  FLOOR(location_x / 32768.0) , FLOOR(location_y / 32768.0) , target, count( target )  from '
	+ @tmp_table + '  ( nolock )  group by FLOOR(location_x / 32768.0) , FLOOR(location_y / 32768.0) , target  )  option (MAXDOP 1 ) '
exec (@sql )

-- 
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, x_loc, y_loc, npc_classid, cast_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2,  FLOOR(location_x / 1024.0) , FLOOR(location_y / 1024.0) , target, count( target )  from '
	+ @tmp_table + '  ( nolock )  group by FLOOR(location_x / 1024.0) , FLOOR(location_y / 1024.0) , target  )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)
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
lin_RPCastleTax
	do make castle tax income
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-26
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCastleTax]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' castle_id	smallint, '
		+ ' real_tax	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, castle_id, real_tax ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ',  etc_num1, sum ( etc_num4 )   from  '
	+ ' lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 950  group by etc_num1 )  option (MAXDOP 1 ) '
exec (@sql )
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
lin_RPCastleTaxIncome
	do make castle tax income
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-15
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCastleTaxIncome]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' castle_id	smallint, '
		+ ' tax		int, '
		+ ' total_sell	money , '
		+ ' total_tax	money , '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, castle_id, tax, total_sell, total_tax ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num5, etc_num6,  sum ( cast ( etc_num7 as money ) ), sum( cast ( etc_num8 as money ) ) from  '
	+ ' ( select etc_num5, etc_num6, etc_num7, etc_num8, log_id '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 948 ) as R1 group by etc_num5, etc_num6 )  option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPCastleTaxTribute
	do make castle tax tribute
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-15
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCastleTaxTribute]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' castle_id	smallint, '
		+ ' tribute_id	smallint, '
		+ ' tax		int, '
		+ ' total_sell	money , '
		+ ' total_tax	money , '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, castle_id, tribute_id, tax, total_sell, total_tax ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num2, etc_num3, sum ( cast ( etc_num4 as money ) ), sum ( cast ( etc_num5 as money) )  from  '
	+ ' ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 949 ) as R1 group by etc_num1, etc_num2, etc_num3  )  option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPCastleWar
	do make castle war winner report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-1-15
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCastleWar]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' pledge_name	varchar(50), '
		+ ' log_id	int, '
		+ ' act_time	datetime, '
		+ ' castle_id 	int , '
		+ ' pledge_id 	int , '
		+ ' alliance_id 	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)

end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


-- insert into report table

-- 
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  pledge_name, log_id, act_time,  castle_id, pledge_id, alliance_id ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_str1, log_id, act_time, etc_num1, etc_num2, etc_num3  from lin2log.dbo.' + @table_from 
	+ ' (nolock)  where log_id in ( 244, 245 )  )  option (MAXDOP 1 ) '
exec (@sql )
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
lin_RPChangeClass
	do make changed class
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPChangeClass]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' race		int, '
		+ ' level		int, '
		+ ' class_from	int, '
		+ ' class_to	int, '
		+ ' use_time	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

-- 클래스 변경로그들을 다 저장
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  race, level, class_from, class_to, use_time) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num4, etc_num5, etc_num3, etc_num6 from '
	+ ' ( select log_id, etc_num1, etc_num4, etc_num3, etc_num5, etc_num6, etc_num7 '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 816 and ( etc_num7 is null or etc_num7 = 0 ) ) as R1  ) option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPCharPlay
	do make char play stat
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-03-16
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCharPlay]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' class		smallint, '
		+ ' level		smallint, '
		+ ' loc_x		int, '
		+ ' loc_y		int,  '
		+ ' play_count	int   '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' ( log_date, loc_x,  loc_y,class,  level  ) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end



-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num10, etc_num5, location_x, location_y into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 812  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num10, etc_num5, location_x, location_y ) ( select log_id, etc_num10, etc_num5, location_x, location_y '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 812 ) '
exec (@sql)

-- insert into report table
-- begin quest report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  class, level, loc_x, loc_y, play_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num10, etc_num5, floor( location_x / 1024.0) ,  floor ( location_y / 1024.0 ) , count ( log_id )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num10, etc_num5, floor( location_x / 1024.0) ,  floor ( location_y / 1024.0 )   )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPCharPlayTime
	do make char play time report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-10-22
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCharPlayTime]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' user_id	int, '
		+ ' user_level	int, '
		+ ' log_count	int, '
		+ ' play_time	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor, etc_num4, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 805  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor, etc_num4, etc_num5 ) ( select log_id, actor, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 805 ) '
exec (@sql)


-- insert into report table
-- char play time report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  user_id, user_level, log_count, play_time ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', actor, max ( etc_num4), count ( log_id), sum (etc_num5)  from '
	+ @tmp_table + ' ( nolock )  group by actor )  option (MAXDOP 1 ) '

exec (@sql )


-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPClass
	do make class change report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPClass ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' old_class	smallint, '
		+ ' new_class	smallint, '
		+ ' change_count 	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num3, etc_num5, etc_num7  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 816 and ( etc_num7 is null or etc_num7 = 0 )  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num3, etc_num5, etc_num7  ) ( select log_id, etc_num3, etc_num5, etc_num7  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 816 and ( etc_num7 is null or etc_num7 = 0 )  ) '
exec (@sql)


-- insert into report table

--  전직한 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  old_class, new_class, change_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num5, etc_num3, count(log_id)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num5, etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop 
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPClassDec
	do make class  decrease report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-11-10
********************************************/
CREATE PROCEDURE [DBO].[lin_RPClassDec ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' class		int, '
		+ ' amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

--  class change
-- log_id = 816
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 816  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5 ) ( select log_id, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 816 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  class, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num5, -1 * count( log_id ) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num5  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPClassInc
	do make class  increase report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-11-10
********************************************/
CREATE PROCEDURE [DBO].[lin_RPClassInc ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' class		int, '
		+ ' amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

--  class change
-- log_id = 816
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num3 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 816  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num3 ) ( select log_id, etc_num3 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 816 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  class, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num3, count( log_id ) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num3  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPConcurrent
	do make concurrent connection  report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPConcurrent]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_hour	smallint, '
		+ ' log_min	smallint, '
		+ ' min_logon	int, '
		+ ' max_logon	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end



-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, act_time, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 803 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, act_time, etc_num5 ) ( select log_id, act_time, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 803 ) '
exec (@sql)

-- insert into report table
-- levelup report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_hour, log_min, min_logon, max_logon ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', datepart(hour, act_time), datepart(minute, act_time), min(etc_num5),  max(etc_num5)  from  '
	+ @tmp_table  + ' ( nolock )  group by datepart(hour, act_time), datepart(minute, act_time)  )  option (MAXDOP 1 ) '
exec (@sql )

--
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPCrystalize
	do make die item crystalize stats
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-06-02
********************************************/
CREATE PROCEDURE [DBO].[lin_RPCrystalize]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_id	int, '
		+ ' enchant 	int, '
		+ ' cry_item_id	int, '
		+ ' item_cnt	int, '
		+ ' cry_item_cnt	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5, etc_num7, etc_num8, etc_num9 , etc_num10  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 933 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5, etc_num7,  etc_num8, etc_num9 , etc_num10  ) ( select log_id, etc_num5, etc_num7, etc_num8, etc_num9 , etc_num10  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 933 ) '
exec (@sql)



-- insert into report table
-- levelup report

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, enchant, cry_item_id, item_cnt, cry_item_cnt ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num8, etc_num7, etc_num5, count( etc_num8 ), sum(etc_num10) from  '
	+ @tmp_table  + ' ( nolock )  group by  etc_num8, etc_num7, etc_num5 ) option (MAXDOP 1 ) '
exec (@sql )

-- 
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPDieDrop
	do make die drop item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-08-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPDieDrop]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' race		smallint, '
		+ ' class		smallint, '
		+ ' level		smallint, '
		+ ' item_type	int, '
		+ ' drop_count	int, '
		+ ' drop_amount	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num3, etc_num4, etc_num8, etc_num9  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 915 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num3, etc_num4, etc_num8, etc_num9 ) ( select log_id, etc_num1, etc_num3, etc_num4, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 915 ) '
exec (@sql)


-- insert into report table

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  race, class, level, item_type, drop_count, drop_amount  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num3, etc_num4, etc_num8, count(log_id) , sum(etc_num9) from '
	+ @tmp_table  + ' ( nolock )  group by  etc_num1, etc_num3, etc_num4, etc_num8 )  option (MAXDOP 1 ) '

exec (@sql )

-- 
set @sql = ' drop  table ' + @tmp_table
exec ( @sql )

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
lin_RPDieDuration
	do make die duration report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPDieDuration]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' npc_id	int, '
		+ ' npc_lev	smallint, '
		+ ' die_duration	int, '
		+ ' die_count	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, target_account, etc_num7, etc_num8 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, target_account, etc_num7, etc_num8) ( select log_id, target_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112 ) '
exec (@sql)


-- insert into report table

	-- new report
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  npc_id, npc_lev, die_duration, die_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', target_account, etc_num7, sum(etc_num8), count(log_id)  from  '
		+ @tmp_table  + ' ( nolock )  group by target_account , etc_num7 ) option (MAXDOP 1 ) '
	exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPEarnAdena
	do make earn adena 
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEarnAdena]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ 'log_count 	money , '
		+ ' get_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- insert into report table

-- get item


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num8, etc_num9, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906 and etc_num8 = 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num8, etc_num9, actor  ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num8, etc_num9, actor  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906 and etc_num8 = 57 ) '
exec (@sql)

-- race 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, sum(cast (etc_num9 as money) ) , count( distinct actor )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num1 )  option (MAXDOP 1 ) '
exec (@sql )

-- sex 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count , get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2,  sum(cast (etc_num9 as money) )  , count(distinct actor ) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num2 )  option (MAXDOP 1 ) '
exec (@sql )

-- class 별 사번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,  sum(cast (etc_num9 as money) ) , count(distinct actor ) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

-- level 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count , get_count) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4,  sum(cast (etc_num9 as money) ) , count(distinct actor )  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num4 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)




-- sell store
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num8, etc_num9, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 and etc_num8 = 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num8, etc_num9, actor  ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num8, etc_num9, actor  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 and etc_num8 = 57 ) '
exec (@sql)

-- race 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, sum(cast (etc_num9 as money) ) , count( distinct actor )  from '
	+ @tmp_table  + ' ( nolock ) where   etc_num8 > 0  group by etc_num1 )  option (MAXDOP 1 ) '
exec (@sql )

-- sex 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count , get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2,  sum(cast (etc_num9 as money) )  , count(distinct actor ) from '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 > 0  group by etc_num2 )  option (MAXDOP 1 ) '
exec (@sql )

-- class 별 사번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,  sum(cast (etc_num9 as money) ) , count(distinct actor ) from '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 > 0  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

-- level 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count , get_count) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4,  sum(cast (etc_num9 as money) ) , count(distinct actor )  from  '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 > 0  group by etc_num4 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)


-- sell private store
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num10, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 931 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num10, actor  ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num10, actor  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 931 ) '
exec (@sql)


-- race 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, sum(cast (etc_num10 as money) ) , count( distinct actor )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num1 )  option (MAXDOP 1 ) '
exec (@sql )

-- sex 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count , get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2,  sum(cast (etc_num10 as money) )  , count(distinct actor ) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num2 )  option (MAXDOP 1 ) '
exec (@sql )

-- class 별 사번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,  sum(cast (etc_num10 as money) ) , count(distinct actor ) from '
	+ @tmp_table + ' ( nolock )  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

-- level 별 번 adena 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count , get_count) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4,  sum(cast (etc_num10 as money) ) , count(distinct actor )  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num4 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPEarnSP
	do make earn sp
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEarnSP]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ 'log_count 	money , '
		+ ' get_count	int ' 
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, actor  ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, actor  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112 ) '
exec (@sql)

-- insert into report table



-- race 별 번 sp 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, sum(cast ( etc_num5 as money )) , count(distinct actor )   from '
	+ @tmp_table + ' ( nolock )  group by etc_num1 ) option (MAXDOP 1 ) '
exec (@sql )
-- sex 별 번 sp 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count , get_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, sum(cast ( etc_num5 as money ))  , count(distinct actor ) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num2 )  option (MAXDOP 1 )'
exec (@sql )
-- class 별 사번 sp 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count , get_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, sum(cast ( etc_num5 as money ))  , count(distinct actor )  from '
	+ @tmp_table + ' ( nolock )  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )
-- level 별 번 sp 총 양
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count , get_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4, sum(cast ( etc_num5 as money ))  , count(distinct actor )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num4 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPEnchant
	do make enchant item succeeded report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEnchant ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_id	int,'
		+ ' old_enchant	smallint, ' 
		+ ' succeed_count 	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5, etc_num8 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 925  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5, etc_num8  ) ( select log_id, etc_num5, etc_num8  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 925 ) '
exec (@sql)

-- insert into report table

--  enchant  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, old_enchant, succeed_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, etc_num5, count( log_id)  from  '
	+ @tmp_table + ' ( nolock )  group by etc_num8, etc_num5 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

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
lin_RPEnchantFail
	do make enchant item failedreport table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEnchantFail ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_id	int,'
		+ ' old_enchant	smallint, ' 
		+ ' fail_count 	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num7, etc_num8 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 926  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num7, etc_num8 ) ( select log_id, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 926 ) '
exec (@sql)

-- insert into report table

--  enchant  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, old_enchant, fail_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, etc_num7, count(log_id)  from  '
	+ @tmp_table + ' ( nolock )  group by etc_num8, etc_num7 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

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
lin_RPEndQuest
	do make end quest
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-06-02
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEndQuest]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' race		smallint, '
		+ ' class		smallint, '
		+ ' level		smallint, '
		+ ' quest_id	int, '
		+ ' quest_count	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num3, etc_num4, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 305  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num3, etc_num4, etc_num5 ) ( select log_id, etc_num1, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 305 ) '
exec (@sql)

-- insert into report table
-- begin quest report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  race, class, level, quest_id, quest_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num3, etc_num4, etc_num5, count(log_id) from  '
	+ @tmp_table  + ' ( nolock )  group by  etc_num1, etc_num3, etc_num4, etc_num5 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPEquipItem
	do make equip item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEquipItem]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' item_type 	int , '
		+ ' equip_count 	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num6 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 824  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num6 ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num6 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 824 ) '
exec (@sql)

-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  item_type, equip_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1,  etc_num6, count(log_id)  from   '
	+ @tmp_table  + ' ( nolock )  group by etc_num1, etc_num6 ) option (MAXDOP 1 )  '
exec (@sql )
-- sex  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  item_type, equip_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2,  etc_num6, count(log_id) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num2, etc_num6 ) option (MAXDOP 1 )  '
exec (@sql )
-- class  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  item_type, equip_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,   etc_num6, count(log_id)  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num3, etc_num6 ) option (MAXDOP 1 )  '
exec (@sql )
-- level  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4,  etc_num6, count( log_id ) from    '
	+ @tmp_table  + ' ( nolock )  group by etc_num4, etc_num6 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPEquipped
	do make class change report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-10-31
********************************************/
CREATE PROCEDURE [DBO].[lin_RPEquipped ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' level		int, '
		+ ' class		int, '
		+ ' slot_type	int,'
		+ ' item_type	int,'
		+ ' equip_count	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 833 and act_time > ''2003/10/29 10:0:0''  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10 ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 833 and act_time > ''2003/10/29 10:0:0''   ) '
exec (@sql)


-- insert into report table

--  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 3, etc_num3, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 4, etc_num4, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num4 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 5, etc_num5, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num5 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 6, etc_num6, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num6 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 7, etc_num7, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num7 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 8, etc_num8, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num8 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 9, etc_num9, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num9 ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class, slot_type, item_type, equip_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num1, etc_num2, 10, etc_num10, count( *)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1, etc_num2, etc_num10 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop 
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPExp
	do make exp report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-10-23
********************************************/
CREATE PROCEDURE [DBO].[lin_RPExp]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' level		int, '
		+ ' class 	int, '
		+ ' party		int,  '
		+ ' partycount	int, '
		+ ' playtime	int, '
		+ ' exp		int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select  etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num10 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 813 and etc_num6 > 0 and etc_num7 >= 0  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num10 ) ( select  etc_num4, etc_num5, etc_num6, etc_num7, etc_num8 , etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 813 and etc_num6 > 0  and etc_num7 >= 0 ) '
exec (@sql)

	-- new insert 
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level, class,  party, partycount, playtime, exp ) ( ' 
		+ ' select ' + CAST(@logdate as varchar)  + ' ,  etc_num4, etc_num5, case etc_num8 when 0 then 0 else 1 end, '
		+ '  etc_num8, sum ( cast ( etc_num6 as float ) ) - sum ( cast ( isnull( etc_num10 , 0 ) as float ) ) ,  sum ( etc_num7 )  from '
		+  @tmp_table + ' group by etc_num4, etc_num5, etc_num8 '
		+ '  )  option (MAXDOP 1 ) '
	exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)
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
lin_RPGetItem
	do make get item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-10-29
********************************************/
CREATE PROCEDURE [DBO].[lin_RPGetItem]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' level		int,' 
		+ ' class		int, '
		+ ' item_type	int, '
		+ ' char_count	int, '
		+ ' get_count	int, '
		+ ' item_amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor, etc_num3, etc_num4,  etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906  '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor, etc_num3, etc_num4,  etc_num8, etc_num9 ) ( select log_id, actor,  etc_num3, etc_num4, etc_num8, -1*etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 940 and act_time > ''2003/10/29 10:0:0'' ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor,  etc_num3, etc_num4,  etc_num8, etc_num9 ) ( select log_id, actor,  etc_num3, etc_num4, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906 ) '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor,  etc_num3, etc_num4,  etc_num8, etc_num9 ) ( select log_id, actor, etc_num3, etc_num4, etc_num8, -1*etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 940 and act_time > ''2003/10/29 10:0:0'' ) '
exec (@sql)

-- insert into report table

-- get item  
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  class, level, item_type, char_count, get_count,  item_amount ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num3, etc_num4, etc_num8, count( distinct ( actor)), count( log_id),  sum(etc_num9) from '
	+ @tmp_table  + ' ( nolock )  where etc_num9 > 0 group by etc_num3, etc_num4, etc_num8 ) option (MAXDOP 1 )'
exec (@sql )

-- get item  which char dropped
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, class,  level, item_type, char_count, get_count, item_amount ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num3, etc_num4, etc_num8, count ( distinct ( actor ) ) , count( log_id), sum(etc_num9) from '
	+ @tmp_table  + ' ( nolock )  where etc_num9 < 0 group by etc_num3, etc_num4, etc_num8 ) option (MAXDOP 1 )'
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

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
lin_RPHuntCount
	do make hunting count report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPHuntCount]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ 'npc_id	int, '
		+ ' npc_level	int, '
		+ 'log_count 	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, target_account, etc_num7, etc_num10 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, target_account, etc_num7, etc_num10 ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, target_account, etc_num7, etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112 ) '
exec (@sql)

-- insert into report table

	-- race 별 사냥한 총 NPC수
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, npc_id, npc_level,   log_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, target_account, etc_num7, count(distinct etc_num10 )  from  '
		+ @tmp_table  + ' ( nolock )  group by etc_num1, target_account , etc_num7 )  option (MAXDOP 1 ) '
	exec (@sql )
	-- sex 별 사냥한 총 NPC수
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, npc_id, npc_level,  log_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, target_account, etc_num7, count(distinct etc_num10 )  from  '
		+ @tmp_table  + ' ( nolock )  group by etc_num2, target_account , etc_num7 ) option (MAXDOP 1 ) '
	exec (@sql )
	-- class 별 사냥한 총 NPC수
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, npc_id,  npc_level, log_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, target_account, etc_num7,  count(distinct etc_num10 ) from   '
		+ @tmp_table  + ' ( nolock )  group by etc_num3, target_account , etc_num7 )  option (MAXDOP 1 ) '
	exec (@sql )
	-- level 별 사냥한 총 NPC수
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, npc_id,  npc_level, log_count ) ( ' 
		+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4, target_account, etc_num7, count(distinct etc_num10 ) from  '
		+ @tmp_table  + ' ( nolock )  group by etc_num4, target_account , etc_num7  ) option (MAXDOP 1 ) '
	exec (@sql )

-- drop tmptable
set @sql = 'drop table ' + @tmp_table
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


/********************************************
lin_RPItem
	do make item snap shot report
INPUT
	@db_server	varchar(30),
	@user_id	varchar(30),
	@user_pass	varchar(30),
	@world_id	int

OUTPUT

return
made by
	young
date
	2003-6-18
********************************************/
CREATE PROCEDURE [DBO].[lin_RPItem]
	@db_server	varchar(30),
	@user_id	varchar(30),
	@user_pass	varchar(30),
	@world_id	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)
declare @dtnow datetime
declare @dtyear int
declare @dtmonth int
declare @dtday int
declare @logdate int
declare @table_to nvarchar(50)

set @dtnow = getdate()
set @dtyear = datepart( yyyy, @dtnow)
set @dtmonth = datepart( mm, @dtnow)
set @dtday = datepart( day, @dtnow)
set @logdate = @dtyear * 10000 + @dtmonth * 100 + @dtday

if @dtmonth < 10
	set @table_to = 'R' + cast( @dtyear as varchar) + '_0'  + cast( @dtmonth as varchar) + '_ITEM_' + cast( @world_id as varchar)
else
	set @table_to = 'R' + cast( @dtyear as varchar) + '_'  + cast( @dtmonth as varchar) + '_ITEM_' + cast( @world_id as varchar)


-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_type	int, '
		+ ' warehouse	int, '
		+ ' amount	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

set @sql = '  insert into ' + RTRIM(@table_to) + ' ( log_date, item_type, warehouse, amount ) ( ' 
	+ ' select  * '
	+ ' from OPENROWSET ( ''SQLOLEDB'', ''' + @db_server + ''';''' + @user_id + ''';''' + @user_pass  + ''',  '
	+ ' ''select log_date=' +  CAST( @logdate as NVARCHAR) + ' , item_type, warehouse, amount=sum( cast ( amount as money) ) from lin2world.dbo.user_item  (nolock) where char_id >1 group by item_type, warehouse'' )  )'
exec (@sql )

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
lin_RPItemBuy
	do make item buy report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-18
********************************************/
CREATE PROCEDURE [DBO].[lin_RPItemBuy]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' seller_id	int,' 
		+ ' item_id	int, '
		+ ' buy_count	int, '
		+ ' buy_amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5,  etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 901  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5, etc_num8, etc_num9 ) ( select log_id, etc_num5, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 901 ) '
exec (@sql)

-- insert into report table

-- 구입한 item
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, seller_id, item_id, buy_count, buy_amount ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num5, etc_num8, count(log_id), sum(etc_num9) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num5, etc_num8 ) option (MAXDOP 1 )'
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

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
lin_RPItemDec
	do make item amount increase report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPItemDec ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_id	int, '
		+ ' amount	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

--  item amount decrease
-- 상점에서 판것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 and etc_num9 < 0 and etc_num8 <> 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 and etc_num9 < 0 and etc_num8 <> 57  ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, sum(etc_num9)  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)


-- 아이템 삭제한것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9, etc_num10  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 907  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9, etc_num10 ) ( select log_id, etc_num8, etc_num9, etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 907 ) '
exec (@sql)


set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',  etc_num8, -1*sum(etc_num10)  from '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 = 0  group by etc_num8  )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',  etc_num8, sum(etc_num9)  from '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 < 0   group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',   etc_num8, -1*sum(etc_num9)   from  '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 > 0 and etc_num10 = 0 and etc_num8 <> 57   group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

-- 아이템 떨어뜨린것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 908  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 908 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',   etc_num8, sum(etc_num9) from '
	+ @tmp_table  + ' ( nolock ) where  etc_num9 < 0    group by etc_num8  )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',   etc_num8, -1*sum(etc_num9) from '
	+ @tmp_table + ' ( nolock ) where   etc_num9 > 0   group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

-- use item 한것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 911  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 911 ) '
exec (@sql)


set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',   etc_num8, sum(etc_num9) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num8   ) option (MAXDOP 1 ) '
exec (@sql )

-- 죽어서 떨어뜨린것
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',    etc_num8, -1*sum(etc_num9) from  '
	+ @tmp_table + ' ( nolock )  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

-- enchant fail 로 날린것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 926  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 926 ) '
exec (@sql)


set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',   etc_num8, -1*count(log_id) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )


-- 결정화해서 준것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 933  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 933 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, -1*count(etc_num9) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

----------------------------------------------------------------------------------------------------------------------------------------------------------------
-- adena amount decrease
-- 상점에서 아이템 구입한 비용
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 901 and etc_num8 = 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 901 and etc_num8 = 57 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, sum(cast(etc_num9 as money))  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

--  deposit fee
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 928and etc_num8 = 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 928 and etc_num8 = 57  ) '
exec (@sql)


set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',  etc_num8, -1*sum(cast(etc_num9 as money))  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num8 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop table 
set @sql = ' drop table ' + @tmp_table
exec ( @sql)

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
lin_RPItemInc
	do make item amount increase report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPItemInc ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_id	int, '
		+ ' amount	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

--  item amount increase
-- 상점에서 산것

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 901  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 901 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, sum(etc_num9)   from '
	+ @tmp_table  + ' ( nolock ) where etc_num9 > 0 and etc_num8 <> 57  group by etc_num8  )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, count( log_id )   from '
	+ @tmp_table  + ' ( nolock ) where etc_num9 = 0 and etc_num8 <> 57  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

-- 아이템 주은것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',  etc_num8, sum(etc_num9)  from '
	+ @tmp_table  + ' ( nolock ) where   etc_num9 > 0 and etc_num8 <> 57  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = 'drop table ' + @tmp_table
exec (@sql)

-- 결정화해서 생긴것
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5, etc_num10 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 933  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5, etc_num10 ) ( select log_id, etc_num5, etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 933 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ',   etc_num5, sum(etc_num10)  from '
	+ @tmp_table  + ' ( nolock ) where   etc_num5 <> 57   group by etc_num5   ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table ' + @tmp_table
exec (@sql )

--------------------------------------------------
-- adena amount increase
-- 상점에서 아이템 판 금액
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 and etc_num8 = 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 and etc_num8 = 57 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, sum(cast(etc_num9 as money))   from '
	+ @tmp_table + ' ( nolock )  group by etc_num8  )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table ' + @tmp_table
exec ( @sql)


-- 아데나 줍기
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906 and etc_num8 = 57  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num9 ) ( select log_id, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 906 and etc_num8 = 57 ) '
exec (@sql)
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num8, sum(cast(etc_num9 as money))  from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num8  ) option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPItemSell
	do make item sell report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-18
********************************************/
CREATE PROCEDURE [DBO].[lin_RPItemSell]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' buyer_id	int,' 
		+ ' item_id	int, '
		+ ' sell_count	int, '
		+ ' sell_amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5, etc_num8, etc_num9 ) ( select log_id, etc_num5, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 902 ) '
exec (@sql)


-- insert into report table

-- 판매한  item
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, buyer_id, item_id, sell_count, sell_amount ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num5, etc_num8, count(log_id), sum(etc_num9) from '
	+ ' ( select log_id, etc_num5, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 902 ) as R1 group by etc_num5, etc_num8 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPKillPCCount
	do make kill pc stat
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-03-16
********************************************/
CREATE PROCEDURE [DBO].[lin_RPKillPCCount]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' class		smallint, '
		+ ' level		smallint, '
		+ ' loc_x		int, '
		+ ' loc_y		int,  '
		+ ' kill_count	int   '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' ( log_date, loc_x,  loc_y,class,  level  ) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end



-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num3, etc_num4, location_x, location_y into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1111  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num3, etc_num4, location_x, location_y ) ( select log_id, etc_num3, etc_num4, location_x, location_y '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1111 ) '
exec (@sql)

-- insert into report table
-- begin quest report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  class, level, loc_x, loc_y, kill_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num3, etc_num4, floor( location_x / 1024.0) ,  floor ( location_y / 1024.0 ) , count ( log_id )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num3, etc_num4, floor( location_x / 1024.0) ,  floor ( location_y / 1024.0 )   )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPLearnSkillLev
	do make average skill level to learn each skills
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPLearnSkillLev]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ 'skill_id	int, '
		+ 'log_count 	int, '
		+ ' learnskill_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num3, etc_num5, etc_num4, etc_num8 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 401  and ( etc_num8 is null or etc_num8 = 0 ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num3, etc_num5, etc_num4, etc_num8 ) ( select log_id, etc_num1, etc_num3, etc_num5, etc_num4, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 401  and ( etc_num8 is null or etc_num8 = 0 ) ) '
exec (@sql)


-- insert into report table
-- race 별 스킬을 익힌 평균 레벨
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, skill_id, log_count , learnskill_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, etc_num5, sum(etc_num4) / count(log_id) , count(log_id) from '
	+ @tmp_table  + ' ( nolock )  group by etc_num5, etc_num1 )  option (MAXDOP 1 ) '
exec (@sql )

-- class 별 스킬을 익힌 평균 레벨
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, skill_id, log_count , learnskill_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num3, etc_num5, sum(etc_num4) / count(log_id) , count(log_id) from '
	+ @tmp_table + ' ( nolock ) group by etc_num3, etc_num5 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql  = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPLevDec
	do make Level decrease report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-11-10
********************************************/
CREATE PROCEDURE [DBO].[lin_RPLevDec ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' lev		int, '
		+ ' amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

--  lev decrease
-- log_id = 810
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num5 ) ( select log_id, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  lev, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num5, -1 * count( log_id ) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num5  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPLevInc
	do make Level increase report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-11-10
********************************************/
CREATE PROCEDURE [DBO].[lin_RPLevInc ]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' lev		int, '
		+ ' amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

--  lev  increase
-- log_id = 810
-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num4 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num4 ) ( select log_id, etc_num4 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810 ) '
exec (@sql)

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  lev, amount ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', etc_num4, count( log_id ) from  '
	+ @tmp_table  + ' ( nolock )  group by etc_num4  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPLevUp
	do make levelup report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPLevUp]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' levup_level	int, '
		+ ' levup_time	int, '
		+ ' char_count	int, '
		+ ' avg_time	bigint, '
		+ ' var_time	bigint, '
		+ ' v2_time	bigint, '
		+ ' min_time	int, '
		+ ' max_time	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num4, etc_num5,  etc_num6 , etc_num7  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num4, etc_num5,  etc_num6 , etc_num7   ) ( select log_id, etc_num4, etc_num5,  etc_num6 , etc_num7  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810  ) '
exec (@sql)


-- insert into report table
-- levelup report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  levup_level, levup_time, char_count, avg_time, var_time, v2_time, min_time, max_time ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num4, sum(etc_num6), count(log_id), avg(etc_num6), var(etc_num6) , count(log_id) * (var(etc_num6) + cast(avg(etc_num6 ) as bigint) * cast(avg(etc_num6 ) as bigint ) ), min(etc_num6), max(etc_num6)  from '
	+ @tmp_table +  ' ( nolock ) where  etc_num4 > etc_num5 and etc_num6 > 0 and ( etc_num7 is null or etc_num7 = 0 )    group by etc_num4 )  option (MAXDOP 1 ) '
exec (@sql )


-- drop tmptable
set @sql = 'drop table ' + @tmp_table
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
lin_RPLevUp2
	do make levelup2 report ( more accurate )
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-18
********************************************/
CREATE PROCEDURE [DBO].[lin_RPLevUp2]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' levup_level	int, '
		+ ' levup_count	int, '
		+ ' avg_time	int, '
		+ ' avgcount_time int, '
		+ ' std_time	int, '
		+ ' min_time	int, '
		+ ' max_time	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num4, etc_num5,  etc_num6 , etc_num7  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810  and etc_num7 = 0 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num4, etc_num5,  etc_num6 , etc_num7   ) ( select log_id, etc_num4, etc_num5,  etc_num6 , etc_num7  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 810 and etc_num7 = 0 ) '
exec (@sql)

-- insert into report table
-- levelup report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  levup_level, levup_count, avg_time, avgcount_time,  std_time, min_time, max_time ) ( ' 
	+ ' select ' + CAST ( @logdate as varchar)  +  ' , R1.etc_num4, char_count=count ( R1.etc_num4),  char_avg=avg ( R1.etc_num6) , count( R1.etc_num4 ) * avg( R1.etc_num6 ), char_std=stdev ( R1.etc_num6), min ( R1.etc_num6), Max ( R1.etc_num6 ) from ( '
	+ ' select etc_num4, etc_num6  from ' + @tmp_table + ' (nolock)   where log_id = 810 and etc_num4 > etc_num5 ) as R1 '
	+ '  left join ( '
	+ ' select etc_num4, avg6=avg( etc_num6 )  ,  stdev6=stdev ( etc_num6 ) , min2 = min ( etc_num6 ) from ' + @tmp_table + ' (nolock) where log_id = 810 and etc_num4 > etc_num5 group by etc_num4   ) as R2 '
	+ ' on R1.etc_num4 = R2.etc_num4 and R1.etc_num6 between    R2.avg6 - R2.stdev6 * 0.5 and R2.avg6 + R2.stdev6 * 3.0 '
	+ ' where R2.etc_num4 is not null '
	+ ' group by R1.etc_num4 '
	+ ' )  option (MAXDOP 1 ) '

 exec (@sql )

-- drop tmptable
set @sql = 'drop table ' + @tmp_table
exec (@sql)

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
lin_RPLoginCount
	do make login count report table
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT
	
return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPLoginCount]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ 'log_count 	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1,  etc_num2, etc_num3, etc_num4, actor , actor_account  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 803  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4,  actor , actor_account ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor , actor_account  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 803  ) '
exec (@sql)



-- insert into report table

-- race 별 로그인한 캐릭 숫자
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)  + ', 1, etc_num1, count(distinct actor) from '
	+ @tmp_table + '  ( nolock )  group by etc_num1 )  option (MAXDOP 1 ) '
exec (@sql )

-- sex 별 로그인한 캐릭 숫자
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)   + ', 2, etc_num2, count(distinct actor) from '
	+ @tmp_table + '  ( nolock )  group by etc_num2 )  option (MAXDOP 1 ) '
exec (@sql )

-- class 별 로그인한 캐릭 숫자
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)   + ', 3, etc_num3, count(distinct actor) from '
	+ @tmp_table + '   ( nolock )  group by etc_num3 )  option (MAXDOP 1 ) '
exec (@sql )

-- level 별 로그인한 캐릭 숫자
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)   + ', 4, etc_num4, count(distinct actor) from '
	+ @tmp_table + '   ( nolock )  group by etc_num4 )  option (MAXDOP 1 ) '
exec (@sql )

-- 로그인한 계정 숫자
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar)   + ', 5, 0, count(distinct actor_account) from '
	+ @tmp_table + '   ( nolock )   )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPNPCDieLoc
	do make cpc die location report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCDieLoc]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_type	smallint, '
		+ ' x_loc		int, '
		+ ' y_loc 	int, '
		+ ' die_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num10,  location_x, location_y  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num10,  location_x, location_y ) ( select log_id, etc_num10, location_x, location_y '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  ) '
exec (@sql)



-- insert into report table
	-- new report
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, x_loc, y_loc, die_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 1, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0), count( distinct  etc_num10 )  from '
		+ @tmp_table + '  ( nolock )  group by FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0) )  option (MAXDOP 1 ) '
	exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql )

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
lin_RPNPCDieLoc2
	do make cpc die location report ( group by class or level )
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCDieLoc2]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

return

/*
declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_type	smallint, '
		+ ' log_val	smallint, '
		+ ' x_loc		int, '
		+ ' y_loc 	int, '
		+ ' die_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num3, etc_num4,  location_x, location_y  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num3, etc_num4,  location_x, location_y ) ( select log_id, etc_num3, etc_num4, location_x, location_y '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  ) '
exec (@sql)


-- insert into report table

-- map 별 죽은 횟수  ( group by class )
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  x_loc, y_loc, die_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0), count( log_id ) from '
	+ @tmp_table + '  ( nolock )  group by etc_num3, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0) )  option (MAXDOP 1 ) '
exec (@sql )

-- map 별 죽은 횟수 ( group by level)
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  x_loc, y_loc, die_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0), count(log_id)   from '
	+ @tmp_table + '  ( nolock )  group by etc_num4, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0) )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

*/

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
lin_RPNPCDrop
	do make NPC drop item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCDrop]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_id	int, '
		+ ' item_sum	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor_account, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time > ''2003/10/29 10:0:0'' '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912 and act_time < ''2003/10/29 10:0:0''  ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912 and act_time > ''2003/10/29 10:0:0''  ) '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912 and act_time < ''2003/10/29 10:0:0''  ) '
exec (@sql)

-- insert into report table

-- 클래스 변경로그들을 다 저장
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_id, item_sum ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num8, sum(etc_num9 )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num8 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPNPCDrop2
	do make NPC drop item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCDrop2]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' npc_id	int,'
		+ ' item_id	int, '
		+ ' item_sum	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor_account, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time > ''2003/10/29 10:0:0'' '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time < ''2003/10/29 10:0:0'' ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912 and act_time > ''2003/10/29 10:0:0''  ) '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time < ''2003/10/29 10:0:0'' ) '
exec (@sql)

-- insert into report table

-- 
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  npc_id, item_id, item_sum ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', actor_account, etc_num8, sum(etc_num9 )  from '
	+ @tmp_table + ' ( nolock ) group by actor_account, etc_num8 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPNPCDropItem
	do make NPC drop item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCDropItem]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_type	int, '
		+ ' npc_id	int, '
		+ ' drop_count	int, '
		+ ' drop_amount	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end




-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, actor_account, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time > ''2003/10/29 10:0:0'' '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time < ''2003/10/29 10:0:0'' ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912 and act_time > ''2003/10/29 10:0:0''  ) '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, actor_account, etc_num8, etc_num9 ) ( select log_id, actor_account, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time < ''2003/10/29 10:0:0'' ) '
exec (@sql)


-- insert into report table

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_type, npc_id, drop_count, drop_amount ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num8, actor_account, count(log_id), sum(etc_num9)   from '
	+ @tmp_table + ' ( nolock )  group by etc_num8 , actor_account )  option (MAXDOP 1 ) '

exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql )

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
lin_RPNPCDropLoc
	do make NPC drop item for each map location report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCDropLoc]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' map_x	tinyint, '
		+ ' map_y	tinyint, '
		+ ' map_z	tinyint, '
		+ ' item_type	int, '
		+ ' drop_amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end



-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, location_x, location_y, etc_num8, etc_num9 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time > ''2003/10/29 10:0:0'' '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, location_x, location_y, etc_num8, etc_num9 ) ( select log_id, location_x, location_y, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time < ''2003/10/29 10:0:0'' ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, location_x, location_y, etc_num8, etc_num9 ) ( select log_id, location_x, location_y, etc_num8, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912 and act_time > ''2003/10/29 10:0:0''  ) '
exec (@sql)

set @sql = ' insert into ' + @tmp_table + ' ( log_id, location_x, location_y, etc_num8, etc_num9 ) ( select log_id, location_x, location_y, etc_num7, etc_num8 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 912  and act_time < ''2003/10/29 10:0:0'' ) '
exec (@sql)

-- insert into report table

-- npc drop
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  map_x, map_y,  item_type, drop_amount ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 20 + floor(location_x / 32768.0) , 18 + floor(location_y / 32768.0) , etc_num8, sum(etc_num9)  from '
	+ @tmp_table + ' group by 20 + floor(location_x / 32768.0), 18 + floor(location_y / 32768.0), etc_num8 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPNPCHunted
	do make # of NPC hunted
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPNPCHunted]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_val	int, '
		+ 'log_count 	int, '
		+ ' npc_level	smallint '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select target_account, etc_num10, etc_num7 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( target_account, etc_num10, etc_num7 ) ( select target_account, etc_num10, etc_num7  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  ) '
exec (@sql)




-- insert into report table

	-- new insert 
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_val, log_count , npc_level ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', target_account, count ( distinct etc_num10 ), etc_num7   from '
		+ @tmp_table + '  group by target_account , etc_num7  )  option (MAXDOP 1 ) '
	exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPPCDie
	do make pc die report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPCDie]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ 'log_count 	int, '
		+ 'char_count 	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id,  etc_num1, etc_num2, etc_num3, etc_num4, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1101  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id,  etc_num1, etc_num2, etc_num3, etc_num4, actor   ) ( select log_id,  etc_num1, etc_num2, etc_num3, etc_num4, actor    '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1101  ) '
exec (@sql)


-- insert into report table

-- race 별 죽은 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, count(log_id) , count(distinct actor)  from '
	+ @tmp_table + ' (nolock)  group by etc_num1  )  option (MAXDOP 1 ) '
exec (@sql )
-- sex 별 죽은 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count , char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2,  count(log_id) , count(distinct actor)  from '
	+ @tmp_table + ' (nolock) group by etc_num2   ) option (MAXDOP 1 ) '
exec (@sql )
-- class 별 죽은 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  log_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,   count(log_id)  , count(distinct actor) from '
	+ @tmp_table + '  ( nolock )  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )
-- level 별 죽은 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count , char_count  ) ( ' 
	+ ' select  ' + CAST(@logdate as varchar) + ', 4, etc_num4,   count(log_id)  , count(distinct actor)  from '
	+ @tmp_table + ' ( nolock )  group by etc_num4  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPPCDieLoc
	do make pc die location report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPCDieLoc]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_type	smallint, '
		+ ' x_loc		int, '
		+ ' y_loc 	int, '
		+ ' die_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id,  location_x, location_y into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1101  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id,  location_x, location_y  ) ( select log_id,  location_x, location_y   '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1101  ) '
exec (@sql)


-- insert into report table

-- map 별 죽은 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, x_loc, y_loc, die_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0), count(log_id) from  '
	+ ' ( select log_id, location_x, location_y from '
	+ @tmp_table  + ' ( nolock )  ) as R1 group by FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0) ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop  table ' + @tmp_table
exec (@sql)

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
lin_RPPCDieLoc2
	do make pc die location report ( group by class or level )
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-21
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPCDieLoc2]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_type	smallint, '
		+ ' log_val	smallint, '
		+ ' x_loc		int, '
		+ ' y_loc 	int, '
		+ ' die_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num3, etc_num4,location_x, location_y into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1101  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num3, etc_num4,location_x, location_y ) ( select log_id, etc_num3, etc_num4,location_x, location_y  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1101  ) '
exec (@sql)


-- insert into report table

-- map 별 죽은 횟수 ( class 별로 )
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, x_loc, y_loc, die_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0), count(log_id)  from '
	+ ' ( select log_id, etc_num3, location_x, location_y from '
	+ @tmp_table  + ' ( nolock )  ) as R1   group by etc_num3, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0) )  option (MAXDOP 1 ) '
exec (@sql )

-- map 별 죽은 횟수 ( level 별로 )
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, x_loc, y_loc, die_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0), count(log_id)  from '
	+ ' ( select log_id, etc_num4, location_x, location_y from  '
	+ @tmp_table + ' ( nolock ) ) as R1  group by etc_num4, FLOOR(location_x / 32768.0), FLOOR(location_y / 32768.0) ) option (MAXDOP 1 )  '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPPCKillNPC
	do make pc kill npc report ( processed data )
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-4-1
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPCKillNPC]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' target_account	int , '
		+ ' x		smallint, '
		+ ' y		smallint, '
		+ ' z		smallint, '
		+ ' race		tinyint, ' 
		+ ' class		tinyint, '
		+ ' pc_level	tinyint, '
		+ ' npc_level	tinyint, '
		+ ' time2die	smallint, ' 
		+ ' kill_count	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select target_account, location_x, location_y, location_z, etc_num1, etc_num3, etc_num4, etc_num7, etc_num10 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( target_account, location_x, location_y, location_z, etc_num1, etc_num3, etc_num4, etc_num7, etc_num10 ) ( select target_account, location_x, location_y, location_z, etc_num1, etc_num3, etc_num4, etc_num7 , etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 1112  ) '
exec (@sql)


-- insert into report table

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, target_account, x, y, z, race, class, pc_level, npc_level , time2die, kill_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', target_account, R_loc_x , R_loc_y , 0, etc_num1, etc_num3, etc_num4, avg(etc_num7), 0 , count( distinct ( etc_num10 ) ) from '
	+ ' ( select R_log_id = 1112, target_account, R_loc_x = FLOOR(location_x / 1024.0), R_loc_y = FLOOR(location_y / 1024.0) , etc_num1, etc_num3, etc_num4, etc_num7 , etc_num10 from '
	+ @tmp_table + ' ( nolock )  ) as R1 group by  target_account, R_loc_x , R_loc_y, etc_num1, etc_num3, etc_num4 )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPPCKillPC
	do make pc kill pc  stats
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-26
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPCKillPC]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' kill_type	smallint, '
		+ ' char_count	int, '
		+ ' kill_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  kill_type, char_count, kill_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 0, count ( distinct ( actor)  ) , count ( actor )  from '
		+ 'lin2log.dbo.' + @table_from + '  ( nolock )  where log_id = 1111  )  option (MAXDOP 1 ) '
	exec (@sql )


	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  kill_type, char_count, kill_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 1, count ( distinct ( target )  ) , count ( target )  from '
		+ 'lin2log.dbo.' + @table_from + '  ( nolock )  where log_id = 1111  )  option (MAXDOP 1 ) '
	exec (@sql )

	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  kill_type, char_count, kill_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 2, count ( distinct ( actor)  ) , count ( actor )  from '
		+ 'lin2log.dbo.' + @table_from + '  ( nolock )  where log_id = 1111  and etc_num6 > 0 )  option (MAXDOP 1 ) '
	exec (@sql )

	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  kill_type, char_count, kill_count ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 3, count ( distinct ( target )  ) , count ( target )  from '
		+ 'lin2log.dbo.' + @table_from + '  ( nolock )  where log_id = 1111  and etc_num6 > 0 )  option (MAXDOP 1 ) '
	exec (@sql )
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
lin_RPPlayAge
	do make play age report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-8-5
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPlayAge]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' age		int, '
		+ ' play_count	int, '
		+ ' play_time	money  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  age, play_count, play_time  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num2, count( distinct actor_account  ),  sum( cast ( etc_num4 as money) )  from  '
	+ ' ( select etc_num2, actor_account, etc_num4  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 804 ) as R1 group by etc_num2   )  option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPPlaySex
	do make play sexreport
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-8-5
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPlaySex]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(512)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' sex		int, '
		+ ' play_count	int, '
		+ ' play_time	money  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  sex , play_count, play_time  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num3, count( distinct ( actor_account) ),  sum( cast ( etc_num4 as money) )  from  '
	+ ' ( select etc_num3, actor_account,  etc_num4  '
	+ ' from lin2log.dbo.' + RTRIM(@table_from) + ' ( nolock ) where log_id = 804 ) as R1 group by etc_num3  )  option (MAXDOP 1 ) '
exec (@sql )

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
lin_RPPlayStat
	do make player report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-25
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPlayStat]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' snap_hour	smallint, '
		+ ' snap_level	smallint, '
		+ ' snap_count	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  snap_hour, snap_level, snap_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', datepart ( hh, act_time), etc_num5, count ( distinct ( actor ))  from '
	+ ' lin2log.dbo.' + @table_from  + ' ( nolock )  where log_id = 812 and datepart ( mi, act_time ) < 20  group by datepart( hh, act_time), etc_num5 ) option (MAXDOP 1 ) '

exec (@sql )
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
lin_RPPlayTime
	do make average play time
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-17
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPlayTime]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_type	smallint, '
		+ ' log_val	int, '
		+ ' log_count	bigint, '
		+ ' char_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 805  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, actor  ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, actor  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 805 ) '
exec (@sql)

-- insert into report table

-- race 별 플레이 시간
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1,  etc_num1, sum(etc_num5), count(distinct actor)  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num1  )  option (MAXDOP 1 )'
exec (@sql )

-- sex 별 플레이 시간
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2,  etc_num2, sum(etc_num5), count(distinct actor) from '
	+ @tmp_table + ' ( nolock )  group by etc_num2  )  option (MAXDOP 1 ) '
exec (@sql )

-- class 별 플레이 시간
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3,  etc_num3, sum(etc_num5), count(distinct actor) from '
	+ @tmp_table + ' ( nolock ) group by etc_num3  )  option (MAXDOP 1 ) '
exec (@sql )

-- level 별 플레이 시간
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val, log_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4,  etc_num4, sum(etc_num5), count(distinct actor) from '
	+ @tmp_table + ' ( nolock ) group by etc_num4  )  option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPPledgeUp
	do make pledge level up report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2004-2-25
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPledgeUp]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' lev		smallint, '
		+ ' lev_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  lev, lev_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num7, count( etc_num7)  from '
	+ ' lin2log.dbo.' + @table_from  + ' ( nolock )  where log_id = 215 and etc_num6 = 5 group by etc_num7 ) option (MAXDOP 1 ) '

exec (@sql )
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
lin_RPPrivateStore

INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-11-18
********************************************/
CREATE PROCEDURE [DBO].[lin_RPPrivateStore]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' race		int, '
		+ ' class		int, '
		+ ' level		int, '
		+ ' private_count		int, '
		+ ' private_time	 	int'
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 838  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 838 ) '
exec (@sql)

	-- race 별 사냥한 총 NPC수
	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  race, class, level, private_count, private_time ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num3, etc_num4, count(etc_num1), sum(etc_num5)   from  '
		+ @tmp_table  + ' ( nolock )  group by etc_num1, etc_num3, etc_num4 )  option (MAXDOP 1 ) '
	exec (@sql )

-- drop tmptable
set @sql = 'drop table ' + @tmp_table
exec ( @sql )
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
lin_RPRecipe
	do make recipe  report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-9-3
********************************************/
CREATE PROCEDURE [DBO].[lin_RPRecipe]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_type	int, '
		+ ' user_class	int, '
		+ ' user_level	int, '
		+ ' item_count	int, '
		+ ' item_amount	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num8, etc_num3, etc_num4, etc_num9  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 935  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num8, etc_num3, etc_num4, etc_num9 ) ( select log_id, etc_num8, etc_num3, etc_num4, etc_num9 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 935 ) '
exec (@sql)



-- insert into report table
-- levelup report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  item_type, user_class, user_level, item_count, item_amount  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num8, etc_num3, etc_num4, count(log_id), sum( etc_num9 ) from '
	+ @tmp_table + ' ( nolock )  group by etc_num8, etc_num3, etc_num4  )  option (MAXDOP 1 ) '

exec (@sql )


-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPSayCount
	do make say count report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-9-3
********************************************/
CREATE PROCEDURE [DBO].[lin_RPSayCount]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' log_time	datetime, '
		+ ' say_count	int, '
		+ ' say_size	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, act_time, etc_num1, etc_num2  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 832  '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, act_time, etc_num1, etc_num2 ) ( select log_id, act_time, etc_num1, etc_num2 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 832 ) '
exec (@sql)


-- insert into report table
-- levelup report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_time, say_count, say_size   ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', act_time, etc_num1, etc_num2  from '
	+ @tmp_table + ' ( nolock )  )  option (MAXDOP 1 ) '

exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPSellPrivate
	do make item sell in private store
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-06-02
********************************************/
CREATE PROCEDURE [DBO].[lin_RPSellPrivate]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' class_id	int,' 
		+ ' level		int, '
		+ ' item_id	int, '
		+ ' enchant_no	int, '
		+ ' sell_count	int, '
		+ ' sell_price	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num3, etc_num4, etc_num7, etc_num8, etc_num9, etc_num10 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 931 and etc_num8 <> 57   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num3, etc_num4, etc_num7, etc_num8, etc_num9, etc_num10 ) ( select log_id, etc_num3, etc_num4, etc_num7, etc_num8, etc_num9, etc_num10 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 931 and etc_num8 <> 57 ) '
exec (@sql)

-- insert into report table

-- 판매한  item
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date, class_id, level, item_id, enchant_no, sell_count, sell_price  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num3, etc_num4, etc_num8, etc_num7, sum(etc_num9), sum(etc_num10 * etc_num9 )  from '
	+ @tmp_table + ' ( nolock ) group by etc_num3, etc_num4, etc_num8, etc_num7 )  option (MAXDOP 1 ) '
exec (@sql )

set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPStand
	do make stand report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPStand]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' stand_count 	int , '
		+ ' sit_time 	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 822   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4,  etc_num5 ) ( select log_id,  etc_num1, etc_num2, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 822 ) '
exec (@sql)


-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  stand_count, sit_time ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1,  count( log_id ), sum(etc_num5)  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num1 ) option (MAXDOP 1 ) '
exec (@sql )

-- sex  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  stand_count, sit_time ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2,  count( log_id ), sum(etc_num5)  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num2 ) option (MAXDOP 1 ) '
exec (@sql )

-- class  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  stand_count, sit_time ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,  count( log_id ), sum(etc_num5)  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

-- level  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  stand_count, sit_time ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4,  count( log_id ), sum(etc_num5)  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num4 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPStopQuest
	do make stop quest
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-06-02
********************************************/
CREATE PROCEDURE [DBO].[lin_RPStopQuest]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' race		smallint, '
		+ ' class		smallint, '
		+ ' level		smallint, '
		+ ' quest_id	int, '
		+ ' quest_count	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num3, etc_num4, etc_num5 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 307   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num3, etc_num4, etc_num5 ) ( select log_id, etc_num1, etc_num3, etc_num4, etc_num5 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 307 ) '
exec (@sql)


-- insert into report table
-- begin quest report
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  race, class, level, quest_id, quest_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num1, etc_num3, etc_num4, etc_num5, count(log_id)  from '
	+ @tmp_table + ' ( nolock )  group by  etc_num1, etc_num3, etc_num4, etc_num5 ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmltable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPSvrStart
	do make server start, stop stats
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-19
********************************************/
CREATE PROCEDURE [DBO].[lin_RPSvrStart]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' svr_type	smallint, '
		+ ' start_type	smallint, '
		+ ' act_time	datetime '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  start_type,  svr_type, act_time  ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num1, act_time  from '
		+ 'lin2log.dbo.' + @table_from + '  ( nolock )  where log_id = 1305  )  option (MAXDOP 1 ) '
	exec (@sql )


	set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  start_type,  svr_type, act_time  ) ( ' 
		+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, act_time  from '
		+ 'lin2log.dbo.' + @table_from + '  ( nolock )  where log_id = 1306  )  option (MAXDOP 1 ) '
	exec (@sql )
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
lin_RPTradeGet
	do make trade get report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPTradeGet]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' trade_count 	int , '
		+ ' char_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 910   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 910 ) '
exec (@sql)

-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, count( log_id ) , count ( distinct actor )  from  '
	+ @tmp_table + ' ( nolock )  group by etc_num1  ) option (MAXDOP 1 ) '
exec (@sql )

-- sex  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, count( log_id ) , count ( distinct actor )  from  '
	+ @tmp_table + ' ( nolock )  group by etc_num2  ) option (MAXDOP 1 ) '
exec (@sql )

-- class  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, count( log_id ) , count ( distinct actor )  from  '
	+ @tmp_table + ' ( nolock )  group by etc_num3  ) option (MAXDOP 1 ) '
exec (@sql )

-- level  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count, char_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, count( log_id ) , count ( distinct actor )  from  '
	+ @tmp_table + ' ( nolock )  group by etc_num4  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPTradeGive
	do make trade give report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPTradeGive]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' trade_count 	int , '
		+ ' char_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 909   '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, actor '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 909 ) '
exec (@sql)


-- insert into report table

-- race 횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count , char_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, count( log_id)  , count(distinct actor )  from '
	+ @tmp_table + ' ( nolock )  group by etc_num1  ) option (MAXDOP 1 ) '
exec (@sql )

-- sex  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count , char_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, count( log_id)  , count(distinct actor )  from '
	+ @tmp_table + ' ( nolock )  group by etc_num2  ) option (MAXDOP 1 ) '
exec (@sql )

-- class  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count , char_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, count( log_id)  , count(distinct actor )  from '
	+ @tmp_table + ' ( nolock )  group by etc_num3 ) option (MAXDOP 1 ) '
exec (@sql )

-- level  횟수
set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  trade_count , char_count  ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, count( log_id)  , count(distinct actor )  from '
	+ @tmp_table + ' ( nolock )  group by etc_num4  ) option (MAXDOP 1 ) '
exec (@sql )

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec ( @sql )

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
lin_RPTradeItem
	do make trade item report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-10-31
********************************************/
CREATE PROCEDURE [DBO].[lin_RPTradeItem]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' level_from	int, '
		+ ' level_to	int, '
		+ ' item_type	int, '
		+ ' trade_no	int, '
		+ ' trade_count	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num4, etc_num6, etc_num8, etc_num9  into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 910 '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num4, etc_num6, etc_num8, etc_num9   ) ( select log_id, etc_num4, etc_num6, etc_num8, etc_num9  '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 910 ) '
exec (@sql)

-- insert into report table

set @sql = 'insert into ' + RTRIM(@table_to) + ' ( log_date,  level_from, level_to, item_type, trade_no,  trade_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', etc_num4, etc_num6, etc_num8,  count( etc_num9 ), amount=sum(etc_num9 )  from '
	+ @tmp_table  + ' ( nolock )  group by etc_num4, etc_num6, etc_num8  )  option (MAXDOP 1 ) '

exec (@sql )

-- 
set @sql = ' drop  table ' + @tmp_table
exec ( @sql )

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
lin_RPUseSkill
	do make use skill report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPUseSkill]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' skill_id 	int , '
		+ ' skill_level 	smallint , '
		+ ' use_count 	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- insert into report table

-- make tmptable
set @table_from = replace ( @table_from, 'data0', 'data2' )
set @sql = ' select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6 into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 403 and ( etc_num7 is null or etc_num7 = 0 ) '
exec (@sql)

set @table_from = replace ( @table_from, 'data2', 'data' )
set @sql = ' insert into ' + @tmp_table + ' ( log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6 ) ( select log_id, etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6 '
	+ ' from lin2log.dbo.' + @table_from  + ' ( nolock) where log_id = 403 and ( etc_num7 is null or etc_num7 = 0 ) ) '
exec (@sql)


-- race 횟수
set @sql = ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, use_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, etc_num5, etc_num6, count ( log_id ) from    '
	+ @tmp_table  + ' ( nolock ) group by etc_num5, etc_num6, etc_num1   )  option (MAXDOP 1 )'
exec (@sql )

-- sex  횟수
set @sql =  ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, use_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, etc_num5, etc_num6, count ( log_id ) from    '
	+ @tmp_table  + ' ( nolock ) group by etc_num5, etc_num6, etc_num2   )  option (MAXDOP 1 )'
exec (@sql )

-- class  횟수
set @sql =  ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, use_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3,  etc_num5, etc_num6, count ( log_id ) from    '
	+ @tmp_table  + ' ( nolock ) group by etc_num5, etc_num6, etc_num3  )  option (MAXDOP 1 )'
exec (@sql )

-- level  횟수
set @sql = ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  skill_id, skill_level, use_count ) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, etc_num5, etc_num6, count ( log_id ) from    '
	+ @tmp_table  + ' ( nolock ) group by etc_num5, etc_num6, etc_num4  )  option (MAXDOP 1 )'
exec ( @sql)

-- drop tmptable
set @sql = ' drop table ' + @tmp_table
exec (@sql)

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
lin_RPWareDeposit
	do make warehouse deposit report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPWareDeposit]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' deposit_count 	int, '
		+ ' char_count 	int  '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end


-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end


-- insert into report table

-- race 횟수
set @sql = ' select log_id, etc_num1, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from +  ' (nolock) where log_id = 903  '
	+ ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  deposit_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, count(log_id)  , count ( distinct actor)  from '
	+ @tmp_table  + ' ( nolock ) group by etc_num1  ) option (MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table
exec (@sql )

-- sex  횟수
set @sql = ' select log_id, etc_num2, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from +  ' (nolock) where log_id = 903  '
	+ ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  deposit_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, count(log_id)  , count ( distinct actor)  from '
	+ @tmp_table  + ' ( nolock ) group by etc_num2  ) option (MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table

exec (@sql )

-- class  횟수
set @sql = ' select log_id, etc_num3, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from +  ' (nolock) where log_id = 903  '
	+ ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  deposit_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, count(log_id)  , count ( distinct actor)  from '
	+ @tmp_table  + ' ( nolock ) group by etc_num3  ) option (MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table

exec (@sql )

-- level  횟수
set @sql = ' select log_id, etc_num4, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from +  ' (nolock) where log_id = 903  '
	+ ' insert into ' + RTRIM(@table_to) + ' ( log_date,  log_type, log_val,  deposit_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, count(log_id)  , count ( distinct actor)  from '
	+ @tmp_table  + ' ( nolock ) group by etc_num4  ) option (MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table

exec (@sql )

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
lin_RPWareRetrieve
	do make warehouse retrieve report
INPUT
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

OUTPUT

return
made by
	young
date
	2003-3-28
********************************************/
CREATE PROCEDURE [DBO].[lin_RPWareRetrieve]
	@table_from	varchar(60),
	@table_to	varchar(60),
	@logdate	int

AS
SET NOCOUNT ON

declare @sql varchar(4000)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ 'log_type	smallint, '
		+ 'log_val	int, '
		+ ' retrieve_count 	int , '
		+ ' char_count	int '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- check tmp table
declare @tmp_table varchar(512)
set @tmp_table = 'dbo.tmp' + @table_to

set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''tmp' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT > 0)
begin
	set @sql = ' drop table dbo.tmp' + @table_to
	exec (@sql)
end

-- insert into report table

-- race 횟수
set @sql = ' select log_id, etc_num1, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from + ' ( nolock ) where log_id = 904  '
	+ ' insert into ' + @table_to + ' ( log_date,  log_type, log_val,  retrieve_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 1, etc_num1, count(log_id) , count( distinct  actor )   from '
	+ @tmp_table + ' ( nolock) group by etc_num1 ) option ( MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table
exec (@sql )

-- sex  횟수
set @sql =  ' select log_id, etc_num2, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from + ' ( nolock ) where log_id = 904  '
	+ ' insert into ' + @table_to + ' ( log_date,  log_type, log_val,  retrieve_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 2, etc_num2, count(log_id) , count( distinct  actor )   from '
	+ @tmp_table + ' ( nolock) group by etc_num2 ) option ( MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table

exec (@sql )

-- class  횟수
set @sql =  ' select log_id, etc_num3, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from + ' ( nolock ) where log_id = 904  '
	+ ' insert into ' + @table_to + ' ( log_date,  log_type, log_val,  retrieve_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 3, etc_num3, count(log_id) , count( distinct  actor )   from '
	+ @tmp_table + ' ( nolock) group by etc_num3 ) option ( MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table

exec (@sql )

-- level  횟수

set @sql =   ' select log_id, etc_num4, actor into ' + @tmp_table
	+ ' from lin2log.dbo.' + @table_from + ' ( nolock ) where log_id = 904  '
	+ ' insert into ' + @table_to + ' ( log_date,  log_type, log_val,  retrieve_count , char_count) ( ' 
	+ ' select ' + CAST(@logdate as varchar) + ', 4, etc_num4, count(log_id) , count( distinct  actor )   from '
	+ @tmp_table + ' ( nolock) group by etc_num4 ) option ( MAXDOP 1 ) '
	+ ' drop table ' + @tmp_table

exec (@sql )

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
lin_RPWorldSnap
	do make snap shot report. item, class, level
INPUT
	@db_server	varchar(30),
	@user_id	varchar(30),
	@user_pass	varchar(30),
	@world_id	int

OUTPUT

return
made by
	young
date
	2003-10-31
********************************************/



CREATE PROCEDURE [DBO].[lin_RPWorldSnap]
	@db_server	varchar(30),
	@user_id	varchar(30),
	@user_pass	varchar(30),
	@world_id	int

AS

SET NOCOUNT ON

declare @sql varchar(4000)
declare @dtnow datetime
declare @dtyear int
declare @dtmonth int
declare @dtday int
declare @logdate int
declare @table_to nvarchar(50)

set @dtnow = getdate()
set @dtyear = datepart( yyyy, @dtnow)
set @dtmonth = datepart( mm, @dtnow)
set @dtday = datepart( day, @dtnow)
set @logdate = @dtyear * 10000 + @dtmonth * 100 + @dtday

--------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------
-- item snap shot
--------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------
if @dtmonth < 10
	set @table_to = 'R' + cast( @dtyear as varchar) + '_0'  + cast( @dtmonth as varchar) + '_SNAPITEM_' + cast( @world_id as varchar)
else
	set @table_to = 'R' + cast( @dtyear as varchar) + '_'  + cast( @dtmonth as varchar) + '_SNAPITEM_' + cast( @world_id as varchar)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' item_type	int, '
		+ ' warehouse	int, '
		+ ' amount	money '
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

set @sql =   '   insert into ' + RTRIM(@table_to) + ' ( log_date, item_type, warehouse, amount ) ( ' 
	+ ' select  * '
	+ ' from OPENROWSET ( ''SQLOLEDB'', ''' + @db_server + ''';''' + @user_id + ''';''' + @user_pass  + ''',  '
	+ ' ''select log_date=' +  CAST( @logdate as NVARCHAR) + ' , item_type, warehouse, amount=sum( cast ( amount as money) ) from lin2world.dbo.user_item  (nolock) where char_id >1 group by item_type, warehouse'' )  )'

exec (@sql )


--------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------
-- level  snap shot
--------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------
if @dtmonth < 10
	set @table_to = 'R' + cast( @dtyear as varchar) + '_0'  + cast( @dtmonth as varchar) + '_SNAPLEV_' + cast( @world_id as varchar)
else
	set @table_to = 'R' + cast( @dtyear as varchar) + '_'  + cast( @dtmonth as varchar) + '_SNAPLEV_' + cast( @world_id as varchar)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' lev		int, '
		+ ' lev_count	int ' 
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table

set @sql = '  insert into ' + RTRIM(@table_to) + ' ( log_date, lev, lev_count ) ( ' 
	+ ' select  * '
	+ ' from OPENROWSET ( ''SQLOLEDB'', ''' + @db_server + ''';''' + @user_id + ''';''' + @user_pass  + ''',  '
	+ ' ''select log_date=' +  CAST( @logdate as NVARCHAR) + ' , lev, count( lev )  from lin2world.dbo.user_data  (nolock) where char_id >1 group by lev '' )  )'
exec (@sql )


--------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------
-- class  snap shot
--------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------
if @dtmonth < 10
	set @table_to = 'R' + cast( @dtyear as varchar) + '_0'  + cast( @dtmonth as varchar) + '_SNAPCLASS_' + cast( @world_id as varchar)
else
	set @table_to = 'R' + cast( @dtyear as varchar) + '_'  + cast( @dtmonth as varchar) + '_SNAPCLASS_' + cast( @world_id as varchar)

-- check table whether @table_to is exists or not
set @sql = 'select * from lin2report.dbo.sysobjects (nolock) where name = ''' + @table_to + ''''
exec (@sql)

if (@@ROWCOUNT = 0)
begin
	set @sql = 'CREATE TABLE dbo.' + @table_to + ' (' 
		+ ' log_date	int, '
		+ ' class		int, '
		+ ' class_count	int ' 
		+ ' ) '
	exec (@sql)

	set @sql = 'CREATE INDEX IX_' + @table_to + '_1 on dbo.' + @table_to + ' (log_date) '
	exec (@sql)
end
else begin
	set @sql = 'delete from dbo.' + @table_to + ' where log_date = ' + CAST(@logdate as varchar)
	exec (@sql)
end

-- insert into report table

set @sql = '  insert into ' + RTRIM(@table_to) + ' ( log_date, class, class_count ) ( ' 
	+ ' select  * '
	+ ' from OPENROWSET ( ''SQLOLEDB'', ''' + @db_server + ''';''' + @user_id + ''';''' + @user_pass  + ''',  '
	+ ' ''select log_date=' +  CAST( @logdate as NVARCHAR) + ' , class, count( class )  from lin2world.dbo.user_data  (nolock) where char_id >1 group by class '' )  )'
exec (@sql )

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

