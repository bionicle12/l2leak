if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddAccountList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddAccountList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_AddFavorite]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_AddFavorite]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelArticle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelArticle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelComment]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelComment]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_DelFavorite]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_DelFavorite]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_Delete]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_Delete]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetAnnounceList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetAnnounceList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetArticleList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetArticleList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBoardAdmin]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBoardAdmin]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBoardList]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBoardList]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBoardPage]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBoardPage]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBoardPermission]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBoardPermission]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBoardRights]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBoardRights]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetBoardTree]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetBoardTree]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetFavorite]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetFavorite]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetKeyword]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetKeyword]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_GetLocation]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_GetLocation]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_InitNewArticles]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_InitNewArticles]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MakeBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MakeBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModArticle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModArticle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ModBoard]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ModBoard]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharClear]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharClear]
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

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_MoveCharacter]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_MoveCharacter]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ReadArticle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ReadArticle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ReadArticle2]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ReadArticle2]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ReadArticleThread]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ReadArticleThread]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_ReadComment]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_ReadComment]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RequestCharCheck]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RequestCharCheck]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_RequestCharMove]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_RequestCharMove]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SearchArticle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SearchArticle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetAnnounce]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetAnnounce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetBoardAdmin]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetBoardAdmin]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetBoardRights]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetBoardRights]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetFavorite]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetFavorite]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_SetRest]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_SetRest]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_WriteArticle]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_WriteArticle]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[lin_WriteComment]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[lin_WriteComment]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[board_announce]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[board_announce]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[board_favorite]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[board_favorite]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[board_keyword]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[board_keyword]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[board_list]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[board_list]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[board_rest]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[board_rest]
GO

CREATE TABLE [dbo].[board_announce] (
	[announce_id] [int] IDENTITY (1, 1) NOT NULL ,
	[post_date] [datetime] NULL ,
	[board_id] [int] NULL ,
	[title] [nvarchar] (128) COLLATE Korean_Wansung_CI_AS NULL ,
	[content] [nvarchar] (3000) COLLATE Korean_Wansung_CI_AS NULL ,
	[deleted] [tinyint] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[board_favorite] (
	[make_date] [datetime] NULL ,
	[char_id] [int] NULL ,
	[world_id] [int] NULL ,
	[fav_id] [int] IDENTITY (1, 1) NOT NULL ,
	[fav_name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[url_string] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[arg1] [int] NULL ,
	[arg2] [int] NULL ,
	[arg3] [int] NULL ,
	[arg4] [int] NULL ,
	[arg5] [int] NULL ,
	[arg6] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[board_keyword] (
	[field_key] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[field_desc] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[field_type] [smallint] NULL ,
	[field_order] [smallint] NULL ,
	[field_id] [int] IDENTITY (1, 1) NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[board_list] (
	[bid] [int] IDENTITY (1, 1) NOT NULL ,
	[name] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[description] [nvarchar] (100) COLLATE Korean_Wansung_CI_AS NULL ,
	[type] [int] NULL ,
	[permission] [int] NULL ,
	[pledge_id] [int] NULL ,
	[world_id] [smallint] NULL ,
	[articles] [int] NULL ,
	[page_size] [smallint] NULL ,
	[deleted] [smallint] NULL ,
	[parent_bid] [int] NULL ,
	[location] [int] NULL ,
	[admin] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[create_date] [datetime] NULL ,
	[new_articles] [int] NULL ,
	[keyword_type] [int] NULL ,
	[check_per] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[board_rest] (
	[char_id] [int] NOT NULL ,
	[pledge_id] [int] NULL ,
	[bid] [int] NOT NULL ,
	[world_id] [smallint] NOT NULL ,
	[permission] [int] NULL ,
	[rest_id] [int] IDENTITY (1, 1) NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[board_list] WITH NOCHECK ADD 
	CONSTRAINT [PK_board_list] PRIMARY KEY  CLUSTERED 
	(
		[bid]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[board_announce] WITH NOCHECK ADD 
	CONSTRAINT [DF_board_announce_post_date] DEFAULT (getdate()) FOR [post_date],
	CONSTRAINT [DF_board_announce_deleted] DEFAULT (0) FOR [deleted]
GO

ALTER TABLE [dbo].[board_favorite] WITH NOCHECK ADD 
	CONSTRAINT [DF_bbs_favorite_make_date] DEFAULT (getdate()) FOR [make_date]
GO

ALTER TABLE [dbo].[board_list] WITH NOCHECK ADD 
	CONSTRAINT [DF_board_list_type] DEFAULT (1) FOR [type],
	CONSTRAINT [DF_board_list_permission] DEFAULT (1) FOR [permission],
	CONSTRAINT [DF_board_list_pledge_id] DEFAULT (0) FOR [pledge_id],
	CONSTRAINT [DF_board_list_world_id] DEFAULT (1) FOR [world_id],
	CONSTRAINT [DF_board_list_articles] DEFAULT (0) FOR [articles],
	CONSTRAINT [DF_board_list_page_size] DEFAULT (20) FOR [page_size],
	CONSTRAINT [DF_board_list_deleted] DEFAULT (0) FOR [deleted],
	CONSTRAINT [DF_board_list_parent_bid] DEFAULT (0) FOR [parent_bid],
	CONSTRAINT [DF_board_list_location] DEFAULT (0) FOR [location],
	CONSTRAINT [DF_board_list_create_date] DEFAULT (getdate()) FOR [create_date],
	CONSTRAINT [DF_board_list_new_articles] DEFAULT (0) FOR [new_articles],
	CONSTRAINT [DF_board_list_keyword_type] DEFAULT (0) FOR [keyword_type],
	CONSTRAINT [DF_board_list_check_per] DEFAULT (1) FOR [check_per]
GO

ALTER TABLE [dbo].[board_rest] WITH NOCHECK ADD 
	CONSTRAINT [DF_board_rest_char_id] DEFAULT (0) FOR [char_id],
	CONSTRAINT [DF_board_rest_pledge_id] DEFAULT (0) FOR [pledge_id],
	CONSTRAINT [DF_board_rest_world_id] DEFAULT (1) FOR [world_id],
	CONSTRAINT [DF_board_rest_permission] DEFAULT (0) FOR [permission]
GO

 CREATE  INDEX [IX1_board_announce] ON [dbo].[board_announce]([board_id]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_bbs_favorite] ON [dbo].[board_favorite]([char_id], [world_id]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_board_keyword] ON [dbo].[board_keyword]([field_type]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_board_list] ON [dbo].[board_list]([deleted], [world_id], [type]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_board_list_1] ON [dbo].[board_list]([world_id], [deleted], [parent_bid]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_board_rest] ON [dbo].[board_rest]([char_id], [world_id], [bid]) ON [PRIMARY]
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO


/********************************************
lin_AddAccountList
	do add temp account list
return
made by
	myhong
date
	2003-06-26
********************************************/
CREATE PROCEDURE [DBO].[lin_AddAccountList]
	@sid		varchar(20),
	@world_id	int,
	@account_id	int,
	@account_name	varchar(50),
	@char_id	int,
	@char_name	nvarchar(50),
	@pledge_id	int,
	@lev		tinyint
AS

SET NOCOUNT ON

insert into temp_account_list ( sid, world_id, account_id, account_name, char_id, char_name, pledge_id, lev )
values
( @sid, @world_id, @account_id, @account_name, @char_id, @char_name, @pledge_id, @lev )

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
lin_AddAnnounce
	do add board announce
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_AddAnnounce]
	@board_id	int,
	@title		nvarchar(128),
	@content	nvarchar(3000)
AS
SET NOCOUNT ON
insert into board_announce ( board_id, title, content )
values
( @board_id, @title, @content   )


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
lin_AddFavorite
	do add board tree info
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_AddFavorite]
	@char_id		int,
	@world_id		int,
	@fav_name		nvarchar(50),
	@url_string		nvarchar(50),
	@arg1			int,
	@arg2			int,
	@arg3			int
AS
SET NOCOUNT ON
insert into board_favorite( char_id, world_id, fav_name, url_string, arg1, arg2, arg3)
values
(@char_id, @world_id, @fav_name, @url_string, @arg1, @arg2, @arg3)


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
lin_DelArticle
	do delete article 
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_DelArticle]
	@board_id		int,
	@bid			int,
	@option		int
AS
SET NOCOUNT ON
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
declare @str_bid	nvarchar(12)
declare @str_boardid	nvarchar(12)
set @table_name = 'board_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = 'select * from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
exec (@sql)
if (@@ROWCOUNT = 0) return
set @str_bid = cast( @bid as nvarchar)
set @str_boardid = cast( @board_id as nvarchar)
-- board table exists,,, modify article ^^
if (@option =  0 )
begin
	-- undelete 
	set @sql = ' update dbo.' + @table_name + ' set status = 0 where bid = ' + @str_bid + ' and status = 1 '
	exec (@sql)
	set @sql = 'update dbo.board_list set articles = articles + 1 where bid = ' + @str_boardid
	exec (@sql)
end
if (@option =  1 )
begin
	set @sql = ' select * from dbo.' + @table_name + ' where bid = ' + @str_bid + ' and status = 0 and datediff( d, post_date , getdate() ) = 0 ' 
	exec (@sql)
	if ( @@ROWCOUNT > 0)
	begin
		set @sql = 'update dbo.board_list set new_articles = new_articles  - 1 where new_articles > 0 and bid = ' + @str_boardid
		exec (@sql)
	end
	set @sql = ' update dbo.' + @table_name + ' set status = 1 where bid = ' + @str_bid + ' and status = 0 ' 
	exec (@sql)
	if ( @@ROWCOUNT > 0)
	begin
		set @sql = 'update dbo.board_list set articles = articles - 1 where bid = ' + @str_boardid
		exec (@sql)
	end
end
if (@option = 2)
begin
	set @sql = ' select * from dbo.' + @table_name + ' where bid = ' + @str_bid + ' and status = 0 and datediff( d, post_date , getdate() ) = 0 ' 
	exec (@sql)
	if ( @@ROWCOUNT > 0)
	begin
		set @sql = 'update dbo.board_list set new_articles = new_articles  - 1 where new_articles > 0 and bid = ' + @str_boardid
		exec (@sql)
	end
	set @sql = ' delete from dbo.' + @table_name + ' where bid = ' + @str_bid + ' and status = 0 '
	exec (@sql)
	if ( @@ROWCOUNT > 0)
	begin
		set @sql = 'update dbo.board_list set articles = articles - 1 where articles > 0 and bid = ' + @str_boardid
		exec (@sql)
	end else begin
		set @sql = ' delete from dbo.' + @table_name + ' where bid = ' + @str_bid + ' and status = 1 '
		exec (@sql)	
	end
end 
return
EXEC_FAIL:
	return

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
lin_DelBoard
	do delete board
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_DelBoard]
	@board_id	int,
	@delete_option	int
AS
SET NOCOUNT ON
declare @sql nvarchar(512)
declare @bid int
	if @delete_option = 0
	begin
		-- undo delete 
		update board_list set deleted = 0 where bid = @board_id
	end 
	if @delete_option = 1
	begin
		update board_list set deleted = 1 where bid = @board_id
	end 
	if @delete_option = 2
	begin
			delete board_list where bid = @board_id
	
			set @sql = 'drop table dbo.board_' + cast ( @board_id  as nvarchar)
			exec (@sql)
	
			set @sql = 'drop table dbo.comment_' + cast ( @board_id  as nvarchar)
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
lin_DelComment
	do delete comment
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_DelComment]
	@board_id		int,
	@comment_id		int,
	@option		int
AS
SET NOCOUNT ON
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
declare @str_commentid	nvarchar(12)
set @table_name = 'comment_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = 'select * from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
exec (@sql)
if (@@ROWCOUNT = 0) return
set @str_commentid = cast( @comment_id as nvarchar)
-- comment table exists,,, modify article ^^
if (@option =  3 )
begin
	set @sql = ' declare @bid int'
		+ ' select @bid = bid from dbo.' + @table_name + ' where comment_id = ' + @str_commentid
		+ ' update dbo.board_' + cast(@board_id as nvarchar) + ' set comment_cnt = comment_cnt - 1 where bid = @bid and comment_cnt > 0 '
	exec (@sql)
	set @sql = ' delete from dbo.' + @table_name + ' where comment_id = ' + @str_commentid
	exec (@sql)

end 
return
EXEC_FAIL:
	return


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
lin_DelFavorite
	do del board tree info
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_DelFavorite]
	@fav_id		int,
	@world_id		int
AS
SET NOCOUNT ON
delete from board_favorite where fav_id = @fav_id and world_id = @world_id


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
lin_Delete
	do delete article 
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_Delete]
	@board_id		int,
	@bid			int,
	@comment_id		int,
	@option		int
