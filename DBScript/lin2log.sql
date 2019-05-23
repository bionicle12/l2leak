if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_BulkInsert]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_BulkInsert]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_CheckLogTimeTable2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_CheckLogTimeTable2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DropLogTable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DropLogTable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DropLogTable2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DropLogTable2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeChatLogTable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeChatLogTable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeItemLogTable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeItemLogTable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeLogTable]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeLogTable]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetInserted]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetInserted]
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE dbo.lin_BulkInsert 
(
	@log_table	varchar(512),
	@log_file	varchar(128)
)
AS

set nocount on

declare @sql varchar(1024)

set @sql = ' set nocount on'
	+ ' BULK INSERT ' + @log_table + ' FROM ''' + @log_file + ''' WITH ( MAXERRORS = 65535, FIELDTERMINATOR = '','',  ROWTERMINATOR = ''\n'' ) '
	+ ' select @@ROWCOUNT  ' 
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
lin_CheckLogTimeTable2
	do check whether real time log table is exist or not
INPUT
	@strDate varchar(16),
	@nWorld  int
OUTPUT
	
return
made by
	young
date
	2002-11-11
********************************************/
CREATE PROCEDURE [DBO].[lin_CheckLogTimeTable2]
(
	@strDate varchar(16),
	@nWorld  int
)
AS
SET NOCOUNT ON

declare @table_name varchar(60)
declare @table2_name varchar(60)
declare @view_name varchar(60)
declare @sql varchar(2048)

-- check log_realtime
set @table_name = @strDate + 'log_realtime_' + cast (@nWorld as varchar)
set @sql = 'select * from sysobjects (nolock) where name = '''+ @table_name + ''''

exec ( @sql)
if ( @@ROWCOUNT = 0) 
begin
	set @sql = 'exec lin_MakeLogTable ''' + @table_name + ''''
	exec (@sql)
end

-- check log_audit
set @table_name = @strDate + 'log_audit_' + cast (@nWorld as varchar)
set @sql = 'select * from sysobjects (nolock) where name = '''+ @table_name + ''''
exec ( @sql)
if ( @@ROWCOUNT = 0) 
begin
	set @sql = 'exec lin_MakeLogTable ''' + @table_name + ''''
	exec (@sql)
end

-- check log_data ( store 0~12 hour log)
set @table_name = @strDate + 'log_data_' + cast (@nWorld as varchar)
set @sql = 'select * from sysobjects (nolock) where name = '''+ @table_name + ''''
exec ( @sql)
if ( @@ROWCOUNT = 0) 
begin
	set @sql = 'exec lin_MakeLogTable ''' + @table_name + ''''
	exec (@sql)
end

-- check log_data2 ( store 12~24 hour log)
set @table2_name = @strDate + 'log_data2_' + cast (@nWorld as varchar)
set @sql = 'select * from sysobjects (nolock) where name = '''+ @table2_name + ''''
exec ( @sql)
if ( @@ROWCOUNT = 0) 
begin
	set @sql = 'exec lin_MakeLogTable ''' + @table2_name + ''''
	exec (@sql)
end

-- check log_data0 ( view )
set @view_name = @strDate + 'log_data0_' + cast (@nWorld as varchar)
set @sql = 'select * from sysobjects (nolock) where name = '''+ @view_name + ''''
exec ( @sql)
if ( @@ROWCOUNT = 0) 
begin
--	set @sql = 'exec lin_MakeLogTable ''' + @table_name + ''''
	set @sql = 'CREATE VIEW dbo.' + @view_name + '  ( ' 
		+ ' act_time,  log_id, actor, actor_account, target, target_account, location_x, location_y, location_z, ' 
		+ 'etc_str1, etc_str2, etc_str3,  ' 
		+ 'etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10, ' 
		+ 'STR_actor, STR_actor_account, STR_target, STR_target_account, item_id ' 
		+ ' ) AS ' 
		+ ' SELECT  act_time,  log_id, actor, actor_account, target, target_account, location_x, location_y, location_z, '
		+ ' etc_str1, etc_str2, etc_str3,  ' 
		+ ' etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10, '
		+ ' STR_actor, STR_actor_account, STR_target, STR_target_account, item_id ' 
		+ ' from   ' + @table_name  + '  (nolock) UNION ALL '
		+ ' SELECT  act_time,  log_id, actor, actor_account, target, target_account, location_x, location_y, location_z, '
		+ ' etc_str1, etc_str2, etc_str3,  '
		+ ' etc_num1, etc_num2, etc_num3, etc_num4, etc_num5, etc_num6, etc_num7, etc_num8, etc_num9, etc_num10, '
		+ ' STR_actor, STR_actor_account, STR_target, STR_target_account, item_id '
		+ ' from   ' + @table2_name + '  (nolock)  '
	exec (@sql)
end

-- check chat 
set @table_name = @strDate + 'log_chat_' + cast (@nWorld as varchar)
set @sql = 'select * from sysobjects (nolock) where name = '''+ @table_name + ''''
exec ( @sql)
if ( @@ROWCOUNT = 0) 
begin
	set @sql = 'exec lin_MakeChatLogTable ''' + @table_name + ''''
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






CREATE PROCEDURE dbo.lin_DropLogTable
	@drop_date	datetime,
	@drop_world	int
AS

if @drop_date is null
begin
	set @drop_date = getdate()
	set @drop_date = dateadd(d, -30, getdate())
end

DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)
DECLARE @logdate int

set @nyear = datepart(yyyy, @drop_date)
set @nmonth = datepart(mm, @drop_date)
set @nday = datepart(dd, @drop_date)

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
declare @sql varchar (1024)


set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data0_' + cast ( @drop_world as varchar)
set @sql = ' drop view ' + @table_from

exec (@sql)


set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data_' + cast ( @drop_world as varchar)
set @sql = ' drop table ' + @table_from

exec (@sql)


set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_data2_' + cast ( @drop_world as varchar)
set @sql = ' drop table ' + @table_from

exec (@sql)


set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_chat_' + cast ( @drop_world as varchar)
set @sql = ' drop table ' + @table_from

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




CREATE PROCEDURE dbo.lin_DropLogTable2
	@drop_date	datetime,
	@drop_world	int
AS

if @drop_date is null
begin
	set @drop_date = getdate()
	set @drop_date = dateadd(d, -30, getdate())
end

DECLARE @nyear int
DECLARE @nmonth int
DECLARE @nday int
DECLARE @stryear varchar(10)
DECLARE @strmonth varchar(10)
DECLARE @strday varchar(10)
DECLARE @str_report varchar(32)
DECLARE @logdate int

set @nyear = datepart(yyyy, @drop_date)
set @nmonth = datepart(mm, @drop_date)
set @nday = datepart(dd, @drop_date)

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
declare @sql varchar (1024)


set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_audit_' + cast ( @drop_world as varchar)
set @sql = ' drop table ' + @table_from
exec (@sql)

set @table_from = 'L' + @stryear  + '_' + @strmonth + '_' + @strday + '_log_realtime_' + cast ( @drop_world as varchar)
set @sql = ' drop table ' + @table_from
exec (@sql)





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
lin_MakeChatLogTable
	do make whether log table is exist or not
INPUT
	@table_name varchar(60)
OUTPUT
	
return
made by
	young
date
	2003-09-19
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeChatLogTable]
(
	@table_name varchar(60)
)
AS
SET NOCOUNT ON

declare @sql varchar(1024)

set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
	+ 'act_time  datetime NULL ,' 
	+ 'log_id  smallint NULL ,' 
	+ 'actor  int  NULL , ' 
	+ 'target  int NULL , ' 
	+ 'location_x  int NULL , ' 
	+ 'location_y  int NULL , ' 
	+ 'location_z  int NULL , ' 
	+ 'say varchar (256) NULL , ' 
	+ 'STR_actor  varchar (32) NULL , ' 
	+ 'STR_target  varchar (32) NULL  '
 	+ ' )'

exec (@sql)

set @sql = 'CREATE NONCLUSTERED INDEX IX_' + @table_name + '_ACTOR on dbo.' + @table_name + ' ( actor , log_id   )   WITH FILLFACTOR = 90 ON [PRIMARY]  '
exec (@sql)

set @sql = 'CREATE NONCLUSTERED INDEX IX_' + @table_name + '_TARGET on dbo.' + @table_name + ' ( target , log_id   )  WITH FILLFACTOR = 90 ON [PRIMARY]   '
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
lin_MakeItemLogTable
	do make whether log table is exist or not
INPUT
	@table_name varchar(60)
OUTPUT
	
return
made by
	young
date
	2002-11-11
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeItemLogTable]
(
	@table_name varchar(60)
)
AS
SET NOCOUNT ON

declare @sql varchar(1024)

set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
	+ 'act_time  datetime NULL ,' 
	+ 'log_id  smallint NULL ,' 
	+ 'item_id  int NULL , ' 
	+ 'item_type  int NULL , ' 
	+ 'actor  varchar(32)  NULL , ' 
	+ 'actor_account  varchar(32)  NULL , ' 
	+ 'target  varchar(32)  NULL , ' 
	+ 'target_account  varchar(32)  NULL , ' 
	+ 'location_x  int NULL , ' 
	+ 'location_y  int NULL , ' 
	+ 'location_z  int NULL , ' 
	+ 'etc_num1  int NULL , ' 
	+ 'etc_num2  int NULL , ' 
	+ 'etc_num3  int NULL , ' 
	+ 'etc_num4  int NULL , ' 
	+ 'etc_num5  int NULL , ' 
	+ 'etc_num6  int NULL , ' 
	+ 'etc_num7  int NULL , ' 
	+ 'etc_num8  int NULL  ' 
	+ ' )'

exec (@sql)


set @sql = 'CREATE INDEX IX_' + @table_name + '_1 on dbo.' + @table_name + ' (log_id) '
exec (@sql)

set @sql = 'CREATE INDEX IX_' + @table_name + '_2 on dbo.' + @table_name + ' (item_id)  '
exec (@sql)

set @sql = 'CREATE INDEX IX_' + @table_name + '_3 on dbo.' + @table_name + ' (item_type) '
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
lin_MakeLogTable
	do make whether log table is exist or not
INPUT
	@table_name varchar(60)
OUTPUT
	
return
made by
	young
date
	2002-11-11
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeLogTable]
(
	@table_name varchar(60)
)
AS
SET NOCOUNT ON

declare @sql varchar(1024)

set @sql = 'CREATE TABLE dbo.' + @table_name + ' (' 
	+ 'act_time  datetime NULL ,' 
	+ 'log_id  smallint NULL ,' 
	+ 'actor  int  NULL , ' 
	+ 'actor_account  int  NULL , ' 
	+ 'target  int NULL , ' 
	+ 'target_account  int NULL , ' 
	+ 'location_x  int NULL , ' 
	+ 'location_y  int NULL , ' 
	+ 'location_z  int NULL , ' 
	+ 'etc_str1  varchar (200) NULL , ' 
	+ 'etc_str2  varchar (50) NULL , ' 
	+ 'etc_str3  varchar (50) NULL , ' 
	+ 'etc_num1  float NULL , ' 
	+ 'etc_num2  float NULL , ' 
	+ 'etc_num3  int NULL , ' 
	+ 'etc_num4  int NULL , ' 
	+ 'etc_num5  int NULL , ' 
	+ 'etc_num6  int NULL , ' 
	+ 'etc_num7  int NULL , ' 
	+ 'etc_num8  int NULL , ' 
	+ 'etc_num9  int NULL , ' 
	+ 'etc_num10  int NULL,'
	+ 'STR_actor  varchar (48) NULL , ' 
	+ 'STR_actor_account  varchar (32) NULL , ' 
	+ 'STR_target  varchar (48) NULL , ' 
	+ 'STR_target_account  varchar (32) NULL,  ' 
	+ 'item_id int NULL'
	+ ' )'

exec (@sql)

set @sql = 'CREATE CLUSTERED INDEX IX_' + @table_name + '_ACTOR on dbo.' + @table_name + ' ( log_id, actor ) WITH FILLFACTOR = 90 ON [PRIMARY]  '
exec (@sql)

set @sql = 'CREATE NONCLUSTERED INDEX IX_' + @table_name + '_ITEMTYPE on dbo.' + @table_name + ' ( actor , log_id   ) WITH FILLFACTOR = 90 ON [PRIMARY]  '
exec (@sql)

set @sql = 'CREATE NONCLUSTERED INDEX IX_' + @table_name + '_ITEMID on dbo.' + @table_name + ' ( item_id ) WITH FILLFACTOR = 90 ON [PRIMARY]  '
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
lin_SetInserted
	insert or update log file as inserted
INPUT
	@log_file	nvarchar(255),
	@log_table	nvarchar(50),
	@log_year	int,
	@log_month	int,
	@log_day	int,
	@log_hour	int,
	@log_ip		int,
	@log_svr	nvarchar(20),
	@log_inout	nvarchar(20),
	@rowsprocessed int
OUTPUT

return
made by
	young
date
	2002-10-14
********************************************/
CREATE PROCEDURE [DBO].[lin_SetInserted]
(
	@log_file	nvarchar(255),
	@log_table	nvarchar(50),
	@log_year	int,
	@log_month	int,
	@log_day	int,
	@log_hour	int,
	@log_ip		int,
	@log_svr	nvarchar(20),
	@log_inout	nvarchar(20),
	@rowsprocessed int,
	@process_time int  = 0
)
AS
SET NOCOUNT ON

insert into log_insert( log_file, log_table, rowsprocessed, log_year, log_month, log_day, log_hour, log_ip, log_svr, log_inout, inserted, process_time )
values
(@log_file, @log_table, @rowsprocessed, @log_year, @log_month, @log_day, @log_hour, @log_ip, @log_svr, @log_inout, 1, @process_time )






GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

