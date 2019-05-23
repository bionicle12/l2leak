if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[server]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[server]
GO

CREATE TABLE [dbo].[server] (
	[id] [int] NOT NULL ,
	[name] [varchar] (50) NOT NULL ,
	[ip] [varchar] (15) NOT NULL ,
	[inner_ip] [varchar] (15) NOT NULL ,
	[ageLimit] [int] NOT NULL ,
	[pk_flag] [tinyint] NOT NULL ,
	[kind] [int] NOT NULL ,
	[port] [int] NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[server] WITH NOCHECK ADD 
	CONSTRAINT [DF_server_pk_flag] DEFAULT (1) FOR [pk_flag],
	CONSTRAINT [DF__server__kind__6C040022] DEFAULT (0) FOR [kind],
	CONSTRAINT [DF_server_port] DEFAULT (7777) FOR [port]
GO