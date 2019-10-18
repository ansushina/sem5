
ALTER TABLE dbo.artist ADD
CONSTRAINT artist_age_chk CHECK (age > 0);

ALTER TABLE dbo.composer ADD
CONSTRAINT composer_age_chk CHECK (age > 0);

alter table dbo.Song add constraint FK_MV foreign key (musicvideoid) references dbo.musicvideo (MusicVideoID);
 
alter table dbo.artist add constraint FK_LA foreign key (labelID) references dbo.label(labelid);
 
alter table dbo.composer add constraint FK_LC foreign key (labelID) references dbo.label(labelid);

create table dbo.SA (
    ID int not null primary key,
    SongID int not null,
    ArtistID int not null
);
 
create table dbo.SC (
    ID int not null primary key,
    SongID int not null,
    ComposerID int not null
);
 
alter table dbo.SA add constraint FK_SA foreign key (SongID) references dbo.song (SongID);
 
alter table dbo.SA add constraint FK_artist foreign key (ArtistID) references dbo.artist (ArtistID);

alter table dbo.SC add constraint FK_SC foreign key (SongID) references dbo.song (SongID);
 
alter table dbo.SC add constraint FK_composer foreign key (ComposerID) references dbo.composer (ComposerID);
 