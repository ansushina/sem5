-- 1)
-- Из таблиц базы данных, созданной в ЛР No 1, извлечь данные с помощью
-- конструкции FOR XML; проверить все режимы конструкции FOR XML.
-- FYI: MSDN Library «Использование режима EXPLICIT совместно с
-- предложением FOR XML» - https://msdn.microsoft.com/ru-ru/library/
-- ms189068(v=sql.120).aspx.

-- сделано для json формата.

copy (select to_jsonb(dbo.label.*) from dbo.label)
to '/tmp/label_json.txt';

copy (select to_jsonb(dbo.artist.* ) from dbo.artist)
to '/tmp/artist_json.txt';

copy (select to_jsonb( dbo.composer.* ) from dbo.composer)
to '/tmp/composer_json.txt';

copy (select to_jsonb( dbo.song.* ) from dbo.song)
to '/tmp/song_json.txt';

copy (select to_jsonb( dbo.musicvideo.* ) from dbo.musicvideo)
to '/tmp/musicvideo_json.txt';

copy (select to_jsonb( dbo.sa.* ) from dbo.sa)
to '/tmp/sa_json.txt';

copy (select to_jsonb( dbo.sc.* ) from dbo.sc)
to '/tmp/sc_json.txt';

-- 2) С помощью функции OPENXML и OPENROWSET выполнить загрузку и
-- сохранение XML-документа в таблице базы данных, созданной в ЛР No 1.

-- для json

create or replace function json_parse(tablename text, path text, variadic arr text[])
returns int
as $$
    p = ""
    for i in range(len(arr)):
        p+= arr[i]
        if i != len(arr)-1:
            p += ", "
    file = open(path, "r")
    for s in file:
        #plpy.debug("INSERT INTO " + tablename + " SELECT * from jsonb_to_record('" + s + "') as x ( " + p + " ) ")
        plpy.execute("INSERT INTO " + tablename + " SELECT * from jsonb_to_record('" + s + "') as x ( " + p + " );")
    return 0
$$ language plpython2u;

create table dbo.copy_sa (
    ID int not null primary key,
    SongID int not null,
    ArtistID int not null
);

select * from json_parse('dbo.copy_sa', '/tmp/sa_json.txt',
    'ID int',
    'SongID int',
    'ArtistID int');

select * from dbo.copy_sa;
drop table dbo.copy_sa;