AS
SET NOCOUNT ON
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
declare @str_bid	nvarchar(12)
set @table_name = 'board_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = 'select * from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
exec (@sql)
if (@@ROWCOUNT = 0) return
if @option = 0 or @option = 1 or @option = 2 
begin
	exec lin_DelArticle @board_id, @bid, @option
end else if @option = 3 
begin
	exec lin_DelComment @board_id, @comment_id, @option
end
return


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
lin_GetAnnounce
	do get board announce
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_GetAnnounce]
	@announce_id	int
AS
SET NOCOUNT ON
select R2. name, R1.board_id, R1.n_date, R1.title, R1.content from
(
select board_id, n_date=datediff( ss, "1970/1/1 0:0:0" , post_date ) , title, content from board_announce (nolock)
where announce_id = @announce_id
) as R1
left join
(
select * from board_list (nolock)
) as R2
on R1.board_id = R2.bid


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
lin_GetAnnounceList
	do get board announce llist
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_GetAnnounceList]
	@board_id	int
AS
SET NOCOUNT ON
select top 4 announce_id, datediff( ss, '1970/1/1 0:0:0' , post_date ) , title  from board_announce (nolock)
where board_id = @board_id and deleted = 0
order by post_date desc


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
lin_GetArticleList
	do get article  list
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_GetArticleList]
	@board_id		int,
	@page			int,
	@nlist			int = 0
AS
SET NOCOUNT ON
declare @str_board_id	nvarchar(12)
declare @str_page	nvarchar(12)
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
declare @top		int
declare @loc_id		int
set @str_board_id = cast ( @board_id as nvarchar) 
if @page < 1 set @page = 1
set @str_page = cast ( @page as nvarchar) 
set @table_name = 'board_' + @str_board_id

-- select @top = page_size * @page from board_list (nolock) where bid = @board_id

if @nlist = 0
	select @top = page_size * @page from board_list (nolock) where bid = @board_id
else
	set @top = @nlist * @page


