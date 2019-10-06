use MusicLabelsDB
GO

ALTER TABLE dbo.artist ADD
CONSTRAINT artist_age_chk CHECK (age > 0)
GO
ALTER TABLE dbo.composer ADD
CONSTRAINT composer_age_chk CHECK (age > 0)
GO

alter table dbo.Song add constraint FK_MV foreign key (musicvideoid) references dbo.musicvideo (MusicVideoID);
GO
alter table dbo.artist add constraint FK_LA foreign key (labelID) references dbo.label(labelid);
go
alter table dbo.composer add constraint FK_LC foreign key (labelID) references dbo.label(labelid);
go

create table dbo.SA (
    ID int not null primary key,
    SongID int not null,
    ArtistID int not null
);
GO
create table dbo.SC (
    ID int not null primary key,
    SongID int not null,
    ComposerID int not null
);
GO
alter table dbo.SA add constraint FK_SA foreign key (SongID) references dbo.song (SongID);
Go
alter table dbo.SA add constraint FK_artist foreign key (ArtistID) references dbo.artist (ArtistID);
go

alter table dbo.SC add constraint FK_SC foreign key (SongID) references dbo.song (SongID);
go
alter table dbo.SC add constraint FK_composer foreign key (ComposerID) references dbo.composer (ComposerID);
go