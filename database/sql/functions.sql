

--1) Скалярную функцию

create function dbo.maxAge()
returns integer as $$
begin
    return (select max(age) from (
        select * from dbo.artist
        union
        select * from dbo.composer) as people);
end;
$$
LANGUAGE 'plpgsql';

select dbo.maxAge();

--2) Подставляемую табличную функцию

create function dbo.artistNotInLabel()
returns table ( ArtistID int,
    Name varchar(50),
    Surname varchar(50),
    Age int,
    DebutDate date,
    Country varchar(100),
    Sex varchar(6),
    LabelID int)
    as $$
    begin
        return query(
            select a.*
            from dbo.artist a left join dbo.sa on a.artistid = sa.artistid
            where sa.songid is null
                );
    end;
    $$
language 'plpgsql';

drop function dbo.artistNotInLabel()

select * from dbo.artistNotInLabel();

--3) Многооператорную табличную функцию

create function dbo.OldMen()
returns @old table
--4) Рекурсивную функцию или функцию с рекурсивным ОТВ