if @top < 1 return
-- check board_#### 
set @sql = ' declare @ret int'
	+ ' declare @page_size int'
	+ ' select @ret = count(*) from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
	+ ' if @ret < 1 return '
	+ ' ' 	-- get page_size
	+ ' select @page_size = page_size from board_list (nolock) where bid = ' + @str_board_id
	+ ' ' 	-- get list
	+ ' select top  ' + cast( @top as nvarchar)  + ' root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title,  datediff( ss, ''1970/1/1 0:0:0'' , post_date ) , datediff( ss, ''1970/1/1 0:0:0'' , modify_date ) , read_count, status, comment_cnt, keyword  '
	+ ' from dbo.' + @table_name
	+ ' ( nolock) where status = 0 and root_bid > 0 order by root_bid desc, thread_order asc ' 
exec (@sql)
return
EXEC_FAIL:
	return

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
lin_GetBoardAdmin
	do get board admin
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBoardAdmin]
	@bid		int,
	@world_id	int
AS
SET NOCOUNT ON
select char_id, permission  from board_rest (nolock) where bid = @bid and world_id = @world_id order by char_id asc


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
lin_GetBoardList
	do get board list
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBoardList]
	@parent_node_id	int,
	@world_id	int,
	@location	int,
	@pledge_id	int
AS
SET NOCOUNT ON
if @parent_node_id > 0 
begin
	-- with parent node id
	-- sub folder boards
	select parent_bid, bid, admin, location, pledge_id , dtcreate=datediff( ss, '1970/1/1 0:0:0', create_date ), name, description, type, permission, articles, page_size, new_articles  from board_list (nolock) 
	where deleted = 0 and parent_bid = @parent_node_id
	order by type asc, name asc
end else if @location < 0
begin
	-- show location boards
	select parent_bid, bid, admin, location, pledge_id , dtcreate=datediff( ss, '1970/1/1 0:0:0', create_date ), name, description, type, permission, articles, page_size , new_articles from board_list (nolock) 
	where deleted = 0 and location > 0 and world_id = @world_id
	order by type asc, name asc
end else begin
	--  others ( parent_node_id is not entered)
	-- init state
	select parent_bid, bid, admin, location, pledge_id , dtcreate=datediff( ss, '1970/1/1 0:0:0', create_date ), name, description, type, permission, articles, page_size, new_articles  from board_list (nolock) 
	where deleted = 0 and parent_bid = 0 and world_id in (  @world_id , 0 )
	order by type asc, name asc
	
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
lin_GetBoardPage
	do get board page info
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBoardPage]
	@board_id		int
AS
SET NOCOUNT ON
select page_size,  articles, name from board_list (nolock) where bid = @board_id


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
lin_GetBoardPermission
	do get board permisssion
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBoardPermission]
	@char_id	int,
	@bid		int,
	@world_id	int
AS
SET NOCOUNT ON
select permission  from board_rest (nolock) where bid = @bid and world_id = @world_id and char_id = @char_id


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
lin_GetBoardRights
	do get board permisssion
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBoardRights]
	@char_id	int,
	@pledge_id	int,
	@bid		int,
	@world_id	int
AS
SET NOCOUNT ON
declare @check_per int
declare @rights int
set @rights = 0
select @check_per = check_per from board_list (nolock) where bid = @bid
if ( @check_per  = 1 )
begin
	-- char_id, bid 
	select @rights = permission from board_rest (nolock) 
	where char_id = @char_id and bid = @bid and world_id = @world_id
end 
else if ( @check_per = 2)
begin
	-- check char_id, bid first
	if ( @char_id > 0 ) select @rights = permission from board_rest (nolock) where char_id = @char_id and bid = @bid and world_id = @world_id
	-- pledge_id, bid
	if ( @rights = 0) 	select @rights = permission from board_rest (nolock)  where pledge_id = @pledge_id and bid = @bid and world_id = @world_id	
end
-- pagesize, narticles, board name, permission 
if (@rights > 0 )
begin
	select page_size, articles, name, @rights from board_list (nolock) where bid = @bid
end else begin
	select page_size, articles, name, permission from board_list (nolock) where bid = @bid
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
lin_GetBoardTree
	do get board tree info
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_GetBoardTree]
	@board_id		int
AS
SET NOCOUNT ON
select parent_bid, bid, name, description, type, permission from board_list (nolock) where bid = @board_id


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
lin_GetFavorite
	do get board tree info
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_GetFavorite]
	@char_id		int,
	@world_id		int
AS
SET NOCOUNT ON
/* select R1.*, R2.name, R2.description from 
( select * from lin2comm.dbo.board_favorite(nolock)  ) as R1
left join
( select * from lin2comm.dbo.board_list (nolock) ) as R2
on R1.arg1 = R2.bid */
select R1.*, R2.name, R2.description from
(
	select top 10 char_id, dtcreate=datediff( ss, '1970/1/1 0:0:0' , make_date ), fav_id, fav_name, url_string, arg1, arg2, arg3, arg4, arg5, arg6 
	from board_favorite (nolock) 
	where char_id = @char_id and world_id = @world_id
	order by make_date desc
) as R1
left join
( select * from board_list (nolock) ) as R2
on R1.arg1 = R2.bid


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
lin_GetKeyword
	do get keyword
INPUT
OUTPUT
return
made by
	young
date
	2003-06-04
********************************************/
CREATE PROCEDURE [DBO].[lin_GetKeyword]
	@bid	int
AS
SET NOCOUNT ON
declare @keyword_type int
select @keyword_type = keyword_type from board_list (nolock) where bid = @bid
select field_key from board_keyword (nolock)
where field_type = @keyword_type
order by field_order asc


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
lin_GetLocation
	do get board location
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_GetLocation]
	@loc_id		int,
	@world_id	int
AS
SET NOCOUNT ON
declare @newloc int
if ( @loc_id < 0 )
begin
	set @newloc = @loc_id * -1
	select top 1 bid from board_list (nolock) where location = @newloc	 and world_id = @world_id
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
lin_InitNewArticles
	do init new articles
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_InitNewArticles]
AS
set nocount on
update board_list set new_articles = 0


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
lin_MakeBoard
	do make board
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_MakeBoard]
	@parent_bid	int,
	@name	nvarchar(50),
	@location	int,
	@description	nvarchar(200),
	@type		int,
	@admin		nvarchar(50),
	@permission	int,
	@pledge_id	int,
	@world_id	smallint,
	@page_size	smallint,
	@keyword	int
AS
SET NOCOUNT ON
declare @return int
declare @sql nvarchar(1024)
declare @table_name nvarchar(64)
declare @board_id int
declare @node_id int
declare @identity nvarchar(12)
set @return = 0

-- insert into board_list
insert into board_list ( name, description, type, admin, parent_bid , permission, pledge_id, world_id, page_size , location , keyword_type )
values ( @name, @description, @type, @admin, @parent_bid, @permission, @pledge_id, @world_id, @page_size , @location , @keyword )

set @board_id = @@IDENTITY
set @identity = cast ( @board_id as NVARCHAR)
-- make board_#### 
set @table_name = 'board_' + @identity
-- begin tran
set @sql = ' CREATE TABLE [dbo].[' + @table_name + '] ( '
	+'	[root_bid] [int] NOT NULL , '
	+'	[thread_order] [smallint] NOT NULL , '
	+'	[bid] [int] IDENTITY (1, 1) NOT NULL , '
	+'	[step] [smallint] NULL , '
	+'	[parent_bid] [int] NOT NULL , '
	+'	[char_id] [int] NULL , '
	+'	[char_name] [nvarchar] (50) , '
	+'	[account_id] [int] NULL , '
	+'	[account_name] [nvarchar] (50) , '
	+'	[world_id] [smallint] NULL , '
	+'	[title] [nvarchar] (128) , '
	+'	[content] [nvarchar] (3000) , '
	+'	[post_date] [datetime] NULL , '
	+'	[modify_date] [datetime] NULL , '
	+'	[read_count] [int] NULL , '
	+'	[status] [int] NULL,  '
	+'	[ip] [nvarchar] (20),  '
	+'	[comment_cnt] [smallint] NULL , '
	+'	[keyword] [nvarchar] (20)  '
	+') ON [PRIMARY] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED

