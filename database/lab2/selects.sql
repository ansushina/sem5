
select * from dbo.Label;
select * from dbo.Artist;
select * from dbo.Composer;
select * from dbo.Song;
select * from dbo.MusicVideo;
select * from dbo.sc;
select * from dbo.sa;


--1 Инструкция SELECT, использующая предикат сравнения.
-- все пары лейблов из одной страны
select l1.country, l1.title, l2.title
from dbo.label as l1 join  dbo.label as l2 on l1.country = l2.country
where l1.labelid <> l2.labelid and l1.country='Congo'
order by l1.country, l1.title;

--2 Инструкция SELECT, использующая предикат BETWEEN.
-- все артисты от 18 до 30
select distinct a.name, a.age
from dbo.artist a
where a.age between 18 and 30
order by age;

select distinct a.name, a.age
from dbo.artist a
where a.age > 30;

--3 Инструкция SELECT, использующая предикат LIKE.
-- всех артистов заканчивающиеся на ней
select distinct a.name, a.age
from dbo.artist a
where a.name like '%ney';

--4 Инструкция SELECT, использующая предикат IN с вложенным подзапросом.
-- всех артистов компании которых с кубы
select name, surname, age, sex, labelid
from dbo.artist a
where a.labelid in (
    select labelid
    from dbo.label l
    where l.country = 'Congo'
    )
order by labelid

--5 Инструкция SELECT, использующая предикат EXISTS с вложенным подзапросом.
-- выбрать все песни для которых неизвестен артист
select *
from dbo.song as s1 left join dbo.sa on s1.songid = sa.songid
where exists (
    select  distinct dbo.song.songid
    from dbo.song left join dbo.sa on song.songid = sa.songid
    where sa.songid is null and song.songid=s1.songid order by songid )
order by s1.songid;

--6 Инструкция SELECT, использующая предикат сравнения с квантором.
-- вывести всех артистов старше ртистов из мальты
select name, surname, age, sex, country
from dbo.artist
where age > all (
    select age
    from dbo.artist
    where country='Malta'
    )
order by age;

--7 Инструкция SELECT, использующая агрегатные функции в выражениях столбцов.
-- средний возраст артистов из каждой страны
select country, avg(age) as avg, max(age)/min(age) as diff, min(age), max(age), count(*)
from dbo.artist
group by country
order by count

--8 Инструкция SELECT, использующая скалярные подзапросы в выражениях столбцов.
-- подсчитываем количество песен у каждого артиста младше 30
select name, surname, age, sex,
       (select count(*)
           from dbo.sa
           where sa.artistid = a.artistid) as songcnt
from dbo.artist a
where age < 30 order  by songcnt;

--9 Инструкция SELECT, использующая простое выражение CASE.
-- добавим стоблец с выводом каких-то данных о возрасте
SELECT name,
    CASE age
    WHEN 90 THEN 'vary old'
    WHEN 15 THEN 'vary young'
    ELSE ' normal'
    END AS age
FROM dbo.artist;
--10 Инструкция SELECT, использующая поисковое выражение CASE.
-- поделим всех артистов на три группы и запишем это в новый столбец
select name, surname, age, sex,
       case
           when age > 80 then 'oldest'
            when age  > 40 then 'middle'
            else 'young and free'
            end as p
from dbo.artist
order by age;

--11 Создание новой временной локальной таблицы из результирующего набора данных инструкции SELECT.
-- новая таблица с артистами и подсчетом количества песен у них
select a.artistid, name, surname, count(*)
into something
from dbo.artist a join dbo.sa on a.artistid = sa.artistid
group by a.artistid

select * from something;
drop table something;

--12 Инструкция SELECT, использующая вложенные коррелированныеподзапросы в качестве производных таблиц в предложении FROM.
 -- все артисты, компании которых с Конго
select *
from dbo.artist left join
    (
        select labelid, title, country
        from dbo.label
        where country = 'Congo'
        ) as dd on artist.labelid = dd.labelid
where dd.labelid is not null
order by name, surname

-- все ртисты из компаний в которых 5 артистов
select name, surname,title, cnt
from dbo.artist left join
     (
         select dbo.label.labelid, title, count(*) as cnt
         from dbo.label join dbo.artist on label.labelid = artist.labelid
         group by dbo.label.labelid, title
         order by labelid
     ) as dd on dd.labelid = artist.labelid
where cnt = 5
order by title

