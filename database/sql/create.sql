CREATE DATABASE MusicLabelsDB;/*  */
go


USE MusicLabelsDB
GO

create schema dbo;
go

IF OBJECT_ID('dbo.Label', 'U') IS NOT NULL
DROP TABLE dbo.Label
GO
create table dbo.Label(
    LabelID int not null PRIMARY KEY IDENTITY(1,1),
    CraeteDate date,
    Title varchar(30),
    Country varchar(40),
    Creator varchar(50)
);
go

IF OBJECT_ID('dbo.Artist', 'U') IS NOT NULL
DROP TABLE dbo.Artist
GO
create table dbo.Artist(
    ArtistID int not null PRIMARY KEY IDENTITY(1,1),
    Name varchar(30), 
    Surname varchar(30),
    Age int not null,
    DebutDate date,
    Country varchar(30),
    Sex varchar(6),
    LabelID int not null
);
go

IF OBJECT_ID('dbo.Composer', 'U') IS NOT NULL
DROP TABLE dbo.Composer
GO
create table dbo.Composer(
    ComposerID int not null PRIMARY KEY IDENTITY(1,1),
    Name varchar(30), 
    Surname varchar(30),
    Age int not null,
    DebutDate date,
    Country varchar(30),
    Sex varchar(6),
    LabelID int not null
);
go

IF OBJECT_ID('dbo.MusicVideo', 'U') IS NOT NULL
DROP TABLE dbo.MusicVideo
GO
create table dbo.MusicVideo(
    MusicVideoID int not null PRIMARY KEY IDENTITY(1,1),
    Title varchar(30),
    ReleaseDate date,
    Producer varchar(30)
);
go


IF OBJECT_ID('dbo.Song', 'U') IS NOT NULL
DROP TABLE dbo.Song
GO
create table dbo.Song(
    SongID int not null PRIMARY KEY IDENTITY(1,1),
    Title varchar(30),
    ReleaseDate date,
    MusicVideoID int not null
);
go

select * from dbo.Label;
GO
select * from dbo.Artist;
GO
select * from dbo.Composer;
GO
select * from dbo.Song;
GO
select * from dbo.MusicVideo;

select * from sys.all_objects 
where type='u';

select tbl.name , FK_SA.*
 from sys.Objects FK_SA
 inner join 
  sys.Objects tbl
 on FK_SA.parent_object_id = tbl.Object_id where FK_SA.type in ('PK', 'f');