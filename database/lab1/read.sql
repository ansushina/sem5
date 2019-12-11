

COPY dbo.label(labelid, title, country, creator )
FROM '/tmp/labels.csv' DELIMITER ';' CSV;


COPY dbo.artist(artistid,age,country,name,surname,sex, labelid)
FROM '/tmp/artist.csv' DELIMITER ';' CSV;

COPY dbo.composer(composerid,age,country,name,surname,sex, labelid)
FROM '/tmp/composers.csv' DELIMITER ';' CSV;

copy dbo.musicvideo(musicvideoid, title, producer)
    FROM '/tmp/musicvideos.csv' delimiter ';' csv;

COPY dbo.song(songid, title, musicvideoid)
FROM '/tmp/songs.csv' DELIMITER ';' CSV;

copy dbo.sa (id, songid, artistid) FROM '/tmp/sa.csv' delimiter ';' csv;

copy dbo.sc (id, songid, composerid) from '/tmp/sc.csv' delimiter ';' csv;

select * from dbo.composer;