set @sql = ' ALTER TABLE [dbo].[' + @table_name + '] WITH NOCHECK ADD  ' 
	+'	CONSTRAINT [DF_' + @table_name + '_root_bid] DEFAULT (0) FOR [root_bid], '
	+'	CONSTRAINT [DF_' + @table_name + '_thread_order] DEFAULT (0) FOR [thread_order], '
	+'	CONSTRAINT [DF_' + @table_name + '_parent_bid] DEFAULT (0) FOR [parent_bid],'
	+'	CONSTRAINT [DF_' + @table_name + '_step] DEFAULT (0) FOR [step],'
	+'	CONSTRAINT [DF_' + @table_name + '_world_id] DEFAULT (1) FOR [world_id],'
	+'	CONSTRAINT [DF_' + @table_name + '_post_date] DEFAULT (getdate()) FOR [post_date],'
	+'	CONSTRAINT [DF_' + @table_name + '_read_count] DEFAULT (0) FOR [read_count], '
	+'	CONSTRAINT [DF_' + @table_name + '_status] DEFAULT (0) FOR [status], '
	+'	CONSTRAINT [DF_' + @table_name + '_comment_cnt] DEFAULT (0) FOR [comment_cnt] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED


-- CREATE  CLUSTERED  INDEX [ix_board_114_1] ON [dbo].[board_114]([root_bid] DESC , [thread_order]) ON [PRIMARY]
-- CREATE  INDEX [IX_board_114] ON [dbo].[board_114]([bid] DESC ) ON [PRIMARY]

set @sql = ' CREATE CLUSTERED  INDEX [IX_' + @table_name + '_1] ON [dbo].[' + @table_name + ']([root_bid] DESC , [thread_order ] ) ON [PRIMARY] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED

set @sql = ' CREATE  INDEX [IX_' + @table_name + '] ON [dbo].[' + @table_name + ']([bid] DESC ) ON [PRIMARY] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED
-- make comment_#### 
set @table_name = 'comment_' + @identity
set @sql = ' CREATE TABLE [dbo].[' + @table_name + '] ( '
	+'	[comment_id] [int] IDENTITY (1, 1) NOT NULL , '
	+'	[bid] [int] NULL , '
	+'	[comment_date] [datetime] NULL , '
	+'	[char_id] [int] NULL , '
	+'	[char_name] [nvarchar] (50) , '
	+'	[account_id] [int] NULL , '
	+'	[account_name] [nvarchar] (50) , '
	+'	[world_id] [smallint] NULL , '
	+'	[comment] [nvarchar] (128) , '
	+'	[status] [int] NULL  '
	+') ON [PRIMARY] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED
set @sql =' ALTER TABLE [dbo].[' + @table_name + '] WITH NOCHECK ADD '
	+'	CONSTRAINT [DF_' + @table_name + '_comment_date] DEFAULT (getdate()) FOR [comment_date], '
	+'	CONSTRAINT [DF_' + @table_name + '_world_id] DEFAULT (1) FOR [world_id], '
	+'	CONSTRAINT [DF_' + @table_name + '_status] DEFAULT (0) FOR [status] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED
set @sql = ' CREATE  INDEX [IX_' + @table_name + '] ON [dbo].[' + @table_name + ']([bid] DESC ) ON [PRIMARY] '
exec (@sql)
if (@@ERROR <> 0 ) goto EXEC_FAILED
-- commit tran
set @return = 1
select @return
return
EXEC_FAILED: 
--	rollback tran
	set @return = 0
	select @return
	return

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
lin_ModArticle
	do modify article  body
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_ModArticle]
	@board_id		int,
	@bid			int,
	@title			nvarchar(128),
	@content		nvarchar(3000),
	@keyword		nvarchar(20) = ''
