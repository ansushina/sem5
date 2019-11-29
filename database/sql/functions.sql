

--1) Скалярную функцию

-- максимальный возраст среди людей

create function dbo.maxAge()
returns int as $$
begin
    return (select max(age) from (
        select * from dbo.artist
        union
        select * from dbo.composer) as people);
end;
$$
LANGUAGE 'plpgsql';

drop function  dbo.maxAge();

select dbo.maxAge();

--2) Подставляемую табличную функцию

-- артисты по возрасту

create function dbo.getArtistByAge(int)
returns setof dbo.artist
    as $$
    begin
        return query(
            select a.*
            from dbo.artist a
            where a.age = $1
                );
    end;
    $$
language 'plpgsql';

drop function dbo.getArtistByAge(int);

select * from dbo.getArtistByAge(18);

-- те же артисты по возрасту но с названиями столбцов

create function dbo.getArtist(int)
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
            from dbo.artist a
            where a.age = $1
                );
    end;
    $$
language 'plpgsql';

drop function dbo.getArtist(int);

select * from dbo.getArtist(18);

--3) Многооператорную табличную функцию

-- самые старые люди
create function dbo.OldMen()
returns setof dbo.artist
as $$
    declare
        max integer;
    begin
     max := dbo.maxAge();
    return query (select a.*
            from dbo.artist a
            where a.age = max);
    end
    $$ language 'plpgsql';

select * from dbo.OldMen();

--4) Рекурсивную функцию или функцию с рекурсивным ОТ

-- по сути это факториал

create or replace function myProduct (ct int, pr int)
returns table (counter int, product int)
language plpgsql
as $$
begin
    return query select ct, pr;
    if ct > 1 then
        return query
		select *
		from myProduct(ct - 1, pr * (ct - 1));
    end if;
end $$;

select * from myProduct(10, 10);


-- а вот это просто все люди с интервалом 5 лет в возрасте
create function dbo.recursive(artist_age int)
returns setof dbo.artist
as $$
    begin
    return query (select *
    from dbo.artist a
        where a.age = artist_age);
    if (artist_age > 6) then
        return query
        select *
        from dbo.recursive(artist_age - 5);
    end if;
    end
    $$ language 'plpgsql';

drop function dbo.recursive(artist_age int);
select * from dbo.recursive(50);

--1) Хранимую процедуру без параметров или с параметрами

select *
into dbo.people
from (
        select * from dbo.artist
        union
        select * from dbo.composer) as p;
select * from dbo.people
order by age;

create function update_people(p_age integer, p_new_age integer) returns void
as $$
    begin
    update dbo.people
    set age = p_new_age
    where age = p_age;
    end;
    $$ language 'plpgsql';

select * from update_people(15, 16);

--2) Рекурсивную хранимую процедуру или хранимую процедур с рекурсивным ОТВ

create or replace function update_names(p_age integer, p_new_name varchar(30)) returns void
as $$
    begin
    update dbo.people
    set name = p_new_name
    where age = p_age;
    if (p_age > 6) then
         perform * from update_names(p_age-5, p_new_name);
    end if;
    end;
    $$ language 'plpgsql';

select * from update_names(31,'Вася' );

select * from dbo.people
order by age;

drop table dbo.people;

--3) Хранимую процедуру с курсором

create function update_people_cursor(p_age integer, p_new_age integer) returns void
as $$
    declare
        row record;
        cur cursor for
        select * from dbo.people
        where age = p_age;
    begin
        open cur;
        loop
		    fetch cur into row;
		    exit when not found;
		    update dbo.people p
            set age = p_new_age
            where p.artistid = row.artistid;
		end loop;
        close cur;
    end;
    $$ language 'plpgsql';

select * from update_people_cursor(16, 15);
select * from dbo.people
order by age;

--4) Хранимую процедуру доступа к метаданным

select table_name, count(*) as size
into dbo.my_tables
from information_schema.tables
where table_schema not in ('information_schema','pg_catalog')
group by table_name;

select * from dbo.my_tables;

create or replace function table_size() returns void as
$$
declare
	cur cursor
	for select table_name, size
	from (
		select table_name,
		pg_relation_size(cast('dbo.' || table_name as varchar)) as size
		from information_schema.tables
		where table_schema not in ('information_schema','pg_catalog')
		order by size desc
	) AS tmp;
		 row record;
begin
	open cur;
	loop
		fetch cur into row;
		exit when not found;
		raise notice '{table : %} {size : %}', row.table_name, row.size;
		update dbo.my_tables
        set size = row.size
        where dbo.my_tables.table_name = row.table_name;
	end loop;
	close cur;
end
$$ language plpgsql;

select * from  table_size();
select * from dbo.my_tables;

--1) Триггер AFTER

create table dbo.new_people(
    id int not null,
    name varchar(30) ,
    surname varchar(40));

create  or replace function tr_func() returns trigger as
    $$
    begin
        insert into dbo.new_people (id, name, surname) values (new.artistid, new.name, new.surname);
        return new;
    end;
    $$ language 'plpgsql';

CREATE TRIGGER pInsert
after insert ON dbo.people
for each row
EXECUTE PROCEDURE tr_func();

drop function tr_func() cascade ;

insert into dbo.people(artistid, name, surname, age, country, sex)
values(3232132, 'sasaas', 'sassaas', 21, 'russia', 'male');

select * from dbo.new_people


--2) Триггер INSTEAD OF

create view dbo.people_view as
select *
from dbo.people;

create or replace function denyIn() returns trigger as
    $$
    begin
        raise notice 'Cant insert';
        return new;
    end;
    $$ language 'plpgsql' ;


CREATE TRIGGER DenyInsert
INSTEAD OF INSERT ON dbo.people_view
FOR EACH ROW
EXECUTE PROCEDURE denyIn();

insert into dbo.people_view (artistid, name, surname, age, country, sex)
values(3232132, 'sasaas', 'sassaas', 21, 'russia', 'male');


drop function denyIn() cascade ;
drop view dbo.people_view cascade ;
