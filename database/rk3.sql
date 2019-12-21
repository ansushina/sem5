-- create database rk3;
-- create schema rk3;

create table rk3.times(
    worker_id int not null,
    w_date date,
    day varchar(15),
    time time,
    type int);


create table rk3.workers(
    id int not null primary key,
    fio varchar(100),
    birthday date,
    team varchar(100)
);


insert into rk3.times (worker_id, w_date, day, time, type) VALUES (1, '14-12-2018', 'Суббота', '9:00', 1);
insert into rk3.times (worker_id, w_date, day, time, type) VALUES (1, '14-12-2018', 'Суббота', '9:20', 2);
insert into rk3.times (worker_id, w_date, day, time, type) VALUES (1, '14-12-2018', 'Суббота', '9:25', 1);
insert into rk3.times (worker_id, w_date, day, time, type) VALUES (2, '14-12-2018', 'Суббота', '9:05', 1);
insert into rk3.times (worker_id, w_date, day, time, type) VALUES (3, '14-12-2018', 'Суббота', '9:15', 1);
insert into rk3.times (worker_id, w_date, day, time, type) VALUES (4, '14-12-2018', 'Суббота', '9:35', 1);
insert into rk3.times (worker_id, w_date, day, time, type) VALUES (4, '20-12-2019', 'Суббота', '9:35', 1);
select * from rk3.times;

insert into rk3.workers (id, fio, birthday, team) VALUES (1, 'Иванов Иван Иванович', '25-09-1990' ,'ИТ');
insert into rk3.workers (id, fio, birthday, team) VALUES (2, 'Петров Петр Петрович', '12-11-1987' ,'Бухгалтерия');
insert into rk3.workers (id, fio, birthday, team) VALUES (3, 'Петров Петр Иванович', '12-11-1976' ,'Бухгалтерия');
insert into rk3.workers (id, fio, birthday, team) VALUES (4, 'Петров Петр Иванович', '12-11-1955' ,'Бухгалтерия');

select * from rk3.workers;

drop table rk3.times;
drop table rk3.workers;

create or replace function avg_late_people()
returns int
as $$

    declare
        now_date date;
    begin
        now_date := now();
        return (select avg((now_date - birthday)/365)
            from rk3.workers w join rk3.times t on t.worker_id = w.id
            where t.time > '9:00' and t.type = 1);
    end;
    $$ language 'plpgsql';

select * from avg_late_people();

drop function avg_late_people();

create or replace function avg_late_people_2()
returns interval
as $$
    begin
        return (select avg(age(birthday))
            from rk3.workers w join rk3.times t on t.worker_id = w.id
            where t.time > '9:00' and t.type = 1);
    end;
    $$ language 'plpgsql';

select * from avg_late_people_2()


select w.team from rk3.workers w join
    (select * from rk3.times  where time > '9:00' and  type = 1 and w_date + 10 > now()) as t
        on t.worker_id = w.id
group by w.team


with max_out as (
    select max(cnt) from
    (select worker_id, count(*) as cnt
     from rk3.times
     where time between '9:00' and '18:00' and w_date = '14-12-2018'
     group by worker_id) as m
)
select * from rk3.workers w
where id in (select worker_id from
            (select worker_id, count(*) as cnt
            from rk3.times
            where time between '9:00' and '18:00' and w_date = '14-12-2018'
            group by worker_id) as m where cnt =(select * from max_out))