AS
SET NOCOUNT ON
declare @table_name nvarchar(64)
declare @sql nvarchar(4000)
set @table_name = 'board_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = 'select * from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
exec (@sql)
if (@@ROWCOUNT = 0) return
-- board table exists,,, modify article ^^
set @sql = ' update ' + @table_name + N' set keyword = N''' + @keyword + N''' ,  title =  N''' + @title + N''' , content = N''' + @content + N''' where bid = ' + cast(@bid as nvarchar)
exec (@sql)
return
EXEC_FAIL:
	return


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
lin_ModBoard
	do modify board info
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_ModBoard]
	@bid		int,
	@parent_bid	int,
	@name		nvarchar(50),
	@description	nvarchar(200),
	@admin		nvarchar(50),
	@type		int,
	@permission	int,
	@location	int,
	@pledge_id	int,
	@world_id	smallint,
	@page_size	smallint,
	@keyword_type	int
AS
SET NOCOUNT ON
declare @boardcount int
select @boardcount = count(*) from board_list (nolock) where bid = @bid
if @boardcount = 1
begin
	update board_list set parent_bid = @parent_bid, admin= @admin, location=@location, name = @name, description = @description, type = @type, permission=@permission, pledge_id = @pledge_id, world_id = @world_id, page_size=@page_size , keyword_type = @keyword_type where bid = @bid
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
lin_MoveCharClear
	clear moved character
INPUT

OUTPUT

return
made by
	young
date
	2003-7-30
********************************************/
CREATE PROCEDURE [DBO].[lin_MoveCharClear]
	@world_id	int
AS

SET NOCOUNT ON

-- set character as non-playable
-- update user_data set old_account_id = account_id 
-- where account_id > 0 and char_id in ( select old_char_id from lin2comm.dbo.req_charmove (nolock) where old_world_id = @world_id )

update user_data set account_id = -3
where char_id in ( select old_char_id from dbo.req_charmove (nolock) where old_world_id = @world_id )

-- update pledge info
declare @old_char_id int
declare @old_char_name nvarchar(50)

DECLARE move_cursor CURSOR FOR 
SELECT old_char_id, old_char_name
FROM dbo.req_charmove (nolock)
WHERE old_world_id = @world_id

OPEN move_cursor 

FETCH NEXT FROM move_cursor  
INTO @old_char_id, @old_char_name

WHILE @@FETCH_STATUS = 0
BEGIN
	select @old_char_id, @old_char_name
	exec lin_MoveCharacter @old_char_id

	-- Get the next 
	FETCH NEXT FROM move_cursor 
	INTO @old_char_id, @old_char_name

END

close move_cursor 
deallocate move_cursor
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
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
	+ ' select ' + @world_id + '  , R1.pledge_id, ruler_id, 0, name + ''-' + @world_id + ''' , 0, 0, 0, 0 ,0 ,skill_level , 0, 0, 0, name_value, 0, 0, 0, 0, 0, 0, 0, 0  from ( select * from '
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

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

-- drop procedure lin_MoveCharSvr

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

-- update pledge in user_data table
set @sql = ' update r '
	+ ' set r.pledge_id = u.pledge_id '
	+ ' from user_data as r  inner join pledge as u '
	+ ' on r.old_pledge_id = u.old_pledge_id '
	+ ' where r.char_name like ''%-' +  CAST ( @old_world_id as VARCHAR)  + '''  and u.pledge_id is not null  '
select @sql

exec (@sql)


-- update pledge owner in pledge table
set @sql = ' update r '
	+ ' set r.ruler_id = u.char_id'
	+ ' from pledge as r  inner join user_data as u '
	+ ' on r.old_ruler_id = u.old_char_id '
	+ ' where r.old_world_id = ' +  CAST ( @old_world_id as VARCHAR)  + '  and u.char_id is not null  '

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
	+ ' ( select * from user_item (nolock) where item_type = 2375 and old_world_id = ' + CAST ( @old_world_id as varchar ) + ' ) as R1 '
	+ ' left join '
	+ ' ( ' 
	+ ' select * from  ' 
	+ ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', ' 
	+ ' '' select pet_id, npc_class_id, expoint, hp, mp, sp, meal  from lin2world.dbo.pet_data (nolock) '' ) ' 
	+ ' ) as R2 ' 
	+ ' on R1.old_item_id = R2.pet_id '
	+ ' where R2.npc_class_id is not null ' 
exec (@sql)



-- user_item owned by pet
set @sql = ' insert into user_item( char_id, item_type, amount, enchant, eroded, bless, ident, wished, warehouse  ) ' 
	+ ' select R2.item_id, R1.item_type, R1.amount, R1.enchant, R1.eroded, R1.bless, R1.ident, R1.wished, R1.warehouse  ' 
	+ ' from ' 
	+ ' ( ' 
	+ ' select * from  ' 
	+ ' OPENROWSET ( ''SQLOLEDB'', ''' + @conn_str + ''', ' 
	+ ' '' select * from lin2world.dbo.user_item (nolock) where warehouse = 5 '' ) ' 
	+ ' ) as R1 ' 
	+ ' left join '
	+ ' ( select * from user_item (nolock) where old_world_id = ' + CAST ( @old_world_id as varchar ) + ' ) as R2 '
	+ ' on R1.char_id = R2.old_item_id '
	+ ' where R2.item_id is not null '

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

CREATE PROCEDURE dbo.lin_MoveCharacter
(
	@player_id INT
)
AS
SET NOCOUNT ON
DECLARE @pledge_id INT
SELECT @pledge_id = pledge_id FROM user_data WHERE char_id = @player_id
IF @pledge_id <> 0
BEGIN
	DECLARE @ruler_id INT
	DECLARE @now_war_id INT
	SELECT @ruler_id = ruler_id, @now_war_id = now_war_id FROM pledge WHERE pledge_id = @pledge_id
	IF @ruler_id = @player_id -- Ç÷¸ÍÁÖÀÎ °æ¿ì Ç÷¸Í Á¤¸®
	BEGIN
		IF @now_war_id <> 0 -- Ç÷Àü ÁßÀÎ Ç÷¸ÍÀÎ °æ¿ì Ç÷Àü Á¤¸®
		BEGIN
			DECLARE @challenger INT
			DECLARE @challengee INT
			SELECT @challenger = challenger, @challengee = challengee FROM pledge_war WHERE id = @now_war_id
			UPDATE pledge SET now_war_id = 0 WHERE pledge_id IN (@challenger, @challengee)
			DELETE FROM pledge_war WHERE id = @now_war_id
		END
		
	--	DELETE FROM pledge WHERE pledge_id = @pledge_id
		UPDATE user_data SET pledge_id = 0 , nickname = null WHERE pledge_id = @pledge_id
	END
	UPDATE user_data SET pledge_id = 0 , nickname = null WHERE char_id = @player_id
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
lin_ReadArticle
	do read article 
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_ReadArticle]
	@board_id		int,
	@bid			int,
	@account_id		int,
	@pledge_id		int,
	@world_id		int
AS
SET NOCOUNT ON
declare @str_board_id	nvarchar(12)
declare @str_bid	nvarchar(12)
declare @str_account_id		nvarchar(20)
declare @str_world_id	nvarchar(12)
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
set @str_board_id = cast ( @board_id as nvarchar) 
set @str_bid = cast ( @bid as nvarchar) 
set @str_account_id = cast ( @account_id as nvarchar) 
set @str_world_id = cast ( @world_id as nvarchar) 
set @table_name = 'board_' + @str_board_id
-- check board_#### 
set @sql = ' declare @ret int'
	+ ' select @ret = count(*) from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
	+ ' if @ret < 1 return '
	+ '  '	-- board table exists, inc readcount
	+ ' ' 	-- read
	+ ' select root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title, content, datediff( ss, ''1970/1/1 0:0:0'' , post_date ), datediff( ss, ''1970/1/1 0:0:0'' , post_date ), read_count, status , ip , 0 '
	+ ' , keyword from dbo.' + @table_name
	+ ' ( nolock) where bid = ' + @str_bid + ' and status = 0 ' 
exec (@sql)


if @account_id > 0
begin
	set @sql = ' update dbo.' + @table_name + ' set read_count = read_count + 1 where bid = ' + @str_bid + ' and ( account_id <> ' + @str_account_id + '  ) '
	exec (@sql)
end 

return

EXEC_FAIL:

	return

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
lin_ReadArticle
	do read article 
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_ReadArticle2]
	@board_id		int,
	@bid			int,
	@account_id		int,
	@pledge_id		int,
	@world_id		int
AS
SET NOCOUNT ON
declare @str_board_id	nvarchar(12)
declare @str_bid	nvarchar(12)
declare @str_account_id		nvarchar(20)
declare @str_world_id	nvarchar(12)
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
set @str_board_id = cast ( @board_id as nvarchar) 
set @str_bid = cast ( @bid as nvarchar) 
set @str_account_id = cast ( @account_id as nvarchar) 
set @str_world_id = cast ( @world_id as nvarchar) 
set @table_name = 'board_' + @str_board_id
-- check board_#### 
set @sql = ' declare @ret int'
	+ ' select @ret = count(*) from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
	+ ' if @ret < 1 return '
	+ '  '	-- board table exists, inc readcount
	+ ' ' 	-- read
	+ ' select root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title, content, datediff( ss, ''1970/1/1 0:0:0'' , post_date ), datediff( ss, ''1970/1/1 0:0:0'' , post_date ), read_count, status , ip , 0 '
	+ ' , keyword from dbo.' + @table_name
	+ ' ( nolock) where bid = ' + @str_bid + ' and status = 0 ' 
exec (@sql)

if @account_id > 0
begin
	set @sql = ' update dbo.' + @table_name + ' set read_count = read_count + 1 where bid = ' + @str_bid + ' and ( account_id <> ' + @str_account_id + '  ) '
select @sql
--	exec (@sql)
end 

/*
	+ ' if ' + cast ( @account_id as nvarchar) + ' > 0 '
	+ ' begin '
	+ ' 	update dbo.' + @table_name + ' set read_count = read_count + 1 where bid = ' + @str_bid + ' and ( account_id <> ' + @str_account_id + '  ) '
	+ ' end ' 
*/

return
EXEC_FAIL:
	return
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
lin_ReadArticleThread
	do read article thread
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_ReadArticleThread]
	@board_id		int,
	@bid			int,
	@char_id		int,
	@world_id		int,
	@ncount		int = 8
AS
SET NOCOUNT ON
declare @str_board_id	nvarchar(12)
declare @str_bid	nvarchar(12)
declare @str_char_id	nvarchar(12)
declare @str_world_id	nvarchar(12)
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
set @str_board_id = cast ( @board_id as nvarchar) 
set @str_bid = cast ( @bid as nvarchar) 
set @str_char_id = cast ( @char_id as nvarchar) 
set @str_world_id = cast ( @world_id as nvarchar) 
set @table_name = 'board_' + @str_board_id
-- check board_#### 
set @sql = ' declare @ret int'
	+ ' declare @root_bid int'
	+ ' select @ret = count(*) from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
	+ ' if @ret < 1 return '
	+ ' ' 	-- read thread
	+ ' select @root_bid = root_bid from dbo.' + @table_name + ' (nolock) where bid = ' + @str_bid
	+ ' '
	+ ' select top ' + cast ( @ncount as nvarchar) + '  root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title,  datediff( ss, ''1970/1/1 0:0:0'' , post_date ), datediff( ss, ''1970/1/1 0:0:0'' , modify_date ) , read_count, status, comment_cnt, keyword   '
	+ ' from dbo.' + @table_name
	+ ' ( nolock) where root_bid = @root_bid  and status = 0 order by root_bid desc, thread_order asc ' 
exec (@sql)
return
EXEC_FAIL:
	return


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
lin_ReadComment
	do read comment
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_ReadComment]
	@board_id		int,
	@bid			int,
	@ncount		int = 10
AS
SET NOCOUNT ON
declare @table_name	nvarchar(64)
declare @sql		nvarchar(1024)
set @table_name = 'comment_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = ' declare @ret int'
	+ ' select @ret = count(*) from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
	+ ' if @ret < 1 return '
	+ ' ' 	-- read
	+ ' select * from ( select top ' + cast ( @ncount as nvarchar) + ' char_name, comment , comment_tick = datediff( ss, ''1970/1/1 0:0:0'' , comment_date ) , comment_id, char_id, account_id , world_id   '
	+ ' from dbo.' + @table_name
	+ ' ( nolock) where bid = ' + cast ( @bid as nvarchar)
	+ ' order by comment_date asc' 
	+ ' ) as R1 '
	+ ' order by comment_tick asc '
exec (@sql)
return
EXEC_FAIL:
	return



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
lin_RequestCharCheck
	request char move
INPUT

OUTPUT

return
made by
	young
date
	2003-07-25
********************************************/
CREATE PROCEDURE [DBO].[lin_RequestCharCheck]
	@old_char_name	nvarchar(50),
	@new_char_name	nvarchar(50),
	@old_char_id		int,
	@account_name	nvarchar(50),
	@account_id		int,
	@old_world_id		int,
	@new_world_id		int

AS
SET NOCOUNT ON

declare @check_field int
declare @req_count int



-- check wheather this account already requested or not
if ( exists( select new_char_name from req_charmove (nolock) where account_id = @account_id    ) ) 
begin
--	this account has requested to move character
	select -2
	RETURN -1	
end



set @check_field = 0

select top 1 @check_field = check_field from req_charmove_check (nolock) where world_no = @new_world_id

if ( @check_field = 1 ) 
begin
	select -3
	return -1
end

select @req_count =  count(*) from req_charmove (nolock) where new_world_id = @new_world_id
if ( @req_count > 10000)
begin
	select -3

	update req_charmove_check set check_field = 1 where world_no = @new_world_id

	return -1
end

-- check new_char_name string can be used
IF @new_char_name LIKE N' ' 
BEGIN
--	this char name is prohibited word
	select -1
	RETURN -1
END

-- check new_char_name string can be used
if exists(select char_name from user_prohibit (nolock) where char_name = @new_char_name)
begin
--	this char name is prohibited word
	select -1
	RETURN -1	
end

-- check new_char_name string can be used
declare @user_prohibit_word nvarchar(20)
select top 1 @user_prohibit_word = words from user_prohibit_word (nolock) where PATINDEX('%' + words + '%', @new_char_name) > 0 
if @user_prohibit_word is not null
begin
--	this char name contain  prohibited word
	select -1
	RETURN -1	
end

-- check wheather new_char_name string is already requested or not
-- if ( exists( select new_char_name from req_charmove (nolock) where new_char_name = @new_char_name    ) ) 
if ( exists( select new_char_name from req_charmove (nolock) where new_char_name = @new_char_name  and new_world_id = @new_world_id  ) ) 
begin
--	this char name, new world id has been requested
	select -1
	RETURN -1	
end

select 1
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
lin_RequestCharMove
	request char move
INPUT

OUTPUT

return
made by
	young
date
	2003-07-25
********************************************/
CREATE PROCEDURE [DBO].[lin_RequestCharMove]
	@old_char_name	nvarchar(50),
	@new_char_name	nvarchar(50),
	@old_char_id		int,
	@account_name	nvarchar(50),
	@account_id		int,
	@old_world_id		int,
	@new_world_id		int

AS
SET NOCOUNT ON

declare @req_count int
declare @check_field int

-- check wheather this account already requested or not
if ( exists( select new_char_name from req_charmove (nolock) where account_id = @account_id    ) ) 
begin
--	this account has requested to move character
	select -2
	RETURN -1	
end


set @check_field = 0

select top 1 @check_field = check_field from req_charmove_check (nolock) where world_no = @new_world_id

if ( @check_field = 1 ) 
begin
	select -3
	return -1
end

select @req_count =  count(*) from req_charmove (nolock) where new_world_id = @new_world_id
if ( @req_count > 10000)
begin
	select -3

	update req_charmove_check set check_field = 1 where world_no = @new_world_id

	return -1
end


-- check new_char_name string can be used
IF @new_char_name LIKE N' ' 
BEGIN
--	this char name is prohibited word
	select -1
	RETURN -1
END

-- check new_char_name string can be used
if exists(select char_name from user_prohibit (nolock) where char_name = @new_char_name)
begin
--	this char name is prohibited word
	select -1
	RETURN -1	
end

-- check new_char_name string can be used
if ( exists ( select words from user_prohibit_word (nolock) where words like '%' + @new_char_name + '%' ) ) 
begin
--	this char name contain  prohibited word
	select -1
	RETURN -1	
end


-- check wheather new_char_name string is already requested or not
--if ( exists( select new_char_name from req_charmove (nolock) where new_char_name = @new_char_name    ) ) 
if ( exists( select new_char_name from req_charmove (nolock) where new_char_name = @new_char_name  and new_world_id = @new_world_id  ) ) 
begin
--	this char name, new world id has been requested
	select -1
	RETURN -1	
end

insert into req_charmove ( old_char_name, old_char_id, account_name, account_id, old_world_id, new_world_id, new_char_name)
values ( @old_char_name, @old_char_id, @account_name, @account_id, @old_world_id, @new_world_id , @new_char_name )

if (@@ERROR <> 0 ) goto EXEC_FAILED

select 1
return

EXEC_FAILED: 
	select -1
	return
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
lin_SearchArticle
	do search
INPUT
OUTPUT
return
made by
	young
date
	2003-04-24
********************************************/
CREATE PROCEDURE [DBO].[lin_SearchArticle]
	@ntop			int,
	@board_id		int,
	@search_option		int,
	@search_string		nvarchar(20)
AS
SET NOCOUNT ON
declare @bcount int
declare @sql nvarchar(800)
declare @where nvarchar(256)
select @bcount = count(*) from board_list (nolock) where bid = @board_id
if @bcount < 1 return
set @search_string = rtrim(ltrim(@search_string))
set @search_string = replace( @search_string, N'           ', N' ')
set @search_string = replace( @search_string, N'          ', N' ')
set @search_string = replace( @search_string, N'         ', N' ')
set @search_string = replace( @search_string, N'        ', N' ')
set @search_string = replace( @search_string, N'       ', N' ')
set @search_string = replace( @search_string, N'      ', N' ')
set @search_string = replace( @search_string, N'     ', N' ')
set @search_string = replace( @search_string, N'    ', N' ')
set @search_string = replace( @search_string, N'   ', N' ')
set @search_string = replace( @search_string, N'  ', N' ')
if len(@search_string) < 2 return
if len(@search_string) > 12 return
if ( @search_option = 0 )
begin
	-- search title
	-- make sql
	set @sql = 'select top ' +  cast( @ntop as nvarchar) + ' root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title, ndate = datediff( ss, ''1970/1/1 0:0:0'' , post_date ), read_count, status, comment_cnt , keyword ' 
		+ ' from dbo.board_' + cast ( @board_id as nvarchar) 
	set @where = replace( @search_string, ' ', '%'' and title like N''%')
	set @sql = @sql + ' where title like N''%' + @where + '%'' and status = 0 '
		+ ' ORDER by ndate desc ' 
	exec (@sql)
end
if ( @search_option = 1 ) begin
	-- search writer
	-- make sql
	set @sql = 'select top ' +  cast( @ntop as nvarchar)  + ' root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title,  ndate = datediff( ss, ''1970/1/1 0:0:0'' , post_date )  , read_count, status, comment_cnt, keyword  ' 
		+ ' from dbo.board_' + cast ( @board_id as nvarchar) 
	set @where = replace( @search_string, ' ', '%'' and char_name like N''%')
	set @sql = @sql + ' where char_name like N''%' + @where + '%''  and status = 0 '
		+ ' ORDER by ndate desc ' 
	exec (@sql)
end
if ( @search_option = 2 ) begin
	-- search title + writer
	-- make sql
	set @sql = 'select top ' +  cast( @ntop as nvarchar) + ' root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title, ndate = datediff( ss, ''1970/1/1 0:0:0'' , post_date ), read_count, status, comment_cnt , keyword ' 
		+ ' from dbo.board_' + cast ( @board_id as nvarchar) 
	set @where = replace( @search_string, ' ', '%'' and title like N''%')
	set @sql = @sql + ' where title like N''%' + @where + '%'' and status = 0 '
	set @sql = @sql + ' UNION '
	set @sql = @sql + 'select top ' +  cast( @ntop as nvarchar)  + ' root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title,  ndate = datediff( ss, ''1970/1/1 0:0:0'' , post_date )  , read_count, status, comment_cnt, keyword  ' 
		+ ' from dbo.board_' + cast ( @board_id as nvarchar) 
	set @where = replace( @search_string, ' ', '%'' and char_name like N''%')
	set @sql = @sql + ' where char_name like N''%' + @where + '%''  and status = 0 '
		+ ' ORDER by ndate desc ' 
	exec (@sql)
end
if ( @search_option = 3 ) begin
	-- search body
	-- make sql
	set @sql = 'select top ' +  cast( @ntop as nvarchar)  + ' root_bid, thread_order, bid, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title,  ndate = datediff( ss, ''1970/1/1 0:0:0'' , post_date )  , read_count, status, comment_cnt, keyword  ' 
		+ ' from dbo.board_' + cast ( @board_id as nvarchar) 
	set @where = replace( @search_string, ' ', '%'' and char_name like N''%')
	set @sql = @sql + ' where content like N''%' + @where + '%''  and status = 0 '
		+ ' ORDER by ndate desc ' 
	exec (@sql)
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
lin_SetAnnounce
	do set  board announce
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_SetAnnounce]
	@announce_id	int,
	@title		nvarchar(128),
	@content	nvarchar(3000),
	@deleted	tinyint
AS
SET NOCOUNT ON
if @deleted = 1 
begin
	update board_announce set deleted = 1 where announce_id = @announce_id
end else begin
	if (@title is null ) or (@content is null)
	begin
		update board_announce set deleted = 0 where announce_id = @announce_id
	end else begin
		update board_announce set title=@title, content=@content where announce_id = @announce_id
	end
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
lin_SetBoardAdmin
	set board admin
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_SetBoardAdmin]
	@char_id	int,
	@node_admin	nvarchar(50),
	@bid		int,
	@world_id	smallint,
	@permission	int
AS
SET NOCOUNT ON
declare @boardcount int
select @boardcount = count(*) from board_list (nolock) where bid = @bid
if @boardcount >0
begin
	update board_list set admin = @node_admin where bid = @bid and world_id = @world_id
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
lin_SetBoardRights
	do set board permisssion
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_SetBoardRights]
	@type		int,
	@char_id	int,
	@pledge_id	int,
	@bid		int,
	@world_id	int,
	@permission	int
AS
SET NOCOUNT ON
declare @scount int
set @scount = 0
if ( @type  = 1 )
begin
	-- char_id, bid 
	select @scount = count(*) from board_rest (nolock) 
	where char_id = @char_id and bid = @bid and world_id = @world_id
	
	if ( @scount > 0 )
	begin
		update board_rest set permission = @permission where char_id = @char_id and bid = @bid and world_id = @world_id
	end else begin
		insert into board_rest ( char_id, pledge_id, bid, world_id, permission  ) values
		( @char_id, 0, @bid, @world_id, @permission )
	end
end 
else if ( @type = 2)
begin
	-- pledge_id, bid
	select @scount = count(*) from board_rest (nolock) 
	where pledge_id = @pledge_id and bid = @bid and world_id = @world_id	
	if ( @scount > 0 )
	begin
		update board_rest set permission = @permission where pledge_id = @pledge_id and bid = @bid and world_id = @world_id
	end else begin
		insert into board_rest ( char_id, pledge_id, bid, world_id, permission  ) values
		( 0, @pledge_id, @bid, @world_id, @permission )
	end
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
lin_SetFavorite
	do set board tree info
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_SetFavorite]
	@char_id		int,
	@world_id		int,
	@fav_name		nvarchar(50),
	@url_string		nvarchar(50),
	@arg1			int,
	@arg2			int,
	@arg3			int,
	@arg4			int,
	@arg5			int,
	@arg6			nvarchar(20)
AS
SET NOCOUNT ON
declare @rowcount int
set @rowcount = 0
select @rowcount = count(*) from board_favorite (nolock)
where char_id = @char_id and world_id = @world_id and url_string = @url_string and arg1 = @arg1 and arg2 = @arg2 and arg3 = @arg3 and arg4 = @arg4 and arg5 = @arg5 and arg6 = @arg6
if ( @rowcount = 1 )
begin
	update board_favorite 
	set make_date = getdate()
	where  char_id = @char_id and world_id = @world_id and url_string = @url_string and arg1 = @arg1 and arg2 = @arg2 and arg3 = @arg3 and arg4 = @arg4 and arg5 = @arg5 and arg6 = @arg6
end else begin
	insert into board_favorite( char_id, world_id, fav_name, url_string, arg1, arg2, arg3, arg4, arg5, arg6 )
	values
	(@char_id, @world_id, @fav_name, @url_string, @arg1, @arg2, @arg3, @arg4, @arg5, @arg6 )
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
lin_SetRest
	do set  board restriction
INPUT
OUTPUT
return
made by
	young
date
	2003-05-14
********************************************/
CREATE PROCEDURE [DBO].[lin_SetRest]
	@char_id	int,
	@bid		int,
	@permission	int,
	@world_id	int
AS
SET NOCOUNT ON
declare @perm int
select @perm = permission from board_rest (nolock) where char_id = @char_id and bid = @bid and world_id = @world_id
if @@ROWCOUNT < 1
begin
	insert into board_rest (char_id, bid, world_id, permission) values ( @char_id, @bid, @world_id, @permission)
end else begin
	update board_rest set permission = @permission where char_id = @char_id and bid = @bid and world_id = @world_id
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
lin_WriteArticle
	do write article 
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_WriteArticle]
	@board_id		int,
	@parent_bid		int,
	@char_id		int,
	@char_name		nvarchar(50),
	@account_id		int,
	@account_name	nvarchar(50),
	@world_id		smallint,
	@title			nvarchar(128),
	@content		nvarchar(3000),
	@ip			nvarchar(20),
	@keyword		nvarchar(20) = '' 
AS
SET NOCOUNT ON

declare @table_name nvarchar(64)
declare @sql nvarchar(4000)
declare @bid nvarchar(32)
set @table_name = 'board_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = 'select * from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
exec (@sql)
if (@@ROWCOUNT = 0) return
-- check permission
declare @per int
declare @per2 int
select @per = permission from board_list (nolock) where bid = @board_id

if ( ( @per & 4  <> 4) or ( @per & 8 <> 8) ) 
begin
	set @per2 = 0
	select @per2 = permission from board_rest (nolock) where bid = @board_id and char_id = @char_id and world_id = @world_id

	if ( ( @per2 & 4  <> 4) or ( @per2 & 8 <> 8) ) return
end 

-- change title, content
set @title =  replace ( @title , N'''', nchar(127) )
set @content = replace ( @content , N'''', nchar(127) )


-- board table exists,,, insert article ^^
-- begin tran
if @parent_bid = 0 
begin
	-- insert as new thread
	set @sql = N'insert into dbo.' + @table_name + N' (root_bid, thread_order, step,  parent_bid, char_id, char_name, account_id, account_name, world_id, title , ip, keyword ) values ( '
		+ N' 0 , ' 
		+ N' 0 , ' 
		+ N' 0 , ' 
		+ N' 0 , ' 
		+ cast( @char_id as nvarchar) + N' , N''' 
		+ @char_name + N'''  , ' 
		+ cast( @account_id as nvarchar) + N' , N''' 
		+ @account_name + '''  , ' 
		+ cast( @world_id as nvarchar) + N' , N''' 
		+ @title + N''' , N'''
		+ @ip + N'''  , N'''
		+ @keyword + '''  '
		+ ' ) '

	exec (@sql)

	if @@ERROR <> 0 goto EXEC_FAIL
	set @bid = cast (@@IDENTITY as nvarchar)

	-- update root_bid, content 
	set @sql = N' update dbo.' + @table_name + N' set root_bid  = ' + @bid + N' , parent_bid = ' + @bid + N', content = N''' + @content + ''' where bid = ' + @bid
	exec (@sql)
	if @@ERROR <> 0 goto EXEC_FAIL
	-- update articles count from board_list
	set @sql = 'update board_list set articles = articles + 1, new_articles = new_articles + 1 where bid = ' +  cast(@board_id as nvarchar)
	exec (@sql)
	if @@ERROR <> 0 goto EXEC_FAIL
--	commit tran
	return
end 
-- insert as reply for one thread
set @sql = 'select * from dbo.' + @table_name + ' (nolock) where bid = ' + cast(@parent_bid as  nvarchar)
exec (@sql)
if @@ROWCOUNT = 0 goto EXEC_FAIL
set @sql = N'insert into dbo.' + @table_name + N' (root_bid, thread_order, step, parent_bid, char_id, char_name, account_id, account_name, world_id, title, ip, keyword ) values ( '
		+ N' 0 , ' 
		+ N' 0 , ' 
		+ N' 0 , ' 
		+ N' 0 , ' 
		+ cast( @char_id as nvarchar) + ' , N''' 
		+ @char_name + N'''  , ' 
		+ cast( @account_id as nvarchar) + N' , N''' 
		+ @account_name + '''  , ' 
		+ cast( @world_id as nvarchar) + ' , N''' 
		+ @title + ''' , N'''
		+ @ip + '''  , N'''
		+ @keyword + '''  '
		+ ' ) '
exec (@sql)
if @@ERROR <> 0 goto EXEC_FAIL
set @bid = cast (@@IDENTITY as nvarchar)
-- update content 
set @sql = N' update dbo.' + @table_name + N' set content = N''' + @content + ''' where bid = ' + @bid
exec (@sql)
if @@ERROR <> 0 goto EXEC_FAIL
-- update root_bid, thread_order, step, parent_bid
set @sql = '  declare @p_root_bid int '
	+ ' declare @p_thread_order smallint '
	+ ' declare @p_step smallint ' 
	+ ' declare @thread_order_cmp smallint '
	+ ' select @p_root_bid = root_bid, @p_thread_order=thread_order, @p_step=step from dbo.' + @table_name  + ' (nolock) where bid = ' + cast(@parent_bid as nvarchar)
	+ ' select @thread_order_cmp = max( thread_order)  from dbo.' + @table_name + ' (nolock) where parent_bid = ' + cast(@parent_bid as nvarchar)
	+ ' if @thread_order_cmp is null '
		+ ' select @thread_order_cmp = max( thread_order)  from dbo.' + @table_name + ' (nolock) where bid = ' + cast(@parent_bid as nvarchar) 
	+ ' update dbo.' + @table_name + ' set thread_order = thread_order + 1 where root_bid = @p_root_bid and thread_order > @thread_order_cmp '
	+ ' update dbo.' + @table_name + ' set root_bid=@p_root_bid, thread_order = @thread_order_cmp + 1 , step = @p_step + 1 , parent_bid = ' + cast ( @parent_bid as nvarchar) + ' where bid = ' + @bid
exec (@sql)
if @@ERROR <> 0 goto EXEC_FAIL
-- update articles count from board_list
set @sql = 'update board_list set articles = articles + 1 , new_articles = new_articles + 1  where bid = ' +  cast(@board_id as nvarchar)

exec (@sql)
if @@ERROR <> 0 goto EXEC_FAIL
-- commit tran
return
EXEC_FAIL:
--	rollback tran

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
lin_WriteComment
	do write article 
INPUT
OUTPUT
return
made by
	young
date
	2003-04-22
********************************************/
CREATE PROCEDURE [DBO].[lin_WriteComment]
	@board_id		int,
	@bid			int,
	@char_id		int,
	@char_name		nvarchar(50),
	@account_id		int,
	@account_name	nvarchar(50),
	@world_id		smallint,
	@comment		nvarchar(128)
AS
SET NOCOUNT ON
declare @table_name nvarchar(64)
declare @sql nvarchar(1024)
set @table_name = 'comment_' + cast(@board_id as nvarchar)
-- check board_#### 
set @sql = 'select * from dbo.sysobjects (nolock) where name = ''' + @table_name + ''' '
exec (@sql)
if (@@ROWCOUNT = 0) return
-- check permission
declare @per int
declare @per2 int
select @per = permission from board_list (nolock) where bid = @board_id
if (@per = 4)
begin
	set @per2 = 0
	select @per2 = permission from board_rest (nolock) where bid = @board_id and char_id = @char_id	
	if @per2 = 0
	begin
		return
	end
end
-- board table exists,,, insert comment  ^^
--begin tran
	-- insert as new thread
	set @sql = N'insert into dbo.' + @table_name + N' ( bid, char_id, char_name, account_id, account_name, world_id, comment ) values ( '
		+ cast( @bid as nvarchar) + N' , ' 
		+ cast( @char_id as nvarchar) + N' , N''' 
		+ @char_name + N'''  , ' 
		+ cast( @account_id as nvarchar) + N' , N''' 
		+ @account_name + N'''  , ' 
		+ cast( @world_id as nvarchar) + N' , N''' 
		+ @comment + N'''  '
		+ N' ) '
	exec (@sql)
	if @@ERROR <> 0 goto EXEC_FAIL
	set @sql = ' update dbo.board_' + cast( @board_id  as nvarchar)  + ' set comment_cnt = comment_cnt + 1 where  bid = ' +  cast( @bid as nvarchar) 
	exec (@sql)
	if @@ERROR <> 0 goto EXEC_FAIL
--commit tran
return
EXEC_FAIL:
--	rollback tran

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

