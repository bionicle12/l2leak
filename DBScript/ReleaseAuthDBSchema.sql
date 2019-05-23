if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ap_GPwd]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[ap_GPwd]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ap_GStat]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[ap_GStat]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ap_GUserTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[ap_GUserTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ap_SLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[ap_SLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ap_SUserTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[ap_SUserTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[l2p_TempCreateAccount]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[l2p_TempCreateAccount]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[block_msg]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[block_msg]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[block_reason_code]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[block_reason_code]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[gm_illegal_login]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[gm_illegal_login]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[item_code]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[item_code]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[server]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[server]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[ssn]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[ssn]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_account]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_account]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_auth]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_auth]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_count]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_count]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_info]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_info]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[user_time]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[user_time]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[worldstatus]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[worldstatus]
GO

CREATE TABLE [dbo].[block_msg] (
	[uid] [int] NULL ,
	[account] [varchar] (14) NOT NULL ,
	[msg] [varchar] (50) NULL ,
	[reason] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[block_reason_code] (
	[block_reason] [int] NOT NULL ,
	[block_desc] [varchar] (50) NOT NULL ,
	[flag] [tinyint] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[gm_illegal_login] (
	[account] [varchar] (15) NOT NULL ,
	[try_date] [datetime] NOT NULL ,
	[ip] [varchar] (15) NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[item_code] (
	[item_id] [int] NOT NULL ,
	[name] [varchar] (20) NOT NULL ,
	[duration] [int] NOT NULL ,
	[active_date] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[server] (
	[id] [int] NOT NULL ,
	[name] [varchar] (25) NOT NULL ,
	[ip] [varchar] (15) NOT NULL ,
	[inner_ip] [varchar] (15) NOT NULL ,
	[ageLimit] [tinyint] NOT NULL ,
	[pk_flag] [tinyint] NOT NULL ,
	[kind] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[ssn] (
	[ssn] [char] (13) NOT NULL ,
	[name] [varchar] (15) NOT NULL ,
	[email] [varchar] (50) NOT NULL ,
	[newsletter] [tinyint] NOT NULL ,
	[job] [int] NOT NULL ,
	[phone] [varchar] (16) NOT NULL ,
	[mobile] [varchar] (20) NULL ,
	[reg_date] [datetime] NOT NULL ,
	[zip] [varchar] (6) NOT NULL ,
	[addr_main] [varchar] (255) NOT NULL ,
	[addr_etc] [varchar] (255) NOT NULL ,
	[account_num] [tinyint] NOT NULL ,
	[status_flag] [int] NOT NULL ,
	[final_news_date] [datetime] NULL ,
	[master] [varchar] (14) NULL ,
	[valid_email_date] [datetime] NULL ,
	[final_master_date] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_account] (
	[uid] [int] IDENTITY (1, 1) NOT NULL ,
	[account] [varchar] (14) NOT NULL ,
	[pay_stat] [int] NOT NULL ,
	[login_flag] [int] NOT NULL ,
	[warn_flag] [int] NOT NULL ,
	[block_flag] [int] NOT NULL ,
	[block_flag2] [int] NOT NULL ,
	[block_end_date] [datetime] NULL ,
	[last_login] [datetime] NULL ,
	[last_logout] [datetime] NULL ,
	[subscription_flag] [int] NOT NULL ,
	[last_world] [tinyint] NULL ,
	[last_game] [int] NULL ,
	[last_ip] [varchar] (15) NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_auth] (
	[account] [varchar] (14) NOT NULL ,
	[password] [binary] (16) NOT NULL ,
	[quiz1] [varchar] (255) NOT NULL ,
	[quiz2] [varchar] (255) NOT NULL ,
	[answer1] [binary] (32) NOT NULL ,
	[answer2] [binary] (32) NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_count] (
	[record_time] [datetime] NOT NULL ,
	[server_id] [tinyint] NOT NULL ,
	[world_user] [smallint] NOT NULL ,
	[limit_user] [smallint] NOT NULL ,
	[auth_user] [int] NOT NULL ,
	[wait_user] [int] NOT NULL ,
	[dayofweek] [tinyint] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_info] (
	[account] [varchar] (14) NOT NULL ,
	[create_date] [datetime] NOT NULL ,
	[ssn] [varchar] (13) NOT NULL ,
	[status_flag] [tinyint] NOT NULL ,
	[kind] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[user_time] (
	[uid] [int] NOT NULL ,
	[account] [varchar] (14) NOT NULL ,
	[present_time] [int] NOT NULL ,
	[next_time] [int] NULL ,
	[total_time] [int] NOT NULL ,
	[op_date] [datetime] NOT NULL ,
	[flag] [tinyint] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[worldstatus] (
	[idx] [int] NOT NULL ,
	[server] [varchar] (50) NOT NULL ,
	[status] [tinyint] NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[item_code] WITH NOCHECK ADD 
	CONSTRAINT [PK_item_code] PRIMARY KEY  CLUSTERED 
	(
		[item_id]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[ssn] WITH NOCHECK ADD 
	CONSTRAINT [PK_ssn] PRIMARY KEY  CLUSTERED 
	(
		[ssn]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[user_account] WITH NOCHECK ADD 
	CONSTRAINT [PK_user_account_] PRIMARY KEY  CLUSTERED 
	(
		[account]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[user_auth] WITH NOCHECK ADD 
	CONSTRAINT [PK_user_auth] PRIMARY KEY  CLUSTERED 
	(
		[account]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[user_info] WITH NOCHECK ADD 
	CONSTRAINT [PK_user_info] PRIMARY KEY  CLUSTERED 
	(
		[account]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[user_time] WITH NOCHECK ADD 
	CONSTRAINT [PK_user_time] PRIMARY KEY  CLUSTERED 
	(
		[uid]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[worldstatus] WITH NOCHECK ADD 
	CONSTRAINT [PK_worldstatus] PRIMARY KEY  CLUSTERED 
	(
		[idx]
	) WITH  FILLFACTOR = 90  ON [PRIMARY] 
GO

 CREATE  CLUSTERED  INDEX [IX_block_msg] ON [dbo].[block_msg]([uid]) ON [PRIMARY]
GO

ALTER TABLE [dbo].[gm_illegal_login] WITH NOCHECK ADD 
	CONSTRAINT [DF_gm_illegal_login_try_date] DEFAULT (getdate()) FOR [try_date]
GO

ALTER TABLE [dbo].[server] WITH NOCHECK ADD 
	CONSTRAINT [DF_server_ageLimit] DEFAULT (0) FOR [ageLimit],
	CONSTRAINT [DF_server_pk_flag] DEFAULT (0) FOR [pk_flag],
	CONSTRAINT [DF_server_kind] DEFAULT (0) FOR [kind]
GO

ALTER TABLE [dbo].[ssn] WITH NOCHECK ADD 
	CONSTRAINT [DF_ssn_newsletter] DEFAULT (0) FOR [newsletter],
	CONSTRAINT [DF_ssn_reg_date] DEFAULT (getdate()) FOR [reg_date],
	CONSTRAINT [DF_ssn_account_num] DEFAULT (0) FOR [account_num],
	CONSTRAINT [DF_ssn_status_flag] DEFAULT (0) FOR [status_flag],
	CONSTRAINT [DF_ssn_final_master_date] DEFAULT (getdate()) FOR [final_master_date]
GO

ALTER TABLE [dbo].[user_account] WITH NOCHECK ADD 
	CONSTRAINT [DF_user_account__pay_stat] DEFAULT (0) FOR [pay_stat],
	CONSTRAINT [DF_user_account__login_flag] DEFAULT (0) FOR [login_flag],
	CONSTRAINT [DF_user_account__warn_flag] DEFAULT (0) FOR [warn_flag],
	CONSTRAINT [DF_user_account__block_flag] DEFAULT (0) FOR [block_flag],
	CONSTRAINT [DF_user_account__block_flag2] DEFAULT (0) FOR [block_flag2],
	CONSTRAINT [DF_user_account_subscription_flag] DEFAULT (0) FOR [subscription_flag]
GO

ALTER TABLE [dbo].[user_count] WITH NOCHECK ADD 
	CONSTRAINT [DF_user_count_record_time] DEFAULT (getdate()) FOR [record_time],
	CONSTRAINT [DF_user_count_dayofweek] DEFAULT (datepart(weekday,getdate())) FOR [dayofweek]
GO

ALTER TABLE [dbo].[user_info] WITH NOCHECK ADD 
	CONSTRAINT [DF_user_info_create_date] DEFAULT (getdate()) FOR [create_date],
	CONSTRAINT [DF_user_info_status_flag] DEFAULT (0) FOR [status_flag],
	CONSTRAINT [DF_user_info_kind] DEFAULT (0) FOR [kind]
GO

ALTER TABLE [dbo].[worldstatus] WITH NOCHECK ADD 
	CONSTRAINT [DF_worldstatus_status] DEFAULT (0) FOR [status]
GO

 CREATE  INDEX [IX_account] ON [dbo].[block_msg]([account]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_record] ON [dbo].[user_count]([record_time]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_serverid] ON [dbo].[user_count]([server_id]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_dayofweek] ON [dbo].[user_count]([dayofweek]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

 CREATE  INDEX [idx_account] ON [dbo].[user_time]([account]) WITH  FILLFACTOR = 90 ON [PRIMARY]
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO





-- Created By darkangel
-- 2003.06.19
-- Get Account's Password

CREATE PROCEDURE [dbo].[ap_GPwd]  @account varchar(14), @pwd binary(16) output
AS
SELECT @pwd=password FROM user_auth with (nolock) WHERE account=@account


GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO


CREATE PROCEDURE [dbo].[ap_GStat]
@account varchar(14), 
@uid int OUTPUT, 
@payStat int OUTPUT, 
@loginFlag int OUTPUT, 
@warnFlag int OUTPUT, 
@blockFlag int OUTPUT, 
@blockFlag2 int OUTPUT, 
@subFlag int OUTPUT, 
@lastworld tinyint OUTPUT,
@block_end_date datetime OUTPUT
 AS
SELECT @uid=uid, 
	 @payStat=pay_stat,
              @loginFlag = login_flag, 
              @warnFlag = warn_flag, 
              @blockFlag = block_flag, 
              @blockFlag2 = block_flag2, 
              @subFlag = subscription_flag , 
              @lastworld=last_world, 
              @block_end_date=block_end_date 
               FROM user_account WITH (nolock)
WHERE account=@account

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


CREATE PROCEDURE [dbo].[ap_GUserTime]  @uid int, @userTime int OUTPUT
AS
SELECT @userTime=total_time FROM user_time WITH (nolock) 
WHERE uid = @uid


GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO



CREATE PROCEDURE [dbo].[ap_SLog] 
@uid int, @lastlogin datetime, @lastlogout datetime, @LastGame int, @LastWorld tinyint, @LastIP varchar(15)
AS
UPDATE user_account 
SET last_login = @lastlogin, last_logout=@lastlogout, last_world=@lastWorld, last_game=@lastGame, last_ip=@lastIP
WHERE uid=@uid


GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


CREATE PROCEDURE [dbo].[ap_SUserTime] @useTime int, @uid int
AS
UPDATE user_time SET total_time = total_time - @useTime, present_time = present_time - @useTime
WHERE uid = @uid


GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO


CREATE PROCEDURE [dbo].[l2p_TempCreateAccount]
@account varchar(14),
@ssn varchar(13)
AS 
-- 더미 계정을 생성하기 위한 루틴입니다.  
-- 이미 계정이 생성되어 있는 주민등록번호의 경우에는 생성되지 않습니다. 
-- 클로즈베타기간에만 사용되어야 합니다. 

DECLARE @account_num int

SELECT account FROM user_info WHERE account = @account
IF @@ROWCOUNT <> 0 
BEGIN
	print 'Already Exist'
	RETURN
END

SELECT @account_num= account_num FROM ssn WHERE ssn =@ssn
If @@rowcount  =  0
begin
	set @account_num = 1
end
else
begin
	set @account_num = @account_num + 1
end

BEGIN TRAN	
	IF @account_num = 1
		Insert ssn ( ssn, name, email, newsletter, job, phone, mobile, reg_date, zip, addr_main, addr_etc, account_num, status_flag )
		values (@ssn, '테스트계정', 'newjisu@ncsoft.net',0,0,'02-1234-1234','011-1234-1234',getdate(),'','','',@account_num,0)		
	ELSE
		UPDATE ssn SET account_num = @account_num WHERE ssn =  @ssn
	IF @@ERROR <> 0 GOTO DO_ROLLBACK
	INSERT INTO user_account (account, pay_stat) VALUES (@account, 0)
	IF @@ERROR <> 0 GOTO DO_ROLLBACK
	Insert user_auth ( account, password, quiz1, quiz2, answer1, answer2 ) 
	values ( @account, 0xB53AA65D7C98EF3F0A93B5B578E2C4C4, '내가 다닌 초등학교 이름은 무엇일까?', '내가 다닌 초등학교 이름은 무엇일까?', 0x93A5EFCC45DA1D96A33A1C1CD14B6D6D, 0x93A5EFCC45DA1D96A33A1C1CD14B6D6D)
	IF @@ERROR <> 0 GOTO DO_ROLLBACK
	Insert user_info ( account, create_date, ssn, status_flag, kind )
	values ( @account, getdate(),@ssn, 0, 99  )
	IF @@ERROR <> 0 GOTO DO_ROLLBACK	
	
	
	--update user_account set pay_stat=101, login_flag=0 where account = @account
commit TRAN
RETURN 1

DO_ROLLBACK:
ROLLBACK TRAN
RETURN 0

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