--13 Инструкция SELECT, использующая вложенные подзапросы с уровнем вложенности 3.
-- выбрать все компании, в которых состоят самые старые артисты
select title, name, surname, age
from dbo.label join (
    select artistid, age, name, surname, labelid
    from dbo.artist a
    where age = (
        select max(age)
        from dbo.artist
    )
) as dd on dd.labelid = dbo.label.labelid

--14 Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING
-- количество артистов в лейбле
select dbo.label.labelid, title, count(*) as cnt
         from dbo.label join dbo.artist on label.labelid = artist.labelid
         group by dbo.label.labelid, title
         order by cnt

--15 Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY и предложения HAVING
-- все компании, в которых количество артистов больше среднего
select dbo.label.labelid, title, count(*) as cnt
from dbo.label join dbo.artist on label.labelid = artist.labelid
group by dbo.label.labelid, title
having count(*) > (
    select avg(cnt) from (
    select dbo.label.labelid, count(*) as cnt
    from dbo.label join dbo.artist on label.labelid = artist.labelid
    group by dbo.label.labelid) as aa
    )
order by cnt

--16 Однострочная инструкция INSERT, выполняющая вставку в таблицу однойстроки значений.
INSERT  into dbo.label(labelid, title, country, creator)
VALUES (999, 'MY LABEL', NULL, 'VASYA PUPKIN');

select * from dbo.label where label.title = 'MY LABEL';

--17 Многострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса.
INSERT INTO dbo.sa (id, songid, artistid)
select songid+2000 as id, songid, artistid
       from dbo.song, dbo.artist
        where song.title like '%am' and artist.name='Sunny';

select * from dbo.sa join dbo.song on sa.songid = song.songid where song.title like '%am'

--18 Простая инструкция UPDATE.
UPDATE dbo.song
SET title = 'UVUVUVU'
WHERE songid = 1002;

select * from dbo.song order by songid;

--19 Инструкция UPDATE со скалярным подзапросом в предложении SET.
UPDATE dbo.artist
SET age =
(
SELECT AVG(age)
FROM dbo.composer
)
WHERE artistid = 1003;

select * from dbo.artist order by artistid;

--20 Простая инструкция DELETE.
DELETE from dbo.sa
WHERE artistid = 1002;

select * from dbo.sa where  artistid = 1002;

--21 Инструкция DELETE с вложенным коррелированным подзапросом в предложении WHERE.
DELETE FROM dbo.sa
WHERE songid IN
(
SELECT song.songid
FROM dbo.song left join  dbo.sc on song.songid = sc.songid
WHERE sc.songid is null
)

select * from dbo.sa
WHERE songid IN
(
SELECT song.songid
FROM dbo.song left join  dbo.sc on song.songid = sc.songid
WHERE sc.songid is null
)

--22 Инструкция SELECT, использующая простое обобщенное табличное выражение
WITH avg_table AS
(
    select dbo.label.labelid, count(*) as cnt
    from dbo.label join dbo.artist on label.labelid = artist.labelid
    group by dbo.label.labelid
)
select dbo.label.labelid, title, count(*) as cnt
from dbo.label join dbo.artist on label.labelid = artist.labelid
group by dbo.label.labelid, title
having count(*) > (
    select avg(cnt) from avg_table)
order by cnt;

--23 Инструкция SELECT, использующая рекурсивное обобщенное табличное выражение.

alter table dbo.artist add constraint FK_LA foreign key (labelID) references dbo.label(labelid);


select a.name, a.age  from
(select artistid, name, surname, age
        from dbo.artist
        where age = (
            select max(age)
            from dbo.artist)) as aa join dbo.artist a  on aa.age = a.age+30

select *
from dbo.artist where age = 30


with recursive rec(artistid, name, surname, age) as
    (
        select artistid, name, surname, age
        from dbo.artist
        where age = (
            select max(age)
            from dbo.artist)

        union all

        select a.artistid, a.name, a.surname, a.age
        from dbo.artist a join rec on rec.age = a.age+30
    )

select artistid, age, count(*)
from rec
group by artistid, age
order by age;

--24 Оконные функции. Использование конструкций MIN/MAX/AVG OVER()
SELECT *,
AVG(age) OVER(partition by sex) AS AvgAge, MIN(age) OVER(partition by sex) AS Min,
MAX(age) OVER(partition by sex) AS MaxP
FROM dbo.artist;


--25 оконные функции для устранения дублей
select * from (
select name, surname, age, country, sex,
       row_number() over (partition by a.artistid) as row
FROM dbo.artist a join dbo.sa on sa.artistid = a.artistid) as aa
where row = 1;
