--CREATE DATABASE MusicLabelsDB;/*  */

create schema dbo;

create table dbo.Label(
    LabelID int not null PRIMARY KEY ,
    CraeteDate date,
    Title varchar(50),
    Country varchar(100),
    Creator varchar(50)
);



create table dbo.Artist(
    ArtistID int not null PRIMARY KEY,
    Name varchar(50),
    Surname varchar(50),
    Age int not null,
    DebutDate date,
    Country varchar(100),
    Sex varchar(6),
    LabelID int not null
);

create table dbo.Composer(
    ComposerID int not null PRIMARY KEY,
    Name varchar(30), 
    Surname varchar(30),
    Age int not null,
    DebutDate date,
    Country varchar(100),
    Sex varchar(6),
    LabelID int not null
);

create table dbo.MusicVideo(
    MusicVideoID int not null PRIMARY KEY,
    Title varchar(30),
    ReleaseDate date,
    Producer varchar(30)
);

create table dbo.Song(
    SongID int not null PRIMARY KEY,
    Title varchar(30),
    ReleaseDate date,
    MusicVideoID int not null
);


select * from dbo.Label;
select * from dbo.Artist;
select * from dbo.Composer;
select * from dbo.Song;
select * from dbo.MusicVideo;

select * from dbo.Artist where labelid = 1027;